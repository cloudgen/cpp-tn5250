---
name: iso27001-statement-of-applicability
id: LM-ISO27001-STATEMENT-OF-APPLICABILITY
kind: law-mold
description: >
  Portable law mold. Cite as LM-ISO27001-STATEMENT-OF-APPLICABILITY (path secondary).
---

**file**: template-iso27001-statement-of-applicability.md  
**Status**: Active (Version 1.0.0 – Portable Statement of Applicability (SoA) pattern)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

## 1. Purpose

This template defines the **Statement of Applicability (SoA)** pattern: which Annex A controls (or control themes) are **included** or **excluded**, with **justification**, linkage to risk treatment, and implementation evidence pointers.

**Router:** `docs/templates/requirements/template-iso27001-isms-baseline.md`  
**Inputs:** `template-iso27001-risk-management.md`, `template-iso27001-annex-a-controls.md`  
**Checklist:** `docs/templates/checklists/checklist-iso27001-control-review.md`

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
| **ISO 27001 ISMS** | `docs/terminologies/iso-27001-isms.md` | `product-law` | SoA control selection |

**SSOT types used:** `meta-catalog` · `policy` · `product-law`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Core rules

### 2.1 Completeness

1. Every in-scope control (or agreed theme row) **MUST** appear in the SoA.  
2. **Exclude** requires written justification (not blank).  
3. **Include** requires implementation status and evidence pointer.

### 2.2 Status values

| Status | Meaning |
|--------|---------|
| `included-implemented` | Control selected and in operation |
| `included-planned` | Selected; implementation in progress (owner + target date) |
| `excluded` | Not selected; justified |
| `not-in-edition` | N/A for chosen standard edition |

### 2.3 Linkage

| Link | Required |
|------|----------|
| Risk treatment | Control inclusion should trace to risks mitigated (or baseline policy) |
| Technical requirements | Prefer live `requirement-*.md` when specialized |
| Evidence | Checklist run, config path, procedure doc, ticket — **no secrets** |

### 2.4 Review cadence

1. Review SoA on material scope/risk change and on a defined periodic schedule.  
2. Version the SoA (date + revision).  
3. Management / Security role acknowledges residual exclusions.

---

## 3. SoA header (specialize completely)

| Field | Value |
|-------|--------|
| Organization / product scope | `{{ISMS_SCOPE}}` |
| Standard edition | e.g. ISO/IEC 27001:2022 |
| SoA version / date | … |
| Prepared by | … |
| Approved by | … |
| Related risk register ID/path | … |

---

## 4. SoA row shape

| Control / theme ID | Title (short) | Status | Justification (include or exclude) | Implementation summary | Evidence pointer | Owner |
|--------------------|---------------|--------|------------------------------------|------------------------|------------------|-------|
| e.g. A.8.x or theme label | … | included-implemented / included-planned / excluded | … | … | path or checklist ID | … |

**Rules:**

- Use official control IDs from the licensed edition when claiming formal SoA.  
- Theme-level rows are acceptable for early draft SoA if labeled **theme-level (not certification-grade)**.  
- No secret values in any cell.

---

## 5. Protection Rule (Sacred)

Future agents **MUST NOT**:

- Publish a “complete SoA” with empty justifications.  
- Mark controls implemented without evidence.  
- Claim certification-ready SoA when only theme-level drafts exist.  
- Invent control IDs.  
- Store credentials or personal sensitive data in SoA tables.  
- Cite this template as product-source ALIGNMENT law.

---


## Design-time verification

| Gate | Artifact | Phase |
|------|----------|-------|
| Checklist | `../checklists/checklist-iso27001-control-review.md` | Design + Review |
| Skill | `skill-iso27001-isms-review` | Review |

**RTM:** `../tests/template-requirement-test-traceability.md` §4.

**Last Updated**: 2026-07-12  
**Owner**: {{OWNER}}  
**Alignment**: ISO/IEC 27001 SoA concept, `template-iso27001-risk-management.md`, `template-iso27001-annex-a-controls.md`, CIAO / CIAO-Lite
