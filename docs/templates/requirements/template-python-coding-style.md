---
name: python-coding-style
id: LM-PYTHON-CODING-STYLE
kind: law-mold
description: >
  Portable law mold. Cite as LM-PYTHON-CODING-STYLE (path secondary).
---

**file**: docs/templates/requirements/template-python-coding-style.md
**Status**: Active (Version 1.0.0 – Generalized reusable template for CIAO-Lite Python PyPI Execution Projects)
**Project**: {{APP_NAME}} – Python PyPI Execution Project / CLI Tool
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

# Template: Python Coding Style (PyPI Execution Project)

## 1. Purpose

This template defines the mandatory **Python coding style** for CIAO-Lite Python PyPI Execution Projects (CLI tools).

It ensures implementations remain clean, maintainable, defensive, and fully aligned with CIAO-Lite principles while taking full advantage of Python’s object-oriented capabilities.

**Specialize-in (software-development):** product law is a specialized `requirement-python-coding-style.md`. **Without that REQ, agents bring these learned lessons raw.** Term: `coding-style-requirement`.

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
| **Python CLI architecture** | `docs/terminologies/python-cli-architecture.md` | `product-law` | Style conventions |

**SSOT types used:** `meta-catalog` · `policy` · `product-law`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Single Source of Truth (SSOT) Rule — CENTRAL AND SACRED

- All `requirement-*.md` files are the **SSOT** for rules, behavior, and design decisions.
- `docs/requirements/index.md` is the master index.
- The centralized output / logging module (e.g. `ChronicleLogger` or equivalent) is the **SSOT** for all output, logging, storage path resolution, quiet/JSON modes, and defensive practices.

Every class, method, and design decision must reference back to the relevant requirement document.

## 3. OOP Rule — Detailed and Sacred (Python Implementation)

**The OOP rule is the core architectural principle** for all Python code in {{APP_NAME}}.

### What the OOP rule means:
- **Everything must be implemented as clean, independent classes** (e.g. `{{MAIN_ORCHESTRATOR_CLASS}}`, `CookieManager`, `FileUploader`, `BackupManager`).
- **No procedural scripts** or long top-level functions are allowed in the main application logic.
- **Class responsibilities must stay clear and focused**.

### Specific rules when adding new features:
- **New features** → Add new member variables using `Attr()` (e.g. `self.cookie_db_path`, `self.dry_run`). Do **not** simplify existing method signatures or flatten class structure to avoid adding variables.
- **Method signatures** → **Do NOT simplify or shorten** them. Keep explicit parameters and clear names.
- **Class structure** → **Do NOT flatten** classes.
- **Logger / Output access** → **Always use the flattened pattern**: `self.log_message(...)`, `self.output_text(...)`, `self.output_json(...)`. Never write `self.logger.xxx(...)`.

These rules prevent the common anti-pattern of “cleaning up” OOP code into procedural style.

## 4. Mandatory Python Coding Rules

- Every Python file **must** start with the full CIAO defensive header (including Protection Zones).
- All major classes that manage state **must** inherit from `StateLogic`.
- All state attributes **must** be declared using the `Attr()` descriptor in `__init__()`.
- Storage paths are **always** resolved via the centralized configuration/logger module — never hard-coded.
- Output control (`--quiet`, `--json`) is handled **exclusively** by the centralized output module.
- Use `try: import ... except ImportError:` at module level for optional or missing dependencies.
- All public methods should have clear docstrings.
- Type hints are encouraged for better maintainability.

## 4b. Temporary files and publish / move (Sacred — multi-mount)

System `TMPDIR` / `/tmp` and user media (USB, secondary disks, network mounts) are often **different filesystems**. Bare rename does not cross mounts (e.g. Linux **`EXDEV`** / “Invalid cross-device link”).

### Rules

1. When the **final destination path is known**, intermediate files **MUST** prefer the **same filesystem/mount** as that destination (writable parent of the final path) when practical.  
2. To **move or publish** a completed file to its final path, code **MUST** use **`shutil.move`** (or a thin wrapper that only calls `shutil.move`).  
   - Same mount → rename.  
   - Cross-device → copy then remove source.  
