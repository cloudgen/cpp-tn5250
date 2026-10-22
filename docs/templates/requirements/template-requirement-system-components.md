---
name: requirement-system-components
id: LM-REQUIREMENT-SYSTEM-COMPONENTS
kind: law-mold
description: >
  Portable law mold. Cite as LM-REQUIREMENT-SYSTEM-COMPONENTS (path secondary).
---

**file**: template-requirement-system-components.md
**Status**: Active (Version 1.0.0 – Generalized reusable template)
**Project**: {{APP_NAME}} – {{PLATFORM_NAME}} Platform Management CLI
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

# Template: System Components (CIAO Defensive Architecture)

## 1. Purpose

This template defines the official system components that form the core architecture of a CIAO-Lite CLI tool. It serves as the high-level blueprint showing how all `requirement-*.md` documents, singletons, and functions interconnect to deliver a robust, maintainable, and defensive system.

It is the **architectural single source of truth** for the entire project.

**Template Usage**: Duplicate this file, replace all `{{PLACEHOLDER}}` values, and rename to `requirement-system-components.md` (or a more specific name; target after specialization, not live until created).

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
| **Three-layer privilege** | `docs/terminologies/three-layer-privilege.md` | `product-law` | System components by layer |
| **System user** | `docs/terminologies/system-user.md` | `identity-runtime` | Component ownership |

**SSOT types used:** `identity-runtime` · `meta-catalog` · `policy` · `product-law`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Core System Components (Mandatory)

| Component                        | Responsibility                                                                 | Primary `requirement-` Document                  | Key Singletons / Functions                          |
|----------------------------------|--------------------------------------------------------------------------------|--------------------------------------------------|-----------------------------------------------------|
| {{CONFIG_MODULE}}                | App identity, paths, global flags, runtime modes (`isJson`, `isQuiet`, `isDebug`, `isInteractive`) | `docs/templates/requirements/template-configuration-management.md`        | `Config` singleton (single source of truth)        |
| {{OUTPUT_MODULE}}                | All console output (info, success, warn, error, debug, json, result); enforces --json / --quiet / stderr rules | `docs/templates/requirements/template-output-requirements.md`             | `Output` class / singleton                         |
| {{ABOUT_MODULE}}                 | Version, titles, descriptions, `about` diagnostics, self-description           | `docs/templates/requirements/template-requirement-system-components.md` (or coding-style)         | `About` singleton                                  |
| {{HELP_MODULE}}                  | All help/usage text, command descriptions, `help` command rendering            | `docs/templates/requirements/template-cli-interface.md`                   | `Help` singleton                                   |
| {{SESSION_MODULE}}               | Authentication state (token, endpoint, user), session file I/O (0600)          | `docs/templates/requirements/template-configuration-management.md`        | `Session` singleton                                |
| {{API_CLIENT_LAYER}}             | All remote platform data access via official client (`connect` + `findAll` etc.) | `docs/templates/requirements/template-nodejs-api-client.md`                      | Official `{{API_CLIENT_PACKAGE}}` + upstream study |
| Core Business Logic              | Command handlers, domain workflows (install, configure, cards list, etc.)     | `docs/templates/requirements/template-cli-interface.md`                   | `{{APP_NAME}}_*` functions / command modules       |

> **Note for template users**: Add one row per major architectural component. Keep the table sorted from foundational cross-cutting concerns (Config, Output, Session) to domain-specific logic. Never hardcode concrete project names or paths — always use `{{PLACEHOLDER}}`.

---

## 3. Interconnection Rules (Mandatory)

- Every component **must** reference the others via the `requirement-*.md` documents and import only from the designated singletons.
- All functions / methods **must** follow the official prefix or naming conventions defined in `docs/templates/requirements/template-modular-function-design.md` (or the Node.js equivalent).
- Changes to any component require:
  1. Updating this master document
  2. Updating the linked `requirement-*.md` files
  3. Running the enforcement checklist in `template-enforcement-checklist.md`
- The main CLI entrypoint remains a **thin wrapper** that initializes singletons early and delegates to command handlers. No business logic lives in the entrypoint.

---

## 4. Design Principles (CIAO / CIAO-Lite)

- **Caution (CIAO Principle 1)**: Every component assumes the worst-case environment (missing singletons, permission issues, non-interactive execution, incomplete model data from the platform).
- **Intentional (CIAO Principle 2)**: Clear ownership and explicit cross-references between components make the architecture auditable and predictable.
- **Anti-fragile (CIAO Principle 3)**: The system survives partial failures in any single component because singletons provide safe defaults and graceful degradation.
- **Over-protect (CIAO Principle 4 / CIAO-Lite O · Principle 20)**: Protection Zones, safe defaults, backup-before-modify, and the mandatory enforcement checklist defend the architecture from erosion by future changes or AI-assisted edits.

### 4.1 Why This Requirement Exists (Direct CIAO Alignment)
- **CIAO Principle 2 – Intentional** (https://github.com/cloudgen/ciao): Clear ownership and interconnection rules prevent scattered logic and make the system understandable.
- **CIAO Principle 3 – Anti-fragile** (https://github.com/cloudgen/ciao): Explicit component boundaries and single sources of truth allow the project to survive repeated modifications.
- **CIAO Principle 4 / CIAO-Lite O · Principle 20 – Over-protect / Protect Against AI** (https://github.com/cloudgen/ciao): Treating the component table and interconnection rules as a living master document protects the defensive architecture over time.

---

## 5. Protection Rule (Sacred)

**Future AI assistants, Grok, or maintainers MUST NOT**:
- Remove or weaken any listed core component (especially Config, Output, About, Help, Session).
- Bypass singletons by reading `process.env`, writing files directly, or maintaining module-level state for auth/output/version/help.
- Refactor the thin entrypoint + singleton initialization pattern without updating this document and the enforcement checklist.
- Delete or rename components without also updating `docs/requirements/index.md` and running the full enforcement checklist.
- Ignore the official function / method naming conventions when adding new code.
- Treat this document as optional documentation — it is an active architectural contract.

**Violating this rule is considered a critical regression.**

---

## 6. How to Specialize This Template

1. Copy this file to `requirement-system-components.md` (target name after specialization; not a live file until created).
2. Replace all `{{PLACEHOLDER}}` values with concrete decisions for your project.
3. Populate the table with the actual singletons and major modules your CLI uses.
4. Add any project-specific components (e.g. Docker management, self-host logic) if they exist.
5. After specialization, update `docs/requirements/index.md` with the specialized `requirement-*.md` row only (see diff below — requirement path, not this template).
6. Bump version/date and add to the "Active Supporting Requirements" list.

## Design-time verification

| Gate | Artifact | Phase |
|------|----------|-------|
| Specialize → product suite or checklist | declare TP-IDs or checklist in specialized REQ | Design |
| RTM | `../tests/template-requirement-test-traceability.md` | Design |

When this mold has no executable TP family, mark **n/a** with reason in product `reviews/test-plan.md`.

