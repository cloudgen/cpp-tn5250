---
name: python-cli-interface
id: LM-PYTHON-CLI-INTERFACE
kind: law-mold
description: >
  Portable law mold. Cite as LM-PYTHON-CLI-INTERFACE (path secondary).
---

**file**: template-python-cli-interface.md
**Status**: Active (Version 1.1.0 – dual mention inherited from LM-CLI-INTERFACE)
**Project**: Any CIAO-Lite Python Project (reusable template)
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

# Template: Python CLI Interface

## 1. Purpose

This template defines the official command-line interface, flags, interactive mode, and parameters for Python-based CIAO-Lite CLI tools.

It serves as the single source of truth for all user-facing commands and ensures consistency with the `StateLogic` + `Attr` architecture and ChronicleLogger output control.

### 1.1 Empty argv (default Type N)

Unless this Python product also specializes **online install** (`template-online-install.md` / empty-argv **Type O**), bare invocation without required args **SHOULD** show help or interactive prompts as designed — **Type N**. Do **not** default to shell one-liner install-ensure. See `template-shell-cli-zero-arguments.md` and **`LM-CLI-INTERFACE`** §1.1.

This mold **inherits dual mention** from **`LM-CLI-INTERFACE`** §4.1. Specialize into `requirement-python-cli-interface.md` — **not** only the generic `requirement-shell-cli-interface.md`.

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
| **Python CLI architecture** | `docs/terminologies/python-cli-architecture.md` | `product-law` | CLI surface |
| **Type O empty argv** | `docs/terminologies/type-o-empty-argv.md` | `product-law` | Empty argv when online |

**SSOT types used:** `meta-catalog` · `policy` · `product-law`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Command-Line Interface Overview

**Primary command** (recommended):

```bash
{{APP_NAME}} [OPTIONS] <local-directory>
```

The tool should:
- Support configuration via `ChronicleLogger` (for paths, quiet/json modes, etc.)
- Default to interactive mode when required parameters are missing
- Respect `--quiet` and `--json` flags through centralized output handling

### Positional Argument
- `<local-directory>` – Path to the local folder to process (required in most cases)

### Core Options (Recommended)

| Option                    | Type     | Default     | Purpose |
|---------------------------|----------|-------------|---------|
| `--workspace-id` / `-w`   | string   | (interactive) | Target identifier (e.g. workspace/project ID) |
| `--dry-run`               | flag     | false       | Simulate operations without making changes |
| `--quiet` / `-q`          | flag     | false       | Suppress non-error output |
| `--json`                  | flag     | false       | Output only machine-readable JSON |
| `--force`                 | flag     | false       | Force operations (bypass safety checks where appropriate) |
| `--help` / `-h`           | flag     | -           | Show help |
| `--version`               | flag     | -           | Show version (via `class_version()` or equivalent) |

### Interactive Mode (Default)

When a required identifier (e.g. workspace/project) is not provided via flag, the tool should:
1. Attempt to list available targets (if supported)
2. Prompt the user to select one
3. Remember the choice for the current session

## 2.1 Dual mention (inherited — sacred)

Every routed product verb (argparse/click dest, console-script action, or orchestrator route) **MUST** be named in **at least two** Active specialized `requirement-*.md` files:

1. **`requirement-python-cli-interface`** (dispatch / help honesty).  
2. The **topic-owner** requirement (lifecycle, privilege, domain, vault, session, request, actor, …).

**MUST NOT** leave a verb only on the Python CLI-interface file. That file is rewritten per product. argparse/click `--help` is **usage text**, not the second requirement mention.

Adding a verb to Implementation Notes **MUST** name it on the topic-owner REQ in the same change. Superclass: **`LM-CLI-INTERFACE`** §4.1.

## 3. Output Behavior

- Normal mode: Human-readable progress and messages
- `--quiet`: Only errors and final summary
- `--json`: Single clean JSON object at the end (no other output)
- All output must be routed through `ChronicleLogger` (or the project's centralized output system)

## 4. Design Principles (CIAO-Lite)

- **Caution**: Default to interactive mode for safety when identifiers are missing.
- **Intentional**: CLI behavior must be driven by the main orchestrator class (inheriting from `StateLogic`).
- **Anti-fragile**: Must work correctly in both interactive terminals and non-interactive environments (CI/CD, scripts).
- **Over-protect**: No direct network calls from the CLI layer — everything must route through proper OOP classes.

## 5. Protection Rule (Sacred)

**Future AI assistants, Grok, or maintainers MUST NOT**:

- Add new top-level scripts or procedural CLI code outside the main orchestrator class.
- Hard-code storage paths or endpoint URLs.
- Bypass `ChronicleLogger` (or equivalent) for output control and path resolution.
- Remove or weaken the mandatory use of `--quiet` / `--json` handling through the central output system.
- Change flag names or core behavior without updating this template and the master requirements index.  
- Skip dual mention (§2.1) or treat argparse/click help as the second requirement mention.  
- Specialize this mold into a shell-only `requirement-shell-cli-interface.md` when the product is Python.

## 6. How to Specialize This Template

1. Specialize into `docs/requirements/requirement-python-cli-interface.md` (do **not** overwrite **`LM-CLI-INTERFACE`**).  
2. Replace `{{APP_NAME}}` with the product command name.  
3. Adjust options and orchestrator class in Implementation Notes.  
4. Dual-mention every routed verb (§2.1) on this REQ **and** the topic-owner.  
5. Register `docs/requirements/index.md`.  
6. Keep the Protection Rule and §2.1 intact.

---


## Design-time verification

| Gate | Artifact | Phase |
|------|----------|-------|
| Skill | `skill-python-cli-coding` | Review |

**RTM:** `../tests/template-requirement-test-traceability.md` §4.

**Last Updated**: 2026-08-18  
**Owner**: CLI Architecture Layer (Generalized Template)  
**Version history:**  
- **1.1.0** (2026-08-18): Inherit **`LM-CLI-INTERFACE`** §4.1 dual mention.  
- **1.0.0**: Initial Python CLI surface mold.

**Alignment**: **`LM-CLI-INTERFACE`** §4.1 · `template-python-coding-style.md` · `template-python-classes.md` · **CIAO Principles 2, 4, 20 (v2.10.2)**.