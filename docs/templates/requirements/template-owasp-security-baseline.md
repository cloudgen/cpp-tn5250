---
name: owasp-security-baseline
id: LM-OWASP-SECURITY-BASELINE
kind: law-mold
description: >
  Portable law mold. Cite as LM-OWASP-SECURITY-BASELINE (path secondary).
---

**file**: template-owasp-security-baseline.md  
**Status**: Active (Version 1.0.0 – OWASP track router / security baseline)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

## 1. Purpose

This template is the **entry point for the OWASP-related template track**. It defines how agents map **portable security requirements** to project specialization without hardcoding product names, hosts, or secrets, and without teaching exploitation.

**Related templates (load as needed):**

| Template | Role |
|----------|------|
| `docs/templates/requirements/template-owasp-top-10.md` | Web / app risk categories (Top 10) |
| `docs/templates/requirements/template-owasp-asvs.md` | Verification levels and requirement selection |
| `docs/templates/requirements/template-owasp-api-security.md` | API-focused Top 10 controls |
| `docs/templates/requirements/template-owasp-secure-coding.md` | Secure coding practices (agent + human) |
| `docs/templates/requirements/template-secret-management.md` | Secrets storage / masking |
| `docs/templates/requirements/template-least-privilege-user.md` (**`LM-LEAST-PRIVILEGE-USER`**) | OS least privilege (product/CLI) |
| `docs/templates/requirements/template-three-layer-privilege-model.md` (**`LM-THREE-LAYER-PRIVILEGE-MODEL`**) | Type 0 / 1 / 2 privilege architecture |
| `docs/policies/policy-least-privilege.md` | Harness least privilege + **avoid LLM escape** (local-default, egress whitelist) |
| `docs/templates/checklists/checklist-least-privilege.md` (**`CL-LEAST-PRIVILEGE`**) | Privilege gate |
| `docs/templates/checklists/checklist-llm-escape.md` (**`CL-LLM-ESCAPE`**) | Escape-activity gate (`E-*`) |
| `docs/templates/requirements/template-ssl-certificate-management.md` | TLS / certificate lifecycle |
| `docs/templates/checklists/security-review.md` (**`CL-SECURITY-REVIEW`**) | General security checklist (companions CL-LEAST-PRIVILEGE / CL-LLM-ESCAPE when in scope) |
| `docs/templates/checklists/checklist-owasp-security-review.md` | OWASP-oriented blank checklist |
| `docs/templates/requirements/template-iso27001-isms-baseline.md` | ISMS / ISO 27001 process companion (governance, not a substitute for OWASP) |
| `docs/templates/checklists/checklist-iso27001-control-review.md` | ISMS control / SoA review checklist |
| `docs/skills/skill-owasp-security-review.md` | Agent harness: OWASP review Pass/Revise/Block |
| `docs/terminologies/owasp-app-security.md` | Shared language: Top 10 / ASVS / API vs ISMS/QMS |
| `docs/skills/README.md` | OWASP ↔ skill mapping (categories → coding/install/API skills) |

**Agent review path:** Run **`SK-OWASP-SECURITY-REVIEW`** (loads this baseline + OWASP checklist + **`CL-SECURITY-REVIEW`**). When privilege model, system user, Type 0/1/2, or agent egress is in scope, also complete **`CL-LEAST-PRIVILEGE`** and **`CL-LLM-ESCAPE`** per [`policy-least-privilege.md`](../../policies/policy-least-privilege.md). For ISMS process also run **`SK-ISO27001-ISMS-REVIEW`** (separate verdict).

