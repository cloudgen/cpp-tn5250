# Requirements registry

Product law for cpp-tn5250. Rows match files in this folder. The public source repository is the project repository named by the root README Stars banner.

| Key | Area | Status | Path |
|-----|------|--------|------|
| requirement-class-software-dev | class | Active | requirement-class-software-dev.md |
| requirement-cpp-coding-style | coding | Active | requirement-cpp-coding-style.md |
| requirement-cpp-logger | logger | Active | requirement-cpp-logger.md |
| requirement-cpp-logger-folder | logger | Active | requirement-cpp-logger-folder.md |
| requirement-cpp-output | output | Active | requirement-cpp-output.md |
| requirement-cpp-json | json | Active | requirement-cpp-json.md |
| requirement-cpp-debug-mode | debug | Active | requirement-cpp-debug-mode.md |
| requirement-cpp-parameters | parameters | Active | requirement-cpp-parameters.md |
| requirement-cpp-project-structure | structure | Active | requirement-cpp-project-structure.md |
| requirement-cpp-folder | folder | Active | requirement-cpp-folder.md |
| requirement-cpp-tests | tests | Active | requirement-cpp-tests.md |
| requirement-cpp-dependencies | dependencies | Active | requirement-cpp-dependencies.md |
| requirement-cpp-global-installation | install | Active | requirement-cpp-global-installation.md |
| requirement-cpp-local-installation | install | Active | requirement-cpp-local-installation.md |
| requirement-domain-tn5250 | domain | Active | requirement-domain-tn5250.md |

The link set is GLib, GTK 3, OpenSSL, and threads. The window's main view is the 5250 terminal. The program does not link WebKit or VTE. That link rule is owned by `requirement-cpp-dependencies.md`. The 5250 session is owned by `requirement-domain-tn5250.md`. Extra tokens from the curses client, including `ssl_ca_file=`, `ssl_cert_file=`, `ssl_pem_pass=`, `ssl_check_exp=`, and `env.NAME=VALUE`, are part of that session.

The logger row owns `logger_*` in `src/main/cpp/logger.cpp` and `src/main/cpp/logger.h`, the human line `[YYYY-MM-DD HH:MM:SS] pid:<pid> [<LEVEL>] @main :] <message>`, and the dated file that stores it. The well-known levels are `INFO`, `DEBUG`, `WARNING`, `ERROR`, and `FATAL`. `test --home /tmp --log-datestamp 20261003` names `/tmp/.app/cpp-tn5250/log/cpp-tn5250-20261003.log`. `test --prefix /tmp` with the same stamp names `/tmp/var/cpp-tn5250/log/cpp-tn5250-20261003.log`. `list` prints the names in the selected directory. `show` prints the file for one datestamp.

The logger-folder row owns the application directory and the log directory. Project-base-path is the application directory for the current environment. Root or sudo uses `/var/cpp-tn5250`. Every other user uses `$HOME/.app/cpp-tn5250`. Project-log-path is that directory plus `/log`: `/var/cpp-tn5250/log` or `$HOME/.app/cpp-tn5250/log`. The project's cache path is a different directory. A normal user uses `$HOME/.cache/cache-cpp-tn5250/` or `/dev/shm/cache/cache-cpp-tn5250`. Root or sudo uses `/var/cache/cpp-tn5250/`. The test command uses `--prefix <dir>` for `<dir>/var/cpp-tn5250/log` and `--home <dir>` for `<dir>/.app/cpp-tn5250/log`. It does not read `PREFIX`, `HOME`, or the effective user id. `--prefix` wins when both switches are set.

The output row owns the human-line streams, quiet, and `--verbose`. Stdout log lines are hidden unless `--verbose` is set. `--verbose` shows them only when the run is not quiet and not JSON. The human error and fatal lines on stderr stay. `list`, `show`, `help`, `--version`, and the plan verbs are not log lines, so that gate does not hide them.

The JSON row owns JSON mode. JSON mode implies quiet. The terminal shows the JSON object and does not show another product message. `--verbose` does not add the human line.

The folder row owns `src/main/cpp`: `main.cpp`, `logger.cpp`, `logger.h`, `project.h`, `gtkterm.cpp`, `gtkterm.h`, `gnome_app.cpp`, and `gnome_app.h`. That directory is the product source root. `lib5250/` is the protocol library the same build compiles.

The coding-style row owns linkage, kebab-case, and camel-case. A translation unit is `.cpp` unless `requirement-cpp-folder.md` names a `.c` file. `logger.h` and `project.h` stay headers.

The dependencies row owns the libraries the C++ program links: GLib, GTK 3 (`gtk+-3.0`), OpenSSL (`libssl` and `libcrypto`), and threads. `./build.sh install` is that apt command. WebKit and VTE stay off the link line.

The global-installation row copies `cpp-tn5250` into `$PREFIX/bin` at mode `0755`. `PREFIX` defaults to `/usr/local`. The local-installation row copies it into `$HOME/.local/bin` at mode `0755`. Those bins are not cpp-log-path. Neither command calls `sudo`. Tests do not use `HOME`. They build one binary and run the test command. That check is `requirement-cpp-tests.md`.

`./build.sh` implements `install`, `install-local`, `install-global`, `clean`, and `build`. The primary build verbs stay in `requirement-class-software-dev.md`. Meson compiles the same sources.
