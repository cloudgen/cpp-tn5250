---
name: iso9000-risk-opportunity
id: LM-ISO9000-RISK-OPPORTUNITY
kind: law-mold
description: >
  Portable law mold. Cite as LM-ISO9000-RISK-OPPORTUNITY (path secondary).
---

**file**: template-iso9000-risk-opportunity.md  
**Status**: Active (Version 1.0.0 – Portable QMS risk-based thinking & opportunities)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

## 1. Purpose

This template defines **risk-based thinking** and **opportunity** handling for a quality management system (ISO 9001:2015+ pattern): identify what can go wrong or better, evaluate, plan actions, and check effectiveness—without requiring a full enterprise ERM tool.

**Router:** `docs/templates/requirements/template-iso9000-qms-baseline.md`  
**Distinct from:** `docs/templates/requirements/template-iso27001-risk-management.md` (information security risks). Link both when a change has quality **and** security impact.

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
| **ISO 9000 QMS** | `docs/terminologies/iso-9000-qms.md` | `product-law` | Risk-based thinking |

**SSOT types used:** `meta-catalog` · `policy` · `product-law`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Core rules

### 2.1 Quality risk categories (portable)

| Category | Examples |
|----------|----------|
| Product quality | Wrong behavior, data loss, broken install, regression |
| Process quality | Skipped review, hollow requirements, missing tests |
| Customer / user | Misleading docs, install failure, support burden |
| Supplier / upstream | Breaking API, bad dependency, compromised package |
| Delivery | Late release, failed pipeline, environment mismatch |
| Compliance / contract | Missed obligated feature or record (when applicable) |

### 2.2 Opportunity categories (portable)

| Category | Examples |
|----------|----------|
| Efficiency | Automation, checklist reuse, modular templates |
| Quality uplift | Better validation, stronger idempotency, clearer SSOT |
| Customer value | Simpler install, better diagnostics, clearer UX |
| Learning | Incidents → skills/templates/requirements hardening |

### 2.3 Evaluation

1. Define simple **likelihood** and **impact** scales (or equivalent).  
2. Prioritize actions for risks above threshold.  
3. Assign **owner** and target review date.  
4. Record residual risk when accepting without full mitigation.

### 2.4 Actions

| Response | Meaning |
|----------|---------|
| Mitigate | Change process/product to reduce risk |
| Avoid | Remove risky activity/feature |
| Transfer | Share via supplier terms (document how) |
| Accept | Explicit residual acceptance |
| Pursue (opportunity) | Planned improvement with success criteria |

### 2.5 Triggers for reassessment

- New major feature or architecture change  
- Recurring nonconformities  
- Supplier/upstream change  
- Release channel / install method change  
- Customer-critical incidents  

---

## 3. Register row shape (specialize completely)

| ID | Type (risk/opportunity) | Description | Likelihood | Impact | Action | Owner | Status | Links (REQ/process) |
|----|-------------------------|-------------|------------|--------|--------|-------|--------|---------------------|
| QRO-… | risk / opportunity | … | … | … | … | … | open/closed | … |

**MUST NOT** put secrets in the register.

---

## 4. CIAO alignment

| Principle | Application |
|-----------|-------------|
| **Caution** | Assume failure modes; surface risks early in Plan |
| **Intentional** | Explicit owners and acceptance |
| **Anti-fragile** | Opportunities harden the system; learn from NC |
| **Over-protect** | High product risks need controls before ship |

---

## 5. Protection Rule (Sacred)

Future agents **MUST NOT**:

- Ship known high product-quality risks without documented mitigation or acceptance.  
- Confuse quality risks with security risks without linking the security track when both apply.  
- Leave hollow “risk: TBD” in specialized QMS deliverables claimed complete.  
- Store secrets in risk registers.  
- Cite this template as product-source ALIGNMENT law.

---


## Design-time verification

| Gate | Artifact | Phase |
|------|----------|-------|
| Checklist | `../checklists/checklist-iso9000-qms-review.md` | Design + Review |
| Skill | `skill-iso9000-qms-review` | Review |

**RTM:** `../tests/template-requirement-test-traceability.md` §4.

**Last Updated**: 2026-07-12  
**Owner**: {{OWNER}}  
**Alignment**: ISO 9001 risk-based thinking intent, `template-iso9000-qms-baseline.md`, `template-iso9000-nonconformity-improvement.md`, CIAO / CIAO-Lite
