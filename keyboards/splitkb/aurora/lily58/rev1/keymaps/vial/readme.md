# Personal Aurora Lily58 Vial configuration

This keymap targets `splitkb/aurora/lily58/rev1` with two Liatris controllers
(`CONVERT_TO=liatris`). Firmware builds belong in GitHub Actions; no local firmware
build or flashing is part of this migration.

## Migration contract

- Base: official `vial-kb/vial-qmk` branch `vial`, commit
  `dd43959ae5c08d8a28d38a1acf7b04e86b14a344` (checked 2026-11-11).
- Preserve the nine layer IDs, Vial UID, secure unlock combination, German
  Space Cadet configuration, two encoders, RGB effects and OLED/WPM display.
- Keep personal behavior and hardware preferences in this keymap. The shared
  `lily58.c` and revision `keyboard.json` must match upstream.
- Keep the original `my-config` branch and a complete backup before migration.
- The current keyboard's `.vil` export is still pending. The C keymaps are
  fallback defaults, not evidence of the keyboard's current saved layout.

## Files and behavior

- `keymap.c`: fallback keys/encoders, stable layer IDs and OS detection callback.
- `lily58_vial.h`: shared layer names for the keymap and its display/lighting.
- `oled.c`: personal display rendering through `oled_task_user()`. Returning
  `false` suppresses the shared keyboard's default display content.
- `rgb.c`: personal layer colors and 11 modifier LED flags. Flags are applied
  during keymap initialization instead of editing the shared LED layout.
- `config.h`: nine layers, existing UID/unlock keys, German Space Cadet,
  encoder resolution 2 on both halves, RGB effects and `RGB_MATRIX_SLEEP`.
- `rules.mk`: Liatris conversion and enabled Vial/QMK settings, OLED, WPM,
  RGB Matrix, Caps Word and Repeat Key.

| ID | Layer | Activation |
| --- | --- | --- |
| 0 | Mac base | macOS/iOS detection |
| 1 | Windows base | Windows/Linux detection |
| 2 | CodenEnglish | Manual base selection |
| 3 / 4 | Mac / Windows Lower | Hold `MO(3)`; Windows overlay is derived |
| 5 / 6 | Mac / Windows Raise | Hold `MO(5)`; Windows overlay is derived |
| 7 | Adjust 1 | Hold Lower and Raise in either order |
| 8 | Adjust 2 | Manual activation, preserved for existing layouts |

The Lower layers keep the Raise thumb key as `MO(5)`; the Raise layers keep the
Lower thumb key as `MO(3)`. Mapping those keys to `MO(7)` bypasses the inputs
needed by the tri-layer callback. Verify these four positions when importing the
pending `.vil` export. Layer IDs and ordinary key assignments otherwise remain
unchanged. The three fallback base maps are still identical.

OS detection now uses `process_detected_host_os_user()` when QMK reports a
settled result, including later host changes. An unknown result preserves the
selected base, and repeated reports of the same base avoid another EEPROM write.
This removes the former nested, one-shot deferred callback.

## GitHub builds and checks

The existing CI workflow builds only this keyboard in `appdevtk/vial-qmk`, for
both `default` and `vial` with `CONVERT_TO=liatris`. Other repositories retain the
upstream mass-build jobs. Pushes, pull requests and manual workflow dispatch use
the same workflow. The QMK container digest is inherited from the recorded
upstream, and checkout initializes its submodules recursively.

Each successful firmware job uploads a separate artifact containing its UF2,
`SHA256SUMS` and `firmware-build.txt` with the source commit. Choose the **vial**
artifact for the personal configuration. Artifacts expire after 90 days; download
and retain any known-good firmware separately.

The native regression harness can also run without QMK dependencies:

```sh
python3 keyboards/splitkb/aurora/lily58/rev1/keymaps/vial/tests/check_keymap.py
```

It compiles only a small host-side harness containing the real layer/OS
callbacks. It checks 12 press/release sequences across three bases, all four
recognized OS values, an unknown host, repeated reports and a host change. It
does not build firmware or validate USB timing, split transport, EEPROM layout,
display or LEDs. The complete firmware build runs in GitHub.

## Backup and pending keyboard export

Before this migration, the original tip was saved as
`codex/backup/my-config-2026-11-11` at
`f79bb5da43ce125f910c844146ada8f0023c9f38`; `my-config` is also preserved.
Local backup files live in `.backups/2026-11-11-pre-vial-rebase/`:

- `repository.bundle`: complete repository history before the migration,
  verified with `git bundle verify`.
- `config-snapshot.tar.gz`: original Lily58/VS-Code files and Serena metadata.
- `rebased-config-snapshot.tar.gz` and `rebased-tip.txt`: state after the rebase,
  before extracting personal code.
- `SHA256SUMS`: checksums of the backup archives.

Restore into a new directory rather than resetting an active checkout:

```sh
git clone .backups/2026-11-11-pre-vial-rebase/repository.bundle ../vial-qmk-restored
git -C ../vial-qmk-restored switch my-config
```

Before a future rebase, export the active keyboard layout, retain the last
working UF2, save the source tip as a backup branch, and create a fresh Git bundle
and file snapshot. A `.vil` export backs up runtime settings; `vial.json` describes
the keyboard to the GUI and is not that export.

The latest `.vil` export is still outstanding. Do not assume source defaults
match saved keyboard settings or import an old layout without checking the layer
thumb keys above. Changing firmware/storage layouts can reset dynamic settings.
No keyboard has been flashed or reset by this migration.

After the GitHub build, verify both halves, all keys/encoders, nine layers,
Lower+Raise and release order, OS changes, OLED/WPM, RGB/suspend and Vial secure
unlock. Firmware build, source checks and hardware results are separate evidence.

Sources: [Vial porting](https://get.vial.today/docs/porting-to-vial.html),
[Vial settings and memory](https://get.vial.today/docs/firmware-size.html),
[QMK OS callbacks](https://docs.qmk.fm/features/os_detection#callbacks).
