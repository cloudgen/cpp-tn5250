---
name: policy-principles
id: LM-POLICY-PRINCIPLES
kind: law-mold
description: >
  Portable law mold. Cite as LM-POLICY-PRINCIPLES (path secondary).
---

**file**: template-policy-principles.md  
**Status**: Active (Version 1.0.0 – Portable mold for policy-class principles / rules packaging)  
**Project**: Any CIAO-Lite **policy** workspace (reusable template — **no project brand**)  
**Philosophy**: CIAO **v2.10.2** / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered / Over-protect)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

# =============================================================================
# Template: policy-principles (NOT a requirement)
# Specialize into: root README principles sections, CIAO-style principle docs,
#                  DAIL / agent-boundary docs, or docs under a principles path
# Never specialize into docs/requirements/requirement-*.md
# =============================================================================


## Design-time verification

| Gate | Artifact | Phase |
|------|----------|-------|
| Specialize → product suite or checklist | declare TP-IDs or checklist in specialized REQ | Design |
| RTM | `../tests/template-requirement-test-traceability.md` | Design |

When this mold has no executable TP family, mark **n/a** with reason in product `reviews/test-plan.md`.

## How to use this template (authoring only)

1. Confirm project nature is **policy** ([`policy-project`](../../policies/policy-project.md)) — not software-development, not server-maintenance, not genesis-template.  
2. **MUST NOT** create `docs/requirements/requirement-*.md` for this class (including no `requirement-class-policy*`).  
3. Specialize content into **principles / rules surfaces** (root README, dedicated principle files, agent-boundary / DAIL docs, optional `examples/` demos).  
4. Keep harness knowledge portable; published policy brand lives only in product surfaces.  
5. Empty `docs/requirements/` registry remains **required honesty**.

**Target surfaces (examples of *kinds*, not hard-coded product paths):**  
product root README · dedicated principles document · agent-boundary / DAIL document · illustrative `examples/`  

---

# Policy principles package (mold)

**Status:** {{STATUS}}  
**Class:** policy  
**Updated:** {{YYYY-MM-DD}}

## 1. Purpose

State the **normative principles and rules** this package publishes for humans and agents (how to write, change, protect, or operate systems). This is **specialized policy knowledge**, not product-feature acceptance criteria and not ops command-whitelist law.

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
| **Policy project** | `docs/terminologies/policy-project.md` | `product-law` | Class #4 principles package |
| **Project class** | `docs/terminologies/project-class.md` | `product-law` | Eleven-class model (internal name) |
| **Project nature** | `docs/terminologies/project-nature.md` | `product-law` | Daily-life name for **project class** (alias stub) |

**SSOT types used:** `meta-catalog` · `policy` · `product-law`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Core rules (mandatory — portable shape)

### 2.0 Class membership

1. **MUST** treat the workspace as **policy** class.  
2. **MUST NOT** author or register any `requirement-*.md` while class is policy.  
3. **MUST** retain harness knowledge (skills/terms/templates/AGENTS).  
4. **MUST NOT** claim software-development or server-maintenance class gates (class REQs, ship-unit primary, allowlist primary) without explicit reclassify.  
5. **MUST** distinguish this specialized package from **genesis-template** (blank specialization): principles/rules surfaces are present and claimed.

### 2.1 Principles body

6. **MUST** publish a durable **principles / rules body** (one or more documents) with complete sections — no hollow “coming soon” as claimed-done policy.  
7. **MUST** name each principle/rule so agents can cite it.  
8. **SHOULD** group rules into clear families (e.g. caution, intentionality, anti-fragility, over-protection, output SSOT, dual policies).  
9. **MUST NOT** hide secrets, credentials, or private host paths in principle docs.  
10. **MUST** keep portable harness layers free of frozen product brand as universal law ([`no-hardcode-policy`](../../policies/policy-no-hardcode.md)).

### 2.2 Rules vs procedures

11. **MUST** keep **rules** (what must be true) distinct from **skills** (how agents perform tasks).  
12. **MUST NOT** treat `docs/skills/*` as the published product principles SSOT.  
13. **SHOULD** use examples only to **illustrate** rules, not as a second conflicting SSOT.

### 2.3 Honesty

14. **MUST** keep `docs/requirements/index.md` empty of product-law rows while class is policy.  
15. **MUST NOT** invent requirement paths for “completeness.”  
16. **MUST** reclassify via owner intent before introducing software-dev or server-maintenance law.

## 3. Implementation notes (fill when specializing)

| Field | This package |
|-------|----------------|
| Policy / principles title | {{POLICY_TITLE}} |
| Primary principles document path(s) | {{PRINCIPLES_PATHS}} |
| Agent-boundary / DAIL doc (if any) | {{AGENT_BOUNDARY_PATH}} |
| Illustrative examples (if any) | {{EXAMPLES_PATH}} |
| Version of principles package | {{VERSION}} |
| Contact / license surface | {{LICENSE_OR_CONTACT}} |

## 4. Acceptance (policy package)

- [ ] Class declared **policy** in workspace maps  
- [ ] Zero `requirement-*.md` on disk  
- [ ] Principles/rules body complete and citable  
- [ ] No secrets in published materials  
- [ ] Examples (if any) do not contradict principles  
- [ ] Harness knowledge retained  

---

**Last Updated**: 2026-07-17  
**Alignment**: policy-project · project-class · harness-knowledge · dual-policies · stay-honest · no-hardcode-policy
