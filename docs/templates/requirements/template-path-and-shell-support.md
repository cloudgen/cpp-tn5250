---
name: path-and-shell-support
id: LM-PATH-AND-SHELL-SUPPORT
kind: law-mold
description: >
  Portable law mold. Cite as LM-PATH-AND-SHELL-SUPPORT (path secondary).
---

**file**: template-path-and-shell-support.md  
**Status**: Active (Version 1.9.0 – PATH block: `{{HOME}}/.local/bin` then `/usr/local/bin` when `/bin` is ahead)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

## 1. Purpose

This template defines how a CIAO-Lite CLI tool should handle PATH management and multi-shell compatibility after installation.

The goal is to ensure the installed binary is immediately usable without requiring the user to manually edit their shell configuration.

**Capability name (glossary SSOT):** [`shell-path-integration`](../../terminologies/shell-path-integration.md) — ensure the **local installation location** is on PATH via `.bashrc`, `.zshrc`, `.zshenv`, `.profile`, and Fish. The exact line is `path_export_line`. When this process `PATH` has `/bin` before `/usr/local/bin`, that line is `${HOME}/.local/bin` then `/usr/local/bin`. Zsh always-on write stays **`LM-SHELL-ZSHENV`** (`path_add_zshenv`). Interactive zsh uses `path_add_zshrc` in this mold. The sibling edit [`profile-ensure`](../../terminologies/profile-ensure.md) creates a missing `.profile` that sources `.bashrc`. That sample does **not** contain a `PATH` line. Path-ensure appends the block after the body.

## Terminologies

Related glossary entries (**disk-truth**). Templates **point**; they do not redefine terms or act as product law.
SSOT types follow `docs/policies/policy-ssot-terminology-for-templates.md`.
Binding rules: `docs/policies/policy-terminology-for-templates.md`.

| Term | Path | SSOT type | Role |
|------|------|-----------|------|
| **Project templates** | `docs/terminologies/project-templates.md` | `meta-catalog` | What law molds are; specialize-out target |
| **Docs folder structure** | `docs/terminologies/docs-folder-structure.md` | `policy` | Where this mold lives vs product law / tests |
| **No-hardcode policy** | `docs/terminologies/no-hardcode-policy.md` | `policy` | Placeholders only in portable molds |
| **Dual policies** | `docs/terminologies/dual-policies.md` | `policy` | No-placeholder × no-hardcode balance |
| **Terminology policy for templates** | `docs/terminologies/terminology-policy-for-templates.md` | `policy` | Mandatory Terminologies section rules |
| **SSOT-terminology policy for templates** | `docs/terminologies/ssot-terminology-policy-for-templates.md` | `policy` | SSOT type column on rows |
| **Shell CLI bootstrap** | `docs/terminologies/shell-cli-bootstrap.md` | `mention-only` | Install PATH integration |
| **Ship unit** | `docs/terminologies/ship-unit.md` | `identity-runtime` | Binary on PATH |
| **Appname policy** | `docs/terminologies/appname-policy.md` | `identity-runtime` | Path segments by APP_NAME |
| **Shell path integration** | `docs/terminologies/shell-path-integration.md` | `product-law` | Capability this mold owns (`path_add_*`) |
| **Profile-ensure** | `docs/terminologies/profile-ensure.md` | `product-law` | Create-if-absent `.profile` that sources `.bashrc`; never overwrite; sample has no `PATH` line |
| **Shell profile** | `docs/terminologies/shell-profile.md` | `product-law` | The login file `path_ensure_profile` writes |
| **Shell bashrc** | `docs/terminologies/shell-bashrc.md` | `product-law` | Interactive rc write target (`BASHRC` default `{{HOME}}/.bashrc`) |
| **Shell zshenv** | `docs/terminologies/shell-zshenv.md` | `product-law` | Zsh always-on rc — PATH owner **`LM-SHELL-ZSHENV`** |
| **Shell zshrc** | `docs/terminologies/shell-zshrc.md` | `product-law` | Interactive zsh — same PATH block via `path_add_zshrc` |
| **Shell rc-file** | `docs/terminologies/shell-rc-file.md` | `mention-only` | File family |
| **Shell-rc feature** | `docs/terminologies/shell-rc-feature.md` | `product-law` | path-ensure and profile-ensure are catalog rows |
| **Shell-rc test fixture** | `docs/terminologies/shell-rc-test-fixture.md` | `product-law` | Temp root + env retarget + cleanup; **MUST** `rc-test` when claimed |
| **Test-purpose verb** | `docs/terminologies/test-purpose-verb.md` | `product-law` | Class of `rc-test` |
| **LLM pain point** | `docs/terminologies/llm-pain-point.md` | `mention-only` | **`PP-A-24`** / **`PP-A-25`** |
| **Shell rc file ownership** | `docs/terminologies/shell-rc-file-ownership.md` | `product-law` | Owner after every create/modify |
| **Template example variable** | `docs/terminologies/template-example-variable.md` | `mention-only` | `BASHRC` / `USER_BIN` Config examples |
| **Template example function** | `docs/terminologies/template-example-function.md` | `mention-only` | `path_add_*` bodies in §3.1 |
| **Command line for normal user only** | `docs/terminologies/command-line-for-normal-user-only.md` | `policy` | PATH ensure stays Type 0 this-login |

**SSOT types used:** `identity-runtime` · `mention-only` · `meta-catalog` · `policy` · `product-law`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Installation Paths

**Glossary SSOTs (load when specializing):**  
[`shell-path-integration`](../../terminologies/shell-path-integration.md) ·  
[`local-installation-location`](../../terminologies/local-installation-location.md) ·  
[`global-installation-location`](../../terminologies/global-installation-location.md) ·  
function helpers: [`shell-function-naming-convention`](../../terminologies/shell-function-naming-convention.md) (`path_*`).

