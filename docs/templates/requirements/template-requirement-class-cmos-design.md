---
name: requirement-class-cmos-design
id: LM-REQUIREMENT-CLASS-CMOS-DESIGN
kind: law-mold
description: >
  Portable law mold. Cite as LM-REQUIREMENT-CLASS-CMOS-DESIGN (path secondary).
---

**file**: template-requirement-class-cmos-design.md  
**Status**: Active (Version 1.0.0 – CMOS-design class law + residual process/EDA/deliverable collection)  
**Project**: Any CIAO-Lite CMOS-design workspace (reusable template — **no project brand**)  
**Philosophy**: CIAO **v2.10.2** / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered / Over-protect)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

# =============================================================================
# Template: requirement-class-cmos-design
# Specialize to: docs/requirements/requirement-class-cmos-design.md
# No-hardcode: use {{PLACEHOLDER}} only — never freeze a product name as universal law
# =============================================================================


## Design-time verification

| Gate | Artifact | Phase |
|------|----------|-------|
| Specialize → product suite or checklist | declare TP-IDs or checklist in specialized REQ | Design |
| RTM | `../tests/template-requirement-test-traceability.md` | Design |

When this mold has no executable TP family, mark **n/a** with reason in product `reviews/test-plan.md`.

## How to use this template (authoring only — do not paste this section into claimed-done project law)

1. Confirm project nature is **cmos-design** (not genesis-template; not software-development; not server-maintenance).  
2. Copy/specialize to **`docs/requirements/requirement-class-cmos-design.md`** only.  
3. Fill **Implementation Notes** with *this* project’s real non-secret design/process facts (no-placeholder when Status is approved/done).  
4. Keep **core rules** portable: process families, EDA tool **classes**, and deliverable classes as choice models — not one foundry hostname as universal law.  
5. **Residual collection rule:** put here only facts **not already owned** by a more specific Active `requirement-*.md`. When a dedicated requirement later owns a topic, **move** detail there and leave a short pointer (own-or-point).  
6. Register the specialized file in `docs/requirements/index.md` (Area **`class`**).  
7. **Content hygiene for versioned requirements:** specialized requirement bodies must not list harness paths (`docs/templates/**`, skills, terminologies, …) when git is used.  
8. **Git is not mandatory** for this class — do not invent remotes, Stars badges, or precommit theater.  
9. **Do not** invent process node / PDK / EDA pins — collect or leave honest not-yet-collected.

**Target basename (fixed):** `requirement-class-cmos-design.md`  
**Genesis:** do **not** create this file (or any `requirement-*.md`) in genesis-template.  
**Not the software-dev residual template:** do **not** use language/compiler residual tables as this class’s primary residual.  
**Not the server-maintenance residual template:** do **not** use OS/libc/allowlist residual as this class’s primary residual.

---

# Requirement: class-cmos-design

**Status:** {{STATUS}}  
**Area:** class  
**Key:** `requirement-class-cmos-design`  
**Updated:** {{YYYY-MM-DD}}

## 1. Purpose

Declare this workspace as a **CMOS-design** project class and hold the **general residual collection** of silicon-design facts that are **not yet (or not better) recorded** in more specific requirements: **design deliverable class**, **process / line-width / PDK family**, **EDA tool class**, and domain-track intent defaults.

This file is **class law + residual SSOT**, not a second copy of domain feature catalogs, full PDK ensure tables, or software-development ship/git SSOTs.

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
| **CMOS-design project** | `docs/terminologies/cmos-design-project.md` | `product-law` | Class #6 |
| **Project class** | `docs/terminologies/project-class.md` | `product-law` | Eleven-class model (internal name) |
| **Project nature** | `docs/terminologies/project-nature.md` | `product-law` | Daily-life name for **project class** (alias stub) |
| **Good IC design** | `docs/terminologies/good-ic-design.md` | `product-law` | Quality vocabulary (not the class) |
| **Project requirements** | `docs/terminologies/project-requirements.md` | `product-law` | Residual REQs |

**SSOT types used:** `meta-catalog` · `policy` · `product-law`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Core Rules (Mandatory — portable)

### 2.0 Project class membership

1. **MUST** treat this workspace as **cmos-design** (silicon / circuit design specialization), not genesis-template, not software-development, and not server-maintenance.  
2. **MUST** use basename **`requirement-class-cmos-design.md`** as the sole Active class-law file for this class.  
3. **MUST NOT** register an Active `requirement-class-software-dev.md` or `requirement-class-server-maintenance.md` while class is cmos-design.  
4. **MUST** retain portable harness knowledge; specialized design knowledge lives in this and peer `requirement-*.md` files.  
5. **MUST NOT** require software-development-only SSOTs for class completeness (README identity triad, Stars, ship unit, online-install channel, precommit READY, companion digest as class requirements).  
6. **MUST** keep **git surface optional** — not a class membership or review-pass gate.  
7. **MUST NOT** invent hollow product docs solely to look specialized.  
8. **MUST NOT** collapse this class into “software-development + domain track” when the primary promise is IC design.

