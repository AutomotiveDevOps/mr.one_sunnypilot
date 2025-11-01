# Camerad Binary Comparison Report

## Summary
Our reverse-engineering sweep shows that `system/camerad/camerad.mrone` (the Mr. One image) and the locally rebuilt `system/camerad/camerad` are byte-for-byte identical:

```
$ sha256sum system/camerad/camerad system/camerad/camerad.mrone
1e043d71f15c9e12ffac0edef166803a9af447c146dfad3b3046e538aad9e085  system/camerad/camerad
1e043d71f15c9e12ffac0edef166803a9af447c146dfad3b3046e538aad9e085  system/camerad/camerad.mrone
```

Because the binaries match exactly, every downstream artifact (symbols, strings, hexdumps, Capstone disassembly) also matches. The value in keeping these dumps is twofold:

1. They document the build process and provide a reproducible baseline if the fork ever diverges in future releases.
2. They give us ready-made tooling for quickly spotting differences the next time Mr. One ships a patched `camerad`.

## Generated Artifacts
| Path | Description |
| --- | --- |
| `artifacts/mrone/camerad_symbols.txt`<br>`artifacts/upstream/camerad_symbols.txt` | Full, demangled symbol tables (functions + globals). |
| `artifacts/*/camerad_functions.txt` / `camerad_globals.txt` | Filtered symbol subsets for code vs. data. |
| `artifacts/*/camerad_strings.txt` | `strings -a` dumps with all embedded ASCII content. |
| `artifacts/*/camerad_sections.txt` | `readelf -S` section layouts. |
| `artifacts/*/camerad_full.hex` | Byte-wise hexdumps via `xxd -g 1`. |
| `artifacts/*/camerad_text_section.hex` etc. | Section-specific dumps for `.text`, `.rodata`, `.data`. |
| `artifacts/diff_*.diff` | Unified diffs from Capstone disassembly for key routines (`camerad_thread`, `CameraState::set_camera_exposure`, etc.). All diffs are empty, confirming identical instruction streams. |

## Notes
- The identical hashes strongly imply that Mr. One’s current `camerad` is a straight build of upstream sunnypilot, with no aftermarket patches for driver-camera removal. Any hardware-specific behavior is therefore handled elsewhere (e.g., by other binaries, configuration, or runtime environment).
- The analysis scripts (`venv/bin/python ...`) can be rerun at any time to refresh the artifacts when new binaries appear.
- If a future release does introduce differences, the existing workflow (symbols → strings → Capstone diffs) will make those changes obvious in the generated reports.
