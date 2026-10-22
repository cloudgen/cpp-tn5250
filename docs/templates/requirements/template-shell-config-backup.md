---
name: shell-config-backup
id: LM-SHELL-CONFIG-BACKUP
kind: law-mold
description: >
  Portable law mold for this-login config-file deposit: backup-config (Type 1
  product command via util_sudo), sync-config (Type 0 pull), optional
  sync-from-remote (Type 0 scp). DEPENDS ON LM-SHELL-SUDOER — do not invent a
  second wrap or grant. Cite as LM-SHELL-CONFIG-BACKUP. Sample code lives here.
---

**file**: template-shell-config-backup.md  
**Mold-ID**: LM-SHELL-CONFIG-BACKUP  
**Status**: Active (Version 1.0.0)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered / Over-protect)

**Folder structure (policy):** [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md). This file is a **law mold** under `docs/templates/requirements/`.

# Template: Shell this-login config deposit (`backup-config` / `sync-config`)

## 1. Purpose

Portable law for depositing **one this-login config file** into a host store and copying it back:

| Verb | Privilege | Direction |
|------|-----------|-----------|
| `backup-config` | Type 1 — re-exec `sudo -n {{GLOBAL_BIN}}/{{APP_NAME}} backup-config` | this-login file → host store |
| `sync-config` | Type 0 — **no sudo** | host store → this-login file (mode **600**) |
| `sync-from-remote [SPEC]` | Type 0 `scp` — **no sudo** | remote store → this-login file |

**Not** folder-archive tar.gz (`backup` / `restore` — **`LM-FOLDER-ARCHIVE-BACKUP`**). **Not** a private-key tree copy. **Not** keyword policy for the OpenSSH client file. Unsupported parameters in that file are **`LM-OPENSSH-CLIENT-CONFIG`**.

Specialize into `requirement-shell-config-backup`. **This mold is not product law.**

### 1.1 Dependency on sudoer features (sacred)

`backup-config` **MUST** compose **`LM-SHELL-SUDOER`**:

| Need | Owner |
|------|--------|
| `util_sudo` wrap + `sudo -n` exact argv | **`LM-SHELL-SUDOER`** §3.5 / §4.2 |
| JSON grant `args: ["backup-config"]` | **`LM-SHELL-SUDOER`** §3.2 |
| `print-sudoers` / `generate-sudoer-request` / `submit-sudoer-request` | **`LM-SHELL-SUDOER`** §3.1 |
| Operator Next on refused sudo | generate then submit |

**MUST NOT** invent a second wrap, a second JSON schema, or OS-tool sudoers (`cp`/`mkdir`/`chmod`) “because the copy needs root.” After elev, **this** command copies and chowns internally.

Copy sample code from **`LM-SHELL-SUDOER`** first; then specialize the deposit helpers in §4 here.

## 2. Terminologies

| Term | Path | SSOT type | Role |
|------|------|-----------|------|
| **Sudo-wrapping function** | `docs/terminologies/sudo-wrapping-function.md` | `product-law` | `util_sudo` (owned by **`LM-SHELL-SUDOER`**) |
| **Sudoers exact argv** | `docs/terminologies/sudoers-exact-argv.md` | `product-law` | Verb-only grant |
| **Command line for normal user only** | `docs/terminologies/command-line-for-normal-user-only.md` | `product-law` | Deposit unused on Termux / Git Bash / Windows cmd |
| **Least privilege** | `docs/terminologies/least-privilege.md` | `policy` | Product command only |
| **Template example function** | `docs/terminologies/template-example-function.md` | `mention-only` | Sample bodies below |
| **SSOT catalog** | `docs/terminologies/ssot-catalog.md` | `meta-catalog` | Inventory |

**SSOT types used:** `product-law` · `policy` · `mention-only` · `meta-catalog`

