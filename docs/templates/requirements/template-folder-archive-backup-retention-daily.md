---
name: folder-archive-backup-retention-daily
id: LM-FOLDER-ARCHIVE-BACKUP-RETENTION-DAILY
kind: law-mold
description: >
  Portable law mold for maximum durable folder-archive count per project basename
  per calendar day. Default cap 5; when exceeded, remove oldest archive of the
  current day until count ≤ cap. Cite as LM-FOLDER-ARCHIVE-BACKUP-RETENTION-DAILY.
---

**file**: template-folder-archive-backup-retention-daily.md  
**Status**: Active (Version 1.0.0)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered / Over-protect)

**Folder structure (policy):** law mold under `docs/templates/requirements/`.  
**Specialize into:** `docs/requirements/requirement-folder-archive-backup-retention-daily.md` (or project-equivalent).

# =============================================================================
# CIAO DEFENSIVE TEMPLATE — Folder archive backup retention (daily cap)
# =============================================================================

# Template: Folder archive backup — daily retention cap

## 1. Purpose

This mold defines **operational retention law** for the **maximum number of durable
folder-archive backups kept for one project basename on one calendar day**.

| Default | Meaning |
|---------|---------|
| **`{{MAX_DAILY_BACKUPS}}`** | **5** — hard product default unless specialized env/config documents otherwise |

When the count of matching durable archives for **`{{SOURCE_FOLDER_NAME}}` + `YYYYMMDD`**
**exceeds** the cap, the product **MUST** remove the **oldest backup of that same day**
until the day count is **≤ `{{MAX_DAILY_BACKUPS}}`**.

**Not this mold:**

| Concern | Owner instead |
|---------|----------------|
| Create / name / deposit / verify / restore | **`LM-FOLDER-ARCHIVE-BACKUP`** |
| Max **total** archives across days | **`LM-FOLDER-ARCHIVE-BACKUP-RETENTION-TOTAL`** |
| Principle 12 pre-mutate `.bak` | **`LM-BACKUP-STRATEGY`** |
| Next-`N` no-overwrite allocate | Shell idempotency / folder-archive naming law |

## Terminologies

| Term | Path | SSOT type | Role |
|------|------|-----------|------|
| **Docs folder structure** | `docs/terminologies/docs-folder-structure.md` | `policy` | Law vs product paths |
| **No-hardcode policy** | `docs/terminologies/no-hardcode-policy.md` | `policy` | Placeholders in molds |
| **Least privilege** | `docs/terminologies/least-privilege.md` | `policy` | Narrow delete elev only |

**Peer molds:** **`LM-FOLDER-ARCHIVE-BACKUP`** · **`LM-FOLDER-ARCHIVE-BACKUP-RETENTION-TOTAL`** · **`LM-THREE-LAYER-PRIVILEGE-MODEL`**

---

## 2. Core Rules (Mandatory)

### 2.1 Scope of count (day bucket)

1. **MUST** count only durable archives under  
   `{{BACKUP_ROOT}}/{{BACKUP_NOTATION}}/`  
   matching  
   `{{SOURCE_FOLDER_NAME}}-{{YYYYMMDD}}-N.{{ARCHIVE_EXT}}`  
   for **one** basename and **one** calendar day `{{YYYYMMDD}}`  
   (local date at backup start, same SSOT as naming).  
2. **MUST NOT** count other days’ archives toward the daily cap.  
3. **MUST NOT** count other basenames.  
4. **MUST NOT** count stage/temp or non-product filenames.

### 2.2 Cap

1. Default **`{{MAX_DAILY_BACKUPS}}` = 5**.  
2. Product **MAY** allow env override (e.g. `MAX_DAILY_BACKUPS`) only if documented; invalid values fail closed or fall back to default.  
3. Cap **MUST** be a positive integer. Cap `0` **MUST NOT** mean unlimited without redesign.

### 2.3 When to enforce

1. **MUST** enforce after a **successful durable deposit** for that basename on that day (post-verify preferred).  
2. Applies when next free `N` would create (or has created) more than cap archives for that basename+day.  
3. **MUST NOT** overwrite an existing `N` to “stay under 5” — allocate next `N` then prune oldest of **that day**.

### 2.4 What “oldest of current day” means

