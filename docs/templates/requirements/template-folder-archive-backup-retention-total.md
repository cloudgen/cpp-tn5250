---
name: folder-archive-backup-retention-total
id: LM-FOLDER-ARCHIVE-BACKUP-RETENTION-TOTAL
kind: law-mold
description: >
  Portable law mold for maximum total durable folder-archive count per project
  basename under the deposit directory. Default cap 30; when exceeded, remove
  oldest archives until count ≤ cap. Cite as LM-FOLDER-ARCHIVE-BACKUP-RETENTION-TOTAL.
---

**file**: template-folder-archive-backup-retention-total.md  
**Status**: Active (Version 1.0.0)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered / Over-protect)

**Folder structure (policy):** law mold under `docs/templates/requirements/`.  
**Specialize into:** `docs/requirements/requirement-folder-archive-backup-retention-total.md` (or project-equivalent).

# =============================================================================
# CIAO DEFENSIVE TEMPLATE — Folder archive backup retention (total cap)
# =============================================================================

# Template: Folder archive backup — total retention cap

## 1. Purpose

This mold defines **operational retention law** for the **maximum number of durable
folder-archive backups kept per project basename** under the product deposit tree.

| Default | Meaning |
|---------|---------|
| **`{{MAX_TOTAL_BACKUPS}}`** | **30** — hard product default unless specialized env/config raises/lowers within documented bounds |

When the count of matching durable archives **exceeds** the cap after a successful
deposit (or when retention is enforced), the product **MUST** remove the **oldest**
archive(s) until the count is **≤ `{{MAX_TOTAL_BACKUPS}}`**.

**Not this mold:**

| Concern | Owner instead |
|---------|----------------|
| Create / name / deposit / verify / restore | **`LM-FOLDER-ARCHIVE-BACKUP`** |
| Max backups **per calendar day** | **`LM-FOLDER-ARCHIVE-BACKUP-RETENTION-DAILY`** |
| Principle 12 pre-mutate `.bak` classes | **`LM-BACKUP-STRATEGY`** |
| Sudoers / elev tables | **`LM-THREE-LAYER-PRIVILEGE-MODEL`** |

## Terminologies

| Term | Path | SSOT type | Role |
|------|------|-----------|------|
| **Docs folder structure** | `docs/terminologies/docs-folder-structure.md` | `policy` | Law vs product paths |
| **No-hardcode policy** | `docs/terminologies/no-hardcode-policy.md` | `policy` | Placeholders in molds |
| **Least privilege** | `docs/terminologies/least-privilege.md` | `policy` | Narrow delete elev only |
| **Ship unit** | `docs/terminologies/ship-unit.md` | `product-law` | CLI under test |

**Peer molds:** **`LM-FOLDER-ARCHIVE-BACKUP`** · **`LM-FOLDER-ARCHIVE-BACKUP-RETENTION-DAILY`** · **`LM-THREE-LAYER-PRIVILEGE-MODEL`**

---

## 2. Core Rules (Mandatory)

### 2.1 Scope of count

1. **MUST** count only durable archives under  
   `{{BACKUP_ROOT}}/{{BACKUP_NOTATION}}/`  
   that match product naming  
   `{{SOURCE_FOLDER_NAME}}-YYYYMMDD-N.{{ARCHIVE_EXT}}`  
   (default ext `tar.gz`) for **one** `{{SOURCE_FOLDER_NAME}}` (project basename).  
2. **MUST NOT** count archives of other basenames toward this project’s total.  
3. **MUST NOT** count stage/temp trees, local hop trees (`.h1-backup-*` / `.h2-backup-*`), or non-product filenames.  
4. Scope **MUST** be **per project basename**, not “all archives of all projects in one global 30” (unless a future specialized law explicitly chooses global scope).

### 2.2 Cap

1. Default **`{{MAX_TOTAL_BACKUPS}}` = 30**.  
2. Product **MAY** allow env override (e.g. `MAX_TOTAL_BACKUPS`) **only** if documented; invalid values **MUST** fail closed or fall back to default.  
3. Cap **MUST** be a positive integer. Cap `0` **MUST NOT** mean “unlimited” without explicit redesign.

### 2.3 When to enforce

1. **MUST** enforce after a **successful durable deposit** of a new archive for that basename (post-verify preferred so a failed backup does not delete older good archives).  
2. **MAY** also enforce on an explicit retention / prune command if the product adds one.  
3. **MUST NOT** delete archives as a substitute for allocate-next-`N` (idempotency peer still forbids overwrite).

### 2.4 What “oldest” means

