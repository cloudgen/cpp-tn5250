# cpp-tn5250

[![Stars](https://img.shields.io/github/stars/cloudgen/cpp-tn5250?style=social)](https://github.com/cloudgen/cpp-tn5250)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE.md)
[![Version](https://img.shields.io/badge/Version-1.0.0-blue.svg)](src/main/cpp/project.h)
[![CIAO](https://img.shields.io/badge/Philosophy-CIAO%20Defensive-purple.svg)](CIAO-PRINCIPLES.md)
[![UI](https://img.shields.io/badge/UI-GNOME%205250-brightgreen.svg)]()

**cpp-tn5250** is a GNOME 5250 terminal. The main view is the interactive 5250 screen. ChronicleLogger lines use component `main`: `[YYYY-MM-DD HH:MM:SS] pid:<pid> [LEVEL] @main :] message`.

The product version is `1.0.0` in `src/main/cpp/project.h`, `project.ini`, and `meson.build`. The protocol library stays tn5250 `0.19.0`.

Upstream client notes are in `doc/UPSTREAM-tn5250.md`. The `lib5250` sources keep their LGPL terms. This application is MIT.

This project follows the **CIAO** Defensive Programming Philosophy in `CIAO-PRINCIPLES.md`.

## Features

- GTK window with Session Connect, Disconnect, and Quit, plus Help Keyboard and About
- The same session options as the curses client: `map=`, `env.TERM=`, `env.DEVNAME=`, `trace=`, `+underscores`, `+ruler`, `+ssl_verify_server`, and a host such as `ssl:host`
- Terminal types `IBM-3179-2` (24x80) through `IBM-3477-FC` (27x132). The drawing area follows the type
- Keys follow the curses client: Enter sends the screen, keypad Enter is Field Exit, F1–F12 and Shift+F1–F12 are F1–F24, Page Up rolls down, Page Down rolls up, Ctrl+Q ends the session
- SSL through OpenSSL. A trace file is opened when `trace=` is set. Extra tokens `ssl_ca_file=`, `ssl_cert_file=`, `ssl_pem_pass=`, `ssl_check_exp=`, and `env.NAME=VALUE` pass through
- `help`, `test`, `list`, and `show` stay the logger commands. Stdout log lines stay hidden unless `--verbose` is set
- Root or sudo logs in `/var/cpp-tn5250/log`. Every other user logs in `$HOME/.app/cpp-tn5250/log`

## Build

```bash
sudo apt install build-essential pkg-config meson ninja-build libglib2.0-dev libgtk-3-dev libssl-dev
./build.sh build
./target/exe/debug/cpp-tn5250
```

`./build.sh install` may use `sudo apt` for those packages. It does not copy the program. `./build.sh clean` removes only `target/` and `builddir/`.

```bash
./build.sh install-local
./build.sh install-global
```

Local installation copies the binary to `$HOME/.local/bin/cpp-tn5250` at mode `0755`. Global installation copies it to `${PREFIX:-/usr/local}/bin` when that directory is writable. Neither command calls `sudo`.

Meson compiles the same sources:

```bash
meson setup builddir --buildtype=debug
meson compile -C builddir
./builddir/cpp-tn5250
```

## Run

```bash
./target/exe/debug/cpp-tn5250
./target/exe/debug/cpp-tn5250 map=37 +ruler ssl:ibmi.example
./target/exe/debug/cpp-tn5250 --version
./target/exe/debug/cpp-tn5250 key-check
./target/exe/debug/cpp-tn5250 help
```

A host on the command line connects when the window opens. `--shutdown=1` opens the window and leaves after one second.

## Checks

The checks compile with `g++` through `tests/compile-app.sh`. They do not run `./build.sh`.

```bash
sh tests/test-logger-folder.sh
sh tests/test-log-verbs.sh
sh tests/test-tn5250-terminal.sh
sh tests/test-gnome-window.sh
```
