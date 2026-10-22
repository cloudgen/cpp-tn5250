---
name: requirement-system-user
id: LM-REQUIREMENT-SYSTEM-USER
kind: law-mold
description: >
  Portable law mold. Cite as LM-REQUIREMENT-SYSTEM-USER (path secondary).
---

**file**: docs/templates/requirements/template-requirement-system-user.md
**Status**: Active (Version 1.1.0 – Type 1 allowlisted elev → Tables A/B/C on three-layer SSOT)
**Project**: {{PROJECT_NAME}} – {{SHORT_DESCRIPTION}}
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

# =============================================================================
# CIAO DEFENSIVE TEMPLATE - Least Privilege User Policy
# =============================================================================
#
# This is a reusable template for defining least-privilege execution policies
# in defensive CLI, installer, or platform management tools.
# It was converted from an obsolete project-specific requirement to serve
# as a generalized, placeholder-driven template for future CIAO-Lite projects.
#
# All specific values use {{PLACEHOLDER}} syntax. No project names, usernames,
# paths, or endpoints are hardcoded.
#
# Primary audience: General (policy level) — not tied to one runtime/language.
# Therefore the generic `template-` prefix is used per filename discipline.
# =============================================================================

## 1. Purpose

This template establishes the mandatory least-privilege user execution model for tools that must perform a mix of unprivileged and privileged operations. It protects both the end user (who should not need to run the entire tool as root) and any dedicated system accounts used for persistent services or data ownership.

The policy distinguishes command categories by required privilege level and mandates an **internal sudo escalation** pattern for normal users.

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
| **System user** | `docs/terminologies/system-user.md` | `identity-runtime` | Primary term |
| **Three-layer privilege** | `docs/terminologies/three-layer-privilege.md` | `product-law` | Type 2 context |
| **Least privilege** | `docs/terminologies/least-privilege.md` | `policy` | Minimum power; Type 2 identity under policy-least-privilege |
| **LLM escape** | `docs/terminologies/llm-escape.md` | `policy` | Skip context-switch = `E-PRIV-02`; unapproved egress = `E-NET-*` |

**SSOT types used:** `identity-runtime` · `meta-catalog` · `policy` · `product-law`

