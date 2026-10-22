---
name: shell-sudoer
id: LM-SHELL-SUDOER
kind: law-mold
description: >
  Portable law mold for a POSIX shell CLI’s sudoer features: JSON grant,
  sudoers(5) text dual, print/generate/submit/remove workflow, and the
  in-tool util_sudo wrap. Cite as LM-SHELL-SUDOER. Sample code lives here
  so agents copy instead of reinventing. Elev ops (backup-config) compose
  this mold — they MUST NOT invent a second wrap or grant.
---

**file**: template-shell-sudoer.md  
**Mold-ID**: LM-SHELL-SUDOER  
**Status**: Active (Version 1.0.0)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered / Over-protect)

**Folder structure (policy):** [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md). This file is a **law mold** under `docs/templates/requirements/`.

# Template: Shell sudoer features

## 1. Purpose

Portable law for **all sudoer-related features** on a POSIX `/bin/sh` CLI:

1. JSON grant body + sudoers(5) text dual (project command only).  
2. Type 0 workflow: `print-sudoers`, `print-sudoers-install-script`, `generate-sudoer-request`, `submit-sudoer-request`, `remove-project-sudoers`.  
3. One in-tool wrap `util_sudo` + studied allow table.

Specialize into `requirement-shell-sudoer`. **This mold is not product law.** Product source cites the specialized requirement.

**Peers (point, do not duplicate bodies):**

| Concern | Owner |
|---------|--------|
| Type 0/1/2 architecture | **`LM-THREE-LAYER-PRIVILEGE-MODEL`** |
| JSON field table / `kind` when two grants exist | **`LM-SUDOER-JSON-FILE`** |
| Wrap C0–C6 only | **`LM-SHELL-SUDO-COMMAND`** (this mold **owns the complete CLI + samples**) |
| Config-file deposit that **uses** this grant | **`LM-SHELL-CONFIG-BACKUP`** (depends on this mold) |
| Folder-archive `backup` / `restore` | **`LM-FOLDER-ARCHIVE-BACKUP`** (different product; **MUST NOT** mix verbs) |

## 2. Terminologies

| Term | Path | SSOT type | Role |
|------|------|-----------|------|
| **Sudoer JSON file** | `docs/terminologies/sudoer-json-file.md` | `product-law` | Grant body |
| **Sudoers fragment** | `docs/terminologies/sudoers-fragment.md` | `product-law` | Text dual |
| **Project-sudoers-file** | `docs/terminologies/project-sudoers-file.md` | `product-law` | Draft / installed dest |
| **Sudo-wrapping function** | `docs/terminologies/sudo-wrapping-function.md` | `product-law` | `util_sudo` |
| **Sudoers exact argv** | `docs/terminologies/sudoers-exact-argv.md` | `product-law` | Verb-only ≠ `verb *` |
| **Three-layer privilege** | `docs/terminologies/three-layer-privilege.md` | `product-law` | Type map |
| **Command line for normal user only** | `docs/terminologies/command-line-for-normal-user-only.md` | `product-law` | Type 1/2 unused |
| **Least privilege** | `docs/terminologies/least-privilege.md` | `policy` | Minimum elev |
| **LLM escape** | `docs/terminologies/llm-escape.md` | `policy` | Broad sudoers / OS-tool grant |
| **Template example function** | `docs/terminologies/template-example-function.md` | `mention-only` | Sample bodies below |
| **SSOT catalog** | `docs/terminologies/ssot-catalog.md` | `meta-catalog` | Inventory |

**SSOT types used:** `product-law` · `policy` · `mention-only` · `meta-catalog`

**Policies:** `docs/policies/policy-least-privilege.md` · `docs/policies/policy-no-hardcode.md` · **`PO-NON-EXPOSE-LOCAL-MACHINE`**

**Missing terms:** none

## 3. Core rules (portable)

### 3.1 Verbs (dual mention with **`LM-CLI-INTERFACE`**)

| Verb | Privilege | Behavior |
|------|-----------|----------|
| `print-sudoers [path]` | Type 0 | Emit fragment; **MUST NOT** write `/etc` |
| `print-sudoers-install-script [path]` | Type 0 | Write admin script; **MUST NOT** run as root |
| `generate-sudoer-request [path]` | Type 0 | Local JSON; **MUST NOT** write inbound |
| `submit-sudoer-request [file]` | Type 0 | Compose into sibling inbound; **MUST NOT** mkdir inbound |
| `remove-project-sudoers [path]` | Type 0 | Delete **user draft** only |

Samples (specialize `{{APP_NAME}}`):