| Installation Type | Recommended Target Path | Config / env | Default For |
|-------------------|-------------------------|--------------|-------------|
| **Local** (user / non-root) | `${HOME}/.local/bin/{{APP_NAME}}` | `USER_BIN` → `${USER_BIN}/${APP_NAME}` | Normal users |
| **Global** (system-wide / root) | `/usr/local/bin/{{APP_NAME}}` | `GLOBAL_BIN` → `${GLOBAL_BIN}/${APP_NAME}` | Root / elevated install |

Portable defaults: `USER_BIN=${HOME}/.local/bin`, `GLOBAL_BIN=/usr/local/bin`. Resolve `HOME` before expanding `USER_BIN` under `set -u`.

### 2.1 Shell variables (install path Config SSOT)

Full inventories: glossary **global-installation-location** and **local-installation-location**. Summary used by install + path_add:

| Variable | Meaning | Default (portable) |
|----------|---------|-------------------|
| `HOME` | User home (resolve first under `set -u`) | passwd / getent / `/tmp` |
| `GLOBAL_BIN` | Global install **directory** | `/usr/local/bin` |
| `USER_BIN` | Local/user install **directory** | `${HOME}/.local/bin` |
| `BASHRC` | Interactive rc **write path** for `path_add_bashrc` | `${HOME}/.bashrc` (tests **MUST** retarget via a [shell-rc test fixture](../../terminologies/shell-rc-test-fixture.md)) |
| `ZSHENV` | Always-on zsh **write path** for `path_add_zshenv` | `${HOME}/.zshenv` (owner **`LM-SHELL-ZSHENV`**; line from `path_export_line`) |
| `ZSHRC` | Interactive zsh **write path** for `path_add_zshrc` | `${HOME}/.zshrc` (create when the shell is zsh, `ZSHRC` is set, or the file exists) |
| `FISH_CONFIG` | Fish **write path** for `path_add_fish` | `${HOME}/.config/fish/config.fish` |
| `PROFILE` | Login rc **write path** | `${HOME}/.profile`. Profile-ensure creates the sample. `path_add_profile` appends the PATH block after that body |
| `APP_NAME` | Binary basename | product identity |
| `INSTALL_PATH` | Resolved full path for this install op | `${GLOBAL_BIN}/${APP_NAME}` if root else `${USER_BIN}/${APP_NAME}` |
| `IS_ROOT` | Privilege flag for path selection | `1` if `id -u` = 0 else `0` |
| `FORCE_USER` | Force user path (when designed) | `0` |
| `FORCE_GLOBAL` | Force global path (when designed) | `0` |
| `VERSION` | Installer comment in shell rc (optional) | product version |
| `JSON` / `QUIET` | Suppress human PATH tips | `0` |

**Not path-location variables:** `SCRIPT_URL`, `REPO_*`, `CHECKSUM` (online channel).

```sh
: "${HOME:=/tmp}"
: "${GLOBAL_BIN:=/usr/local/bin}"
: "${USER_BIN:=${HOME}/.local/bin}"
: "${BASHRC:=${HOME}/.bashrc}"
: "${ZSHENV:=${HOME}/.zshenv}"
: "${ZSHRC:=${HOME}/.zshrc}"
: "${FISH_CONFIG:=${HOME}/.config/fish/config.fish}"
: "${PROFILE:=${HOME}/.profile}"
: "${APP_NAME:=app}"
if [ "$(id -u 2>/dev/null || echo 1)" -eq 0 ]; then
    IS_ROOT=1
    INSTALL_PATH="${GLOBAL_BIN}/${APP_NAME}"
else
    IS_ROOT=0
    INSTALL_PATH="${USER_BIN}/${APP_NAME}"
fi
: "${IS_ROOT:=0}"
```

## 3. PATH Configuration (shell-path-integration)

After user-level installation, the tool should automatically add the **local installation location** (e.g. `USER_BIN` / `~/.local/bin`) to the user's shell configuration files. This is **shell-path-integration** — not the same as placing the binary file (that is install to local/global location).

### Supported Shells (Recommended)
- **Bash** → `BASHRC` (default `{{HOME}}/.bashrc`; create if missing; env override for tests/CI)
- **Zsh always-on** → `ZSHENV` (default `{{HOME}}/.zshenv`; **`LM-SHELL-ZSHENV`** / `path_add_zshenv`)
- **Zsh interactive** → `ZSHRC` (default `{{HOME}}/.zshrc`; `path_add_zshrc` in this mold). On macOS, `/etc/zprofile` runs `path_helper` after `.zshenv` and can leave `/bin` ahead of `/usr/local/bin`. `.zshrc` runs later for an interactive zsh.
- **Fish** → `FISH_CONFIG` (default `{{HOME}}/.config/fish/config.fish`)
- **Login profile** → `PROFILE` (default `{{HOME}}/.profile`). Profile-ensure writes the source-bashrc sample when the file is absent. Path-ensure then appends the PATH block after that body. Login `sh` does not source `.bashrc`, so `.profile` carries the block itself.

**MUST NOT** create `{{HOME}}/.bash_profile` or `{{HOME}}/.zprofile` for this block. **MUST NOT** put `/usr/local/bin` ahead of `${HOME}/.local/bin`. **MUST NOT** write a `PATH` line into the pyenv shims directory or `/opt/homebrew`. **MUST NOT** install the CLI as `/usr/local/bin/{{APP_NAME}}` from this feature.

### PATH block (exact line)

Compare this process `PATH` from left to right. Strip one trailing slash. Skip an empty element. The condition holds when `/bin` appears before `/usr/local/bin`, and when `/bin` appears and `/usr/local/bin` does not. The first `/usr/local/bin` before the first `/bin` means the condition does not hold.