3. Code **MUST NOT** use bare **`os.replace`**, **`os.rename`**, **`pathlib.Path.replace`**, or **`pathlib.Path.rename`** alone as the sole publish path when source may be system temp and destination may be another mount.  
4. **`shutil.copy2` / `copy` / `copyfile`** are copy-only — if used, define whether source is kept or deleted; they are not a complete move by themselves.  
5. Intermediate temps **MUST** be cleaned on success and failure paths (best-effort).

### Corresponding APIs (portable reference)

| Intent | Prefer | Avoid as sole cross-mount publish |
|--------|--------|-----------------------------------|
| Move/publish file | **`shutil.move(src, dst)`** | bare **`os.replace`**, **`os.rename`** |
| pathlib-oriented move | `Path` + **`shutil.move`** | bare **`Path.replace`**, **`Path.rename`** across mounts |
| Copy keep source | `shutil.copy2` | treating copy as move without unlink policy |

### Implementation Notes (fill when specializing)

| Field | This project |
|-------|----------------|
| **Publish API used** | e.g. `shutil.move` via helper `{{PROMOTE_HELPER_NAME}}` |
| **Temp staging policy** | e.g. same parent as final output when writable |
| **Product ops REQ (if any)** | peer key that applies these rules to a pipeline |

## 5. Rule for Handling Missing pip Packages (Sacred)

When a required package is missing:

```python
try:
    import ChronicleLogger
except ImportError:
    print("ERROR: ChronicleLogger is required. Please run: pip install ChronicleLogger")
    sys.exit(1)
```

- Always provide a clear installation instruction.
- Never crash silently or continue in a broken state.

## 6. Protection Rule (Sacred)

**Future implementation MUST follow**:
- Strict OOP design using `StateLogic` + `Attr()`
- Single Source of Truth rule
- Centralized output/logger module as SSOT for output and path resolution
- The detailed OOP rules above (new member variables via `Attr()`, no signature simplification, no class flattening, flattened access pattern)

**Future AI or developers MUST NOT**:
- Use procedural scripts instead of proper OOP classes
- Bypass the centralized output/logger module
- Remove or weaken any Protection Zone
- Hard-code storage paths
- Ignore the SSOT role of requirement documents
- Simplify method signatures or flatten class structure when adding new features
- Cite `template-*.md` or `skill-*.md` as behavioral authority in **product source** comments
- Invent or leave non-existent `requirement-*.md` paths in product source headers
- Use bare cross-mount `os.replace` / `os.rename` / `Path.replace` / `Path.rename` as the sole file publish path (use **`shutil.move`**)
- Assume system temp and user media always share one filesystem

**Product-source documentation authority:** module/class comments that claim ALIGNMENT must cite only live `docs/requirements/requirement-*.md` files. Agents may load templates/skills while coding; those paths are not product law. See `template-defensive-practices.md` §2.7.

---


## Design-time verification

| Gate | Artifact | Phase |
|------|----------|-------|
| Skill | `skill-python-cli-coding` | Review |
| Multi-mount publish | specialized suite or manual TP | Design |

**RTM:** `../tests/template-requirement-test-traceability.md` §4.

**Last Updated**: 2026-08-09 (§4b shutil.move / multi-mount temps)  
**Owner**: Python Architecture Layer (Generalized Template)  
**Alignment**: Fully synchronized with `template-python-classes.md`, `template-python-error-handling.md`, `template-python-project-structure.md`, `docs/terminologies/python-cli-architecture.md` / `template-python-system-architecture.md`, `template-defensive-practices.md` §2.7, `skill-python-cli-coding` §2.4b, and **CIAO Principles 1, 2, 3, 4, 11, 20 (v2.10.2)** (https://github.com/cloudgen/ciao).

---

**How to specialize this template**:
1. Copy to `docs/requirements/requirement-python-coding-style.md` (target name after specialization; create only when needed).
2. Replace `{{APP_NAME}}` and `{{MAIN_ORCHESTRATOR_CLASS}}` with concrete values for this project.
3. Fill §4b Implementation Notes (publish helper, staging policy, ops peer if any).
4. Update `docs/requirements/index.md` (and master requirements index if the project uses one).
5. Keep the OOP rules, flattened access pattern, and **shutil.move** multi-mount rules intact.
6. Do not leave conversion session notes, absolute host paths, or product-specific names in the specialized file.