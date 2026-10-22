**file**: docs/requirements/requirement-cpp-folder.md
**Status**: Active
**Updated**: 2026-10-22
**Philosophy**: CIAO v2.10.2 / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered / Over-protect)

## 1. Purpose

This file owns the ship-unit directory `src/main/cpp`. Coding style owns spelling and linkage. Project structure owns the rest of the repository map. The builds compile this directory. They do not choose another source root.

### 1.1 Human-facing

**In one sentence:** You put the product C++ sources in `src/main/cpp`, and `lib5250/` is the protocol library the same build compiles.

| Box | Meaning | Example |
|-----|---------|---------|
| You / this login | The person adding a source file | You add a `.cpp` file under `src/main/cpp` |
| The other role | `./build.sh` and Meson | They compile the translation units in that directory |
| Not this file | How a name is spelled, and what a log line looks like | `requirement-cpp-coding-style.md` and `requirement-cpp-logger.md` |

| Includes | Excludes |
|----------|----------|
| The directory path, the files that belong there, and the rule that `src/main/c` is not a source root | Flag lists, the ChronicleLogger line, and apt package names |

| Surface | What you open | What for |
|---------|---------------|----------|
| `src/main/cpp/` | Ship-unit sources | The files in §2.1 |
| `project.sh` | `SRC_C` | The path the simple build searches |

| You do… | What it means | What you type |
|---------|---------------|---------------|
| Find the sources | Open the only ship-unit directory | `src/main/cpp` |

## 2. Core rules

1. The only ship-unit source directory is `src/main/cpp`. There is no `src/main/c`.
2. A translation unit in that directory is `.cpp` unless this requirement names a `.c` file. This requirement names no `.c` file.
3. A header named in §2.1 stays `.h`. Do not rename `logger.h` or `project.h` to `.hpp`.
4. Shell scripts, Meson files, and Markdown do not go in this directory.
5. `project.sh` sets `SRC_C` to `src/main/cpp`. `./build.sh` compiles the `.cpp` files there and the `lib5250` sources named in `meson.build`. `meson.build` lists the same translation units. A new translation unit is added to this file and to the Meson source list in the same change. `./build.sh clean` removes only `target/` and `builddir/`.
6. A header and its translation unit stay paired. `project.h` holds identity macros only.
7. cpp-log-path is not a source directory. For root or sudo it is `/var/cpp-tn5250/log`. For every other user it is `$HOME/.app/cpp-tn5250/log`. The directory is `requirement-cpp-logger-folder.md`. The dated file in it is `requirement-cpp-logger.md`. Do not move `main.cpp` or `logger.cpp` into that directory.

### 2.1 Files in this directory

| File | Role |
|------|------|
| `main.cpp` | Program entry |
| `logger.cpp` | Logger implementation |
| `logger.h` | Logger declarations |
| `project.h` | Runtime identity |
| `gtkterm.cpp` | 5250 terminal on a GTK drawing area |
| `gtkterm.h` | Terminal declarations |
| `gnome_app.cpp` | Window, menus, and session startup |
| `gnome_app.h` | Window declarations |

`lib5250/` stays the upstream protocol library. This requirement does not rename those files and does not patch them. The build lists them beside the ship unit.

### Sample (this project)

```text
src/main/cpp/
  main.cpp
  logger.cpp
  logger.h
  project.h
  gtkterm.cpp
  gtkterm.h
  gnome_app.cpp
  gnome_app.h
lib5250/
  buffer.cpp conf.cpp dbuffer.cpp debug.cpp display.cpp
  field.cpp macro.cpp menu.cpp printsession.cpp record.cpp
  scrollbar.cpp scs.cpp session.cpp sslstream.cpp stream.cpp
  telnetstr.cpp terminal.cpp utility.cpp version.cpp window.cpp wtd.cpp
```

## 3. Protection rule

Future editors must not recreate `src/main/c`, add a second ship-unit source root, or move a named header off `.h`.

## 4. Related artifacts

| Artifact | Role |
|----------|------|
| `docs/requirements/index.md` | Registry |
| `docs/requirements/requirement-cpp-coding-style.md` | Spelling and linkage |
| `docs/requirements/requirement-cpp-project-structure.md` | Repository map outside this directory |
| `docs/requirements/requirement-cpp-logger-folder.md` | Log directory, not this source directory |
| `docs/requirements/requirement-cpp-logger.md` | Dated log file inside that directory |
| `build.sh` | Compiles this directory |
| `meson.build` | Meson source list |
| `project.sh` | `SRC_C=src/main/cpp` |

**Last updated**: 2026-10-03
**Owner**: C++ source folder
