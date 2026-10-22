---
name: class-accounting-management
id: LM-REQUIREMENT-CLASS-ACCOUNTING-MANAGEMENT
kind: law-mold
description: >
  Portable law mold. Cite as LM-REQUIREMENT-CLASS-ACCOUNTING-MANAGEMENT (path secondary).
---

**file**: template-requirement-class-accounting-management.md  
**Status**: Active (Version 1.0.0 – class law + residual collection)  
**Project**: Any CIAO-Lite accounting-management workspace (reusable template — **no project brand**)  
**Philosophy**: CIAO **v2.10.2** / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered / Over-protect)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

# =============================================================================
# Template: requirement-class-accounting-management
# Specialize to: docs/requirements/requirement-class-accounting-management.md
# No-hardcode: use {{PLACEHOLDER}} only — never freeze a product name as universal law
# =============================================================================

## Design-time verification

| Gate | Artifact | Phase |
|------|----------|-------|
| Specialize → product suite or checklist | declare TP-IDs or checklist in specialized REQ | Design |
| RTM | `../tests/template-requirement-test-traceability.md` | Design |

When this mold has no executable TP family, mark **n/a** with reason in product `reviews/test-plan.md`.

## How to use this template (authoring only — do not paste this section into claimed-done project law)

1. Confirm project nature is **accounting-management** (not genesis-template; not a peer class).  
2. Copy/specialize to **`docs/requirements/requirement-class-accounting-management.md`** only.  
3. Fill **Implementation Notes** with *this* project’s real non-secret residual facts (no-placeholder when Status is approved/done).  
4. Keep **core rules** portable: residual as choice models — not one brand/host as universal law.  
5. **Residual collection rule:** put here only facts **not already owned** by a more specific Active `requirement-*.md`.  
6. Register the specialized file in `docs/requirements/index.md` (Area **`class`**).  
7. **Content hygiene for versioned requirements:** specialized requirement bodies must not list harness paths when git is used.  
8. **Git is not mandatory** for this class — do not invent remotes, Stars badges, or precommit theater.  
9. **Do not** invent residual pins — collect or leave honest not-yet-collected.

**Target basename (fixed):** `requirement-class-accounting-management.md`  
**Genesis:** do **not** create this file (or any `requirement-*.md`) in genesis-template.  
**Not software-dev residual:** do **not** use language/compiler residual as primary.  
**Not server-maintenance residual:** do **not** use OS/libc/allowlist residual as primary.  
**Not cmos-design residual:** do **not** use PDK/foundry residual as primary unless this class truly owns silicon work (it does not).

---

# Requirement: class-accounting-management

**Status:** {{STATUS}}  
**Area:** class  
**Key:** `requirement-class-accounting-management`  
**Updated:** {{YYYY-MM-DD}}

## 1. Purpose

Declare this workspace as a **accounting-management** project class and hold the **general residual collection** of facts that are **not yet (or not better) recorded** in more specific requirements: books scope · standards family · fiscal calendar · tool class.

This file is **class law + residual SSOT**, not a second copy of peer catalogs or software-development ship/git SSOTs.

## Terminologies

Related glossary entries (**disk-truth**). Templates **point**; they do not redefine terms or act as product law.
SSOT types follow `docs/policies/policy-ssot-terminology-for-templates.md`.
Binding rules: `docs/policies/policy-terminology-for-templates.md`.

| Term | Path | SSOT type | Role |
|------|------|-----------|------|
| **Project templates** | `docs/terminologies/project-templates.md` | `meta-catalog` | What law molds are |
| **Docs folder structure** | `docs/terminologies/docs-folder-structure.md` | `policy` | Where this mold lives |
| **No-hardcode policy** | `docs/terminologies/no-hardcode-policy.md` | `policy` | Placeholders only in portable molds |
| **Dual policies** | `docs/terminologies/dual-policies.md` | `policy` | No-placeholder × no-hardcode balance |
| **Accounting-management project** | `docs/terminologies/accounting-management-project.md` | `product-law` | Class #10 |
| **Project class** | `docs/terminologies/project-class.md` | `product-law` | Eleven-class model (internal name) |
| **Project nature** | `docs/terminologies/project-nature.md` | `product-law` | Daily-life name for **project class** (alias stub) |
| **Project requirements** | `docs/terminologies/project-requirements.md` | `product-law` | Residual REQs |

