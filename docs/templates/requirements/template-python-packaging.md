---
name: python-packaging
id: LM-PYTHON-PACKAGING
kind: law-mold
description: >
  Portable law mold. Cite as LM-PYTHON-PACKAGING (path secondary).
---

**file**: docs/templates/requirements/template-python-packaging.md
**Status**: Active (Version 1.0.0 – Generalized reusable template for CIAO-Lite Python PyPI Execution Projects)
**Project**: {{APP_NAME}} – Python PyPI Execution Project
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

# Template: Python Packaging

## 1. Purpose

This template defines the mandatory packaging standards for CIAO-Lite Python PyPI Execution Projects (CLI tools published on PyPI).

It ensures modern, maintainable, and defensive packaging practices aligned with current Python packaging standards (PEP 517, PEP 621).

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
| **Python CLI architecture** | `docs/terminologies/python-cli-architecture.md` | `product-law` | Package layout |

**SSOT types used:** `meta-catalog` · `policy` · `product-law`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Primary Manifest: pyproject.toml (Sacred)

**`pyproject.toml` is the Single Source of Truth** for this project.

All of the following **MUST** be defined in `pyproject.toml`:

- Project metadata (name, version, description, authors)
- Python version requirement
- Build system
- Runtime dependencies
- Optional dependencies (extras)
- Console script entry points
- Development / build dependencies

### Why `pyproject.toml`?
- It is the modern standard for Python packaging.
- It supports rich metadata and entry points without `setup.py`.
- It works cleanly with `pip`, `uv`, `poetry`, `hatch`, etc.
- It provides a single, declarative file that tools and humans can reliably parse.

## 3. Forbidden Practices

### 3.1 Do NOT use `requirements.txt` as Primary Manifest

**`requirements.txt` MUST NOT be used** as the primary way to declare dependencies for a PyPI-published CLI tool.

**Reasons**:
- `requirements.txt` is primarily intended for pinning exact versions in deployment environments.
- It lacks rich metadata (description, entry points, Python version classifiers, etc.).
- Using it as the source of truth creates duplication and maintenance burden.
- It conflicts with modern PEP 621 packaging.

**Allowed limited use**:
- Only for development environments or specific CI pinning (clearly documented as secondary).
- Never committed as the authoritative dependency list.

### 3.2 No `setup.py` (Unless Absolutely Necessary)

New projects **SHOULD NOT** use `setup.py`. All packaging configuration must live in `pyproject.toml`.

Legacy `setup.py` is only acceptable during migration and must be removed once `pyproject.toml` is complete.

## 4. Console Script Entry Points (Mandatory)

The CLI command must be defined declaratively in `pyproject.toml`:

```toml
[project.scripts]
{{APP_NAME}} = "{{PACKAGE_NAME}}.cli:main"
```

**Rules**:
- The entry point function (`main()`) must be minimal — it should only initialize the main `StateLogic` class and delegate.
- No business logic is allowed directly in the entry point module.
- The entry point must respect `--quiet` and `--json` flags (handled inside the `StateLogic` class).

## 5. Dependency Management Rules

| Dependency Type          | Location in `pyproject.toml`              | Notes |
|--------------------------|-------------------------------------------|-------|
| Core runtime             | `[project.dependencies]`                  | Required packages |
| Optional features        | `[project.optional-dependencies]`         | e.g. `dev`, `test` |
| Build / packaging        | `[build-system]` + `[tool.*]`             | Build backend configuration |
| Development / testing    | `[project.optional-dependencies.dev]`     | `pytest`, `ruff`, `mypy`, etc. |

**Key Principles**:
- Keep core dependencies minimal.
- Use optional dependencies (`extras`) for features not needed by every user.
- Never hard-code version pins in a way that prevents security updates.

## 6. Design Principles (CIAO / CIAO-Lite)

- **Caution (CIAO Principle 1)**: Packaging decisions have long-term impact on installability, security updates, and user experience.
- **Intentional (CIAO Principle 2)**: `pyproject.toml` is the single, authoritative location for all packaging concerns.
- **Anti-fragile (CIAO Principle 3)**: Modern declarative packaging survives changes in build tools and Python versions better than legacy patterns.
- **Over-protect (CIAO Principle 4 / CIAO-Lite O · Principle 20)**: Clear rules against legacy patterns prevent gradual degradation of packaging quality.

## 7. Protection Rule (Sacred)

**Future implementation and packaging changes MUST follow**:
- `pyproject.toml` is the only authoritative packaging manifest.
- Console script entry points must be declared in `pyproject.toml`.
- All runtime dependencies must be declared in `pyproject.toml`.

**Future AI assistants, Grok, or maintainers MUST NOT**:
- Introduce or rely on `requirements.txt` as the primary dependency source.
- Add new console scripts without updating `pyproject.toml`.
- Create `setup.py` for new functionality.
- Duplicate dependency lists across multiple files.
- Bypass `pyproject.toml` when adding new Python packages.

Violating this rule is considered a **packaging regression**.

---


## Design-time verification

| Gate | Artifact | Phase |
|------|----------|-------|
| Skill | `skill-python-cli-coding` | Review |

**RTM:** `../tests/template-requirement-test-traceability.md` §4.

**Last Updated**: 2026-06-21  
**Owner**: Python Packaging Layer (Generalized Template)  
**Alignment**: Fully synchronized with `template-python-project-structure.md`, `template-python-coding-style.md`, and **CIAO Principles 1, 2, 4, 20 (v2.10.2)** (https://github.com/cloudgen/ciao).

---

**How to specialize this template**:
1. Copy to `docs/requirements/requirement-python-packaging.md` (target name after specialization; create only when needed).
2. Replace `{{APP_NAME}}` and `{{PACKAGE_NAME}}` with concrete values for this project.
3. Update `docs/requirements/index.md` (and master requirements index if the project uses one).
4. Keep the `pyproject.toml` as Single Source of Truth rule intact.
5. Do not leave conversion session notes, absolute host paths, or product-specific names in the specialized file.