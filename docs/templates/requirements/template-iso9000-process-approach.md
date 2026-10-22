---
name: iso9000-process-approach
id: LM-ISO9000-PROCESS-APPROACH
kind: law-mold
description: >
  Portable law mold. Cite as LM-ISO9000-PROCESS-APPROACH (path secondary).
---

**file**: template-iso9000-process-approach.md  
**Status**: Active (Version 1.0.0 – Portable QMS process approach patterns)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

## 1. Purpose

This template defines the **process approach** for quality management: identify key processes, their inputs/outputs, interactions, owners, criteria, and performance measures—so work is managed as a coherent system rather than ad-hoc tasks.

**Router:** `docs/templates/requirements/template-iso9000-qms-baseline.md`  
**Related:** plan/implement/review checklists, `docs/terminologies/sub-agent-roles.md`, `docs/terminologies/harness-engineering.md` (when present)

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
| **ISO 9000 QMS** | `docs/terminologies/iso-9000-qms.md` | `product-law` | Process approach |

**SSOT types used:** `meta-catalog` · `policy` · `product-law`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Core rules

### 2.1 Process definition (minimum fields)

| Field | Content |
|-------|---------|
| Process name / ID | Stable identifier |
| Purpose | Why the process exists |
| Owner | Role accountable for performance |
| Inputs | Information, materials, triggers |
| Activities | Ordered steps (high level) |
| Outputs | Deliverables, records |
| Criteria | Acceptance / done rules |
| Resources | People, tools, environments |
| Risks / opportunities | Link to risk-opportunity register |
| Performance indicators | What is measured |
| Interactions | Upstream/downstream processes |

### 2.2 Typical engineering QMS processes (portable catalog)

| Process (example) | Typical outputs | Typical harness links |
|-------------------|-----------------|----------------------|
| Requirements management | `requirement-*.md`, index rows | `skill-requirement-elicitation`, `skill-create-specific-requirement`, `skill-requirement-review` |
| Design & development | Architecture, plans, design reviews | plan mode, `skill-system-architecture-design`, architecture templates |
| Implementation | Code, configs, install units | `skill-sh-script-coding` / python / nodejs coding skills, CIAO zones |
| Verification & validation | Tests, checklist runs | `code-review`, `implementation-ciao`, `checklist-iso9000-qms-review` |
| Release & delivery | Versioned artifacts, README install truth | `skill-commit-check`, `skill-write-readme`, `skill-online-install-self-management` |
| Change control | Approved change, updated requirements | `plan-and-requirements` checklist |
| Nonconformity & CAPA | Corrective actions | `template-iso9000-nonconformity-improvement`, `skill-incident-report`, `skill-debug-procedures` |
| Supplier / upstream control | Analyzed upstream, pinned deps | `skill-upstream-git-analysis` |
| Documented information | Controlled docs/records | `template-iso9000-documented-information`, `skill-template-review`, `skill-write-readme` |

Projects **select** applicable processes; unused ones are **N/A with justification** in specialized docs.

### 2.3 Process interactions (system view)

```text
Customer / stakeholder needs
        → Requirements management
        → Design & development
        → Implementation
        → Verification & validation
        → Release & delivery
        → Feedback / support
                ↺ Improvement / CAPA
```

Multi-agent mapping (default):

| Stage | Primary roles |
|-------|----------------|
| Needs → requirements | Explore, Plan |
| Design | Plan, Security |
| Build | Implement |
| Verify | Review, Security |
| Release | Implement, Review |
| Improve | All; Security for safety/security NC |

### 2.4 Performance

1. Define at least one indicator per critical process (e.g. escaped defects, checklist pass rate, install success, time-to-restore).  
2. Review indicators on a defined cadence.  
3. Act on adverse trends via improvement process.

### 2.5 Outsourced / external processes

1. Identify externally provided processes (cloud, packages, APIs, contractors).  
2. Define controls (pins, analysis, SLAs, acceptance checks).  
3. Do not treat “vendor did it” as automatic conformity.

---

## 3. Process register row (specialize completely)

| Process ID | Name | Owner | Critical? | KPI | Related REQ-IDs | Status |
|------------|------|-------|-----------|-----|-----------------|--------|
| … | … | … | Y/N | … | … | active / N/A |

---

## 4. Protection Rule (Sacred)

Future agents **MUST NOT**:

- Skip defining acceptance criteria for critical processes.  
- Invent process IDs as product law without specialization.  
- Claim process control without records/checklists where required.  
- Put secrets in process maps.  
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
**Alignment**: ISO 9001 process approach intent, `template-iso9000-qms-baseline.md`, CIAO / CIAO-Lite, harness role playbooks
