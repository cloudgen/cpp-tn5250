---
name: nodejs-coding-style
id: LM-NODEJS-CODING-STYLE
kind: law-mold
description: >
  Portable law mold. Cite as LM-NODEJS-CODING-STYLE (path secondary).
---

**file**: docs/templates/requirements/template-nodejs-coding-style.md
**Status**: Active (Version 1.0.0 – Generalized Node.js coding style template)
**Project**: {{APP_NAME}} – {{PLATFORM_NAME}} Platform Management CLI
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

# Template: Coding Style & Defensive Practices (Node.js)

## 1. Purpose

This template defines the official coding style and defensive practices for {{APP_NAME}}-style Node.js platform management CLIs. It ensures maximum maintainability, consistency, and strict adherence to the CIAO philosophy while supporting clean, modern JavaScript development.

**Specialize-in (software-development):** product law is a specialized `requirement-nodejs-coding-style.md`. **Without that REQ, agents bring these learned lessons raw.** Term: `coding-style-requirement`.

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
| **Node.js CLI architecture** | `docs/terminologies/nodejs-cli-architecture.md` | `product-law` | Coding conventions |

**SSOT types used:** `meta-catalog` · `policy` · `product-law`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Runtime and Shebang Decision — {{RUNTIME}}

**Official Rule**: The main CLI **MUST** use {{RUNTIME}} with the shebang:

```js
{{SHEBANG}}
```

### Reasons (Direct CIAO Alignment)
- **CIAO Principle 2 – Intentional** and **Principle 3 – Anti-fragile**: Using a modern, well-supported runtime enables direct, correct usage of the official platform API client (`{{API_CLIENT_PACKAGE}}`) instead of fragile workarounds.
- Enables proper structured data handling, async/await, strong typing (where applicable), and reuse of the official client library.
- Provides a stable, predictable execution environment.

Legacy helper scripts (if any) may continue to use POSIX shell where strictly necessary, but the primary implementation must remain in {{RUNTIME}}.

## 3. Module / Function Organization (Mandatory)

All code **MUST** follow a clear, centralized ownership model using singletons or well-defined modules for cross-cutting concerns.

### Recommended Core Modules (Single Sources of Truth)

| Module / Singleton       | Responsibility                                      | Key Rules |
|--------------------------|-----------------------------------------------------|---------|
| `{{CONFIG_MODULE}}`      | App identity, paths (`{{PROJECT_DIR}}`), flags, modes, runtime configuration | Single source for `app_name`, `isJson`, `isQuiet`, `isDebug`, `mode` |
| `{{OUTPUT_MODULE}}`      | All console output (info, success, warn, error, debug, json, result) | Never use raw `console.log`/`console.error` for user messages |
| `{{ABOUT_MODULE}}`       | Version, titles, descriptions, diagnostics, self-description | Never hard-code version or descriptive text |
| `{{HELP_MODULE}}`        | All help text, usage, command descriptions, `help` command rendering | Single source for CLI interface documentation |
| `{{SESSION_MODULE}}`     | Token, endpoint, user identity, session file I/O    | Never read/write session file directly or maintain module-level auth variables |

### Function / Method Naming
- Use clear, descriptive names.
- Methods on singletons should follow consistent naming (e.g. `output.info()`, `output.error()`).
- Internal helpers should still carry meaningful prefixes or be clearly scoped inside their module.

## 4. General Coding Rules (CIAO / CIAO-Lite)

- Write clean, modern JavaScript (primary runtime is {{RUNTIME}}).
- All user-facing output **must** go through the centralized `{{OUTPUT_MODULE}}`.
- All version numbers, titles, descriptions, `about` diagnostics, and app metadata **must** come from the `{{ABOUT_MODULE}}`.
- All help/usage text, command descriptions, and help command rendering **must** come from the `{{HELP_MODULE}}`.
- All authentication state and session file handling **must** go through the `{{SESSION_MODULE}}`.
- Heavy commenting and Protection Zones are intentional and required.
- Prefer explicit, readable control flow over clever one-liners.

**Error Handling Style (Mandatory)**
- Prefer explicit, readable error handling.
- All error-related output must go through `{{OUTPUT_MODULE}}.error()` or equivalent (guaranteed to go to stderr).
- In `--json` mode, errors must be emitted as structured JSON on stderr.

