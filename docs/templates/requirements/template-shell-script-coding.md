---
name: shell-script-coding
id: LM-SHELL-SCRIPT-CODING
kind: law-mold
description: >
  Portable law mold. Cite as LM-SHELL-SCRIPT-CODING (path secondary).
---

**file**: template-shell-script-coding.md
**Status**: Active (Version 3.16.0 – named section Under command line for normal user only)
**Project**: Any CIAO-Lite Project using POSIX /bin/sh (reusable template)
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

# Template: Shell Script Coding Style (POSIX /bin/sh)

## 0. SSOT notice (mandatory)

| Role | Path |
|------|------|
| **This file — authoritative shell coding body** | `docs/templates/requirements/template-shell-script-coding.md` |
| **Alias only (no forked body)** | `docs/templates/requirements/template-sh-coding-style.md` |
| **Cross-language coding-style router** | `docs/templates/requirements/template-coding-style.md` |

Agents **MUST** edit shell coding law here (or in a specialized `requirement-*.md`), not in the alias or router.

## 1. Purpose and Intention

This template defines the recommended coding style for POSIX-compliant `/bin/sh` scripts in CIAO-Lite projects.

**Specialize-in (software-development):** this mold is **portable**. Product law is a specialized `requirement-shell-script-coding.md`. **Without that REQ, agents bring these learned lessons raw.** That REQ is the specialize-in home (term `coding-style-requirement`). Class **MUST** have it.

**Core Intention**:
Produce scripts that are:
- Extremely portable across minimal and legacy environments
- Safe to re-execute (idempotent-friendly)
- Explicitly controlled without hidden automatic exits
- Easy to read, trace, and maintain over long periods
- Suitable for harsh environments (minimal containers, old systems, `curl | sh` installations, Git Bash on Windows)

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
| **Shell function naming convention** | `docs/terminologies/shell-function-naming-convention.md` | `product-law` | Prefixes |
| **Interactive vs noninteractive** | `docs/terminologies/interactive-vs-noninteractive.md` | `runtime-mode` | Mode SSOT; TTY vs automation |
| **No retest TTY** | `docs/terminologies/no-retest-tty.md` | `runtime-reliability` | Positive rule: measure `[ -t` outside functions; helpers consume `TTY` |
| **Shell TTY / privilege traps** | `docs/terminologies/shell-tty-privilege-traps.md` | `runtime-reliability` | Failure class (**T1-SUBSHELL** when no-retest-tty is violated) |
| **Three-layer privilege** | `docs/terminologies/three-layer-privilege.md` | `product-law` | Type 0/1/2; scoped elevation |
| **Template example function** | `docs/terminologies/template-example-function.md` | `meta-catalog` | Example bodies in molds |
| **Template example variable** | `docs/terminologies/template-example-variable.md` | `meta-catalog` | Example vars in molds |
| **Ship unit** | `docs/terminologies/ship-unit.md` | `mention-only` | Coding target |
| **Coding-style requirement** | `docs/terminologies/coding-style-requirement.md` | `product-law` | Software-dev MUST specialize this mold; without the REQ, lessons arrive raw |
| **Check before sudo** | `docs/terminologies/check-before-sudo.md` | `runtime-reliability` | Before `sudo`; chmod is the example |
| **Sudo-wrapping function** | `docs/terminologies/sudo-wrapping-function.md` | `product-law` | Only in-tool `sudo` call site |

**SSOT types used:** `mention-only` · `meta-catalog` · `policy` · `product-law` · `runtime-mode` · `runtime-reliability`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. CIAO-Lite Justification

### Reasons (CIAO-Lite Justification)
- **Maximum cross-platform compatibility**: Works reliably on Alpine ash, dash, BusyBox, Git Bash, macOS sh, minimal containers, and legacy Unix systems.
- **No unnecessary Bashisms**: Avoids features that are not available in strict POSIX `/bin/sh`.
- **Reliable behavior in `curl | sh` one-liner installations**: Scripts must behave predictably even when piped directly from the network.
- **Defensive goal**: Designed to run in the harshest possible environments with minimal assumptions.
- **Long-term maintainability**: Heavy structure and documentation reduce the risk of accidental regressions when the code is modified in the future.

## 3. Function Naming Convention (Mandatory)

