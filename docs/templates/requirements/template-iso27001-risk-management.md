---
name: iso27001-risk-management
id: LM-ISO27001-RISK-MANAGEMENT
kind: law-mold
description: >
  Portable law mold. Cite as LM-ISO27001-RISK-MANAGEMENT (path secondary).
---

**file**: template-iso27001-risk-management.md  
**Status**: Active (Version 1.0.0 – Portable ISMS risk assessment / treatment patterns)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

## 1. Purpose

This template defines a **portable risk management pattern** for information security: identify assets and threats, assess risk, choose treatment, and feed the Statement of Applicability (SoA).

**Router:** `docs/templates/requirements/template-iso27001-isms-baseline.md`  
**Downstream:** `docs/templates/requirements/template-iso27001-statement-of-applicability.md`, `docs/templates/requirements/template-iso27001-annex-a-controls.md`

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
| **ISO 27001 ISMS** | `docs/terminologies/iso-27001-isms.md` | `product-law` | Risk assessment/treatment |

**SSOT types used:** `meta-catalog` · `policy` · `product-law`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Core rules

### 2.1 Risk criteria

1. Define **likelihood** and **impact** scales (qualitative is acceptable if consistent).  
2. Define **risk acceptance** threshold and who may accept residual risk.  
3. Document criteria in specialized requirements or controlled policy docs — not as hollow “TBD.”

### 2.2 Asset and process inventory (minimum)

| Class | Examples (portable) |
|-------|---------------------|
| Information | Config, logs, customer data, credentials (meta only) |
| Software | Product binary, services, scripts, dependencies |
| Infrastructure | Hosts, containers, CI, cloud projects (as patterns) |
| People / roles | Invoker, admin, system user, on-call |
| Suppliers | Upstream APIs, package registries, install channels |

**MUST NOT** put secret values into the risk register.

### 2.3 Risk identification

For each in-scope asset/process, identify:

- Threats (e.g. unauthorized access, integrity loss, availability loss, supply-chain compromise)  
- Vulnerabilities (missing authz, weak update integrity, secret leakage, misconfig)  
- Existing controls  

### 2.4 Risk analysis and evaluation

1. Score likelihood × impact (or equivalent method).  
2. Rank risks; flag those above acceptance threshold.  
3. Record **owner** for each material risk.

### 2.5 Risk treatment options

| Option | Meaning |
|--------|---------|
| **Modify / mitigate** | Add or improve controls (Annex A / technical) |
| **Avoid** | Remove activity or feature from scope |
| **Share** | Transfer (e.g. supplier contractual, insurance) — document how |
| **Retain** | Accept residual risk with explicit approval |

Treatment **MUST** map to SoA control inclusion or justified exclusion.

### 2.6 Monitoring

1. Reassess on material change (new API, new install channel, privilege model change).  
2. Link incidents to risk register updates when incidents exist.  
3. Keep residual risk visible until closed or re-accepted.

---

## 3. Risk register row shape (specialize completely)

| Field | Content |
|-------|---------|
| Risk ID | Stable ID (e.g. `RISK-{{AREA}}-{{NNN}}`) |
| Asset / process | … |
| Threat / vulnerability | … |
| Likelihood / impact / level | … |
| Existing controls | … |
| Treatment | mitigate / avoid / share / retain |
| Target controls (Annex A themes / OWASP / tech) | … |
| Owner | … |
| Status | open / treating / accepted / closed |
| Residual risk | … |

---

## 4. CIAO alignment

| Principle | Application |
|-----------|-------------|
| **Caution** | Assume threats; no silent risk |
| **Intentional** | Explicit criteria, owners, acceptance |
| **Anti-fragile** | Reassess on change; learn from incidents |
| **Over-protect** | High risks require controls before ship |

---

## 5. Protection Rule (Sacred)

Future agents **MUST NOT**:

- Accept high residual risk silently without documented owner approval.  
- Put secrets or personal sensitive data into risk registers committed to git.  
- Invent control IDs not present in the chosen Annex A edition.  
- Claim “risk managed” without a register or equivalent evidence.  
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
**Alignment**: ISO/IEC 27001 risk-based thinking, `template-iso27001-isms-baseline.md`, `template-iso27001-statement-of-applicability.md`, CIAO / CIAO-Lite
