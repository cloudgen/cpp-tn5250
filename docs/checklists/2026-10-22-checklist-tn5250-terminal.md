# Checklist: 5250 terminal map

**Filled run** for `requirement-domain-tn5250.md` and `requirement-cpp-tests.md` §2.3.

**Date:** 2026-10-22

## Warning

Do not call `mktemp` or `mkstemp`. Do not read, expand, assign, or delete `HOME`. This check builds one binary with `g++` and does not open a window. Cleanup deletes `/tmp/cpp-tn5250-terminal-work`.

## Checks

- [x] `key-check` prints `PASS key-check`
- [x] `key-plan` contains Attention, Field Exit, F24, Enter, Roll, and Ctrl+Q
- [x] `attribute-plan` contains `0 green`, `7 nondisplay`, `16 turquoise`, and `31 nondisplay`
- [x] `screen-plan` contains `IBM-3179-2 24 80` and `IBM-3477-FC 27 132`
- [x] `session-plan` without a host exits 1 with `session-plan requires a host`
- [x] `session-plan map=37 ssl:ibmi.example` prints `host=ssl:ibmi.example` and `argv=map=37 ssl:ibmi.example`
- [x] `form-plan` rebuilds `map=37`, `+ruler`, `+underscores`, `+ssl_verify_server`, `env.TERM=IBM-3477-FC`, `env.DEVNAME=DSP01`, `trace=trace-file`, `ssl_ca_file=ca.pem`, `ssl_cert_file=cert.pem`, `ssl_pem_pass=phrase`, `ssl_check_exp=60`, `env.CODEPAGE=37`, and `ssl:ibmi.example`
- [x] Two plan verbs exit 1 with `one plan command`
- [x] `--version` prints `cpp-tn5250 1.0.0` and `tn5250 0.19.0`
- [x] `help` still contains `--verbose`, `--log-datestamp`, `/var/`, `/.app/`, `not a WebKit view`, and `ssl_ca_file=`
- [x] `tests/test-tn5250-terminal.sh` printed `PASS tn5250 terminal` on 2026-10-22

## Verdict

- [x] **Pass**
- [ ] **Revise**
- [ ] **Block**