**Glossary SSOT:** [`docs/terminologies/shell-function-naming-convention.md`](../../terminologies/shell-function-naming-convention.md).  
**Config variables:** [`docs/terminologies/shell-cli-config-variables.md`](../../terminologies/shell-cli-config-variables.md) (full Type 0 shell CLI inventory + default order).  
**Obey the general shell naming convention unless a specialized project requirement specifies otherwise.**

All functions **MUST** follow a categorized prefix system. Install path config names (`GLOBAL_BIN`, `USER_BIN`) are defined under  
[`global-installation-location`](../../terminologies/global-installation-location.md) and  
[`local-installation-location`](../../terminologies/local-installation-location.md).

### Recommended Function Prefix Table

| Prefix | Category | Purpose | Examples |
|--------|----------|---------|----------|
| `out_` | Output system (SSOT) | All user-facing and machine output | `out_text`, wrappers, `out_json`, `out_json_error` — **full examples:** `template-output-requirements.md` §3.1 |
| `inst_` | Installation & self-management | One-time setup, local/online install, uninstall, self-update | `inst_perform_install`, `inst_local_install`, `inst_self_update` |
| `util_` | General utilities | Reusable helpers | `util_backup`, `util_resolve_storage`, `util_parse_args` |
| `app_` | **General app CLI surface** (product-neutral) | CLI entry, dispatch, about/help/version/where-is-me — **not** domain business logic | `app_main`, `app_about`, `app_help`, `app_version`, `app_where_is_me` |
| `{{APP_NAME}}_` | **Domain / product business logic** | Project-specific operations (start, configure, deploy, domain workflows) | `{{APP_NAME}}_start`, `{{APP_NAME}}_configure`, `{{APP_NAME}}_status` |
| `ver_` | Version comparison | Semantic version handling | `ver_check`, `ver_gt` |
| `path_` | Shell path integration | PATH ensure via `.bashrc`/`.zshrc`/fish (`USER_BIN`) | `path_add_shell`, `path_add_bashrc`, `path_add_zshrc`, `path_add_fish` — **full examples:** `template-path-and-shell-support.md` §3.1 |
| `prompt_` | Interactive prompts | Confirmations that **consume `TTY`** (term **no-retest-tty**). **MUST NOT** `$()` (term **do-not-capture-read** / **`PP-A-22`**) | `prompt_yes_no`, `prompt_ask` |

**`app_*` vs `{{APP_NAME}}_*` (mandatory distinction)**:
- Use **`app_*`** for cross-cutting CLI application surface that every shell CLI needs (main entry, help/about/version presentation hooks, command dispatch, where-is-me). Prefer this name so scripts stay readable and portable without baking a product string into every general function.
- Use **`{{APP_NAME}}_*`** only for **domain business logic** specific to the product. When specializing, replace `{{APP_NAME}}` with a **path-safe** function prefix (if `APP_NAME=timer-template`, domain functions often stay `timer_*` when documented).
- Do **not** put domain ops under `app_*`, and do **not** put generic about/help/main under `{{APP_NAME}}_*` unless a specialized requirement explicitly requires product-prefixed aliases.

**Strict Rules**:
- Every new function **must** use one of the defined prefixes.
- Names must be descriptive but concise **snake_case** after the prefix.
- Never use bare names like `install`, `main`, `helper`, `do_something`, `about`, or `help` as **functions** without a prefix (use `app_main`, `app_help`, `inst_*`, etc.). User-facing **commands** may still be short words.

## 4. Function Structure Template (Mandatory)

Every function **MUST** follow this exact defensive structure:

```sh
# =============================================================================
# function_name() - Short one-line purpose
# =============================================================================
#
# GENERAL PURPOSE:
# Clear one-paragraph explanation of what this function does and why it exists.
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

function_name() {
    # --- Safe Variable Defaults ---
    : "${VAR1:=default}"
    : "${VAR2:=default}"
    # ... other variables used in the function

    # Main logic here...
}
```

**Mandatory Requirements**:
- The full header comment block **must** be present.
- The `!!! DO NOT MODIFY OR SIMPLIFY THIS FUNCTION !!!` warning **must** be included.
- Safe variable defaults using `: "${VAR:=default}"` **must** appear at the top of the function body.
- The "CIAO PRINCIPLES APPLIED" section should be filled meaningfully.

### 4.1 Product-source documentation authority

Optional `ALIGNMENT` / `See` lines in **product source** (the CLI script itself) **MUST** cite only live `docs/requirements/requirement-*.md` paths that exist on disk.

