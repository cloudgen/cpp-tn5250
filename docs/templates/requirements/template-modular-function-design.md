---
name: modular-function-design
id: LM-MODULAR-FUNCTION-DESIGN
kind: law-mold
description: >
  Portable law mold. Cite as LM-MODULAR-FUNCTION-DESIGN (path secondary).
---

**file**: template-modular-function-design.md  
**Status**: Active (Version 1.4.0 – self-place `inst_*` owner map)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

## 1. Purpose

This template defines the modular function organization strategy for CIAO-Lite CLI tools.

It enables maintainability, reusability, and safe AI-assisted development while keeping the main script as a **single executable file** (important for `curl | sh` compatibility).

**Specialize into:** a project `requirement-*-modular-function-design.md` (e.g. `requirement-shell-modular-function-design.md`) with filled Implementation Notes (prefix table as shipped, domain prefix usage).

**Related templates:** `template-output-requirements.md`, `template-self-management.md`, `template-shell-script-coding.md`, `template-interactive-vs-noninteractive.md`, `template-idempotency.md`.

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
| **Shell function naming convention** | `docs/terminologies/shell-function-naming-convention.md` | `product-law` | Prefix families |
| **Ship unit** | `docs/terminologies/ship-unit.md` | `mention-only` | Single-file modular CLI |

**SSOT types used:** `mention-only` · `meta-catalog` · `policy` · `product-law`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Overall Architecture

The recommended architecture is **monolithic yet modular**:

- One single executable file for the main CLI tool (required for classic `curl | sh`)
- Functions are **logically grouped** using strict, consistent prefixes
- Every function follows a standardized, heavily documented structure with full CIAO comment blocks
- Durable rules live in specialized `requirement-*.md` files; code comments encode intent and Protection Zones

Optional multi-file layout under `src/` for authoring **MAY** exist only if a build or pack step still produces **one** installable artifact.

## 3. Official Function Naming Convention (Mandatory)

**Glossary SSOT:** [`shell-function-naming-convention`](../../terminologies/shell-function-naming-convention.md) — **obey that convention unless a specialized requirement specifies otherwise.**

**All functions MUST follow a categorized prefix system.** Bare names (`main`, `install`, `help`, `about`, `helper`) are forbidden as **function** names (CLI **commands** may still be `install` / `help` — dispatch maps them to prefixed functions).

### Recommended Function Prefix Table

| Prefix | Category | Purpose | Example Functions |
|--------|----------|---------|-------------------|
| `out_` | Output system (SSOT) | All user-facing and machine-readable output | `out_text`, wrappers, `out_json`, `out_json_error`, `out_die` — **examples:** `template-output-requirements.md` §3.1 |
| `inst_` | Installation & self-management | Install, uninstall, self-update, install detect, **CLI self-place** | `inst_perform_install`, `inst_self_install`, `inst_cli_dest_mode`, `inst_local_install`, `inst_is_installed` |
| `util_` | General utilities | Reusable helpers | `util_backup`, `util_sudo`, `util_chmod`, `util_resolve_storage` — **examples:** §3.2 (one owner mold each) |
| `app_` | **General app CLI surface** (product-neutral) | Entry, dispatch, about/help/version/where-is-me — **not** domain business logic | `app_main`, `app_about`, `app_help`, `app_version`, `app_where_is_me` |
| `{{APP_NAME}}_` | **Domain / product business logic** | Project-specific operations (path-safe prefix form) | `{{APP_NAME}}_start`, `{{APP_NAME}}_configure` |
| `ver_` | Version comparison | Semantic version handling | `ver_check`, `ver_gt` |
| `path_` | Shell path integration | Ensure `USER_BIN` on PATH via shell rc | `path_add_shell`, `path_add_bashrc`, `path_add_zshrc`, `path_add_fish` — **examples:** `template-path-and-shell-support.md` §3.1 |
| `prompt_` | Interactive prompts | TTY-safe confirmations and questions. **MUST NOT** `$()` (term **do-not-capture-read** / **`PP-A-22`**) | `prompt_yes_no`, `prompt_ask` |

**`app_*` vs `{{APP_NAME}}_*`:** `app_*` = general CLI surface (`app_main`, `app_help`, `app_about`, …). `{{APP_NAME}}_*` = domain business logic only. Do not mix. If `APP_NAME` contains hyphens, use a documented path-safe domain prefix (e.g. `{{domain}}_*` for hyphenated `{{APP_NAME}}`). Domain prefix may be unused until product ops exist.

### Strict Naming Rules

