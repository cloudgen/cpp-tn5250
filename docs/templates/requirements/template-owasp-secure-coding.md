---
name: owasp-secure-coding
id: LM-OWASP-SECURE-CODING
kind: law-mold
description: >
  Portable law mold. Cite as LM-OWASP-SECURE-CODING (path secondary).
---

**file**: template-owasp-secure-coding.md  
**Status**: Active (Version 1.0.0 – Secure coding practices for agents and humans)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

## 1. Purpose

This template defines **secure coding practices** that implement OWASP-oriented controls in day-to-day code changes. It complements language coding skills (`skill-sh-script-coding`, `skill-python-cli-coding`, `skill-nodejs-cli-coding` when on disk) and CIAO defensive templates.

**Router:** `docs/templates/requirements/template-owasp-security-baseline.md`  
**Related:** `template-owasp-top-10.md`, `template-defensive-practices.md`, `template-error-handling.md`, `template-secret-management.md`, `template-input` via error-handling / Top 10 A03

**Not for:** exploit tutorials or offensive tooling.

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
| **OWASP app security** | `docs/terminologies/owasp-app-security.md` | `product-law` | Secure coding controls |
| **Error handling** | `docs/terminologies/error-handling.md` | `product-law` | Safe failure modes |

**SSOT types used:** `meta-catalog` · `policy` · `product-law`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Mandatory secure coding rules

### 2.1 Input handling

1. Treat all external input as untrusted (argv, env, files, network, IPC).  
2. Validate early; reject illegal patterns with clear errors (no silent coerce to unsafe values).  
3. Use allowlists for commands, paths, and enumerations where possible.

### 2.2 Output and encoding

1. Route user/diagnostic output through project output SSOT (`out_*` / Output module).  
2. Never mix secrets into stdout JSON payloads.  
3. Encode for context when emitting data into HTML/shell/logs.

### 2.3 Commands and queries

1. Prefer argument arrays / structured APIs over shell string concatenation.  
2. Prefer parameterized queries / official SDK calls over string-built queries.  
3. Gate dangerous operations (delete, privilege change, remote install) behind force/confirm policy appropriate to interactive vs noninteractive mode.

### 2.4 Secrets and crypto

1. Load secrets from env/secret files/stores; never hardcode.  
2. Mask secrets in debug.  
3. Do not implement novel cryptography; use platform libraries.

### 2.5 Files and temp

1. Use `mktemp` / safe temp APIs; no predictable sensitive temp names.  
2. Atomic publish for binaries and critical state.  
3. Restrictive permissions on secret-bearing files (`0600` class).

### 2.6 Authz and privilege

1. Check authorization next to the sensitive operation (not only at UI edge).  
2. Drop privileges after Type 1 bootstrap; Type 2 as system user when required.  
3. Avoid running routine ops as root.

### 2.7 Dependencies and remote code

1. Minimize new dependencies; pin versions per project policy.  
2. Verify integrity of remote install/update artifacts when claimed.  
3. Do not `eval` untrusted remote content.

### 2.8 Product-source documentation

1. Source `ALIGNMENT` / `See` cites **live** `requirement-*.md` only.  
2. Do not cite `template-owasp-*` or skills as product law.  
3. Agents still **load** these templates while coding.

---

## 3. Language notes (pointers)

| Track | Prefer loading |
|-------|----------------|
| POSIX shell | `template-shell-script-coding.md`, online-install skill when install-related |
| Python | `template-python-*` secure I/O and packaging practices |
| Node | `template-nodejs-*`, official API client + upstream analysis when remote |

---

## 4. Review hooks

Before claiming done on security-sensitive changes:

1. `docs/templates/checklists/security-review.md`  
2. `docs/templates/checklists/checklist-owasp-security-review.md`  
3. Language implementation checklist / CIAO implementation checklist as applicable  

---

## 5. Protection Rule (Sacred)

Future agents **MUST NOT**:

- Introduce string-built shell/SQL with untrusted input.  
- Log or commit secrets (real or dummy).  
- Disable authz/validation for convenience.  
- Add exploit PoCs to the product tree.  
- Strip Protection Zones that enforce safety checks.  
- Cite this template as product-source ALIGNMENT.

---


## Design-time verification

| Gate | Artifact | Phase |
|------|----------|-------|
| Checklist | `../checklists/checklist-owasp-security-review.md` | Design + Review |
| Skill | `skill-owasp-security-review` | Review |

**RTM:** `../tests/template-requirement-test-traceability.md` §4.

**Last Updated**: 2026-07-12  
**Owner**: {{OWNER}}  
**Alignment**: OWASP secure coding intent, `template-owasp-top-10.md`, `template-defensive-practices.md`, `template-secret-management.md`, CIAO / CIAO-Lite
