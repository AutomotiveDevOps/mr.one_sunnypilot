# Camerad Reverse Engineering Notes

## Overview

We restored the upstream `system/camerad` sources alongside Mr. One’s prebuilt binary to make static analysis possible. The shipped executable was preserved as `system/camerad/camerad.mrone`, and the restored sources mirror the upstream `sunnypilot` tree so the fork can be compared line-by-line.

The repo previously lacked the build metadata required for `scons`. We added `SConstruct` from upstream and patched it to tolerate hosts without Qt’s `qmake`, enabling artifact generation scripts without installing additional system packages. Full compilation still requires the large C++ dependency stack (capnp headers, Qt, OpenCL toolchain, etc.), but the analysis below does **not** depend on producing a new `camerad` binary.

## File Inventory

| Location | Notes |
| --- | --- |
| `system/camerad/camerad.mrone` | Original Mr. One binary renamed for reference. |
| `system/camerad/` (sources) | Restored upstream C++ sources (`main.cc`, `cameras/`, `sensors/`, tests). |
| `SConstruct` | Upstream build script with a fallback when `qmake` is missing. |
| `artifacts/upstream/camerad_functions_from_source.txt` | Function list generated with `ctags` from restored sources. |
| `artifacts/mrone/camerad_functions.txt` | Function symbols found in the Mr. One binary (demangled). |
| `artifacts/mrone/camerad_globals.txt` | Global/object symbols in the binary (demangled). |
| `artifacts/mrone/camerad_symbols.txt` | Raw `nm` output for completeness. |
| `artifacts/mrone/camerad_disassembly.txt` | Capstone-produced disassembly chunked per function. |

## Symbol Comparison Highlights

* The binary still exports `camerad_thread()`, `CameraState::{init,set_camera_exposure,sendState}`, and all Spectra camera routines (`SpectraCamera::configISP`, `SpectraCamera::processFrame`, etc.), matching the upstream sources.
* Driver camera hooks are present even on the Lite hardware:
  * Function `cereal::Event::Builder::initDriverCameraState()` remains compiled in.
  * Global tables `DRIVER_CAMERA_CONFIG` appear three times (`0x844d0`, `0x84778`, `0x84820`).
  * Numerous driver-topic Cap’n Proto strings are embedded (e.g., `driverMonitoringState`, `DriverTooDistracted`).
* Lambdas that `ctags` reports as `__anon…` are optimized away or merged, which is why they do not appear in the binary symbol list. Similarly, inline helpers such as `get_gain_factor()` and `power_set_wait()` are folded into their callers.
* The binary contains many additional utility routines (e.g., JSON helpers, messaging plumbing) because it links against the prebuilt `common` and `cereal` objects that Mr. One ships as `.so` files. These show up in `artifacts/mrone/camerad_functions.txt` as extra demangled names after namespace stripping.

## Disassembly Notes

* `artifacts/mrone/camerad_disassembly.txt` groups each function with its AArch64 disassembly. Use it to trace branches or search for literal references. Example entry: `Function camerad_thread() (0x2aa60, 1692 bytes)`.
* Global data in `artifacts/mrone/camerad_globals.txt` includes the persistent `Driver` configuration arrays, timing constants, and the camera register payload blocks copied from the source’s `spectra.cc` and `sensors/*.cc` tables.

## Build Status

* `SConstruct` now tolerates missing `qmake`, but a full `scons -u system/camerad` build still fails without the broader C++ toolchain (Cap’n Proto headers, Qt SDK, OpenCL libs, etc.). Those dependencies were deliberately removed from the fork in favor of prebuilt `.so` artifacts. Reintroducing them is out-of-scope for this pass.
* The added Python environment (`venv/`) hosts `capstone`, `pyelftools`, and `cxxfilt` used by the disassembly scripts.

## Next Steps

1. If a reproducible Mr. One build is desired, the missing upstream libraries (`common/*.cc`, `cereal/messaging/*.cc`, Cap’n Proto headers, Qt) must be restored alongside this camerad tree.
2. Use the generated disassembly and symbol tables to diff against a freshly built upstream `camerad` (once available) to pinpoint binary-level patches.
3. Extend this analysis with scriptable comparisons (e.g., pattern-matching register writes) to highlight practical behavior differences, especially around the absent driver camera pipeline.


