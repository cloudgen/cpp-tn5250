---
name: cmos-design
id: LM-CMOS-DESIGN
kind: law-mold
description: >
  Portable law mold for CMOS circuit/layout design practice under CMOS-design
  (and tools that generate CMOS). Cite as LM-CMOS-DESIGN (path secondary).
---

**file**: template-cmos-design.md  
**Status**: Active (Version 1.0.0 – CMOS design practice law)  
**Project**: Any CIAO-Lite **cmos-design** (or circuit-tooling) workspace — reusable template; **no product brand**  
**Philosophy**: CIAO **v2.10.2** / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered / Over-protect)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

# =============================================================================
# Template: cmos-design
# Specialize to: docs/requirements/requirement-cmos-design.md
# No-hardcode: use {{PLACEHOLDER}} only — never freeze a foundry brand as universal law
# =============================================================================

## Design-time verification

| Gate | Artifact | Phase |
|------|----------|-------|
| Specialize → product suite or checklist | declare TP-IDs or checklist in specialized REQ | Design |
| RTM | `../tests/template-requirement-test-traceability.md` | Design |

When this mold has no executable TP family, mark **n/a** with reason in product `reviews/test-plan.md` (when used).

## How to use this template (authoring only — do not paste this section into claimed-done project law)

1. Confirm project nature is **cmos-design** (or owner explicitly applies CMOS law under another class).  
2. Ensure Active **`requirement-class-cmos-design.md`** (or matching class file) before non-class REQs.  
3. Specialize to **`docs/requirements/requirement-cmos-design.md`**.  
4. Fill **Implementation Notes** with *this* project’s process family, deliverable class, and critical-path rules (no-placeholder when approved/done).  
5. **Own-or-point:** do not duplicate full domain feature catalogs or full PDK ensure tables—point to peer REQs.  
6. Register in `docs/requirements/index.md` (Area **`design`** recommended).  
7. Versioned requirements surface: specialized bodies must not list harness paths (`docs/templates/**`, skills, terminologies, …).  
8. **Git not mandated** for cmos-design class completeness.

**Target basename (recommended):** `requirement-cmos-design.md`  
**Key:** `requirement-cmos-design`  
**Optional RQ-ID:** `RQ-CMOS-DESIGN` (project-local only)

---

# Requirement: cmos-design

**Status:** {{STATUS}}  
**Area:** design  
**Key:** `requirement-cmos-design`  
**Updated:** {{YYYY-MM-DD}}

## 1. Purpose

Define enforceable **CMOS design** law for this workspace: complementary MOS circuit and layout practices that produce **usable delayed edges** and **glitch-aware select/combine logic**, without claiming absolute glitch-free silicon and without absorbing PDK-install or domain-feature catalogs owned by peer requirements.

## Terminologies

Related glossary entries (**disk-truth**). Templates **point**; they do not redefine terms or act as product law.
SSOT types follow `docs/policies/policy-ssot-terminology-for-templates.md`.
Binding rules: `docs/policies/policy-terminology-for-templates.md`.

| Term | Path | SSOT type | Role |
|------|------|-----------|------|
| **CMOS design** | `docs/terminologies/cmos-design.md` | `product-law` | Primary vocabulary |
| **Good IC design** | `docs/terminologies/good-ic-design.md` | `product-law` | Quality parent |
| **Gate-glitch rule** | `docs/terminologies/gate-glitch-rule.md` | `product-law` | AND/OR/XOR hazard |
| **Glitchless mux design** | `docs/terminologies/glitchless-mux-design.md` | `product-law` | MUX select/combine |
| **Signal glitch** | `docs/terminologies/signal-glitch.md` | `product-law` | False-pulse symptom |
| **Multi-leg gate** | `docs/terminologies/multi-leg-gate.md` | `product-law` | Layout multiplicity |
| **Delay cell** | `docs/terminologies/delay-cell.md` | `product-law` | Delay unit |
| **Target line width** | `docs/terminologies/target-line-width.md` | `product-law` | Process size vocabulary |
| **CMOS-design project** | `docs/terminologies/cmos-design-project.md` | `product-law` | Typical host class |
| **Project class** | `docs/terminologies/project-class.md` | `product-law` | Eleven-class model (internal name) |
| **Project nature** | `docs/terminologies/project-nature.md` | `product-law` | Daily-life name for **project class** (alias stub) |
| **Project templates** | `docs/terminologies/project-templates.md` | `meta-catalog` | Law molds |
| **Docs folder structure** | `docs/terminologies/docs-folder-structure.md` | `policy` | Placement |
| **No-hardcode policy** | `docs/terminologies/no-hardcode-policy.md` | `policy` | Placeholders in molds |
| **Dual policies** | `docs/terminologies/dual-policies.md` | `policy` | Completeness balance |