```text
{{APP_NAME}} print-sudoers
{{APP_NAME}} generate-sudoer-request
{{APP_NAME}} submit-sudoer-request
{{APP_NAME}} print-sudoers-install-script
{{APP_NAME}} remove-project-sudoers
```

### 3.2 Grant (project command only)

1. Grant **MUST** name only `{{GLOBAL_BIN}}/{{APP_NAME}}`.  
2. `commands[].args` **MUST** be the elev verb only (typical `["{{ELEV_VERB}}"]`, often `backup-config`). **MUST NOT** use `*`.  
3. `runas` **MUST** be `root`; tags **MUST** include `NOPASSWD` when the wrap uses `sudo -n`.  
4. **MUST NOT** allowlist `cp`, `mkdir`, `chmod`, `chown`, `tar`, `rm`, shells. After elev, the **product command** does those internally.  
5. Single Type 1 deposit grant **MAY** omit `kind`. **MUST NOT** label it `login-hook-elev`.  
6. **MUST NOT** grant Type 0 verbs (`sync-config`, `print-sudoers`, …).

**Filename grammar (queued):**

```text
sudoer-{{YYYYMMDD}}-{{APP_NAME}}-{{username}}-{{action}}-{{n}}.json
```

**Sample JSON (add):**

```json
{
  "schema_version": 1,
  "purpose": "Allow {{USERNAME}} to run {{APP_NAME}} {{ELEV_VERB}} as root.",
  "username": "{{USERNAME}}",
  "service": "{{APP_NAME}}",
  "action": "add",
  "commands": [
    {
      "runas": "root",
      "tags": ["NOPASSWD"],
      "path": "{{GLOBAL_BIN}}/{{APP_NAME}}",
      "args": ["{{ELEV_VERB}}"]
    }
  ]
}
```

**Text dual:**

```text
{{USERNAME}} ALL=(root) NOPASSWD: {{GLOBAL_BIN}}/{{APP_NAME}} {{ELEV_VERB}}
```

Use `id -un` at runtime for `{{USERNAME}}`. **MUST NOT** freeze a session login in the mold.

### 3.3 Paths

| Kind | Path family |
|------|-------------|
| Installed fragment | `/etc/sudoers.d/{{APP_NAME}}-{{username}}` |
| Draft | `{{HOME}}/.config/{{APP_NAME}}/sudoers.fragment-{{username}}` |
| Local JSON | `{{HOME}}/.config/{{APP_NAME}}/sudoer-request-{{username}}.json` |
| Inbound | sibling dest (typical `/var/sudoer-cli/sudoer-request`) — **MUST** already exist |

Type 0 **MUST NOT** write `/etc`. **MUST NOT** mkdir inbound.

### 3.4 Trust tier

| Tier | Meaning |
|------|---------|
| production | readable+executable `{{GLOBAL_BIN}}/{{APP_NAME}}` |
| test_local | only `{{USER_BIN}}/{{APP_NAME}}` |
| unmanaged | neither |

Non-production emit **MUST** fail closed unless `--allow-test-local` or `ALLOW_TEST_LOCAL_SUDOERS=1`.

### 3.5 Wrap (`util_sudo`)

1. **MUST** keep one wrap. **MUST NOT** scatter raw `sudo`.  
2. Already-root **MUST** run argv without sudo.  
3. Non-root + matching NOPASSWD row **MUST** use `sudo -n` on that **exact** argv.  
4. **MUST NOT** probe `sudo true` / `sudo mkdir` / `sudo cp`.  
5. Allow table **MUST** be studied from `print-sudoers` / installed fragment / `sudo -n -l` — **MUST NOT** guess dest or `verb *`.

### 3.6 Dependency for elev ops

A Type 1 product verb that re-execs this CLI as root (typical `backup-config`) **MUST** compose this mold:

- wrap = `util_sudo` from §4  
- grant args = that verb only  
- operator Next on refuse = `generate-sudoer-request` then `submit-sudoer-request`

**`LM-SHELL-CONFIG-BACKUP`** is the portable elev-ops consumer. **MUST NOT** invent a second sudoer stack there.

## 4. Example implementations (illustration — not product law)

Specialize names (`sshd_*`, product prefix) and `{{ELEV_VERB}}`. Callers use `out_*` from **`LM-OUTPUT-REQUIREMENTS`**.

### 4.1 Variables

```sh
: "${APP_NAME:=app}"
: "${GLOBAL_BIN:=/usr/local/bin}"
: "${USER_BIN:=${HOME}/.local/bin}"
: "${ELEV_VERB:=backup-config}"
: "${SUDOERS_D_DIR:=/etc/sudoers.d}"
: "${ALLOW_TEST_LOCAL_SUDOERS:=0}"
```

### 4.2 Wrap + identity helpers