1. Every new function **must** use one of the defined prefixes (or extend the specialized requirement’s table in the same change).
2. Names should be descriptive but concise **snake_case** after the prefix.
3. Internal helper functions must still carry the correct prefix.
4. Update the prefix table in the specialized requirement when adding new categories.
5. Prefer `app_*` for about/help/main/dispatch/where-is-me presentation; reserve `{{APP_NAME}}_*` for product domain ops.
6. Prefer small, single-purpose functions over mega-functions that mix output, install, and domain logic.
7. Install destinations: [`global-installation-location`](../../terminologies/global-installation-location.md) (`GLOBAL_BIN`) and [`local-installation-location`](../../terminologies/local-installation-location.md) (`USER_BIN`) — not function-name concerns.

### 3.1 Ownership and SSOT by prefix (portable)

| Concern | Owning prefix / entry | Rule |
|---------|----------------------|------|
| User-facing output | `out_*` | No raw user messages outside `out_*` |
| Install + CLI lifecycle | `inst_*` | One install orchestrator; self-update reuses it |
| Version compare / remote check | `ver_*` | Pure compare helpers stay portable |
| PATH / shell profile ([shell-path-integration](../../terminologies/shell-path-integration.md)) | `path_*` | Duplicate-safe append; safe cleanup callers |
| CLI entry / dispatch | `app_*` | Single dispatcher; no second parallel main |
| Interactive confirm | `prompt_*` | Single source for yes/no; non-interactive safe behavior |
| Backup / storage resolve | `util_*` | Reusable; no domain hardcodes as universal law |
| Domain product ops | `{{APP_NAME}}_*` | Only when product ops exist |

### 3.2 `util_*` example ownership (sacred)

`util_*` helpers are **shared**. A name in the prefix table is **not** an example. Every portable `util_*` **MUST** have a **template-example-function** (fenced `sh`) on **one** owner law mold. Specialize-out **MUST** copy a fenced `sh` example onto the **topic-owner** `requirement-*.md`. Do not paste the same full body into a second mold.

| Function | Owner mold | Specialize-into | Class |
|----------|------------|-----------------|-------|
| `util_json_escape` | **`LM-OUTPUT-REQUIREMENTS`** §3.1 | `requirement-*-output-requirements` | B (JSON field escape) |
| `util_resolve_running_path` | **`LM-SHELL-LOCAL-SELF-MANAGEMENT`** §9.2 | `requirement-*-local-self-management` | B (running path) |
| `util_get_install_bin_path` | **`LM-SHELL-LOCAL-SELF-MANAGEMENT`** §9.3 | same | B (managed bin path) |
| `util_resolve_storage` | **`LM-SHELL-CLI-STORAGE`** examples | `requirement-*-cli-storage` | B (scratch root) |
| `util_get_current_shell` | **`LM-SHELL-CLI-STORAGE`** examples | same | B (about diagnostics) |
| `util_backup` | **`LM-BACKUP-STRATEGY`** examples | `requirement-*-backup-strategy` **or** the modular REQ when backup-strategy is not specialized | pre-change sibling `.bak` |
| `util_sha256_file` | **`LM-ONLINE-INSTALL`** §3.6 | only when online law is Active | B (digest) |
| `util_fetch_remote_version` | **`LM-ONLINE-INSTALL`** §3.6 | only when online law is Active | B (channel VERSION) |

**`inst_*` self-place (not `util_*`) — one owner:**

| Function | Owner mold | Specialize-into |
|----------|------------|-----------------|
| `inst_argv0_is_shell_interpreter` | **`LM-SHELL-CLI-SELF-INSTALL`** §3.1 | `requirement-shell-cli-self-install` |
| `inst_resolve_self_script` | **`LM-SHELL-CLI-SELF-INSTALL`** §3.2 | same |
| `inst_cli_dest_mode` | **`LM-SHELL-CLI-SELF-INSTALL`** §3.3 | same |
| `inst_self_install_copy_from_script` | **`LM-SHELL-CLI-SELF-INSTALL`** §3.4 | same |
| `inst_self_install` | **`LM-SHELL-CLI-SELF-INSTALL`** §3.5 | same |
| `inst_maybe_install` | **`LM-INTERACTIVE-VS-NONINTERACTIVE`** | `requirement-shell-interactive-vs-noninteractive` |
| `inst_perform_install*` | **`LM-ONLINE-INSTALL`** §3.6 | online install REQ |
| `inst_self_update` / `inst_self_uninstall*` | **`LM-SELF-MANAGEMENT`** §7 | self-management REQ |