**Policies:** `docs/policies/policy-least-privilege.md` · `docs/policies/policy-no-hardcode.md` · **`PO-NON-EXPOSE-LOCAL-MACHINE`**

**Missing terms:** none

## 3. Core rules (portable)

### 3.1 Source and dest

| Slot | Typical family (specialize) |
|------|-----------------------------|
| Source | this-login file, e.g. `{{HOME}}/.ssh/config` |
| Store dir | `/var/{{APP_NAME}}` (override `{{CONFIG_ROOT}}` in tests) |
| Store leaf | `{{CONFIG_ROOT}}/config` |
| Sync dest | same this-login path; mode **600** |

1. When euid is 0 via sudo, invoking home **MUST** be `SUDO_USER`’s passwd home (not `/root`) unless tests set an explicit root home.  
2. **MUST NOT** copy private keys, `id_*`, or a whole `~/.ssh` tree.  
3. Missing source **MUST** fail closed with Next: create the file, then `backup-config`.  
4. Re-run **MUST** overwrite the same basename (idempotent snapshot, no dated tar).

### 3.2 `backup-config` (elevated deposit)

1. On Termux / Git Bash / Windows cmd **MUST** fail closed. Next: POSIX Linux host.  
2. Writing the production dest as non-root **MUST** re-exec `sudo -n {{GLOBAL_BIN}}/{{APP_NAME}} backup-config` through `util_sudo` from **`LM-SHELL-SUDOER`**.  
3. Refused sudo **MUST** fail closed. Next: `{{APP_NAME}} generate-sudoer-request && {{APP_NAME}} submit-sudoer-request`.  
4. As root: `mkdir` dest if needed, copy, `chown root:root`, file mode **0644**, dest dir **0755** (so Type 0 `sync-config` can read without sudo).  
5. A writable `{{CONFIG_ROOT}}` **outside** the production dest **MAY** accept Type 0 deposit for tests. Production dest **MUST NOT** skip elev because it happens to be writable.

### 3.3 `sync-config` (no sudo)

1. **MUST NOT** call `sudo`. **MUST NOT** appear in the sudoers grant.  
2. Fail closed if the store is missing or unreadable. Next: someone with the approved grant must `backup-config` first.  
3. Create dest dir if needed (typical mode **700**). Dest file mode **600**.

### 3.4 `sync-from-remote [SPEC]` (no sudo)

1. Type 0 `scp` BatchMode. **MUST** be available on Termux / Git Bash / Windows cmd.  
2. SPEC: `user@host`, host, IPv4, or `user@domain`. Off-TTY missing SPEC fail-closed. On TTY, `read` in the current shell (**MUST NOT** `_spec=$(prompt_ask …)`).  
3. Preferred SPEC in durable persistence (`{{HOME}}/.local/{{APP_NAME}}/preferred-remote`, mode **600**) — **MUST NOT** store on `/dev/shm`.  
4. **MUST NOT** open a real SSH session in Core tests (fake `{{SCP}}`).

### 3.5 Invocation samples

```text
{{APP_NAME}} backup-config
{{APP_NAME}} sync-config
{{APP_NAME}} sync-from-remote user@host.example.test
{{APP_NAME}} generate-sudoer-request
{{APP_NAME}} submit-sudoer-request
```

The last two are **sudoer** verbs — owned by **`LM-SHELL-SUDOER`**, listed here so operators see the dependency.

## 4. Example implementations (illustration — not product law)

Copy `util_sudo` from **`LM-SHELL-SUDOER`**. Specialize `{{CONFIG_SRC}}` / `{{CONFIG_ROOT}}`.

