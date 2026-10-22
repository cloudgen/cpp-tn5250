---
name: iso27001-isms-baseline
id: LM-ISO27001-ISMS-BASELINE
kind: law-mold
description: >
  Portable law mold. Cite as LM-ISO27001-ISMS-BASELINE (path secondary).
---

**file**: template-iso27001-isms-baseline.md  
**Status**: Active (Version 1.0.0 – ISO/IEC 27001 ISMS track router / baseline)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

## 1. Purpose

This template is the **entry point for the ISO/IEC 27001-related template track**. It defines how agents and teams shape an **Information Security Management System (ISMS)** pattern set for a product or organization without hardcoding company names, sites, or secrets, and without claiming formal certification.

**Related templates (load as needed):**

| Template | Role |
|----------|------|
| `docs/templates/requirements/template-iso27001-risk-management.md` | Risk identification, assessment, treatment |
| `docs/templates/requirements/template-iso27001-annex-a-controls.md` | Annex A control themes (2022 structure) |
| `docs/templates/requirements/template-iso27001-statement-of-applicability.md` | Statement of Applicability (SoA) pattern |
| `docs/templates/requirements/template-iso27001-incident-management.md` | Security incident process (ISMS view) |
| `docs/templates/requirements/template-owasp-security-baseline.md` | Technical app-security companion (OWASP) |
| `docs/templates/requirements/template-iso9000-qms-baseline.md` | Quality management companion (ISO 9000/9001 — distinct from ISMS) |
| `docs/templates/requirements/template-secret-management.md` | Secrets handling |
| `docs/templates/requirements/template-least-privilege-user.md` | OS least privilege |
| `docs/templates/requirements/template-three-layer-privilege-model.md` | Type 0 / 1 / 2 privilege architecture |
| `docs/templates/requirements/template-backup-strategy.md` | Backup / restore |
| `docs/templates/checklists/security-review.md` | General security code/config review |
| `docs/templates/checklists/checklist-owasp-security-review.md` | OWASP-oriented review |
| `docs/templates/checklists/checklist-iso27001-control-review.md` | ISMS / Annex A oriented blank checklist |
| `docs/skills/skill-iso27001-isms-review.md` | Agent harness: ISMS review Pass/Revise/Block (no certification) |
| `docs/terminologies/iso-27001-isms.md` | Shared language: ISMS vs QMS vs OWASP |
| `docs/skills/README.md` | ISO 27001 ↔ skill mapping |

**Agent review path:** Run `docs/skills/skill-iso27001-isms-review.md` (loads baseline + checklist). For app/API code also run OWASP security checklist / `security-review.md`.

