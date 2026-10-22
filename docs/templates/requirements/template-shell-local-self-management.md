---
name: shell-local-self-management
id: LM-SHELL-LOCAL-SELF-MANAGEMENT
kind: law-mold
description: >
  Portable law mold. Cite as LM-SHELL-LOCAL-SELF-MANAGEMENT (path secondary).
---

**file**: template-shell-local-self-management.md  
**Status**: Active (Version 1.3.2 – `util_get_install_bin_path` user-then-global)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered / Over-protect)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

## 1. Purpose

This template defines **local self-managed** lifecycle for a POSIX shell CLI: **install** and **uninstall** using only the **already-present ship unit** (copy/remove on disk), plus **where-is-me** path reporting—**without** online install channel, remote download, or remote self-update.

It also documents the **full local Type 0 package** agents should expect when specializing a **non-online-installable** (alias **local-only**) CLI: lifecycle commands **plus** local diagnostics (`version`, `about`, `help`). **Local version** answers “what version is this ship unit?” and **must not** be confused with remote **version-check**.

**Specialize into:** `requirement-shell-local-self-management.md` (or project-chosen key) with filled Implementation Notes; wire diagnostics in the peer CLI-interface requirement.

**Do not use this template when** the product’s primary distribution is `curl | sh` with remote self-update — use the **online package** instead:

| Online package piece | Template |
|----------------------|----------|
| Channel / pipe install / Type O mandate | `template-online-install.md` |
| Remote version-check / self-update / self-uninstall | `template-self-management.md` |
| Companion integrity | `template-automatic-checksum.md` |
| Local version + dispatcher | `template-cli-interface.md` |

(or **both** local + online only if dual modes are explicit product law — never half-live channel).

**Anti-duplication:** This template does **not** redefine online channel, Type O, or remote version-check. Online template does **not** redefine local copy install.

---

## Terminologies (mandatory)

| Term | Path | SSOT type | Role in this template |
|------|------|-----------|------------------------|
| **Where-is-me** | `docs/terminologies/where-is-me.md` | `product-law` | Path-report command (no install mutate) |

| **Project templates** | `docs/terminologies/project-templates.md` | `meta-catalog` | What law molds are; specialize-out target |
| **Docs folder structure** | `docs/terminologies/docs-folder-structure.md` | `policy` | Where this mold lives vs product law / tests |
| **No-hardcode policy** | `docs/terminologies/no-hardcode-policy.md` | `policy` | Placeholders only in portable molds |
| **Dual policies** | `docs/terminologies/dual-policies.md` | `policy` | No-placeholder × no-hardcode balance |
| **Terminology policy for templates** | `docs/terminologies/terminology-policy-for-templates.md` | `policy` | Mandatory Terminologies section rules |
| **SSOT-terminology policy for templates** | `docs/terminologies/ssot-terminology-policy-for-templates.md` | `policy` | SSOT type column on rows || Local self-managed | `docs/terminologies/local-self-managed.md` | product-law / lifecycle mode | **Primary mode** this template implements |
| **Where-is-me** | `docs/terminologies/where-is-me.md` | `product-law` | Path-report command (no install mutate) |
| Online self-managed | `docs/terminologies/online-self-managed.md` | product-law / lifecycle mode | Contrast — **out of scope** here |
| Ship unit | `docs/terminologies/ship-unit.md` | product artifact | Install **source**; local version SSOT carrier (`VERSION`) |
| Global installation location | `docs/terminologies/global-installation-location.md` | identity-runtime / path | Root install dir + vars |
| Local installation location | `docs/terminologies/local-installation-location.md` | identity-runtime / path | User install dir + vars |
| Shell path integration | `docs/terminologies/shell-path-integration.md` | runtime-mode / UX | Optional `path_add_*` after user install |
| Shell function naming convention | `docs/terminologies/shell-function-naming-convention.md` | meta / naming | `inst_*` / `app_*` / `util_*` |
| Shell CLI config variables | `docs/terminologies/shell-cli-config-variables.md` | meta / config catalog | Full var inventory pointer |
| Idempotency rule | `docs/terminologies/idempotency-rule.md` | product-law / re-run | Install no-op / uninstall absent |
| Interactive vs noninteractive | `docs/terminologies/interactive-vs-noninteractive.md` | runtime-mode | Uninstall confirm vs `--force` |
| Bootstrap trim | `docs/terminologies/bootstrap-trim.md` | process | When B is trimmed from online A |

**Do not re-own here:** full output SSOT (`template-output-requirements.md`), empty-argv Type O vs N deep rules (`template-shell-cli-zero-arguments.md` — local products usually Type N), online channel (`template-online-install.md`), remote version-check/self-update (`template-self-management.md`).

