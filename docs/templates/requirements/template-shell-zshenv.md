---
name: shell-zshenv
id: LM-SHELL-ZSHENV
kind: law-mold
description: >
  Portable law mold for zsh PATH on .zshenv. The same block on .zshrc is path_add_zshrc in LM-PATH.
  Cite as LM-SHELL-ZSHENV (path secondary).
---

**file**: template-shell-zshenv.md  
**Mold-ID**: LM-SHELL-ZSHENV  
**Status**: Active (Version 1.0.2 – `.zshenv` keeps the shared PATH block; `.zshrc` is `path_add_zshrc`)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered / Over-protect)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

## 1. Purpose

This template defines **always-on zsh PATH** for a CIAO-Lite CLI: after user-bin install, every zsh start finds `USER_BIN` because **`.zshenv`** carries the shared line from `path_export_line` (**`LM-PATH-AND-SHELL-SUPPORT`**).

Specialize into `requirement-shell-zshenv` (or the product’s named owner). Bash / Fish PATH, **profile-ensure**, the `.profile` append, and **`path_add_zshrc`** stay on **`LM-PATH-AND-SHELL-SUPPORT`**. This mold writes `.zshenv` only. It **MUST NOT** write `.zprofile` or put a `PATH` line inside the profile-ensure sample.

**Capability name (glossary SSOT):** [`shell-zshenv`](../../terminologies/shell-zshenv.md) — always-on zsh rc. PATH edit: [`shell-path-integration`](../../terminologies/shell-path-integration.md).

## Terminologies

Related glossary entries (**disk-truth**). Templates **point**; they do not redefine terms or act as product law.

| Term | Path | SSOT type | Role |
|------|------|-----------|------|
| **Project templates** | `docs/terminologies/project-templates.md` | `meta-catalog` | What law molds are |
| **Docs folder structure** | `docs/terminologies/docs-folder-structure.md` | `policy` | Where this mold lives |
| **No-hardcode policy** | `docs/terminologies/no-hardcode-policy.md` | `policy` | Placeholders only |
| **Dual policies** | `docs/terminologies/dual-policies.md` | `policy` | No-placeholder × no-hardcode |
| **Shell zshenv** | `docs/terminologies/shell-zshenv.md` | `product-law` | Always-on write target (`ZSHENV`) |
| **Shell zshrc** | `docs/terminologies/shell-zshrc.md` | `product-law` | Interactive zsh — same block via `path_add_zshrc` in **`LM-PATH`** |
| **Shell path integration** | `docs/terminologies/shell-path-integration.md` | `product-law` | Shared `export PATH=` identity |
| **Shell rc-file** | `docs/terminologies/shell-rc-file.md` | `mention-only` | File family |
| **Shell-rc feature** | `docs/terminologies/shell-rc-feature.md` | `product-law` | path-ensure catalog row |
| **Profile-ensure** | `docs/terminologies/profile-ensure.md` | `mention-only` | Login `.profile` create-if-absent; not this file |
| **Shell-rc test fixture** | `docs/terminologies/shell-rc-test-fixture.md` | `product-law` | Temp root + `ZSHENV` retarget |
| **Test-purpose verb** | `docs/terminologies/test-purpose-verb.md` | `product-law` | Class of `rc-test --file zshenv` |
| **Command line for normal user only** | `docs/terminologies/command-line-for-normal-user-only.md` | `policy` | PATH ensure stays Type 0 |
| **Template example function** | `docs/terminologies/template-example-function.md` | `mention-only` | `path_add_zshenv` body |
| **Template example variable** | `docs/terminologies/template-example-variable.md` | `mention-only` | `ZSHENV` / `USER_BIN` |

