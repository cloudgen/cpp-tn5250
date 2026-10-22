# Review: GNOME 5250 terminal

**Date:** 2026-10-22

The product binary is `target/exe/debug/cpp-tn5250`. The window's main view is a GTK drawing area that implements `Tn5250Terminal`. The link line uses GTK 3 and OpenSSL. It does not link WebKit or VTE.

## What was run

- `./build.sh build` produced `target/exe/debug/cpp-tn5250`.
- `tests/test-logger-folder.sh` printed `PASS logger folder`.
- `tests/test-log-verbs.sh` printed `PASS log verbs`.
- `tests/test-tn5250-terminal.sh` printed `PASS tn5250 terminal`.
- `tests/test-gnome-window.sh` on `DISPLAY=:0` printed `PASS gnome window`.
- `--version` printed `cpp-tn5250 1.0.0` and `tn5250 0.19.0`.
- A command-line host `127.0.0.1:1` with `--shutdown=2` logged `Connection refused` on stderr and the process exited 0. Shutdown dismissed the error dialog.
- With `GDK_BACKEND=x11`, the mapped window is titled `cpp-tn5250`. It shows Session and Help, Host, Map, Terminal, SSL, Verify, Ruler, Underscores, Connect, Disconnect, Device, Trace, and Extra. The drawing area is the black 5250 screen with a green cursor, the status text `5250`, and the cursor `001/001`. The footer reads Disconnected.
- The same checks were run again on 2026-10-22. `test-logger-folder.sh`, `test-tn5250-terminal.sh`, and `test-gnome-window.sh` passed together. `test-log-verbs.sh` passed when run by itself. It shares `/tmp/.app/cpp-tn5250` with the folder check, so those two scripts are run one after the other.
- A `debug:` trace with Clear Unit, Write to Display, an input field, and Insert Cursor was opened as the host. The window title included that host. The screen showed green `CPP-TN5250`, a cursor block in the field, status `5250`, `MW`, and `004/004`, and the footer `Connected`. `--shutdown=4` ended the session and the process exited 0.

The headless form check also rebuilds `ssl_ca_file=ca.pem`, `ssl_cert_file=cert.pem`, `ssl_pem_pass=phrase`, `ssl_check_exp=60`, and `env.CODEPAGE=37`. Those tokens are the curses client's extra SSL and environment options. The same `gtkterm_nav_key`, `gtkterm_translate_ctrl`, and `form_to_args` functions are the sample in the domain law mold and in `requirement-domain-tn5250.md`.

## Limit

No IBM i host was available. A live sign-on, a macro record, and a TLS handshake against a real host were not exercised. A recorded display stream was painted through the same session loop the curses client uses. The key map, attribute map, terminal geometry, and option round trip were checked without a host. Printer tools `lp5250d` and `scs2ascii` stay the upstream programs and are not the GNOME window.

## Verdict

The harness, the headless 5250 checks, the window open path, and a recorded 5250 screen pass. A full host session remains an operator check on a real system.