1. **Oldest** = lowest sort key among matching archives:  
   primary **`YYYYMMDD` ascending**, secondary **`N` ascending**  
   (lexicographic sort of `NAME-YYYYMMDD-N.tar.gz` is acceptable when day is zero-padded `YYYYMMDD` and `N` is compared numerically if widths differ).  
2. **MUST** remove oldest first, one at a time (or batch equivalent), until count ≤ cap.  
3. **MUST NOT** remove the just-deposited archive solely to free a slot if older archives remain — remove **older** ones first.  
4. After prune, count **MUST** be ≤ `{{MAX_TOTAL_BACKUPS}}`.

### 2.5 Delete safety (sacred)

1. **MUST** delete **only** individual matching archive files under the deposit notation dir.  
2. **MUST NOT** `rm -rf` the deposit root, `{{BACKUP_ROOT}}`, `/var`, or any path outside the deposit notation directory.  
3. **MUST NOT** delete unrelated basenames, non-archive files, or paths that fail the naming pattern.  
4. Delete of root-owned deposit files **MUST** use Type 1 **narrow** allowlisted remove (or root) — **not** unrestricted shell. Elev tables **MUST** bound Cmnd to the deposit archive path pattern.  
5. If prune is required and elevation is missing, product **MUST** fail closed with operator hint (print-sudoers / admin) **or** document an honest residual; **MUST NOT** silently leave unbounded growth without reporting.

### 2.6 Interaction with daily retention

1. When both total and daily molds are specialized, **daily prune** (same day) **SHOULD** run before or with total prune so day-local pressure is cleared first; total prune then enforces the global-per-basename cap.  
2. Neither mold **MAY** weaken the other’s hard cap.

### 2.7 Operator visibility

Human mode **SHOULD** report prune actions (basename, files removed, remaining count, cap).  
JSON mode **SHOULD** include fields such as `retention_total_cap`, `retention_total_removed`, `retention_total_remaining` when prune runs.

### 2.8 Implementation Notes (fill when specializing)

| Item | Placeholder / value |
|------|---------------------|
| **Product** | `{{APP_NAME}}` |
| **Deposit** | `{{BACKUP_ROOT}}/{{BACKUP_NOTATION}}/` |
| **Naming** | `{{SOURCE_FOLDER_NAME}}-YYYYMMDD-N.tar.gz` |
| **MAX_TOTAL_BACKUPS** | `30` (default) |
| **Env override** | document or “none” |
| **Prune timing** | after successful deposit + verify |
| **Elev delete** | Table A row / pointer to three-layer |
| **Suite / TP** | declare product TP-IDs |

---

## 3. Design Principles (CIAO / CIAO-Lite)

- **Caution:** Pattern-match before delete; fail closed on path/elev errors.  
- **Intentional:** Cap 30 is product law, not ad-hoc cleanup.  
- **Anti-fragile:** Bounded disk use; oldest discarded first.  
- **Over-protect:** No broad delete elev; no cross-basename prune.

---

## 4. Protection Rule (Sacred)

**MUST NOT**:

1. Leave total count unbounded when this mold is specialized Active.  
2. Delete archives of a **different** `{{SOURCE_FOLDER_NAME}}` to satisfy this cap.  
3. Use retention as an excuse for `rm -rf` deposit or host trees.  
4. Overwrite instead of prune (overwrite ban remains).  
5. Remove newest archive while older ones for the same basename remain.  
6. Hardcode one host’s absolute deposit path into **this mold** (use `{{PLACEHOLDER}}`).  
7. Treat **`LM-BACKUP-STRATEGY`** (pre-mutate `.bak`) as a substitute for this mold.

---

## 5. Acceptance criteria (portable)

| ID | Criterion |
|----|-----------|
| AC-1 | Default total cap is **30** per project basename |
| AC-2 | After deposit, if count > cap, oldest removed until count ≤ cap |
| AC-3 | Other basenames never deleted by this prune |
| AC-4 | Non-matching filenames under deposit not deleted |
| AC-5 | Missing elev for delete fails closed or reports honestly (no silent skip of required prune without signal) |
| AC-6 | Just-deposited archive retained when older archives exist to prune |

---

## Design-time verification

Suggested TP themes: **retention-total-under-cap**, **retention-total-prune-oldest**, **retention-total-no-cross-basename**, **retention-total-no-elev-fail-closed**.

---

**Last Updated**: 2026-08-12  
**Owner**: {{OWNER}}  
**Version history:**  
- **1.0.0** (2026-08-12): Initial total cap mold (default 30; oldest-first prune per basename).

**Alignment**: **`LM-FOLDER-ARCHIVE-BACKUP`** · **`LM-FOLDER-ARCHIVE-BACKUP-RETENTION-DAILY`** · **`LM-THREE-LAYER-PRIVILEGE-MODEL`** · CIAO 1, 10, 12, 20.