**SSOT types used:** `identity-runtime` · `mention-only` · `meta-catalog` · `policy` · `product-law`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md` · `docs/policies/policy-least-privilege.md`

## 2. Core rules

### 2.1 File

| MUST | MUST NOT |
|------|----------|
| Write zsh `USER_BIN` PATH to `ZSHENV` (default `{{HOME}}/.zshenv`) using `path_export_line` | Write `.zprofile`, or put PATH inside the profile-ensure sample |
| Honor a non-empty `ZSHENV` override (tests) | Hard-code only `{{HOME}}/.zshenv` |
| Create if missing **when** zsh environment **or** `ZSHENV` is set | Invent `{{HOME}}/.zshenv` for bash-only with no override |
| Modify if the file exists (keep body; append exact export if absent) | Replace / truncate an existing `.zshenv` |
| Use the exact line from `path_export_line` (one-directory, or two-directory when `/bin` is ahead of `/usr/local/bin`) | Make `path+=('…')` the line this product writes |
| Dual-mention Type 0 `rc-test --file zshenv --root` | Treat a missing `.zshenv` line as proved by `.zshrc` alone |

**Zsh environment** (any one): `basename "${SHELL:-}"` is `zsh`; caller set `ZSHENV`; target file exists.

### 2.2 Example implementation (`path_add_zshenv`)

**Kind:** [template-example-function](../../terminologies/template-example-function.md).

```sh
path_add_zshenv() {
    _zshenv_explicit=0
    if [ -n "${ZSHENV+x}" ]; then
        _zshenv_explicit=1
    fi
    : "${HOME:=/tmp}"
    : "${USER_BIN:=${HOME}/.local/bin}"
    : "${ZSHENV:=${HOME}/.zshenv}"
    : "${APP_NAME:=app}"
    : "${VERSION:=0.0.0}"
    : "${JSON:=0}"
    _zshenv="${ZSHENV}"
    _path_line=$(path_export_line)
    _comment=$(printf '# Added by %s installer (%s)' "${APP_NAME}" "${VERSION}")
    _zsh_shell=0
    case "$(basename "${SHELL:-}")" in
        zsh) _zsh_shell=1 ;;
    esac
    if [ ! -f "${_zshenv}" ]; then
        if [ "${_zshenv_explicit}" -eq 0 ] && [ "${_zsh_shell}" -eq 0 ]; then
            return 1
        fi
        if ! printf '# Always-on zsh rc created by %s installer (%s)\n' "$APP_NAME" "$VERSION" > "${_zshenv}"; then
            return 1
        fi
        if [ "${JSON}" -eq 0 ]; then
            out_plain "→ Created ${_zshenv}"
        fi
    fi
    if ! grep -Fxq "${_path_line}" "${_zshenv}" 2>/dev/null; then
        printf "\n%s\n" "${_comment}" >> "${_zshenv}"
        printf '%s\n' "${_path_line}" >> "${_zshenv}"
        if [ "${JSON}" -eq 0 ]; then
            out_plain "→ Added ${USER_BIN} to PATH for zsh (.zshenv)"
        fi
        return 0
    fi
    if ! grep -qF "${_comment}" "${_zshenv}" 2>/dev/null; then
        printf "\n%s\n" "${_comment}" >> "${_zshenv}"
        return 0
    fi
    return 1
}
```

`path_add_shell` **MUST** call `path_add_zshenv`. The same block on `.zshrc` is `path_add_zshrc` in **`LM-PATH-AND-SHELL-SUPPORT`**. This function does not write `.zshrc`.

## Under command line for normal user only

When the product may run on Termux, Git Bash, Windows cmd, or the same class: Type 1/2 unused on detect; no in-tool sudo / apt / dedicated system user; no `sudo curl | sh` recommend; Git Bash and Windows cmd do not invoke Termux `pkg`.

**This mold:** zshenv PATH ensure stays Type 0 this-login file writes. Tests retarget `ZSHENV` to a temp folder.

## Design-time verification

| TP family / ID | Intent |
|----------------|--------|
| **TP-LC-23** | Existing `ZSHENV` dongle kept; exact PATH appended |
| **TP-LC-24** | VERSION + exact PATH already match → bytes unchanged |
| **TP-LC-34** | `ZSHENV` set / `$SHELL` is zsh → create if missing |
| **TP-LC-35** | bash-only, no override, missing file → do not invent |
| **TP-LC-36** | Same exact line once on `.zshrc` when zsh applies (`path_add_zshrc` in **`LM-PATH-AND-SHELL-SUPPORT`**) |
| **`rc-test --file zshenv`** | Fixture `--root`; real home `.zshenv` untouched |

Proof mold: **`PM-INSTALL-LIFECYCLE-TEST-PLAN`** § zshenv. Gate: **`CL-SHELL-ZSHENV`**.

## How to specialize

1. Create `requirement-shell-zshenv` via **`SK-CREATE-SPECIFIC-REQUIREMENT`**.  
2. Dual-mention `rc-test --file zshenv` on the CLI-interface REQ.  
3. Point **`LM-PATH-AND-SHELL-SUPPORT`** leftover zsh row here.  
4. Implement `path_add_zshenv` with `path_export_line`. Leave `.zshrc` to `path_add_zshrc`.  
5. Same-change **TP-LC-23/24/34/35/36** in the product suite.

## Protection Rule (Sacred)

Future agents **MUST NOT**:

1. Drop the `.zshenv` line, write `.zprofile`, or put PATH inside the profile-ensure sample. `.zshrc` is `path_add_zshrc` in **`LM-PATH-AND-SHELL-SUPPORT`**. Profile-ensure is `path_ensure_profile`.  
2. Invent `{{HOME}}/.zshenv` for bash-only with no `ZSHENV` override.  
3. Replace an existing `.zshenv` body.  
4. Invent a private `path+=` dialect as the line this product writes.  
5. Skip `rc-test --file zshenv`.  
6. Treat this mold as product-source behavioral authority after specialize.  
7. Omit **Under command line for normal user only**.

**Last Updated**: 2026-09-29 (1.0.2 — `.zshenv` uses `path_export_line`; `.zshrc` is `path_add_zshrc` in `LM-PATH-AND-SHELL-SUPPORT`)  
**Version history:**  
- **1.0.2** (2026-09-29): This mold still writes `.zshenv` only. The interactive block is `path_add_zshrc`. The line is `path_export_line`.  
- **1.0.1** (2026-09-29): Profile-ensure stays on `LM-PATH-AND-SHELL-SUPPORT`. This mold does not write `.profile`.  
**Owner**: {{OWNER}}  
**Alignment**: **`SK-WRITE-TEMPLATE`** · **`SK-CREATE-SHELL-ZSHENV`** · [`shell-zshenv.md`](../../terminologies/shell-zshenv.md) · **`PO-STAY-IN-PROJECT-SSOT`** · CIAO / CIAO-Lite
