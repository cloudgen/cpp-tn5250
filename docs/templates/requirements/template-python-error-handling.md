---
name: python-error-handling
id: LM-PYTHON-ERROR-HANDLING
kind: law-mold
description: >
  Portable law mold. Cite as LM-PYTHON-ERROR-HANDLING (path secondary).
---

**file**: template-python-error-handling.md
**Status**: Active (Version 1.0.0 – Converted from template form docs/templates/requirements/template-python-error-handling.md)
**Project**: Any CIAO-Lite Python Project (reusable template)
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

# Template: Python Error Handling

**Shared language:** `docs/terminologies/error-handling.md` (CLI + web + FSM; this template specializes **Python CLI / StateLogic**).

## 1. Purpose

This template defines how Python implementations in CIAO-Lite projects must handle errors while remaining safe, informative, and non-destructive.

It emphasizes the use of `StateLogic` + `Attr` for error state management and routes all output through a centralized logging/output system (e.g. `ChronicleLogger`).

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
| **Error handling** | `docs/terminologies/error-handling.md` | `product-law` | Error vocabulary |
| **Python CLI architecture** | `docs/terminologies/python-cli-architecture.md` | `product-law` | Python error path |

**SSOT types used:** `meta-catalog` · `policy` · `product-law`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Error Handling Principles

The implementation follows **CIAO-Lite** defensive design:

- **Caution** — Never lose user data. Prefer safe failure over risky continuation.
- **Intentional** — Every error has a clear, human-readable message routed through the central output system.
- **Anti-fragile** — The tool must recover gracefully or exit cleanly without leaving partial state.
- **Over-protect** — Mandatory pre-checks before any network or destructive operation.

### Core Error Categories (Recommended)

| Error Type                      | Detection Point             | Required Action                              | Output via Central Logger |
|---------------------------------|-----------------------------|----------------------------------------------|---------------------------|
| Invalid/missing configuration   | Startup / validation        | Immediate exit with clear instructions       | ERROR + help text         |
| Network / connectivity issues   | Any external call           | Graceful backoff + retry, then exit          | ERROR + suggested fix     |
| Resource not found              | Selection or flag           | List available options or exit cleanly       | ERROR + options list      |
| File read / permission error    | Local operations            | Skip file + continue (non-fatal)             | WARNING + continue        |
| Rate limiting / transient error | API calls                   | Pause, log, continue with remaining work     | WARNING + retry hint      |
| Dry-run mode                    | `--dry-run` flag            | No destructive/network operations            | INFO summary              |
| JSON output corruption          | `--json` mode               | Never mix human text with JSON               | Pure JSON or nothing      |

## 3. StateLogic Error Mapping & Resumption Rules (Mandatory)

All error handling **MUST** occur inside `StateLogic` classes.

- Every error condition **must** explicitly map to a corresponding named state via `Attr()`.
- The `operational_state` attribute is the single source of truth for error states.

**Recommended `operational_state` values** (declare via `Attr` in `__init__`):

- `"NORMAL"`
- `"PROCESSING"` (or domain-specific equivalent)
- `"BACKOFF"`
- `"ERROR"`
- `"EXIT"`

**Resumption Rule (Sacred)**:  
From **ANY** error state, the tool **MUST** support clean transition to one of the following:

- Normal operational state
- Backoff mode (less aggressive)
- Exit state (clean shutdown)

State transitions must only be performed through `StateLogic` methods.

## 4. State Management for Errors

The main orchestrator class must declare at minimum:

```python
Attr(self, attrName='operational_state', value="NORMAL")
Attr(self, attrName='error_count', value=0)
Attr(self, attrName='last_error_timestamp', value=None)
```

All errors must:
1. Increment `error_count`
2. Update `last_error_timestamp`
3. Transition `operational_state` according to the Resumption Rule
4. Log via the central output system (never use direct `print()`)

## 5. Output & Logging

- All messages must go through the centralized output/logging system.
- `--quiet`: Only final summary + errors
- `--json`: Single clean JSON object at the very end
- Never mix human text with JSON output

## 6. Design Principles (CIAO-Lite)

- **Caution**: Always validate state before proceeding with operations.
- **Intentional**: Error states are explicit and managed through `Attr`.
- **Anti-fragile**: Support resumption from error states without data loss.
- **Over-protect**: The Resumption Rule and centralized logging are protected.

## 7. Protection Rule (Sacred)

**Future AI assistants, Grok, or maintainers MUST NOT**:

- Use raw `print()` or `sys.exit()` outside the central output system.
- Bypass error state tracking or the Resumption Rule.
- Suppress or hide errors in `--quiet` or `--json` modes.
- Change error categories or resumption rules without updating this template and the master requirements.
- Remove or weaken the requirement to manage error state via `StateLogic` + `Attr`.

## 8. How to Specialize This Template

1. Copy this file and rename it to `requirement-python-error-handling.md` (target name after specialization; not a live file until created).
2. Adjust the `operational_state` values to match your domain (e.g. "SYNCING", "CLEANING").
3. Customize the error categories table for your specific operations.
4. Update the main class name and any domain-specific references.
5. Add the requirement to `docs/requirements/index.md`.
6. Keep the Protection Rule and Resumption Rule sections intact.

---


## Design-time verification

| Gate | Artifact | Phase |
|------|----------|-------|
| Skill | `skill-python-cli-coding` | Review |

**RTM:** `../tests/template-requirement-test-traceability.md` §4.

**Last Updated**: 2026-06-16  
**Owner**: Error Handling Layer (Generalized Template)  
**Alignment**: Fully synchronized with `docs/templates/requirements/template-python-coding-style.md`, `docs/templates/requirements/template-python-classes.md`, `docs/requirements/index.md`, and **CIAO Principles 1, 2, 3, 4, 20 (v2.10.2)**.