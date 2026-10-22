---
name: shell-cli-self-install
id: LM-SHELL-CLI-SELF-INSTALL
kind: law-mold
description: >
  Portable law mold. Cite as LM-SHELL-CLI-SELF-INSTALL (path secondary).
  Non-interactive empty argv = CLI self-place (not payload). Script $0 copies
  without download. Dest mode 0755 global / 0700 local.
---

**file**: template-shell-cli-self-install.md  
**Mold-ID**: LM-SHELL-CLI-SELF-INSTALL  
**Status**: Active (Version 1.1.0 – full Type 0 self-place examples)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered / Over-protect)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

## 1. Purpose

This mold is the portable **requirement spec design rules** for **shell-cli-self-install**: how a Type 0 POSIX `/bin/sh` CLI **places itself**.

Specialize into `requirement-shell-cli-self-install.md` (or the project-chosen key). Product source cites the **requirement**, never this template.

| This mold owns | Peer owns |
|----------------|-----------|
| Named verb **`self-install`** | Verb catalog dual-mention: **`LM-CLI-INTERFACE`** |
| Non-interactive empty argv → **CLI place only** | Empty-argv TTY menu vs Type N help: **`LM-SHELL-CLI-ZERO-ARGUMENTS`** |
| `$0` interpreter vs script; copy-without-download | Pipe must still call main: **`LM-ONLINE-INSTALL`** §3.0 bootstrap |
| Dest mode **0755** global / **0700** local on this place path | Channel URL / checksum: **`LM-ONLINE-INSTALL`** · **`LM-AUTOMATIC-CHECKSUM`** |
| **MUST NOT** run payload on this path | Payload `install` / `setup`: domain / **`LM-PAYLOAD-ONLINE-INSTALL`** |
| PATH rc **MAY** run so the CLI is on PATH | PATH **bodies**: **`LM-PATH-AND-SHELL-SUPPORT`** |

**Do not use this mold when** the product is **non-online-installable** (no channel, local `install`/`uninstall` only) — use **`LM-SHELL-LOCAL-SELF-MANAGEMENT`**.

---

## Terminologies

Related glossary entries (**disk-truth**). Templates **point**; they do not redefine terms or act as product law.

| Term | Path | SSOT type | Role |
|------|------|-----------|------|
| **Shell CLI self-install** | `docs/terminologies/shell-cli-self-install.md` | `product-law` | **Primary** procedure this mold implements |
| **Self-install** | `docs/terminologies/self-install.md` | `product-law` | Verb token |
| **Payload installer** | `docs/terminologies/payload-installer.md` | `product-law` | Fence: empty argv **MUST NOT** be this |
| **Type O empty argv** | `docs/terminologies/type-o-empty-argv.md` | `runtime-mode` | Empty argv class; this mold is Type O-S depth |
| **Shell CLI bootstrap** | `docs/terminologies/shell-cli-bootstrap.md` | `product-law` | Pipe still calls main; `$0` is often the interpreter |
| **Online self-managed** | `docs/terminologies/online-self-managed.md` | `product-law` | Mode that uses `self-install` |
| **Ship unit** | `docs/terminologies/ship-unit.md` | `identity-runtime` | File being copied or fetched |
| **Global / local installation location** | `docs/terminologies/global-installation-location.md`, `local-installation-location.md` | `identity-runtime` | Dest dirs; this mold owns **mode** 0755/0700 |
| **Atomic file copy** | `docs/terminologies/atomic-file-copy.md` | `product-law` | Stage → chmod → mv |
| **Temp file system** | `docs/terminologies/temp-file-system.md` | `product-law` | Stage leaf under isolated `TMPDIR` |
| **Well-known CLI verb** | `docs/terminologies/well-known-cli-verb.md` | `product-law` | `self-install` operational; `setup` is payload |
| **Project templates** | `docs/terminologies/project-templates.md` | `meta-catalog` | What law molds are |
| **Docs folder structure** | `docs/terminologies/docs-folder-structure.md` | `policy` | Where this mold lives |
| **No-hardcode policy** | `docs/terminologies/no-hardcode-policy.md` | `policy` | Placeholders only |
| **Dual policies** | `docs/terminologies/dual-policies.md` | `policy` | No-placeholder × no-hardcode |
| **Least privilege** | `docs/terminologies/least-privilege.md` | `policy` | Type 0 place; no sudo by convenience |

