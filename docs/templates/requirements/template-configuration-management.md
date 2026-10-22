---
name: configuration-management
id: LM-CONFIGURATION-MANAGEMENT
kind: law-mold
description: >
  Portable law mold. Cite as LM-CONFIGURATION-MANAGEMENT (path secondary).
---

**file**: docs/templates/requirements/template-configuration-management.md
**Status**: Active (Version 1.0.0 – Generalized template; replaces obsolete installer-era requirement)
**Project**: {{APP_NAME}} – {{PLATFORM_NAME}} Platform Management CLI
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

# Template: Configuration Management (CIAO Defensive)

## 1. Purpose

This template defines the defensive approach to configuration management for CIAO-Lite projects. It ensures that all persistent configuration and state (session tokens, endpoints, user identity, and any additional project-specific settings) are handled in a secure, centralized, and auditable manner.

For pure {{APP_NAME}}-style Node.js platform clients, the primary configuration artifact is the authenticated session. The template also provides extension points for projects that may later incorporate additional configuration files or self-host components.

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
| **Ship unit** | `docs/terminologies/ship-unit.md` | `identity-runtime` | Config on ship unit |
| **Appname policy** | `docs/terminologies/appname-policy.md` | `identity-runtime` | APP_NAME identity |

**SSOT types used:** `identity-runtime` · `meta-catalog` · `policy`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Core Rules / Requirements (Mandatory)

### 2.1 Centralized Ownership of Configuration State

All configuration and persistent state **MUST** be owned and accessed through well-defined modules:

| Concern                    | Owner Module                  | Rules |
|---------------------------|-------------------------------|-------|
| App identity, paths, flags, modes | `{{CONFIG_MODULE}}`          | Single source of truth for `app_name`, `project_dir`, `isJson`, `isQuiet`, `isDebug` |
| Authentication state (token, endpoint, user) | `{{SESSION_MODULE}}`     | Never read/write session file directly; always use `load()`, `set()`, `save()`, `clear()` |
| Additional project config | Dedicated config loader (if needed) | Must go through `{{CONFIG_MODULE}}` or a clearly documented extension |

### 2.2 Session / Auth Configuration (Current Primary Scope)

- The session file (`{{SESSION_FILE}}`) located under `{{PROJECT_DIR}}` is the **only** persistent authentication configuration in the current platform client scope.
- It **MUST** be created with restrictive permissions (`0600`).
- All read/write operations must go exclusively through the `{{SESSION_MODULE}}`.
- The file format (e.g. `KEY=VALUE` lines) must be treated as an implementation detail of the Session module — never parsed directly elsewhere.

### 2.3 Safe Defaults and Environment Handling

- All configuration values must have safe, explicit defaults inside the owning module.
- Environment variables may be used for overrides, but the module must document precedence clearly (e.g. CLI flag > env var > config file > default).
- Never rely on implicit current-working-directory behavior for locating configuration.

### 2.4 Why This Requirement Exists (Direct CIAO Alignment)
- **CIAO Principle 2 – Intentional** (https://github.com/cloudgen/ciao): Clear ownership prevents scattered configuration logic and makes the system auditable.
- **CIAO Principle 3 – Anti-fragile** (https://github.com/cloudgen/ciao): Centralized configuration survives refactoring, team changes, and AI-assisted edits.
- **CIAO Principle 4 / CIAO-Lite O · Principle 20 – Over-protect / Protect Against AI** (https://github.com/cloudgen/ciao): Restrictive permissions on sensitive files (tokens) and explicit module ownership protect user credentials.

## 3. Design Principles (CIAO / CIAO-Lite)

- **Caution** (CIAO Principle 1): Assume configuration files can be missing, corrupted, or accessed by untrusted code. Always validate and use safe defaults.
- **Intentional** (CIAO Principle 2): Every piece of configuration has one clear owner and access path.
- **Anti-fragile** (CIAO Principle 3): The design works for minimal CLI clients today and can gracefully extend to richer configuration needs later.
- **Over-protect** (CIAO Principle 4 / CIAO-Lite O · Principle 20): Explicit rules about session file permissions and module ownership defend against the most common configuration-related security and reliability issues.

## 4. Protection Rule (Sacred)

**Future AI assistants, Grok, or maintainers MUST NOT**:
- Read or write the session file (`{{SESSION_FILE}}`) or any configuration file directly using `fs` or equivalent — always go through the designated owner module (`{{SESSION_MODULE}}` / `{{CONFIG_MODULE}}`).
- Hardcode concrete paths (e.g. `~/.app/{{APP_NAME}}`, `/opt/{{APP_NAME}}`) — always use `{{PROJECT_DIR}}` and `{{SESSION_FILE}}` placeholders.
- Introduce new configuration files without documenting their owner module and access rules.
- Bypass restrictive file permissions (`0600`) on any file containing tokens or credentials.
- Remove or weaken the centralized ownership model when specializing this template.
- Reference concrete previous project paths, Docker compose files, or nginx configuration from the obsolete installer era.

Violating this rule is considered a **critical regression**.

---


## Design-time verification

| Gate | Artifact | Phase |
|------|----------|-------|
| Specialize → product suite or checklist | declare TP-IDs or checklist in specialized REQ | Design |
| RTM | `../tests/template-requirement-test-traceability.md` | Design |

When this mold has no executable TP family, mark **n/a** with reason in product `reviews/test-plan.md`.

**Last Updated**: 2026-06-09 (Generalized from obsolete self-host installer requirement; now focused on secure session/configuration ownership for Node.js platform clients)
**Owner**: Configuration & State Layer
**Alignment**: Fully synchronized with `docs/requirements/index.md`, `docs/templates/requirements/template-defensive-practices.md`, `AGENTS.md` (CIAO Protection Zones) and specialized requirements, `docs/requirements/index.md` (if exists), and **CIAO Principles 1, 2, 3, 4, 20 (v2.10.2)** (https://github.com/cloudgen/ciao).

---

**How to specialize this template**:
1. Copy to `docs/templates/requirements/template-configuration-management.md`.
2. Replace `{{PLACEHOLDER}}` values with project decisions.
3. Implement or extend the `{{CONFIG_MODULE}}` and `{{SESSION_MODULE}}` as needed.
4. Add any additional configuration concerns (e.g. user preferences, cache settings) with clear ownership.
5. After specialization, update `docs/requirements/index.md` with the specialized `requirement-*.md` row only (never list this template path in the registry).