**Policies (normative bodies):** `docs/policies/policy-least-privilege.md` · `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

**Checklists:** **`CL-LEAST-PRIVILEGE`** · **`CL-LLM-ESCAPE`** when agent/ops power in scope

## 2. Core Rules / Requirements (Mandatory)

### 2.1 Command Type Classification
All commands exposed by the tool **MUST** be explicitly classified into one of three types:

| Type | Description | Execution Context | Example Operations |
|------|-------------|-------------------|--------------------|
| **Type 0** | Safe for normal user | Direct execution as invoking user | `status`, `help`, `version`, `whoami`, read-only queries |
| **Type 1** | Requires elevated privileges but supports internal escalation | Normal user invokes; tool internally uses `sudo` for the privileged sub-step | Package installation, Docker service control, system user creation, certificate renewal |
| **Type 2** | Dedicated least-privilege system user (CIAO Principle 9) | Must run as dedicated app/system user; context-switch if needed | App install/configure, service/data ops under app ownership — **not** “root-only” |

### 2.2 Internal Sudo Escalation Pattern (Sacred for Type 1)
- The tool **MUST** implement internal sudo escalation for Type 1 commands when the invoking user is not root.
- Preferred implementation: re-execute the specific privileged sub-command (or the whole command) via `sudo "$0" "$@"` or targeted `sudo` calls for individual operations.
- When Type 1 uses **allowlisted OS-tool** elev / product sudoers: elev **Tables A/B/C** live on **`LM-THREE-LAYER-PRIVILEGE-MODEL`** specialized law (or single peer SSOT) — this system-user mold **MUST NOT** invent a conflicting elev table; ship elev ⊆ Table A.
- The tool **MUST NOT**:
  - Require the user to run the entire CLI as root for routine Type 1 operations.
  - Cache or log the sudo password.
  - Fall back to "please run as root" instructions without attempting internal escalation first.
- Sudo configuration on the target system is the responsibility of the administrator (e.g., passwordless sudo for the dedicated {{SYSTEM_USER}} or appropriate group).

### 2.3 Dedicated System User for Services
When the tool manages long-running services or persistent data:
- A dedicated, non-login system user ({{SYSTEM_USER}}) **SHOULD** be created during installation / first-run setup.
- All persistent files, volumes, sockets, and service processes **SHOULD** be owned by this dedicated user.
- The CLI itself (when run by a normal human) interacts with these resources via controlled escalation (Type 1) rather than by running as the system user directly.

### 2.4 Protection of the Dedicated System Account
- The dedicated {{SYSTEM_USER}} account **MUST** be locked (no password login, no shell) unless explicitly required for debugging under controlled conditions.
- All management of the account and its resources must go through the tool's Type 1 paths or explicit admin procedures.

### 2.5 Why This Requirement Exists (Direct CIAO Alignment)
- **CIAO Principle 10 – Least-Privilege User** (https://github.com/cloudgen/ciao): The tool must allow normal users to perform necessary privileged operations without forcing the entire process to run with elevated privileges from the start.
- **CIAO Principle 1 – Caution**: Assume the invoking user is a normal account on a multi-user system; do not assume root.
- **CIAO Principle 3 – Anti-fragile**: The internal sudo pattern survives both interactive human use and automated/CI scenarios while still providing clear failure modes when sudo is unavailable or denied.

## 3. Design Principles (CIAO / CIAO-Lite)

- **Caution (CIAO Principle 1)**: Never assume the CLI starts with root privileges. Always provide a safe path for normal users via internal escalation.
- **Intentional (CIAO Principle 2)**: Command types (Type 0/1/2) are explicitly documented and enforced so that future maintainers and AI assistants cannot accidentally weaken the privilege model.
- **Anti-fragile (CIAO Principle 3)**: The policy works across interactive terminals, `curl | sh` installers, CI/CD pipelines, and containers without requiring constant root.
- **Over-protect (CIAO Principle 4 / CIAO-Lite O · Principle 20)**: The internal sudo pattern and dedicated system user rules are protected zones; they must not be simplified or removed for "convenience."

## 4. Protection Rule (Sacred)

**Future AI assistants, Grok, or maintainers MUST NOT**:

- Remove or weaken the Type 0 / Type 1 / Type 2 classification.
- Replace the internal sudo escalation pattern with instructions that tell the user to "run the whole command as root".
- Hardcode concrete usernames, project-specific paths, or service names inside the generated content (use `{{SYSTEM_USER}}` / `{{PLACEHOLDER}}` instead).
- Assume the tool always runs as root or always runs as a normal user — both paths must be supported.
- Delete or bypass the "Why This Requirement Exists (Direct CIAO Alignment)" subsection.
- Convert this template back into a project-specific requirement without re-applying the full upstream analysis and placeholder discipline.
- Skip Type 2 **context switch** to `{{SYSTEM_USER}}` or run app/data work as root for convenience (`PP-A-08` / `E-PRIV-01`/`E-PRIV-02`) — violates [`policy-least-privilege.md`](../../policies/policy-least-privilege.md).
- Perform unapproved external access while specializing/implementing (`PP-A-16` / `E-NET-*`); use **`CL-LLM-ESCAPE`** when Review/Security gates escape risk.

Violating any of the above is considered a **critical regression** against the project's defensive documentation layer and **least-privilege / LLM-escape policy**.


## Design-time verification

| Gate | Artifact | Phase |
|------|----------|-------|
| Specialize → product suite or checklist | declare TP-IDs or checklist in specialized REQ | Design |
| RTM | `../tests/template-requirement-test-traceability.md` | Design |

When this mold has no executable TP family, mark **n/a** with reason in product `reviews/test-plan.md`.

**Last Updated**: 2026-08-07 (v1.1.0 – allowlisted Type 1 elev tables via LM-THREE-LAYER-PRIVILEGE-MODEL) 
**Owner**: Defensive Policy Layer (converted from obsolete installer-era requirement)  
**Alignment**: **`LM-LEAST-PRIVILEGE-USER`** · **`LM-THREE-LAYER-PRIVILEGE-MODEL`** · harness **`policy-least-privilege`** · terms `system-user` · `least-privilege` · `llm-escape` · gates **`CL-LEAST-PRIVILEGE`** · **`CL-LLM-ESCAPE`** · CIAO Principles 1, 3, 4, 9, 10, 20 (v2.10.2) (https://github.com/cloudgen/ciao).

---

**Conversion Notes (for maintainers)**:
- Original file `docs/requirements/requirement-least-privilege-user.md` was marked obsolete after the v1.0.0 reset (installer functionality removed; CLI is now a pure Node.js platform client).
- This template preserves the core defensive principle so it can be re-specialized for future projects or companion shell components that still require mixed-privilege behavior.
- When specializing this template into a project-specific `requirement-*.md`, replace all `{{PLACEHOLDER}}` values and add concrete examples relevant to that project's command surface.