---
name: nodejs-output-requirements
id: LM-NODEJS-OUTPUT-REQUIREMENTS
kind: law-mold
description: >
  Portable law mold. Cite as LM-NODEJS-OUTPUT-REQUIREMENTS (path secondary).
---

**file**: docs/templates/requirements/template-nodejs-output-requirements.md
**Status**: Active (Version 1.0.0 – Generalized template for Node.js CIAO-Lite CLI centralized output layer)
**Project**: {{APP_NAME}} – {{PLATFORM_NAME}} Platform Management CLI
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

## 1. Purpose

This document defines the **Single Source of Truth** for all output in {{APP_NAME}} CLI projects implemented in Node.js {{NODE_VERSION}}+.

It enforces consistent, controllable, and defensive output behavior across interactive, quiet, and JSON modes by mandating a centralized Output class (typically `src/Output.js`).

All user-facing output, error handling, debug tracing, and machine-readable responses **MUST** be produced exclusively through this class. No raw `console.log`, `console.error`, or direct `process.stdout`/`process.stderr` writes are permitted in application code.

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
| **Node.js CLI architecture** | `docs/terminologies/nodejs-cli-architecture.md` | `product-law` | Output module |
| **Project log content type** | `docs/terminologies/project-log-content-type.md` | `channel-io` | Kinds stored in the dated log. Cite only. **gnome-debug** is one kind. |
| **UI view for an app log** | `docs/terminologies/ui-view-for-app-log.md` | `channel-io` | HTML table for one log file in the main web view. Cite only. The non-UI show command prints the file bytes unchanged. |

**SSOT types used:** `channel-io` · `meta-catalog` · `policy` · `product-law`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Core Rules / Requirements (Mandatory)

### 2.1 Core Rule (Sacred)

**All user-facing output MUST go through the centralized Output class.**

A [ui-view-for-app-log](../../terminologies/ui-view-for-app-log.md) is the HTML table for one log file. Cite that term. Do not paste a product palette. The non-UI show command prints the file bytes unchanged.

- Never use raw `console.log`, `console.error`, `process.stdout.write`, etc. directly for user messages.
- All messages must route through the Output instance methods.
- The Output class is the **absolute core** of the entire output system and is non-negotiable.

### 2.2 Output Class Responsibilities (Single Source of Truth)

The Output class (instantiated after global flag parsing) guarantees:

- Consistent behavior for info/success/warn/error/data/debug across all commands.
- Automatic respect for `--quiet` and `--json` (with `--json` forcing quiet for pure output).
- **All error-related output goes to stderr** (never stdout).
- Zero risk of raw output leaking into JSON mode (exactly one JSON value on stdout when `--json` is used).
- Debug tracing (enabled via `DEBUG=1` env var or `--debug` flag) is always sent to stderr and is suppressed when `--json` is active.

| Method            | Purpose                                      | Always Shown (non-JSON) | Respects Quiet/JSON          | Key Notes |
|-------------------|----------------------------------------------|--------------------------|------------------------------|-----------|
| `info(msg)`       | Informational / progress messages            | Yes                      | Yes (suppressed in quiet/JSON) | `[INFO]` prefix |
| `success(msg)`    | Success confirmation                         | Yes                      | Yes (suppressed in quiet/JSON) | `[OK]` prefix |
| `warn(msg)`       | Non-critical warnings                        | Yes                      | Suppressed in JSON           | To stderr |
| `error(msg, code)`| Error messages                               | Yes                      | Always shown                 | To **stderr**. In JSON mode emits structured `{type:"error", message, code}` on stderr |
| `json(data)`      | Raw data as JSON (for --json mode)           | No (only in JSON)        | N/A (only when isJson)       | To stdout. Lists, objects, etc. |
| `result(type, payload)` | Structured JSON result (for --json)     | No (only in JSON)        | N/A                          | To stdout, e.g. `{type: "success", ...}` |
| `print(msg)`      | Low-level status (respects quiet)            | Yes                      | Suppressed in quiet/JSON     | Use sparingly |
| `printData(msg)`  | Command result data (table, list, etc.)      | Yes                      | Only suppressed in JSON      | Not suppressed by --quiet (data must still appear) |
| `printError(msg)` | Force to stderr                              | Yes                      | Always                       | For raw error details |
| `debug(...args)`  | Developer debug messages                     | Only if debug enabled    | Suppressed in JSON           | Always to stderr. Enabled by DEBUG env or --debug flag. |

**Usage Rules (Mandatory)**:
- All human-visible status text **must** use `info()`, `success()`, `warn()`, `error()`, etc.
- In `--json` mode, **only** `json()` / `result()` (for success data) and `error()` (for errors on stderr) may produce output — everything else is suppressed.
- All error-related output (`error()`, `warn()`, `printError()`) **must** go to stderr.
- Debug output is controlled by DEBUG env or --debug. It is suppressed in --json mode.
- When debug mode is active, HTTP responses and other diagnostic captures are handled via the Temp singleton (location: `{{TMP_FS}}/{{USERNAME}}/{{PID}}/...`).