---

## 2. Feature package (normative understanding)

Agents specializing a **non-online-installable** (alias **local-only**) shell CLI **MUST** distinguish three layers:

### 2.1 Layer A — Local self-managed lifecycle (this template **owns**)

**Exclusive local command pair:** **`install`** + **`uninstall`** (+ **`where-is-me`**).  
**Forbidden as primary local verbs:** `self-install`, `self-uninstall`, `self-update` (online vocabulary only).

| Feature | Command | Meaning |
|---------|---------|---------|
| Local install | **`install`** | Copy **running** ship unit → privilege-correct bin; **no** network |
| Local uninstall | **`uninstall`** | Remove **managed** binary only; confirm / `--force` |
| Local refresh | **`install --force`** | Replace managed binary from **this** running ship unit (not channel) |
| Where-is-me | `where-is-me` | Report running path + managed install path + installed flag |

| Mix-up | Correct local | Correct online |
|--------|---------------|----------------|
| Place binary | **`install`** | channel `install` / Type O / pipe |
| Remove binary | **`uninstall`** | **`self-uninstall`** |
| Update from network | N/A | **`self-update`** |

### 2.2 Layer B — Local diagnostics (required companions; **CLI interface owns** wiring)

These are **not** remote-channel ops. They **SHOULD** ship with every local self-managed product unless a specialized REQ explicitly omits them with rationale.

| Feature | Command | Meaning | Handler family |
|---------|---------|---------|----------------|
| **Local version** | `version` | Print ship-unit **local** identity version (`VERSION` / Config SSOT) | `app_version` |
| Local about | `about` | Environment / diagnostics; **no** `SCRIPT_URL` install one-liner as product UX | `app_about` |
| Help | `help` | Usage; list Layer A + B; **no** remote lifecycle as product commands | `app_help` |

**Local version contract (portable):**

| Rule | Meaning |
|------|---------|
| Source of truth | Product `VERSION` hard-assign / Config SSOT in the **running ship unit** |
| Network | **MUST NOT** fetch remote version |
| Human | Show `{{APP_NAME}}` + version string |
| JSON | Structured object (e.g. `type=version`, `app`, `version`) via output SSOT |
| Contrast | **Not** `version-check` (remote compare) — see §2.4 |

### 2.3 Layer C — Optional / out of mode

| Feature | Status under local self-managed |
|---------|----------------------------------|
| Domain verbs (product ops) | Optional; own domain REQ — **not** lifecycle |
| Shell path integration | Optional after user-bin install |
| Remote `version-check` / `self-update` | **Out of mode** — online self-managed only |
| Online remove command **`self-uninstall`** | **Out of mode** as primary verb — online only ([`self-uninstall.md`](../../terminologies/self-uninstall.md)); local uses bare **`uninstall`** |
| `curl\|sh` / `SCRIPT_URL` install | **Out of mode** — online install only |
| Type O empty-argv install-ensure | **Out of mode** unless dual-mode product law |

### 2.4 Local version vs remote version-check (must not confuse)

| Capability | Question answered | Channel | Template owner |
|------------|-------------------|---------|----------------|
| **Local `version`** | “What version is **this file** I’m running?” | None (disk) | CLI interface + this package (§2.2) |
| **Remote `version-check`** | “Is there a **newer** version on the channel?” | `SCRIPT_URL` / remote | `template-self-management.md` only |
| **Self-update** | “Fetch and replace from remote” | Remote | `template-self-management.md` only |

Specializing local self-managed **MUST** include **local version** (Layer B) unless explicitly deferred. Specializing local self-managed **MUST NOT** reintroduce remote version-check under this mode’s ownership.

### 2.5 Full local Type 0 command package (recommended inventory)

When product law claims local self-managed **and** a local Type 0 CLI:

| Command | Layer | In help? |
|---------|-------|----------|
| `install` | A | Yes |
| `uninstall` | A | Yes |
| `where-is-me` | A | Yes |
| `version` | B (**local version**) | Yes |
| `about` | B | Yes |
| `help` | B | Yes |
| *(empty argv)* | Type N → `help` | Yes (behavior) |

---

## 3. Ownership map (anti-duplication)