| Allowed in product source comments | Forbidden in product source comments |
|------------------------------------|--------------------------------------|
| Live `requirement-*.md` (and `index.md` registration) | `template-*.md` / `docs/templates/…` as authority |
| Incident IDs for lessons (optional) | `skill-*.md` as ALIGNMENT / product law |
| | Invented or stale `requirement-*.md` names |

Agents load templates/skills when coding; those citations stay in agent harnesses and docs — not in the shipped script’s authority lines. See `template-defensive-practices.md` §2.7 and `template-modular-function-design.md` §4.1.

## 5. Single Source of Truth (SSOT) Principles

To maintain clarity, reduce duplication, and improve maintainability, the following SSOT rules **MUST** be followed:

### 5.1 Values and Constants (SSOT)
- All important constants, default values, and configuration values **MUST** have a single source of truth.
- Define them once (preferably near the top of the script or in a dedicated initialization section) and reference them everywhere else.
- Avoid hardcoding the same value in multiple places.
- Session `$DISPLAY` is **not** a frozen constant: inherit `${DISPLAY:-}`; **MUST NOT** `: "${DISPLAY:=localhost:11.0}"` (or `:0` / `localhost:10.0`) in the ship unit.

**Example**:
```sh
# Single Source of Truth — specialize {{DEFAULT_PORT}} and {{STATE_DIR_NAME}} per project
readonly DEFAULT_PORT={{DEFAULT_PORT}}
readonly STATE_DIR_NAME="{{STATE_DIR_NAME}}"

# Later usage
STATE_DIR="${PROJECT_DIR}/${STATE_DIR_NAME}"
```

### 5.2 Input Handling (SSOT)
- All input sources (command-line arguments, environment variables, and interactive input) **MUST** be processed and normalized in one central location.
- After initial parsing, the rest of the script should work with internal variables only.
- Avoid repeatedly reading or parsing the same input in multiple functions.

**Guideline**: Create a dedicated input normalization section or function (e.g., `util_parse_args` or `inst_initialize`) that sets all internal variables.

### 5.3 Output Handling (SSOT)
- All user-facing and machine-readable output **MUST** go through the centralized output system (`out_text()`, `out_info()`, `out_success()`, `out_json()`, etc.).
- Never use raw `echo` or `printf` for user-facing messages outside of the approved output functions.
- This ensures consistent formatting, quiet mode support, and JSON output capability.

## 6. General Coding Rules (CIAO / CIAO-Lite)

- Use **safe variable defaults** in **every** function: `: "${VAR:=default}"`
- All user-facing output **must** go through the centralized output system (`out_text()`, `out_info()`, `out_success()`, `out_json()`, etc.).
- Prefer strict **POSIX-compatible syntax**. Avoid Bashisms such as arrays, `[[ ]]`, process substitution (`<(...)`), and here-strings unless absolutely necessary.
- Always quote variables: `"${VAR}"`
- Heavy commenting and Protection Zones are **intentional and required**.
- Preserve all `!!! DO NOT MODIFY OR SIMPLIFY !!!` blocks.
- Pay special attention to integration points (Docker, external services, privilege boundaries, and cross-platform path handling).
- Design every function and script with the assumption that it may be re-run at any time (idempotency).

## 7. Compatibility Recommendations

### 7.1 Use `.` Instead of `source`
Prefer the dot command for maximum compatibility with minimal shells.

### 7.2 Avoid `which` Unless Necessary
Use `command -v` instead of `which`.

### 7.3 Path Handling on Windows (Git Bash)
Be extremely careful with path formats when the script may run under Git Bash on Windows.

## 8. Error Handling

Prefer explicit `if` checks over `command || { ... }` constructs.

When an error occurs, provide context and perform reasonable cleanup before returning or exiting.

## 8.1 TTY, command substitution, and Type 1 escalation (Mandatory)

**Problem class:** Using `[ -t 0 ]` / `[ -t 1 ]` **inside command substitution** `$(…)` (or backticks) to decide whether the human can answer a **sudo password** prompt. Inside `$(…)`, stdin is **not** a TTY even when the operator launched the script from a real terminal. That produces **false fail-closed** elevation (“no usable sudo”) while a password would work.

**Positive rule (glossary):** [`no-retest-tty.md`](../../terminologies/no-retest-tty.md) — measure interactive capability **once** in the **main process, outside functions**; helpers **consume** `TTY`.  
**Failure class (glossary):** `docs/terminologies/shell-tty-privilege-traps.md` (T1-SUBSHELL, T1-NODEONLY, …).  
**Blank gate:** `docs/templates/checklists/checklist-shell-tty-privilege-traps.md` (**CL-SHELL-TTY-PRIVILEGE-TRAPS**).  
**Proof mold:** `docs/templates/tests/template-shell-tty-privilege-test-plan.md` (**TP-ELEV-*** including **TP-ELEV-07**).

