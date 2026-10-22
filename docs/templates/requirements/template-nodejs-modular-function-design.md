---
name: nodejs-modular-function-design
id: LM-NODEJS-MODULAR-FUNCTION-DESIGN
kind: law-mold
description: >
  Portable law mold. Cite as LM-NODEJS-MODULAR-FUNCTION-DESIGN (path secondary).
---

**file**: docs/templates/requirements/template-nodejs-modular-function-design.md
**Status**: Active (Version 1.0.0 – Generalized from template form docs/templates/requirements/template-modular-function-design.md for reusable Node.js CIAO-Lite CLI projects)
**Project**: {{APP_NAME}} – {{PLATFORM_NAME}} Platform Management CLI
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

## 1. Purpose

This document defines the modular function organization and extraction strategy used in {{APP_NAME}} CLI projects implemented in Node.js {{NODE_VERSION}}+ . It enables maintainability, reusability, and safe AI-assisted development while supporting single-executable distribution patterns where applicable.

It establishes:
- Consistent function prefix conventions for clear categorization.
- Mandatory use of centralized singletons as single sources of truth for core concerns (configuration, output, authentication session, self-description metadata, help/CLI interface documentation, and temporary file handling).

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
| **Node.js CLI architecture** | `docs/terminologies/nodejs-cli-architecture.md` | `product-law` | Module layout |

**SSOT types used:** `meta-catalog` · `policy` · `product-law`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Core Rules / Requirements (Mandatory)

### 2.1 Official Function Naming Convention (Mandatory)

**All functions MUST follow this prefix system.** This is the Single Source of Truth for organization.

| Prefix          | Category                          | Example Functions                                      |
|-----------------|-----------------------------------|--------------------------------------------------------|
| `output.`       | Output system                     | `output.info()`, `output.success()`, `output.json()`, `output.error()` (all errors to stderr) |
| `inst_`         | Installation & Self-management    | `inst_perform_install`, `inst_self_update`            |
| `util_`         | General utilities                 | `util_backup`, `util_resolve_storage`                 |
| `{{APP_NAME}}_` | Core business logic               | `{{APP_NAME}}_start`, `{{APP_NAME}}_status`, `{{APP_NAME}}_configure` |
| `ver_`          | Version comparison                | `ver_check`, `ver_gt`                                  |
| `path_`         | PATH & config handling            | `path_add_bashrc`, `path_add_shell`                    |
| `docker_`       | Docker-related helpers            | `docker_pull_by_digest`                                |

**Strict Naming Rules**:
1. Every new function **must** use one of the above prefixes.
2. Names should be descriptive but concise.
3. Internal helper functions must still carry the correct prefix.
4. Update this table when adding new categories.

### 2.2 Singleton Architecture for Node.js Implementations (Mandatory)

**Shared terminology (agents):** `docs/terminologies/nodejs-cli-architecture.md`

The Node.js implementation **MUST** treat the following modules as single sources of truth. All code must import and delegate to them; never duplicate logic, hardcode values, or maintain module-level state.

- `src/Config.js`: Single source of truth for app identity ({{APP_NAME}}), paths ({{PROJECT_DIR}} for session storage at `~/.app/{{APP_NAME}}`), runtime flags (quiet/json/debug), and interactive/non-interactive mode detection.
- `src/Output.js`: Single source of truth for **all** console output. Respects --json (exactly one JSON value on stdout, forces quiet), --quiet, and sends all errors/warnings/debug to stderr. Debug mode (DEBUG=1 env or --debug flag) supported and suppressed in --json.
- `src/About.js`: Single source of truth for version number, human-readable titles, descriptions, `about` diagnostics content, and command catalog facts. Never hardcode version strings or descriptive text.
- `src/Help.js`: Single source of truth for **all** help/usage text, command descriptions, global option documentation, and the rendering logic for `help` / `--help` / `-h` (human + --json forms). No descriptive CLI strings or showHelp logic may live outside this module.
- `src/Session.js`: Single source of truth for authentication state (token, endpoint, user) and all loading/saving/parsing of the session file. Never read/write the session file directly or maintain module-level ENDPOINT/TOKEN/USER variables.
- `src/Temp.js`: Single source of truth for all temporary files and debug capture results (HTTP responses, etc.). Location pattern: `{{TMP_FS}}/{{USERNAME}}/{{PID}}/N.txt` (tmp_fs priority: /dev/shm → /tmp → `~/.app/{{APP_NAME}}/temp`; username/pid from About singleton).

