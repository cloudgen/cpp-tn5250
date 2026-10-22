---
name: python-system-architecture
id: LM-PYTHON-SYSTEM-ARCHITECTURE
kind: law-mold
description: >
  Portable law mold. Cite as LM-PYTHON-SYSTEM-ARCHITECTURE (path secondary).
---

**file**: docs/templates/requirements/template-python-system-architecture.md
**Status**: Active (Version 1.0.0 – Generalized reusable template for CIAO-Lite Python PyPI Execution Projects)
**Project**: {{APP_NAME}} – Python PyPI Execution Project
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

# Template: Python System Architecture (PyPI Execution Project)

## 1. Purpose

This template is the **Single Source of Truth** for the high-level system architecture of CIAO-Lite Python-based CLI tools.

It enforces the correct project type classification and ensures all future implementation and requirement decisions respect the boundaries of a **PyPI Execution Project**.

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
| **Python CLI architecture** | `docs/terminologies/python-cli-architecture.md` | `product-law` | Architecture |
| **Three-layer privilege** | `docs/terminologies/three-layer-privilege.md` | `mention-only` | Privilege layers |

**SSOT types used:** `mention-only` · `meta-catalog` · `policy` · `product-law`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Project Type Classification (Mandatory)

This project **MUST** be treated as a:

**PyPI Execution Project**

**Definition**:
> A Python project published on PyPI and executed as a CLI tool or script (e.g. `black`, `pytest`, custom CLI). These projects **do not** have a Python Project Root (for `sys.path`) or a dedicated Python System User. They are invoked directly via the installed console script entrypoint.

### Why This Classification Matters
- No dedicated non-login system user is required.
- No `Python Project Root` needs to be added to `sys.path`.
- The tool runs with the privileges of the invoking user.
- All state is managed inside the main `StateLogic` orchestrator class.
- Persistent data (cookies, backups, config) is resolved exclusively through the centralized configuration / logger module.

**Future AI assistants, Grok, or maintainers MUST NOT** assume this is a Web API System or WebSocket System.

## 3. Core Architectural Rules

### 3.1 Execution Model
- Primary entry point: console script defined in `pyproject.toml` (e.g. `{{APP_NAME}} = "{{PACKAGE_NAME}}.cli:main"`).
- The `main()` function performs minimal initialization and immediately delegates to the main `StateLogic` class (e.g. `{{MAIN_ORCHESTRATOR_CLASS}}`).
- No long-running server process.
- No Docker / container management in the core scope (future optional extension only).

### 3.2 State Management
- All significant state **MUST** live inside `StateLogic` subclasses using the `Attr()` descriptor.
- `operational_state`, `quiet_mode`, `json_mode`, `dry_run`, etc. are declared as `Attr()` member variables.
- No global variables or module-level mutable state for core workflow.

### 3.3 Path & Storage Resolution
- All user-specific paths (cookies, backups, config) **MUST** be resolved through the centralized configuration / logger module.
- Never hard-code `~/.app/{{APP_NAME}}/` or similar paths in business logic.

### 3.4 Privilege Model
- Type 0 operations (self-management: version, help, about) run directly.
- No Type 1 (elevated) or Type 2 (dedicated system user) operations are required in the current scope.
- If future features require privileged operations, they must be explicitly classified and added to this template first.

## 4. Design Principles (CIAO / CIAO-Lite)

- **Caution (CIAO Principle 1)**: Assume the tool will be invoked by normal users in varied environments. Do not introduce unnecessary privilege or complexity assumptions.
- **Intentional (CIAO Principle 2)**: The architecture is deliberately simple because this is a focused CLI tool.
- **Anti-fragile (CIAO Principle 3)**: Clear classification survives future feature additions and prevents accidental adoption of heavier patterns.
- **Over-protect (CIAO Principle 4 / CIAO-Lite O · Principle 20)**: Explicit boundaries and Protection Rules defend the lightweight nature of the project.

## 5. Protection Rule (Sacred)

**Future AI assistants, Grok, or maintainers MUST NOT**:

- Introduce a dedicated Python System User or assume the tool must run under a non-root system account.
- Add `Python Project Root` logic or manipulate `sys.path` for import purposes.
- Apply Web API / long-running service architecture patterns without first updating this template.
- Remove or weaken the PyPI Execution Project classification.
- Hard-code paths instead of using centralized resolution.

Violating this rule is considered a **critical regression** against CIAO principles.

## 6. Relationship to Other Templates

This template is the parent architecture document for all Python implementation templates. It must be referenced by:
- `template-python-cli-interface.md`
- `template-python-classes.md`
- `template-python-coding-style.md`
- `template-python-error-handling.md`
- `template-python-output-requirements.md`

**Shared terminology (agents):** `docs/terminologies/python-cli-architecture.md`

## 7. Future Enhancements (Documentation Phase Reminder)

- Optional Docker support (must remain strictly optional and documented here first).
- Configuration file support.
- Watch mode / daemon-like behavior (would require re-classification discussion).

---


## Design-time verification

| Gate | Artifact | Phase |
|------|----------|-------|
| Skill | `skill-python-cli-coding` | Review |

**RTM:** `../tests/template-requirement-test-traceability.md` §4.

**Last Updated**: 2026-06-21  
**Owner**: Python Architecture Layer (Generalized Template)  
**Alignment**: Fully synchronized with `docs/terminologies/python-cli-architecture.md` / `template-python-system-architecture.md`, `template-python-classes.md`, `template-python-cli-interface.md`, `template-python-project-structure.md`, and **CIAO Principles 1, 2, 3, 4, 20 (v2.10.2)** (https://github.com/cloudgen/ciao).

---

**How to specialize this template**:
1. Copy to `docs/requirements/requirement-python-system-architecture.md` (target name after specialization; create only when needed).
2. Replace `{{APP_NAME}}`, `{{PACKAGE_NAME}}`, and `{{MAIN_ORCHESTRATOR_CLASS}}` with concrete values for this project.
3. Update `docs/requirements/index.md` (and master requirements index if the project uses one).
4. Keep the PyPI Execution Project classification and centralized resolution rules intact.
5. Do not leave conversion session notes, absolute host paths, or product-specific names in the specialized file.