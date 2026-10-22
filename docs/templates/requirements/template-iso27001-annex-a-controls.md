---
name: iso27001-annex-a-controls
id: LM-ISO27001-ANNEX-A-CONTROLS
kind: law-mold
description: >
  Portable law mold. Cite as LM-ISO27001-ANNEX-A-CONTROLS (path secondary).
---

**file**: template-iso27001-annex-a-controls.md  
**Status**: Active (Version 1.0.0 – Portable Annex A control themes, ISO/IEC 27001:2022-oriented)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

## 1. Purpose

This template provides **portable control themes** aligned with **ISO/IEC 27001:2022 Annex A** (four themes). Exact control numbering and full normative text remain in the official standard; agents **MUST** verify IDs against the licensed edition when specializing formal SoA rows.

**Router:** `docs/templates/requirements/template-iso27001-isms-baseline.md`  
**SoA:** `docs/templates/requirements/template-iso27001-statement-of-applicability.md`  
**Technical companion:** `docs/templates/requirements/template-owasp-top-10.md`, privilege/secrets/backup templates

**Not a substitute for:** purchasing/using the official ISO text for certification.

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
| **ISO 27001 ISMS** | `docs/terminologies/iso-27001-isms.md` | `product-law` | ISMS control framing |

**SSOT types used:** `meta-catalog` · `policy` · `product-law`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. How to use

1. For each theme/control area, mark **Applicable / Partial / N/A** for the ISMS scope.  
2. Map to technical implementations (code, config, process).  
3. Record inclusion/exclusion in the SoA with justification.  
4. Promote durable rules into `requirement-*.md` when product law is needed.

---

## 3. Theme A.5 — Organizational controls (intent patterns)

| Area (portable label) | MUST / SHOULD intent | Typical tech/process links |
|-----------------------|----------------------|----------------------------|
| Policies for information security | Documented, approved, reviewed security policies | ISMS baseline, product security requirements |
| Roles and responsibilities | Named owners for security decisions | Sub-agent Security role; on-call |
| Segregation of duties | Separate conflicting duties where practical | Type 0/1/2 privilege split |
| Threat intelligence / awareness | Use reliable sources; no exploit how-tos in product tree | Upstream analysis skill when APIs change |
| Information security in project management | Security in plan/review for non-trivial work | Plan checklist, security-review checklist |
| Inventory of information / assets | Know what is protected | Risk register assets |
| Acceptable use / access rights rules | Rules for access grant/review | Access control requirements |
| Supplier relationships | Requirements for third parties and deps | Dependency pin policy; API clients |
| Incident management readiness | Defined response path | `template-iso27001-incident-management.md` |
| Business continuity aspects of security | Availability objectives where required | Backup/restore templates |
| Compliance / legal | Identify applicable obligations | Specialized legal requirements (project-specific) |

---

## 4. Theme A.6 — People controls (intent patterns)

| Area | MUST / SHOULD intent | Links |
|------|----------------------|-------|
| Screening / onboarding (as applicable) | Fit for privileged access | Org HR process (out of code scope) |
| Awareness / training | Operators understand secret handling and privilege | Docs, runbooks |
| Disciplinary process (org) | Misuse has consequences | Org policy |
| Responsibilities after termination | Access removal | Access review / offboarding checklist (specialize) |
| Confidentiality agreements (as applicable) | NDAs where required | Org legal |
| Remote working security | Secure remote access patterns | VPN/SSO/product design as applicable |

---

## 5. Theme A.7 — Physical controls (intent patterns)

| Area | MUST / SHOULD intent | Notes for software-centric projects |
|------|----------------------|-------------------------------------|
| Physical security perimeter / entry | Protect facilities hosting critical systems | Often **N/A** or supplier-owned for pure SaaS/CLI; document N/A justification |
| Equipment security / cabling / clear desk | Reduce physical theft/shoulder-surf | N/A or partial for cloud-only |
| Secure disposal | Media and device disposal | Include laptop/USB policy if in scope |
| Supporting utilities / environmental | Power/cooling for critical sites | Often supplier |

**Rule:** Software-only scopes **MUST** still explicitly mark physical controls Include/Exclude in SoA — silent omission is not justification.

---

## 6. Theme A.8 — Technological controls (intent patterns)

| Area | MUST / SHOULD intent | Typical CIAO / OWASP links |
|------|----------------------|----------------------------|
| User endpoint / privileged utility protection | Harden admin tools; least privilege | three-layer privilege, system-user |
| Access control / authentication | Identity, authn, authz | OWASP A01/A07, API security |
| Secure authentication | Strong auth patterns where applicable | secret-management, no dummy creds |
| Capacity / availability monitoring | Detect resource exhaustion | error-handling, ops monitoring |
| Malware protection (as applicable) | Endpoint/server protections | Org endpoint standards |
| Vulnerability / technical compliance | Manage known issues | OWASP A06, dependency pins |
| Configuration management | Secure baselines; Config SSOT | configuration-management template |
| Information deletion | Secure delete where required | data retention policy (specialize) |
| Data masking / leakage prevention | Mask secrets/PII in logs and support | secret-management, output SSOT |
| Backup | Backup before destructive change; restore tested | template-backup-strategy |
| Logging / monitoring | Security events; no secret leakage | stdout/stderr SSOT terms |
| Network security / segregation | Segment trust zones | network architecture (specialize) |
| Web filtering / secure coding | Dev secure practices | OWASP secure coding |
| Secure development lifecycle | Security in plan/implement/review | checklists, harness roles |
| Application security requirements | Explicit security requirements | specialize from OWASP + Annex A |
| Secure architecture / engineering principles | Least privilege, fail-closed, defense in depth | CIAO, system-architecture templates |
| Change management | Control security-impacting changes | plan-and-requirements checklist |
| Test information protection | No production secrets in tests | test doubles only |
| Audit logging protection | Protect logs from tampering/unauthorized access | logging design |
| Cryptography / key management | Vetted crypto; key lifecycle | SSL template, secret-management |

---

## 7. Applicability matrix (fill when specializing)

| Theme | Applicable? | Primary owners | Linked REQ-IDs / evidence |
|-------|-------------|----------------|---------------------------|
| A.5 Organizational | Yes / Partial / N/A | | |
| A.6 People | Yes / Partial / N/A | | |
| A.7 Physical | Yes / Partial / N/A | | |
| A.8 Technological | Yes / Partial / N/A | | |

*(Specialized requirements: every cell complete — no hollow blanks when claiming done.)*

---

## 8. Protection Rule (Sacred)

Future agents **MUST NOT**:

- Treat this summary as the full normative Annex A text.  
- Invent control numbers.  
- Mark all controls “Included” without implementation evidence.  
- Exclude physical/people controls silently when facilities/staff are in scope.  
- Embed secrets in control descriptions.  
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
**Alignment**: ISO/IEC 27001:2022 Annex A themes, ISO/IEC 27002 guidance (edition-aware), `template-iso27001-isms-baseline.md`, `template-owasp-security-baseline.md`, CIAO / CIAO-Lite
