---
name: interactive-vs-noninteractive
id: LM-INTERACTIVE-VS-NONINTERACTIVE
kind: law-mold
description: >
  Portable law mold. Cite as LM-INTERACTIVE-VS-NONINTERACTIVE (path secondary).
---

**file**: template-interactive-vs-noninteractive.md  
**Status**: Active (Version 2.4.0 – `inst_maybe_install` Type 0 example)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

## 1. Purpose

This template defines how a CIAO-Lite CLI behaves in **interactive** (human user with TTY) versus **non-interactive** (CI/CD, scripts, pipes, Ansible, Docker build, `--json` / often `--quiet`, etc.) environments.

`curl | sh` is one **common** non-interactive path for **Type O** online-install CLIs; it is **not** the definition of all non-interactive mode. Empty-argv install vs help is owned by `template-shell-cli-zero-arguments.md` (Type O vs Type N), not by this mode template alone.

**Specialize into:** a project `requirement-*-interactive-vs-noninteractive.md` (e.g. `requirement-shell-interactive-vs-noninteractive.md`) with filled Implementation Notes and a command-level interactive matrix.

**Related templates (do not duplicate ownership):**

| Topic | Template |
|-------|----------|
| CLI flags / dispatcher | `template-cli-interface.md` |
| Empty argv Type O / Type N | `template-shell-cli-zero-arguments.md` |
| Output SSOT | `template-output-requirements.md` |
| Self-management confirms | `template-self-management.md` |
| Idempotency / force reinstall | `template-idempotency.md` |

---

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
| **Interactive vs noninteractive** | `docs/terminologies/interactive-vs-noninteractive.md` | `runtime-mode` | Primary mode vocabulary |
| **No retest TTY** | `docs/terminologies/no-retest-tty.md` | `runtime-reliability` | Measure `[ -t` once in main process / outside functions; helpers consume `TTY` |
| **Shell TTY / privilege traps** | `docs/terminologies/shell-tty-privilege-traps.md` | `runtime-reliability` | Failure class when no-retest-tty is violated (**T1-SUBSHELL**) |
| **Shell CLI bootstrap** | `docs/terminologies/shell-cli-bootstrap.md` | `product-law` | Pipe non-interactive path |

**SSOT types used:** `meta-catalog` · `policy` · `product-law` · `runtime-mode` · `runtime-reliability`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Definitions (portable)

| Mode | Definition |
|------|------------|
| **Interactive** | A human is driving the tool with a usable terminal (**TTY**). Confirmations, colors, and onboarding prompts are allowed when not overridden by machine flags. |
| **Non-interactive** | No human is available to answer prompts: pipes, CI/CD, `curl \| sh`, config management, Docker build, scripts, or machine flags such as `--json` (and often `--quiet`). The tool **must never hang waiting for input** and must apply **documented safe automatic defaults**. |

---

## 3. Mode SSOT (choose one specialization shape)

A product **MUST** pick **one** mode SSOT shape and document it in Implementation Notes. Do **not** invent a second parallel mode system in individual commands.

### 3.1 Shape A — POSIX shell globals (recommended for single-file shell CLIs)

Mode SSOT = global flag / TTY block at script top + values set by the dispatcher after parsing:

| Signal | Variable / check | Meaning |
|--------|------------------|---------|
| TTY | `TTY=1` when stdin and stdout are terminals — measured **once** in the **main process, outside functions** (term [`no-retest-tty`](../../terminologies/no-retest-tty.md)) | Interactive UX possible |
| Quiet | `QUIET=1` (`--quiet` / `-q`) | Suppress non-essential human chatter |
| JSON | `JSON=1` (`--json`; implies quiet) | Machine output; no human hang; no human banners |
| Debug | `DEBUG=1` (`--debug`) | Extra stderr diagnostics; suppressed under JSON |
| Force | `FORCE=1` / `FORCE_REINSTALL=1` (`--force`) | Skip confirms / force reinstall / allow policy-gated downgrade |
| Explicit interactive override | `INTERACTIVE=1` (optional env) | Rare override when low-level TTY checks are flaky (value prompts only) |

**Rules:**