| Concern | Owner template / term | This template |
|---------|----------------------|---------------|
| Remote `curl\|sh` / `SCRIPT_URL` | `template-online-install.md` | **Forbidden** as install source |
| Remote version-check / self-update | `template-self-management.md` | **Out of scope** |
| **Local version** / about / help command table | `template-cli-interface.md` | **Requires** as package companions (§2.2); does not re-own full CLI catalog |
| Bin directory defaults (`GLOBAL_BIN` / `USER_BIN`) | location glossary terms | **Consume** only (pointer) |
| PATH rc ensure (`path_add_*`) | `template-path-and-shell-support.md` | **MAY** call after user install |
| Output modes | `template-output-requirements.md` | **Consume** `out_*` |
| Confirm / non-interactive | `template-interactive-vs-noninteractive.md` | Uninstall confirm contract |
| Idempotency | `template-idempotency.md` | Already installed / already uninstalled |
| Empty argv help vs install-ensure | `template-shell-cli-zero-arguments.md` | Prefer **Type N** for non-online-installable (alias local-only) products |

---

## 4. Command surface (normative)

### 4.1 Lifecycle (Layer A — this template)

| Command | Purpose | Typical flags | Handler family |
|---------|---------|---------------|----------------|
| `install` | Copy **running ship unit** to privilege-correct bin | `--force` reinstall | `inst_local_install` |
| `uninstall` | Remove managed binary | `--force` skip confirm | `inst_local_uninstall` |
| `where-is-me` | Full path of running app (+ install path) | `--json`, `--quiet` | `app_where_is_me` |

### 4.2 Local diagnostics (Layer B — required companions)

| Command | Purpose | Typical flags | Handler family |
|---------|---------|---------------|----------------|
| `version` | **Local version** of running ship unit | `--json`, `--quiet` | `app_version` |
| `about` | Local diagnostics (no online install UX) | `--json`, `--quiet` | `app_about` |
| `help` | Usage for Layers A+B | `--json` short note | `app_help` |

**User-facing names** may stay short (`install`, `uninstall`, `version`); **functions** use prefixes ([shell-function-naming-convention](../../terminologies/shell-function-naming-convention.md)).

### 4.3 Example shape (`app_version` — local version only)

```sh
# Portable sketch — local version only; never fetch remote.
# GENERAL PURPOSE: Report ship-unit VERSION SSOT for operators and machines.
app_version() {
    : "${APP_NAME:=app}"
    : "${VERSION:=0.0.0}"
    : "${JSON:=0}"
    if [ "${JSON}" -eq 1 ]; then
        out_json "version" "" \
            "app" "${APP_NAME}" \
            "version" "${VERSION}"
        return 0
    fi
    out_info "${APP_NAME} version ${VERSION}"
}
```

**Forbidden in this helper:** remote URL fetch, comparing against channel latest, writing `is_latest` from network.

---

## 5. Local install (normative)

| Rule | Meaning |
|------|---------|
| Source | Currently executing ship unit (resolve `$0` / argv0 when possible) — **not** a URL |
| Target | Root → `${GLOBAL_BIN}/${APP_NAME}`; non-root → `${USER_BIN}/${APP_NAME}` |
| Defaults | Point to location terms — do not restate full path theory here |
| Create dirs | Create target bin dir when missing; fail loud if not writable |
| Atomic | Stage → `chmod 0755` → `mv` onto final path (not `chmod +x` on `mktemp` 0600 → **0711**) |
| Idempotent | Already installed + force off → success no-op |
| Force | `--force` / `FORCE=1` allows replace |
| PATH | **MAY** invoke shell-path-integration after **user** install only |
| Network | **MUST NOT** require network for install |

**Helpers and full examples:** §8 (variables) and §9 (functions).

---

## 6. Local uninstall (normative)

| Rule | Meaning |
|------|---------|
| User command | **`uninstall`** only (not `self-uninstall`) |
| Target | Managed `${GLOBAL_BIN|USER_BIN}/${APP_NAME}` only |
| Absent | Success no-op |
| Confirm | Interactive confirm unless `--force`; non-interactive/json/quiet without force → **fail closed** (`confirm_required`) |
| PATH cleanup | Only if safe (e.g. USER_BIN empty) — see shell-path-integration reverse |
| No over-delete | No domain data, home trees, or unrelated binaries |

**Example:** §9.5 `inst_local_uninstall`.

---

## 7. Where-is-me (normative)

| Rule | Meaning |
|------|---------|
| Running path | Absolute path of executing ship unit when resolvable |
| Install path | Expected managed path; mark installed if executable present |
| Pipe degradation | Honest message when `$0` is not a file path |
| JSON | At least `running_path`, `install_path`, `installed` |
| Output | Via `out_*` / `out_json` only |

**Example:** §9.6 `app_where_is_me`.

---

## 8. Config variables (local self-managed)

