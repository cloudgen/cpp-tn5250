# Checklist: list and show

**Filled run** for `requirement-cpp-logger.md` and `requirement-cpp-tests.md` §2.2.

**Date:** 2026-10-22

## Warning

Do not call `mktemp` or `mkstemp`. Do not read, expand, assign, or delete `HOME`. This check builds one binary with `g++` and uses the literal directory `/tmp`. Cleanup deletes `/tmp/.app/cpp-tn5250`, `/tmp/var/cpp-tn5250`, `/tmp/cpp-tn5250-home-decoy`, `/tmp/cpp-tn5250-prefix-decoy`, empty parents, and `/tmp/cpp-tn5250-verb-work`.

## Checks

- [x] One `g++` binary at `/tmp/cpp-tn5250-verb-work/cpp-tn5250`. The check does not run `./build.sh`
- [x] `list --home /tmp` before any file prints nothing and does not create `/tmp/.app/cpp-tn5250`
- [x] `list --home /tmp` prints `cpp-tn5250-20261002.log` then `cpp-tn5250-20261003.log`, and skips `notes.txt` and a directory named `extra.log`
- [x] `show --home /tmp --log-datestamp 20261003` prints that file, including `test log`, and does not change it
- [x] `--quiet` and `--json` still print the names and the file. `show --json` does not print a JSON object
- [x] A missing directory switch, a short stamp, and `test list` each exit 1
- [x] `--prefix` wins over `--home`. `PREFIX` is ignored
- [x] A missing file exits 1 with `cannot read log file`. A log path that is a file exits 1 with `cannot read log directory`
- [x] `tests/test-log-verbs.sh` printed `PASS log verbs` on 2026-10-22

## Verdict

- [x] **Pass**
- [ ] **Revise**
- [ ] **Block**
