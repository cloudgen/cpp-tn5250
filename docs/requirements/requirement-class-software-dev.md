**file**: docs/requirements/requirement-class-software-dev.md
**Status**: Active
**Area**: class
**Key**: requirement-class-software-dev
**Updated**: 2026-10-22
**Philosophy**: CIAO v2.10.2 / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered / Over-protect)

## 1. Purpose

This workspace is a software product people install and run: a GNOME program whose main view is an interactive 5250 terminal. This file is the class law and the residual home for stack facts that no peer requirement owns. The coding-style file is the specialize-in home for portable learned lessons. Without that file, those lessons arrive raw.

### 1.1 Human-facing

**In one sentence:** You run cpp-tn5250 on this Linux login; the program opens a GTK window whose main view is the 5250 screen and writes ChronicleLogger lines; this file only records what kind of software project this folder is.

| Box | Meaning | Example |
|-----|---------|---------|
| You / this login | The person who builds or launches the program | `./build.sh build` then run the binary |
| The other role | The GNOME program | It opens the 5250 window and prints through `logger_*` |
| Not this file | Feature behavior, build commands, and coding rules | Those live in the peer requirements |

| Includes | Excludes |
|----------|----------|
| Language, compilers, and which build tool is primary | Bookmark URLs, cookie schema, and menu layout |
| The decision that there is no approval desk | A second class file for another kind of work |

| Surface | What you open | What for |
|---------|---------------|----------|
| `src/main/cpp/project.h` | Runtime name and start page | Machine identity |
| `docs/requirements/index.md` | Registry | Which requirement owns a topic |

| You do… | What it means | What you type |
|---------|---------------|---------------|
| Build the program | The primary path is the simple GCC build | `./build.sh build` |
| Read the coding rules | Portable lessons are specialized in the C++ coding-style requirement | open `requirement-cpp-coding-style.md` |

## 2. Core rules

1. This workspace is software-development. The only class file is `requirement-class-software-dev.md`.
2. This file holds stack facts until a peer owns them. Peers are not copied here.
3. The primary language is C++. The ship-unit directory and its files are owned by `requirement-cpp-folder.md`. There is no Lua file. Naming is in `requirement-cpp-coding-style.md`.
4. The ship-unit compiler is system `g++`. Version policy is unconstrained: a recent toolchain that passes the build. C++ is C++17. A `.c` file named by a requirement would use `gcc` and C11. Cross-compilation is out of scope.
5. The primary build tool is `./build.sh` (`install`, `clean`, `build`). Meson is a second build file and must compile the same sources. Global and local binary place are `requirement-cpp-global-installation.md` and `requirement-cpp-local-installation.md`. The dependency set is owned by `requirement-cpp-dependencies.md`. There is no lockfile.
6. The end-user runtime is a Linux graphical session. The window is GTK 3. The developer machine needs a C++ compiler (`g++`), GLib headers, GTK 3 headers, and OpenSSL headers. Package names are owned by `requirement-cpp-dependencies.md`. The program does not link WebKit or VTE.
7. Actor / role / subject: **considered — no dest approver and no approval subject**. There is no approval desk.
8. Dest fence conditions: **considered — no dest fence conditions**. Do not invent one.
9. Coding-style related requirement: `requirement-cpp-coding-style.md`. This class file points at it and does not restate the C++ rules.
10. The ship unit does not call `sudo`. `./build.sh install` may run `sudo apt` to install host packages. That is developer bootstrap, not an in-application sudo grant. There is no sudo-command requirement.

### 2.1 Implementation notes (this project)

- Display name: `cpp-tn5250` (`PROJECT_NAME` in `src/main/cpp/project.h`).
- Runtime id: `cpp-tn5250` (`PROJECT_ID`).
- Version macros in `project.h` are the runtime version `1.0.0`. `project.ini` `VERSION` and `meson.build` use the same `1.0.0`. The protocol library version stays `0.19.0` from `config.h`. `project.h` does not define `VERSION`.
- This folder is not a git repository. No origin URL is recorded.
- Host packages and link modules are owned by `requirement-cpp-dependencies.md`.

## 3. Residual ownership

| Topic | Owner |
|-------|--------|
| Class, languages, compilers, primary build tool | this file |
| C++ source folder `src/main/cpp` | `requirement-cpp-folder.md` |
| C++ coding rules | `requirement-cpp-coding-style.md` |
| Logger line and dated log file | `requirement-cpp-logger.md` |
| cpp-base-path and cpp-log-path | `requirement-cpp-logger-folder.md` |
| Console output, quiet, and verbose | `requirement-cpp-output.md` |
| 5250 session, keys, and the window view | `requirement-domain-tn5250.md` |
| JSON mode | `requirement-cpp-json.md` |
| Debug flag | `requirement-cpp-debug-mode.md` |
| Kebab-case and camel-case | `requirement-cpp-coding-style.md` |
| C++ link and apt dependencies | `requirement-cpp-dependencies.md` |
| Flags and environment variables | `requirement-cpp-parameters.md` |
| `./build.sh` binary path `target/exe/debug/cpp-tn5250` | this file |
| Meson source list | `requirement-cpp-folder.md` |
| Global installation | `requirement-cpp-global-installation.md` |
| Local installation | `requirement-cpp-local-installation.md` |

## 4. Protection rule

Future editors must not add a second class file, invent an approver, invent a dest fence, or move the C++ coding rules out of `requirement-cpp-coding-style.md`.

## 5. Related artifacts

| Artifact | Role |
|----------|------|
| `docs/requirements/index.md` | Registry |
| `docs/requirements/requirement-cpp-coding-style.md` | Coding-style home |
| `src/main/cpp/project.h` | Runtime identity |
| `docs/requirements/requirement-cpp-dependencies.md` | Libraries and apt packages |

**Last updated**: 2026-10-03
**Owner**: Project class
