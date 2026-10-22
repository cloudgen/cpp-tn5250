---
name: folder-archive-backup
id: LM-FOLDER-ARCHIVE-BACKUP
kind: law-mold
description: >
  Portable law mold for folder archive backup: stage tar.gz, durable Type 1 deposit,
  verify, elev Tables A/B/C skeleton, fail-closed matrix. Not domain four-pillar.
  Cite as LM-FOLDER-ARCHIVE-BACKUP (path secondary).
---

**file**: template-folder-archive-backup.md  
**Status**: Active (Version 1.3.0 – Table A is project command only; OS-tool elev withdrawn)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered / Over-protect)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

# =============================================================================
# CIAO DEFENSIVE TEMPLATE - Folder Archive Backup (operational law)
# =============================================================================
#
# Specialize into: docs/requirements/requirement-folder-archive-backup.md
# (or project-equivalent basename). Area is backup/ops — NOT domain.
# Domain four-pillar surface stays in requirement-domain-* when present.
# Use {{PLACEHOLDER}} only in this mold.
# =============================================================================

# Template: Folder archive backup

## 1. Purpose

This mold defines **operational law** for backing up a **folder tree** into a **gzip tar** archive, depositing it to a **durable host path**, and **verifying** inventory (counts) and size before success.

It is **not**:

| Not this mold | Owner instead |
|---------------|---------------|
| Domain four pillars (verbs/help/about catalog) | Domain requirements mold / `requirement-domain-*` |
| Principle 12 risk-class “backup before mutate” matrix | **`LM-BACKUP-STRATEGY`** |
| Sudoers fragment file workflow | **`LM-THREE-LAYER-PRIVILEGE-MODEL`** |
| CLI install lifecycle | Shell self-management molds |

## Terminologies

Related glossary entries (**disk-truth**). Templates **point**; they do not redefine terms or act as product law.  
SSOT types follow `docs/policies/policy-ssot-terminology-for-templates.md`.  
Binding rules: `docs/policies/policy-terminology-for-templates.md`.

| Term | Path | SSOT type | Role |
|------|------|-----------|------|
| **Project templates** | `docs/terminologies/project-templates.md` | `meta-catalog` | What law molds are |
| **Docs folder structure** | `docs/terminologies/docs-folder-structure.md` | `policy` | Law vs product paths |
| **No-hardcode policy** | `docs/terminologies/no-hardcode-policy.md` | `policy` | Placeholders in molds |
| **Dual policies** | `docs/terminologies/dual-policies.md` | `policy` | Balance with no-placeholder |
| **Terminology policy for templates** | `docs/terminologies/terminology-policy-for-templates.md` | `policy` | Terminologies section rules |
| **SSOT-terminology policy for templates** | `docs/terminologies/ssot-terminology-policy-for-templates.md` | `policy` | SSOT type column |
| **Three-layer privilege** | `docs/terminologies/three-layer-privilege.md` | `product-law` | Type 0 create / Type 1 deposit |
| **Sudoers fragment** | `docs/terminologies/sudoers-fragment.md` | `product-law` | Elev allowlist files |
| **Ship unit** | `docs/terminologies/ship-unit.md` | `product-law` | Product CLI under test |
| **Least privilege** | `docs/terminologies/least-privilege.md` | `policy` | Narrow elevation |
| **Temp file system** | `docs/terminologies/temp-file-system.md` | `runtime-mode` | Staging vs durable |

**SSOT types used:** `meta-catalog` · `policy` · `product-law` · `runtime-mode`