### 8.1.1 Rules

1. **Mode SSOT / no-retest-tty** — interactive capability lives in the main process: entry-time `TTY` / Config flags / optional re-probe of **`/dev/tty`**. Live `[ -t 0 ]` / `[ -t 1 ]` **MUST** run **outside functions** (script top) or in a **direct mode setter** that assigns `TTY`. Helpers (`prompt_*`, `out_*` color, `about`, elev detect) **MUST consume `TTY`**. **MUST NOT** bury live `[ -t 0 ]` in string-returning helpers that are only called via `$(…)`.  
1b. **`/dev/tty` openability** — **MUST NOT** treat device **existence** (or r/w bits alone) as interactive. Some agent/CI environments expose a non-openable `/dev/tty` (“No such device or address”); require a successful open (e.g. `( : </dev/tty ) 2>/dev/null`) before password-sudo mode.  
2. **MUST NOT** use `[ -t 0 ]` / `[ -t 1 ]` **inside** `$(helper)` or `` `helper` `` as the **sole** gate for interactive Type 1 sudo.  
3. Prefer a **direct** function that sets a mode variable (e.g. `{{PREFIX}}_set_escalation_mode` → `{{ESC_MODE_VAR}}`) over `mode=$(detect)` when `detect` needs live TTY policy.  
4. **Type 1 package / host package install** ladder (when product claims elevated package ensure):  
   **Default:** **root** → **password sudo** (controlling TTY / `/dev/tty`) → **fail closed**.  
   **`sudo -n` is not a default rung.** Insert it **only** when specialized product law **explicitly** names a NOPASSWD Table A grant / hook / JSON ticket. Copying `-n` from this mold without that sentence is **T1-N-POLLUTE**.  
5. **MUST NOT** print “open an interactive terminal” / “no usable sudo” unless the designed password-sudo path is actually unavailable.  
6. Password sudo **SHOULD** bind the prompt to the controlling terminal (e.g. `sudo … </dev/tty`) when stdin may be redirected.  
7. **JSON / noninteractive** paths **MUST NOT** hang on password prompts; use fail-closed machine code (e.g. `elevation_required`).  
8. **MUST NOT** “fix” broken Type 1 detection by unprivileged package install or by reintroducing forbidden source-clone/build when law is package-only.  
9. Align with term `interactive-vs-noninteractive` and `three-layer-privilege` (Type 1 = scoped elevated host prep / packages).  
10. **Table A vs Table C (mix model).** **Table A** = Cmnds **in sudoers** (F6 / `print-sudoers`). **Table C** = OS tools the ship unit runs as **`sudo <tool>`** (password `sudo`; **not** `sudo -n`). Table C **MUST NOT** appear in sudoers. Type 1 `setup` **MAY** call `sudo useradd`. **MUST NOT** write “ship unit MUST NOT invoke `sudo`” as default law — that rule was never portable.  
11. **MUST NOT** add **sudoers** Cmnds (Table A) by script edit alone — update elev tables + security review + admin fragment first (**E-PRIV-04**). Table C `sudo useradd` is **not** a new sudoers line.  
12. `print-sudoers` output **MUST** match Table A when the product emits a sudoers fragment. **MUST NOT** emit `useradd` / `userdel` there.  
13. **`sudo -n` is not suggested** — default ship unit, help, and examples **MUST NOT** treat `-n` as escalation. Write `-n` **only** when specialized law names a NOPASSWD grant / hook (**T1-N-POLLUTE** if copied as boilerplate).  
14. **`sudo -n` is not escalation** — it is *NOPASSWD ticket or fail*. **MUST NOT** write first-time `setup` / install as `sudo -n {{APP}}` (**T1-BOOTSTRAP-N**). Mix model: already-root, **outer** password `sudo`, **or in-tool** password `sudo`.  
15. **Bootstrap vs post-grant** — a verb that **creates** Table A / the LPU **MUST NOT** require `SUDO_USER` to be that LPU. Day-to-day approve verbs **MAY** require the LPU after the grant exists.  
16. **Multi-user install** — local `USER_BIN` is any login; global `GLOBAL_BIN` is any host admin with write/root. **MUST NOT** treat one LPU as the only installer.  
17. **When `-n` may be specified** — login hook / rc / CI **after** Table A NOPASSWD exists (must not hang `.bashrc` / `scp`). JSON/noninteractive: fail closed; do **not** invent `-n` to “avoid a hang” if no grant exists.