```sh
: "${APP_NAME:=app}"
: "${GLOBAL_BIN:=/usr/local/bin}"
: "${CONFIG_ROOT:=/var/${APP_NAME}}"
: "${ELEV_VERB:=backup-config}"

util_invoking_home() {
    if [ "$(id -u 2>/dev/null || echo 1)" -eq 0 ] && [ -n "${SUDO_USER:-}" ] && [ "${SUDO_USER}" != "root" ]; then
        _h=""
        if command -v getent >/dev/null 2>&1; then
            _h=$(getent passwd "${SUDO_USER}" 2>/dev/null | cut -d: -f6)
        fi
        if [ -z "${_h}" ] && [ -r /etc/passwd ]; then
            _h=$(awk -F: -v u="${SUDO_USER}" '$1==u {print $6; exit}' /etc/passwd 2>/dev/null)
        fi
        if [ -n "${_h}" ] && [ -d "${_h}" ]; then
            printf '%s' "${_h}"
            unset _h
            return 0
        fi
        unset _h
    fi
    printf '%s' "${HOME:-/tmp}"
}

util_config_src() {
    printf '%s' "$(util_invoking_home)/.ssh/config"
}

util_config_root() {
    : "${CONFIG_ROOT:=/var/${APP_NAME}}"
    printf '%s' "${CONFIG_ROOT}"
}

util_dest_needs_elev() {
    _d="${1:-}"
    : "${_d:=/var/${APP_NAME}}"
    if [ "$(id -u 2>/dev/null || echo 1)" -eq 0 ]; then
        unset _d
        return 1
    fi
    case "${_d}" in
        /var/${APP_NAME}|/var/${APP_NAME}/*)
            unset _d
            return 0
            ;;
    esac
    if [ -d "${_d}" ] && [ -w "${_d}" ]; then
        unset _d
        return 1
    fi
    if mkdir -p "${_d}" 2>/dev/null && [ -w "${_d}" ]; then
        unset _d
        return 1
    fi
    unset _d
    return 0
}

cmd_backup_config() {
    : "${APP_NAME:=app}"
    : "${GLOBAL_BIN:=/usr/local/bin}"
    # refuse Termux / Git Bash / Windows cmd first (product detect helpers)
    _src=$(util_config_src)
    _dest=$(util_config_root)
    if [ ! -f "${_src}" ]; then
        out_die "Cannot backup-config: missing ${_src}. Next: create this login's config, then ${APP_NAME} backup-config."
    fi
    if [ "$(id -u 2>/dev/null || echo 1)" -ne 0 ] && util_dest_needs_elev "${_dest}"; then
        _bin="${GLOBAL_BIN}/${APP_NAME}"
        [ -x "${_bin}" ] || out_die "Need global binary ${_bin}. Next: install globally, then ${APP_NAME} generate-sudoer-request && ${APP_NAME} submit-sudoer-request."
        out_info "Elevating: sudo -n ${_bin} backup-config"
        util_sudo "${_bin}" backup-config || out_die "sudo ${APP_NAME} backup-config was refused. Next: ${APP_NAME} generate-sudoer-request && ${APP_NAME} submit-sudoer-request."
        return 0
    fi
    mkdir -p "${_dest}" || out_die "Cannot create ${_dest}"
    _outp="${_dest}/config"
    if command -v install >/dev/null 2>&1; then
        install -m 0644 "${_src}" "${_outp}" || out_die "Failed to copy ${_src}"
    else
        cp "${_src}" "${_outp}" || out_die "Failed to copy ${_src}"
        chmod 0644 "${_outp}" 2>/dev/null || true
    fi
    if [ "$(id -u 2>/dev/null || echo 1)" -eq 0 ]; then
        chown root:root "${_outp}" "${_dest}" 2>/dev/null || true
        chmod 0644 "${_outp}" 2>/dev/null || true
        chmod 0755 "${_dest}" 2>/dev/null || true
    fi
    out_success "backup-config complete: ${_src} → ${_outp}"
}

cmd_sync_config() {
    : "${HOME:=/tmp}"
    _src="$(util_config_root)/config"
    _destdir="${HOME}/.ssh"
    _dest="${_destdir}/config"
    [ -f "${_src}" ] || out_die "Cannot sync-config: store missing (${_src}). Next: someone with approved sudo ${APP_NAME} backup-config must push first."
    [ -r "${_src}" ] || out_die "Cannot read ${_src} without sudo."
    mkdir -p "${_destdir}" || out_die "Cannot create ${_destdir}"
    chmod 0700 "${_destdir}" 2>/dev/null || true
    if command -v install >/dev/null 2>&1; then
        install -m 0600 "${_src}" "${_dest}" || out_die "Failed to write ${_dest}"
    else
        cp "${_src}" "${_dest}" || out_die "Failed to write ${_dest}"
        chmod 0600 "${_dest}" 2>/dev/null || true
    fi
    out_success "sync-config complete: ${_src} → ${_dest} (mode 600)"
}
```