**SSOT types used:** `product-law` · `meta-catalog` · `policy`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Core Rules (Mandatory — portable)

### 2.0 Scope and ownership

1. **MUST** treat this file as the **default home** for CMOS circuit/layout practice law **not owned** by a more specific Active peer requirement.  
2. **MUST NOT** re-own full domain product feature catalogs (calibration, programmability pillars)—point to peer `requirement-domain-*` when present.  
3. **MUST NOT** re-own full PDK ensure / package install strategies—point to peer process/PDK requirement when present.  
4. **MUST** keep **git surface optional** when class is cmos-design (absence of git is not a CMOS law failure).  
5. When a peer takes ownership of a residual topic, **MUST** update residual ownership in the same change.

### 2.1 Technology style

6. **MUST** declare the primary implementation style as **CMOS** (complementary nMOS + pMOS networks) for digital control, select, and delay-fabric logic in scope.  
7. **MUST** prefer **static CMOS** for glitch-critical digital control and select logic unless a peer requirement documents a different style with hazard analysis.  
8. **MUST NOT** invent foundry, PDK, or node pins in core rules—use choice sets; pins live in Implementation Notes or peer process REQs.  
9. **SHOULD** declare intended process / line-width family as a choice set when known (or point to peer).

### 2.2 Critical-path logic topology

10. **MUST** apply **glitch-critical path** discipline: prefer AND-class structure; treat OR/XOR as glitch-prone on delayed-edge select/combine (domain gate-glitch rule).  
11. **MUST** apply **glitchless mux design** intent for delay-select and edge-combine MUXes on critical paths.  
12. **MUST NOT** claim absolute “glitch-free” or “zero-jitter” silicon without measurement or simulation evidence recorded in Implementation Notes or peer verification law.  
13. **MUST NOT** use “glitter” in published design law or user-facing claims.

### 2.3 Delay fabric and devices

14. **MUST** treat delay cells / edge drivers as first-class CMOS blocks when the product is a delay line (or point to peer domain law for cell catalog).  
15. **SHOULD** use multi-leg / matching layout practices where delay matching is product law.  
16. **MUST** treat **NMOS as faster** and **PMOS as slower** at comparable geometry (electron vs hole mobility).  
17. When combining NMOS and PMOS on glitch/jitter-critical paths, **SHOULD delay the NMOS connection** by extending the link with **serpentine lines**.  
18. **SHOULD** strengthen/widen **PMOS** as complementary compensation; serpentine-delay on NMOS and widen-PMOS **MAY** combine.  
19. **MUST** separate **logic topology** decisions from **place-and-route** ownership: PnR does not rewrite Boolean hazard rules; serpentine lines are intentional match delay.

### 2.4 Supplies, wells, and integrity (portable minimum)

17. **MUST** declare intended supply domain count as a choice set when known (single digital rail vs multi-rail).  
18. **MUST** keep substrate/well connectivity intentional (no floating wells as accidental default on critical fabric).  
19. **SHOULD** record ESD / pad strategy as residual or peer when I/O is in scope.  
20. **MUST NOT** store secrets or private process recipes in this file.

### 2.5 Verification and claim bar

21. **MUST** list verification classes claimed (schematic review, LVS, DRC, timing/edge simulation, silicon measure)—each **in-scope / out-of-scope / not-yet-collected**.  
22. **MUST** fail closed on marketing overclaim: intent language only without evidence.  
23. **SHOULD** name critical nets/edges for review when Implementation Notes are complete enough.

### 2.6 No-hardcode / dual policy

24. **MUST NOT** hard-code a single product brand, host path, or secret as universal core law.  
25. **MUST** put live product name, process pins, and tool pins in **Implementation Notes** when collected.  
26. Draft status **MAY** keep honest **not-yet-collected** rows; approved/done **MUST NOT** leave hollow unfinished markers for claimed surfaces.

### 2.1 Implementation Notes (this project)