## 5. Design Principles (CIAO / CIAO-Lite)

- **Caution** (CIAO Principle 1): Assume future developers and AI assistants will attempt to bypass centralized modules or introduce inconsistent patterns.
- **Intentional** (CIAO Principle 2): Clear module ownership and naming make the codebase easy to navigate and audit.
- **Anti-fragile** (CIAO Principle 3): Centralized singletons survive repeated modifications and team/AI changes.
- **Over-protect** (CIAO Principle 4 / CIAO-Lite O · Principle 20): Explicit rules and Protection Zones defend against accidental violations of the defensive architecture.

### 5.1 Product-source documentation authority

In **product source** comments (`ALIGNMENT` / `See` / module headers):

- **Cite only** live `docs/requirements/requirement-*.md` paths that exist on disk.
- **Do not cite** `template-*.md` or `skill-*.md` as behavioral authority in product source (skills may be used as agent harnesses, not as ALIGNMENT substitutes).
- **Do not invent** requirement paths. See `template-defensive-practices.md` §2.7.

## 6. Protection Rule (Sacred)

**Future AI assistants, Grok, or maintainers MUST NOT**:
- Downgrade or change away from the declared `{{RUNTIME}}` and `{{SHEBANG}}` without updating the corresponding requirements.
- Bypass the centralized `{{OUTPUT_MODULE}}` for any user-facing messages.
- Bypass the `{{ABOUT_MODULE}}` for version, titles, descriptions, or diagnostics content.
- Bypass the `{{HELP_MODULE}}` for CLI help text, usage, or command descriptions.
- Bypass the `{{SESSION_MODULE}}` for token, endpoint, user, or session file operations.
- Introduce raw `console.log` / `console.error` calls for application output.
- Violate the single-source-of-truth pattern for Config, Output, About, Help, and Session.
- Remove or weaken Protection Zones and explicit ownership rules.
- Skip upstream git analysis (`skill-upstream-git-analysis.md`) when working with the official API client or platform models.
- Cite `template-*.md` or `skill-*.md` as product-source authority, or invent missing `requirement-*.md` paths in source comments.

**Violating this rule is considered a critical regression.**

---


## Design-time verification

| Gate | Artifact | Phase |
|------|----------|-------|
| Skill | `skill-nodejs-cli-coding` | Review |

**RTM:** `../tests/template-requirement-test-traceability.md` §4.

**Last Updated**: 2026-07-12 (§5.1 product-source documentation authority)
**Owner**: Coding Standards & Defensive Layer
**Alignment**: Fully synchronized with `docs/requirements/index.md`, `docs/templates/requirements/template-nodejs-api-client.md`, `docs/templates/requirements/template-output-requirements.md`, `AGENTS.md` (CIAO Protection Zones) and specialized requirements, `docs/templates/requirements/template-defensive-practices.md`, and **CIAO Principles 1, 2, 3, 4, 20 (v2.10.2)** (https://github.com/cloudgen/ciao).

---

**How to specialize this template**:
1. Copy to `docs/templates/requirements/template-coding-style.md` / `template-shell-script-coding.md`.
2. Replace `{{PLACEHOLDER}}` values with concrete project decisions.
3. Implement or document the actual core modules/singletons.
4. After specialization, update `docs/requirements/index.md` with the specialized `requirement-*.md` row only if new project rules were added (never list this template path).

**Precise diff needed for `docs/requirements/index.md`**:

```diff
diff --git a/docs/requirements/index.md b/docs/requirements/index.md
index abc1234..def5678 100644
--- a/docs/requirements/index.md
+++ b/docs/requirements/index.md
@@ -XX,6 +XX,7 @@ All self-host installer functionality has been removed.
 ## 3. Active Supporting Requirements

 - docs/requirements/index.md (this file)
+- template-nodejs-coding-style.md (generalized reusable template for Node.js CLI coding standards)
 - docs/templates/requirements/template-nodejs-api-client.md
 - docs/templates/requirements/template-output-requirements.md
 - docs/templates/requirements/template-error-handling.md
```

**Note**: This template focuses on the defensive value of centralized singletons (Config, Output, About, Help, Session) as the primary pattern for {{APP_NAME}}-style Node.js CLIs. It can be extended with additional language-specific rules as needed.