**Purpose:** Portable **Config/env** inventory for local place/remove/where-is-me.  
Full Type 0 catalog (including online-only keys): [shell-cli-config-variables](../../terminologies/shell-cli-config-variables.md).  
Path depth: [global-installation-location](../../terminologies/global-installation-location.md), [local-installation-location](../../terminologies/local-installation-location.md).

### 8.1 Identity & local version

| Variable | Role | Typical default / note |
|----------|------|------------------------|
| `APP_NAME` | Binary basename SSOT | hard-assign then `: "${APP_NAME:=app}"` |
| `VERSION` | **Local version** SSOT | hard-assign then `: "${VERSION:=0.0.0}"` |
| `APP_DESC` / `SHORT_DESCRIPTION` / `DESCRIPTION` | Help/about text | human strings |

### 8.2 Mode flags

| Variable | Role | Typical default |
|----------|------|-----------------|
| `QUIET` | Suppress non-error human chatter | `0` |
| `JSON` | Machine JSON (implies quiet in dispatcher) | `0` |
| `DEBUG` | Debug on stderr | `0` |
| `TTY` | Both stdin/stdout are TTYs | set if `[ -t 0 ] && [ -t 1 ]` |
| `FORCE` | Install replace; uninstall skip confirm | `0` |
| `INTERACTIVE` | Optional prompt override | unset / `0` |

### 8.3 Install locations & privilege

| Variable | Role | Typical default |
|----------|------|-----------------|
| `HOME` | User home — resolve **before** `${HOME}/…` under `set -u` | passwd / `/tmp` |
| `GLOBAL_BIN` | System-wide bin dir | `/usr/local/bin` |
| `USER_BIN` | Per-user bin dir | `${HOME}/.local/bin` |
| `INSTALL_PATH` | Resolved path for current op (optional cache) | from `util_get_install_bin_path` |
| `IS_ROOT` | `1` if elevated | from `id -u` |
| `FORCE_USER` | Force user-bin target | `0` (optional) |
| `FORCE_GLOBAL` | Force global-bin target | `0` (optional) |

### 8.4 Dispatch

| Variable | Role | Typical default |
|----------|------|-----------------|
| `COMMAND` | Selected subcommand | `help` |
| `SH` | Recommended shell name in tips | `sh` |

### 8.5 Not used as local install source (online-only)

| Variable | Role under **local** mode |
|----------|---------------------------|
| `SCRIPT_URL`, `REPO_USER`, `REPO_NAME` | **MUST NOT** be install source |
| `CHECKSUM`, `REMOTE_VERSION` | **Not** local install integrity channel |
| Domain `VOLATILE_DIR` / `PERSISTENT_DIR` / entity flags | **Out of mode** unless separate domain law |

### 8.6 Safe defaults block (sketch — script top)

```sh
# Product identity SSOT (extractors: grep '^APP_NAME="' / '^VERSION="')
APP_NAME="{{APP_NAME}}"
: "${APP_NAME:={{APP_NAME}}}"
VERSION="{{VERSION}}"
: "${VERSION:={{VERSION}}}"
: "${APP_DESC:=Local self-managed POSIX shell CLI}"
: "${SHORT_DESCRIPTION:=${APP_DESC}}"
: "${DESCRIPTION:=POSIX /bin/sh local self-managed CLI: install, uninstall, where-is-me, version, about, help.}"

: "${QUIET:=0}"
: "${JSON:=0}"
: "${FORCE:=0}"
: "${DEBUG:=0}"
: "${TTY:=0}"
: "${COMMAND:=help}"

# HOME before any ${HOME}/… (set -u)
: "${HOME:=/tmp}"
: "${GLOBAL_BIN:=/usr/local/bin}"
: "${USER_BIN:=${HOME}/.local/bin}"
: "${INSTALL_PATH:=}"
: "${FORCE_USER:=0}"
: "${FORCE_GLOBAL:=0}"
: "${SH:=sh}"

if [ "$(id -u 2>/dev/null || echo 1)" -eq 0 ]; then
    IS_ROOT=1
else
    IS_ROOT=0
fi
: "${IS_ROOT:=0}"

[ -t 0 ] && [ -t 1 ] && TTY=1
```

---

## 9. Functions (local self-managed)

### 9.1 Inventory

