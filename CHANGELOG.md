# Changelog

## 1.0.0 — 2026-10-22

- Product identity is cpp-tn5250, bootstrapped from the cpp-logger harness.
- The window's main view is an interactive 5250 terminal on GTK 3. The protocol library remains tn5250 0.19.0.
- Logger verbs `test`, `list`, and `show` keep the ChronicleLogger paths under `/var/cpp-tn5250/log` and `$HOME/.app/cpp-tn5250/log`.
- Headless checks cover keys, attributes, terminal geometry, and session-option round trip, including `ssl_ca_file=`, `ssl_cert_file=`, `ssl_pem_pass=`, `ssl_check_exp=`, and `env.CODEPAGE=`.
- Public repository: https://github.com/cloudgen/cpp-tn5250