1. Prompt, color, and hang-sensitive decisions **MUST** respect these globals and/or shared `prompt_*` helpers — not ad-hoc `read` scattered in domain logic.  
2. After global flags are parsed in the dispatcher (e.g. `app_main`), subsequent code **MUST** see the updated values.  
3. **No-retest-tty (mandatory):** live `[ -t 0 ]` / `[ -t 1 ]` for interactive capability **MUST** run **outside functions** (script top) or in a **direct mode setter** that assigns `TTY`. `prompt_*`, `out_*` color, and `app_about` **MUST consume `TTY`**. They **MUST NOT** re-test live `[ -t` as the sole policy gate (especially under `$(…)` — **T1-SUBSHELL**).  
4. Allowed exception: a **data-source** probe of *this* stdin (`[ -t 0 ]` to choose `--file` xor pipe) is not interactive-capability SSOT.  
5. Command business logic **SHOULD** call `prompt_*` instead of re-implementing prompt guards.  
6. **MUST NOT** capture `prompt_ask` / `prompt_yes_no` / any `read` helper with `$()` or backticks. Call in the current shell. Value prompts assign **`PROMPT_ASK_VALUE`**. Law body: **`LM-SHELL-SCRIPT-CODING` §8.1.5**. Terms **do-not-capture-read** · **prompt-ask-value**. Pain **`PP-A-22`**. stderr+$() is **not** a license.

### 3.2 Shape B — Config / singleton (recommended for Node/Python class-based CLIs)

Mode SSOT = centralized config object (e.g. `{{CONFIG_SINGLETON}}` at `{{CONFIG_PATH}}`) exposing flags such as `isTTY`, `isInteractive`, `isQuiet`, `isJson`, and a `mode` enum.

**Rules:**

1. All prompt / color / hang decisions **MUST** read from that config after flags are applied.  
2. Thin entrypoints must not re-implement mode logic.  
3. Direct `process.std*.isTTY` (or language equivalent) checks outside the config **MUST NOT** become a second SSOT.

### 3.3 Flow (both shapes)

```text
flags + TTY / environment
           │
           ▼
     Mode SSOT (Shape A or B)
           │
     ┌─────┴─────┐
     ▼           ▼
interactive   non-interactive
(human UX)    (no hang, safe defaults)
```

---

## 4. Behavioral differences (portable)

### 4.1 Interactive mode (TTY, not quiet/json)

| Allowed / expected | Notes |
|--------------------|--------|
| Colored / prefixed human output | Via output SSOT when TTY and not quiet/json |
| Helpful messages and about diagnostics | Full human surface |
| Confirmation prompts for destructive actions | Via prompt SSOT unless `--force` |
| Onboarding / install prompt when not installed | When product supports it |
| Value prompts with defaults | Via prompt SSOT |

### 4.2 Non-interactive mode (automation)

| Required | Forbidden |
|----------|-----------|
| **Never wait** for user input | Bare `read` / stdin prompts without mode guards |
| **Safe automatic defaults** documented per command | Assuming someone will type “yes” |
| Suppress or skip prompts under quiet/json | Hanging on confirm in CI |
| Support `--json` purity (output template) | Mix human text into JSON stdout |
| Non-zero exit on critical failure | Silent hang that looks like a stuck job |
| Work under pipes / Docker / CI | Requiring a full TTY for core ensure ops that claim automation support |

### 4.3 Flag interactions

| Flag / state | Impact |
|--------------|--------|
| `--json` | Force quiet-style human suppression; no prompts; structured stdout; errors on stderr |
| `--quiet` | No prompts; reduced chatter; errors (and warnings per output SSOT) still surface |
| `--force` | Skip uninstall confirm; allow reinstall/downgrade policy paths |
| `--debug` | stderr diagnostics; never block; suppressed under JSON |
| Non-TTY stdin/stdout | Treat as non-interactive for prompts |

### 4.4 Empty argv (owned by type — do not override)

| Product type | Empty argv | Owner |
|--------------|------------|--------|
| **Type N — Non-online-install** | **Help / usage** | `template-shell-cli-zero-arguments.md` |
| **Type O — Online-install** | **Install-ensure** (not help) | same + `template-online-install.md` §3.0a |

This template **MUST NOT** force Type O install-ensure on every CLI.

---

## 5. Prompt SSOT (portable)

| Helper pattern | Role |
|----------------|------|
| Yes/no confirm | **Only** path for destructive/optional confirms (e.g. shell `prompt_yes_no`) |
| Value prompt | **Only** simple value prompt path with default (e.g. shell `prompt_ask`) |
| Prompt fragment without newline | Human-only fragment via output SSOT (e.g. `out_msg_n`) |

**Rules:**