| Function | Prefix | Role | Example |
|----------|--------|------|---------|
| `util_resolve_running_path` | `util_` | Absolute path of running ship unit (class B stdout) | §9.2 |
| `util_get_install_bin_path` | `util_` | Privilege-correct managed bin path (class B) | §9.3 |
| `inst_is_installed` | `inst_` | Detect managed binary executable | §9.4 |
| `inst_local_install` | `inst_` | Local copy install (**`install`**) | §9.5 |
| `inst_local_uninstall` | `inst_` | Local remove (**`uninstall`**) | §9.6 |
| `app_where_is_me` | `app_` | Path report command | §9.7 |
| `app_version` | `app_` | Local version (no network) | §4.3 |
| `app_about` / `app_help` / `app_main` | `app_` | Diagnostics / help / dispatch | CLI interface peer |
| `path_add_shell` (optional) | `path_` | User PATH ensure after install | path template |
| `prompt_yes_no` | `prompt_` | Uninstall confirm (**do-not-capture-read**: `if prompt_yes_no`; **MUST NOT** `$()`) | interactive template |
| `out_*` | `out_` | All user/machine messages | output template |

**Not in local mode:** `inst_perform_install*`, `inst_self_update`, `inst_self_uninstall*`, `ver_check`, `util_fetch_remote_version`.

### 9.2 `util_resolve_running_path` — class B return-via-stdout

```sh
# GENERAL PURPOSE: Resolve absolute path of the running ship unit for local install source.
# PRINTF EXCEPTION (class B): path data for $(…) capture only — not product UX.
util_resolve_running_path() {
    : "${0:=}"
    local src="$0"
    local dir base resolved

    case "$src" in
        ""|sh|bash|dash|ash|zsh|ksh|*/sh|*/bash|*/dash|*/ash)
            if [ ! -f "$src" ]; then
                printf '%s' ""
                return 0
            fi
            ;;
    esac

    if [ ! -f "$src" ] && [ ! -L "$src" ]; then
        printf '%s' ""
        return 0
    fi

    if command -v readlink >/dev/null 2>&1; then
        resolved=$(readlink -f "$src" 2>/dev/null || true)
        if [ -n "$resolved" ] && [ -e "$resolved" ]; then
            printf '%s' "$resolved"
            return 0
        fi
    fi
    if command -v realpath >/dev/null 2>&1; then
        resolved=$(realpath "$src" 2>/dev/null || true)
        if [ -n "$resolved" ] && [ -e "$resolved" ]; then
            printf '%s' "$resolved"
            return 0
        fi
    fi

    dir=$(CDPATH= cd -- "$(dirname -- "$src")" 2>/dev/null && pwd) || dir=""
    base=$(basename -- "$src" 2>/dev/null || printf '%s' "$src")
    if [ -n "$dir" ] && [ -n "$base" ]; then
        printf '%s' "${dir}/${base}"
        return 0
    fi
    printf '%s' "$src"
}
```

### 9.3 `util_get_install_bin_path` — class B return-via-stdout

```sh
# GENERAL PURPOSE: Privilege-correct managed install path for APP_NAME.
util_get_install_bin_path() {
    : "${APP_NAME:=app}"
    : "${JSON:=0}" : "${QUIET:=0}"
    : "${GLOBAL_BIN:=/usr/local/bin}"
    : "${HOME:=/tmp}"
    : "${USER_BIN:=${HOME}/.local/bin}"
    : "${FORCE_USER:=0}"
    : "${FORCE_GLOBAL:=0}"
    local bin_path=""

    if [ "${FORCE_USER}" -eq 1 ]; then
        bin_path="${USER_BIN}/${APP_NAME}"
    elif [ "${FORCE_GLOBAL}" -eq 1 ] || [ "$(id -u 2>/dev/null || echo 1)" -eq 0 ]; then
        bin_path="${GLOBAL_BIN}/${APP_NAME}"
    elif [ -f "${USER_BIN}/${APP_NAME}" ]; then
        bin_path="${USER_BIN}/${APP_NAME}"
    elif [ -f "${GLOBAL_BIN}/${APP_NAME}" ]; then
        bin_path="${GLOBAL_BIN}/${APP_NAME}"
        if [ "${JSON}" -eq 0 ] && [ "${QUIET}" -eq 0 ]; then
            out_warn "Global installation found. Operating on it (you may need elevated rights to uninstall)."
        fi
    else
        bin_path="${USER_BIN}/${APP_NAME}"
    fi
    printf '%s' "${bin_path}"
}
```

### 9.4 `inst_is_installed`

```sh
inst_is_installed() {
    local bin_path
    bin_path=$(util_get_install_bin_path)
    [ -n "$bin_path" ] && [ -x "$bin_path" ]
}
```

### 9.5 `inst_local_install` — user command `install`