**SSOT types used:** `identity-runtime` · `meta-catalog` · `policy` · `product-law` · `runtime-mode`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md` · `docs/policies/policy-least-privilege.md`

---

## 2. Core Rules (portable)

### 2.1 Command and empty argv

1. Online self-manageable products **MUST** expose **`self-install`** as the CLI place/ensure verb.  
2. When **argv is empty** and the run is **non-interactive** (no TTY, or `JSON=1`, or `QUIET=1`), the dispatcher **MUST** call the self-install orchestrator — **MUST NOT** open the menu, **MUST NOT** dump help, **MUST NOT** run payload `install` / `setup`.  
3. Interactive empty argv **MAY** be a TTY menu when claimed (**`LM-SHELL-CLI-ZERO-ARGUMENTS`** · **`LM-CLI-DEFAULT-INTERACTION`**).  
4. Explicit `{{APP_NAME}} install` / `setup` remains the **payload** path when the product has a payload.  
5. Dual mention: **`self-install`** on the CLI-interface requirement **and** the specialized self-install requirement.

### 2.2 `$0` source detect

**Kind:** [template-example-function](../../terminologies/template-example-function.md). **Not product law.**

```sh
inst_argv0_is_shell_interpreter() {
    _a0="$1"
    _base="${_a0##*/}"
    case "${_base}" in
        -*) _base="${_base#-}" ;;
    esac
    case "${_base}" in
        sh|bash|dash|ash|zsh|ksh|mksh|yash|posh|csh|tcsh|fish|busybox)
            return 0
            ;;
    esac
    return 1
}
```

| `$0` | Place |
|------|-------|
| Interpreter basename (table above), including `/bin/sh` | **Download** channel + integrity |
| Readable regular file (relative or absolute) | **Copy** that file — **no** download |
| Basename-only, `command -v` finds a readable file | **Copy** that file |
| Else | Fail closed, or download if a channel is configured — **MUST NOT** silent success |

### 2.3 Copy-from-script (no download)

When `$0` is a script:

1. Resolve an absolute readable path.  
2. Stage with `mktemp` under isolated `TMPDIR`: **`{{APP_NAME}}-XXXXXX`**.  
3. `cp` source → stage.  
4. `chmod` dest mode on the stage **before** `mv`. **MUST NOT** `chmod +x` on `mktemp` 0600.  
5. `mv` onto `${INSTALL_PATH}`.  
6. `chmod` dest mode on dest.  
7. **MUST NOT** fetch `SCRIPT_URL`. **MUST NOT** require network.

### 2.4 Dest mode

| Privilege | `INSTALL_PATH` | Mode |
|-----------|----------------|------|
| root (`id -u` 0) | `${GLOBAL_BIN}/{{APP_NAME}}` | **0755** |
| non-root | `${USER_BIN}/{{APP_NAME}}` | **0700** |

Global **0755** is the shebang other-read contract (**PP-A-28**). Local **0700** is owner-only (this login can open the shebang; other logins cannot).

### 2.5 Already installed

Force off → success no-op (“already installed”); **no** re-copy; **no** re-download; **no** payload. Force on → replace via copy or download per `$0`.

### 2.6 Out of this path

**MUST NOT** on `self-install` / NI empty argv:

- Domain package ensure (`pkg` / apt)  
- Host daemon start / `sshd -t`  
- Payload project/toolchain install  
- Treat dest **0711** as success  

PATH rc ensure **MAY** run (CLI usability). Bodies stay **`LM-PATH-AND-SHELL-SUPPORT`**.

---

## 3. Example functions (not product law)

**Kind:** [template-example-function](../../terminologies/template-example-function.md).  
**One owner:** these five bodies live **here**. Peers **point**. Download/checksum helpers stay **`LM-ONLINE-INSTALL`**. TTY confirm **`inst_maybe_install`** lives on **`LM-INTERACTIVE-VS-NONINTERACTIVE`**. Empty-argv split: **`LM-SHELL-CLI-ZERO-ARGUMENTS`** §5.5b.

Defaults: `: "${APP_NAME:=app}"`. **MUST NOT** freeze a product brand.

### 3.1 `inst_argv0_is_shell_interpreter` — pipe vs checkout

```sh
# True when $0 is the interpreter (curl|sh), not the ship-unit file.
inst_argv0_is_shell_interpreter() {
    local _a0="${1:-}"
    local _base="${_a0##*/}"
    case "${_base}" in
        -*) _base="${_base#-}" ;;
    esac
    case "${_base}" in
        sh|bash|dash|ash|zsh|ksh|mksh|yash|posh|csh|tcsh|fish|busybox)
            return 0
            ;;
    esac
    return 1
}
```

### 3.2 `inst_resolve_self_script` — class B path or empty

```sh
# PRINTF EXCEPTION (class B): absolute path of the running script, or return 1.
inst_resolve_self_script() {
    local _a0="${1:-}"
    local _dir _found
    [ -n "${_a0}" ] || return 1
    if inst_argv0_is_shell_interpreter "${_a0}"; then
        return 1
    fi
    if [ -f "${_a0}" ] && [ -r "${_a0}" ]; then
        _dir=$(CDPATH= cd -- "$(dirname -- "${_a0}")" && pwd) || return 1
        printf '%s\n' "${_dir}/${_a0##*/}"
        return 0
    fi
    case "${_a0}" in
        */*) return 1 ;;
    esac
    _found=$(command -v "${_a0}" 2>/dev/null) || return 1
    if [ -f "${_found}" ] && [ -r "${_found}" ]; then
        printf '%s\n' "${_found}"
        return 0
    fi
    return 1
}
```

### 3.3 `inst_cli_dest_mode` — class B mode string

```sh
# Global dest 0755 (other-read shebang). Local dest 0700.
# MUST NOT chmod +x on mktemp 0600 (that mints 0711).
inst_cli_dest_mode() {
    if [ "$(id -u 2>/dev/null || echo 1)" -eq 0 ]; then
        printf '%s\n' "0755"
    else
        printf '%s\n' "0700"
    fi
}
```

### 3.4 `inst_self_install_copy_from_script` — no download

```sh
inst_self_install_copy_from_script() {
    local _src="$1"
    local _mode="$2"
    local _tmp
    : "${APP_NAME:=app}"
    : "${JSON:=0}"
    : "${INSTALL_PATH:=}"

    _tmp=$(mktemp -t "${APP_NAME}-XXXXXX")
    if [ -z "${_tmp}" ]; then
        out_error "Failed to create temporary file"
        return 1
    fi
    if ! cp "${_src}" "${_tmp}"; then
        rm -f "${_tmp}" 2>/dev/null || true
        out_error "Failed to copy ${_src}"
        return 1
    fi
    chmod "${_mode}" "${_tmp}" 2>/dev/null || true
    rm -f "${INSTALL_PATH}" 2>/dev/null
    if ! mv "${_tmp}" "${INSTALL_PATH}" 2>/dev/null; then
        rm -f "${_tmp}" 2>/dev/null || true
        out_error "Failed to move to ${INSTALL_PATH}"
        return 1
    fi
    chmod "${_mode}" "${INSTALL_PATH}" 2>/dev/null || true
    return 0
}
```

### 3.5 `inst_self_install` — copy when `$0` is the script, else download

```sh
inst_self_install() {
    : "${JSON:=0}"
    : "${FORCE_REINSTALL:=0}"
    : "${APP_NAME:=app}"
    : "${VERSION:=}"
    : "${HOME:=/tmp}"
    : "${GLOBAL_BIN:=/usr/local/bin}"
    : "${USER_BIN:=${HOME}/.local/bin}"
    : "${REMOTE_VERSION:=${VERSION}}"
    : "${CHECKSUM:=}"
    : "${SCRIPT_URL:=}"

    if [ "$(id -u 2>/dev/null || echo 1)" -eq 0 ]; then
        IS_ROOT=1
        INSTALL_PATH="${GLOBAL_BIN}/${APP_NAME}"
    else
        IS_ROOT=0
        INSTALL_PATH="${USER_BIN}/${APP_NAME}"
    fi
    local _mode _src _tmp _ck
    _mode=$(inst_cli_dest_mode)

    path_add_shell

    if inst_is_installed && [ "${FORCE_REINSTALL}" -eq 0 ]; then
        out_success "${APP_NAME} is already installed."
        return 0
    fi
    inst_perform_install_prepare_target || return 1

    _src=$(inst_resolve_self_script "$0") || _src=""
    if [ -n "${_src}" ]; then
        inst_self_install_copy_from_script "${_src}" "${_mode}" || return 1
        out_success "${APP_NAME} ${REMOTE_VERSION} successfully installed to ${INSTALL_PATH}"
        return 0
    fi

    # Interpreter / pipe: download + integrity (peer LM-ONLINE-INSTALL).
    _tmp=$(mktemp -t "${APP_NAME}-XXXXXX")
    [ -n "${_tmp}" ] || return 1
    _ck=0
    : "${INST_AUTO_CHECKSUM_OK:=0}"
    if [ -n "${CHECKSUM}" ]; then
        inst_perform_install_download_with_checksum "${_tmp}" || {
            rm -f "${_tmp}" 2>/dev/null || true
            return 1
        }
        _ck=1
    else
        INST_AUTO_CHECKSUM_OK=0
        inst_perform_install_download_without_checksum "${_tmp}" || {
            rm -f "${_tmp}" 2>/dev/null || true
            return 1
        }
        _ck=${INST_AUTO_CHECKSUM_OK:-0}
    fi
    inst_perform_install_atomic_install "${_tmp}" "${_ck}" || {
        rm -f "${_tmp}" 2>/dev/null || true
        return 1
    }
    chmod "${_mode}" "${INSTALL_PATH}" 2>/dev/null || true
    return 0
}
```

Empty-argv **body** (TTY confirm vs NI auto): **`LM-SHELL-CLI-ZERO-ARGUMENTS`** §5.5b + **`inst_maybe_install`**. Dispatcher **MUST** still `app_main "$@"` under pipe (no `${0##*/}` gate).

---

## Under command line for normal user only

When the product may run on Termux, Git Bash, Windows cmd, or the same class: Type 1/2 unused on detect; no in-tool `sudo` / `apt`; no `sudo curl | sh` recommend; Git Bash and Windows cmd do not invoke Termux `pkg`. **This mold:** self-install stays Type 0 this-login place (`USER_BIN` **0700**, or Termux `$PREFIX/bin` when that is the global dest). **MUST NOT** become a sudo/apt install path.

---

## 4. Design Principles (CIAO / CIAO-Lite)

- **Caution:** Fail closed on I/O; never silent success when Case A should place.  
- **Intentional:** Empty argv NI = CLI place; payload is a named verb.  
- **Anti-fragile:** Copy works offline from a checkout; download remains for pipes.  
- **Over-protect:** Dest mode table; interpreter list; no `chmod +x` 0711 trap.

---

## 5. Protection Rule (Sacred)

Future agents **MUST NOT**:

1. Route non-interactive empty argv to payload `install` / `setup` / domain start.  
2. Download when `$0` is a readable script file.  
3. Gate the only call to main on `${0##*/}` == `{{APP_NAME}}`.  
4. `chmod +x` on `mktemp` staging; leave global dest **0711** or **0700**.  
5. Use local dest **0755** as a substitute for this mold’s **0700** local contract (or the reverse on global).  
6. Cite this template as product-source ALIGNMENT.  
7. Strip **Under command line for normal user only**.

---

## 6. Design-time verification

| TP family / ID | Intent |
|----------------|--------|
| **TP-SI-01** | `self-install` with script `$0` places without network |
| **TP-SI-02** | Local dest mode **0700**; global dest mode **0755** |
| **TP-SI-03** | Non-interactive empty argv = self-install (not help, not menu, not payload) |
| **TP-SI-04** | Interpreter `$0` (`cat ship \| sh`) uses channel download |
| **TP-SI-05** | Already-installed no-op (force off) |
| **TP-SI-06** | Help lists `self-install` |
| **TP-SI-07** | No live `chmod +x`; dest helper `inst_cli_dest_mode` present |
| **TP-SI-08** | Isolated `GLOBAL_BIN` dest **0755** (heals **0711**) |

Proof mold: **`PM-SHELL-CLI-SELF-INSTALL-TEST-PLAN`**. Product map: `docs/reviews/test-plan.md`.

---

## 7. How to specialize

1. **`SK-CREATE-SPECIFIC-REQUIREMENT`** — create `requirement-shell-cli-self-install.md`; fill Implementation Notes; registry row.  
2. Dual-mention `self-install` on the CLI-interface REQ.  
3. Empty-argv NI on the zero-arguments REQ **points** here (CLI place), not payload.  
4. Implement via **`SK-SHELL-CLI-SELF-INSTALL`** · **`SK-SH-SCRIPT-CODING`**.  
5. Tests from **`PM-SHELL-CLI-SELF-INSTALL-TEST-PLAN`** via **`SK-ADD-TESTS`**.

**Last Updated**: 2026-09-17  
**Owner**: {{OWNER}}  
**Version history:**  
- **1.1.0** (2026-09-17): Full portable examples — `inst_argv0_is_shell_interpreter`, `inst_resolve_self_script`, `inst_cli_dest_mode`, `inst_self_install_copy_from_script`, `inst_self_install` (`APP_NAME:=app`). **TP-SI-07** / **TP-SI-08**.  
- **1.0.0** (2026-09-17): Initial CLI self-place mold.

**Alignment**: term `shell-cli-self-install` · **`SK-SHELL-CLI-SELF-INSTALL`** · **`LM-SHELL-CLI-ZERO-ARGUMENTS`** · **`LM-ONLINE-INSTALL`** · **`LM-CLI-INTERFACE`** · [CIAO](https://github.com/cloudgen/ciao) / [CIAO-Lite](https://github.com/cloudgen/ciao-lite)  
- **`PO-STAY-IN-PROJECT-SSOT`** — no silent sibling-project write (**`E-BLAST-09`**)
