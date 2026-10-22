---
name: iso9000-qms-baseline
id: LM-ISO9000-QMS-BASELINE
kind: law-mold
description: >
  Portable law mold. Cite as LM-ISO9000-QMS-BASELINE (path secondary).
---

**file**: template-iso9000-qms-baseline.md  
**Status**: Active (Version 1.0.0 – ISO 9000 family / QMS track router & baseline)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

## 1. Purpose

This template is the **entry point for the ISO 9000 family quality-management track**. In practice, certifiable **requirements** come from **ISO 9001** (Quality Management System); **ISO 9000** provides fundamentals and vocabulary. These templates give **portable QMS patterns** for products and multi-agent engineering work—without hardcoding organization names or claiming certification.

**Related templates (load as needed):**

| Template | Role |
|----------|------|
| `docs/templates/requirements/template-iso9000-process-approach.md` | Process approach, interactions, performance |
| `docs/templates/requirements/template-iso9000-risk-opportunity.md` | Risk-based thinking & opportunities |
| `docs/templates/requirements/template-iso9000-documented-information.md` | Controlled documented information |
| `docs/templates/requirements/template-iso9000-nonconformity-improvement.md` | Nonconformity, corrective action, continual improvement |
| `docs/templates/requirements/template-iso27001-isms-baseline.md` | Information security management companion (distinct standard) |
| `docs/templates/requirements/template-owasp-security-baseline.md` | Application security companion |
| `docs/templates/checklists/plan-and-requirements.md` | Plan / requirements gate |
| `docs/templates/checklists/implementation-ciao.md` | Implementation quality gate |
| `docs/templates/checklists/code-review.md` | Product quality review gate |
| `docs/templates/checklists/checklist-iso9000-qms-review.md` | QMS-oriented blank checklist |
| `docs/skills/skill-iso9000-qms-review.md` | Agent harness to run the QMS review (Pass/Revise/Block; no certification) |

**Shared language (terminology):** `docs/terminologies/iso-9000-qms.md` (ISO 9000 vs 9001 vs QMS vs ISMS/OWASP)

