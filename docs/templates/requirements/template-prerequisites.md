---
name: prerequisites
id: LM-PREREQUISITES
kind: law-mold
description: >
  Portable law mold. Cite as LM-PREREQUISITES (path secondary).
---

**file**: template-prerequisites.md
**Status**: Active (Version 1.0.0 – Converted & Generalized from template form docs/templates/requirements/template-prerequisites.md)
**Project**: Any CIAO-Lite Project (reusable template)
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

## 1. Purpose

This template defines the **exact scope and behavior** of the system prerequisites / setup command (commonly named `prerequisites` or `setup`).

It is the **Single Source of Truth** for all system-level preparation required before project-specific operations can begin.

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
| **Ship unit** | `docs/terminologies/ship-unit.md` | `mention-only` | Runtime prerequisites for CLI |

**SSOT types used:** `mention-only` · `meta-catalog` · `policy`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Core Requirements (Mandatory)

The prerequisites command **must**:

- Run **only under root or sudo** (it performs system package installation). Use internal sudo pattern so normal users can invoke it directly.
- Install essential system packages required by the project (e.g. `git`, `curl`, `ca-certificates`, package managers, etc.).
- Install **Docker Engine** (official installation method) when Docker is required.
- Install **Docker Compose v2 plugin** (or equivalent) so that `docker compose` is available.
- Be **fully idempotent** — running it multiple times must be safe and produce no side effects.
- Support `--quiet` and `--json` flags.
- **Never** perform any project-specific operations (no git clone, no configuration file creation, no project directory setup).

## 3. Integration with Least-Privilege User Model

- The prerequisites command **must not** create or manage the dedicated project system user.
- After successful prerequisites, the next recommended step is usually the `install` command, which will:
  - Create the dedicated system user (if it does not exist).
  - Perform all subsequent operations **as the dedicated least-privilege user**.
- If the current user is **not** root/sudo (and cannot escalate), the command must stop with a clear error and do nothing.

## 4. Output & Error Handling

- All output **must** go through the centralized output system.
- On success: clear confirmation message + next-step guidance.
- On failure: fatal error with actionable message (e.g. "package installation failed", "Docker installation failed").
- In `--json` mode: return clean machine-readable JSON.

## 5. Why This Requirement Exists (Direct CIAO Alignment)

- **CIAO Principle 10 – Least-Privilege User** (https://github.com/cloudgen/ciao): System-level privileged operations (Type 1) must be strictly separated from project operations (Type 2 and Type 3).
- **CIAO Principle 1 – Caution** (https://github.com/cloudgen/ciao): Assume the system may be missing required packages or Docker. Provide a safe, repeatable way to prepare it.
- **CIAO Principle 2 – Intentional** (https://github.com/cloudgen/ciao): Clear separation between system preparation and project work prevents privilege leaks and fragile assumptions.

## 6. Design Principles (CIAO / CIAO-Lite)

- **Caution (CIAO Principle 1)**: Only perform system-level privileged work. Never mix with project operations.
- **Intentional (CIAO Principle 2)**: Clear scope and strict separation from user creation and project logic.
- **Anti-fragile (CIAO Principle 3)**: Idempotent design allows safe re-execution.
- **Over-protect (CIAO Principle 4 / CIAO-Lite O · Principle 20)**: Explicit rules prevent privilege escalation mistakes and scope creep.

## 7. Protection Rule (Sacred)

**Future AI assistants, Grok, or maintainers MUST NOT**:

- Add user/group management or dedicated user creation inside the prerequisites command.
- Remove Docker (or equivalent container runtime) installation when it is part of the project requirements.
- Allow the prerequisites command to run under a normal user without proper escalation.
- Bypass idempotency checks.
- Mix project operations (git clone, configuration, project directory creation) into prerequisites.
- Change the list of essential system packages without updating this document.

**Violating any of these is considered a critical regression.**

---


## Design-time verification

| Gate | Artifact | Phase |
|------|----------|-------|
| Specialize → product suite or checklist | declare TP-IDs or checklist in specialized REQ | Design |
| RTM | `../tests/template-requirement-test-traceability.md` | Design |

When this mold has no executable TP family, mark **n/a** with reason in product `reviews/test-plan.md`.

**Last Updated**: 2026-06-04  
**Owner**: System Architecture Layer (Generalized Template)  
**Alignment**: Fully synchronized with `docs/templates/requirements/template-least-privilege-user.md`, `docs/templates/requirements/template-requirement-system-user.md`, `docs/templates/requirements/template-cli-interface.md`, `docs/templates/requirements/template-defensive-practices.md`, `docs/requirements/index.md`, and **CIAO Principles v2.10.2** (https://github.com/cloudgen/ciao).

---

**How to use this template**:
1. Copy to your project as `docs/templates/requirements/template-prerequisites.md`.
2. Customize the list of required system packages and Docker installation steps.
3. Implement internal sudo logic so normal users can run the command.
4. Strictly separate this command from user creation and project operations.
5. Keep the Protection Rule and idempotency requirements intact.