```sh
# GENERAL PURPOSE: Copy running ship unit to managed bin (no network).
inst_local_install() {
    : "${APP_NAME:=app}"
    : "${VERSION:=0.0.0}"
    : "${FORCE:=0}"
    : "${JSON:=0}"
    : "${QUIET:=0}"
    : "${GLOBAL_BIN:=/usr/local/bin}"
    : "${HOME:=/tmp}"
    : "${USER_BIN:=${HOME}/.local/bin}"

    local src target target_dir tmp_file

    src=$(util_resolve_running_path)
    if [ -z "$src" ] || [ ! -f "$src" ]; then
        out_die "Cannot resolve running ship unit for local install. Run from the ${APP_NAME} script file."
    fi

    target=$(util_get_install_bin_path)
    target_dir=$(dirname -- "$target")

    if [ -x "$target" ] && [ "${FORCE}" -eq 0 ]; then
        if [ "${JSON}" -eq 1 ]; then
            out_json "out_success" "${APP_NAME} is already installed." \
                "path" "$target" "version" "${VERSION}"
        else
            out_success "${APP_NAME} is already installed at ${target}"
            out_info "Use --force to reinstall/replace from the running ship unit."
        fi
        return 0
    fi

    if [ ! -d "$target_dir" ]; then
        mkdir -p "$target_dir" 2>/dev/null || out_die "Cannot create install directory: ${target_dir}"
    fi
    if [ ! -w "$target_dir" ]; then
        out_die "Install directory not writable: ${target_dir}"
    fi

    out_info "Local install: copying ${src} → ${target}"

    tmp_file=$(mktemp "${target_dir}/.${APP_NAME}.XXXXXX" 2>/dev/null) || \
        tmp_file=$(mktemp 2>/dev/null) || out_die "Cannot create temporary file for local install"

    if ! cp -f "$src" "$tmp_file" 2>/dev/null; then
        rm -f "$tmp_file" 2>/dev/null || true
        out_die "Failed to copy ship unit to temporary install path"
    fi
    chmod 0755 "$tmp_file" || {
        rm -f "$tmp_file" 2>/dev/null || true
        out_die "Cannot set dest mode 0755 on staging file"
    }

    if ! mv -f "$tmp_file" "$target" 2>/dev/null; then
        rm -f "$tmp_file" 2>/dev/null || true
        out_die "Failed to move into place: ${target}"
    fi

    # Optional: path_add_shell   # user-bin only — path template

    if [ "${JSON}" -eq 1 ]; then
        out_json "out_success" "${APP_NAME} ${VERSION} installed (local)." \
            "path" "$target" "source" "$src"
    else
        out_success "${APP_NAME} ${VERSION} installed to ${target}"
        out_info "Ensure $(dirname -- "$target") is on your PATH if needed."
    fi
    return 0
}
```

### 9.6 `inst_local_uninstall` — user command `uninstall`

```sh
# GENERAL PURPOSE: Remove managed install binary only (local pair — not self-uninstall).
inst_local_uninstall() {
    : "${APP_NAME:=app}"
    : "${FORCE:=0}"
    : "${JSON:=0}"
    : "${QUIET:=0}"
    : "${GLOBAL_BIN:=/usr/local/bin}"
    : "${HOME:=/tmp}"
    : "${USER_BIN:=${HOME}/.local/bin}"

    local bin_path

    bin_path=$(util_get_install_bin_path)
    if [ ! -e "$bin_path" ]; then
        if [ -x "${GLOBAL_BIN}/${APP_NAME}" ]; then
            bin_path="${GLOBAL_BIN}/${APP_NAME}"
        elif [ -x "${USER_BIN}/${APP_NAME}" ]; then
            bin_path="${USER_BIN}/${APP_NAME}"
        fi
    fi

    if [ ! -e "$bin_path" ]; then
        if [ "${JSON}" -eq 1 ]; then
            out_json "out_success" "${APP_NAME} is not installed. Nothing to uninstall."
        else
            out_warn "${APP_NAME} is not installed. Nothing to uninstall."
        fi
        return 0
    fi

    if [ "${FORCE}" -eq 0 ]; then
        if [ "${JSON}" -eq 1 ] || [ "${QUIET}" -eq 1 ] || [ ! -t 0 ] || [ ! -t 1 ]; then
            if [ "${JSON}" -eq 1 ]; then
                out_json_error "Uninstall requires --force in non-interactive mode (refusing to remove ${bin_path})." "confirm_required"
            else
                out_error "Uninstall requires --force in non-interactive mode (refusing to remove ${bin_path})."
                out_info "Re-run with: ${APP_NAME} uninstall --force"
            fi
            return 1
        fi
        # WARNING — do-not-capture-read (**PP-A-22**): MUST NOT _y=$(prompt_yes_no …)
        if ! prompt_yes_no "This will remove: ${bin_path}"; then
            out_plain "Uninstall cancelled by user."
            return 1
        fi
    fi

    if ! rm -f "$bin_path" 2>/dev/null; then
        out_die "Failed to remove ${bin_path}"
    fi

    if [ "${JSON}" -eq 1 ]; then
        out_json "out_success" "${APP_NAME} has been uninstalled." "path" "$bin_path"
    else
        out_success "${APP_NAME} has been uninstalled (${bin_path})."
    fi
    return 0
}
```

