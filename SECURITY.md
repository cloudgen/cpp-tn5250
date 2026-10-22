# Security Policy

**cpp-tn5250** is a GNOME 5250 terminal. The main view is the interactive 5250 screen. It links GTK 3 and OpenSSL. It does not embed WebKit.

## Supported versions

The 1.0.x line is supported. The protocol library version is tn5250 0.19.0 and is not a separate product release.

## What to protect

- A `trace=` file records the session byte stream. Treat it as confidential and do not leave it in a shared directory.
- `ssl:` uses the system OpenSSL trust store unless `ssl_ca_file=` names another file. `+ssl_verify_server` turns on server certificate checks. Leave verification on when the host presents a certificate you intend to trust.
- The program does not store cookies and does not call `sudo`.
- Config search reads `/usr/local/etc/tn5250rc` and `~/.tn5250rc` when those files exist. A missing file is not an error.

## Reporting a vulnerability

Email **Cloudgen Wong** <cloudgen.wong@gmail.com> with a description, the steps to reproduce, and the impact. Do not include a live session trace if it contains screen data you cannot share. Non-sensitive defects can use https://github.com/cloudgen/cpp-tn5250/issues. Do not put a session trace or a credential in a public issue.