1. Never implement user-visible confirms with raw print + read outside the prompt SSOT.  
2. Under JSON or quiet, prompts **MUST NOT** block: return default / no / cancel per documented policy.  
3. Without TTY (unless explicit interactive override where designed), prompts **MUST NOT** block.  
4. Destructive non-interactive actions that would have required confirm **MUST** either:  
   - require `--force` (fail closed without it — e.g. JSON error code `confirm_required`), or  
   - document an explicit safe auto-proceed policy (e.g. zero-arg install under pipe for Type O).

**Intentional dual policy (common for Type O shell tools):** pipe **install** may auto-proceed; **destructive uninstall** does **not** without `--force`.

---

## 6. Command matrix sketch (specialize fully)

| Command / path | Interactive (TTY, not quiet/json) | Non-interactive / quiet / json |
|----------------|-----------------------------------|--------------------------------|
| Empty argv — Type N | Help | Help / short usage (not install) |
| Empty argv — Type O, not installed | Optional confirm then install | Auto install (no hang) |
| Empty argv — Type O, already installed | Success no-op (not help) | Same |
| `install` | Human messages | No prompt; honor force for reinstall |
| `self-uninstall` | Confirm unless `--force` | Without force: **fail closed** (`confirm_required`); never fake “cancelled by user” success JSON |
| `self-update` / `version-check` | Human status | No prompts; fail loud if channel missing |
| `about` / `version` / `help` | Human surface | Quiet suppress / JSON structured only |

---

## 7. Why This Pattern Exists (Direct CIAO Alignment)