### 8.1.2 Portable pattern (illustration — not product law)

```sh
# Illustration only. OMIT the sudo -n branch unless product law specifies NOPASSWD.
# Default portable path: already-root or password sudo (or outer sudo). Do not paste -n.
# Entry (main process) — existence of /dev/tty is NOT enough; open must succeed
TTY=0
[ -t 0 ] && [ -t 1 ] && TTY=1
if [ "${TTY}" -eq 0 ] && [ -c /dev/tty ] 2>/dev/null && ( : </dev/tty ) 2>/dev/null; then
    TTY=1
fi

# Set mode WITHOUT relying on [ -t 0 ] inside $(...)
{{PREFIX}}_set_escalation_mode() {
    {{ESC_MODE_VAR}}="fail"
    if [ "$(id -u 2>/dev/null || echo 1)" -eq 0 ]; then
        {{ESC_MODE_VAR}}="root"
        return 0
    fi
    command -v sudo >/dev/null 2>&1 || return 1
    if sudo -n true 2>/dev/null; then
        {{ESC_MODE_VAR}}="sudo-n"
        return 0
    fi
    if [ "${JSON:-0}" -eq 0 ] && [ "${TTY:-0}" -eq 1 ]; then
        {{ESC_MODE_VAR}}="sudo-tty"
        return 0
    fi
    return 1
}

{{PREFIX}}_run_as_root() {
    {{PREFIX}}_set_escalation_mode || true
    case "${{{ESC_MODE_VAR}}:-fail}" in
        root) "$@" ;;
        sudo-n) sudo -n "$@" ;;
        sudo-tty)
            if [ -c /dev/tty ] 2>/dev/null && ( : </dev/tty ) 2>/dev/null; then
                sudo "$@" </dev/tty
            elif [ -t 0 ]; then
                sudo "$@"
            else
                return 1
            fi
            ;;
        *) return 1 ;;
    esac
}
```

### 8.1.3 Review gate

Before claiming Type 1 package install done: complete **CL-SHELL-TTY-PRIVILEGE-TRAPS** (or equivalent specialized checklist run). **Block** false fail-closed **and** **T1-BOOTSTRAP-N**.

### 8.1.4 Avoid `sudo -n` unless specified (default)

**Default for every product:** do **not** write `sudo -n`. That flag is optional, specified law — not a portable habit.

| Write | Meaning | When |
|-------|---------|------|
| `sudo {{APP}} setup` / `sudo {{APP}} install` | Outer elev; **password OK**; any host admin | **Default** first-time / multi-user |
| In-tool `sudo useradd` / `sudo userdel` | Mix model; Table C; **not** a sudoers Cmnd | Type 1 setup / teardown |
| (omit `-n` entirely) | No ticket check | Default |
| `sudo -n {{GLOBAL_BIN}}/{{APP}} …` | Existing **NOPASSWD** ticket or fail | **Only if** specialized law names that grant + verb |
| In-tool `sudo -n` copied as default elev | Knowledge pollution | **Not suggested** (**T1-N-POLLUTE**) |

The ship unit **MAY** invoke password `sudo`. Help **MUST** show `sudo {{APP}} setup`, not `sudo -n {{APP}} setup`, unless a live requirement **explicitly** specifies `-n`.

### 8.1.5 Do not capture `read` helpers (Mandatory)

**Last updated:** 2026-09-02

**Problem:** `_var=$(prompt_ask …)` (or `$()` / backticks around **any** function whose body contains `read`) runs that helper in a subshell. Prompt text on stdout is swallowed; `read` can block with no visible prompt (**T1-PROMPT-CAPTURE** / **`PP-A-22`**). Sending the prompt to stderr does **not** license `$()`. Positive rule: term **do-not-capture-read**. Mechanism: **command-substitution-subshell**. Return: **prompt-ask-value**.

**MUST NOT:**

- `_x=$(prompt_ask …)` / `_x=$(prompt_yes_no …)` / backticks of those names  
- `$()` / backticks around **any** function that contains `read`

**MUST:**

