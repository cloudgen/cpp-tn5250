---
name: python-output-requirements
id: LM-PYTHON-OUTPUT-REQUIREMENTS
kind: law-mold
description: >
  Portable law mold. Cite as LM-PYTHON-OUTPUT-REQUIREMENTS (path secondary).
---

**file**: docs/templates/requirements/template-python-output-requirements.md
**Status**: Active (Version 1.0.0 – Generalized reusable template for CIAO-Lite Python PyPI Execution Projects)
**Project**: {{APP_NAME}} – Python PyPI Execution Project / CLI Tool
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

# Template: Python Output Requirements

## 1. Purpose

This template defines the mandatory output behavior for CIAO-Lite Python PyPI Execution Projects (CLI tools).

It ensures that every piece of user-facing or machine-readable output is produced **exclusively** through a centralized output/logging module, respects `quiet_mode` and `json_mode` states, and follows a clean, flattened access pattern from within `StateLogic` classes.

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
| **SSOT of stdout** | `docs/terminologies/single-source-of-truth-of-stdout.md` | `channel-io` | stdout purity |
| **SSOT of stderr** | `docs/terminologies/single-source-of-truth-of-stderr.md` | `channel-io` | stderr channel |
| **Python CLI architecture** | `docs/terminologies/python-cli-architecture.md` | `product-law` | Output module |
| **Project log content type** | `docs/terminologies/project-log-content-type.md` | `channel-io` | Kinds stored in the dated log. Cite only. **gnome-debug** is one kind. |
| **UI view for an app log** | `docs/terminologies/ui-view-for-app-log.md` | `channel-io` | HTML table for one log file in the main web view. Cite only. The non-UI show command prints the file bytes unchanged. |

**SSOT types used:** `channel-io` · `meta-catalog` · `policy` · `product-law`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Centralized Output Module as Single Source of Truth (Sacred)

**All output MUST go through the centralized output module** (e.g. `ChronicleLogger` or equivalent).

A [ui-view-for-app-log](../../terminologies/ui-view-for-app-log.md) is the HTML table for one log file. Cite that term. Do not paste a product palette. The non-UI show command prints the file bytes unchanged.

This includes:
- Normal human-readable messages
- Success / info / warning / error messages
- JSON output (`--json` mode)
- Debug / internal logging
- Path resolution for user data

**Forbidden mechanisms**:
- Raw `print()`
- `sys.stdout.write()` / `sys.stderr.write()`
- Direct use of Python `logging` module outside the centralized module
- Any shell-style output in Python code

## 3. StateLogic Integration (Mandatory)

The main orchestrator class (`{{MAIN_ORCHESTRATOR_CLASS}}`) **MUST** declare the following as `Attr()` member variables:

```python
Attr(self, attrName='quiet_mode', value=False)
Attr(self, attrName='json_mode', value=False)
```

### Output Behavior Rules

| Mode     | `quiet_mode` | `json_mode` | Behavior |
|----------|--------------|-------------|----------|
| Normal   | False        | False       | Full human-readable output with progress |
| Quiet    | True         | False       | Only errors + final summary |
| JSON     | True         | True        | Exactly **one** clean JSON object at the very end. No other text on stdout. |

**Important Rules**:
- When `json_mode` is `True`, the class **MUST** suppress all non-JSON output.
- JSON output must be produced by a dedicated method (e.g. `self.output_json(...)`).
- All output methods must check the current state of `quiet_mode` and `json_mode` before writing.

## 4. Flattened Output Access Pattern (Mandatory)

Inside any `StateLogic` subclass, output methods **MUST** be called directly on `self`:

**Correct (Required)**:
```python
self.output_text("Starting sync...")
self.output_success("File uploaded successfully")
self.output_json({"status": "ok", "files": 42})
self.log_message("Internal debug info", level="DEBUG")
```

**Forbidden**:
```python
self.logger.output_text(...)           # Wrong
self.chronicle_logger.xxx(...)         # Wrong
```

This "flattened" pattern reduces nesting and keeps all output centralized.

## 5. Core Output Methods (Expected Interface)

| Method                    | Purpose                              | Respects quiet/json |
|---------------------------|--------------------------------------|---------------------|
| `output_text(msg)`        | General informational message        | Yes                 |
| `output_success(msg)`     | Success message                      | Yes                 |
| `output_warn(msg)`        | Warning                              | Yes                 |
| `output_error(msg)`       | Error message                        | Yes                 |
| `output_json(data)`       | Machine-readable JSON output         | Forces quiet        |
| `log_message(msg, level)` | Internal / debug logging             | Respects debug_mode |

## 6. Design Principles (CIAO / CIAO-Lite)

- **Caution (CIAO Principle 1)**: Assume output can be consumed by both humans and machines. Never mix human text with JSON.
- **Intentional (CIAO Principle 2)**: Every output path is deliberate and goes through one controlled mechanism.
- **Anti-fragile (CIAO Principle 3)**: The system behaves correctly in `--quiet`, `--json`, and normal modes without special-casing throughout the codebase.
- **Over-protect (CIAO Principle 4 / CIAO-Lite O · Principle 20)**: Strict centralization prevents output pollution and inconsistent behavior.

## 7. Protection Rule (Sacred)

**Future implementation MUST follow**:
- All output and logging must go exclusively through the centralized output module.
- `quiet_mode` and `json_mode` must be declared as `Attr()` and respected by all output methods.
- Use only the flattened access pattern (`self.output_*` / `self.log_message`).

**Future AI or developers MUST NOT**:
- Introduce any raw `print()`, `sys.stdout`, or alternative logging mechanisms.
- Bypass the centralized output module.
- Add new output methods that do not respect `quiet_mode` / `json_mode`.
- Remove or weaken the flattened access requirement.
- Mix human-readable text into JSON output.

Violating this rule is considered a **critical regression**.

---


## Design-time verification

| Gate | Artifact | Phase |
|------|----------|-------|
| Skill | `skill-python-cli-coding` | Review |

**RTM:** `../tests/template-requirement-test-traceability.md` §4.

**Last Updated**: 2026-10-05  
**Owner**: Output & Logging Layer (Generalized Template)  
**Alignment**: Fully synchronized with `template-python-classes.md`, `template-python-coding-style.md`, `template-python-error-handling.md`, and **CIAO Principles 1, 2, 3, 4, 20 (v2.10.2)** (https://github.com/cloudgen/ciao).

---

**How to specialize this template**:
1. Copy to `docs/requirements/requirement-python-output-requirements.md` (target name after specialization; create only when needed).
2. Replace `{{APP_NAME}}` and `{{MAIN_ORCHESTRATOR_CLASS}}` with concrete values for this project.
3. Update `docs/requirements/index.md` (and master requirements index if the project uses one).
4. Keep the centralized output module and flattened access pattern requirement intact.
5. Do not leave conversion session notes, absolute host paths, or product-specific names in the specialized file.