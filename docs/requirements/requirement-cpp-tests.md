**file**: docs/requirements/requirement-cpp-tests.md
**Status**: Active
**Updated**: 2026-10-22
**Philosophy**: CIAO v2.10.2 / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered / Over-protect)

## 1. Purpose

This file owns how the program is checked. The named check is a full-program check.

### 1.1 Human-facing

**In one sentence:** You prove a change with one compiled binary, then `test`, `list`, `show`, the 5250 plan verbs, and, on a display, the window.

| Box | Meaning | Example |
|-----|---------|---------|
| You / this login | The person who verifies | You run `tests/test-logger-folder.sh`, `tests/test-log-verbs.sh`, and `tests/test-tn5250-terminal.sh` |
| The other role | The test-plan map | It lists TP ids that are still todo |
| Not this file | The product rules those ids check | The owning requirement |

| Includes | Excludes |
|----------|----------|
| One test binary, the verbs `test`, `list`, and `show`, and the dated log file | Copying that binary into an install bin, and running `./build.sh` from these checks |

| Surface | What you open | What for |
|---------|---------------|----------|
| `./build.sh` | Compile check | The binary links |
| `docs/reviews/test-plan.md` | TP map | Status of each id |

| You do… | What it means | What you type |
|---------|---------------|---------------|
| Collect the other-user rehearsal file | One binary, then the test command | `cpp-tn5250 test --home /tmp --log-datestamp 20261003` |
| Collect the root-or-sudo rehearsal file | The same binary | `cpp-tn5250 test --prefix /tmp --log-datestamp 20261003` |
| Read the names and one file | The same binary, under the same switches | `cpp-tn5250 list --home /tmp` and `cpp-tn5250 show --home /tmp --log-datestamp 20261003` |

## 2. Core rules

Allowed:

1. `./build.sh build` compiles every ship-unit `.cpp` file and the `lib5250` sources named in `meson.build`. The checks compile one binary with `g++` through `tests/compile-app.sh` and do not run `./build.sh`, because sourcing `project.sh` installs apt packages.
2. A manual run with `DEBUG=1`, `--debug`, `--quiet`, `--json`, `help`, the verbs `test`, `list`, and `show`, or a plan verb from `requirement-domain-tn5250.md`.
3. The single-binary log-file check in §2.1.
4. The terminal check in §2.3 and the window check in §2.4.
5. The TP ids below. A TP id stays todo until that check has been run.

There is a GTK window. There is no WebKit object to test.

| TP-ID | Owner | Pass |
|-------|-------|------|
| TP-CPP-DEPENDENCIES | requirement-cpp-dependencies | `pkg-config --exists gtk+-3.0`, `libssl`, and `libcrypto` succeed. Both builds request those modules and do not request WebKitGTK or VTE |
| TP-CPP-LOGGER-FOLDER | requirement-cpp-logger-folder and requirement-cpp-logger | §2.1. One binary. `test --home /tmp --log-datestamp 20261003` writes `/tmp/.app/cpp-tn5250/log/cpp-tn5250-20261003.log`. `test --prefix /tmp` with the same stamp writes `/tmp/var/cpp-tn5250/log/cpp-tn5250-20261003.log` |
| TP-CPP-LOG-VERBS | requirement-cpp-logger | §2.2. `list` prints the dated names. `show` prints one file. A missing switch, a short stamp, a second purpose verb, and a missing file each exit 1 |
| TP-TN5250-TERMINAL | requirement-domain-tn5250 | §2.3. `key-check` prints `PASS key-check`. The plan verbs print the key, attribute, screen, and form tokens. Two plan verbs exit 1 |
| TP-GNOME-WINDOW | requirement-domain-tn5250 | §2.4. `--verbose --shutdown=1` prints `gnome window ready` on a display |

### 2.1 Single-binary log-file check

A C check is one compiled binary and the cpp-test-purpose-command `test`. It is not a copy of that binary into an install bin. This check does not call `./build.sh`, `./build.sh install-local`, or `./build.sh install-global`. It does not start a normal run, because a normal run would use the login home or `/var/cpp-tn5250`.