When the condition holds, one line. Home stays first. `/usr/local/bin` is the next directory this block adds, ahead of `/usr/bin` and `/bin`:

```sh
export PATH="${HOME}/.local/bin:/usr/local/bin:$PATH"
```

Fish: `set -gx PATH ${HOME}/.local/bin /usr/local/bin $PATH`.

When `/usr/local/bin` is already ahead of `/bin`, the block is only the user bin:

```sh
export PATH="${HOME}/.local/bin:$PATH"
```

Fish: `set -gx PATH ${HOME}/.local/bin $PATH`.

The default `USER_BIN` (`${HOME}/.local/bin`) is written with the literal `${HOME}` characters. A non-default `USER_BIN` is written expanded, in the same two shapes. The comment immediately above the line is `# Added by {{APP_NAME}} installer ({{VERSION}})`. Exact-line check is `grep -Fxq`. A directory mention on another line is not already present. An older one-directory line stays. When the condition holds and the two-directory line is absent, append the two-directory line. A second run adds nothing.

### Recommended Functions (prefix `path_` — shell-function-naming-convention)

| Function | Role |
|----------|------|
| `path_bin_before_usr_local` | True when `/bin` is ahead of `/usr/local/bin` on this process `PATH` |
| `path_rc_token` | Literal `${HOME}/.local/bin` when `USER_BIN` is that default; otherwise the expanded directory |
| `path_export_line` | The bash/zsh exact line for this process `PATH` |
| `path_fish_line` | The Fish exact line for this process `PATH` |
| `path_add_shell` | **Orchestrator** — run per-shell helpers, then profile-ensure, then the profile PATH append |
| `path_add_bashrc` | Ensure the exact line in `BASHRC` (create if missing) |
| `path_add_zshenv` | Ensure the exact line in `ZSHENV` (body: **`LM-SHELL-ZSHENV`**; line from `path_export_line`) |
| `path_add_zshrc` | Ensure the exact line in `ZSHRC` (create when zsh, `ZSHRC` set, or the file exists) |
| `path_add_fish` | Ensure the exact Fish line in `FISH_CONFIG` |
| `path_ensure_profile` | **Profile-ensure** — create `PROFILE` if absent so it sources `.bashrc`; never overwrite; sample has **no** `PATH` line |
| `path_add_profile` | Append the exact line after the existing `PROFILE` body. Do not create the file. Do not replace the body |

Do **not** use bare names like `add_path()` without the `path_` prefix.

### Bashrc PATH ensure (normative when claimed)

When a product claims **bash** shell-path-integration (`path_add_bashrc` / install companion writes interactive rc):

| MUST | MUST NOT |
|------|----------|
| Honor **`BASHRC`** (default `{{HOME}}/.bashrc`) as the **write path** | Hard-code only `{{HOME}}/.bashrc` so tests cannot retarget a temp file |
| **Create** the file if missing (header with `{{APP_NAME}}` / `{{VERSION}}`, then PATH) | Leave `BASHRC` missing when create is claimed |
| **Modify** an existing file: keep the prior body; append PATH if the exact export is absent | Replace / truncate an existing dongle or user rc |
| **No-op** when `{{VERSION}}` installer comments **and** the exact line from `path_export_line` already match | Treat a `USER_BIN` substring (comment, unrelated line) as already-good |
| Prove the three cases in **`PM-INSTALL-LIFECYCLE-TEST-PLAN`**: **TP-LC-20** create-if-missing, **TP-LC-21** modify dongle, **TP-LC-22** VERSION+exact-PATH no-op — all with `BASHRC` in a **[shell-rc test fixture](../../terminologies/shell-rc-test-fixture.md)** (`mktemp -d`, trap-remove), and `{{HOME}}/.bashrc` untouched. When zsh PATH is claimed: **TP-LC-23** / **TP-LC-24**. Dual-mention Type 0 **`rc-test --root`** on the CLI-interface REQ (**`PP-A-24`**) | Claim bashrc PATH ensure with only a HOME-isolated substring grep, or no tester verb |
| **Sibling unify:** the exact line from `path_export_line` (one-directory, or two-directory when `/bin` is ahead). An older one-directory line stays; append the two-directory line when that line is absent. Later product **MAY** add only its `# Added by {{APP_NAME}}` comment. **MUST NOT** a third PATH dialect or rewrite another app’s comments (**`PP-A-25`**) | Duplicate the same exact line; put `/usr/local/bin` ahead of the home bin |

These functions should:
- Check the **exact** PATH export line (idempotent)
- Append a comment with version and installer/tool name when adding
- Print a helpful message about restarting the terminal (unless in quiet/JSON mode)
- Route user-visible lines through `out_*` (file redirects use class-C printf exception)
- After every create or modify, align [shell-rc file ownership](../../terminologies/shell-rc-file-ownership.md) to the corresponding user (home owner). Writer euid **MUST NOT** remain the owner.

### Call site (after user-bin install)

```sh
# Inside local or online install success path (user install only — not root/global):
# path_add_shell
```

---

## 3.1 Example implementations (portable — from Type 0 shell CLIs)

**Kind:** [template-example-function](../../terminologies/template-example-function.md); path vars as [template-example-variable](../../terminologies/template-example-variable.md).  
Specialize `{{APP_NAME}}` / live `APP_NAME` + `VERSION` in product code. Bash example: create `BASHRC` if missing; idempotent `grep -qF` of the **exact** `export PATH=` line (not a `USER_BIN` substring).

**PRINTF EXCEPTION (class C – file I/O redirect):** `printf … >> "$rcfile"` writes shell config content to a file, not product stdout/stderr. User-visible “→ Added …” lines use `out_plain` / output SSOT.

