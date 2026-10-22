---
name: backup-strategy
id: LM-BACKUP-STRATEGY
kind: law-mold
description: >
  Portable law mold. Cite as LM-BACKUP-STRATEGY (path secondary).
---

**file**: template-backup-strategy.md  
**Status**: Active (Version 2.1.0 – util_backup sibling-.bak example)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered / Over-protect)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

## 1. Purpose

This template defines **CIAO Principle 12 — Right Backup & Restore Strategy** (cloudgen/ciao **v2.10.2**):

> Every irreversible or high-risk state change must have a recovery strategy **proportionate** to the data’s value and replaceability — **not** “run `cp` before every `rm`.”

CIAO is **anti-fragile about durable state**, not pedantic about ephemeral working files. Agents **must not** invent a universal “backup everything” ritual — and **must not** skip recovery for real configuration or user data because a temp file did not need a `.bak`.

**Related:** `template-ciao-principles.md` · `template-defensive-practices.md` · `template-file-modes-umask.md` (secret backup modes) · `template-secret-management.md` · Principle **11** (temps = cleanup, not museum copies).

**Specialize into:** `requirement-*-backup-strategy.md` when product law needs an enforceable matrix.

---

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
| **Temp file system** | `docs/terminologies/temp-file-system.md` | `runtime-mode` | Scratch vs durable backup targets |

**SSOT types used:** `meta-catalog` · `policy` · `runtime-mode`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Classify data before mutate (mandatory)

| Class | Examples | Backup / recovery rule |
|-------|----------|-------------------------|
| **EPHEMERAL** | `mktemp` outputs, download staging, pipe intermediates | **No** dated `.bak`. **Must** clean up (`trap`). Deleting temps is normal. |
| **REGENERABLE** | Installable binary re-fetched from known URL; pure build artifacts with provenance | Dated backup **optional**. **Must** keep provenance (URL, version, checksum). Prefer atomic replace (`write temp → verify → mv`). |
| **CONFIGURATION** | Shell rc PATH blocks, app config, service units, nginx sites | **Must** backup **or** equivalent transactional/rollback **before** modify. Rollback should be testable. |
| **PERSISTENT_USER_DATA** | Project data under `{{APP_DATA_BASE}}`, DBs, cookie stores, user content | **Must** dated backup **before** modify/delete/rename. Preserve structure and protected prefixes. |
| **CREDENTIAL_OR_SECRET** | Tokens, keys, session files, `.env` with secrets | **Must not** casually scatter world-readable `.bak`. Recovery needs **security review** (e.g. `0600`, location, retention). Prefer secret-store restore when applicable. |
| **DESTRUCTIVE_UNINSTALL** | Remove product binary, wipe install tree | **Must** explicit authorization (command / flag / confirmed scope). Reinstallable bits may skip binary `.bak`; user config/data still follow their classes. |

**One-line rule:**  
**Recoverability scaled to risk — hard for config and user data; cleanup for temps; provenance for regenerable installs; caution for secrets.**

---

## 3. When dated file/folder backup is required

### 3.1 File naming

```text
<original-name>.YYYYMMDD-N.bak
```

Example: `default.conf.20260408-1.bak`

Where `YYYYMMDD` = `$(date +%Y%m%d)` and `-N` increments same day.

### 3.2 Folder naming (project data)

```text
{{APP_DATA_BASE}}/{{FULL_PROJECT_NAME}}.YYYYMMDD-N.bak/
```

Preserve original structure **inside** the backup folder. **Never rename** protected prefixes such as `cookies.*`.

### 3.3 Mandatory practices (when backup applies)

1. Never overwrite/delete/rename **CONFIGURATION** or **PERSISTENT_USER_DATA** without a recovery path first.  
2. Protect critical naming patterns (`cookies.*`, cookie storage under resolved app data paths).  
3. Create backup dirs with correct permissions (Principle **10** least-privilege; Principle **22** modes).  
4. **Log** backup/restore via Output SSOT (Principle **5**) when product messaging applies.  
5. Prefer copy-then-modify for in-place config edits.  
6. **Non-interactive:** when backup is required, create it automatically — non-interactive is **not** permission to skip.  
7. **Fail loudly** if a **required** backup cannot be created.  
8. Creating a throwaway `.bak` and immediately deleting it is **not** compliant recovery for durable state.

---

## 4. What this principle is not

- **Not** “backup every temp, every staging `mv`, or every regenerable install artifact.”  
- **Not** a license to skip recovery for shell configs / project data because the script also touches temps.  
- **Not** in conflict with Principle **11**: temps need unpredictable names + cleanup, not dated museum copies.

---

## 5. Specialization sketch