**Not shipped on non-online-installable products (alias local-only):** `util_sha256_file`, `util_fetch_remote_version`, `inst_self_install` download branch. Do not specialize those examples into product law “for completeness.”

`util_backup` is the CIAO **pre-change sibling `.bak`** helper (`<name>.YYYYMMDD-N.bak`). It is **not** a folder-archive `backup`/`restore` verb.

## 4. Function Documentation Standards (Mandatory)

Every function **must** include a complete defensive header following this structure:

```sh
# =============================================================================
# function_name() - Short one-line purpose
# =============================================================================
#
# GENERAL PURPOSE:
# Clear explanation of what this function does and why it exists.
#
# CIAO PRINCIPLES APPLIED:
# - Caution (Principle 1): ...
# - Intentional (Principle 2): ...
# - Anti-fragile (Principle 3): ...
# - Over-protect (Principle 4 / CIAO-Lite O · Principle 20): ...
#
# !!! DO NOT MODIFY OR SIMPLIFY THIS FUNCTION !!!
# Designed to be reusable in other CIAO-Lite projects.
#
# Lessons Learned (CIAO Reflection):
# [Date]: [Short note when fixing regressions or improving defensive comments]
#
# Last reviewed: YYYY-MM-DD
# =============================================================================
```

### 4.1 Optional ALIGNMENT / See lines (product source only)

When a function header names related documents, **product source** must cite only **live** specialized requirements:

```text
# ALIGNMENT (live requirements only):
# - requirement-<topic>.md   # must exist under docs/requirements/
```

| Do | Do not |
|----|--------|
| Cite `docs/requirements/requirement-*.md` that exist and are in `index.md` | Cite `template-*.md` or `docs/templates/…` |
| Prefer the specialized requirement that owns the behavior | Cite `skill-*.md` as product law / ALIGNMENT substitute |
| Omit ALIGNMENT if no live requirement applies | Invent `requirement-*.md` paths to look complete |

Agents **may** load templates and skills while implementing; those paths belong in agent harnesses and docs work, **not** in product source comment authority. See `template-defensive-practices.md` §2.7.

## 5. Why This Requirement Exists (Direct CIAO Alignment)