### 9.7 `app_where_is_me`

```sh
# GENERAL PURPOSE: Report running path + managed install path.
app_where_is_me() {
    : "${APP_NAME:=app}"
    : "${JSON:=0}"
    : "${QUIET:=0}"
    : "${GLOBAL_BIN:=/usr/local/bin}"
    : "${HOME:=/tmp}"
    : "${USER_BIN:=${HOME}/.local/bin}"

    local running install_path installed="false"

    running=$(util_resolve_running_path)
    [ -z "$running" ] && running="(unresolved)"

    install_path=$(util_get_install_bin_path)
    if [ -x "$install_path" ]; then
        installed="true"
    elif [ -x "${GLOBAL_BIN}/${APP_NAME}" ]; then
        install_path="${GLOBAL_BIN}/${APP_NAME}"
        installed="true"
    elif [ -x "${USER_BIN}/${APP_NAME}" ]; then
        install_path="${USER_BIN}/${APP_NAME}"
        installed="true"
    fi

    if [ "${JSON}" -eq 1 ]; then
        out_json "where_is_me" "" \
            "app" "${APP_NAME}" \
            "running_path" "$running" \
            "install_path" "$install_path" \
            "installed" "$installed"
        return 0
    fi

    [ "${QUIET}" -eq 1 ] && { out_plain "$running"; return 0; }

    out_info "Running path:  ${running}"
    if [ "$installed" = "true" ]; then
        out_success "Installed:     ${install_path}"
    else
        out_info "Install path:  ${install_path} (not installed)"
        out_info "Install with:  ${APP_NAME} install"
    fi
}
```

### 9.8 Dispatcher wiring sketch (names only)

```sh
# Inside app_main — local package only
case "${COMMAND}" in
    install)      inst_local_install ;;
    uninstall)    inst_local_uninstall ;;   # not self-uninstall
    where-is-me)  app_where_is_me ;;
    version)      app_version ;;
    about)        app_about ;;
    help|*)       app_help ;;
esac
```

---

## 10. Empty argv

Local-only products **SHOULD** use **Type N** (empty argv → help) per `template-shell-cli-zero-arguments.md`.  
Do **not** force Type O install-ensure unless the product also specializes online-install.

---

## 11. Help / about honesty (local package)

When Layer A is Active, human `help` **MUST** list install / uninstall / where-is-me.  
When Layer B is Active, human `help` **MUST** list `version` (local), `about`, `help`.  
`help` / `about` **MUST NOT** productize:

- `curl \| sh` primary install one-liners  
- `SCRIPT_URL=` as required install UX  
- remote `version-check` / `self-update` as product commands  
- **Repository:** / **Install channel:** rows (forge slug and empty-channel text are not local-only operator diagnostics)

GUI / X11 products: `about` **MUST** print live `${DISPLAY:-}` (or unset). **MUST NOT** freeze a host display id as Config.

Optional **notes** may state that online update is out of scope (honest non-goal).

---

## 12. Why this pattern exists (CIAO)

- **Caution:** No silent network install; uninstall fail-closed without force.  
- **Intentional:** Local vs online modes are separate templates; local version ≠ remote version-check.  
- **Anti-fragile:** Air-gap / checkout-first workflows.  
- **Over-protect:** Atomic local publish; no over-delete on uninstall.  
- **Least privilege:** User bin vs global bin by invoker privilege.  
- **SSOT:** `VERSION` in ship unit for local version; output via `out_*`.

---

## Under command line for normal user only

When the ship unit detects a **command line for normal user only** (Termux, Git Bash, or the same class — term [`command-line-for-normal-user-only.md`](../../terminologies/command-line-for-normal-user-only.md)):