**Public references (standards context — not product hosts):**  
ISO 9000 (fundamentals/vocabulary), ISO 9001 (QMS requirements), [ISO](https://www.iso.org/), [CIAO](https://github.com/cloudgen/ciao)

**Important:** Using these templates does **not** mean the organization is ISO 9001 certified. Certification requires formal audit against the licensed standard and organizational evidence.

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
| **ISO 9000 QMS** | `docs/terminologies/iso-9000-qms.md` | `product-law` | Primary QMS baseline term |
| **Project requirements** | `docs/terminologies/project-requirements.md` | `product-law` | Product law surface |

**SSOT types used:** `meta-catalog` · `policy` · `product-law`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Scope

| In scope | Out of scope |
|----------|--------------|
| Portable QMS process patterns (context, leadership, planning, support, operation, performance, improvement) | Claiming ISO 9001 certification without audit evidence |
| Process approach for product/engineering delivery | Copying the full copyrighted standard into the repo |
| Quality objectives, customer requirements, nonconformity handling | Hardcoding org brand, customer PII, or secrets as universal law |
| Linking QMS to multi-agent harness (roles, checklists, requirements) | Confusing QMS with ISMS (use ISO 27001 track for security management) |

---

## 3. Quality management principles (portable)

Use these as design intent (aligned with ISO 9000 family thinking):

1. **Customer focus** — understand and meet stated/implied needs; measure satisfaction where applicable.  
2. **Leadership** — direction, accountability, quality culture.  
3. **Engagement of people** — competence and clear responsibilities (including agent roles).  
4. **Process approach** — managed interrelated activities with inputs/outputs.  
5. **Improvement** — continual improvement of processes and products.  
6. **Evidence-based decision making** — use records, tests, reviews—not vibes.  
7. **Relationship management** — suppliers, upstream projects, integrators.

---

## 4. QMS process baseline (Plan–Do–Check–Act)

### 4.1 Context of the organization (Clause 4 pattern)

1. Define external/internal issues relevant to quality objectives.  
2. Identify interested parties and their requirements (customers, operators, regulators, agents).  
3. Define **QMS scope** (products, services, lifecycle stages, exclusions with justification).  
4. Establish process map (see `template-iso9000-process-approach.md`).

### 4.2 Leadership (Clause 5 pattern)

1. Quality policy: commit to requirements and improvement.  
2. Roles: who owns quality decisions (including **Review** / **Security** when quality intersects safety).  
3. Customer focus: requirements and feedback loops.

### 4.3 Planning (Clause 6 pattern)

1. Address risks and opportunities (`template-iso9000-risk-opportunity.md`).  
2. Set **quality objectives** (measurable where practical).  
3. Plan changes that affect product quality (requirements, architecture, release).

### 4.4 Support (Clause 7 pattern)

1. Resources, competence, awareness.  
2. Documented information control (`template-iso9000-documented-information.md`).  
3. Communication of quality-impacting changes.

### 4.5 Operation (Clause 8 pattern)

1. Determine and review **product/service requirements**.  
2. Design/development controls (plan, inputs, outputs, review, verification, validation as applicable).  
3. Control of externally provided processes/products (dependencies, upstream APIs).  
4. Production/delivery control (build, test, release, install integrity when applicable).  
5. Release and post-delivery activities (support, self-update quality).

### 4.6 Performance evaluation (Clause 9 pattern)

1. Monitoring, measurement, analysis (tests, metrics, reviews).  
2. Internal audit / checklist-driven reviews.  
3. Management review inputs: nonconformities, customer feedback, process performance, risks.

### 4.7 Improvement (Clause 10 pattern)

1. Nonconformity and corrective action (`template-iso9000-nonconformity-improvement.md`).  
2. Continual improvement of QMS and product.  
3. Feed durable lessons into requirements, templates, skills, incidents when applicable.

---

## 5. Multi-agent harness mapping

| QMS concern | Harness aspect |
|-------------|-----------------|
| Customer / product requirements | `docs/requirements/` + elicitation skills |
| Process definition | This track + skills playbooks |
| Documented information | Requirements, README/CHANGELOG, checklists, dual policy |
| Verification | `project-check-lists` blank forms + filled runs |
| Nonconformity | Incidents (process) + defects/reviews (product) |
| Roles | Explore / Plan / Implement / Review / Security |

---

## 6. Specialization into project requirements

When durable product/org law is needed:

1. Define QMS scope and process map.  
2. Set quality objectives and risk/opportunity register.  
3. Specialize process rules into `requirement-*.md` (parameterize app type, path choices, privilege actors per `project-requirements` term when present).  
4. Register in `docs/requirements/index.md` when files exist.  
5. Verify with `checklist-iso9000-qms-review.md` and implementation/code-review checklists.

**Empty requirements (genesis) are valid** — use these templates as design patterns until specialized. **Do not invent** missing requirement paths.

---

## 7. Dual policy (documented information)

| Surface | Rule |
|---------|------|
| Templates / skills | Portable; `{{PLACEHOLDER}}` OK; no secrets |
| Specialized requirements | Complete when claimed done; no hollow TBD |
| Product README / CHANGELOG | Real non-secret product facts allowed (no-hardcode excluded) |
| Quality records | Prefer redaction; never commit secrets or unnecessary personal data |

---

## 8. Protection Rule (Sacred)

Future agents **MUST NOT**:

1. Claim **ISO 9001 certified** or full conformity without formal evidence and authorized statement.  
2. Paste the full copyrighted standard text into the repository as a substitute for licensed use.  
3. Invent clause/control numbers not present in the applicable edition.  
4. Store secrets or unnecessary personal data in QMS docs.  
5. Cite `template-iso9000-*` as product-source ALIGNMENT law (specialize to live `requirement-*.md`).  
6. Invent missing skill/requirement/template paths.  
7. Treat QMS completeness as a substitute for security (use ISO 27001 + OWASP tracks where security applies).

---


## Design-time verification

| Gate | Artifact | Phase |
|------|----------|-------|
| Checklist | `../checklists/checklist-iso9000-qms-review.md` | Design + Review |
| Skill | `skill-iso9000-qms-review` | Review |

**RTM:** `../tests/template-requirement-test-traceability.md` §4.

**Last Updated**: 2026-07-12  
**Owner**: {{OWNER}}  
**Alignment**: ISO 9000 family fundamentals, ISO 9001 QMS requirements (edition-aware), CIAO / CIAO-Lite, `docs/policies/policy-no-hardcode.md`, `docs/terminologies/project-requirements.md`, `docs/terminologies/sub-agent-roles.md`
