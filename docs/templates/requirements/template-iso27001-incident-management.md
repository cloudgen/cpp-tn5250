---
name: iso27001-incident-management
id: LM-ISO27001-INCIDENT-MANAGEMENT
kind: law-mold
description: >
  Portable law mold. Cite as LM-ISO27001-INCIDENT-MANAGEMENT (path secondary).
---

**file**: template-iso27001-incident-management.md  
**Status**: Active (Version 1.0.0 – ISMS security incident management patterns)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

## 1. Purpose

This template defines **information security incident management** patterns for an ISMS: detect, report, assess, respond, learn, and improve—aligned with ISO/IEC 27001 operational control thinking and this workspace’s **incident-report** practice.

**Router:** `docs/templates/requirements/template-iso27001-isms-baseline.md`  
**Workspace incident language:** `docs/terminologies/incident-report.md`  
**Authoring skill (when on disk):** `docs/skills/skill-incident-report.md`  
**Storage pattern:** `docs/incidents/incident-*.md` (project-local; may be empty at genesis)

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
| **ISO 27001 ISMS** | `docs/terminologies/iso-27001-isms.md` | `product-law` | Security incident process |
| **Incident report** | `docs/terminologies/incident-report.md` | `product-law` | Incident write-up shape |

**SSOT types used:** `meta-catalog` · `policy` · `product-law`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Core rules

### 2.1 Definitions

| Term | Meaning |
|------|---------|
| **Security event** | Observable occurrence relevant to security (may not be an incident) |
| **Security incident** | Unwanted/unexpected event with probability of compromising information security |
| **Major incident** | High impact; requires escalated response and post-incident review |

### 2.2 Process stages

1. **Prepare** — roles, contacts, runbooks, logging readiness (no secrets in runbooks).  
2. **Detect & report** — channels for humans/agents/monitoring to report events.  
3. **Assess** — severity, scope, data classes affected, ongoing threat.  
4. **Respond** — contain, eradicate, recover; least privilege; backup-before-destructive fix when applicable.  
5. **Communicate** — internal stakeholders; external only per legal/policy (specialize).  
6. **Learn** — post-incident review; update risks, SoA, requirements, templates/skills.  
7. **Record** — durable incident report when policy requires (structure per incident-report term/skill).

### 2.3 Severity (example scale — specialize)

| Level | Example triggers |
|-------|------------------|
| Low | Attempt blocked; no data impact |
| Medium | Limited unauthorized access or integrity issue contained |
| High | Confirmed data exposure, privilege abuse, or widespread availability loss |
| Critical | Ongoing breach, regulatory trigger, or core trust failure |

### 2.4 Evidence and secrecy

1. **MUST NOT** commit raw credentials, session tokens, or personal sensitive data in incident files.  
2. Redact secrets; reference secret store / ticket IDs instead.  
3. Preserve forensic integrity where legal holds apply (specialize).

### 2.5 Link to multi-agent roles

| Role | Incident duty |
|------|---------------|
| **Explore** | Facts, timeline, systems touched |
| **Plan** | Containment sequence; requirement/SoA updates |
| **Implement** | Fixes; surgical; Protection Zones respected |
| **Review** | Completeness of postmortem and regressions tests |
| **Security** | Severity, blast radius, external notification decision support |

### 2.6 Genesis note

At **genesis template** state, `docs/incidents/` may have **zero** `incident-*.md` files. That is valid. Do not invent sample incidents. Create reports only for real events after specialization.

---

## 3. Minimum incident record fields

Align with `docs/terminologies/incident-report.md` when writing files:

1. Header (status, date, owner, related)  
2. Summary  
3. Description  
4. Root cause  
5. Impact  
6. Lessons (CIAO reflection)  
7. Corrective & preventive actions  
8. Protection Rule  
9. Status / next steps  

---

## 4. Protection Rule (Sacred)

Future agents **MUST NOT**:

- Hide material incidents without record when policy requires recording.  
- Put secrets or full sensitive payloads into incident markdown.  
- Skip lessons-learned → risk/SoA/requirement updates for major incidents.  
- Invent incident files “for completeness.”  
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
**Alignment**: ISO/IEC 27001 incident management intent, `docs/terminologies/incident-report.md`, `docs/skills/skill-incident-report.md` (when present), `template-iso27001-risk-management.md`, CIAO / CIAO-Lite
