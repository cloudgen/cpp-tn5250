---
name: project-folder
id: LM-PROJECT-FOLDER
kind: law-mold
description: >
  Portable law mold. Cite as LM-PROJECT-FOLDER (path secondary).
---

**file**: template-project-folder.md
**Status**: Active (Version 1.0.0 – Converted & Generalized from template form docs/templates/requirements/template-project-folder.md)
**Project**: Any CIAO-Lite Project (reusable template)
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

## 1. Purpose

This template defines the official project folder structure and management rules for CIAO-Lite CLI tools.

**Critical Distinction**:
There are **two fundamentally different types** of project folders that must be clearly separated:

1. **Type 1 – CLI Tool’s Own Project Folders** (`{app-name}` folders)
2. **Type 2 – Target Application’s Project Folder** (especially when managing git clones or self-hosted instances)

Within **Type 1**, there are two sub-types depending on installation mode:

- **Type 1a – Per-User (Normal User Installation)**
- **Type 1b – Global / System-wide Installation**

This distinction is **mandatory** to prevent permission errors, path conflicts, and privilege issues.

### 1.1 Why This Requirement Exists (Direct CIAO Alignment)
- **CIAO Principle 1 – Caution** (https://github.com/cloudgen/ciao): Assume nothing about installation mode or multi-user environments.
- **CIAO Principle 10 – Least-Privilege User** (https://github.com/cloudgen/ciao): Global folders and target application folders must follow strict privilege rules.
- **CIAO Principle 4 / CIAO-Lite O · Principle 20 – Over-protect / Protect Against AI** (https://github.com/cloudgen/ciao): Explicit separation of folder types defends against permission and ownership mistakes.

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
| **Three-layer privilege** | `docs/terminologies/three-layer-privilege.md` | `product-law` | Layout by privilege type |
| **System user** | `docs/terminologies/system-user.md` | `identity-runtime` | Type 2 ownership paths |
| **Appname policy** | `docs/terminologies/appname-policy.md` | `identity-runtime` | Path identity |
| **Project-base-path** | `docs/terminologies/project-base-path.md` | `identity-runtime` | Application directory for the current environment |
| **Project-log-path** | `docs/terminologies/project-log-path.md` | `identity-runtime` | Log directory under that base; not the cache row |

**SSOT types used:** `identity-runtime` · `meta-catalog` · `policy` · `product-law`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Type 1 – CLI Tool’s Own Project Folders (`{app-name}`)

These folders belong exclusively to the CLI tool itself.

### 2.1 Type 1a – Per-User Installation (Normal User)

| Purpose               | Recommended Pattern                              | Notes |
|-----------------------|--------------------------------------------------|-------|
| Binary                | `~/.local/bin/{app-name}`                        | User-level binary |
| Configuration         | `~/.config/{app-name}/`                          | Per-user config |
| Cache / Volatile      | `~/.cache/cache-{app-name}/` or `/dev/shm/cache/cache-{app-name}` | The project's cache path. Not project-log-path. Prefer RAM when available |
| Data / Persistent     | `~/.local/share/{app-name}/`                     | Per-user data |
| Runtime / Temporary   | `/tmp/{app-name}-${USERNAME}-$$`                 | Must include PID |

**Rules for Type 1a**:
- All paths **must** include `${USERNAME}` for strict per-user isolation.
- Temporary folders **must** combine app-name + user-name + PID to prevent multiple users from sharing or conflicting with the same temporary directory.
- Must respect XDG base directory specification where possible.
- Must use centralized resolver functions.

### 2.2 Type 1b – Global / System-wide Installation

**Important Rule**:
Global `{app-name}` project folders are **only for storing global shared information**.  
**Only users with root/sudo privileges are allowed to modify these folders.**

| Purpose               | Recommended Pattern                     | Notes |
|-----------------------|-----------------------------------------|-------|
| Binary                | `/usr/local/bin/{app-name}`             | Requires root/sudo |
| Configuration         | `/etc/{app-name}/`                      | System-wide config (normal users: read-only) |
| Data / Persistent     | `/var/lib/{app-name}/`                  | System-wide shared data (root/sudo modification only) |
| Cache / Volatile      | `/var/cache/{app-name}/`                | System-wide cache. Not `/var/{app-name}/log` |
| Runtime / Temporary   | `/tmp/{app-name}`                       | Shared (use with caution) |

**Rules for Type 1b**:
- These paths require elevated privileges (root/sudo) to create and modify.
- Normal users **must not** be able to write to these folders.
- Must not be mixed with Type 1a (per-user) paths.

## 3. Type 2 – Target Application’s Project Folder

This refers to the project folder of the **application being managed** by the CLI (especially git clones or self-hosted services).

**Recommended Pattern**:
```
/opt/{system-user}/{project-name}
```

Example pattern: `/opt/{{SYSTEM_USER}}/{{PROJECT_NAME}}`

This path should:
- Reside under the dedicated system user’s home
- Follow the expected structure of the upstream project/repository
- Contain configuration, compose files (if applicable), and persistent data
- Be owned and operated exclusively by the dedicated least-privilege system user

**Rules for Type 2**:
- The CLI must respect the expected layout of the target project.
- The CLI may generate/maintain its own service definition files (e.g. `compose.yml`) inside this directory.
- All persistent data should reside under this directory tree.
- Must be created with correct ownership.
- Type 2 folders must **never** be mixed with Type 1 (CLI tool’s own) folders.

## 4. Core Rules (Mandatory)

- **Clear separation between all types and sub-types is sacred**.
- Type 1a and Type 1b must never share paths or allow cross-write access.
- Type 2 must never be mixed with Type 1 folders.
- **Temporary folders must combine app-name + user-name + PID** to avoid privilege problems in multi-user environments.
- Per-user isolation is mandatory for Type 1a.
- Only root/sudo can modify Type 1b and Type 2 folders.
- Always use central resolver functions.
- Backup before any modification.

## 5. Design Principles (CIAO / CIAO-Lite)

- **Caution** (CIAO Principle 1): Never mix per-user, global, and target application folders. Never use shared temporary directories without proper isolation.
- **Intentional** (CIAO Principle 2): Every path decision must clearly identify its type and sub-type.
- **Anti-fragile** (CIAO Principle 3): Survives different installation modes and multi-user environments through clear separation and PID-isolated temp folders.
- **Over-protect** (CIAO Principle 4 / CIAO-Lite O · Principle 20): Explicit typing of folders prevents permission, ownership, and privilege mistakes.

## 6. Protection Rule (Sacred)

**Future AI assistants, Grok, or maintainers MUST NOT**:
- Allow normal users to modify Type 1b (global) or Type 2 folders
- Mix Type 1a with Type 1b folders
- Mix Type 1 with Type 2 folders
- Use shared temporary folders without including app-name + user-name + PID
- Hardcode paths instead of using central resolver functions
- Remove or weaken the separation rules between folder types

**Violating this rule is considered a critical regression.**

---


## Design-time verification

| Gate | Artifact | Phase |
|------|----------|-------|
| Specialize → product suite or checklist | declare TP-IDs or checklist in specialized REQ | Design |
| RTM | `../tests/template-requirement-test-traceability.md` | Design |

When this mold has no executable TP family, mark **n/a** with reason in product `reviews/test-plan.md`.

**Last Updated**: 2026-06-04  
**Owner**: Storage & Project Structure Layer (Generalized Template)  
**Alignment**: Fully synchronized with `docs/requirements/index.md`, `docs/templates/requirements/template-defensive-practices.md`, `docs/templates/requirements/template-least-privilege-user.md`, and **CIAO Principles 1, 2, 3, 4, 9, 10, 20 (v2.10.2)** (https://github.com/cloudgen/ciao).

---

**How to use this template**:
1. Copy to your project as `docs/templates/requirements/template-project-folder.md`.
2. Replace `{app-name}` and example paths with your project’s actual names.
3. Define your recommended Type 2 path (if applicable).
4. Implement centralized resolver functions that respect these types.
5. Enforce the temp folder naming rule (app-name + user-name + PID) in all temporary directory creation.
6. Keep the Protection Rule and separation requirements intact.