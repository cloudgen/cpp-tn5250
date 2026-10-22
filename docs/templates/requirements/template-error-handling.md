---
name: error-handling
id: LM-ERROR-HANDLING
kind: law-mold
description: >
  Portable law mold. Cite as LM-ERROR-HANDLING (path secondary).
---

**file**: template-error-handling.md
**Status**: Active (Version 1.0.0 – Converted & Generalized from template form docs/templates/requirements/template-error-handling.md)
**Project**: Any CIAO-Lite Project (reusable template)
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

## 1. Purpose

This template defines the defensive error handling strategy for CIAO-Lite CLI tools and scripts.

It ensures the tool fails loudly and clearly for critical problems while providing graceful degradation for non-critical issues, always with actionable guidance for the user.

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
| **Error handling** | `docs/terminologies/error-handling.md` | `product-law` | Primary vocabulary |
| **SSOT of stderr** | `docs/terminologies/single-source-of-truth-of-stderr.md` | `channel-io` | Error channel |
| **SSOT of stdout** | `docs/terminologies/single-source-of-truth-of-stdout.md` | `channel-io` | Success channel purity |

**SSOT types used:** `channel-io` · `meta-catalog` · `policy` · `product-law`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Core Error Handling Rules (Mandatory)

### 2.1 Single Source of Error Output

- All errors **MUST** go through the centralized error output functions (e.g. `out_error()` and `out_die()`).
- Never use raw `echo`, `printf`, or `cat` for error messages.
- `out_die()` (or equivalent fatal error function) must:
  - Print the error via the central output system
  - Output a proper JSON error when `--json` mode is active
  - Exit with a non-zero status (usually `exit 1`)

### 2.2 Fail Fast vs Graceful Degradation

- **Critical failures** (cannot create required storage, corrupted critical files, invalid input that would cause data loss, permission issues on critical paths, network failure during self-update, digest mismatch on verified downloads) → **Fail fast** using `out_die()` (or equivalent).
- **Unknown argv command** (dispatcher token after flag parse) → **Fail fast** (`out_die` / non-zero). Proof **TP-CLI-06**. **MUST NOT** use this path for a TTY **menu** typo.
- **Invalid TTY menu choice** (unused number, unknown name, nested-layer typo at **any menu layer**) → **Graceful recovery**: `out_error()` (not `out_die()`), reprint **this** layer, re-prompt. Proof **TP-CLI-19**. Law **`LM-CLI-DEFAULT-INTERACTION`** §4 item 8c.
- **Non-critical issues** (optional feature unavailable, fallback storage used, non-fatal backup failure, optional component missing) → Use warning level (`out_warn()`) and continue when possible.
- Always provide **actionable recovery instructions** when an error occurs.

### 2.3 Non-Interactive Safety

- Never hang waiting for user input in non-interactive mode (`curl | sh`, CI/CD, Docker build, scripts, etc.).
- Use safe defaults and automatic fallbacks.
- Error messages must remain clear and useful even in `--quiet` or `--json` mode.

## 3. Recommended Error Patterns

### Primary Pattern (Recommended)
```sh
command || out_die "Descriptive error message with recovery hint"

if [ ! -f "${REQUIRED_FILE}" ]; then
    out_die "Required file '${REQUIRED_FILE}' not found. Please run the setup command first."
fi
```

### Graceful Degradation Example
```sh
if ! mkdir -p "${STORAGE_DIR}" 2>/dev/null; then
    STORAGE_DIR="/tmp/${APP_NAME}-fallback"
    out_warn "Primary storage unavailable. Using fallback: ${STORAGE_DIR}"
fi
```

### JSON + Human Mode Consistency
```sh
if [ "${JSON}" -eq 1 ]; then
    out_json_error "Operation failed" "error_code"
else
    out_error "Operation failed. See logs or run with --verbose for details."
fi
```

## 4. Why This Requirement Exists (Direct CIAO Alignment)

- **CIAO Principle 1 – Caution** (https://github.com/cloudgen/ciao): Assume things will go wrong (missing directories, permission issues, network failures, corrupted state). Prepare for failure.
- **CIAO Principle 2 – Intentional** (https://github.com/cloudgen/ciao): Every error must be actionable and guide the user toward recovery.
- **CIAO Principle 3 – Anti-fragile** (https://github.com/cloudgen/ciao): The tool should survive partial failures and help users recover instead of crashing silently or leaving them stuck.
- **CIAO Principle 4 / CIAO-Lite O · Principle 20 – Over-protect / Protect Against AI** (https://github.com/cloudgen/ciao): Loud, clear, and consistent error handling prevents silent failures that are extremely difficult to debug later.

## 5. Design Principles (CIAO / CIAO-Lite)

- **Caution (CIAO Principle 1)**: Assume failures will happen in storage, network, permissions, and external dependencies.
- **Intentional (CIAO Principle 2)**: Every error message must be clear, consistent, and include recovery guidance.
- **Anti-fragile (CIAO Principle 3)**: The system should survive non-critical failures and guide users to recovery.
- **Over-protect (CIAO Principle 4 / CIAO-Lite O · Principle 20)**: Consistent, loud error handling through a single source of truth prevents silent and hard-to-diagnose failures.

## 6. Protection Rule (Sacred)

**Future AI assistants, Grok, or maintainers MUST NOT**:
- Use raw `echo` or `printf` for any error messages.
- Remove or weaken the use of `out_die()` (or equivalent) for critical failures.
- Make critical errors silent in `--quiet` or `--json` mode.
- Remove recovery suggestions or actionable guidance from error messages.
- Bypass centralized error handling in storage, Docker, self-management, or configuration operations.
- Turn warnings into silent failures or make errors overly quiet without strong justification.

**Clear, loud, consistent, and actionable error handling is a deliberate defensive feature — not something to simplify or "clean up".**

---


## Design-time verification

| TP family / ID | Proof mold | Planned suite |
|----------------|------------|---------------|
| **TP-CLI-06,09** unknown + install fail loud | `../tests/template-shell-cli-test-plan.md` | `tests/test_cli.sh` |
| **TP-LC-09** bad channel | `../tests/template-install-lifecycle-test-plan.md` | `tests/test_install_lifecycle.sh` |

**RTM:** `../tests/template-requirement-test-traceability.md`

**Last Updated**: 2026-09-13 (TTY menu invalid choice recovers; unknown argv still fail-fast)  
**Owner**: {{OWNER}}  
**Alignment**: Fully synchronized with `docs/terminologies/error-handling.md` (shared language), `docs/requirements/index.md`, `docs/templates/requirements/template-output-requirements.md`, `docs/templates/requirements/template-defensive-practices.md`, `docs/templates/requirements/template-interactive-vs-noninteractive.md`, `docs/policies/policy-no-hardcode.md`, and **CIAO Principles 1, 2, 3, 4, 20 (v2.10.2)** (https://github.com/cloudgen/ciao).

---

**How to use this template**:
1. Copy to your project as `docs/templates/requirements/template-error-handling.md`.
2. Customize the list of what counts as "critical" vs "non-critical" failures for your specific application.
3. Implement consistent error handling functions (`out_error`, `out_die`, `out_json_error`, etc.).
4. Enforce the use of these patterns in all new code and during reviews.
5. Keep the Protection Rule and centralized error output requirement intact.