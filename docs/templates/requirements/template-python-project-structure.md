---
name: python-project-structure
id: LM-PYTHON-PROJECT-STRUCTURE
kind: law-mold
description: >
  Portable law mold. Cite as LM-PYTHON-PROJECT-STRUCTURE (path secondary).
---

**file**: docs/templates/requirements/template-python-project-structure.md
**Status**: Active (Version 1.0.0 – Generalized reusable template for CIAO-Lite Python PyPI Execution Projects / CLI tools)
**Project**: {{APP_NAME}} – Python PyPI Execution Project
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

# Template: Python Project Structure (PyPI Execution Project)

## 1. Purpose

This template defines the recommended directory layout and organization rules for CIAO-Lite **Python PyPI Execution Projects** (CLI tools published on PyPI and invoked via console script entrypoint).

It enforces:
- Clear separation between tool source code and user runtime data
- Strict `requirement-` prefix discipline for all requirement documents
- Use of centralized path resolution (e.g. via `ChronicleLogger` or equivalent config module)
- OOP-only implementation (no procedural scripts in main logic)
- PyPI Execution Project classification (no dedicated Python System User or Python Project Root required)

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
| **Python CLI architecture** | `docs/terminologies/python-cli-architecture.md` | `product-law` | Tree layout |
| **Project-base-path** | `docs/terminologies/project-base-path.md` | `identity-runtime` | The resolved application directory |
| **Project-log-path** | `docs/terminologies/project-log-path.md` | `identity-runtime` | Log directory under that base; not the cache path |

**SSOT types used:** `meta-catalog` · `policy` · `product-law` · `identity-runtime`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Recommended Root Directory Structure

```
{{APP_NAME}}/
├── README.md
├── LICENSE
├── CHANGELOG.md
├── pyproject.toml                  # Single Source of Truth for packaging
├── docs/
│   ├── api/                        # API endpoint references (if any)
│   ├── requirements/               # ALL requirement documents (must use requirement- prefix)
│   └── security/                   # Security and header rules
├── src/
│   └── {{PACKAGE_NAME}}/           # Python package (e.g. grok_project_sync, my_cli_tool)
│       ├── __init__.py
│       ├── __main__.py
│       └── cli.py                  # Main entry point (OOP classes only)
└── .gitignore
```

**Important Rules**:
- The `~/.app/{{APP_NAME}}/` folder (user runtime data) is **NOT** part of the repository.
- No `target/`, `build/`, `dist/`, or generated folders should be committed.
- `pyproject.toml` is the **Single Source of Truth** for metadata, dependencies, and console script entry points.

## 3. docs/ Directory Rules (Sacred)

- All requirement files **must** start with the exact prefix `requirement-` (e.g. `docs/templates/requirements/template-python-project-structure.md`).
- Only `requirement-*.md` files are allowed inside `docs/requirements/`.
- Other documentation lives in `docs/api/` and `docs/security/`.
- `docs/requirements/index.md` is the master index of every requirement file.

## 4. Runtime / User Environment Structure

All persistent user data **MUST** be resolved at runtime via the centralized configuration / logger module (never hard-coded).

Recommended structure:

```
~/.app/{{APP_NAME}}/                    # Resolved via centralized config/logger
├── cookies/
│   └── cookies.sqlite                  # Session storage (if applicable)
├── backups/                            # Dated incremental backups
├── config/                             # Optional user configuration
└── ...
```

**Key Principle**: The exact base path is [project-base-path](../../terminologies/project-base-path.md), resolved centrally. The log directory is [project-log-path](../../terminologies/project-log-path.md). Business logic classes should read the resolved path from state (via `Attr()`) rather than constructing paths themselves.

## 5. File Naming Conventions

| Type                        | Convention                     | Example |
|-----------------------------|--------------------------------|--------|
| Requirement documents       | `docs/requirements/index.md`    | `docs/templates/requirements/template-python-cli-interface.md` |
| Python source files         | `snake_case.py`                | `cli.py`, `file_uploader.py` |
| Backup files                | `filename.YYYYMMDD-N`          | `report.md.20260621-1` |
| Cookie / session database   | `cookies.sqlite` (protected)   | — |

## 6. Design Principles (CIAO / CIAO-Lite)

- **Caution (CIAO Principle 1)**: Clear separation between tool source and user runtime data. Never hard-code runtime paths.
- **Intentional (CIAO Principle 2)**: `docs/requirements/` is the single source of truth for all rules. `pyproject.toml` is the single source of truth for packaging.
- **Anti-fragile (CIAO Principle 3)**: Structure works for both development installs and published PyPI packages. Easy to ignore user data during version control.
- **Over-protect (CIAO Principle 4 / CIAO-Lite O · Principle 20)**: The `requirement-` prefix rule, centralized path resolution, and OOP-only main logic are protected and must not be refactored without updating this template.

## 7. Protection Rule (Sacred)

**Future implementation MUST follow**:
- Strict `requirement-` prefix for all requirement documents.
- All runtime paths resolved via the centralized configuration/logger module (never hard-coded).
- Main CLI logic implemented as OOP classes only (no long procedural scripts in `cli.py` or `__main__.py`).
- `pyproject.toml` as the authoritative packaging manifest.

**Future AI or developers MUST NOT**:
- Place any requirement document outside `docs/requirements/`.
- Use any filename that does not start with `requirement-`.
- Hard-code runtime paths (e.g. `~/.app/{{APP_NAME}}/` or similar) in business logic.
- Create `target/`, `build/`, `dist/`, or generated folders inside the repository.
- Commit user-generated runtime data into the repo.
- Refactor the project structure without updating this template and `docs/requirements/index.md`.
- Mix installation-time paths with runtime user data paths.

---


## Design-time verification

| Gate | Artifact | Phase |
|------|----------|-------|
| Skill | `skill-python-cli-coding` | Review |

**RTM:** `../tests/template-requirement-test-traceability.md` §4.

**Last Updated**: 2026-06-21  
**Owner**: Python Architecture Layer (Generalized Template)  
**Alignment**: Fully synchronized with `template-python-system-architecture.md`, `template-python-classes.md`, `template-python-coding-style.md`, `docs/terminologies/python-cli-architecture.md` / `template-python-system-architecture.md`, and **CIAO Principles 1, 2, 3, 4, 20 (v2.10.2)** (https://github.com/cloudgen/ciao).

---

**How to specialize this template**:
1. Copy to `docs/requirements/requirement-python-project-structure.md` (target name after specialization; create only when needed).
2. Replace `{{APP_NAME}}` and `{{PACKAGE_NAME}}` with concrete values for this project.
3. Update `docs/requirements/index.md` (and master requirements index if the project uses one).
4. Keep the `requirement-` prefix rule and centralized path resolution requirement intact.
5. Do not leave conversion session notes, absolute host paths, or product-specific names in the specialized file.