### `path_bin_before_usr_local`, `path_rc_token`, `path_export_line`, `path_fish_line` — examples

**Kind:** [template-example-function](../../terminologies/template-example-function.md). `path_add_bashrc`, `path_add_zshenv`, `path_add_zshrc`, and `path_add_profile` call `path_export_line`. `path_add_fish` calls `path_fish_line`.

```sh
path_bin_before_usr_local() {
    _rest="${PATH-}"
    while [ -n "${_rest}" ]; do
        _elem="${_rest%%:*}"
        case "${_rest}" in
            *:*) _rest="${_rest#*:}" ;;
            *) _rest="" ;;
        esac
        case "${_elem}" in
            */) _elem="${_elem%/}" ;;
        esac
        [ -n "${_elem}" ] || continue
        if [ "${_elem}" = "/usr/local/bin" ]; then
            unset _rest _elem
            return 1
        fi
        if [ "${_elem}" = "/bin" ]; then
            unset _rest _elem
            return 0
        fi
    done
    unset _rest _elem
    return 1
}

path_rc_token() {
    : "${HOME:=/tmp}"
    : "${USER_BIN:=${HOME}/.local/bin}"
    if [ "${USER_BIN}" = "${HOME}/.local/bin" ]; then
        printf '%s\n' '${HOME}/.local/bin'
    else
        printf '%s\n' "${USER_BIN}"
    fi
}

path_export_line() {
    _ub=$(path_rc_token)
    if path_bin_before_usr_local; then
        printf 'export PATH="%s:/usr/local/bin:$PATH"\n' "${_ub}"
    else
        printf 'export PATH="%s:$PATH"\n' "${_ub}"
    fi
    unset _ub
}

path_fish_line() {
    _ub=$(path_rc_token)
    if path_bin_before_usr_local; then
        printf 'set -gx PATH %s /usr/local/bin $PATH\n' "${_ub}"
    else
        printf 'set -gx PATH %s $PATH\n' "${_ub}"
    fi
    unset _ub
}
```

### `path_add_bashrc` — example

```sh
# =============================================================================
# path_add_bashrc() - Ensure USER_BIN on PATH in BASHRC (default ~/.bashrc)
# =============================================================================
#
# GENERAL PURPOSE:
# Create BASHRC if missing, then append the exact export PATH line only if
# absent. Returns 0 if created or PATH was added, 1 if the exact line is
# already present or create/write failed.
#
# BASHRC defaults to ${HOME}/.bashrc. Tests/CI override BASHRC to a file in a
# random temp folder so this login's real interactive rc is not touched.
#
# Capability: shell-path-integration
# Last reviewed: 2026-09-09
# =============================================================================

path_add_bashrc() {
    : "${HOME:=/tmp}"
    : "${USER_BIN:=${HOME}/.local/bin}"
    : "${BASHRC:=${HOME}/.bashrc}"
    : "${APP_NAME:=app}"
    : "${VERSION:=0.0.0}"
    : "${JSON:=0}"

    local bashrc="${BASHRC}"
    local path_line
    local created=0
    path_line=$(path_export_line)

    if [ ! -f "$bashrc" ]; then
        if ! printf '# Interactive rc created by %s installer (%s)\n' "$APP_NAME" "$VERSION" > "$bashrc"; then
            if [ "${JSON}" -eq 0 ]; then
                out_warn "Could not create ${bashrc}. Next: create that file as this login, then re-run ${APP_NAME} install."
            fi
            return 1
        fi
        created=1
        if [ "${JSON}" -eq 0 ]; then
            out_plain "→ Created ${bashrc}"
        fi
    fi

    if ! grep -Fxq "${path_line}" "$bashrc" 2>/dev/null; then
        printf "\n# Added by %s installer (%s)\n" "${APP_NAME}" "${VERSION}" >> "$bashrc"
        printf '%s\n' "${path_line}" >> "$bashrc"
        if [ "${JSON}" -eq 0 ]; then
            out_plain "→ Added ${USER_BIN} to PATH for bash"
        fi
        return 0
    fi
    if [ "$created" -eq 1 ]; then
        return 0
    fi
    return 1  # exact export already present
}
```

### `path_add_zshrc` — example

**Kind:** [template-example-function](../../terminologies/template-example-function.md). Same exact line as `path_export_line`. Create when the shell basename is `zsh`, or `ZSHRC` is set, or the file exists. Keep an existing body. `.zshenv` stays `path_add_zshenv` (**`LM-SHELL-ZSHENV`**). This function does not write `.zprofile`.

```sh
path_add_zshrc() {
    _zshrc_explicit=0
    if [ -n "${ZSHRC+x}" ]; then
        _zshrc_explicit=1
    fi
    : "${HOME:=/tmp}"
    : "${USER_BIN:=${HOME}/.local/bin}"
    : "${ZSHRC:=${HOME}/.zshrc}"
    : "${APP_NAME:=app}"
    : "${VERSION:=0.0.0}"
    : "${JSON:=0}"
    _path_line=$(path_export_line)
    _comment=$(printf '# Added by %s installer (%s)' "${APP_NAME}" "${VERSION}")
    _zsh_shell=0
    case "$(basename "${SHELL:-}")" in
        zsh) _zsh_shell=1 ;;
    esac
    if [ ! -f "${ZSHRC}" ]; then
        if [ "${_zshrc_explicit}" -eq 0 ] && [ "${_zsh_shell}" -eq 0 ]; then
            unset _zshrc_explicit _path_line _comment _zsh_shell
            return 1
        fi
        if ! printf '# Interactive zsh rc created by %s installer (%s)\n' "$APP_NAME" "$VERSION" > "${ZSHRC}"; then
            unset _zshrc_explicit _path_line _comment _zsh_shell
            return 1
        fi
        if [ "${JSON}" -eq 0 ]; then
            out_plain "→ Created ${ZSHRC}"
        fi
    fi
    if ! grep -Fxq "${_path_line}" "${ZSHRC}" 2>/dev/null; then
        printf '\n%s\n' "${_comment}" >> "${ZSHRC}"
        printf '%s\n' "${_path_line}" >> "${ZSHRC}"
        if [ "${JSON}" -eq 0 ]; then
            out_plain "→ Added ${USER_BIN} to PATH for zsh (.zshrc)"
        fi
        unset _zshrc_explicit _path_line _comment _zsh_shell
        return 0
    fi
    unset _zshrc_explicit _path_line _comment _zsh_shell
    return 1
}
```