| MUST | MUST NOT |
|------|----------|
| Keep **normal user privilege** (Type 0) only | Implement or enable **admin privilege** (Type 1) or **dedicated system user privilege** (Type 2) |
| Document Type 1 **unused** and Type 2 **unused** | In-tool `sudo`; wrap `apt` / `dnf` / `yum`; write `/etc` dests; `useradd` / dedicated LPU; Type 2 `sudo -u` switch |
| Termux: named `pkg` as this login remains Type 0 (**`LM-SHELL-TERMUX-ISH`**) | Recommend `sudo curl \| sh` as the install path |
| Git Bash: same privilege ceiling | Invoke Termux `pkg` because Git Bash was detected |

Detect (typical): Termux — `PREFIX` contains `com.termux`; `TERMUX_VERSION` set; `/data/data/com.termux/files/usr` exists. Git Bash — `MSYSTEM` is `MINGW*` / `MSYS*` / `UCRT*` / `CLANG*`; `uname -s` is `MINGW*` / `MSYS*`. Windows cmd — `OS` is `Windows_NT` or `ComSpec`/`COMSPEC` names `cmd.exe` (after excluding Git Bash, Cygwin, WSL).

**This mold:** local `install` / `uninstall` stay Type 0 into `USER_BIN`; **MUST NOT** wrap `sudo` to write `GLOBAL_BIN` on that class.

---

## 13. Protection Rule (Sacred)

Future agents **MUST NOT**:

1. Reintroduce remote download / `SCRIPT_URL` as install source while claiming this template.  
2. Add remote `version-check` / `self-update` under this template’s ownership (use online self-management template).  
3. Rename local remove to **`self-uninstall`** without dual-mode law (online packages use `self-uninstall`; local keeps **`uninstall`** — term `self-uninstall`).  
3b. Strip the **Under command line for normal user only** section, or wrap `sudo` to write `GLOBAL_BIN` on that class.  
4. Replace or omit **local `version`** while still claiming a complete local Type 0 package without an explicit specialized omission.  
5. Confuse or rename remote version-check as “local version.”  
6. Duplicate full path-directory theory here — update location glossary terms instead.  
7. Duplicate full `path_add_*` bodies here — update `template-path-and-shell-support.md`.  
8. Remove where-is-me while claiming local self-managed.  
9. Auto-uninstall without confirm or `--force` in non-interactive mode.  
10. Delete domain data as part of uninstall.  
11. Hardcode product brands/hosts into this template as universal law.

---

## 14. How to specialize

1. Copy lifecycle law to `docs/requirements/requirement-shell-local-self-management.md` (or chosen key).  
2. Fill Implementation Notes (`{{APP_NAME}}`, ship path, empty-argv choice, whether path_add is required).  
3. Wire **full package** in CLI interface peer: Layer A + Layer B (`version` / `about` / `help`).  
4. Implement helpers; cite **live requirement** in product source only.  
5. Register in `docs/requirements/index.md`.  
6. Tests: local version human+JSON; install/uninstall/where-is-me; no remote channel cases unless dual-mode.  
7. If B was trimmed from online A, also run `skill-bootstrap-trim` honesty checks (drop version-check; keep local version).

---

## 15. Definition of done (template specialization)

Specialization of this template is **not done** until:

1. Layer A commands exist and match install/uninstall/where-is-me rules.  
2. Layer B **local version** works offline from ship-unit `VERSION`.  
3. Help lists A+B and does not productize online lifecycle.  
4. Empty argv is Type N help (unless dual-mode law says otherwise).  
5. No remote version-check/self-update under local-mode ownership.  
6. Live requirements registered; product source cites those files only.

---


## Design-time verification

| TP family / ID | Proof mold | Planned suite |
|----------------|------------|---------------|
| **TP-CLI-*** path/help surface | `../tests/template-shell-cli-test-plan.md` | product local suite |
| Local install/uninstall/where-is-me | product test file | declare in specialized REQ |

**RTM:** `../tests/template-requirement-test-traceability.md`

**Last Updated**: 2026-09-17  
**Owner**: {{OWNER}}  
**Version history:**  
- **1.3.2** (2026-09-17): `util_get_install_bin_path` prefers existing user dest, then global (warn). `: "${APP_NAME:=app}"`.  
- **1.3.1** (2026-09-15): Local atomic place **`chmod 0755`** (not `chmod +x` / **0711**). Same dest-mode contract as online install.  
- **1.2.0**: §8 Config variables + §9 full local function examples (`util_*` / `inst_local_*` / `app_where_is_me`).  
- **1.1.x**: Feature package, peer online ownership, install/uninstall naming fence.

**Alignment**: term `local-self-managed` · `where-is-me` · `shell-cli-config-variables` · location terms · path / interactive / output templates · CLI interface (local version) · skill-bootstrap-trim · contrast `template-self-management` / `template-online-install` · CIAO v2.10.2.
