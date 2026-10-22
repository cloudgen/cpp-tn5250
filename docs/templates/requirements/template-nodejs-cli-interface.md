---
name: nodejs-cli-interface
id: LM-NODEJS-CLI-INTERFACE
kind: law-mold
description: >
  Portable law mold. Cite as LM-NODEJS-CLI-INTERFACE (path secondary).
---

**file**: docs/templates/requirements/template-nodejs-cli-interface.md
**Status**: Active (Version 1.1.0 – dual mention inherited from LM-CLI-INTERFACE)
**Project**: {{APP_NAME}} – {{PLATFORM_NAME}} Platform Management CLI
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

# Template: CLI Interface Definition (Node.js)

## 1. Purpose

This template defines the required structure and ownership rules for the command surface of a Node.js platform management CLI. It enforces that:

- All user-facing command descriptions, usage text, global options, and help rendering logic live in a single source of truth (the Help module / singleton).
- Authentication state, session persistence, and token/endpoint handling are owned exclusively by a Session module.
- Global configuration, paths, flags, and runtime modes are owned by a Config module.
- Version, titles, diagnostics, and self-description content are owned by an About module.
- All console output (including error handling for --json / --quiet) is routed through a centralized Output module.

The template is designed to be specialized for any {{APP_NAME}}-style Node.js CLI that authenticates against a platform account service and then performs data operations via an official API client against the platform's data layer.

### 1.1 Empty argv (default Type N)

Unless this Node product also specializes **online install** (`template-online-install.md` / empty-argv **Type O**), no-args / missing subcommand **SHOULD** show help (or usage) — **Type N**. Do **not** import shell one-liner install-ensure as the default for platform ops CLIs. See `template-shell-cli-zero-arguments.md` and **`LM-CLI-INTERFACE`** §1.1.

This mold **inherits dual mention** from **`LM-CLI-INTERFACE`** §4.1. Specialize into `requirement-nodejs-cli-interface.md`. **MUST NOT** overwrite the generic **`LM-CLI-INTERFACE`** file.

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
| **Node.js CLI architecture** | `docs/terminologies/nodejs-cli-architecture.md` | `product-law` | CLI architecture |

**SSOT types used:** `meta-catalog` · `policy` · `product-law`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Core Rules / Requirements (Mandatory)

### 2.1 Single Source of Truth for CLI Surface (Help Module)

**All** of the following **MUST** be defined and rendered exclusively inside the centralized Help module:

- Full command list and descriptions (Auth, Workspaces, Cards, Inbox/Notifications, Events/Planner, Info, etc.)
- Subcommand details and accepted flags per command
- Global options documentation (`--json`, `--quiet`, `--debug`, `--endpoint`, `--token`, etc.)
- Usage examples and "Note:" sections
- Both human-readable and `--json` forms of help

No command descriptions, usage strings, or `showHelp()` logic may exist in `index.js` or command handlers.

**Law vs Help module:** The Help singleton is **runtime** usage-text SSOT. Product **requirements** **MUST** still **name** each routed verb (dual mention, §2.1a). Naming a verb in `requirement-nodejs-cli-interface.md` and a topic-owner REQ is **not** a Help-module leak. Duplicating help paragraphs into requirements is still forbidden.

### 2.1a Dual mention (inherited — sacred)

Every routed product verb (commander dest, bin action, or dispatch key) **MUST** be named in **at least two** Active specialized `requirement-*.md` files:

1. **`requirement-nodejs-cli-interface`** (dispatch / help honesty).  
2. The **topic-owner** requirement (auth/session, domain, privilege, lifecycle, request, actor, …).

**MUST NOT** leave a verb only on the Node CLI-interface file. The Help singleton **MUST NOT** be counted as the second requirement mention.

Adding a verb to Implementation Notes **MUST** name it on the topic-owner REQ in the same change. Superclass: **`LM-CLI-INTERFACE`** §4.1.

### 2.2 Command Categories (Recommended Structure)

A typical {{APP_NAME}} CLI should organize commands into clear categories. The following is a recommended starting structure (specialize as needed):

#### Auth Commands
| Command   | Description                                      | Required Flags / Notes |
|-----------|--------------------------------------------------|------------------------|
| login     | Authenticate and store reusable session token    | `--endpoint {{ENDPOINT}}`, `--email`, `--password` (or env vars) |
| logout    | Clear stored session                             | — |
| whoami    | Show current authenticated identity + endpoint   | — |

Global overrides for any command: `--token TOKEN`, `--endpoint URL`

#### Workspace Commands
| Command          | Description                              | Flags |
|------------------|------------------------------------------|-------|
| workspaces list  | List workspaces the user can access      | `--json`, `--quiet` |

#### Data Inspection Commands (require prior `login`)
| Command                  | Description                                      | Flags |
|--------------------------|--------------------------------------------------|-------|
| cards list               | List cards / unified objects in a workspace      | `--workspace {{WORKSPACE}}` (required), `--class`, `--title`, `--my`, `--limit`, `--json`, `--quiet` |
| inbox-message list       | List inbox notifications                         | `--workspace {{WORKSPACE}}`, `--user`, `--limit`, `--json`, `--quiet` |
| event list               | List calendar / planner events (aliases: planner, schedule) | `--workspace {{WORKSPACE}}`, `--title`, `--from`/`--to`, `--limit`, `--json`, `--quiet` |