- **CIAO Principle 4 / CIAO-Lite O · Principle 20 – Over-protect / Protect Against AI** (https://github.com/cloudgen/ciao): Standardized function structure with Protection Zones and full documentation defends against accidental or AI-induced regressions.
- **CIAO Principle 2 – Intentional** (https://github.com/cloudgen/ciao): Clear naming conventions and consistent structure make the codebase easy to navigate and understand.
- **CIAO Principle 3 – Anti-fragile** (https://github.com/cloudgen/ciao): Small, focused, well-documented functions can be individually reviewed, tested, and reused safely.

## 6. Design Principles (CIAO / CIAO-Lite)

- **Caution (CIAO Principle 1)**: Each function is small, focused, and heavily guarded with Protection Zones.
- **Intentional (CIAO Principle 2)**: Clear naming and grouping makes the codebase easy to navigate and maintain.
- **Anti-fragile (CIAO Principle 3)**: Functions can be individually reviewed, tested, and reused across projects.
- **Over-protect (CIAO Principle 4 / CIAO-Lite O · Principle 20)**: Protection Zones and "DO NOT MODIFY" comments prevent destructive simplification.

## Under command line for normal user only

When the ship unit detects a **command line for normal user only** (Termux, Git Bash, or the same class — term [`command-line-for-normal-user-only.md`](../../terminologies/command-line-for-normal-user-only.md)):

| MUST | MUST NOT |
|------|----------|
| Keep **normal user privilege** (Type 0) only | Implement or enable **admin privilege** (Type 1) or **dedicated system user privilege** (Type 2) |
| Document Type 1 **unused** and Type 2 **unused** | In-tool `sudo`; wrap `apt` / `dnf` / `yum`; write `/etc` dests; `useradd` / dedicated LPU; Type 2 `sudo -u` switch |
| Termux: named `pkg` as this login remains Type 0 (**`LM-SHELL-TERMUX-ISH`**) | Recommend `sudo curl \| sh` as the install path |
| Git Bash: same privilege ceiling | Invoke Termux `pkg` because Git Bash was detected |

Detect (typical): Termux — `PREFIX` contains `com.termux`; `TERMUX_VERSION` set; `/data/data/com.termux/files/usr` exists. Git Bash — `MSYSTEM` is `MINGW*` / `MSYS*` / `UCRT*` / `CLANG*`; `uname -s` is `MINGW*` / `MSYS*`. Windows cmd — `OS` is `Windows_NT` or `ComSpec`/`COMSPEC` names `cmd.exe` (after excluding Git Bash, Cygwin, WSL).

**This mold:** detect helpers stay domain-prefixed; **MUST NOT** add a `util_sudo` family on that class.

## 7. Protection Rule (Sacred)

**Future AI assistants, Grok, or maintainers MUST NOT**:

- Merge functions or remove the prefix-based grouping system.
- Delete or weaken Protection Zones and `!!! DO NOT MODIFY !!!` comments.
- Remove or shorten the "GENERAL PURPOSE" and "CIAO PRINCIPLES APPLIED" sections.
- Refactor the monolithic single-file structure into multiple files (this breaks `curl | sh` compatibility).
- Violate the official function prefix table.
- Remove or weaken safe variable defaults inside functions.
- Put `template-*.md` or `skill-*.md` paths into product source function headers as behavioral authority (§4.1).
- Claim “fully synchronized with” a `requirement-*.md` that does not exist on disk.
- Leave a portable `util_*` as a table name only — owner mold **MUST** hold the fenced example (§3.2).
- Paste the same full `util_*` body into a second mold.

**Modularity is achieved through clear function boundaries, consistent naming, and full documentation — not by splitting into multiple files.**

---


## Design-time verification

| Gate | Artifact | Planned |
|------|----------|---------|
| Prefix / modular review | `../checklists/code-review.md` | Review pass |
| **TP-CLI-01** syntax | `../tests/template-shell-cli-test-plan.md` | suite green |
| Behavior covered by CLI/LC suites | `../tests/template-shell-cli-suite-test-plan.md` | suite green |

**RTM:** `../tests/template-requirement-test-traceability.md`


**Last Updated**: 2026-09-17  
**Owner**: Architecture & Maintainability Layer (Generalized Template)  
**Version history:**  
- **1.4.0** (2026-09-17): §3.2 `inst_*` self-place owner map (`inst_self_install` family → **`LM-SHELL-CLI-SELF-INSTALL`**); domain example vars unfrozen.  
- **1.3.0** (2026-09-05): Named section Under command line for normal user only.  
- **1.2.0** (2026-08-18): §3.2 `util_*` example ownership — one owner mold, specialize-out to topic-owner REQ.  
- **1.1.0** (2026-07-14): `prompt_` prefix; ownership SSOT table; specialize-into pointer; domain prefix may be unused.  
- **1.0.0**: Initial prefix + header pattern.  

**Alignment**: Shell coding **SSOT** `template-shell-script-coding.md` (router: `template-coding-style.md`); peer templates in §1; **CIAO Principles 2, 3, 4, 20 (v2.10.2)** (https://github.com/cloudgen/ciao).

---

**How to use this template**:
1. Keep under `docs/templates/requirements/`; specialize into `requirement-*-modular-function-design.md`.
2. Customize the prefix table with your project-specific domain prefix (e.g. `{{APP_NAME}}_`) or document “unused until domain ops exist”.
3. Enforce the full function header structure in all new code and during reviews.
4. Keep the Protection Rule and single-file philosophy intact.
5. After specialization, register the new `requirement-*.md` in `docs/requirements/index.md` (requirement row only — do not list template paths in the registry).


---

## Example domain prefix (Type 0 shell CLI `{{domain}}_*`)

When `APP_NAME` is hyphenated (e.g. `{{APP_NAME}}`), domain functions use a **path-safe** prefix (`{{domain}}_*`), not illegal shell identifiers.

| Function | Role |
|----------|------|
| `{{domain}}_resolve_base_dir` | Volatile/persistent base dir |
| `{{domain}}_get_file` | Path for one named item |
| `{{domain}}_sanitize_name` | Path-safe name gate |
| `{{domain}}_domain_fail` | Domain error via `out_*` |
| `{{domain}}_start` / `{{domain}}_stop` / `{{domain}}_status` | Core ops |
| `{{domain}}_kill_or_reset` | kill vs reset |
| `{{domain}}_list` | Enumerate mode |

**Domain vars (specialize):** item name, persist flag, file path, `STORAGE_MODE`, `VOLATILE_DIR`, `PERSISTENT_DIR`, `USERNAME` — see [shell-cli-config-variables](../../terminologies/shell-cli-config-variables.md). **MUST NOT** freeze a product brand as the only domain example.

**Pattern:** domain handlers only; install stays in `inst_*`; CLI surface in `app_*`; messages only via `out_*`.

