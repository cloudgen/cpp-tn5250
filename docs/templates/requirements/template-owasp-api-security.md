---
name: owasp-api-security
id: LM-OWASP-API-SECURITY
kind: law-mold
description: >
  Portable law mold. Cite as LM-OWASP-API-SECURITY (path secondary).
---

**file**: template-owasp-api-security.md  
**Status**: Active (Version 1.0.0 – Portable OWASP API Security control patterns)  
**Project**: Any CIAO-Lite Project exposing or consuming HTTP APIs (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

## 1. Purpose

This template defines portable controls aligned with **OWASP API Security Top 10** thinking for services and **API clients** (including Node platform CLIs that call remote APIs).

**Reference:** [OWASP API Security Project](https://owasp.org/www-project-api-security/)  
**Router:** `docs/templates/requirements/template-owasp-security-baseline.md`  
**Related:** `docs/templates/requirements/template-nodejs-api-client.md`, `docs/skills/skill-upstream-git-analysis.md` (when on disk), `template-owasp-top-10.md`

**N/A:** Pure local CLIs with no HTTP API surface — state N/A when specializing.

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
| **OWASP app security** | `docs/terminologies/owasp-app-security.md` | `product-law` | API Top 10 framing |

**SSOT types used:** `meta-catalog` · `policy` · `product-law`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Control patterns (portable labels)

Use official API Top 10 edition labels from the OWASP project when specializing. Core intents below remain stable even if numbering shifts.

### API1 — Broken object level authorization

- **MUST** re-check object ownership/permission on every access by ID.  
- **MUST NOT** trust client-supplied tenant/user IDs alone.

### API2 — Broken authentication

- **MUST** protect tokens/keys; never log them.  
- **MUST** use short-lived tokens / rotation where design allows.  
- **MUST NOT** accept “auth optional” on sensitive routes without explicit public design.

### API3 — Broken object property level authorization

- **MUST** filter response fields and reject mass-assignment of privileged properties.  
- **SHOULD** use allowlisted DTOs / schemas for write paths.

### API4 — Unrestricted resource consumption

- **MUST** apply rate limits / timeouts / size limits on expensive operations where exposure exists.  
- **SHOULD** bound retries and pagination.

### API5 — Broken function level authorization

- **MUST** enforce role/permission checks on admin and privileged functions.  
- **MUST NOT** hide privileged URLs as the only protection.

### API6 — Unrestricted access to sensitive business flows

- **MUST** protect high-value flows (signup, reset, purchase, install channel change) against automation abuse as required by threat model.  
- **SHOULD** require step-up auth or confirmation for high blast-radius actions.

### API7 — Server side request forgery

- **MUST** constrain user-influenced outbound URLs (allowlist / block private ranges as policy requires).  
- Align with Top 10 A10 controls in `template-owasp-top-10.md`.

### API8 — Security misconfiguration

- **MUST** disable debug in production paths; secure CORS/headers as applicable.  
- **MUST** keep security config in SSOT modules.

### API9 — Improper inventory management

- **MUST** document exposed API versions/endpoints in product docs when shipping.  
- **SHOULD** retire shadow/zombie endpoints deliberately.

### API10 — Unsafe consumption of APIs

- **MUST** validate/sanitize data from upstream APIs before use in security decisions.  
- **MUST** use official clients when policy requires (`skill-upstream-git-analysis` for platform CLIs).  
- **MUST NOT** trust upstream blindly for authz or injection-sensitive sinks.

---

## 3. CLI / client-specific rules

| Rule | Detail |
|------|--------|
| Upstream analysis | Before binding new remote commands, analyze official client/API when required |
| Output SSOT | Never print tokens; JSON mode must not leak secrets |
| Config SSOT | Base URL, auth mode, timeouts from Config — not scattered literals |
| Errors | Map upstream errors without dumping raw credentials or full sensitive payloads |

---

## 4. Applicability matrix (fill when specializing)

| Control area | Applicable? | Notes / REQ-ID |
|--------------|-------------|----------------|
| Object-level authz | Yes / Partial / N/A | |
| Authentication | Yes / Partial / N/A | |
| Property-level authz | Yes / Partial / N/A | |
| Resource consumption | Yes / Partial / N/A | |
| Function-level authz | Yes / Partial / N/A | |
| Business flow abuse | Yes / Partial / N/A | |
| SSRF | Yes / Partial / N/A | |
| Misconfiguration | Yes / Partial / N/A | |
| Inventory | Yes / Partial / N/A | |
| Unsafe API consumption | Yes / Partial / N/A | |

---

## 5. Protection Rule (Sacred)

Future agents **MUST NOT**:

- Build exploit PoCs against APIs as deliverables.  
- Log or commit API tokens.  
- Skip object-level checks “because the UI hides the ID.”  
- Invent official API behavior without upstream evidence when analysis is required.  
- Cite this template as product-source law.

---


## Design-time verification

| Gate | Artifact | Phase |
|------|----------|-------|
| Checklist | `../checklists/checklist-owasp-security-review.md` | Design + Review |
| Skill | `skill-owasp-security-review` | Review |

**RTM:** `../tests/template-requirement-test-traceability.md` §4.

**Last Updated**: 2026-07-12  
**Owner**: {{OWNER}}  
**Alignment**: [OWASP API Security](https://owasp.org/www-project-api-security/), `template-owasp-security-baseline.md`, `template-owasp-top-10.md`, `template-secret-management.md`, CIAO / CIAO-Lite