**Public references (philosophy / standards — not product hosts):**  
[OWASP](https://owasp.org/), [OWASP Top 10](https://owasp.org/www-project-top-ten/), [OWASP ASVS](https://owasp.org/www-project-application-security-verification-standard/), [OWASP API Security](https://owasp.org/www-project-api-security/), [CIAO](https://github.com/cloudgen/ciao)

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
| **OWASP app security** | `docs/terminologies/owasp-app-security.md` | `product-law` | Primary OWASP baseline term |
| **Least privilege** | `docs/terminologies/least-privilege.md` | `policy` | Runtime + agent power envelope |
| **LLM escape** | `docs/terminologies/llm-escape.md` | `policy` | Unapproved egress/privilege activities (`E-*`) |
| **LLM pain point** | `docs/terminologies/llm-pain-point.md` | `mention-only` | `PP-A-08` / `PP-A-16` / `PP-B-22` when reviewing |

**SSOT types used:** `mention-only` · `meta-catalog` · `policy` · `product-law`

**Policies (normative bodies):** `docs/policies/policy-least-privilege.md` · `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md` · `docs/policies/policy-harness-id-notation.md`

## 2. Scope

| In scope | Out of scope |
|----------|--------------|
| Portable MUST/SHOULD security controls for apps, CLIs, APIs, installers | Step-by-step exploit or attack recipes |
| Mapping OWASP categories → CIAO / project checklists | Freezing one product’s URL, tenant, or brand as universal law |
| Specialization into `requirement-*.md` when product law is needed | Dummy secrets to “look complete” |
| Review gates for agents (Security role) | Claiming ASVS L3 without evidence |

---

## 3. Core baseline rules (all projects)

### 3.1 Threat awareness

1. **Assume** untrusted input, hostile networks, misconfigured privileges, and AI-assisted regressions.  
2. Prefer **fail-closed** for authz, crypto, and secret handling.  
3. Prefer **least privilege** for runtime identities (three-layer + system-user terms; harness **`policy-least-privilege`**; gates **`CL-LEAST-PRIVILEGE`** / **`CL-LLM-ESCAPE`** when agent power or egress is in scope).

### 3.2 Secrets and sensitive data

1. **Never** commit real or toy secrets (`password123`, `api_key_here`, `changeme`).  
2. **Never** log secrets or return them in errors.  
3. Store secrets via env / secret store / `0600` files — see `template-secret-management.md`.

### 3.3 Input and injection

1. Validate and sanitize all untrusted input at trust boundaries.  
2. Prefer parameterized APIs over string-built shell/SQL/LDAP/OS commands.  
3. Treat path, URL, and header values as untrusted unless proven otherwise.

### 3.4 Authentication and session (when applicable)

1. Use proven libraries; do not invent crypto protocols.  
2. Enforce explicit authorization on every sensitive action (no IDOR by default).  
3. Session/token storage and rotation follow project Selection / Config SSOT — not scattered literals.

### 3.5 Supply chain and install

1. Pin dependencies per project norms; justify new packages.  
2. Online install / self-update must use integrity checks when claimed (`template-online-install.md`, online-install skill when on disk).  
3. Separate install privilege (Type 1) from day-to-day operations (Type 0 / Type 2).

### 3.6 Documentation honesty

1. Product root **README/CHANGELOG** may state real non-secret security-relevant install facts (**excluded from no-hardcode**).  
2. Templates/skills stay portable with `{{PLACEHOLDER}}`.  
3. Product source cites **live** `requirement-*.md` only — never `template-owasp-*` as ALIGNMENT law.

---

## 4. How to specialize (requirements)

When creating product law:

1. Choose target **ASVS level** or control subset (`template-owasp-asvs.md`).  
2. Map applicable **Top 10 / API Top 10** categories to MUST rules (`template-owasp-top-10.md`, `template-owasp-api-security.md`).  
3. Fill **Selection / defaults** for app type, path choices, privilege actors per `docs/terminologies/project-requirements.md` when present.  
4. Register `requirement-*.md` in `docs/requirements/index.md` when files exist.  
5. Run `checklist-owasp-security-review.md` + `security-review.md` on relevant changes.

**Empty requirements (genesis) are valid** — use these templates as design patterns until specialized.

---

## 5. Agent role map

| Role | Duty |
|------|------|
| **Explore** | Identify trust boundaries, auth surfaces, secret paths, network exposure |
| **Plan** | Select OWASP/ASVS scope; open security requirements if durable intent |
| **Implement** | Apply secure-coding template; no exploit code; surgical changes |
| **Review** | Checklist-driven; dual no-placeholder / no-hardcode |
| **Security** | Own OWASP checklist verdict; block on secrets, authz gaps, injection |

---

## 6. Protection Rule (Sacred)

Future agents **MUST NOT**:

1. Turn OWASP templates into **attack how-tos** or exploit PoCs.  
2. Invent missing `requirement-*` / `skill-*` / `template-*` paths.  
3. Paste `template-owasp-*` into product source as behavioral authority.  
4. Ship dummy secrets or toy security “complete” configs.  
5. Claim full ASVS L2/L3 compliance without a filled verification record.  
6. Weaken least-privilege or secret-masking rules “for simplicity.”

---


## Design-time verification

| Gate | Artifact | Phase |
|------|----------|-------|
| Checklist | `../checklists/checklist-owasp-security-review.md` | Design + Review |
| Skill | `skill-owasp-security-review` | Review |

**RTM:** `../tests/template-requirement-test-traceability.md` §4.

**Last Updated**: 2026-07-12  
**Owner**: {{OWNER}}  
**Alignment**: OWASP public projects (Top 10, ASVS, API Security), CIAO / CIAO-Lite, `docs/templates/requirements/template-secret-management.md`, `template-defensive-practices.md`, `docs/templates/checklists/security-review.md`, `docs/policies/policy-no-hardcode.md`