### 2.1 Residual collection principle (SSOT hygiene)

9. **MUST** treat this file as the **default home** for CMOS design residual facts **not owned** by another Active requirement.  
10. **MUST NOT** duplicate full normative tables that already live in a more specific Active requirement. Prefer a **one-line pointer** to the peer requirement key.  
11. When a new specialized requirement **takes ownership** of a topic previously only listed here, **MUST** update this file in the **same change**.  
12. **MUST NOT** leave contradictory design/process facts across this file and peer requirements.

### 2.2 Design deliverable class

13. **MUST** declare the primary design deliverable class as a closed choice set when known (examples of *classes*, not universal hardcode): schematic, netlist, layout, GDS/streamout, verification suite, multi-deliverable tree.  
14. **SHOULD** declare secondary deliverables only when they are real project law.  
15. **MUST NOT** invent deliverable claims; until collected, Implementation Notes **MUST** record honest **not-yet-collected** with owner.

### 2.3 Process, line-width, and PDK family

16. **MUST** declare intended process / line-width family and PDK family as choice sets when known (or point to peer process/PDK requirement).  
17. **MUST** state version/pin policy as one of: unconstrained | minimum | range | pinned | peer-owned.  
18. **MUST NOT** invent foundry, PDK, or node pins without evidence.

### 2.4 EDA and host tool class

19. **MUST** declare the primary EDA / design-tool class when known (open-flow class, commercial suite class, mixed, or document-only).  
20. **SHOULD** record design-host OS family expectation as a choice set (not a single frozen hostname).  
21. **MUST NOT** freeze one vendor tool name as the only possible universe in core rules.

### 2.5 Domain track and feature law fence

22. **MUST** place domain feature law (cells, calibration, programmability, verification claims) in a dedicated Active `requirement-domain-*` when domain surface is claimed — not as a second residual dump here.  
23. **MUST** keep domain track ids separate from project class: tracks are specialty content; class remains **cmos-design**.  
24. **MUST NOT** claim absolute “glitch-free” or “zero-jitter” silicon without measurement evidence.

### 2.6 Git surface (optional, not mandated)

25. **MUST NOT** require git repository initialization, remote publish, Stars/repository badge, companion channel URL, or precommit/file-leaks **gates** for class membership or class acceptance.  
26. **MAY** adopt git later by explicit owner decision; only then **SHOULD** apply precommit / file-leaks hygiene to the versioned surface.  
27. **MUST NOT** invent hollow git remotes, fake repository URLs, or toy hostnames.  
28. **MUST** keep secrets out of the tree whether or not git is used.

### 2.7 No-hardcode / dual policy

29. **MUST NOT** hard-code a single product brand, production hostname, or personal owner identity as universal core law.  
30. **MUST** put live product name and concrete pins in **Implementation Notes** after collection — complete, not unfinished markers, when Status claims approved or done.  
31. **MUST NOT** store secrets, PATs, or toy credentials in this file.

### 2.1 Implementation Notes (this project)

| Field | Value |
|-------|--------|
| **Project display name** | {{PROJECT_DISPLAY_NAME}} |
| **Project short description** | {{PROJECT_SHORT_DESCRIPTION}} |
| **Project class** | cmos-design |
| **Class requirement basename** | `requirement-class-cmos-design.md` |
| **Domain product intent** | {{DOMAIN_PRODUCT_INTENT}} |
| **Domain track family (intent)** | {{DOMAIN_TRACK_FAMILY}} |
| **Primary design deliverable class** | {{DELIVERABLE_CLASS}} |
| **Process / line-width family** | {{PROCESS_FAMILY}} |
| **PDK family** | {{PDK_FAMILY}} |
| **Process/PDK version policy** | {{PROCESS_VERSION_POLICY}} |
| **Primary EDA / tool class** | {{EDA_TOOL_CLASS}} |
| **Design host OS family** | {{HOST_OS_FAMILY}} |
| **Topics owned here (residual)** | {{RESIDUAL_OWNED}} |
| **Topics pointed elsewhere** | {{RESIDUAL_POINTED}} |
| **Git surface** | **Not mandated** — optional only |
| **Software ship unit / install** | not class-default — {{SHIP_UNIT_NOTE}} |

