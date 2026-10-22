---
name: python-classes
id: LM-PYTHON-CLASSES
kind: law-mold
description: >
  Portable law mold. Cite as LM-PYTHON-CLASSES (path secondary).
---

**file**: template-python-classes.md
**Status**: Active (Version 1.0.0 – Converted from template form docs/templates/requirements/template-python-classes.md)
**Project**: Any CIAO-Lite Python Project (reusable template)
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

# Template: Python Classes using StateLogic + Attr

## 1. Purpose

This template defines the mandatory class structure for Python implementations in CIAO-Lite projects.  
It enforces the **OOP Rule** and requires the use of the **StateLogic + Attr** pattern for all state management.

This template is designed to be specialized into a project-specific `requirement-python-classes.md` file (target name after specialization; not a live file until created).

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
| **Python CLI architecture** | `docs/terminologies/python-cli-architecture.md` | `product-law` | StateLogic / class model |

**SSOT types used:** `meta-catalog` · `policy` · `product-law`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Core OOP Rule (Python)

**The OOP rule is the core architectural principle** for all Python code in the project.

- **Everything must be implemented as clean, independent classes**.
- **No procedural scripts** or long top-level functions are allowed in the main application logic.
- **Class responsibilities must stay clear and focused**.

**Specific rules when adding new features or making changes**:
- **New features** → Add new member variables using `Attr()` instead of simplifying existing method signatures.
- **Method signatures** → Do **NOT** simplify or shorten them. Keep explicit parameters and clear names.
- **Class structure** → Do **NOT** flatten classes.
- **Logger access** → Always use the flattened pattern `self.log_message(...)`, `self.output_text(...)`, etc.

## 3. State Management — Attr + StateLogic (Mandatory)

**All major classes that manage state must**:
- Inherit from `StateLogic` (for Finite State Machine behavior)
- Declare **all** state using the `Attr` descriptor in `__init__()`
- Access state only via getter/setter methods
- For lists: use `self.map_array(entry)` — never use `.append()` directly on state

**Never**:
- Use direct attribute assignment (`self.xxx = yyy`)
- Use long parameter lists to pass state between methods
- Flatten classes or turn methods into procedural functions

## 4. Recommended Classes & Predefined States

| Class                        | Base Class      | Responsibility                                      | Key State Variables (via Attr) |
|------------------------------|-----------------|-----------------------------------------------------|--------------------------------|
| `{{MAIN_CLASS}}`             | `StateLogic`    | Main orchestrator, CLI, workflow coordination       | `operational_state`, `quiet_mode`, `json_mode`, `dry_run`, ... |
| `CookieManager`              | `StateLogic`    | Cookie / session management                         | `cookie_db_path`, ... |
| `FileUploader`               | `StateLogic`    | Upload logic                                        | `current_file`, `upload_mode` |
| `BackupManager`              | `StateLogic`    | Backup operations before destructive actions        | `local_directory`, `backup_mode` |

### Mandatory Predefined States (Example)

In the main class `__init__()`, the following `Attr` declarations are recommended:

```python
Attr(self, attrName='quiet_mode', value=False)
Attr(self, attrName='json_mode', value=False)
Attr(self, attrName='dry_run', value=False)
Attr(self, attrName='operational_state', value="NORMAL")
Attr(self, attrName='error_count', value=0)
Attr(self, attrName='last_error_timestamp', value=None)
```

## 5. Protection Rule (Sacred)

**Future AI assistants, Grok, or maintainers MUST NOT**:

- Put cookie/session logic outside a dedicated `CookieManager` class (or equivalent).
- Use global variables or long parameter lists for state.
- Bypass or remove any `Attr` declarations.
- Flatten classes or simplify method signatures when adding new features.
- Remove or weaken `StateLogic` + `Attr` usage.
- Rename this file back to a project-specific name without strong justification.

## 6. Design Principles (CIAO / CIAO-Lite)

- **Caution (CIAO Principle 1)**: State must be managed explicitly and safely through descriptors.
- **Intentional (CIAO Principle 2)**: Every class has a clear, single responsibility.
- **Anti-fragile (CIAO Principle 3)**: The `StateLogic` + `Attr` pattern survives refactoring and team changes.
- **Over-protect (CIAO Principle 4 / CIAO-Lite O · Principle 20)**: The OOP structure and state management rules are protected zones.

## 7. How to Specialize This Template

1. Copy this file and rename it to `requirement-python-classes.md` (target name after specialization; not a live file until created).
2. Replace `{{MAIN_CLASS}}` and other placeholders with your actual class names.
3. Add or remove classes according to your project's needs.
4. Update `docs/requirements/index.md` to include the new requirement.
5. Keep the Protection Rule section intact.

---


## Design-time verification

| Gate | Artifact | Phase |
|------|----------|-------|
| Skill | `skill-python-cli-coding` | Review |

**RTM:** `../tests/template-requirement-test-traceability.md` §4.

**Last Updated**: 2026-06-16  
**Owner**: Python Architecture Layer (Generalized Template)  
**Alignment**: Fully synchronized with `docs/templates/requirements/template-python-coding-style.md`, `docs/requirements/index.md`, and **CIAO Principles 2, 3, 4, 20 (v2.10.2)**.