**Important architectural rule**: Commands that return platform data (cards, inbox, events, drive, etc.) **must** use the official client (`{{API_CLIENT_PACKAGE}}`) against the data layer (WebSocket `connect` + `findAll` or `connectRest`), **not** direct calls to the auth endpoint. The auth endpoint is auth-only.

### 2.3 Global Flags (Mandatory Behavior)

| Flag              | Behavior                                                                 | stdout                          | stderr                  |
|-------------------|--------------------------------------------------------------------------|---------------------------------|-------------------------|
| (default)         | Human-friendly output with status messages                               | Status + data                   | Warnings + errors       |
| `--quiet` / `-q`  | Suppresses info/success status messages                                  | Data only                       | Warnings + errors       |
| `--json`          | Exactly **one** JSON value on stdout. Forces quiet mode.                 | Pure JSON                       | Errors only             |
| `--debug`         | Enables detailed internal diagnostics (also enabled by `DEBUG=1` env)    | —                               | Debug output            |

**Enforcement rules**:
- `--json` **always** implies `--quiet`.
- All error-related output (including structured JSON errors) **must** go to stderr.
- Debug output is **never** emitted when `--json` is active.
- Version / about / diagnostics content must come exclusively from the About module (never hard-coded).

### 2.4 Implementation Integrity Rules

- The main entry point (`index.js` or equivalent) must:
  1. Parse global flags early.
  2. Initialize Config singleton (sets modes, paths, `app_name`).
  3. Load Session (token/endpoint/user).
  4. Create Output instance that respects Config modes.
  5. Delegate all help rendering to the Help module.
- No module may read/write the session file directly or maintain its own `ENDPOINT` / `TOKEN` variables.
- All work involving the API client must begin with upstream git analysis per `skill-upstream-git-analysis.md`.
- No fake data or simulated results are allowed for any command that advertises use of an authenticated session.

### 2.5 Why This Requirement Exists (Direct CIAO Alignment)
- **CIAO Principle 2 – Intentional** (https://github.com/cloudgen/ciao): Clear ownership of the CLI surface prevents duplication, inconsistency, and difficult maintenance.
- **CIAO Principle 3 – Anti-fragile** (https://github.com/cloudgen/ciao): Centralized Help + Config + Session + Output modules survive repeated edits and future feature additions without regression.
- **CIAO Principle 4 / CIAO-Lite O · Principle 20 – Over-protect / Protect Against AI** (https://github.com/cloudgen/ciao): Strict single-source rules and Protection Zones defend the user experience contract.

## 3. Design Principles (CIAO / CIAO-Lite)

- **Caution** (CIAO Principle 1): Assume future developers and AI assistants will try to add commands or change behavior in multiple places. Centralization prevents this.
- **Intentional** (CIAO Principle 2): Every piece of user-facing text has one obvious home.
- **Anti-fragile** (CIAO Principle 3): The interface remains consistent and machine-readable (`--json`) even as new commands are added.
- **Over-protect** (CIAO Principle 4 / CIAO-Lite O · Principle 20): Verbose documentation of ownership rules and explicit "MUST NOT" statements in the Protection Rule guard against accidental violations.

## 4. Protection Rule (Sacred)

**Future AI assistants, Grok, or maintainers MUST NOT**:
- Place any command description, usage example, or help text outside the centralized Help module **in code**.  
- Skip dual mention (§2.1a) or treat the Help singleton as the second requirement mention.  
- Overwrite **`LM-CLI-INTERFACE`** (`template-cli-interface.md`) with this Node-specific mold.
- Hardcode the string `{{APP_NAME}}` (or any concrete app name) in command output or help text — always read from Config.
- Hardcode version numbers, titles, or diagnostics — always source from the About module.
- Read or write session/auth state directly — always go through the Session module.
- Emit raw `console.log` / `console.error` for user messages — always use the Output module.
- Add new commands that return platform data without using the official client against the data layer (after proper upstream study).
- Remove or weaken the rule that `--json` produces exactly one JSON value on stdout with all errors on stderr.
- Reference concrete workspaces, tokens, endpoints, or previous incidents inside the specialized requirement.

Violating any of the above is considered a **critical regression** against the defensive architecture.

---


## Design-time verification

| Gate | Artifact | Phase |
|------|----------|-------|
| Skill | `skill-nodejs-cli-coding` | Review |

**RTM:** `../tests/template-requirement-test-traceability.md` §4.

**Last Updated**: 2026-08-18  
**Owner**: CLI Architecture Layer  
**Version history:**  
- **1.1.0** (2026-08-18): Inherit **`LM-CLI-INTERFACE`** §4.1; Help module ≠ second REQ; do not overwrite the generic CLI mold.  
- **1.0.0**: Initial Node.js CLI surface mold.

**Alignment**: **`LM-CLI-INTERFACE`** §4.1 · `template-nodejs-api-client.md` · `template-output-requirements.md` · **CIAO Principles 1, 2, 3, 4, 20 (v2.10.2)** (https://github.com/cloudgen/ciao).

---

**How to specialize this template**:
1. Specialize into `docs/requirements/requirement-nodejs-cli-interface.md`. **MUST NOT** copy over `template-cli-interface.md`.  
2. Replace `{{PLACEHOLDER}}` in Implementation Notes.  
3. Keep Help module as **code** usage SSOT; still dual-mention every verb (§2.1a).  
4. Register `docs/requirements/index.md` (requirement row only — never this template path).  
5. Keep the Protection Rule and §2.1a intact.