**Warning.** A test must not call `mktemp` or `mkstemp`. A test must not read, expand, assign, or delete `HOME` in any form. If a test sets a new home and that assignment fails, the shell keeps the original home. `rm -rf` of that value then deletes the user's files. This check uses the literal directory `/tmp` only. Cleanup deletes `/tmp/.app/cpp-tn5250` and `/tmp/var/cpp-tn5250`, removes `/tmp/.app` and `/tmp/var` only when those directories are empty, and deletes `/tmp/cpp-tn5250-folder-work`. It does not delete `/tmp` and it does not delete a home directory.

1. Compile the ship unit and `lib5250` with `tests/compile-app.sh`. App sources use `g++ -std=c++17 -Wall -Wextra -Werror`. The helper passes `pkg-config --cflags gtk+-3.0` and links `pkg-config --libs gtk+-3.0` plus `-lssl -lcrypto -pthread`. The binary is `/tmp/cpp-tn5250-folder-work/cpp-tn5250`. The helper does not run `./build.sh`.
2. Run that binary as `test` with `HOME` and `PREFIX` removed from the process. Without `--prefix` or `--home`, the process exits 1 with `test purpose command requires --prefix or --home` and creates no log file. With `--home /tmp` and no `--log-datestamp`, it exits 1 with `test purpose command requires --log-datestamp YYYYMMDD` and creates no log file. A stamp that is not eight digits exits 1 with `--log-datestamp requires YYYYMMDD` and creates no log file.
3. Run `test --home /tmp --log-datestamp 20261003 --debug` on that same binary, still with `HOME` and `PREFIX` removed, and without `--verbose`. Stdout does not show a human log line. The file `/tmp/.app/cpp-tn5250/log/cpp-tn5250-20261003.log` contains the human line whose message is `test log`. This run does not create `/tmp/var/cpp-tn5250`.
4. Run the same command with `--verbose`. Stdout shows `logger folder /tmp/.app/cpp-tn5250/log` and `log file /tmp/.app/cpp-tn5250/log/cpp-tn5250-20261003.log`. `--verbose --quiet` does not show that human line. `--verbose --json` shows the JSON object and does not show the human line.
5. Run `test --prefix /tmp --log-datestamp 20261003 --debug --verbose` on that same binary. Stdout shows `logger folder /tmp/var/cpp-tn5250/log` and `log file /tmp/var/cpp-tn5250/log/cpp-tn5250-20261003.log`. That file contains `test log`. `--prefix` wins when both `--prefix /tmp` and a different `--home` are present. The test command ignores `PREFIX`. It does not read `HOME`.

The script is `tests/test-logger-folder.sh`. The filled checklist records the same checks.

### 2.2 Log list and show

`list` and `show` are test purpose commands on the same binary. This check is `tests/test-log-verbs.sh`. The filled checklist records the same checks. It uses the literal directory `/tmp` only. It does not start a normal run. Cleanup deletes `/tmp/.app/cpp-tn5250`, `/tmp/var/cpp-tn5250`, `/tmp/cpp-tn5250-home-decoy`, `/tmp/cpp-tn5250-prefix-decoy`, those parents when empty, and `/tmp/cpp-tn5250-verb-work`.

