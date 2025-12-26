#!/usr/bin/env python3
"""
Generate a sunset over Lake Michigan with a lighthouse image.
Generates at 1024x1024 (square) then resizes to 1920x1080.
"""

import sys
import os
from pathlib import Path
from PIL import Image

# Add tinygrad_repo to path
sys.path.insert(0, str(Path(__file__).parent / "tinygrad_repo"))

def generate_and_resize(
    prompt: str = "a sunset over lake michigan with a lighthouse",
    output_path: str = "sunset_lake_michigan_lighthouse.png",
    maintain_aspect: bool = False,
    steps: int = 10
) -> None:
    """
    Generate image at 1024x1024 then resize to 1920x1080.

    Args:
        prompt: Text prompt for image generation
        output_path: Output file path
        maintain_aspect: If True, fit within 1920x1080 (like thumbnail).
                        If False, stretch to fill 1920x1080 (distorts).
        steps: Number of diffusion steps
    """
    # Import here to avoid issues if tinygrad not available
    from examples.sdxl import SDXL, DPMPP2MSampler
    from tinygrad import Tensor, dtypes, GlobalCounters
    from tinygrad.nn.state import safe_load, load_state_dict
    from tinygrad.helpers import fetch, Timing
    from extra.bench_log import BenchEvent, WallTimeEvent
    import argparse

    # Generate at 1024x1024 (square, which works reliably)
    print(f"Generating image at 1024x1024 with prompt: '{prompt}'")
    print("This may take a while on CPU...")

    # Set CPU mode
    os.environ["CPU"] = "1"

    # Create model
    configs = {
        "SDXL_Base": {
            "model": {"adm_in_ch": 2816, "in_ch": 4, "out_ch": 4, "model_ch": 320,
                     "attention_resolutions": [4, 2], "num_res_blocks": 2,
                     "channel_mult": [1, 2, 4], "d_head": 64,
                     "transformer_depth": [1, 2, 10], "ctx_dim": 2048, "use_linear": True},
            "conditioner": {"concat_embedders": ["original_size_as_tuple", "crop_coords_top_left", "target_size_as_tuple"]},
            "first_stage_model": {"ch": 128, "in_ch": 3, "out_ch": 3, "z_ch": 4,
                                 "ch_mult": [1, 2, 4, 4], "num_res_blocks": 2, "resolution": 256},
            "denoiser": {"num_idx": 1000},
        }
    }

    model = SDXL(configs["SDXL_Base"])

    # Load weights
    default_weight_url = 'https://huggingface.co/stabilityai/stable-diffusion-xl-base-1.0/resolve/main/sd_xl_base_1.0.safetensors'
    weights = fetch(default_weight_url, 'sd_xl_base_1.0.safetensors')
    loaded_weights = load_state_dict(model, safe_load(weights), strict=False, verbose=False, realize=False)

    start_mem_used = GlobalCounters.mem_used
    with Timing("loaded weights in ", lambda et_ns: f", {(B:=(GlobalCounters.mem_used-start_mem_used))/1e9:.2f} GB loaded at {B/et_ns:.2f} GB/s"):
        with WallTimeEvent(BenchEvent.LOAD_WEIGHTS):
            Tensor.realize(*loaded_weights)
        del loaded_weights

    # Generate at 1024x1024
    width_gen = 1024
    height_gen = 1024
    N, C, F = 1, 4, 8

    c, uc = model.create_conditioning([prompt], width_gen, height_gen)
    del model.conditioner
    Tensor.realize(*c.values(), *uc.values())
    print("Created conditioning batch")

    shape = (N, C, height_gen // F, width_gen // F)
    randn = Tensor.randn(shape)

    sampler = DPMPP2MSampler(6.0)
    z = sampler(model.denoise, randn, c, uc, steps, timing=False)
    print("Created samples")
    x = model.decode(z).realize()
    print("Decoded samples")

    # Convert to image
    x = (x + 1.0) / 2.0
    x = x.reshape(3, height_gen, width_gen).permute(1, 2, 0).clip(0, 1).mul(255).cast(dtypes.uint8)
    img = Image.fromarray(x.numpy())

    # Resize to 1920x1080
    target_width = 1920
    target_height = 1080

    if maintain_aspect:
        # Maintain aspect ratio (like thumbnail) - fit within bounds
        print(f"Resizing to fit within {target_width}x{target_height} (maintaining aspect ratio)...")
        img.thumbnail((target_width, target_height), Image.Resampling.LANCZOS)

        # Create new image with target size and paste centered
        new_img = Image.new("RGB", (target_width, target_height), (0, 0, 0))
        paste_x = (target_width - img.width) // 2
        paste_y = (target_height - img.height) // 2
        new_img.paste(img, (paste_x, paste_y))
        img = new_img
    else:
        # Stretch to fill exact dimensions (distorts aspect ratio)
        print(f"Resizing to {target_width}x{target_height} (stretching to fill)...")
        img = img.resize((target_width, target_height), Image.Resampling.LANCZOS)

    # Save
    print(f"Saving to {output_path}")
    img.save(output_path, "PNG")
    print(f"Done! Image saved as {output_path}")
    print(f"Final size: {img.size[0]}x{img.size[1]}")


if __name__ == "__main__":
    import argparse
    parser = argparse.ArgumentParser(description="Generate sunset image")
    parser.add_argument("--maintain-aspect", action="store_true",
                       help="Maintain aspect ratio (fit within 1920x1080, like thumbnail)")
    parser.add_argument("--stretch", action="store_true",
                       help="Stretch to fill 1920x1080 (default)")
    parser.add_argument("--steps", type=int, default=10, help="Diffusion steps")
    parser.add_argument("--out", type=str, default="sunset_lake_michigan_lighthouse.png",
                       help="Output filename")
    args = parser.parse_args()

    maintain_aspect = args.maintain_aspect and not args.stretch

    generate_and_resize(
        maintain_aspect=maintain_aspect,
        steps=args.steps,
        output_path=args.out
    )