- Status: `if prompt_yes_no "…"; then` (current shell)  
- Value: `prompt_ask "msg" "default"` then `${PROMPT_ASK_VALUE}` (current shell; `prompt_ask` assigns that global)  
- `$()` remains allowed for **pure data** helpers that never `read` (`id -un`, path resolvers, class-B `printf` of computed strings)  
- Every `prompt_*` / `read`-helper **sample** in this mold and peers **MUST** carry a **WARNING** citing **do-not-capture-read** / **`PP-A-22`**

```sh
# WARNING — do-not-capture-read (**PP-A-22** / T1-PROMPT-CAPTURE)
# MUST NOT _x=$(prompt_ask …). Call in the current shell. Value is PROMPT_ASK_VALUE.
prompt_ask "Remote (user@host)" ""
_spec="${PROMPT_ASK_VALUE}"
```

**Review / proof:** **CL-SHELL-TTY-PRIVILEGE-TRAPS** §1; **CL-CLI-DEFAULT-INTERACTION** when a main menu exists; **TP-ELEV-10** / **TP-CLI-16** static grep for `$(prompt_` (not only `prompt_ask` / `prompt_yes_no`). Terms **do-not-capture-read** · **prompt-ask-value** · **command-substitution-subshell** · **no-retest-tty** · **shell-tty-privilege-traps** (**T1-PROMPT-CAPTURE**). Pain **`PP-A-22`**.

## 8.2 User-owned shell rc (`.profile` / `.bashrc`) (Mandatory)

When Type 1 `setup` / heal **creates or rewrites** a file in another login’s home (`{{HOME}}/.profile`, `{{HOME}}/.bashrc`, or a hook strip via `mktemp`+`mv`):

| # | Rule |
|---|------|
| **R1** | **Owner is the corresponding user** (`{{USER}}:{{GROUP}}`), not the elevated invoker. |
| **R2** | Mode is readable by that user (typical `0644`). Do **not** leave `0600` `root:root`. |
| **R3** | After `mktemp`+`mv`, **`chown` again** — `mv` keeps the temp’s owner. |
| **R4** | When `getent passwd {{USER}}` succeeds, **`chown` failure is fatal**. **MUST NOT** `chown … \|\| true`. |
| **R5** | Do **not** overwrite an existing `.profile` body. Heal owner/mode only. |
| **R6** | Do **not** write another login’s rc. |

Glossary: [`shell-profile.md`](../../terminologies/shell-profile.md) · [`shell-bashrc.md`](../../terminologies/shell-bashrc.md). Procedure: **`SK-CREATE-SHELL-PROFILE`** · **`SK-CREATE-SHELL-BASHRC`**.

```sh
chmod 0644 "${_rc}" || return 1
if getent passwd "${_user}" >/dev/null 2>&1; then
    chown "${_user}:${_group}" "${_rc}" || return 1
fi
```

## 8.3 Check before sudo (Mandatory) — example: `sudo chmod`

Terms: [`check-before-sudo.md`](../../terminologies/check-before-sudo.md) · [`sudo-wrapping-function.md`](../../terminologies/sudo-wrapping-function.md).

**Before any `sudo <cmd>`**, run a **non-sudo** probe. If this login **already can** do the job, **MUST NOT** `sudo` — no further elevated step.

**Worked example (`sudo chmod`):** probe Unix ownership **without sudo**. If this login **owns** the path, **MUST NOT** `sudo chmod`.

| # | Rule |
|---|------|
| **C0** | **Class:** every in-tool `sudo <cmd>`. chmod is the **example**, not the only case. |
| **C1** | Probe with a **non-sudo** command. **chmod example:** POSIX `[ -O path ]` (true when the effective uid owns the path). `stat` / `ls -ld` **without** `sudo` are also allowed. |
| **C2** | If the probe **matches** (this login already can): **MUST NOT** `sudo`. **chmod example:** **MUST NOT** `sudo chmod`; **MUST NOT** chmod further as a sudo step. If the mode already equals the target, skip chmod. If the mode still differs, unprivileged `chmod` is enough. |
| **C3** | `sudo <cmd>` **MAY** run only when the probe **misses**. **chmod example:** `sudo chmod` only when this login does **not** own the path. Still **MUST NOT** default to `sudo -n` (**T1-N-POLLUTE**). |
| **C4** | **MUST NOT** probe with `sudo` (`sudo ls`, `sudo stat`, `sudo -n stat`). |
| **C5** | Already-root (`id -u` = 0) already can — **MUST** run the tool without `sudo`. **chmod example:** `chmod`, not `sudo chmod`. |
| **C6** | In-tool `sudo` **MUST** go through a [sudo-wrapping function](../../terminologies/sudo-wrapping-function.md) (typical `util_sudo`). The chmod example **MUST** go through a chmod helper (`util_chmod`) that applies **C1–C2**. **MUST NOT** scatter raw `sudo` / `sudo chmod`. |

