---
name: iso9000-documented-information
id: LM-ISO9000-DOCUMENTED-INFORMATION
kind: law-mold
description: >
  Portable law mold. Cite as LM-ISO9000-DOCUMENTED-INFORMATION (path secondary).
---

**file**: template-iso9000-documented-information.md  
**Status**: Active (Version 1.0.0 – Portable control of documented information for QMS)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

## 1. Purpose

This template defines how **documented information** (documents and records) is created, updated, controlled, and retained for quality management—aligned with ISO 9001 “documented information” intent and this workspace’s dual **no-hardcode / no-placeholder** policies.

**Router:** `docs/templates/requirements/template-iso9000-qms-baseline.md`  
**Related terms (when on disk):** `project-requirements`, `project-templates`, `project-skills`, `project-check-lists`, `no-hardcode-policy`, `incident-report`

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
| **ISO 9000 QMS** | `docs/terminologies/iso-9000-qms.md` | `product-law` | Documented information control |

**SSOT types used:** `meta-catalog` · `policy` · `product-law`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Document vs record (portable)

| Kind | Meaning | Examples |
|------|---------|----------|
| **Document** | Information to be maintained for operation (can be revised) | Policies, procedures, requirements, templates, skills |
| **Record** | Evidence of results achieved (historical) | Filled checklists, test reports, release notes, incident reports |

---

## 3. Core control rules

### 3.1 Creation and update

1. Identify owner and purpose before creating durable docs.  
2. Use correct **layer**:
   - Templates/skills → portable (`{{PLACEHOLDER}}` OK)  
   - Requirements → specialized product law (complete when done)  
   - Product README/CHANGELOG → real non-secret user facts  
3. Version or date material changes when traceability is required.  
4. **No hollow TBD** in specialized deliverables claimed complete.

### 3.2 Adequacy and suitability

1. Documents must be **sufficient** for the work (agents and humans can execute).  
2. Inventory honesty: do not list files that are not on disk.  
3. Genesis empty requirements/incidents are valid—state emptiness honestly.

### 3.3 Control of changes

1. Security- or quality-impacting doc changes go through Plan/Review as appropriate.  
2. Superseded documents are marked deprecated/superseded or removed with intent.  
3. Product source cites **live** `requirement-*.md` only—not templates/skills as law.

### 3.4 Distribution and access

1. Authoritative copies live in agreed paths (`docs/`, product root user docs).  
2. Do not scatter conflicting “shadow” procedure copies.  
3. Restrict access to records containing sensitive data (prefer redaction in git).

### 3.5 Retention and disposition

1. Define retention for quality records when specializing (e.g. filled checklists, release evidence).  
2. Dispose securely when retention ends (especially if any sensitive content existed).  
3. **Never** retain secrets in QMS records.

### 3.6 External origin documents

1. Identify standards, customer specs, upstream docs used as inputs.  
2. Control versions of external inputs that affect product acceptance.  
3. Do not re-host full copyrighted standards as a substitute for licensed use.

---

## 4. Workspace mapping (default)

| QMS documented info | Default location |
|---------------------|------------------|
| Product law | `docs/requirements/requirement-*.md`, `index.md` |
| Portable patterns | `docs/templates/**` |
| Agent procedures | `docs/skills/**` |
| Glossary | `docs/terminologies/**` |
| Blank quality gates | `docs/templates/checklists/**` |
| Filled quality records | `docs/checklists/**` |
| Process failures | `docs/incidents/**` |
| User product docs | Root `README.md`, `CHANGELOG.md` |
| Agent operating contract | `AGENTS.md` |

---

## 5. Protection Rule (Sacred)

Future agents **MUST NOT**:

- Claim document control while inventories cite missing files.  
- Leave unfinished placeholders in specialized QMS deliverables marked done.  
- Put secrets into quality records.  
- Use templates as finished product law.  
- Dump full copyrighted ISO text into the repo.  
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
**Alignment**: ISO 9001 documented information intent, dual no-hardcode/no-placeholder policies, `template-iso9000-qms-baseline.md`, CIAO / CIAO-Lite
