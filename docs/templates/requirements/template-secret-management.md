---
name: secret-management
id: LM-SECRET-MANAGEMENT
kind: law-mold
description: >
  Portable law mold. Cite as LM-SECRET-MANAGEMENT (path secondary).
---

**file**: template-secret-management.md
**Status**: Active (Version 1.0.0 – New Generalized Template)
**Project**: Any CIAO-Lite Project (reusable template)
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

## 1. Purpose

This template defines the recommended practices for handling secrets and sensitive configuration in CIAO-Lite CLI tools.

Proper secret management is critical to prevent accidental exposure of passwords, API keys, tokens, certificates, and other sensitive data.

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
| **Avoid-file-leaks policy** | `docs/terminologies/avoid-file-leaks-policy.md` | `policy` | No secrets on git surface |

**SSOT types used:** `meta-catalog` · `policy`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Core Requirements

### 2.1 Secrets Must Never Be Logged
- The CLI **must never** log or print secret values in plain text, even in debug or error messages.
- All output functions must filter or mask sensitive fields when displaying configuration.

### 2.2 Secrets Storage
- Secrets should be stored in:
  - The main configuration file (e.g. `.env`), **or**
  - A dedicated secrets file with restricted permissions (recommended: `0600`)
- The CLI should support both approaches.

### 2.3 File Permissions
- Files containing secrets (especially `.env` and dedicated secret files) **must** be created with restrictive permissions (`0600` or `0640` at most).
- The CLI should warn or enforce correct permissions when creating or modifying these files.

### 2.4 Backup Behavior
- Any file containing secrets **must** be backed up before modification (using the central backup function).
- Backup files containing secrets must also have restrictive permissions.

### 2.5 Validation Without Exposure
- The CLI may validate that required secrets are present.
- It **must not** display the actual secret values during validation or error reporting.

### 2.6 Environment Variables
- The CLI should support loading secrets from environment variables (useful for CI/CD and containers).
- Environment variables take precedence over file-based secrets when both are present.

## 3. Why This Requirement Exists (Direct CIAO Alignment)

- **CIAO Principle 1 – Caution** (https://github.com/cloudgen/ciao): Assume secrets can be accidentally exposed through logs, error messages, or incorrect file permissions.
- **CIAO Principle 4 / CIAO-Lite O · Principle 20 – Over-protect / Protect Against AI** (https://github.com/cloudgen/ciao): Strict rules around secret handling, logging, and file permissions defend against data leaks.
- **CIAO Principle 10 – Least-Privilege User** (https://github.com/cloudgen/ciao): Secrets should only be accessible to the processes and users that truly need them.

## 4. Design Principles (CIAO / CIAO-Lite)

- **Caution (CIAO Principle 1)**: Never log secrets. Always use restrictive file permissions.
- **Intentional (CIAO Principle 2)**: Clearly define where secrets are stored and how they are loaded.
- **Anti-fragile (CIAO Principle 3)**: Support multiple secret loading methods (files + environment variables) for different deployment scenarios.
- **Over-protect (CIAO Principle 4 / CIAO-Lite O · Principle 20)**: Masking, permission enforcement, and backup-before-modify reduce the blast radius of secret handling mistakes.

## 5. Protection Rule (Sacred)

**Future AI assistants, Grok, or maintainers MUST NOT**:
- Add any code that logs or prints secret values in plain text.
- Remove or weaken file permission checks for secret-containing files.
- Bypass backup before modifying files that may contain secrets.
- Display actual secret values in error messages or validation output.
- Remove support for loading secrets from environment variables.

**Violating this rule is considered a critical regression.**

---


## Design-time verification

| Gate | Artifact | Phase |
|------|----------|-------|
| Specialize → product suite or checklist | declare TP-IDs or checklist in specialized REQ | Design |
| RTM | `../tests/template-requirement-test-traceability.md` | Design |

When this mold has no executable TP family, mark **n/a** with reason in product `reviews/test-plan.md`.

**Last Updated**: 2026-06-04  
**Owner**: Security & Secrets Layer (Generalized Template)  
**Alignment**: Fully synchronized with `docs/requirements/index.md`, `docs/templates/requirements/template-defensive-practices.md`, `docs/templates/requirements/template-backup-strategy.md`, `docs/templates/requirements/template-project-folder.md`, and **CIAO Principles v2.10.2** (https://github.com/cloudgen/ciao).

---

**How to use this template**:
1. Copy to your project as `docs/templates/requirements/template-secret-management.md`.
2. Define which files in your project are considered secret-containing.
3. Implement secret masking in all output and logging functions.
4. Enforce restrictive permissions when creating `.env` or secret files.
5. Support both file-based and environment variable-based secret loading.
6. Keep the Protection Rule intact.