1. Within the same `{{SOURCE_FOLDER_NAME}}` and same `YYYYMMDD`, **oldest** = lowest **`N`** (or earliest mtime only if `N` unavailable — prefer `N`).  
2. **MUST** remove only archives in **that day’s** set.  
3. **MUST NOT** remove a previous day’s archive to satisfy the **daily** cap.  
4. **MUST NOT** remove the newest of the day while lower-`N` archives of the same day remain.  
5. After prune, day count **MUST** be ≤ `{{MAX_DAILY_BACKUPS}}`.

### 2.5 Delete safety (sacred)

Same bounds as total retention:

1. Delete only matching individual archive files under deposit notation.  
2. **MUST NOT** `rm -rf` deposit/host roots.  
3. **MUST NOT** cross basename or non-pattern files.  
4. Root-owned deposit delete **MUST** use Type 1 **narrow** allowlisted remove (or root).  
5. Missing elev: fail closed with operator hint **or** honest residual signal — no silent unbounded day growth without report.

### 2.6 Interaction with total retention

1. Daily prune **SHOULD** run **before** total prune when both are Active.  
2. Daily cap **MUST NOT** raise the total cap; total cap **MUST NOT** allow more than daily cap on a single day.

### 2.7 Operator visibility

Human mode **SHOULD** report day prune (basename, day, files removed, remaining day count, cap).  
JSON **SHOULD** include e.g. `retention_daily_cap`, `retention_daily_day`, `retention_daily_removed`, `retention_daily_remaining`.

### 2.8 Implementation Notes (fill when specializing)

| Item | Placeholder / value |
|------|---------------------|
| **Product** | `{{APP_NAME}}` |
| **Deposit** | `{{BACKUP_ROOT}}/{{BACKUP_NOTATION}}/` |
| **Naming** | `{{SOURCE_FOLDER_NAME}}-YYYYMMDD-N.tar.gz` |
| **MAX_DAILY_BACKUPS** | `5` (default) |
| **Day SSOT** | local `date +%Y%m%d` at backup start |
| **Prune timing** | after successful deposit + verify |
| **Elev delete** | Table A row / three-layer pointer |
| **Suite / TP** | declare product TP-IDs |

---

## 3. Design Principles (CIAO / CIAO-Lite)

- **Caution:** Day-scoped match only; fail closed on path/elev errors.  
- **Intentional:** Cap 5/day is product law.  
- **Anti-fragile:** Same-day thrash does not fill the deposit.  
- **Over-protect:** Never delete other days under “daily” rule; no broad elev.

---

## 4. Protection Rule (Sacred)

**MUST NOT**:

1. Leave same-day count unbounded when this mold is specialized Active.  
2. Delete **other days’** archives to satisfy the **daily** cap.  
3. Delete other basenames or non-product files.  
4. Overwrite same-day `N` instead of prune.  
5. Remove highest-`N` (newest) of the day while lower-`N` same-day archives remain.  
6. Hardcode one host deposit path into **this mold**.  
7. Confuse daily cap with total cap (**`LM-FOLDER-ARCHIVE-BACKUP-RETENTION-TOTAL`**).

---

## 5. Acceptance criteria (portable)

| ID | Criterion |
|----|-----------|
| AC-1 | Default daily cap is **5** per basename per `YYYYMMDD` |
| AC-2 | When same-day count > cap, oldest same-day (lowest `N`) removed until ≤ cap |
| AC-3 | Other days’ archives not removed by daily prune |
| AC-4 | Other basenames not removed |
| AC-5 | Missing elev for delete fails closed or reports honestly |
| AC-6 | Newest same-day archive retained when older same-day `N` exist |

---

## Design-time verification

Suggested TP themes: **retention-daily-under-cap**, **retention-daily-prune-lowest-N**, **retention-daily-no-other-day**, **retention-daily-no-cross-basename**.

---

**Last Updated**: 2026-08-12  
**Owner**: {{OWNER}}  
**Version history:**  
- **1.0.0** (2026-08-12): Initial daily cap mold (default 5; oldest same-day `N` first).

**Alignment**: **`LM-FOLDER-ARCHIVE-BACKUP`** · **`LM-FOLDER-ARCHIVE-BACKUP-RETENTION-TOTAL`** · **`LM-THREE-LAYER-PRIVILEGE-MODEL`** · CIAO 1, 10, 12, 20.
