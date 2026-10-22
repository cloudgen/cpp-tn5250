---
name: iso9000-nonconformity-improvement
id: LM-ISO9000-NONCONFORMITY-IMPROVEMENT
kind: law-mold
description: >
  Portable law mold. Cite as LM-ISO9000-NONCONFORMITY-IMPROVEMENT (path secondary).
---

**file**: template-iso9000-nonconformity-improvement.md  
**Status**: Active (Version 1.0.0 – Portable nonconformity, corrective action, continual improvement)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

## 1. Purpose

This template defines how to handle **nonconformities (NC)**, **corrective actions**, and **continual improvement** in a QMS—covering product defects, process failures, and documentation nonconformities—aligned with ISO 9001 improvement intent and CIAO learning loops.

**Router:** `docs/templates/requirements/template-iso9000-qms-baseline.md`  
**Related:** `template-iso9000-risk-opportunity.md`, `docs/terminologies/incident-report.md`, code-review / security checklists

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
| **ISO 9000 QMS** | `docs/terminologies/iso-9000-qms.md` | `product-law` | NC / CAPA |
| **Incident report** | `docs/terminologies/incident-report.md` | `product-law` | Process nonconformity write-ups |

**SSOT types used:** `meta-catalog` · `policy` · `product-law`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Definitions

| Term | Meaning |
|------|---------|
| **Nonconformity** | Failure to meet a requirement (product, process, or documented information) |
| **Correction** | Immediate action to contain/fix the instance |
| **Corrective action** | Action to eliminate **root cause** and prevent recurrence |
| **Opportunity for improvement** | Change that enhances performance without a required NC |
| **Effectiveness check** | Verification that corrective action worked |

---

## 3. Core rules

### 3.1 Identification sources

- Failed tests, checklist Fail/Block, customer complaints, install failures  
- Review findings, security findings, monitoring alerts  
- Process deviations (skipped gates, phantom paths, hollow deliverables)  
- Incidents (process) when `docs/incidents/` is used  

### 3.2 Response process

1. **Contain** — stop further bad output; notify stakeholders as needed.  
2. **Correct** — fix or quarantine the nonconforming product/process instance.  
3. **Analyze root cause** — not only symptoms (5-Whys or equivalent; keep evidence).  
4. **Corrective action** — change process, requirements, tests, templates, or code.  
5. **Effectiveness check** — confirm recurrence prevented (retest, re-review, time-boxed watch).  
6. **Record** — durable note (ticket, filled checklist, incident, or NC log)—**no secrets**.  
7. **Update risk/opportunity register** when material.

### 3.3 Severity (example — specialize)

| Level | Example |
|-------|---------|
| Minor | Doc inconsistency; low user impact; caught pre-release |
| Major | User-visible defect escaped; install broken; gate bypassed |
| Critical | Data loss, security breach, widespread outage, trust failure |

### 3.4 Continual improvement

1. Track recurring NC themes.  
2. Convert systemic issues into requirement/template/skill updates.  
3. Prefer preventive improvements (checklists, SSOT, automation) over heroics.  
4. Align with multi-agent **Review/Security** gates so the same failure class is harder next time.

### 3.5 Disposition of nonconforming product

| Disposition | When |
|-------------|------|
| Rework / fix | Defect correctable before release |
| Regrade / limit | Accept with documented limitation (explicit) |
| Reject / recall | Not acceptable; block release or reverse |
| Scrap | Artifact unusable |

**MUST** record disposition for major/critical product NC.

---

## 4. NC record shape (specialize completely)

| Field | Content |
|-------|---------|
| NC ID | Stable ID |
| Source | test / review / customer / install / other |
| Description | What failed which requirement |
| Severity | … |
| Containment / correction | … |
| Root cause | … |
| Corrective action | … |
| Effectiveness check | method + result |
| Owner / dates | … |
| Status | open / verifying / closed |

---

## 5. Mapping to workspace artifacts

| Situation | Prefer |
|-----------|--------|
| Process/policy failure | `docs/incidents/incident-*.md` via incident skill when durable |
| Product defect | Issue tracker + tests + requirement update if law missing |
| Review failure | Checklist Revise/Block + fix before Pass |
| Systemic agent failure | Update skill/template/term (harness improvement) |

---

## 6. Protection Rule (Sacred)

Future agents **MUST NOT**:

- Close major/critical NC without root cause and effectiveness check.  
- Hide escaped defects to force a Pass.  
- Skip updating requirements/tests when the NC proves missing product law.  
- Store secrets in NC records.  
- Invent sample NC “for completeness.”  
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
**Alignment**: ISO 9001 nonconformity & improvement intent, `template-iso9000-qms-baseline.md`, `template-iso9000-risk-opportunity.md`, CIAO / CIAO-Lite, incident-report term