- **CIAO Principle 1 – Caution** (https://github.com/cloudgen/ciao): Never hang or surprise users in automated environments; destructive ops fail closed without force.  
- **CIAO Principle 2 – Intentional** (https://github.com/cloudgen/ciao): Clear, predictable behavior in both modes.  
- **CIAO Principle 3 – Anti-fragile** (https://github.com/cloudgen/ciao): Survive Docker, CI/CD, pipes, and minimal environments.  
- **CIAO Principle 16 – Interactive vs non-interactive awareness** (https://github.com/cloudgen/ciao): First-class mode policy.  
- **CIAO Principle 4 / CIAO-Lite O · Principle 20 – Over-protect / Protect Against AI** (https://github.com/cloudgen/ciao): Protected prompt helpers; no raw-read regressions.

---

## 8. Design Principles (CIAO / CIAO-Lite)

- **Caution:** Prefer cancel over destructive auto-action when intent is ambiguous; prefer auto-install for classic Type O one-liner when not installed.  
- **Intentional:** One mode SSOT + one prompt SSOT.  
- **Anti-fragile:** Non-TTY and quiet/json paths always terminate without stdin.  
- **Over-protect:** Do not “simplify” prompt guards.  
- **Pair with output SSOT:** Prompts use authorized emitters; JSON never shows prompts.

---

## Under command line for normal user only

When the ship unit detects a **command line for normal user only** (Termux, Git Bash, or the same class — term [`command-line-for-normal-user-only.md`](../../terminologies/command-line-for-normal-user-only.md)):

| MUST | MUST NOT |
|------|----------|
| Keep **normal user privilege** (Type 0) only | Implement or enable **admin privilege** (Type 1) or **dedicated system user privilege** (Type 2) |
| Document Type 1 **unused** and Type 2 **unused** | In-tool `sudo`; wrap `apt` / `dnf` / `yum`; write `/etc` dests; `useradd` / dedicated LPU; Type 2 `sudo -u` switch |
| Termux: named `pkg` as this login remains Type 0 (**`LM-SHELL-TERMUX-ISH`**) | Recommend `sudo curl \| sh` as the install path |
| Git Bash: same privilege ceiling | Invoke Termux `pkg` because Git Bash was detected |

Detect (typical): Termux — `PREFIX` contains `com.termux`; `TERMUX_VERSION` set; `/data/data/com.termux/files/usr` exists. Git Bash — `MSYSTEM` is `MINGW*` / `MSYS*` / `UCRT*` / `CLANG*`; `uname -s` is `MINGW*` / `MSYS*`. Windows cmd — `OS` is `Windows_NT` or `ComSpec`/`COMSPEC` names `cmd.exe` (after excluding Git Bash, Cygwin, WSL).

**This mold:** install recommend / `inst_maybe_install` **MUST NOT** suggest `sudo curl | sh` or a Type 1 password-sudo ladder on that class.

---

## 9. Protection Rule (Sacred)

**Future AI assistants, Grok, or maintainers MUST NOT**:

1. Add confirmation prompts outside the prompt SSOT without updating the specialized requirement.  
2. Allow prompts to run under `--json` or `--quiet`.  
3. Hang on prompts when stdin/stdout are not TTYs (except documented interactive override for value prompts).  
4. Break the invariant that `--json` forces quiet-style non-interactive human suppression.  
5. Auto-uninstall in non-interactive mode without `--force`, or emit fake success JSON “cancelled by user” when confirm was required.  
6. Force empty argv → install-ensure on every CLI via this template — that contract is **mandatory only** under Type O / online install.  
7. Scatter ad-hoc TTY/mode logic that contradicts the chosen mode SSOT.  
8. Bypass the output SSOT for prompt text (raw product messages).  
9. Paste this template path into product source as behavioral authority — specialize and cite the live requirement instead.  
10. Re-test live `[ -t 0 ]` / `[ -t 1 ]` **inside** `prompt_*` / `about` / string-returning helpers as the interactive-policy gate (term **no-retest-tty**). Measure outside functions; helpers consume `TTY`.

**Supporting non-interactive environments cleanly is mandatory for CIAO compliance.**

---

## 10. How to use this template

1. Choose **Shape A (shell globals)** or **Shape B (Config singleton)** and document it.  
2. Specialize into `requirement-*-interactive-vs-noninteractive.md` with a full command matrix and prompt contracts.  
3. Align empty-argv rows with Type O / Type N classification (`template-shell-cli-zero-arguments.md`).  
4. Register the requirement in `docs/requirements/index.md` (requirement row only).  
5. Product source cites the specialized **requirement** only.

---


## Design-time verification

| TP family / ID | Proof mold | Planned suite |
|----------------|------------|---------------|
| **TP-CLI-07,11** quiet + uninstall refuse | `../tests/template-shell-cli-test-plan.md` | `tests/test_cli.sh` |
| **TP-LC-07** lifecycle uninstall refuse | `../tests/template-install-lifecycle-test-plan.md` | lifecycle |
| **TP-CURL-02,03** non-TTY pipe | `../tests/template-online-curl-install-test-plan.md` | curl suite |

**RTM:** `../tests/template-requirement-test-traceability.md`


**Last Updated**: 2026-09-17  
**Owner**: CLI Modes / Automation Layer (Generalized Template)  
**Version history:**  
- **2.4.0** (2026-09-17): `inst_maybe_install` Type 0 example — quiet/json **MUST** `inst_self_install` (not skip).  
- **2.3.0** (2026-09-05): Named section Under command line for normal user only.  
- **2.2.1** (2026-09-02): Sample warnings **do-not-capture-read** / **PP-A-22**; terms **prompt-ask-value** · **command-substitution-subshell**.  
- **2.2.0** (2026-09-02): `prompt_ask` assigns `PROMPT_ASK_VALUE`; **MUST NOT** `$()` `read` helpers (**LM-SHELL-SCRIPT-CODING** §8.1.5).  
- **2.1.0** (2026-08-14): **no-retest-tty** — measure `[ -t` outside functions; `prompt_*` examples consume `TTY`; live retest inside helpers forbidden.  
- **2.0.0** (2026-07-14): Shell-first portable Shape A; optional Shape B Config singleton; Type O/N empty-argv ownership; uninstall `confirm_required`; removed residual single-product Node-only wording as sole SSOT.  
- **1.0.0**: Initial generalized form (Config-singleton skewed).  

**Alignment**: `docs/terminologies/interactive-vs-noninteractive.md`; term [`no-retest-tty.md`](../../terminologies/no-retest-tty.md); term `shell-tty-privilege-traps`; peer templates in §1; **CIAO Principles 1, 2, 3, 16, 18** (https://github.com/cloudgen/ciao); CIAO-Lite (https://github.com/cloudgen/ciao-lite).


---

## Example shell functions (Type 0 shell CLI `prompt_*`)

**Prefix:** `prompt_` ([shell-function-naming-convention](../../terminologies/shell-function-naming-convention.md)).  
**Mode vars:** `JSON`, `QUIET`, `TTY`, optional `INTERACTIVE` ([shell-cli-config-variables](../../terminologies/shell-cli-config-variables.md)).  
**Prompt text:** `out_msg_n` / `out_*` only — never raw product `printf` for the question.

### `prompt_yes_no` — example

```sh
# WARNING — do-not-capture-read (**PP-A-22** / T1-PROMPT-CAPTURE)
# MUST NOT _y=$(prompt_yes_no …) / $() / backticks. This body contains `read`.
# Call: if prompt_yes_no "…"; then …  stderr+$() is NOT a license.
# Terms: do-not-capture-read · command-substitution-subshell
prompt_yes_no() {
    : "${JSON:=0}"
    : "${QUIET:=0}"
    local message="$1"
    # Never prompt in quiet/json
    if [ "${JSON}" -eq 1 ] || [ "${QUIET}" -eq 1 ]; then
        return 1
    fi
    if [ "${TTY:-0}" -ne 1 ]; then
        return 1
    fi
    out_msg_n "${message} (y/N)? "
    local answer=""
    read -r answer || true
    case "$answer" in
        [Yy]*|[Yy][Ee][Ss]*) return 0 ;;
        *) return 1 ;;
    esac
}
```

### `prompt_ask` — example

```sh
# WARNING — do-not-capture-read (**PP-A-22** / T1-PROMPT-CAPTURE)
# MUST NOT _x=$(prompt_ask …) / $() / backticks. This body contains `read`.
# Call in the current shell. Value is PROMPT_ASK_VALUE (term prompt-ask-value).
# stderr+$() is NOT a license. Terms: do-not-capture-read · command-substitution-subshell
prompt_ask() {
    : "${JSON:=0}"
    : "${QUIET:=0}"
    : "${PROMPT_ASK_VALUE:=}"
    local message="${1-}" default="${2-}" current="${3-}"
    PROMPT_ASK_VALUE="${default}"
    if [ "${JSON}" -eq 1 ] || [ "${QUIET}" -eq 1 ]; then
        return 0
    fi
    if [ "${TTY:-0}" -ne 1 ]; then
        if [ "${INTERACTIVE:-0}" -ne 1 ]; then
            return 0
        fi
    fi
    [ -n "${current}" ] && out_info "Current: ${current}"
    [ -n "${default}" ] && out_info "Default: ${default}"
    out_msg_n "${message}: "
    local answer=""
    read -r answer || true
    if [ -n "${answer}" ]; then
        PROMPT_ASK_VALUE="${answer}"
    fi
    return 0
}

# caller (current shell)
prompt_ask "Remote (user@host)" ""
_spec="${PROMPT_ASK_VALUE}"
```

**Contract:** quiet/json/non-TTY → no hang; yes/no returns status; ask sets `PROMPT_ASK_VALUE`. **MUST NOT** `_x=$(prompt_ask …)` (**do-not-capture-read**; **`PP-A-22`**; **LM-SHELL-SCRIPT-CODING** §8.1.5).

### `inst_maybe_install` — TTY first-shot confirm (Type O)

**Kind:** [template-example-function](../../terminologies/template-example-function.md). Place **how** stays **`LM-SHELL-CLI-SELF-INSTALL`**. Empty-argv **when** stays **`LM-SHELL-CLI-ZERO-ARGUMENTS`**. **MUST NOT** `$()` this helper (`read` via `prompt_yes_no`).

```sh
# Quiet/JSON: no prompt — MUST call inst_self_install (not return 0 skip).
# TTY: prompt_yes_no then inst_self_install. Non-TTY human: auto-place.
inst_maybe_install() {
    : "${QUIET:=0}" : "${JSON:=0}" : "${TTY:=0}"
    : "${FORCE_REINSTALL:=0}" : "${APP_NAME:=app}" : "${VERSION:=0.0.0}"
    if [ "$(id -u 2>/dev/null || echo 1)" -eq 0 ]; then
        IS_ROOT=1
    else
        IS_ROOT=0
    fi
    if inst_is_installed && [ "${FORCE_REINSTALL}" -eq 0 ]; then
        return 0
    fi
    if [ "${JSON}" -eq 1 ] || [ "${QUIET}" -eq 1 ]; then
        inst_self_install
        return $?
    fi
    out_plain "Note: '${APP_NAME}' is not installed yet."
    if [ "${TTY}" -eq 1 ]; then
        if prompt_yes_no "Install ${APP_NAME} ${VERSION} now?"; then
            inst_self_install
            return $?
        fi
        out_plain "Installation skipped by user."
        return 0
    fi
    out_plain "Non-interactive mode detected → installing automatically..."
    inst_self_install
    return $?
}
```