```sh
util_sudo() {
    if [ "$(id -u 2>/dev/null || echo 1)" -eq 0 ]; then
        "$@"
        return $?
    fi
    command -v sudo >/dev/null 2>&1 || return 1
    sudo -n "$@"
}

util_current_login_user() {
    id -un 2>/dev/null || echo "unknown"
}

util_sudoers_trust_tier() {
    : "${APP_NAME:=app}"
    : "${GLOBAL_BIN:=/usr/local/bin}"
    : "${USER_BIN:=${HOME:-/tmp}/.local/bin}"
    if [ -r "${GLOBAL_BIN}/${APP_NAME}" ] && [ -x "${GLOBAL_BIN}/${APP_NAME}" ]; then
        printf '%s' "production"
        return 0
    fi
    if [ -r "${USER_BIN}/${APP_NAME}" ] && [ -x "${USER_BIN}/${APP_NAME}" ]; then
        printf '%s' "test_local"
        return 0
    fi
    printf '%s' "unmanaged"
}

util_default_installed_sudoers_path() {
    : "${APP_NAME:=app}"
    : "${SUDOERS_D_DIR:=/etc/sudoers.d}"
    printf '%s' "${SUDOERS_D_DIR}/${APP_NAME}-$(util_current_login_user)"
}

util_default_sudoers_draft_path() {
    : "${APP_NAME:=app}"
    : "${HOME:=/tmp}"
    printf '%s' "${HOME}/.config/${APP_NAME}/sudoers.fragment-$(util_current_login_user)"
}

util_default_sudoer_request_path() {
    : "${APP_NAME:=app}"
    : "${HOME:=/tmp}"
    printf '%s' "${HOME}/.config/${APP_NAME}/sudoer-request-$(util_current_login_user).json"
}
```

### 4.3 Emit (fragment + compact JSON)

```sh
util_sudoers_fragment_text() {
    : "${APP_NAME:=app}"
    : "${GLOBAL_BIN:=/usr/local/bin}"
    : "${ELEV_VERB:=backup-config}"
    _user=$(util_current_login_user)
    _tier=$(util_sudoers_trust_tier)
    _bin="${GLOBAL_BIN}/${APP_NAME}"
    _installed=$(util_default_installed_sudoers_path)
    cat <<EOF
# Purpose: Allow ${_user} to run ${APP_NAME} ${ELEV_VERB} as root.
# Grant is the project command only. Does NOT allowlist mkdir/cp/chmod/chown.
# Install: sudo install -m 0440 <this-file> ${_installed}
# Validate: sudo visudo -c -f ${_installed}
# Trust tier: ${_tier}
${_user} ALL=(root) NOPASSWD: ${_bin} ${ELEV_VERB}
EOF
    unset _user _tier _bin _installed
}

util_sudoers_json_text_compact() {
    : "${APP_NAME:=app}"
    : "${GLOBAL_BIN:=/usr/local/bin}"
    : "${ELEV_VERB:=backup-config}"
    : "${SUBMIT_ACTION:=add}"
    _user=$(util_current_login_user)
    _bin="${GLOBAL_BIN}/${APP_NAME}"
    _action="${SUBMIT_ACTION}"
    case "${_action}" in
        add|update) ;;
        *) _action="add" ;;
    esac
    printf '%s' "{\"schema_version\":1,\"purpose\":\"Allow ${_user} to run ${APP_NAME} ${ELEV_VERB} as root.\",\"username\":\"${_user}\",\"service\":\"${APP_NAME}\",\"action\":\"${_action}\",\"commands\":[{\"runas\":\"root\",\"tags\":[\"NOPASSWD\"],\"path\":\"${_bin}\",\"args\":[\"${ELEV_VERB}\"]}]}"
    printf '\n'
    unset _user _bin _action
}

util_sudoers_refuse_forbidden_grant() {
    _gf="${1:-}"
    [ -n "${_gf}" ] && [ -f "${_gf}" ] || { out_die "sudoer grant file missing"; return 1; }
    _gb=$(cat "${_gf}" 2>/dev/null || true)
    case "${_gb}" in
        *"/usr/bin/mkdir"*|*"/bin/mkdir"*|*"/usr/bin/cp"*|*"/bin/cp"*|*"/usr/bin/chmod"*|*"/bin/chmod"*|*"/usr/bin/chown"*|*"/bin/chown"*)
            out_die "refusing sudoer grant with OS-tool commands (need ${GLOBAL_BIN}/${APP_NAME} ${ELEV_VERB} only)"
            ;;
    esac
    unset _gf _gb
}

util_sudoers_verify_grant_verbs() {
    : "${ELEV_VERB:=backup-config}"
    _gf="${1:-}"
    [ -n "${_gf}" ] && [ -f "${_gf}" ] || { out_die "sudoer file missing"; return 1; }
    _gb=$(cat "${_gf}" 2>/dev/null || true)
    case "${_gb}" in
        *'"'"${ELEV_VERB}"'"'*) ;;
        *) out_die "Sudoer file is incomplete: it does not allow ${ELEV_VERB}. Path: ${_gf}" ;;
    esac
    unset _gf _gb
}
```