### `path_ensure_profile` — example

**Kind:** [template-example-function](../../terminologies/template-example-function.md). Feature: [profile-ensure](../../terminologies/profile-ensure.md). Create only when `PROFILE` is absent. The sample has no `PATH` line. **MUST NOT** replace an existing body. `path_add_profile` appends the PATH block after that body.

```sh
# =============================================================================
# path_ensure_profile() - Create PROFILE if absent so login sources .bashrc
# =============================================================================
#
# GENERAL PURPOSE:
# Profile-ensure. When PROFILE (default ${HOME}/.profile) is absent, write the
# source-bashrc sample and chmod 0644. When it exists, return 1 and leave the
# body. The sample has no PATH line. path_add_profile appends that block after
# the body. Returns 0 if created, 1 if present or the write failed.
#
# Capability: profile-ensure
# Last updated: 2026-09-29
# =============================================================================

path_ensure_profile() {
    : "${HOME:=/tmp}"
    : "${PROFILE:=${HOME}/.profile}"
    : "${APP_NAME:=app}"
    : "${JSON:=0}"

    if [ -e "${PROFILE}" ]; then
        return 1
    fi

    {
        printf '# BEGIN %s profile source-bashrc\n' "${APP_NAME}"
        printf '%s\n' '# Created so a bash login shell sources interactive rc.'
        printf '%s\n' 'if [ -n "${BASH_VERSION:-}" ]; then'
        printf '%s\n' '    if [ -f "${HOME}/.bashrc" ]; then'
        printf '%s\n' '        . "${HOME}/.bashrc"'
        printf '%s\n' '    fi'
        printf '%s\n' 'fi'
        printf '# END %s profile source-bashrc\n' "${APP_NAME}"
    } > "${PROFILE}" || return 1

    chmod 0644 "${PROFILE}" || return 1
    _user=$(id -un 2>/dev/null || true)
    _group=$(id -gn 2>/dev/null || true)
    if [ -n "${_user}" ] && getent passwd "${_user}" >/dev/null 2>&1; then
        chown "${_user}:${_group}" "${PROFILE}" || return 1
    fi
    if [ "${JSON}" -eq 0 ]; then
        out_plain "→ Created ${PROFILE}"
    fi
    return 0
}
```

### `path_add_profile` — example

**Kind:** [template-example-function](../../terminologies/template-example-function.md). Append the exact `path_export_line` after the existing body. Do not create `PROFILE` (profile-ensure does that). Do not replace the body. Do not put the line inside the source-bashrc sample.

```sh
path_add_profile() {
    : "${HOME:=/tmp}"
    : "${PROFILE:=${HOME}/.profile}"
    : "${USER_BIN:=${HOME}/.local/bin}"
    : "${APP_NAME:=app}"
    : "${VERSION:=0.0.0}"
    : "${JSON:=0}"
    if [ ! -f "${PROFILE}" ]; then
        return 1
    fi
    _path_line=$(path_export_line)
    if grep -Fxq "${_path_line}" "${PROFILE}" 2>/dev/null; then
        unset _path_line
        return 1
    fi
    printf '\n# Added by %s installer (%s)\n' "${APP_NAME}" "${VERSION}" >> "${PROFILE}"
    printf '%s\n' "${_path_line}" >> "${PROFILE}"
    if [ "${JSON}" -eq 0 ]; then
        out_plain "→ Added ${USER_BIN} to PATH in ${PROFILE}"
    fi
    unset _path_line
    return 0
}
```

### `path_add_fish` — example

```sh
# =============================================================================
# path_add_fish() - Ensure USER_BIN on PATH in Fish config
# =============================================================================
#
# GENERAL PURPOSE:
# Create ~/.config/fish if needed; append the exact path_fish_line only if absent.
# A directory mention on another line is not already present.
# Returns 0 if a new line was added, 1 if failed or already present.
#
# Capability: shell-path-integration
# Last reviewed: 2026-07-17
# =============================================================================

path_add_fish() {
    : "${HOME:=/tmp}"
    : "${USER_BIN:=${HOME}/.local/bin}"
    : "${FISH_CONFIG:=${HOME}/.config/fish/config.fish}"
    : "${APP_NAME:=app}"
    : "${VERSION:=0.0.0}"
    : "${JSON:=0}"

    local fish_config="${FISH_CONFIG}"
    local path_line
    path_line=$(path_fish_line)

    if [ ! -d "${HOME}/.config/fish" ] && ! mkdir -p "${HOME}/.config/fish" 2>/dev/null; then
        return 1
    fi

    if [ -f "$fish_config" ] && grep -Fxq "${path_line}" "$fish_config" 2>/dev/null; then
        return 1  # exact line already present
    fi

    printf "\n# Added by %s installer (%s)\n" "${APP_NAME}" "${VERSION}" >> "$fish_config"
    printf '%s\n' "${path_line}" >> "$fish_config"

    if [ "${JSON}" -eq 0 ]; then
        out_plain "→ Added ${USER_BIN} to PATH for fish shell"
    fi
    return 0
}
```