**Why:** `sudo` on a job this login can already do is extra elev. Principle **10**. chmod example also Principle **22**.

```sh
# Illustration only — specialize names in product law.
# Sudo-wrapping function: only in-tool sudo call site.
util_sudo() {
    if [ "$(id -u 2>/dev/null || echo 1)" -eq 0 ]; then
        "$@"
        return $?
    fi
    command -v sudo >/dev/null 2>&1 || return 1
    sudo "$@"
}

# chmod example: check before sudo via [ -O path ].
util_chmod() {
    _mode="${1:-}"
    _path="${2:-}"
    [ -n "${_mode}" ] && [ -n "${_path}" ] || return 1
    [ -e "${_path}" ] || return 1
    if [ -O "${_path}" ]; then
        chmod "${_mode}" "${_path}"
        return $?
    fi
    util_sudo chmod "${_mode}" "${_path}"
}
```

Peer: **`LM-FILE-MODES-UMASK`** (path `chmod` / umask). This section owns **check before sudo** C0–C6 and the chmod **example**. Dedicated in-tool sudo product law (allow table, compose sibling dest, `sudo -n` row): specialize **`LM-SHELL-SUDO-COMMAND`** → `requirement-shell-sudo-command`. Coding-style REQ **points**.

## Under command line for normal user only

When the ship unit detects a **command line for normal user only** (Termux, Git Bash, or the same class — term [`command-line-for-normal-user-only.md`](../../terminologies/command-line-for-normal-user-only.md)):

| MUST | MUST NOT |
|------|----------|
| Keep **normal user privilege** (Type 0) only | Implement or enable **admin privilege** (Type 1) or **dedicated system user privilege** (Type 2) |
| Document Type 1 **unused** and Type 2 **unused** | In-tool `sudo`; wrap `apt` / `dnf` / `yum`; write `/etc` dests; `useradd` / dedicated LPU; Type 2 `sudo -u` switch |
| Termux: named `pkg` as this login remains Type 0 (**`LM-SHELL-TERMUX-ISH`**) | Recommend `sudo curl \| sh` as the install path |
| Git Bash: same privilege ceiling | Invoke Termux `pkg` because Git Bash was detected |

Detect (typical): Termux — `PREFIX` contains `com.termux`; `TERMUX_VERSION` set; `/data/data/com.termux/files/usr` exists. Git Bash — `MSYSTEM` is `MINGW*` / `MSYS*` / `UCRT*` / `CLANG*`; `uname -s` is `MINGW*` / `MSYS*`. Windows cmd — `OS` is `Windows_NT` or `ComSpec`/`COMSPEC` names `cmd.exe` (after excluding Git Bash, Cygwin, WSL).

**This mold:** §8.1 Type 1 password-sudo ladder **MUST NOT** be implemented on that class; `util_sudo` example is N/A there.

## 9. Protection Rules (Sacred)

**Future AI assistants, Grok, or maintainers MUST NOT**:

