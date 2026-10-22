---
name: environment-variables
id: LM-ENVIRONMENT-VARIABLES
kind: law-mold
description: >
  Portable law mold. Cite as LM-ENVIRONMENT-VARIABLES (path secondary).
---

**file**: docs/templates/requirements/template-environment-variables.md
**Status**: Active (Version 1.0.0 – Generalized template; replaces obsolete installer-era template form docs/templates/requirements/template-environment-variables.md)
**Project**: {{APP_NAME}} – {{PLATFORM_NAME}} Platform Management CLI
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

# Template: Environment Variable Handling (CIAO Defensive)

## 1. Purpose

This template defines the defensive rules for using environment variables in CIAO-Lite projects. It ensures that configuration via environment variables is secure, auditable, and does not bypass the centralized configuration and secret-handling mechanisms.

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
| **Appname policy** | `docs/terminologies/appname-policy.md` | `identity-runtime` | APP_NAME and related env |
| **Script URL** | `docs/terminologies/script-url.md` | `install-channel` | Channel env when online |

**SSOT types used:** `identity-runtime` · `install-channel` · `meta-catalog` · `policy`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Core Rules / Requirements (Mandatory)

### 2.1 Centralized Access to Environment Variables

- Direct access to `process.env` (or equivalent) outside of the designated configuration module is **forbidden**.
- All environment variable reading **MUST** go through `{{CONFIG_MODULE}}` (or a dedicated, well-documented environment loader).
- The `{{CONFIG_MODULE}}` is responsible for:
  - Defining the full list of supported environment variables.
  - Applying safe defaults.
  - Enforcing precedence rules (CLI flags > environment variables > config file > defaults).
  - Validating and sanitizing values where appropriate.

### 2.2 Sensitive Values

- Environment variables that may contain secrets (tokens, passwords, API keys, etc.) **MUST NOT** be logged at any level (including debug).
- The `{{CONFIG_MODULE}}` must treat sensitive variables specially (e.g., never include them in `about` output or structured diagnostics unless explicitly redacted).
- When possible, prefer loading secrets from more secure mechanisms (e.g., secret managers, encrypted files) rather than plain environment variables.

### 2.2.1 Session display (`$DISPLAY`)

- `$DISPLAY` is **inherited session env** (SSH X11 forwarding / local X), not a product Config default.  
- **MUST NOT** hard-code a display id (`localhost:11.0`, `localhost:10.0`, `:0`, `:1`) as a ship-unit or mold default.  
- GUI diagnostics (`about`) **MUST** print the live value (or unset). Tests **MAY** inject `DISPLAY` for isolation; that fixture is not product law.  
- **`PO-NO-HARDCODE`**.

### 2.3 Documentation Requirement

- Every supported environment variable **MUST** be documented in the `{{HELP_MODULE}}` and/or `{{ABOUT_MODULE}}`.
- The documentation must clearly state:
  - Purpose of the variable
  - Expected format / example (without real secrets)
  - Precedence relative to other configuration sources
  - Whether the value is considered sensitive

### 2.4 Why This Requirement Exists (Direct CIAO Alignment)
- **CIAO Principle 1 – Caution** (https://github.com/cloudgen/ciao): Environment variables are a common source of configuration errors, secret leakage, and inconsistent behavior across environments.
- **CIAO Principle 2 – Intentional** (https://github.com/cloudgen/ciao): Centralizing access makes configuration behavior predictable and auditable.
- **CIAO Principle 4 / CIAO-Lite O · Principle 20 – Over-protect / Protect Against AI** (https://github.com/cloudgen/ciao): Explicit rules against direct `process.env` access and requirements for documentation protect both security and maintainability.

## 3. Design Principles (CIAO / CIAO-Lite)

- **Caution** (CIAO Principle 1): Treat environment variables as untrusted input that requires validation and safe defaults.
- **Intentional** (CIAO Principle 2): Every environment variable has a clear owner, documentation, and access path.
- **Anti-fragile** (CIAO Principle 3): The system behaves consistently whether running interactively, in CI/CD, or inside containers.
- **Over-protect** (CIAO Principle 4 / CIAO-Lite O · Principle 20): Strict centralization and documentation requirements defend against configuration drift and secret leakage.

## 4. Protection Rule (Sacred)

**Future AI assistants, Grok, or maintainers MUST NOT**:
- Read environment variables directly via `process.env` (or equivalent) outside the approved `{{CONFIG_MODULE}}`.
- Introduce new environment variables without documenting them in the Help/About modules and updating the centralized loader.
- Log or expose values from sensitive environment variables.
- Weaken or bypass the precedence rules defined in `{{CONFIG_MODULE}}`.
- Remove or weaken this template's rules when specializing it for a concrete project.

Violating this rule is considered a **critical regression**.

---


## Design-time verification

| Gate | Artifact | Phase |
|------|----------|-------|
| Specialize → product suite or checklist | declare TP-IDs or checklist in specialized REQ | Design |
| RTM | `../tests/template-requirement-test-traceability.md` | Design |

When this mold has no executable TP family, mark **n/a** with reason in product `reviews/test-plan.md`.

**Last Updated**: 2026-06-09 (Generalized environment variable handling template created from obsolete requirement)
**Owner**: Configuration Layer
**Alignment**: Fully synchronized with `docs/requirements/index.md`, `docs/templates/requirements/template-configuration-management.md`, `docs/templates/requirements/template-output-requirements.md`, `AGENTS.md` (CIAO Protection Zones) and specialized requirements, and **CIAO Principles 1, 2, 4, 20 (v2.10.2)** (https://github.com/cloudgen/ciao).

---

**How to specialize this template**:
1. Copy to `requirement-environment-variables.md` (target name after specialization; not a live file until created).
2. Define the concrete list of supported environment variables in `{{CONFIG_MODULE}}`.
3. Update `{{HELP_MODULE}}` and `{{ABOUT_MODULE}}` with documentation.
4. After specialization, update `docs/requirements/index.md` with the specialized `requirement-*.md` row only (never list this template path in the registry).
