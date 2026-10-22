---
name: owasp-asvs
id: LM-OWASP-ASVS
kind: law-mold
description: >
  Portable law mold. Cite as LM-OWASP-ASVS (path secondary).
---

**file**: template-owasp-asvs.md  
**Status**: Active (Version 1.0.0 – Portable ASVS selection and verification patterns)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

## 1. Purpose

This template defines how a project **selects and applies OWASP Application Security Verification Standard (ASVS)** levels as a structured verification approach—without copying the entire ASVS catalog into every repo or inventing compliance theater.

**Reference:** [OWASP ASVS](https://owasp.org/www-project-application-security-verification-standard/)  
**Router:** `docs/templates/requirements/template-owasp-security-baseline.md`  
**Companion:** `docs/templates/requirements/template-owasp-top-10.md`

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
| **OWASP app security** | `docs/terminologies/owasp-app-security.md` | `product-law` | ASVS levels |

**SSOT types used:** `meta-catalog` · `policy` · `product-law`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Verification levels (portable summary)

| Level | Intent | Typical systems |
|-------|--------|-----------------|
| **L1** | Opportunistic / baseline | Low-sensitivity tools, internal utilities, many CLIs |
| **L2** | Standard | Applications handling personal or business-sensitive data, multi-user APIs |
| **L3** | Advanced | High-value systems, critical auth/crypto, regulated or high-impact services |

**Rule:** Choose **one target level** (or an explicit subset of chapters) in specialized requirements. **Do not** claim L2/L3 without recorded evidence.

---

## 3. Core rules

### 3.1 Selection

1. Document **target level** (`L1` / `L2` / `L3`) or **custom subset** with rationale.  
2. Map selected ASVS chapters to product surfaces (web, API, CLI, installer, admin).  
3. Mark controls **In scope / Out of scope** with owners.  
4. Prefer living ASVS text from the official project for exact requirement IDs when specializing—**do not invent ASVS IDs**.

### 3.2 Evidence

| Claim | Minimum evidence |
|-------|------------------|
| Control implemented | Code/config path + test or review note |
| Control N/A | Written justification (no hollow “N/A”) |
| Level achieved | Filled checklist / verification record under `docs/checklists/` when persistence is required |

### 3.3 CIAO + ASVS

| ASVS concern | CIAO complement |
|--------------|-----------------|
| V2 Authentication | Caution + fail-closed |
| V4 Access control | Least privilege, explicit authz |
| V6 Cryptography | No homemade crypto; secret management template |
| V10 Malicious code / supply chain | Dependency pinning; install integrity |
| V12 Files & resources | Defensive paths, temp safety |
| V14 Configuration | Safe defaults, Config SSOT |

### 3.4 Agent workflow

1. **Plan** selects level/subset.  
2. **Implement** only in-scope controls.  
3. **Security** verifies with `checklist-owasp-security-review.md` + `security-review.md`.  
4. **Never** paste full ASVS prose into product source as ALIGNMENT; specialize into `requirement-*.md` if durable law is needed.

---

## 4. Selection table (fill when specializing)

| Field | Value |
|-------|--------|
| Target level | L1 / L2 / L3 / custom subset |
| Rationale | … |
| In-scope chapters | … |
| Out-of-scope chapters + why | … |
| Related Top 10 categories | … |
| Verification record path | `docs/checklists/…` or session-only |

*(Specialized requirements: complete every row — no TBD.)*

---

## 5. Protection Rule (Sacred)

Future agents **MUST NOT**:

- Claim ASVS L2/L3 compliance without evidence.  
- Invent ASVS requirement IDs not present in the official standard.  
- Expand scope silently to “all of ASVS” without Plan/Security agreement.  
- Use ASVS as a reason to embed secrets or product hardcodes into templates.  
- Cite this template as product-source behavioral law.

---


## Design-time verification

| Gate | Artifact | Phase |
|------|----------|-------|
| Checklist | `../checklists/checklist-owasp-security-review.md` | Design + Review |
| Skill | `skill-owasp-security-review` | Review |

**RTM:** `../tests/template-requirement-test-traceability.md` §4.

**Last Updated**: 2026-07-12  
**Owner**: {{OWNER}}  
**Alignment**: [OWASP ASVS](https://owasp.org/www-project-application-security-verification-standard/), `template-owasp-security-baseline.md`, `template-owasp-top-10.md`, CIAO / CIAO-Lite