- Change the shebang from `#!/bin/sh`
- Remove or weaken safe variable default blocks (`: "${VAR:=default}"`)
- Replace `out_text()` / `out_json()` with raw `echo` / `printf`
- Introduce heavy Bashisms that break POSIX compatibility
- Delete or weaken Protection Zones and `!!! DO NOT MODIFY !!!` comments
- “Clean up” the script by removing defensive verbosity or repetition
- Violate the official function prefix system
- Use `set -e`, `set -u`, or `set -eu`
- Use `source` instead of `.` for sourcing files
- Use `which` without checking for POSIX alternatives (`command -v`)
- Create functions without following the mandatory naming prefix and structure template
- Remove or bypass explicit error handling in favor of automatic exit behavior
- Ignore cross-platform path safety (especially on Windows + Git Bash)
- Duplicate important values, input parsing logic, or output logic in multiple places (violate SSOT)
- Cite `template-*.md` or `skill-*.md` as behavioral authority in product source comments (§4.1)
- Invent or leave non-existent `requirement-*.md` paths in product source headers
- Use `[ -t 0 ]` / `[ -t 1 ]` **inside functions** (especially under command substitution) as the sole gate for interactive Type 1 sudo or prompt policy (§8.1 / term **no-retest-tty**)
- Capture `prompt_ask` / `prompt_yes_no` / any `read` helper with `$()` or backticks (**T1-PROMPT-CAPTURE** / **`PP-A-22`**, §8.1.5). stderr+$() is **not** a license.
- Emit false fail-closed elevation errors without attempting designed password-sudo when a controlling terminal exists and mode is not JSON (§8.1)
- Install system packages as an unprivileged user when product law requires Type 1 package ensure (§8.1)
- Put Table C tools (`useradd`, `userdel`, `visudo`) **into sudoers** / `print-sudoers` (§8.1.1)
- Write product law “ship unit **MUST NOT** invoke `sudo`” unless the **user** specified that ban
- Treat every in-tool `sudo` as a Table A / F6 Cmnd
- Write first-time `setup` / global install as `sudo -n`, or require the LPU that setup creates (**T1-BOOTSTRAP-N**, §8.1.1)
- Copy `sudo -n` into a product that did not **specify** a NOPASSWD grant / hook / ticket (**T1-N-POLLUTE**, §8.1.4)
- Create or rewrite `{{HOME}}/.profile` / `{{HOME}}/.bashrc` as the elevated invoker and leave that owner (`root:root`) — **§8.2**
- Swallow `chown` of a user rc with `\|\| true` when the corresponding account exists — **§8.2**
- Run `sudo <cmd>` without a **non-sudo** probe, or `sudo` when the probe already shows this login can do the job — **§8.3** (example: `sudo chmod` when `[ -O path ]`)
- Probe with `sudo ls` / `sudo stat` to decide whether to sudo — **§8.3**
- Scatter in-tool `sudo` outside a [sudo-wrapping function](../../terminologies/sudo-wrapping-function.md), or write `sudo chmod` outside the chmod helper — **§8.3 C6**
- Strip the **Under command line for normal user only** section, or implement the §8.1 Type 1 ladder on Termux / Git Bash

---


## Design-time verification

| TP family / ID | Proof mold | Planned suite |
|----------------|------------|---------------|
| **TP-U-05** safe external source | `../tests/template-set-u-test-plan.md` | `tests/test_cli.sh` |
| **TP-U-01–04** nounset | same | CLI + curl |
| **TP-CLI / privilege** TTY escalation mode | product suite or unit probe | `TTY=1` ⇒ password-sudo mode when `sudo` exists without `-n` |
| **TP-ELEV-10** no `$()` of `read` helpers | `../tests/template-shell-tty-privilege-test-plan.md` | static grep; product CLI suite when no elev suite |

**Checklist gate:** **`CL-SHELL-TTY-PRIVILEGE-TRAPS`** when Type 1 elevation / TTY prompts in scope. Dedicated wrap / allow table / **`CL-LEAST-PRIVILEGE`**: specialize **`LM-SHELL-SUDO-COMMAND`**.

**RTM:** `../tests/template-requirement-test-traceability.md`

**Last Updated**: 2026-09-02 (v3.15.1 – §8.1.5 cites **do-not-capture-read** / **PP-A-22**; grep `$(prompt_`; **TP-CLI-16**)
**Owner**: Shell Scripting Layer
**Alignment**: Fully synchronized with CIAO Principles 1, 2, 3, 16, 18, and 22; `template-defensive-practices.md` §2.7; `template-file-modes-umask.md` (U10 points here §8.3); `template-modular-function-design.md` §4.1; `template-interactive-vs-noninteractive.md`; **`LM-SHELL-SUDO-COMMAND`** (wrap / allow table); terms `three-layer-privilege` · `check-before-sudo` · `sudo-wrapping-function`. Designed for maximum portability, safety, and long-term maintainability in POSIX `/bin/sh`.

---

**How to use this template**:
1. Every function must follow the mandatory naming prefix and structure.
2. Apply SSOT principles for values, input handling, and output.
3. Use safe variable defaults and explicit error handling.
4. Preserve all protection blocks and heavy documentation.
5. Design for re-runnability and harsh environments.
6. When Type 1 package elevation or password sudo is claimed: apply §8.1 and run **CL-SHELL-TTY-PRIVILEGE-TRAPS**. When the ship unit invokes sudo: specialize **`LM-SHELL-SUDO-COMMAND`** and run **`CL-LEAST-PRIVILEGE`**.