**Public references (standards context — not product hosts):**  
ISO/IEC 27001 (ISMS requirements), ISO/IEC 27002 (control guidance), [ISO](https://www.iso.org/), [CIAO](https://github.com/cloudgen/ciao)

**Important:** Owning these templates does **not** mean the organization is certified. Certification requires formal audit against the purchased standard text and organizational evidence.

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
| **ISO 27001 ISMS** | `docs/terminologies/iso-27001-isms.md` | `product-law` | Primary ISMS baseline term |
| **OWASP app security** | `docs/terminologies/owasp-app-security.md` | `product-law` | Technical companion |

**SSOT types used:** `meta-catalog` · `policy` · `product-law`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Scope

| In scope | Out of scope |
|----------|--------------|
| Portable ISMS process patterns (context, leadership, planning, support, operation, performance, improvement) | Claiming ISO 27001 certification without audit evidence |
| Annex A control *themes* for specialization | Copying the full copyrighted standard into the repo |
| Risk → treatment → SoA workflow | Hardcoding org name, sites, personal data of employees as universal law |
| Linking technical controls to OWASP/CIAO templates | Secrets, credentials, or audit findings with confidential data in git |

---

## 3. ISMS process baseline (Plan–Do–Check–Act)

### 3.1 Context of the organization

1. Define **information security objectives** for the system/product in scope.  
2. Identify interested parties and their requirements (customers, regulators, operators, agents).  
3. Define **ISMS scope** (products, environments, data classes, exclusions with justification).

### 3.2 Leadership and commitment

1. Assign **roles and responsibilities** for information security (including Security agent role in multi-agent work).  
2. Ensure policies are approved, communicated, and reviewed on a defined cadence.  
3. Provide resources for controls that are marked applicable in the SoA.

### 3.3 Planning (risk-driven)

1. Perform risk assessment and treatment per `template-iso27001-risk-management.md`.  
2. Select controls and document SoA per `template-iso27001-statement-of-applicability.md`.  
3. Set measurable security objectives where practical (e.g. patch SLA, backup restore test frequency).

### 3.4 Support

1. Competence / awareness for people who operate privileged paths.  
2. Documented information control: no secrets in docs; versioned policies; inventory honesty.  
3. Communication of security-relevant changes (break-glass, incidents, material config).

### 3.5 Operation

1. Implement selected Annex A controls (`template-iso27001-annex-a-controls.md`).  
2. Change management for security-impacting changes (auth, crypto, install channel, privilege).  
3. Supplier / dependency awareness for third-party components and online install channels.

### 3.6 Performance evaluation

1. Monitor security-relevant events (align logging SSOT terms when present).  
2. Internal review of control effectiveness (checklist runs under `docs/checklists/` when retained).  
3. Management review inputs: incidents, risks, audit findings, open actions.

### 3.7 Improvement

1. Corrective actions for nonconformities and incidents.  
2. Continual improvement of controls and documentation.  
3. Feed durable lessons into requirements/templates/skills; project incidents when on disk.

---

## 4. Relationship to technical security (OWASP / CIAO)

| Layer | Artifact family | Role |
|-------|-----------------|------|
| **ISMS / governance** | `template-iso27001-*` | Process, risk, SoA, control selection |
| **Application security** | `template-owasp-*` | Technical Top 10 / ASVS / API / secure coding |
| **Runtime defensive engineering** | CIAO templates (privilege, secrets, backup, install integrity) | Implementation safety |

**Agents MUST NOT** treat “we have OWASP templates” as full ISO 27001 conformity, or vice versa.

---

## 5. Specialization into project requirements

When durable product/org law is needed:

1. Scope the ISMS (systems, data classes, environments).  
2. Run risk assessment → treatment options.  
3. Draft SoA (include / exclude + justification).  
4. Specialize Annex A themes into `requirement-*.md` with **parameterization** (app type, path choices, privilege actors) per `docs/terminologies/project-requirements.md` when present.  
5. Register requirements in `docs/requirements/index.md` when files exist.  
6. Verify with `checklist-iso27001-control-review.md` and technical security checklists.

**Genesis / empty requirements are valid** — use these templates as design patterns until specialized. **Do not invent** missing requirement paths.

---

## 6. Documented information rules (dual policy)

| Surface | Rule |
|---------|------|
| Templates / skills | Portable; `{{PLACEHOLDER}}` OK; no secrets |
| Specialized requirements | Complete when claimed done; no hollow TBD; no bare unfilled slots |
| Product README / CHANGELOG | Real non-secret facts allowed (no-hardcode excluded); still no secrets |
| Evidence records | Prefer redacted findings; never commit credentials or personal sensitive data |

---

## 7. Agent role map

| Role | ISMS duty |
|------|-----------|
| **Explore** | Scope, assets, data classes, existing controls |
| **Plan** | Risk → treatment → SoA; requirement create/update |
| **Implement** | Technical controls via secure coding / privilege / install templates |
| **Review** | Completeness of SoA links and checklists |
| **Security** | Own control-review verdict; block fake conformity claims |

---

## 8. Protection Rule (Sacred)

Future agents **MUST NOT**:

1. Claim **ISO 27001 certified** or full conformity without formal evidence and authorized statement.  
2. Paste the full copyrighted standard text into the repository as a substitute for licensed use.  
3. Invent Annex A control IDs that are not from the applicable edition.  
4. Store secrets, personal sensitive data, or raw credentials in ISMS docs.  
5. Cite `template-iso27001-*` as product-source ALIGNMENT law (specialize to live `requirement-*.md`).  
6. Invent missing skill/requirement/template paths.  
7. Confuse ISMS process completeness with application exploit resistance (use OWASP track too).

---


## Design-time verification

| Gate | Artifact | Phase |
|------|----------|-------|
| Checklist | `../checklists/checklist-iso27001-control-review.md` | Design + Review |
| Skill | `skill-iso27001-isms-review` | Review |

**RTM:** `../tests/template-requirement-test-traceability.md` §4.

**Last Updated**: 2026-07-12  
**Owner**: {{OWNER}}  
**Alignment**: ISO/IEC 27001 ISMS concepts, ISO/IEC 27002 control guidance (edition-aware), `template-owasp-security-baseline.md`, CIAO / CIAO-Lite, `docs/policies/policy-no-hardcode.md`, `docs/terminologies/incident-report.md`