| Field | Value |
|-------|--------|
| **Project display name** | {{PROJECT_DISPLAY_NAME}} |
| **Primary style** | CMOS (complementary) |
| **Static CMOS preference** | {{STATIC_CMOS_POLICY}} |
| **Process / line-width family** | {{PROCESS_FAMILY}} |
| **PDK family** | {{PDK_FAMILY}} — or peer-owned |
| **Critical paths** | {{CRITICAL_PATHS}} |
| **MUX / select policy** | glitchless mux design intent on critical paths |
| **Gate-glitch policy** | AND prefer; OR/XOR avoid on critical select/combine |
| **Delay cell / multi-leg** | {{DELAY_CELL_POLICY}} |
| **NMOS vs PMOS / serpentine-line** | {{NP_MATCH_POLICY}} — delay NMOS with serpentine lines; widen PMOS as needed |
| **Supply domains** | {{SUPPLY_DOMAINS}} |
| **Verification in scope** | {{VERIFICATION_SCOPE}} |
| **Topics owned here** | {{RESIDUAL_OWNED}} |
| **Topics pointed elsewhere** | {{RESIDUAL_POINTED}} |

**Residual ownership table:**

| Topic | Owner | Notes |
|-------|--------|------|
| CMOS circuit/layout practice | **this file** | Until split |
| Class membership | class requirement | cmos-design / other |
| Domain features | peer domain REQ | When present |
| PDK ensure depth | peer process/PDK REQ | When present |

## 3. Why This Requirement Exists (Direct CIAO Alignment)

- **CIAO Principle 2 – Intentional**: CMOS style and critical-path rules are explicit.  
- **CIAO Principle 1 – Caution**: Process pins and absolute claims are not invented.  
- **CIAO Principle 5 – SSOT**: One home for CMOS practice residual until peers own slices.  
- **CIAO Principle 21 / dual policies**: Portable core; filled Implementation Notes for this project.

## 4. Design Principles (CIAO / CIAO-Lite)

- **Caution**: Assume node/PDK/tool facts missing until declared.  
- **Intentional**: Static CMOS + glitch-aware select documented.  
- **Anti-fragile**: Choice sets survive multi-tool EDA without mandatory git.  
- **Over-protect**: Protection rule blocks overclaim and residual dual-SSOT.

## 5. Protection Rule (Sacred)

**Future AI assistants, Grok, or maintainers MUST NOT**:

- Absorb full domain feature law or PDK ensure tables into this file when peers own them.  
- Claim absolute glitch-free / zero-jitter silicon without evidence.  
- Use “glitter” as a technical term.  
- Force git/precommit as CMOS acceptance criteria under cmos-design.  
- Hard-code secrets or single-host foundry paths as universal core law.  
- Cite templates or skills as product-source behavioral authority after specialization.

## 6. Acceptance criteria

| ID | Criterion |
|----|-----------|
| AC-1 | Active registered `requirement-cmos-design` under matching class gate |
| AC-2 | CMOS + static preference declared; critical-path glitch/mux rules present |
| AC-3 | Residual ownership honest vs peer REQs |
| AC-4 | No absolute free-silicon claims without evidence |
| AC-5 | Implementation Notes filled or honest not-yet-collected (draft OK) |
| AC-6 | Versioned body free of harness path inventories |

## 7. Related requirements (versioned surface only)

| Artifact | Role |
|----------|------|
| `docs/requirements/index.md` | Registry SSOT |
| Peer class requirement | Class gate |
| Peer `docs/requirements/requirement-domain-*.md` | Domain features when present |
| Peer process/PDK requirement | PDK ensure when present |

## 8. Status history

| Date | Status | Note |
|------|--------|------|
| {{YYYY-MM-DD}} | {{STATUS}} | {{STATUS_NOTE}} |

## 9. Design-time verification

| TP family / ID | Planned proof |
|----------------|---------------|
| CMOS law present (manual) | Registry + this file Active |
| Critical-path rule (manual/review) | AND-prefer / mux intent on named critical paths |
| Overclaim (manual) | No absolute glitch-free claim without evidence |

**Last Updated**: {{YYYY-MM-DD}}  
**Owner**: {{OWNER}}  
**Alignment**: Registry `docs/requirements/index.md`; **CIAO** (https://github.com/cloudgen/ciao); CIAO-Lite (https://github.com/cloudgen/ciao-lite).
