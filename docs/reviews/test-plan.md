# Test plan

Proof map for cpp-tn5250. A row stays todo until its check has been run.

The main view is the GTK 5250 terminal. There is no WebKit view.

| TP-ID | Requirement | What a pass looks like | Status |
|-------|-------------|------------------------|--------|
| TP-CPP-DEPENDENCIES | requirement-cpp-dependencies | `pkg-config --exists gtk+-3.0`, `libssl`, and `libcrypto` succeed. `build.sh` and `meson.build` request those modules and do not request `webkit2gtk-4.1` or `vte-2.91`. Passed 2026-10-22 | pass |
| TP-CPP-LOGGER-FOLDER | requirement-cpp-logger-folder, requirement-cpp-logger, requirement-cpp-output | `tests/test-logger-folder.sh` builds one binary. A missing directory switch, a missing stamp, and a short stamp each exit 1 with their own sentence and create no file. Without `--verbose`, stdout has no human log line and the file still contains `test log`. `--verbose` shows the log directory. `--verbose` shows nothing human with `--quiet` or `--json`. `--home /tmp` writes `/tmp/.app/cpp-tn5250/log/cpp-tn5250-20261003.log`. `--prefix /tmp` writes `/tmp/var/cpp-tn5250/log/cpp-tn5250-20261003.log`. Passed 2026-10-22 | pass |
| TP-CPP-LOG-VERBS | requirement-cpp-logger, requirement-cpp-tests | `tests/test-log-verbs.sh` builds one binary. `list --home /tmp` prints `cpp-tn5250-20261002.log` then `cpp-tn5250-20261003.log`, and skips `notes.txt` and a directory named `extra.log`. `show` prints that file and does not change it. `--quiet` and `--json` still print it. A missing directory switch, a short stamp, and a second purpose verb exit 1. `--prefix` wins. `PREFIX` is ignored. A missing file exits 1 with `cannot read log file`. A log path that is a file exits 1. Passed 2026-10-22 | pass |
| TP-TN5250-TERMINAL | requirement-domain-tn5250 | `tests/test-tn5250-terminal.sh` prints `PASS tn5250 terminal`. `key-check` passes. Plans print the key, attribute, screen, and form tokens, including `ssl_ca_file=ca.pem`, `ssl_cert_file=cert.pem`, `ssl_pem_pass=phrase`, `ssl_check_exp=60`, and `env.CODEPAGE=37`. Two plan verbs exit 1. Passed 2026-10-22 | pass |
| TP-GNOME-WINDOW | requirement-domain-tn5250 | `tests/test-gnome-window.sh` on `DISPLAY=:0` prints `gnome window ready` and `PASS gnome window`. Passed 2026-10-22 | pass |

**Last updated**: 2026-10-22