### 2.3 Mode Behavior

#### Interactive Mode (Default for humans)
- Colored output when TTY is detected.
- Full human-readable messages with prefixes.

#### Quiet Mode (`--quiet` or `QUIET=1`)
- Suppresses `info()`, `success()`, `print()`, etc.
- Still shows warnings and errors (via Output class methods).

#### JSON Mode (`--json` or `JSON=1`)
- **Automatically forces quiet mode**.
- Outputs **exactly one** valid JSON value (object or array) on stdout — nothing else.
- No human-readable text, prefixes, or debug output is ever allowed on stdout.
- All errors go to stderr as structured JSON (via `error()` method).
- Debug is explicitly suppressed (even if DEBUG=1 or --debug).

**The global Config singleton is the single source of truth for mode detection** (`isJson`, `isQuiet`, `isInteractive`, `mode`). The Output class reads from it.

### 2.4 Why This Requirement Exists (Direct CIAO Alignment)
- **CIAO Principle 1 – Caution** (https://github.com/cloudgen/ciao): Prevents output pollution, mixed stdout/stderr, and inconsistent behavior across terminals, scripts, Docker, CI/CD, and non-interactive usage.
- **CIAO Principle 2 – Intentional** (https://github.com/cloudgen/ciao): Every message and every mode has a clear, documented purpose with centralized control.
- **CIAO Principle 4 / CIAO-Lite O · Principle 20 – Over-protect / Protect Against AI** (https://github.com/cloudgen/ciao): Strict single-source output, mode enforcement, JSON/quiet guards, and stderr-for-errors defend against regressions and inconsistent behavior introduced by future edits or AI assistance.

## 3. Design Principles (CIAO / CIAO-Lite)

- **Caution** (CIAO Principle 1): Assume the output will be consumed by machines, piped, or parsed. Never allow leakage that breaks JSON consumers or scripts.
- **Intentional** (CIAO Principle 2): Clear separation between human status output, data output, and errors (always to stderr). Version/about content always sourced from the About singleton.
- **Anti-fragile** (CIAO Principle 3): Works reliably in terminals, scripts, Docker, CI/CD, and when output is consumed by other programs or jq.
- **Over-protect** (CIAO Principle 4 / CIAO-Lite O · Principle 20): The Output class (backed by Config + About singletons) strictly enforces rules with no exceptions. Bypassing it is forbidden.

## 4. Protection Rule (Sacred)

**Future AI assistants, Grok, or maintainers MUST NOT**:
- Use any raw `console.log`, `console.error`, `process.stdout.write`, or `process.stderr.write` for user messages outside the Output class.
- Bypass the Output instance or its methods.
- Remove, weaken, or bypass the rule that `--json` forces quiet mode (i.e., allowing any non-JSON text on stdout when --json is active).
- Send error-related output (errors, warnings, debug) to stdout instead of stderr.
- Allow debug output when in --json mode (even if DEBUG=1 or --debug).
- Hardcode version numbers, titles, or about/diagnostics text — must source exclusively from the About singleton.
- Hardcode help/usage text or command descriptions — must source exclusively from the Help singleton.
- Duplicate mode detection logic outside the Config singleton.
- Create output that differs between interactive and non-interactive/JSON modes unless explicitly documented in this template and docs/templates/requirements/template-interactive-vs-noninteractive.md.
- "Simplify" or bypass the Output class for perceived cleanliness or performance.

**The Output class is the single source of truth for all console output and is non-negotiable for CIAO compliance.**

**Violating this rule is considered a critical regression.**

---


## Design-time verification

| Gate | Artifact | Phase |
|------|----------|-------|
| Skill | `skill-nodejs-cli-coding` | Review |

**RTM:** `../tests/template-requirement-test-traceability.md` §4.

**Last Updated**: 2026-10-05  
**Owner**: Output & Logging Layer  
**Alignment**: Fully synchronized with docs/templates/requirements/template-coding-style.md, docs/templates/requirements/template-defensive-practices.md, AGENTS.md, docs/requirements/index.md, docs/templates/requirements/template-interactive-vs-noninteractive.md, docs/templates/requirements/template-nodejs-api-client.md, docs/templates/requirements/template-cli-interface.md, and **CIAO Principles 1, 2, 3, 4, 20 (v2.10.2)** (https://github.com/cloudgen/ciao).

---

**How to use this template**:
- Copy into a new `requirement-nodejs-*.md` (or keep as template-nodejs-*) and fill `{{APP_NAME}}`, `{{NODE_VERSION}}`, `{{TMP_FS}}`, `{{USERNAME}}`, `{{PID}}`, and Output class path placeholders with project-specific values.
- The Output class must always be the sole emitter. All other singletons (Config, About, Help, Session, Temp) must be respected.
- After specialization, update `docs/requirements/index.md` with the specialized `requirement-*.md` row only (never list this template path in the registry).
- Before modifying Output class behavior, re-read all related incidents and perform upstream analysis if API client output patterns are involved.