**SSOT types used:** `meta-catalog` · `policy` · `product-law`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Core Rules (Mandatory — portable)

### 2.0 Project class membership

1. **MUST** treat this workspace as **accounting-management**, not genesis-template and not a peer class with a different residual catalog.  
2. **MUST** use basename **`requirement-class-accounting-management.md`** as the sole Active class-law file for this class.  
3. **MUST NOT** register a conflicting Active `requirement-class-*.md` for another class while this class is Active.  
4. **MUST** retain portable harness knowledge; specialized knowledge lives in this and peer `requirement-*.md` files.  
5. **MUST NOT** require software-development-only SSOTs for class completeness (README identity triad, Stars, ship unit, online-install channel, precommit READY as class requirements).  
6. **MUST** keep **git surface optional** — not a class membership or review-pass gate.  
7. **MUST NOT** invent hollow product docs solely to look specialized.  
8. **MUST NOT** collapse this class into “software-development + domain track” when the primary promise is this class’s residual.

### 2.1 Residual collection principle (SSOT hygiene)

9. **MUST** treat this file as the **default home** for residual facts **not owned** by another Active requirement.  
10. **MUST NOT** duplicate full normative tables that already live in a more specific Active requirement. Prefer a **one-line pointer** to the peer requirement key.  
11. When a new specialized requirement **takes ownership** of a topic previously only listed here, **MUST** update this file in the **same change**.  
12. **MUST NOT** leave contradictory residual facts across this file and peer requirements.

### 2.2 Class residual topics

13. **MUST** declare residual topic as choice sets when known, or honest not-yet-collected: **books / ledger scope class**.
14. **MUST** declare residual topic as choice sets when known, or honest not-yet-collected: **standards family (choice set)**.
15. **MUST** declare residual topic as choice sets when known, or honest not-yet-collected: **fiscal calendar class**.
16. **MUST** declare residual topic as choice sets when known, or honest not-yet-collected: **accounting tool class**.
17. **MUST** declare residual topic as choice sets when known, or honest not-yet-collected: **entity / consolidation scope**.

### 2.3 Secrets and honesty

20. **MUST NOT** store credentials, account numbers, private personal data, or live secrets in this file.  
21. **MUST** use stay-honest residual claims — no absolute unmeasured guarantees as universal law.

## 3. Implementation Notes (this project — fill on specialize)

| Field | Value |
|-------|-------|
| Display name | {{PROJECT_DISPLAY_NAME}} or not-yet-collected |
| Residual summary | books scope · standards family · fiscal calendar · tool class: … |
| Not-yet-collected | list + owner |
| Git surface | optional (state used / not used) |

## 4. Residual ownership table

| Topic | Owner |
|-------|-------|
| Class membership | **this file** |
| Residual topics listed above | **this file** until peer owns |
| Feature / domain law | peer `requirement-*` keys when present |

## 5. Acceptance criteria

- [ ] Class membership declared as **accounting-management**  
- [ ] Basename is `requirement-class-accounting-management.md`  
- [ ] Residual topics collected or honest not-yet-collected  
- [ ] No secrets  
- [ ] Registry row Area `class` present  
- [ ] Git optional posture respected  

## 6. Related (peer keys only when specialized)

List peer requirement keys only — never harness path inventories.

---

**Last Updated**: 2026-08-03  
**Owner**: {{OWNER}}  
**Alignment**: project-class · accounting-management-project · skill-create-class-requirement · dual-policies · no-hardcode · docs-folder-structure