### 2.3 Why This Requirement Exists (Direct CIAO Alignment)
- **CIAO Principle 2 – Intentional** (https://github.com/cloudgen/ciao): Clear naming conventions and explicit singleton boundaries make the codebase easy to navigate, understand, and audit.
- **CIAO Principle 3 – Anti-fragile** (https://github.com/cloudgen/ciao): Consistent patterns and centralized singletons survive team changes, AI-assisted edits, and long-term evolution.
- **CIAO Principle 4 / CIAO-Lite O · Principle 20 – Over-protect / Protect Against AI** (https://github.com/cloudgen/ciao): The prefix system and singleton mandates act as lightweight architectural guardrails that protect against accidental simplification or destructive refactoring.

## 3. Design Principles (CIAO / CIAO-Lite)

- **Caution** (CIAO Principle 1): Assume future maintainers or AI assistants may attempt to "clean up" or refactor working patterns. Explicit prefixes and singletons reduce that risk.
- **Intentional** (CIAO Principle 2): Every function has a clear category and every core concern has exactly one owner (the relevant singleton).
- **Anti-fragile** (CIAO Principle 3): The structure remains usable and understandable even after many modifications or when new team members join.
- **Over-protect** (CIAO Principle 4 / CIAO-Lite O · Principle 20): Verbose headers, repeated defensive comments, and strict naming rules are deliberate features, not verbosity to be removed.

## 4. Protection Rule (Sacred)

**Future AI assistants, Grok, or maintainers MUST NOT**:
- Merge functions or remove the prefix-based grouping system.
- Delete or weaken Protection Zones and "!!! DO NOT MODIFY" comments.
- Remove General Purpose / CIAO principles / Lessons Learned sections from function headers.
- Bypass or duplicate logic from the singletons (Config, Output, About, Help, Session, Temp). Always import and delegate.
- Hardcode app name, paths, version strings, endpoint conventions, or session file formats — always use the singletons.
- Violate the official function prefix table or introduce functions without an approved prefix.
- "Clean up" defensive verbosity or singleton delegation for perceived readability or performance gains.
- Change the primary runtime or singleton architecture without also updating this template, docs/templates/requirements/template-coding-style.md, AGENTS.md, and docs/requirements/index.md.

**Violating this rule is considered a critical regression.**


## Design-time verification

| Gate | Artifact | Phase |
|------|----------|-------|
| Skill | `skill-nodejs-cli-coding` | Review |

**RTM:** `../tests/template-requirement-test-traceability.md` §4.

**Last Updated**: 2026-06-09  
**Owner**: Coding Standards & Defensive Layer (Grok + Team)  
**Alignment**: Fully synchronized with docs/templates/requirements/template-coding-style.md, AGENTS.md, docs/requirements/index.md, docs/templates/requirements/template-defensive-practices.md, docs/templates/requirements/template-output-requirements.md, docs/templates/requirements/template-nodejs-api-client.md, docs/templates/requirements/template-cli-interface.md, and **CIAO Principles 2, 3, 4, 20 (v2.10.2)** (https://github.com/cloudgen/ciao).

---

**How to use this template**:
- Copy into a new `requirement-nodejs-*.md` (or keep as template-nodejs-*) and fill `{{APP_NAME}}`, `{{NODE_VERSION}}`, `{{PROJECT_DIR}}`, `{{TMP_FS}}` placeholders with project-specific values.
- Always perform full upstream git analysis (via skill-upstream-git-analysis.md) before modifying singleton responsibilities or adding new function categories.
- After specialization, update `docs/requirements/index.md` with the specialized `requirement-*.md` row only (never list this template path in the registry).