`sync-from-remote`: Type 0 `scp -o BatchMode=yes` of `{{user}}@{{host}}:{{CONFIG_ROOT}}/config` into this-login dest mode 600. Fake `{{SCP}}` in CI. Preferred SPEC leaf: `{{HOME}}/.local/{{APP_NAME}}/preferred-remote`.

## 5. How to specialize

1. Specialize **`LM-SHELL-SUDOER`** in the **same change** (or confirm it is already Active).  
2. Create `requirement-shell-config-backup`. Fill source/dest families.  
3. Dual-mention `backup-config` / `sync-config` / `sync-from-remote` on the CLI-interface REQ.  
4. Domain REQ **points** (does not re-own copy semantics).  
5. Proof: **`PM-SHELL-CONFIG-BACKUP-TEST-PLAN`** (**TP-CFG**).

## 6. Design-time verification

| Gate | Artifact |
|------|----------|
| Deposit into test root | **TP-CFG-01** |
| Sync dest mode 600 | **TP-CFG-02** |
| Missing source fail-closed | **TP-CFG-03** |
| Termux / Git Bash / Windows cmd hide deposit | **TP-CFG-04/05/09** |
| `restore-config` unknown | **TP-CFG-08** |
| Grant / JSON | **`PM-SHELL-SUDOER-TEST-PLAN`** / **TP-CFG-06/07** |
| Remote pull | **TP-CFG-10..16** |

## Under command line for normal user only

On Termux / Git Bash / Windows cmd: **MUST NOT** deposit or wrap `sudo`. Direct `backup-config` / local `sync-config` **MUST** fail closed. Menu **MUST** print INFO and omit those rows **and** sudoers. **`sync-from-remote` remains available** (Type 0 `scp`).

**This mold:** host deposit is POSIX Linux; remote pull is this-login `scp` on every class.

## 7. Protection Rule (Sacred)

Future agents **MUST NOT**:

1. Tar a whole key directory or copy `id_*`.  
2. Name the pull verb `restore` / `restore-config`.  
3. Grant `cp`/`mkdir`/`chmod` in sudoers.  
4. Enable **deposit** on Termux / Git Bash / Windows cmd.  
5. Use `/root/…` when `SUDO_USER` is set.  
6. Hide `sync-from-remote` because Termux/Git Bash was detected.  
7. `_spec=$(prompt_ask …)` (do-not-capture-read).  
8. Store preferred-remote on `/dev/shm`.  
9. Invent a second `util_sudo` or JSON grant — compose **`LM-SHELL-SUDOER`**.  
10. Strip sample code “for brevity.”  
11. Treat this mold as product-source authority.

**Last Updated**: 2026-09-12  
**Owner**: {{OWNER}}  
**Version history:**  
- **1.0.0** (2026-09-12): Portable backup-config / sync-config; depends on **`LM-SHELL-SUDOER`**; sample deposit helpers.

**Alignment**: **`LM-SHELL-SUDOER`** · **`LM-SHELL-SUDO-COMMAND`** · **`PM-SHELL-CONFIG-BACKUP-TEST-PLAN`** · CIAO / CIAO-Lite.