### `path_add_shell` — orchestrator example

```sh
# =============================================================================
# path_add_shell() - Orchestrator: path-ensure plus profile-ensure
# =============================================================================
#
# GENERAL PURPOSE:
# Ensure the path_export_line block is on bash, zsh (.zshenv and .zshrc),
# fish, and .profile. Profile-ensure runs first so a missing PROFILE exists;
# path_add_profile appends after that sample. Call only after successful
# user-local install (not global/root installs).
#
# Capability: shell-path-integration · profile-ensure
# Last updated: 2026-09-29
# =============================================================================

path_add_shell() {
    : "${HOME:=/tmp}"
    : "${BASHRC:=${HOME}/.bashrc}"
    : "${ZSHENV:=${HOME}/.zshenv}"
    : "${ZSHRC:=${HOME}/.zshrc}"
    : "${PROFILE:=${HOME}/.profile}"
    : "${JSON:=0}"

    local added=0
    local shell_config="N/A"

    if path_add_bashrc; then
        added=1
        shell_config="${BASHRC}"
    fi

    if path_add_zshenv; then
        added=1
        if [ "$shell_config" = "N/A" ]; then
            shell_config="${ZSHENV}"
        else
            shell_config="${shell_config} ${ZSHENV}"
        fi
    fi

    if path_add_zshrc; then
        added=1
        if [ "$shell_config" = "N/A" ]; then
            shell_config="${ZSHRC}"
        else
            shell_config="${shell_config} ${ZSHRC}"
        fi
    fi

    if path_add_fish; then
        added=1
        if [ "$shell_config" = "N/A" ]; then
            shell_config="${HOME}/.config/fish/config.fish"
        else
            shell_config="${shell_config} ${HOME}/.config/fish/config.fish"
        fi
    fi

    path_ensure_profile || true
    if path_add_profile; then
        added=1
        if [ "$shell_config" = "N/A" ]; then
            shell_config="${PROFILE}"
        else
            shell_config="${shell_config} ${PROFILE}"
        fi
    fi

    if [ "$added" -eq 1 ] && [ "${JSON}" -eq 0 ]; then
        out_plain "→ Restart your terminal or run: source ${shell_config}"
    fi
}
```

### Return-code convention (this example set)

| Return | Meaning (`path_add_bashrc`) |
|--------|----------------------------|
| `0` | File **created** and/or a **new** exact PATH export was written |
| `1` | Write failed, **or** the exact line from `path_export_line` is already present |

Orchestrator treats `0` as “something was added” for the restart hint. Already-present (exact line + current `VERSION` comments) is still a successful ensure for idempotency (no rewrite, no duplicate lines).

### `path_rc_test` — Type 0 test-purpose (prove PATH in `--root` tmp)

**Kind:** [template-example-function](../../terminologies/template-example-function.md). Routed-verb **`rc-test`**. Dual-mention on CLI-interface. Help lists testers **apart** from operational verbs. **MUST NOT** write this login’s real `{{HOME}}/.bashrc`.

```sh
# Usage: {{APP_NAME}} rc-test --root DIR --file bashrc|profile --case create|modify|noop
# GENERAL PURPOSE: Prove path_add_* / profile-ensure against a temp tree.
path_rc_test() {
    : "${HOME:=/tmp}" : "${APP_NAME:=app}"
    _root="" _file="bashrc" _cas="create"
    while [ $# -gt 0 ]; do
        case "$1" in
            --root) _root="${2-}"; shift ;;
            --file) _file="${2-}"; shift ;;
            --case) _cas="${2-}"; shift ;;
            *) out_die "Unknown rc-test flag '$1'. Next: ${APP_NAME} rc-test --root DIR --file bashrc --case create" ;;
        esac
        shift
    done
    [ -n "${_root}" ] || out_die "rc-test needs --root a temp folder. Next: ${APP_NAME} rc-test --root DIR --file bashrc --case create"
    case "${_root}" in
        "${HOME}"|"${HOME}/"|/|"/home")
            out_die "rc-test --root must not be this login home. Next: use a tmp/cache folder"
            ;;
    esac
    BASHRC="${_root}/.bashrc"
    PROFILE="${_root}/.profile"
    export BASHRC PROFILE
    case "${_cas}" in
        create) ;;
        modify)
            printf '# dongle-keep-rc-test\n' > "${BASHRC}"
            ;;
        noop)
            path_add_bashrc || true
            ;;
        *)
            out_die "rc-test --case must be create, modify, or noop."
            ;;
    esac
    case "${_file}" in
        bashrc) path_add_bashrc || true ;;
        profile) path_ensure_profile || true ;;
        *) out_die "rc-test --file must be bashrc or profile." ;;
    esac
    out_success "rc-test ${_cas} ${_file} under ${_root}"
    unset _root _file _cas
}
```

---

## 4. Core Requirements

- Must work correctly for both fresh and existing shell configuration files
- Must not duplicate PATH entries (exact `export PATH=` line, not a directory substring)
- **Bash:** create `BASHRC` if missing; modify an existing dongle/user body (keep it); no-op when `VERSION` comments and the exact export already match
- **`BASHRC` env** (default `{{HOME}}/.bashrc`) is the write path so tests can use a random temp folder without touching this login’s real interactive rc
- Must support adding the directory even if it didn't exist before installation (especially Fish dir create)
- Must be silent in `--json` mode for human PATH tips
- Must respect user vs system installation (only run shell-path-integration for user-level installs)
- User-visible messages go through output SSOT (`out_plain` / `out_*`)
- Claiming bashrc PATH ensure **without** **TP-LC-20** / **TP-LC-21** / **TP-LC-22** (or equivalent named cases) is incomplete design
- Claiming path-ensure **without** a Type 0 `rc-test` (or dual-mentioned peer) that accepts `--root` a tmp/cache folder is **`PP-A-24`**
- A second sibling product **MUST NOT** append a second exact PATH export or invent a private PATH dialect (**`PP-A-25`**)
- **Profile-ensure:** create `PROFILE` when absent with the source-bashrc sample; **MUST NOT** overwrite an existing body; the sample has no PATH line. **Path-ensure** appends the block after that body on `.profile`, and writes the same block on `.bashrc`, `.zshrc`, `.zshenv`, and Fish. **MUST NOT** create `.bash_profile` or `.zprofile`

