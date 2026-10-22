---
name: owasp-top-10
id: LM-OWASP-TOP-10
kind: law-mold
description: >
  Portable law mold. Cite as LM-OWASP-TOP-10 (path secondary).
---

**file**: template-owasp-top-10.md  
**Status**: Active (Version 1.0.0 – Portable OWASP Top 10 control patterns)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

## 1. Purpose

This template turns **OWASP Top 10** risk categories into **portable MUST/SHOULD controls** for design, implementation, and review. Category IDs follow the widely used **OWASP Top 10:2021** labels; projects **MAY** remap to a newer Top 10 edition in Implementation Notes without rewriting core intent.

**Router:** `docs/templates/requirements/template-owasp-security-baseline.md`  
**Checklist:** `docs/templates/checklists/checklist-owasp-security-review.md`  
**Reference:** [OWASP Top 10](https://owasp.org/www-project-top-ten/)

**Not for:** exploit development, payload catalogs, or bypass recipes.

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
| **OWASP app security** | `docs/terminologies/owasp-app-security.md` | `product-law` | Top 10 categories |

**SSOT types used:** `meta-catalog` · `policy` · `product-law`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. How to use this template

1. Mark each category **Applicable / Partial / N/A** for *this* system (CLI, API, web UI, installer).  
2. Promote applicable MUST items into specialized `requirement-*.md` when product law is needed.  
3. Verify with Security role + checklists on relevant diffs.  
4. Keep live secrets, hosts, and app names in Config / product README — not as universal template hardcodes.

---

## 3. Category controls (Top 10:2021 labels)

### A01 — Broken Access Control

| MUST | Detail |
|------|--------|
| Explicit authz | Every sensitive operation checks authorization, not only authentication |
| Deny by default | Missing permission → refuse (fail-closed) |
| Object-level checks | No IDOR: resource IDs from clients re-validated server-side / privileged core |
| Privilege separation | Type 0 / 1 / 2 and system-user models respected when used |

**SHOULD:** Centralize authorization decisions (policy module / middleware), audit denials at appropriate log level without leaking secrets.

---

### A02 — Cryptographic Failures

| MUST | Detail |
|------|--------|
| No homemade crypto | Use vetted libraries and protocols |
| TLS in transit | When data crosses untrusted networks, require modern TLS (see SSL template) |
| Secrets at rest | Restrict permissions; prefer OS/secret-store patterns |
| No secrets in logs | Mask tokens, passwords, keys in all channels |

**MUST NOT:** Commit private keys, paste real certs into docs, or log session tokens.

---

### A03 — Injection

| MUST | Detail |
|------|--------|
| Boundary validation | Validate type, length, charset, path safety at trust boundaries |
| Safe composition | Prefer APIs that separate code from data (parameterized queries, argv arrays, structured APIs) |
| Shell safety | Never build shell command lines from untrusted strings without strict allowlists |
| Output encoding | Encode for the target context (HTML/JSON/shell) when rendering untrusted data |

**MUST NOT:** Document or ship working exploit payloads as “tests” outside isolated test doubles.

---

### A04 — Insecure Design

| MUST | Detail |
|------|--------|
| Threat-aware design | Identify trust boundaries before features ship |
| Safe defaults | Secure-by-default config; debug off on production paths |
| Explicit abuse cases | Document refused actions (rate limits, confirmations for high blast radius) |

**SHOULD:** Use ASVS selection (`template-owasp-asvs.md`) to size verification depth.

---

### A05 — Security Misconfiguration

| MUST | Detail |
|------|--------|
| Hardened defaults | No world-writable secret files; no open admin without auth |
| Config SSOT | Security-relevant flags live in Config — not scattered magic strings |
| Error honesty | Fail loud for operators; do not leak stack/secrets to clients |

**SHOULD:** Inventory enabled features/ports/interfaces; disable unused surfaces.

---

### A06 — Vulnerable and Outdated Components

| MUST | Detail |
|------|--------|
| Justified dependencies | New deps require reason + pin policy |
| Known critical CVEs | Do not ignore fixable critical issues in runtime path without documented risk acceptance |
| Install integrity | When online install/self-update is claimed, verify digests |

**SHOULD:** Prefer minimal dependency surface for CLIs and installers.

---

### A07 — Identification and Authentication Failures

| MUST (when auth exists) | Detail |
|-------------------------|--------|
| Strong session/token handling | Secure storage, rotation, expiry per design |
| Credential protection | Never store plaintext passwords; never log credentials |
| Brute-force resistance | Rate limit / lockout / backoff where interactive auth exists |

**N/A** is allowed for pure local Type 0 tools with no identity system — state N/A explicitly when specializing.

---

### A08 — Software and Data Integrity Failures

| MUST | Detail |
|------|--------|
| Integrity of updates | Checksum/signature for self-update / remote install when advertised |
| Atomic publish | Stage → verify → rename for binaries and critical state |
| CI/supply awareness | Do not execute untrusted remote scripts without integrity and least privilege |

---

### A09 — Security Logging and Monitoring Failures

| MUST | Detail |
|------|--------|
| Security-relevant events | Auth failures, authz denials, integrity failures logged appropriately |
| Channel SSOT | Diagnostics on stderr / central logger — not mixed into machine JSON stdout |
| No secret leakage | Logs redact secrets and high-sensitivity PII |

**SHOULD:** Support DEBUG switch without dumping secrets when enabled.

---

### A10 — Server-Side Request Forgery (SSRF)

| MUST (when outbound URL fetch exists) | Detail |
|---------------------------------------|--------|
| Allowlist / blocklist | Restrict destinations for user-controlled URLs |
| No raw follow of untrusted redirects | Validate final destination policy |
| Metadata protection | Block cloud metadata and link-local ranges when policy requires |

**N/A** for tools with no user-influenced outbound HTTP — document N/A when specializing.

---

## 4. Applicability matrix (complete when specializing)

| ID | Applicable? | Notes / REQ-ID |
|----|-------------|----------------|
| A01 | Yes / Partial / N/A | |
| A02 | Yes / Partial / N/A | |
| A03 | Yes / Partial / N/A | |
| A04 | Yes / Partial / N/A | |
| A05 | Yes / Partial / N/A | |
| A06 | Yes / Partial / N/A | |
| A07 | Yes / Partial / N/A | |
| A08 | Yes / Partial / N/A | |
| A09 | Yes / Partial / N/A | |
| A10 | Yes / Partial / N/A | |

*(In a specialized requirement, fill every cell — no hollow blanks when claiming done.)*

---

## 5. CIAO alignment

| Principle | Mapping |
|-----------|---------|
| **Caution** | Assume hostile input and misconfig |
| **Intentional** | Explicit authz, explicit N/A, explicit threat boundaries |
| **Anti-fragile** | Safe defaults, integrity on update, least privilege |
| **Over-protect** | Fail-closed, secret masking, atomic publish |

---

## 6. Protection Rule (Sacred)

Future agents **MUST NOT**:

- Remove access-control or injection controls to “simplify.”  
- Add exploit PoCs or weaponized payloads to product trees.  
- Claim Top 10 “coverage” without applicability matrix or verification.  
- Hardcode product secrets/hosts into this template.  
- Cite this template as product-source ALIGNMENT law.

---


## Design-time verification

| Gate | Artifact | Phase |
|------|----------|-------|
| Checklist | `../checklists/checklist-owasp-security-review.md` | Design + Review |
| Skill | `skill-owasp-security-review` | Review |

**RTM:** `../tests/template-requirement-test-traceability.md` §4.

**Last Updated**: 2026-07-12  
**Owner**: {{OWNER}}  
**Alignment**: [OWASP Top 10](https://owasp.org/www-project-top-ten/), `template-owasp-security-baseline.md`, `template-owasp-asvs.md`, `template-secret-management.md`, CIAO / CIAO-Lite