### 4.4 Routed verbs (sketch)

```sh
cmd_print_sudoers() {
    _tier=$(util_sudoers_trust_tier)
    if [ "${_tier}" != "production" ] && [ "${ALLOW_TEST_LOCAL_SUDOERS:-0}" != "1" ]; then
        out_die "print-sudoers needs a production install (${GLOBAL_BIN}/${APP_NAME}). Next: install globally, or pass --allow-test-local in tests."
    fi
    util_sudoers_fragment_text
}

cmd_generate_sudoer_request() {
    _dest="${1:-$(util_default_sudoer_request_path)}"
    _dir=$(dirname "${_dest}")
    mkdir -p "${_dir}" || out_die "Cannot create ${_dir}"
    util_sudoers_json_text_compact >"${_dest}" || out_die "Cannot write ${_dest}"
    util_sudoers_refuse_forbidden_grant "${_dest}"
    util_sudoers_verify_grant_verbs "${_dest}"
    out_success "Wrote ${_dest}"
}

# submit-sudoer-request: Type 0 copy of the JSON into an *existing* inbound dir.
# MUST NOT mkdir inbound. MUST NOT write /etc.
```

## 5. How to specialize

1. Create `requirement-shell-sudoer` via **`SK-CREATE-SPECIFIC-REQUIREMENT`**.  
2. Fill Implementation Notes: `{{ELEV_VERB}}`, fragment dest, handlers, studied allow table.  
3. Dual-mention verbs on the CLI-interface REQ.  
4. If the product deposits a this-login file, also specialize **`LM-SHELL-CONFIG-BACKUP`** (depends on this file).  
5. Keep **`LM-THREE-LAYER-PRIVILEGE-MODEL`** for Type 0/1/2; **point** sudoer CLI here.  
6. Proof: **`PM-SHELL-SUDOER-TEST-PLAN`**.

## 6. Design-time verification

| Gate | Artifact |
|------|----------|
| Fragment names product command + elev verb only | **TP-SUDOER** / product **TP-CFG-06** |
| JSON `args` is verb-only | **TP-SUDOER** / **TP-CFG-07** |
| OS-tool grant refused | **TP-SUDOER** |
| Termux / Git Bash / Windows cmd hide | **TP-SUDOER** / **TP-CFG-04/05/09** |
| Checklists | **`CL-LEAST-PRIVILEGE`** · **`CL-CREATE-SUDOERS-SECURITY`** · **`CL-SUDOERS-FILE-CONTENT`** |

## Under command line for normal user only

On Termux, Git Bash, Windows cmd, or the same class: Type 1/2 **unused**. These verbs **MUST** fail closed. TTY menu **MUST** omit sudoers rows. **MUST NOT** wrap `sudo` or recommend `sudo curl | sh`.

**This mold:** no JSON grant, no print-sudoers, no `util_sudo` call on that class.

## 7. Protection Rule (Sacred)

Future agents **MUST NOT**:

1. Allowlist `cp` / `mkdir` / `chmod` / `chown` / shells in the grant.  
2. Write `{{ELEV_VERB}} *` when the studied line is verb-only.  
3. Grant Type 0 verbs (`sync-config`).  
4. Write `/etc/sudoers.d` from Type 0.  
5. Mkdir inbound.  
6. Scatter raw `sudo` or probe `sudo true`.  
7. Invent a second wrap inside **`LM-SHELL-CONFIG-BACKUP`**.  
8. Treat this mold as product-source authority.  
9. Strip sample code “for brevity” (agents then reinvent the wheel).  
10. Strip **Under command line for normal user only**.

**Last Updated**: 2026-09-12  
**Owner**: {{OWNER}}  
**Version history:**  
- **1.0.0** (2026-09-12): Shell sudoer features + sample emit/wrap; config-backup depends here.

**Alignment**: **`LM-SUDOER-JSON-FILE`** · **`LM-SHELL-SUDO-COMMAND`** · **`LM-THREE-LAYER-PRIVILEGE-MODEL`** · **`LM-SHELL-CONFIG-BACKUP`** · **`PM-SHELL-SUDOER-TEST-PLAN`** · CIAO / CIAO-Lite.
