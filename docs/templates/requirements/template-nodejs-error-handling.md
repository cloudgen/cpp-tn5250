---
name: nodejs-error-handling
id: LM-NODEJS-ERROR-HANDLING
kind: law-mold
description: >
  Portable law mold. Cite as LM-NODEJS-ERROR-HANDLING (path secondary).
---

**file**: docs/templates/requirements/template-nodejs-error-handling.md
**Status**: Active (Version 1.0.0 – Converted from template form docs/templates/requirements/template-error-handling.md; generalized for reusable Node.js CLI templates following CIAO)
**Project**: {{PROJECT_NAME}} – {{SHORT_DESCRIPTION}}
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

## 1. Purpose

**Shared language:** `docs/terminologies/error-handling.md` (CLI + web + FSM; this template specializes **Node.js CLI** + Output singleton + privilege UX).

This document defines the defensive error handling strategy used throughout a {{APP_NAME}} CLI implemented in Node.js v20+. It ensures the tool fails loudly and clearly when necessary, while providing graceful degradation in non-critical situations — **including privileged operations**.

It is a core part of the **CIAO / CIAO-Lite** defensive philosophy for Node.js command-line applications.

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
| **Node.js CLI architecture** | `docs/terminologies/nodejs-cli-architecture.md` | `product-law` | Node error path |

**SSOT types used:** `meta-catalog` · `policy` · `product-law`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Core Rules / Requirements (Mandatory)

### 2.1 Single Source of Error Output

- All errors **MUST** go through the centralized `{{OUTPUT_HANDLER_CLASS}}` (the single source of truth for all console output, typically implemented as a singleton or module-exported class such as `Output`).
- Never use raw `console.log` / `console.error` for error messages outside the centralized handler (except the top-level safety net in the main entry point).
- All error-related output goes to **stderr**.
- In `--json` mode, the error handler emits a structured JSON error object **on stderr** (never polluting stdout).

### 2.2 Fail Fast vs Graceful Degradation

- **Critical failures** (invalid state, permission issues on core paths, network failure during remote operations, etc.) → `{{OUTPUT_HANDLER}}.error(...)` + exit (or throw for fatal in async flows).
- **Non-critical issues** (optional feature degradation, fallback paths taken) → `{{OUTPUT_HANDLER}}.warn(...)`.

### 2.3 Privilege Handling (Special Rule – Not a Simple Error)

**Privileged operations MUST NOT be treated as immediate hard errors for normal users.**

- For any command that requires elevated privileges, the implementation **must** use internal escalation patterns appropriate for Node.js (e.g., re-spawn the process with `sudo`, check `process.getuid()` and provide clear guidance, or delegate to a privileged helper).
- This allows the runtime to naturally prompt for credentials when needed.
- Only after internal escalation fails (e.g., user cancels) should a real error be shown via the centralized handler.
- Normal users must be able to run privileged commands directly without getting an immediate “error + exit”.

### 2.4 Non-Interactive Safety

- Never hang waiting for user input in non-interactive mode (`--json`, piped execution, CI/CD, Docker, etc.).
- Use safe defaults and automatic fallbacks.
- Clear diagnostic messages even in quiet/JSON mode for errors (via the centralized handler; JSON errors on stderr).

### 2.x Why This Requirement Exists (Direct CIAO Alignment)
- **CIAO Principle 1 – Caution** (https://github.com/cloudgen/ciao): Assume users will run commands in the most convenient way and never surprise normal users with hard errors on privileged operations.
- **CIAO Principle 3 – Anti-fragile** (https://github.com/cloudgen/ciao): The CLI must survive both interactive human usage and automated/non-interactive environments without breaking UX.
- **CIAO Principle 10 – Least-Privilege User** (https://github.com/cloudgen/ciao): Strictly separate elevated operations while still providing smooth UX via internal escalation.

## 3. Design Principles (CIAO / CIAO-Lite)

- **Caution** (CIAO Principle 1): Assume things can and will go wrong, including privilege situations and non-interactive contexts.
- **Intentional** (CIAO Principle 2): Every error (and privilege escalation) must be actionable and user-friendly through a single, predictable handler.
- **Anti-fragile** (CIAO Principle 3): The CLI should survive partial failures and guide the user (or calling script) to recovery.
- **Over-protect** (CIAO Principle 4 / CIAO-Lite O · Principle 20): Loud, clear errors via the centralized handler prevent silent failures; explicit privilege handling prevents UX regressions across Node.js runtimes.

## 4. Protection Rule (Sacred)

**Future AI assistants, Grok, or maintainers MUST NOT**:
- Use raw `console.log`, `console.error`, or direct `process.stdout/stderr` writes for any error or warning messages outside the centralized `{{OUTPUT_HANDLER_CLASS}}`.
- Remove or weaken the centralized output handler for critical failures.
- Make critical errors silent in `--quiet` or `--json` mode.
- Treat privileged operations as immediate hard errors for normal users (must implement internal escalation appropriate to Node.js).
- Remove recovery suggestions or privilege escalation guidance from error messages.
- Bypass the handler in storage, remote API, or self-management code paths.

**Violating this rule is considered a critical regression.**

**Lessons Learned (CIAO Reflection)**:  
Privilege handling and centralized output were repeatedly sources of UX and consistency regressions in early implementations. Internal escalation + single handler is now explicitly required.

---


## Design-time verification

| Gate | Artifact | Phase |
|------|----------|-------|
| Skill | `skill-nodejs-cli-coding` | Review |

**RTM:** `../tests/template-requirement-test-traceability.md` §4.

**Last Updated**: 2026-06-09  
**Owner**: Error Handling & Resilience Layer  
**Alignment**: Fully synchronized with docs/templates/requirements/template-output-requirements.md, docs/templates/requirements/template-defensive-practices.md, docs/templates/requirements/template-cli-interface.md, docs/requirements/index.md, AGENTS.md, and **CIAO Principles 1, 3, 4, 9, 10, 20 (v2.10.2)** (https://github.com/cloudgen/ciao).

---

**How to use this template**:
- Instantiate your centralized output handler (e.g. `new Output()` or singleton) early after flag parsing.
- Route every `error()`, `warn()`, and fatal path through it.
- Document the exact handler class name in your concrete requirement.
- When activating a project-specific requirement, update `docs/requirements/index.md` with that `requirement-*.md` row only (never list this template path).