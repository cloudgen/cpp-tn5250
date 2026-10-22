# Checklist: GNOME window

**Filled run** for `requirement-domain-tn5250.md` and `requirement-cpp-tests.md` §2.4.

**Date:** 2026-10-22

## Warning

Do not call `mktemp` or `mkstemp`. Do not read, expand, assign, or delete `HOME`. This check builds one binary with `g++`, opens the window on `DISPLAY`, and leaves after one second. Cleanup deletes `/tmp/cpp-tn5250-window-work`.

## Checks

- [x] `DISPLAY` was `:0`
- [x] `--verbose --shutdown=1` prints `gnome window ready`
- [x] That run does not print WebKit
- [x] `tests/test-gnome-window.sh` printed `PASS gnome window` on 2026-10-22

## Verdict

- [x] **Pass**
- [ ] **Revise**
- [ ] **Block**