**Policies:** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-no-hardcode.md` · `docs/policies/policy-least-privilege.md` · terminology/SSOT template policies

**Peer molds:** **`LM-BACKUP-STRATEGY`** (when to backup) · **`LM-THREE-LAYER-PRIVILEGE-MODEL`** (how to elevate) · **`LM-FOLDER-ARCHIVE-BACKUP-RETENTION-TOTAL`** (max total archives) · **`LM-FOLDER-ARCHIVE-BACKUP-RETENTION-DAILY`** (max per day) · shell storage / CLI interface molds when specializing CLI products

---

## 2. Core Rules / Requirements (Mandatory)

### 2.1 Scope and non-goals

| In scope | Out of scope (unless separate law) |
|----------|-------------------------------------|
| One-shot folder → tar.gz → durable deposit → verify | Scheduler/daemon |
| Local create as invoking user | Cloud upload |
| Non-overwriting dated names | Full restore UI |
| Count/size verification | Disk imaging |
| Fail-closed matrix | Silent partial success |
| Restore dest **whitelist** (incl. `/etc/{{username}}`; never `/etc/passwd`) | Blanket allow of all `/etc/*`; unrestricted extract to OS roots |

### 2.2 Source validation

1. **MUST** require a non-empty source operand.  
2. **MUST** resolve to a readable **directory**.  
3. **MUST** fail closed if missing, not a directory, unreadable, or unresolvable.  
4. **MUST NOT** treat a lone regular file as folder backup without redesign.

### 2.3 Archive create (Type 0)

1. **MUST** create gzip tar (`tar -czf` or equivalent).  
2. **MUST** run create as **invoking user**.  
3. **MUST** stage under product effective storage — not unprivileged write into durable root.  
4. **MUST** use a stage path shape compatible with elevation allowlists when Type 1 deposit is used.  
5. **MUST** fail closed if tar/compression missing or fails.  
6. **SHOULD** archive so top-level entry is the folder basename.  
7. **MUST** clean stage on success/failure (trap or equivalent).

### 2.4 Archive naming

```text
{{SOURCE_FOLDER_NAME}}-YYYYMMDD-N.tar.gz
```

| Token | Meaning |
|-------|---------|
| `{{SOURCE_FOLDER_NAME}}` | Path-safe basename |
| `YYYYMMDD` | Local date at start |
| `N` | Next free positive integer for basename+day under deposit dir |

1. **MUST NOT** overwrite existing durable name.  
2. **MUST** allocate next free `N`.  
3. Basename single segment only; reject empty/`.`/`..`.

### 2.5 Durable deposit

| Concept | Placeholder |
|---------|-------------|
| Durable root | `{{BACKUP_ROOT}}` |
| Notation / product subdir | `{{BACKUP_NOTATION}}` |
| Deposit directory | `{{BACKUP_ROOT}}/{{BACKUP_NOTATION}}/` |
| Final path | `…/{{SOURCE_FOLDER_NAME}}-YYYYMMDD-N.tar.gz` |

1. Root-owned durable trees **MUST** deposit via Type 1 elevation (`LM-THREE-LAYER-PRIVILEGE-MODEL` when specialized).  
2. **MUST NOT** claim success if durable file missing.  
3. Deposit failure **MUST** fail closed.  
4. Destination **MUST** stay bound to `{{BACKUP_ROOT}}/{{BACKUP_NOTATION}}/` (no broad write).

### 2.6 Verification (mandatory)

| Metric | Definition |
|--------|------------|
| Source entries | `find` count including root |
| Source files | `find -type f` |
| Archive members | `tar -tzf` lines |
| Archive files | members not ending in `/` |
| Size | byte length of archive file |

| Stage | Checks | Fail-closed |
|-------|--------|-------------|
| **A Stage** | members==entries; files==source files; size>0 | **Yes** |
| **B Deposit** | dest exists; size==stage | **Yes** |
| **C Re-list** | when possible, members/files match stage | **Yes** if listed; see below if not |

**Re-list rules:**

1. May use Type 1 allowlisted `tar -tzf` under deposit dir only (no extract).  
2. If re-list unavailable → success only if A+B passed; human output must note limitation.  
3. If re-list available → mismatch **MUST** fail closed.  
4. Never set verified success if A or B failed.

Human success **MUST** report destination, `source_files`, archive files/members, size, and `verify_mode`.

### 2.7 JSON contract (when product claims JSON)

**SHOULD** include: `source`, `archive_name`, `destination`, `source_entries`, `source_files`, `archive_members`, `archive_files`, `archive_size`, `verified`, `verify_mode`.  
Errors **MUST** use stable codes when feasible (`source_invalid`, `tar_failed`, `deposit_failed`, `verify_failed`, …).

### 2.8 Failure matrix (minimum)

| Condition | Expected |
|-----------|----------|
| No / bad source | Non-zero |
| tar missing/fail | Non-zero |
| Stage verify mismatch | Non-zero |
| Deposit fail / unauthorized | Non-zero + operator hint |
| Dest missing / size mismatch | Non-zero |
| Re-list mismatch when listed | Non-zero |

### 2.8a Type 1 elev allowlist (mandatory when deposit uses sudo)

When durable deposit is Type 1, specialized law **MUST** include elev **Tables A/B/C** per **`LM-THREE-LAYER-PRIVILEGE-MODEL`** §2.2a — either **filled here** or by **single-SSOT pointer** to specialized `requirement-three-layer-privilege-model` (no dual conflicting tables).

**Portable Table A skeleton** (replace `{{…}}` on specialize). Grant is the **managed project command** only — **not** OS-tool `mkdir`/`cp`/`tar`/`rm`:

| ID | Job | Binary (absolute) | Fixed args | Source | Dest | Invoker CLI | NOPASSWD? |
|----|-----|-------------------|------------|--------|------|-------------|-----------|
| ELEV-01 | Backup (stage + deposit + verify) | `{{GLOBAL_BIN}}/{{APP_NAME}}` | `{{BACKUP_CMD}}` | `{{SOURCE_FOLDER}}` | `{{BACKUP_ROOT}}/{{BACKUP_NOTATION}}/` (in-tool) | `{{BACKUP_CMD}}` | yes |
| ELEV-02 | Restore (deposit → dest host) | `{{GLOBAL_BIN}}/{{APP_NAME}}` | `{{RESTORE_CMD}}` | archive under deposit | dest host (product whitelist) | `{{RESTORE_CMD}}` | yes |

**Table B (minimum — specialize):** no OS-tool Cmnds (`mkdir`, `cp`, `tar`, `rm`, `install`, `chmod`); no `rm`/destroy elev; no bare shell; no `ALL`/`NOPASSWD: ALL`.

**Table C:** After elev, the ship unit **MAY** mkdir/copy/tar/rm **internally** ([`elev-is-approval`](../../terminologies/elev-is-approval.md)). Those live tools are **not** a second sudoers catalog. Expand Table A requires security review + admin fragment **before** code; `print-sudoers` ⊆ Table A.

### 2.8b Restore destination whitelist (mandatory when product has restore)

When specialized law includes **`{{RESTORE_CMD}}`**, dest gate **MUST** be **whitelist-oriented** for FHS system prefixes (not a pure “ban all under `/etc`” with no home exception).

**Hard deny (never whitelist):**

| Class | Paths |
|-------|--------|
| Exact OS roots | `/`, `/bin`, `/boot`, `/dev`, `/etc`, `/lib`, `/lib64`, `/proc`, `/root`, `/run`, `/sbin`, `/sys`, `/usr`, `/var` (exact) |
| **`/etc/passwd`** | Always refuse — system account database |
| Deposit tree | `{{BACKUP_ROOT}}`, `{{BACKUP_ROOT}}/{{BACKUP_NOTATION}}`, and under deposit notation |

**Whitelist rows (specialize placeholders):**

| ID | Allowed destination |
|----|---------------------|
| **W-DISK** | Under `{{PROJECTS_ROOT}}/…` (hard-disk host SSOT) |
| **W-RAM** | Under `{{RAM_ROOT}}/…` when ram-drive host |
| **W-ETC-USER** | **`/etc/{{username}}`** or strict child — `{{username}}` = invoking `id -un` only; **never** `/etc/passwd`; **never** `/etc/<other-user>` |
| **W-HOME** | Invoking passwd home (`getent`) or strict child when not already covered by W-ETC-USER |
| **W-TMP / stage** | Product temp/stage trees when used as explicit dest |
| **W-OTHER** | Only via future mold/REQ revision |

**`/etc` rules (portable):**

1. Exact `/etc` refuse.  
2. **`/etc/passwd` refuse always.**  
3. Default refuse under `/etc/…`.  
4. **W-ETC-USER only:** allow `/etc/{{username}}` (+ children) for **invoking** user.  
5. Hard deny evaluated **before** W-* rows.  
6. Type 1 elev **MUST NOT** mean extract-as-root into `/etc`.

### 2.9 Implementation Notes (fill when specializing)

| Item | Placeholder / value |
|------|---------------------|
| **Product** | `{{APP_NAME}}` |
| **Backup command** | `{{BACKUP_CMD}}` (e.g. `backup`) |
| **Restore command** | `{{RESTORE_CMD}}` (e.g. `restore`) |
| **BACKUP_ROOT** | `{{BACKUP_ROOT}}` |
| **BACKUP_NOTATION** | `{{BACKUP_NOTATION}}` |
| **Stage roots** | `{{STAGE_ROOT_PATTERN}}` |
| **User stage** | `{{USER_STAGE}}` (e.g. `/dev/shm/{{APP_NAME}}-{{USER}}`) |
| **Elev-table SSOT** | this file **or** pointer to three-layer REQ (one owner) |
| **Tables A/B/C** | filled rows (or explicit pointer) |
| **Ship unit** | `{{SHIP_UNIT}}` |
| **Suite / TP family** | declare product TP-IDs |
| **Verify modes** | list implemented modes |

---

## 3. Design Principles (CIAO / CIAO-Lite)

- **Caution:** Validate, verify, fail loud.  
- **Intentional:** Separate domain surface from operational backup law; elev Tables A/B/C explicit.  
- **Anti-fragile:** Stage then deposit; elev only Table A durable write/list/restore-stage.  
- **Over-protect:** Mandatory stage verify + size match; closed elev set (anti agent jailbreak); restore dest whitelist is `/etc/{{username}}` only under `/etc` — never `/etc/passwd` or all of `/etc/*`.  
- **Anti-fragile (restore):** Trees at `/etc/{{username}}` remain recoverable for the invoking owner via **W-ETC-USER**.

---

## 4. Protection Rule (Sacred)

**MUST NOT**:

1. Overwrite same-day archives by default.  
2. Skip stage or size verification for convenience.  
3. Claim success on failed deposit/verify.  
4. Extract during verify.  
5. Put full operational backup law only inside domain four-pillar files.  
6. Hardcode one product’s host paths into **this mold** (use `{{PLACEHOLDER}}`).  
7. Treat **`LM-BACKUP-STRATEGY`** as a substitute for this mold (different concern).  
8. Claim Type 1 deposit done without elev **Tables A/B/C** (or single-SSOT pointer).  
9. Allow ship unit elev outside Table A (agent jailbreak residual power).  
10. Specialize restore dest as pure ban on all `/etc/*` without **W-ETC-USER**.  
11. Whitelist all of `/etc` or `/etc/*`, or allow restore into **`/etc/passwd`**.

---

## 5. Acceptance criteria (portable)

| ID | Criterion |
|----|-----------|
| AC-1 | Source validation fail-closed |
| AC-2 | User-privilege tar.gz stage create |
| AC-3 | Non-overwriting `NAME-YYYYMMDD-N.tar.gz` |
| AC-4 | Deposit under `{{BACKUP_ROOT}}/{{BACKUP_NOTATION}}/` |
| AC-5 | Stage count verify vs source |
| AC-6 | Dest size matches stage |
| AC-7 | Human reports counts + size + mode |
| AC-8 | JSON verify fields when JSON claimed |
| AC-9 | Next-N same day |
| AC-10 | Unauthorized deposit fail-closed |
| AC-11 | Type 1 deposit: elev Tables A/B/C complete (or single-SSOT pointer); ship elev ⊆ Table A |
| AC-12 | Restore dest gate is whitelist-oriented (§2.8b); exact `/etc` and other hard-deny roots refuse |
| AC-13 | **W-ETC-USER:** `/etc/{{username}}` or strict child for invoking user allowed by dest gate |
| AC-14 | Dest **`/etc/passwd` always refuses**; `/etc/<other-user>` refuses for a different invoker |

---

## Design-time verification

| Gate | Artifact |
|------|----------|
| Specialize → suite | Product TP-IDs for source fail, naming, fail-closed deposit, elev success+verify, next-N, elev closed-set, restore dest whitelist |
| RTM | `../tests/template-requirement-test-traceability.md` |
| Product map | `reviews/test-plan.md` (`todo` → `have`) |
| Elev law | Tables A/B/C here **or** three-layer SSOT pointer; print-sudoers ⊆ Table A |
| Restore dest | W-ETC-USER + hard deny `/etc/passwd` (e.g. product **TP-*-16**) |

Suggested TP themes: **source-invalid**, **tar-name**, **deposit-fail-closed**, **elev-deposit-verify**, **elev-closed-set**, **next-N**, **leaf-basename**, **restore-w-etc-user**, **restore-refuse-etc-passwd**.

---

## How to use this template

1. Specialize into `docs/requirements/requirement-folder-archive-backup.md` (Area **backup** / ops — **not** domain).  
2. Keep domain four pillars in `requirement-domain-*` as **surface only**; point behavior here.  
3. Fill Implementation Notes with real paths/users (no bare `{{…}}` when claiming done).  
4. Fill elev **Tables A/B/C** here **or** point to specialized **`LM-THREE-LAYER-PRIVILEGE-MODEL`** peer as single SSOT.  
5. Register `docs/requirements/index.md` and map TPs in product reviews/tests.

---

**Last Updated**: 2026-08-21  
**Owner**: {{OWNER}}  
**Version history:**  
- **1.3.0** (2026-08-21): §2.8a Table A = `{{GLOBAL_BIN}}/{{APP_NAME}}` `{{BACKUP_CMD}}`/`{{RESTORE_CMD}}`; withdraw OS-tool `mkdir`/`cp`/`tar` elev rows.  
- **1.2.0** (2026-08-12): §2.8b restore dest **whitelist**; **W-ETC-USER** `/etc/{{username}}`; hard deny **`/etc/passwd`**; AC-12..14; Protection Rule 10–11.  
- **1.1.0** (2026-08-07): Elev Tables A/B/C skeleton aligned to **`LM-THREE-LAYER-PRIVILEGE-MODEL`** §2.2a; elev-table SSOT; AC-11; closed elev set.  
- **1.0.0** (2026-08-03): Initial operational folder-archive backup mold (create, name, deposit, verify); explicit non-domain scope.

**Alignment**: **`LM-BACKUP-STRATEGY`** (peer, different concern) · **`LM-THREE-LAYER-PRIVILEGE-MODEL`** · CIAO Principles 1, 5, 9, 10, 11, 12, 20 (v2.10.2).