1. Compile one binary the same way as §2.1. The binary is `/tmp/cpp-tn5250-verb-work/cpp-tn5250`.
2. `list --home /tmp` with `HOME` and `PREFIX` removed prints no names and does not create `/tmp/.app/cpp-tn5250`.
3. `test --home /tmp --log-datestamp 20261002 --quiet` and `test --home /tmp --log-datestamp 20261003 --quiet` create two files. `list --home /tmp` prints `cpp-tn5250-20261002.log` and then `cpp-tn5250-20261003.log`. A `notes.txt` file and a directory named `extra.log` in that directory are omitted.
4. `show --home /tmp --log-datestamp 20261003` prints the contents of that file, including `test log`. `show` with a datestamp that has no file exits 1. `list` and `show` do not change the file. `--quiet` and `--json` still print the names and the file, and `show --json` does not print a JSON object.
5. `list --prefix /tmp` before a prefix file exists prints no names. After `test --prefix /tmp --log-datestamp 20261003 --quiet`, `list --prefix /tmp` prints `cpp-tn5250-20261003.log` and `show --prefix /tmp --log-datestamp 20261003` prints that file. `list` without a directory switch exits 1 with `test purpose command requires --prefix or --home`. A short `--log-datestamp` exits 1 with `--log-datestamp requires YYYYMMDD`. A missing stamp on `show` exits 1 with `test purpose command requires --log-datestamp YYYYMMDD`. `test list` exits 1. `--prefix` wins over a different `--home`. `PREFIX` is ignored. A missing file exits 1 with `cannot read log file`. When the log path is a file instead of a directory, `list` exits 1 with `cannot read log directory`.

### 2.3 Terminal and session form

This check is `tests/test-tn5250-terminal.sh`. The filled checklist records the same checks. It uses `/tmp/cpp-tn5250-terminal-work` and does not open a window.

1. Compile one binary the same way as §2.1.
2. `key-check` prints `PASS key-check`. `key-plan` contains `Attention`, `Field Exit`, `F24`, `Enter`, `Roll`, and `Ctrl+Q`.
3. `attribute-plan` contains `0 green`, `7 nondisplay`, `16 turquoise`, and `31 nondisplay`. `screen-plan` contains `IBM-3179-2 24 80` and `IBM-3477-FC 27 132`.
4. `session-plan` without a host exits 1 with `session-plan requires a host`. With `map=37 ssl:ibmi.example` it prints `host=ssl:ibmi.example` and `argv=map=37 ssl:ibmi.example`.
5. `form-plan` with `map=37 +ruler +underscores +ssl_verify_server env.TERM=IBM-3477-FC env.DEVNAME=DSP01 trace=trace-file ssl_ca_file=ca.pem ssl_cert_file=cert.pem ssl_pem_pass=phrase ssl_check_exp=60 env.CODEPAGE=37 ssl:ibmi.example` rebuilds those tokens. Two plan verbs exit 1 with `one plan command`. `--version` prints `cpp-tn5250 1.0.0` and `tn5250 0.19.0`. `help` still contains `--verbose`, `--log-datestamp`, `/var/`, `/.app/`, `not a WebKit view`, and `ssl_ca_file=`.

### 2.4 Window

This check is `tests/test-gnome-window.sh`. The filled checklist records the same checks. It needs `DISPLAY`. It compiles one binary the same way as §2.1, runs `--verbose --shutdown=1` with `HOME` and `PREFIX` removed, and requires stdout to contain `gnome window ready`.

## 3. Protection rule

Future editors must not mark a TP id done in `docs/reviews/test-plan.md` until the check has been run. They must not invoke `mktemp` or `mkstemp` from `tests/test-logger-folder.sh` or `tests/test-log-verbs.sh`, and they must not expand, assign, or delete `HOME` there.

## 4. Related artifacts

| Artifact | Role |
|----------|------|
| `docs/requirements/index.md` | Registry |
| `docs/reviews/test-plan.md` | TP status |
| `build.sh` | Compile check |
| `tests/test-logger-folder.sh` | One binary and the dated log file |
| `tests/test-log-verbs.sh` | `list` and `show` on that kind of binary |
| `tests/test-tn5250-terminal.sh` | Keys, attributes, geometry, and the session form |
| `tests/test-gnome-window.sh` | Window open and shutdown |
| `docs/requirements/requirement-domain-tn5250.md` | The 5250 behavior those checks read |
| `docs/requirements/requirement-cpp-logger.md` | The file this check reads |
| `docs/requirements/requirement-cpp-logger-folder.md` | The directory this check prints |

**Last updated**: 2026-10-22
**Owner**: Tests