| Project type | Typical required classes | Notes |
|--------------|--------------------------|--------|
| Type 0 shell CLI install tool | CONFIGURATION (PATH blocks); REGENERABLE install bits | Binary reinstall via channel provenance; PATH edits need backup or append-safe policy |
| Platform client with session file | CREDENTIAL_OR_SECRET session | Modes `0600`; never world-readable backups |
| Self-host installer | CONFIGURATION + optional PERSISTENT_USER_DATA volumes | Volume dumps when requested; not default “backup every container layer” |

Fill concrete paths only in Implementation Notes of a specialized **requirement** — keep this template portable (`{{PLACEHOLDER}}`).

---

## 6. CIAO alignment (v2.10.2)

- **Principle 12** — Right Backup & Restore (this template).  
- **Principle 1 – Caution** — Assume mutation can fail mid-flight.  
- **Principle 2 – Intentional** — Document equivalent rollback when not using dated `.bak`.  
- **Principle 3 – Anti-fragile** — Durable state survives user/AI mistakes.  
- **Principle 4 / CIAO-Lite O · Principle 20** — Do not “simplify away” recovery for real config/data.  
- **Principle 5** — Log backup actions via Output SSOT.  
- **Principle 11** — Temps: cleanup, not Principle 12 museum copies.  
- **Principle 22** — Modes on secret backups (prefer `chmod`, not sticky umask).

---

## 7. Protection Rule (Sacred)

**Future AI assistants, Grok, or maintainers MUST NOT**:

1. Require dated `.bak` for every EPHEMERAL temp as “CIAO compliance.”  
2. Skip required backup for CONFIGURATION / PERSISTENT_USER_DATA for “performance” or “simplicity.”  
3. Scatter world-readable secret backups.  
4. Rename protected prefixes (`cookies.*`) during backup/restore.  
5. Treat non-interactive mode as license to skip required recovery.  
6. Hardcode one product’s `~/.app/…` paths as universal law (use `{{PLACEHOLDER}}` / SSOT).  
7. Paste this template into product source as behavioral authority — specialize and cite the live requirement.

---


## Design-time verification

| Gate | Artifact | Phase |
|------|----------|-------|
| Specialize → product suite or checklist | declare TP-IDs or checklist in specialized REQ | Design |
| RTM | `../tests/template-requirement-test-traceability.md` | Design |

When this mold has no executable TP family, mark **n/a** with reason in product `reviews/test-plan.md`.

**Last Updated**: 2026-08-18  
**Owner**: Defensive Core & Resilience Layer (Generalized Template)  
**Version history:**  
- **2.1.0** (2026-08-18): Portable `util_backup` template-example-function (sibling `.YYYYMMDD-N.bak`).  
- **2.0.0** (2026-07-14): Full CIAO v2.10.2 Principle 12 risk-class model; removed “backup every write” over-read.  
- **1.0.0**: Earlier generalized session/config focus.  

**Alignment**: [cloudgen/ciao](https://github.com/cloudgen/ciao) v2.10.2 Principle 12; `template-ciao-principles.md`.

---

## Example `util_backup` (pre-change sibling `.bak`)

This is the **file/folder sibling** helper for CONFIGURATION / PERSISTENT_USER_DATA — **not** a folder-archive `backup`/`restore` verb, **not** for EPHEMERAL temps, **not** for CREDENTIAL_OR_SECRET files (those need a reviewed secret-store path).

```sh
# GENERAL PURPOSE: Dated sibling backup before mutate. Name: <target>.YYYYMMDD-N.bak
# Messages via out_* only. Refuse /, $HOME, empty.
util_backup() {
    : "${APP_NAME:=app}"
    : "${HOME:=/tmp}"
    : "${JSON:=0}"
    : "${QUIET:=0}"

    local target="${1-}"
    local reason="${2:-pre-change}"

    if [ -z "$target" ] || [ "$target" = "/" ] || [ "$target" = "${HOME}" ]; then
        out_warn "Refusing to backup dangerous path: $target"
        return 1
    fi

    local timestamp counter backup_path
    timestamp=$(date +%Y%m%d)
    counter=1
    backup_path="${target}.${timestamp}-${counter}.bak"
    while [ -e "$backup_path" ]; do
        counter=$((counter + 1))
        backup_path="${target}.${timestamp}-${counter}.bak"
    done

    if [ -d "$target" ]; then
        cp -a "$target" "$backup_path" 2>/dev/null && \
            out_info "Backup created: $backup_path (reason: $reason)" || \
            out_warn "Failed to create backup of directory $target"
    elif [ -f "$target" ]; then
        cp "$target" "$backup_path" 2>/dev/null && \
            out_info "Backup created: $backup_path (reason: $reason)" || \
            out_warn "Failed to create backup of file $target"
    fi
}
```

Specialize-out: if the product has no `requirement-*-backup-strategy`, publish this example on the modular REQ. **MUST NOT** use `util_backup` on secret/vault files.