**Residual ownership table:**

| Topic | Owner | Notes |
|-------|--------|------|
| Project class membership | **this file** | Fixed cmos-design |
| Design deliverable / process / EDA residual | **this file** until dedicated REQ owns them | Honest not-yet-collected until elicitation |
| Domain features | peer `requirement-domain-*` when present | Create after class gate |
| Process / PDK ensure depth | peer process/PDK REQ when present | Optional |
| Git surface / precommit / repository publish | **optional — not mandated** | No class gate on git |
| Software-dev ship/git SSOTs | **out of scope by default** | Wrong class unless owner reclassifies or adds explicit software law |
| Server-maintenance allowlist | **out of scope** | Wrong class |

## 3. Why This Requirement Exists (Direct CIAO Alignment)

- **CIAO Principle 2 – Intentional**: Class and design residual are explicit — not assumed from folder basename or domain track alone.  
- **CIAO Principle 5 – SSOT**: Residual design facts have one home until specialized requirements take ownership.  
- **CIAO Principle 1 – Caution**: Process, PDK, and EDA facts are not invented; not-yet-collected is honest.  
- **CIAO Principle 21 / dual policies**: Portable core; filled Implementation Notes for known facts; no brand/host/secret hardcode in core.

## 4. Design Principles (CIAO / CIAO-Lite)

- **Caution**: Assume process, PDK, and tool pins are missing until declared.  
- **Intentional**: Leave genesis only with declared cmos-design class + product intent; domain law follows separately; git is owner-optional.  
- **Anti-fragile**: Choice sets survive multi-tool EDA environments without requiring a remote.  
- **Over-protect**: Protection rule blocks dual class files, forced software-dev gates, and forced git theater.

## 5. Protection Rule (Sacred)

**Future AI assistants, Grok, or maintainers MUST NOT**:

- Treat this workspace as genesis-template while this Active class file remains registered.  
- Rename the specialized basename away from `requirement-class-cmos-design.md` without an explicit class-model change.  
- Reclassify to software-development solely because automation scripts or circuit tooling appear.  
- **Fail review, block specialize, or invent remotes/URLs solely because git surface is absent.**  
- Treat precommit / Stars / repository URL as **mandatory** class gates.  
- Hard-code one product’s host/secret into core rules as universal law.  
- Duplicate full peer requirement bodies into this residual section.  
- Leave Implementation Notes as hollow unfinished content when Status claims **approved** or **done** (draft may keep explicit not-yet-collected rows; “git not mandated” is complete content).  
- Invent process, PDK, or absolute glitch/jitter guarantees without evidence.  
- Treat this file as server-maintenance allowlist law or software-dev ship law.  
- Create non-class requirements without this class file remaining Active and registered.

**Violating any of these is considered a critical regression.**

## 6. Acceptance criteria

| ID | Criterion |
|----|-----------|
| AC-1 | Active registered `requirement-class-cmos-design.md` matches cmos-design class |
| AC-2 | Product display name and domain product intent recorded in Implementation Notes |
| AC-3 | Residual ownership table honest: no silent dual SSOT with peer REQs |
| AC-4 | Core rules free of frozen product host/secret hardcodes |
| AC-5 | No class file conflict with software-dev or server-maintenance class files |
| AC-6 | Residual fields either filled with real facts or explicit not-yet-collected (draft OK) |
| AC-7 | Domain feature law is not claimed complete solely by this class file |
| AC-8 | Git surface recorded as **not mandated**; missing git is not a class acceptance failure |

## 7. Related requirements (versioned surface only)

| Artifact | Role |
|----------|------|
| `docs/requirements/index.md` | Registry SSOT |
| Peer `docs/requirements/requirement-domain-*.md` | Domain product law when created |
| Peer process/PDK requirement keys when created | Process ensure depth |

## 8. Status history

| Date | Status | Note |
|------|--------|------|
| {{YYYY-MM-DD}} | {{STATUS}} | {{STATUS_NOTE}} |

## 9. Design-time verification

| TP family / ID | Planned proof |
|----------------|---------------|
| Class membership (manual) | Registry + this file present; no software-dev or server-maint class Active |
| Git optional (manual) | Class Pass without `.git`; no forced repository URL in Implementation Notes |
| Domain claims | Peer domain REQ + review/test plan when domain surface is specialized |

**Last Updated**: {{YYYY-MM-DD}}  
**Owner**: {{OWNER}}  
**Alignment**: Registry `docs/requirements/index.md`; **CIAO** (https://github.com/cloudgen/ciao); CIAO-Lite (https://github.com/cloudgen/ciao-lite).