## 5. Why This Requirement Exists (Direct CIAO Alignment)

- **CIAO Principle 1 – Caution** (https://github.com/cloudgen/ciao): Never break or corrupt the user’s existing shell configuration.
- **CIAO Principle 2 – Intentional** (https://github.com/cloudgen/ciao): PATH addition must be traceable, idempotent, and well-documented.
- **CIAO Principle 3 – Anti-fragile** (https://github.com/cloudgen/ciao): Must work across bash, zsh, fish, and common environments without manual intervention.
- **CIAO Principle 4 / CIAO-Lite O · Principle 20 – Over-protect / Protect Against AI** (https://github.com/cloudgen/ciao): Idempotent checks and comments prevent repeated or destructive modifications.

## 6. Design Principles (CIAO / CIAO-Lite)

- **Caution (CIAO Principle 1)**: Never break existing shell configuration.
- **Intentional (CIAO Principle 2)**: Clear, idempotent PATH addition with traceable comments.
- **Anti-fragile (CIAO Principle 3)**: Works across bash, zsh, fish, and future shells.
- **Over-protect (CIAO Principle 4 / CIAO-Lite O · Principle 20)**: Idempotent checks prevent repeated or accidental modifications.

## Under command line for normal user only

When the ship unit detects a **command line for normal user only** (Termux, Git Bash, Windows cmd, or the same class — term [`command-line-for-normal-user-only.md`](../../terminologies/command-line-for-normal-user-only.md)):

| MUST | MUST NOT |
|------|----------|
| Keep **normal user privilege** (Type 0) only | Implement or enable **admin privilege** (Type 1) or **dedicated system user privilege** (Type 2) to write this-login rc |
| Write **this login’s** `BASHRC` / `USER_BIN` PATH | Rewrite another user’s rc; in-tool `sudo`; wrap `apt` |
| Termux: named `pkg` stays Type 0 (**`LM-SHELL-TERMUX-ISH`**) | Recommend `sudo curl \| sh` so PATH ensure runs as root |

**This mold:** PATH ensure is a Type 0 this-login file write. Tests retarget `BASHRC` to a temp folder — they **MUST NOT** require `sudo` or the developer’s real home.

---

## 7. Protection Rule (Sacred)

**Future AI assistants, Grok, or maintainers MUST NOT**:

- Remove support for common shells (bash, zsh, fish at minimum)
- Use raw product-banner `echo`/`printf` instead of the central output system for PATH **messages** (file I/O redirects for rc content are class-C exceptions)
- Make PATH addition non-idempotent (duplicates must be avoided)
- Remove the comment that identifies the installer/tool and version
- Change the target user directory without updating all related logic
- Bypass the orchestrator function for PATH management
- Strip shared `USER_BIN` from PATH on uninstall while other tools still use that directory
- Ignore a non-empty `BASHRC` / `ZSHRC` / `FISH_CONFIG` env (always write only under `{{HOME}}` instead)
- Leave a [shell-rc test fixture](../../terminologies/shell-rc-test-fixture.md) directory behind after PATH tests
- Leave `BASHRC` missing when install companion claims create-if-missing
- Replace an existing bashrc body instead of appending PATH
- Treat a `USER_BIN` substring as already-good when the exact `export PATH=` line is absent
- Claim bashrc PATH ensure **without** named tests: create-if-missing, modify dongle/existing, no-op when `VERSION` + exact `export PATH=` already match (**TP-LC-20** / **TP-LC-21** / **TP-LC-22** in **`PM-INSTALL-LIFECYCLE-TEST-PLAN`**)
- Claim path-ensure **without** dual-mentioning Type 0 **`rc-test --root`** (**`PP-A-24`**)
- Let a second sibling product duplicate the exact PATH export, invent a private PATH dialect, or rewrite another `{{APP_NAME}}` comment (**`PP-A-25`**)
- Put `/usr/local/bin` ahead of `${HOME}/.local/bin`, or skip the two-directory line when `/bin` is ahead of `/usr/local/bin`
- Put the PATH line inside the profile-ensure sample, overwrite an existing `.profile` body, or skip profile-ensure because `PROFILE` is missing
- Create `.bash_profile` or `.zprofile` for this block, or write pyenv shims or `/opt/homebrew` into the line
- Delete `.profile` while removing a path-ensure line, or strip the profile-ensure sample on uninstall
- Remove the installer comment or either exact PATH line (one-directory or two-directory, bash or Fish) while `USER_BIN` still holds other tools. When `USER_BIN` is empty, remove those lines and the installer comment from `.bashrc`, `.zshrc`, `.zshenv`, `.profile`, and Fish

**Reliable PATH setup after installation is critical for a good post-install UX** (especially Type O `curl | sh` user-bin installs; also local self-managed / package installs that land in `~/.local/bin`).

---


## Design-time verification

When bashrc PATH ensure is claimed, these cases are **Core** (not n/a). Isolation: set `BASHRC` to a file in a **random temp folder**; assert `{{HOME}}/.bashrc` is not written.

| TP family / ID | Proof mold | Intent |
|----------------|------------|--------|
| **TP-LC-11** | **`PM-INSTALL-LIFECYCLE-TEST-PLAN`** | Default write path: create bashrc with `USER_BIN` PATH + `VERSION` |
| **TP-LC-13** | **`PM-INSTALL-LIFECYCLE-TEST-PLAN`** | Re-run does not duplicate the exact `export PATH=` line |
| **TP-LC-20** | **`PM-INSTALL-LIFECYCLE-TEST-PLAN`** | `BASHRC` env: **create** in a random temp folder when missing |
| **TP-LC-21** | **`PM-INSTALL-LIFECYCLE-TEST-PLAN`** | `BASHRC` env: **modify** a dongle/existing rc (keep body; append PATH + VERSION once) |
| **TP-LC-23** | **`PM-INSTALL-LIFECYCLE-TEST-PLAN`** | `ZSHRC` env: **modify** existing zshrc in a fixture (when zsh PATH claimed) |
| **TP-LC-24** | **`PM-INSTALL-LIFECYCLE-TEST-PLAN`** | `ZSHRC` env: exact PATH **no-op** (when zsh PATH claimed) |
| **TP-LC-22** | **`PM-INSTALL-LIFECYCLE-TEST-PLAN`** | `BASHRC` env: **no-op** when `VERSION` comments **and** exact `export PATH=` already match (bytes unchanged) |
| **`rc-test`** | **`LM-CLI-INTERFACE`** + [shell-rc-test-fixture](../../terminologies/shell-rc-test-fixture.md) | Type 0 tester: `--root` tmp/cache; `--case create\|modify\|noop` drives **TP-LC-20..22** (**`PP-A-24`**) |
| **TP-LC-12** | **`PM-INSTALL-LIFECYCLE-TEST-PLAN`** | Profile-ensure: install creates `PROFILE` that sources bashrc, only when absent |
| **TP-LC-14** | **`PM-INSTALL-LIFECYCLE-TEST-PLAN`** | Profile-ensure: existing `PROFILE` body kept. Path-ensure may append the PATH block after that body |
| **TP-LC-36** | **`PM-INSTALL-LIFECYCLE-TEST-PLAN`** | Same exact line once on `.zshrc` when zsh applies (`path_add_zshrc`) |

**RTM:** `../tests/template-requirement-test-traceability.md`

**Last Updated**: 2026-09-29 (1.9.0: PATH block is `${HOME}/.local/bin` then `/usr/local/bin` when `/bin` is ahead; written on `.bashrc`, `.zshrc`, `.zshenv`, `.profile`, and Fish)  
**Owner**: Shell Integration Layer (Generalized Template)  
**Version history:**  
- **1.9.0** (2026-09-29): When `/bin` is ahead of `/usr/local/bin`, `path_export_line` is `${HOME}/.local/bin` then `/usr/local/bin`. Orchestrator calls `path_add_zshrc` and `path_add_profile`. The profile-ensure sample stays free of PATH.  
- **1.8.0** (2026-09-29): Define `path_ensure_profile`. Orchestrator calls it and `path_add_zshenv`. PATH is not written into `.profile` or `.zshrc`.  
- **1.7.0** (status before 1.8.0): zsh PATH points at `LM-SHELL-ZSHENV`.  
- **1.6.0** (2026-09-12): `path_rc_test` example — `--root` tmp only; never this login `{{HOME}}/.bashrc`.  
- **1.5.0** (2026-09-09): Sibling-unify one `USER_BIN` PATH line (**`PP-A-25`**). Claiming path-ensure **MUST** dual-mention Type 0 **`rc-test --root`** (**`PP-A-24`**).  
- **1.4.0** (2026-09-09): `ZSHRC`/`FISH_CONFIG` env + [shell-rc test fixture](../../terminologies/shell-rc-test-fixture.md) cleanup.  
- **1.3.0** (2026-09-09): `BASHRC` env; create-if-missing; exact `export PATH=` no-op; **TP-LC-20..22** required whenever bashrc PATH ensure is claimed.  
- **1.2.0**: shell-rc-file-ownership after every path_add write.  
**Alignment**: Glossary `shell-path-integration` · `shell-bashrc`; example shape from Type 0 shell CLI `path_add_*`; **`LM-SELF-MANAGEMENT`**, **`LM-IDEMPOTENCY`**, **`LM-ONLINE-INSTALL`**, **`PM-INSTALL-LIFECYCLE-TEST-PLAN`**; **CIAO Principles 1, 2, 3, 4, 20** (https://github.com/cloudgen/ciao).

---

**How to use this template**:
1. Copy/specialize into a project requirement when PATH UX is claimed (e.g. `requirement-shell-path-and-shell-support.md` or fold into local/online self-management REQ Implementation Notes).
2. Keep portable defaults (`USER_BIN` / `GLOBAL_BIN` / `BASHRC`); fill product `APP_NAME` / `VERSION` only in specialized code or Implementation Notes.
3. Implement `path_bin_before_usr_local`, `path_export_line`, `path_fish_line`, `path_add_bashrc`, `path_add_zshenv` (**`LM-SHELL-ZSHENV`**), `path_add_zshrc`, `path_add_fish`, `path_ensure_profile`, and `path_add_profile` (examples in §3.1); call `path_add_shell` only after successful **user-local** install.
4. Keep the Protection Rule and idempotency requirements intact.
5. Same-change: specialized REQ **Design-time verification** names **TP-LC-20** / **TP-LC-21** / **TP-LC-22** (or explicit n/a with reason if bashrc PATH ensure is **not** claimed).
6. After specialization, register any new `requirement-*.md` in `docs/requirements/index.md` (requirement rows only — do not list template paths in the registry).
