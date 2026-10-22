---
name: output-requirements
id: LM-OUTPUT-REQUIREMENTS
kind: law-mold
description: >
  Portable law mold. Cite as LM-OUTPUT-REQUIREMENTS (path secondary).
---

**file**: template-output-requirements.md  
**Status**: Active (Version 2.7.2 – cite ui-view-for-app-log; C++ `logger_*` bodies stay in §3.2)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered / Over-protect)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

## 1. Purpose

This template defines **CIAO Principle 5 — Single Source of Output** (cloudgen/ciao **v2.10.2**, strengthened in v2.10.1):

All **product** program messaging (info, success, warnings, errors, debug, and machine JSON) **must** go through **one centralized output module** — the **SSOT of output**.

**Specialize into:** a project `requirement-*-output-requirements.md` (e.g. `requirement-shell-output-requirements.md`) with filled Implementation Notes.

**Related:** `template-ciao-principles.md` · `template-cli-interface.md` · `template-interactive-vs-noninteractive.md` · `template-modular-function-design.md` · Principle **14** (channel design stdout vs stderr — ownership remains one Output SSOT).

### 1.1 SSOT family (do not confuse)

| Concept | Role |
|---------|------|
| **SSOT of output** | One Output module owns **all product** emission and mode rules (quiet / JSON / TTY) |
| **SSOT of stdout** | Product primary payload / pure JSON on **fd 1** — **via** that module only |
| **SSOT of stderr** | Product diagnostics (error / warn / debug) on **fd 2** — **via the same** module |
| **SSOT of pipeline** | Internal **data** only: return-via-stdout for `$(…)`, pipes into tools, file redirects — **not** user banners, JSON results, or error UX |

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
| **SSOT of output** | `docs/terminologies/single-source-of-truth-of-output.md` | `channel-io` | Umbrella output SSOT |
| **SSOT of stdout** | `docs/terminologies/single-source-of-truth-of-stdout.md` | `channel-io` | stdout rules |
| **SSOT of stderr** | `docs/terminologies/single-source-of-truth-of-stderr.md` | `channel-io` | stderr rules |
| **SSOT of pipeline** | `docs/terminologies/single-source-of-truth-of-pipeline.md` | `channel-io` | Internal data vs UI |
| **App-name-version-display** | `docs/terminologies/app-name-version-display.md` | `identity-runtime` | Human identity banners: `{{APP_NAME}}({{VERSION}})`; live values = Config |
| **Default CLI main menu style** | `docs/terminologies/default-cli-main-menu-style.md` | `identity-runtime` | Numbered TTY menu look; `out_menu_choice` prints gray italic `{{explain}}` |
| **Template example function** | `docs/terminologies/template-example-function.md` | `mention-only` | §3.1 shell bodies and §3.2 C++ bodies; not product law |
| **Project log content type** | `docs/terminologies/project-log-content-type.md` | `channel-io` | Kinds of message the dated log stores. Cite only. Do not paste the catalog. **gnome-debug** is one kind. |
| **UI view for an app log** | `docs/terminologies/ui-view-for-app-log.md` | `channel-io` | HTML table for one log file in the main web view. Cite only. Do not paste a product palette. The non-UI show command prints the file bytes unchanged. |

**SSOT types used:** `channel-io` · `identity-runtime` · `mention-only` · `meta-catalog` · `policy`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Core Rule (Sacred)

**All user-facing and machine-facing product output MUST go through the centralized output system.**

A message that matches a [project log content type](../../terminologies/project-log-content-type.md) is stored in the dated log. The catalog, including **gnome-debug**, stays in that term. This mold cites it. The specialized requirement copies it.

A [ui-view-for-app-log](../../terminologies/ui-view-for-app-log.md) is how a main web view shows one of those files. The sheet is an HTML table with a distinct header, two body backgrounds, and a third hover background. Displayed cells omit `[` `]` `<` `>` `(` `)` `{` `}`. The non-UI command that shows the same file prints the file bytes unchanged. This mold cites the term. The specialized requirement copies the palette and the command name.

- Do **not** use raw `echo` / `printf` / `console.log` / `console.error` for **product messages** outside the Output module.
- All product messages route through central emitters (e.g. `out_text()` wrappers + `out_json()` / language equivalents).

### 2.1 Allowed pipeline uses (SSOT of pipeline — not product messaging)

| Exception | When allowed | Why it is not a product-output bypass |
|-----------|--------------|----------------------------------------|
| **Inside the output SSOT** | Only central emitters may write product lines to fd 1/2 | Those functions *are* the authorized writers |
| **Function return-via-stdout** | `printf '%s' "$value"` **only** for `$(…)` capture of **pure data** helpers that never `read` | Pipeline data; callers must capture. **MUST NOT** apply to `prompt_ask` / `prompt_yes_no` / any `read` helper (**do-not-capture-read** / **`PP-A-22`**; **LM-SHELL-SCRIPT-CODING** §8.1.5) |
| **File I/O (redirected writes)** | `printf … >> "$config_file"` | File mutation, not product channels |
| **Tool protocol / computation pipes** | e.g. `printf '…' \| sha256sum -c` | Data fed to another tool |
| **Command-substitution fallbacks** | e.g. prefer `${var:-default}`; if using `cmd \|\| printf '%s' "unknown"` assign into a variable | Logic defaults only |

**Prefer `printf` over `echo`** for pipeline returns and cmd-sub fallbacks (portable formatting). Prefer reliable empty defaults (`${var:-default}`) over `grep|cut || echo` without `pipefail`.

**Still forbidden:** bare user-facing lines; ad-hoc diagnostics that skip quiet/JSON; a second competing print helper; uncaptured return-via-stdout used as CLI UX.

### 2.2 Mandatory SSOT remark comment blocks (v2.10.1)

Every **SSOT-of-pipeline** use of `printf` / return-via-stdout / cmd-sub fallback **outside** the Output module **must** be documented so humans and AI agents do not treat it as a product-output violation **or** as free product messaging:

1. **Owning function comment block** — explicit **SSOT REMARK** (or equivalent): pipeline data (not product UX); callers must capture; do not route through `out_*` as a string return; do not uncaptured-call as a banner.  
2. **Call-site mark** — short line above each pipeline `printf` / capture naming the exception class.  
3. **Must not “fix”** pipeline returns into the Output module, and must not strip remarks “for cleanliness.”

### 2.3 JSON mode (Principle 5)

- Exactly **one** success JSON value on stdout (trailing newline after the value is **allowed**).  
- Errors on stderr via the same Output module.  
- No human prefixes mixed into the JSON stdout stream.  
- Escaped `\n` inside JSON strings is allowed when data needs it.

### 2.4 Operator identity display (mandatory)

When a **human** line **names the running program** (menu header, about title, other “who is talking” banners), it **MUST** print [app-name-version-display](../../terminologies/app-name-version-display.md): **`APP_NAME` bold**, **`VERSION` italic** — markdown `**{{APP_NAME}}**(*{{VERSION}}*)`. Live scalars from Config.

```sh
# SSOT REMARK (pipeline): identity token string for capture; not a product banner.
# TTY: SGR 1 bold name, SGR 3 italic version. Off-TTY / JSON: plain APP_NAME(VERSION).
# MUST NOT $() a read helper. Last updated: 2026-09-03
util_app_ident() {
    : "${APP_NAME:=app}"
    : "${VERSION:=0.0.0}"
    : "${TTY:=0}"
    : "${JSON:=0}"
    if [ "${TTY}" -eq 1 ] && [ "${JSON}" -eq 0 ]; then
        printf '\033[1m%s\033[0m(\033[3m%s\033[0m)' "${APP_NAME}" "${VERSION}"
        return 0
    fi
    printf '%s(%s)' "${APP_NAME}" "${VERSION}"
}

out_info "$(util_app_ident) — numbered list of live commands"
```

| MUST | MUST NOT |
|------|----------|
| Main-menu / APP_NAME-led submenu headers; about identity titles | Usage / `Next:` invocation lines (`{{APP_NAME}} <verb>`) |
| Live Config `APP_NAME` and `VERSION` (same scalars as `version`) | Filesystem paths; sudoers/cron binary paths |
| TTY: bold name, italic version; off-TTY: plain `APP_NAME(VERSION)` | CSI/ANSI when `TTY=0` or `JSON=1`; raw CSI in README fences |
| Still via `out_*` (quiet/JSON rules unchanged) | Glue the token into JSON as the only `app`/`version` fields — keep separate keys |

Proof when a numbered menu is claimed: **TP-CLI-17**.

## 3. Recommended Output Functions (shell inventory)

**Prefix ownership:** [`shell-function-naming-convention`](../../terminologies/shell-function-naming-convention.md) (`out_*`).  
**Glossary:** [`single-source-of-truth-of-output`](../../terminologies/single-source-of-truth-of-output.md).

| Function | Purpose | Channel | Quiet | JSON |
|----------|---------|---------|-------|------|
| `out_text` | **Human SSOT** — all levels | level-dependent | filters | suppress all human |
| `out_debug` | Debug diagnostics | stderr | DEBUG only | suppress |
| `out_success` | Success / OK | stdout | suppress | suppress |
| `out_info` | Informational | stdout | suppress | suppress |
| `out_warn` | Warnings | stderr | **still show** | suppress |
| `out_error` | Errors | stderr | **always show** | prefer JSON error path |
| `out_die` | Fatal + exit 1 | stderr (+ JSON error) | always | `out_json_error` then human error |
| `out_plain` | Plain text (no prefix) | stdout | suppress | suppress |
| `out_menu_choice` | Numbered menu row; TTY *italic* + light-gray `{{explain}}` | stdout | suppress | suppress |
| `out_msg_n` | Prompt fragment (no newline) | stdout | suppress | suppress |
| `out_empty_line` | Blank visual line | stdout | suppress | suppress |
| `out_double_line` | Separator line | stdout | suppress | suppress |
| `util_json_escape` | Escape string for JSON values | pipeline (class B) | n/a | helper for `out_json*` |
| `util_app_ident` | Identity token **bold** name / *italic* version | pipeline (class B) | n/a | capture into `out_*`; term **app-name-version-display** |
| `out_json` | Machine success/status object | stdout | n/a | only when `JSON=1` |
| `out_json_error` | Machine error object | stderr | n/a | only when `JSON=1` |

Language equivalents (Node/Python/C loggers) **MAY** map to the same contracts with different names — document the mapping in Implementation Notes.

**C++ prefix:** `logger_` for functions (`logger_info`, `logger_warn`, `logger_error`, `logger_fatal`, `logger_debug`, `logger_log`, `logger_output_init`, `logger_set_quiet`, `logger_get_quiet`, `logger_get_debug`) and `LOGGER_` for level tokens (`LOGGER_LEVEL_INFO`, `LOGGER_LEVEL_WARNING`, `LOGGER_LEVEL_ERROR`, `LOGGER_LEVEL_DEBUG`, `LOGGER_LEVEL_FATAL`). The level type is `LoggerOutputLevel`. The functions are `extern "C"`. The translation unit is `.cpp` unless a specialized requirement names a `.c` file. The header may stay `.h` when that requirement names it. Do not introduce `ciao_` or `CIAO_` names. There is no `logger_set_debug` and no `logger_set_verbose`. `g_print` and `g_printerr` stay inside the logger translation unit. The dated-file append in that same unit may `fprintf` the human line. Style and the ship-unit directory are `LM-CPP-CODING-STYLE` and `LM-CPP-FOLDER`. Specialize this mapping into the product logger, output, and JSON requirements. This mold does not cite a product requirement path.

| Shell contract | C++ function | Level |
|----------------|--------------|-------|
| `out_info` | `logger_info` | `LOGGER_LEVEL_INFO` |
| `out_warn` | `logger_warn` | `LOGGER_LEVEL_WARNING` |
| `out_error` | `logger_error` | `LOGGER_LEVEL_ERROR` |
| `out_die` | `logger_fatal` | `LOGGER_LEVEL_FATAL` |
| `out_debug` | `logger_debug` | `LOGGER_LEVEL_DEBUG` |
| quiet flag | `logger_set_quiet` / `logger_get_quiet` | n/a |
| debug flag | `logger_get_debug` | n/a |

The shell inventory keeps `out_warn` on stderr. `logger_warn` emits `WARNING` on stdout. The shell `out_die` exits 1. `logger_fatal` does not exit.

### C++ console contract

Sections §4 and §5 stay the shell contract. This subsection is the C++ contract. The bodies are §3.2, and that section is the one owner. Do not paste those bodies into another mold.

1. Human streams: `INFO`, `WARNING`, and `DEBUG` use stdout (`g_print`). `ERROR` and `FATAL` use stderr (`g_printerr`). The warning token is `WARNING`, not `WARN`. There is no `CRITICAL` level.
2. Stdout human lines stay hidden unless `--verbose` is set. `--verbose` shows them only when the run is not quiet and not JSON. Quiet does not hide human `ERROR` or `FATAL`. Those two stay without `--verbose`.
3. JSON mode implies quiet. `logger_set_quiet(false)` does not clear quiet while JSON mode is on. The only product console line in JSON mode is one JSON object. `--verbose` does not add the human line beside it. An info, warning, error, or fatal event is still that object. A debug event is that object only when debug is on.
4. Append the human line before the display gate. Hiding the console line does not skip the append. The file is `{{APP_NAME}}-<YYYYMMDD>.log`. The directory is created on append with `g_mkdir_with_parents` at mode `0755`. No `mkstemp`. An unresolved directory writes no file.
5. The human line is `[YYYY-MM-DD HH:MM:SS] pid:<pid> [LEVEL] @<component> :] message`. Time is local `localtime` / `strftime`. Clock failure uses `1970-01-01 00:00:00`. The component is `LOG_COMPONENT` from the identity header. The specialized requirement names that token.
6. A normal run uses two environments. Effective user id 0 uses `/var/{{APP_NAME}}/log`. Every other user uses `{{HOME}}/.app/{{APP_NAME}}/log` when `HOME` is non-empty. An empty `HOME` leaves that path unresolved. Do not call `getpwuid`. Do not read `PREFIX` to choose the log directory.
7. `test`, `list`, and `show` ignore `PREFIX`, `HOME`, and the effective user id. `--prefix <dir>` uses `<dir>/var/{{APP_NAME}}/log`. `--home <dir>` uses `<dir>/.app/{{APP_NAME}}/log`. `--prefix` wins when both directory switches are present. Joining strips trailing slashes. `"/"` plus `var/{{APP_NAME}}` is `/var/{{APP_NAME}}`, not `//var/{{APP_NAME}}`.
8. `--log-datestamp` is eight digits. A present value that is not eight digits is rejected. `test` and `show` require the switch and do not substitute today's date. `list` does not require it. A normal run with the switch absent uses today's local date, or `19700101` when the clock fails.
9. `list` and `show` are not log lines. Quiet, JSON, and a missing `--verbose` do not hide them. They leave init before the init log lines, so they do not append. `list` prints sorted basenames of regular files whose names end in `.log`. A missing directory prints nothing and returns success. Any other failure to open that directory exits 1. `show` prints the file bytes and does not add a newline. A missing file exits 1.
10. `logger_log` takes `va_list` by value and uses `va_copy` before `g_strdup_vprintf`. `logger_debug` returns before that call when debug is off. Debug is `--debug` or a non-empty `DEBUG`. There is no debug setter.

**Source of examples:** shell bodies are §3.1. C++ bodies are §3.2. Specialize defaults (`: "${APP_NAME:=app}"` for shell; `PROJECT_NAME` and `LOG_COMPONENT` for C++). Do **not** freeze a product brand into this mold as universal law.

---

## 3.1 Example implementations (portable shell — Type 0 shell CLI)

**Kind:** [template-example-function](../../terminologies/template-example-function.md) (bodies); mode flags as [template-example-variable](../../terminologies/template-example-variable.md).  
Mode flags used: `JSON`, `QUIET`, `DEBUG`, `TTY` (set at script top / dispatcher — **consume `TTY`**; do not re-test `[ -t` inside `out_*`; term **no-retest-tty**).  
**PRINTF EXCEPTION (class A):** only `out_text`, `out_json`, and `out_json_error` may `printf` product lines to fd 1/2. Wrappers must not re-implement print logic.

### Inventory → function map (Type 0 shell CLI)

| Name | Role |
|------|------|
| `out_text` | Human SSOT |
| `out_debug` / `out_success` / `out_info` / `out_warn` / `out_error` | Level wrappers |
| `out_die` | JSON error + human error + `exit 1` |
| `out_plain` / `out_msg_n` | Plain / prompt fragment |
| `out_menu_choice` | Numbered menu row — **only** when a numbered TTY menu is claimed |
| `out_empty_line` / `out_double_line` | Separators |
| `util_json_escape` | Escape for JSON string fields (class B) |
| `out_json` / `out_json_error` | Machine JSON success (stdout) / error (stderr) |

### `out_text` — human SSOT example

```sh
# =============================================================================
# out_text() - SINGLE SOURCE OF TRUTH FOR ALL HUMAN OUTPUT
# =============================================================================
#
# GENERAL PURPOSE:
# Centralized human-readable emitter. Respects --quiet, --json, TTY colors.
# All out_info / out_success / out_warn / out_error / out_plain / … MUST go here.
#
# PRINTF EXCEPTION (class A – inside output SSOT):
# This function MAY printf product human lines to fd 1/2.
#
# Last reviewed: 2026-07-17
# =============================================================================
out_text() {
    local level="$1" msg="$2"
    : "${JSON:=0}" : "${QUIET:=0}" : "${DEBUG:=0}"
    # JSON mode: never emit human-readable lines (machines use out_json*)
    [ "${JSON}" -eq 1 ] && return 0

    case "${level}" in
        out_error) ;;  # always shown (even under --quiet)
        out_warn)  ;;  # still shown under --quiet (stderr diagnostics)
        out_debug) [ "${DEBUG}" -eq 1 ] || return 0 ;;
        *)         [ "${QUIET}" -eq 1 ] && return 0 ;;
    esac

    local RED='' GREEN='' YELLOW='' BLUE='' DESC='' NC=''
    [ "${TTY:-0}" -eq 1 ] && [ "${QUIET}" -eq 0 ] && [ "${JSON}" -eq 0 ] && {
        RED='\033[0;31m'; GREEN='\033[0;32m'; YELLOW='\033[1;33m'
        BLUE='\033[0;34m'; DESC='\033[3;37m'; NC='\033[0m'
    }

    case "${level}" in
        out_error)   printf >&2 "${RED}[ERROR]${NC} %s\n" "${msg}" ;;
        out_warn)    printf >&2 "${YELLOW}[WARN]${NC} %s\n" "${msg}" ;;
        out_debug)   printf >&2 "${BLUE}[DEBUG]${NC} %s\n" "${msg}" ;;
        out_info)    printf "${GREEN}[INFO]${NC} %s\n" "${msg}" ;;
        out_success) printf "${GREEN}[OK]${NC} %s\n" "${msg}" ;;
        plain)       printf "%s\n" "${msg}" ;;
        plain_n)     printf "%s" "${msg}" ;;
        menu_choice)
            # Number + name default; explain italic + light gray (SGR 3+37).
            printf '%s. %s: %b%s%b\n' "${3-}" "${4-}" "${DESC}" "${5-}" "${NC}"
            ;;
        *)           printf "%s\n" "${msg}" ;;
    esac
}
```

### Level wrappers + separators + fatal (examples)

```sh
out_debug()   { out_text out_debug "$*"; }
out_success() { out_text out_success "$*"; }
out_info()    { out_text out_info "$*"; }
out_warn()    { out_text out_warn "$*"; }
out_error()   { out_text out_error "$*"; }

# Fatal: structured JSON error (when JSON=1) then human error, then exit 1
out_die() { out_json_error "$*"; out_text out_error "$*"; exit 1; }

out_plain()      { out_text plain "$*"; }
out_menu_choice() { out_text menu_choice "" "${1-}" "${2-}" "${3-}" }
out_msg_n()      { out_text plain_n "$*"; }   # prompt fragment (no newline)
out_empty_line() { out_text plain ""; }
out_double_line(){ out_text plain "=================================================="; }
```

### `util_json_escape` — pipeline helper for JSON fields (class B)

```sh
# Escape a string for inclusion in a JSON double-quoted value.
# Class B: return-via-stdout for capture by out_json / out_json_error only.
# awk is POSIX; multi-line values become \n between physical lines (sed cannot).
util_json_escape() {
    printf '%s' "${1-}" | awk '
    {
      line = $0
      gsub(/\\/, "\\\\", line)
      gsub(/"/, "\\\"", line)
      gsub(/\t/, "\\t", line)
      gsub(/\r/, "\\r", line)
      if (NR > 1) printf "\\n"
      printf "%s", line
    }'
}
```

### `out_json` — machine success/status on stdout (class A)

```sh
# =============================================================================
# out_json() - Structured success/status JSON on stdout when JSON=1
# =============================================================================
#
# Usage:
#   out_json "type" "optional message" "key" "value" ...
# Raw nested JSON field: key prefixed with "@" (e.g. "@items" → "items":[...])
#
# PRINTF EXCEPTION (class A – inside output SSOT).
# Last reviewed: 2026-07-17
# =============================================================================
out_json() {
    [ "${JSON}" -eq 0 ] && return 0
    local type="$1" message="$2" key raw_key
    shift 2
    printf '{'
    printf '"type":"%s"' "$(util_json_escape "$type")"
    [ -n "$message" ] && printf ',"message":"%s"' "$(util_json_escape "$message")"
    while [ $# -ge 2 ]; do
        key="$1"
        case "$key" in
            @*)
                raw_key="${key#@}"
                printf ',"%s":%s' "$(util_json_escape "$raw_key")" "$2"
                ;;
            *)
                printf ',"%s":"%s"' "$(util_json_escape "$key")" "$(util_json_escape "$2")"
                ;;
        esac
        shift 2
    done
    printf '}\n'
}
```

### `out_json_error` — machine error on stderr (class A)

```sh
# =============================================================================
# out_json_error() - Structured error JSON on stderr when JSON=1
# =============================================================================
#
# Usage: out_json_error "message" "code"
# Enables:  tool --json … > out.json 2> err.log
#
# PRINTF EXCEPTION (class A – inside output SSOT).
# Last reviewed: 2026-07-17
# =============================================================================
out_json_error() {
    [ "${JSON}" -eq 0 ] && return 0
    local message="$1" code="${2:-unknown}"
    printf >&2 '{'
    printf >&2 '"type":"%s"' "out_error"
    [ -n "$message" ] && printf >&2 ',"message":"%s"' "$(util_json_escape "$message")"
    printf >&2 ',"code":"%s"' "$(util_json_escape "$code")"
    printf >&2 '}\n'
}
```

### Minimal usage sketch

```sh
out_info "Starting"
out_success "Done"
out_warn "Fallback used"
out_error "Something failed"
# out_die "Fatal"   # exits 1

JSON=1
out_json "version" "" "app" "${APP_NAME}" "version" "${VERSION}"
out_json_error "not found" "not_found"
```

---

## 3.2 Example implementations (portable C++ logger)

**Kind:** [template-example-function](../../terminologies/template-example-function.md). This section is the one owner of the C++ logger bodies. `LM-CPP-CODING-STYLE` keeps the declaration shape and links here. Do not paste these bodies into another mold. `PROJECT_NAME` and `LOG_COMPONENT` come from the identity header. Specialize those, and specialize `{{APP_NAME}}` in the C++ console contract, into the product requirements. Product source cites those requirements, not this file.

Console lines use `g_print` and `g_printerr` inside the logger translation unit. The dated-file append uses `fprintf` on that file only. §3.1 remains the shell owner. `out_warn` on stderr there is not the C++ `WARNING` stream.

### Quiet, debug, and level

```cpp
void logger_set_quiet(bool quiet)
{
    if (logger_json_mode) {
        logger_quiet_mode = true;
        return;
    }
    logger_quiet_mode = quiet;
}

bool logger_get_quiet(void)
{
    return logger_quiet_mode;
}

bool logger_get_debug(void)
{
    return debug_env_enabled;
}

static const char *logger_level_name(LoggerOutputLevel level)
{
    switch (level) {
        case LOGGER_LEVEL_INFO:    return "INFO";
        case LOGGER_LEVEL_WARNING: return "WARNING";
        case LOGGER_LEVEL_ERROR:   return "ERROR";
        case LOGGER_LEVEL_DEBUG:   return "DEBUG";
        case LOGGER_LEVEL_FATAL:   return "FATAL";
        default:                 return "INFO";
    }
}

static int logger_stderr_level(LoggerOutputLevel level)
{
    return level == LOGGER_LEVEL_ERROR || level == LOGGER_LEVEL_FATAL;
}
```

### Human line and dated file

```cpp
static void logger_emit_chronicle(LoggerOutputLevel level, const char *message)
{
    char timestamp[32];
    time_t now = time(NULL);
    struct tm *tm_ptr;
    const char *text = message ? message : "";
    const char *level_name = logger_level_name(level);

    tm_ptr = localtime(&now);
    if (tm_ptr == NULL ||
        strftime(timestamp, sizeof timestamp, "%Y-%m-%d %H:%M:%S", tm_ptr) == 0) {
        g_strlcpy(timestamp, "1970-01-01 00:00:00", sizeof timestamp);
    }

    if (logger_stderr_level(level)) {
        g_printerr("[%s] pid:%ld [%s] @%s :] %s\n",
                   timestamp, (long)getpid(), level_name, LOG_COMPONENT, text);
    } else {
        g_print("[%s] pid:%ld [%s] @%s :] %s\n",
                timestamp, (long)getpid(), level_name, LOG_COMPONENT, text);
    }
}

static void logger_append_log_file(LoggerOutputLevel level, const char *message)
{
    char timestamp[32];
    time_t now;
    struct tm *tm_ptr;
    FILE *file;
    const char *text = message ? message : "";

    if (logger_log_path[0] == '\0' || logger_folder[0] == '\0') {
        return;
    }
    if (g_mkdir_with_parents(logger_folder, 0755) != 0) {
        g_printerr("cannot create logger folder %s\n", logger_folder);
        if (logger_purpose != 0) {
            exit(1);
        }
        return;
    }
    now = time(NULL);
    tm_ptr = localtime(&now);
    if (tm_ptr == NULL ||
        strftime(timestamp, sizeof timestamp, "%Y-%m-%d %H:%M:%S", tm_ptr) == 0) {
        g_strlcpy(timestamp, "1970-01-01 00:00:00", sizeof timestamp);
    }
    file = fopen(logger_log_path, "a");
    if (file == NULL) {
        g_printerr("cannot open log file %s\n", logger_log_path);
        if (logger_purpose != 0) {
            exit(1);
        }
        return;
    }
    fprintf(file, "[%s] pid:%ld [%s] @%s :] %s\n",
            timestamp, (long)getpid(), logger_level_name(level), LOG_COMPONENT, text);
    fclose(file);
}
```

### Display gate and JSON object

```cpp
static gchar *logger_json_escape(const char *text)
{
    GString *out = g_string_new("");
    const unsigned char *cursor = (const unsigned char *)(text ? text : "");

    for (; *cursor != '\0'; cursor++) {
        switch (*cursor) {
            case '\\':
                g_string_append(out, "\\\\");
                break;
            case '"':
                g_string_append(out, "\\\"");
                break;
            case '\n':
                g_string_append(out, "\\n");
                break;
            case '\r':
                g_string_append(out, "\\r");
                break;
            case '\t':
                g_string_append(out, "\\t");
                break;
            default:
                if (*cursor < 0x20) {
                    g_string_append_printf(out, "\\u%04x", *cursor);
                } else {
                    g_string_append_c(out, (gchar)*cursor);
                }
                break;
        }
    }
    return g_string_free(out, FALSE);
}

void logger_log(LoggerOutputLevel level, const char *format, va_list ap)
{
    if (level == LOGGER_LEVEL_DEBUG && !logger_get_debug()) {
        return;
    }

    va_list ap_copy;
    va_copy(ap_copy, ap);

    gchar *message = g_strdup_vprintf(format, ap_copy);

    logger_append_log_file(level, message);

    if (logger_json_mode) {
        gchar *escaped = logger_json_escape(message ? message : "");
        g_print("{\"timestamp\":%ld,\"level\":\"%s\",\"message\":\"%s\"}\n",
                (long)time(NULL),
                logger_level_name(level),
                escaped);
        g_free(escaped);
    } else if (logger_stderr_level(level) || (logger_verbose && !logger_get_quiet())) {
        logger_emit_chronicle(level, message);
    }

    g_free(message);
    va_end(ap_copy);
}

void logger_fatal(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    logger_log(LOGGER_LEVEL_FATAL, format, args);
    va_end(args);
}

void logger_debug(const char *format, ...)
{
    if (!logger_get_debug()) return;

    va_list args;
    va_start(args, format);
    logger_log(LOGGER_LEVEL_DEBUG, format, args);
    va_end(args);
}
```

### Two environments and test-purpose paths

```cpp
static void logger_join_base(char *out, size_t out_size, const char *head, const char *tail)
{
    gchar *trimmed;
    gsize length;
    gint wrote;

    if (head == NULL || head[0] == '\0' || strchr(head, '\n') != NULL || strchr(head, '\r') != NULL) {
        g_printerr("logger folder directory is empty or not one line\n");
        exit(1);
    }
    trimmed = g_strdup(head);
    length = strlen(trimmed);
    while (length > 1 && trimmed[length - 1] == '/') {
        trimmed[--length] = '\0';
    }
    if (strcmp(trimmed, "/") == 0) {
        wrote = g_snprintf(out, out_size, "/%s", tail);
    } else {
        wrote = g_snprintf(out, out_size, "%s/%s", trimmed, tail);
    }
    g_free(trimmed);
    if (wrote < 0 || (size_t)wrote >= out_size) {
        g_printerr("logger folder path is too long\n");
        exit(1);
    }
}
```

Inside `logger_output_init`, after the stamp checks, the directory is chosen once. A test-purpose command does not read `HOME`, `PREFIX`, or the effective user id. A normal run does not read `--prefix` or `--home`.

```cpp
        if (logger_purpose != 0) {
            const char *dir = logger_prefix_arg != NULL ? logger_prefix_arg : logger_home_arg;
            if (g_snprintf(tail, sizeof tail, "%s/%s",
                           logger_prefix_arg != NULL ? "var" : ".app",
                           PROJECT_NAME) >= (gint)sizeof tail) {
                g_printerr("logger folder path is too long\n");
                exit(1);
            }
            logger_join_base(base, sizeof base, dir, tail);
            logger_apply_base(base, stamp);
        } else if (geteuid() == 0) {
            if (g_snprintf(base, sizeof base, "/var/%s", PROJECT_NAME) >= (gint)sizeof base) {
                g_printerr("logger folder path is too long\n");
                exit(1);
            }
            logger_apply_base(base, stamp);
        } else {
            const char *home = getenv("HOME");
            if (home != NULL && home[0] != '\0') {
                if (g_snprintf(tail, sizeof tail, ".app/%s", PROJECT_NAME) >= (gint)sizeof tail) {
                    g_printerr("logger folder path is too long\n");
                    exit(1);
                }
                logger_join_base(base, sizeof base, home, tail);
                logger_apply_base(base, stamp);
            }
        }
```

`logger_apply_base` appends `/log` and then `PROJECT_NAME-<stamp>.log`. `list` and `show` run next and exit, before any init log line:

```cpp
    if (logger_purpose == 2) {
        logger_list_log_files();
        exit(0);
    }
    if (logger_purpose == 3) {
        logger_show_log_file();
        exit(0);
    }
```

A second test-purpose verb exits 1. A missing directory switch exits 1. `test` and `show` require an eight-digit stamp. A present stamp that is not eight digits is a different failure. `list` does not require a stamp. The checks below are separate sites in `logger_output_init`, not one nested block.

```cpp
static void logger_set_purpose(int purpose)
{
    if (logger_purpose != 0) {
        g_printerr("one test purpose command\n");
        exit(1);
    }
    logger_purpose = purpose;
}

        if (logger_prefix_arg == NULL && logger_home_arg == NULL) {
            g_printerr("test purpose command requires --prefix or --home\n");
            exit(1);
        }
        if ((logger_purpose == 1 || logger_purpose == 3) && logger_datestamp_arg == NULL) {
            g_printerr("test purpose command requires --log-datestamp YYYYMMDD\n");
            exit(1);
        }
    if (logger_datestamp_arg != NULL && !logger_datestamp_ok(logger_datestamp_arg)) {
        g_printerr("--log-datestamp requires YYYYMMDD\n");
        exit(1);
    }
```

### List and show

`logger_filename_cmp` exists because passing `strcmp` as a `GCompareFunc` fails under `-Werror`.

```cpp
static gint logger_filename_cmp(gconstpointer left, gconstpointer right)
{
    return strcmp((const char *)left, (const char *)right);
}

static void logger_list_log_files(void)
{
    GDir *dir;
    const char *name;
    GSList *names = NULL;
    GSList *item;
    GError *error = NULL;

    if (logger_folder[0] == '\0') {
        g_printerr("log directory unresolved\n");
        exit(1);
    }
    dir = g_dir_open(logger_folder, 0, &error);
    if (dir == NULL) {
        if (error != NULL && g_error_matches(error, G_FILE_ERROR, G_FILE_ERROR_NOENT)) {
            g_error_free(error);
            return;
        }
        g_printerr("cannot read log directory %s\n", logger_folder);
        if (error != NULL) {
            g_error_free(error);
        }
        exit(1);
    }
    while ((name = g_dir_read_name(dir)) != NULL) {
        char path[4096];

        if (!g_str_has_suffix(name, ".log")) {
            continue;
        }
        if (g_snprintf(path, sizeof path, "%s/%s", logger_folder, name) >= (gint)sizeof path) {
            g_dir_close(dir);
            g_slist_free_full(names, g_free);
            g_printerr("log file path is too long\n");
            exit(1);
        }
        if (!g_file_test(path, G_FILE_TEST_IS_REGULAR)) {
            continue;
        }
        names = g_slist_insert_sorted(names, g_strdup(name), logger_filename_cmp);
    }
    g_dir_close(dir);
    for (item = names; item != NULL; item = item->next) {
        g_print("%s\n", (char *)item->data);
    }
    g_slist_free_full(names, g_free);
}

static void logger_show_log_file(void)
{
    gchar *text = NULL;
    gsize length = 0;
    GError *error = NULL;

    if (logger_log_path[0] == '\0') {
        g_printerr("log file unresolved\n");
        exit(1);
    }
    if (!g_file_get_contents(logger_log_path, &text, &length, &error)) {
        g_printerr("cannot read log file %s\n", logger_log_path);
        if (error != NULL) {
            g_error_free(error);
        }
        exit(1);
    }
    if (length > 0) {
        g_print("%s", text);
    }
    g_free(text);
}
```

---

## 4. Channel contract (stdout vs stderr)

This table is the shell contract. The C++ streams are the C++ console contract in §3. C++ `WARNING` uses stdout. C++ `FATAL` does not exit.

| Channel | Use for |
|---------|---------|
| **stdout (fd 1)** | Human product messages in normal mode; **single** JSON object (or documented stream) in JSON mode |
| **stderr (fd 2)** | Warnings, errors, fatal paths, debug diagnostics |

Rules:

1. JSON success path **MUST NOT** mix human banners onto stdout with the JSON body.  
2. Errors in JSON mode go to stderr (structured error emitter) while still allowing non-zero exit.  
3. Quiet mode **MUST NOT** hide fatal errors or (by default) warnings.

## 5. Mode Behavior

Sections 5.1 through 5.4 describe shell modes. The C++ display gate is the C++ console contract in §3.

### 5.1 Normal (Interactive) Mode
- Colored output when TTY is detected
- Full human-readable messages with prefixes and visual elements

### 5.2 Quiet Mode (`--quiet` or `QUIET=1`)
- Suppresses informational and success messages
- Still shows warnings, errors, and fatal errors

### 5.3 JSON Mode (`--json` or `JSON=1`)
- **Automatically forces quiet mode**
- Outputs exactly **one** valid JSON object on the success path (or documented equivalent)
- No human-readable text is allowed on the product success path
- Designed for machine consumption (scripts, AI agents, CI/CD)
- Fail-closed command outcomes (e.g. uninstall confirm required) use structured error codes — not fake success JSON

### 5.4 Debug Mode (`--debug` or `DEBUG=1`)
- Extra diagnostics on stderr when designed
- Suppressed under JSON
- Must not break JSON purity on stdout

## 6. Implementation Guidelines

- Centralized logic should handle colors, quiet filtering, and JSON formatting.
- TTY detection should be used to decide color support.
- All convenience functions should call the central output system.
- JSON mode must strictly suppress all human-readable output on the success path.
- In **product source**, document output ownership by citing the specialized **live** output requirement (after specialization), not this template file path and not coding skills. See `template-defensive-practices.md` §2.7.

## 7. Why This Pattern Exists (Direct CIAO Alignment)

- **CIAO Principle 4 / CIAO-Lite O · Principle 20 – Over-protect / Protect Against AI** (https://github.com/cloudgen/ciao): A single source of output prevents output pollution, inconsistent behavior, and hard-to-debug issues across different execution environments.
- **CIAO Principle 2 – Intentional** (https://github.com/cloudgen/ciao): Clear separation between human-readable and machine-readable output makes behavior predictable.
- **CIAO Principle 3 – Anti-fragile** (https://github.com/cloudgen/ciao): The system works reliably in terminals, scripts, Docker, CI/CD, and non-interactive environments.

## 8. Design Principles (CIAO / CIAO-Lite)

- **Caution (CIAO Principle 1)**: Prevents output pollution and inconsistent behavior across environments.
- **Intentional (CIAO Principle 2)**: Clear separation between human and machine output.
- **Anti-fragile (CIAO Principle 3)**: Works reliably in terminals, scripts, Docker, and CI/CD.
- **Over-protect (CIAO Principle 4 / CIAO-Lite O · Principle 20)**: JSON mode strictly enforces quiet to guarantee clean machine output.

## 9. Protection Rule (Sacred)

**Future AI assistants, Grok, or maintainers MUST NOT**:

- Add raw `echo`, `printf`, or direct fd writes for **product user/machine messages** outside the central output functions (see §2.1 for allowed exceptions).
- Treat return-via-stdout, file redirects, or tool pipes as a license to print user banners without `out_*`.
- Bypass the central output functions for status, errors, or JSON results.
- Remove or weaken the rule that `--json` forces quiet mode.
- Create output that differs between interactive and non-interactive modes unless explicitly documented.
- Remove color support or TTY detection without strong justification.
- Simplify the output system "for cleanliness".
- Emit fake success JSON for fail-closed outcomes that require confirm or integrity failure.
- Paste this template’s path (or any `skill-*.md`) into product source as the output SSOT authority — specialize and cite the live `requirement-*-output-*.md` instead.
- Print a human identity banner (menu header, about title) as a **bare** `{{APP_NAME}}` — **MUST** use **`{{APP_NAME}}({{VERSION}})`** with **bold** name and *italic* version on TTY (term **app-name-version-display**; §2.4).
- Draw a claimed numbered menu off **default-cli-main-menu-style** — **MUST NOT** print numbered-menu `{{explain}}` unstyled on a TTY (it **MUST** be *italic* and light gray via `out_menu_choice`).
- Emit CSI/ANSI for the identity token when `TTY=0` or `JSON=1`, or paste raw CSI into a product README fence.
- Treat the shell `out_warn` stderr row as the C++ `WARNING` stream.
- Make `logger_fatal` call `exit`.
- Hide a C++ human `ERROR` or `FATAL` line behind `--verbose` or quiet.
- Copy the §3.2 C++ bodies into a second mold.

**Single Source of Output is non-negotiable for CIAO compliance.**  
**Not every `printf` is forbidden — only product messaging that bypasses the SSOT.**

---


## Design-time verification

| TP family / ID | Proof mold | Planned suite |
|----------------|------------|---------------|
| **TP-CLI-02,04,07** version/json/quiet | `../tests/template-shell-cli-test-plan.md` | `tests/test_cli.sh` |
| **TP-CLI-17** **default-cli-main-menu-style** (header `APP_NAME(VERSION)`; numbered `{{explain}}` italic + light gray) | same | same (when numbered menu claimed) |
| **TP-CLI-06** error path | same | same |
| **TP-CLI-12** `out_json` `@key` nested/numeric | same | same |
| Domain JSON contracts after specialize | **TP-<SUBJECT>-*** | product domain suite |

**RTM:** `../tests/template-requirement-test-traceability.md`


**Last Updated**: 2026-10-05  
**Owner**: Output & Logging Layer (Generalized Template)  
**Version history:**  
- **2.7.2** (2026-10-05): Cite **ui-view-for-app-log**. The palette is not copied into this mold. The non-UI show command stays raw bytes. §3.2 `logger_*` bodies unchanged.  
- **2.7.1** (2026-10-04): Cite project log content type. The catalog stays in the term. §3.2 `logger_*` bodies unchanged.  
- **2.7.0** (2026-10-03): C++ console contract and §3.2 `logger_*` bodies. Shell `out_*` rows unchanged. The C++ prefix does not cite a product requirement path.  
- **2.6.0** (2026-09-17): Example-sync from Type 0 POSIX CLI — drop frozen product names; `util_json_escape` uses awk (newlines/tabs); `@items` not a product brand.  
- **2.5.0** (2026-09-03): Cite **default-cli-main-menu-style** for numbered-menu look.  
- **2.4.0** (2026-09-03): `out_menu_choice`; TTY numbered `{{explain}}` *italic* + light gray (SGR 3+37).  
- **2.3.0** (2026-09-03): Identity token **bold** `APP_NAME` / *italic* `VERSION`; `util_app_ident`; no CSI off-TTY.  
- **2.2.0** (2026-09-03): **§2.4** operator identity display **`{{APP_NAME}}({{VERSION}})`**; **TP-CLI-17**.  
- **2.1.0** (2026-07-17): Full portable **§3.1** shell examples (`out_*` + `util_json_escape`) from Type 0 shell CLIs.  
- **2.0.0** (2026-07-14): CIAO v2.10.2 Principle 5 SSOT family; pipeline SSOT remarks; prefer printf; JSON newline FAQ alignment.  
- **1.1.0** (2026-07-14): Channel contract; `out_debug` / `out_json_error`; fail-closed JSON.  
- **1.0.0**: Initial output SSOT + printf exceptions.  

**Alignment**: [cloudgen/ciao](https://github.com/cloudgen/ciao) v2.10.2 Principle 5 (+14 channels); `template-ciao-principles.md`; shell **SSOT** `template-shell-script-coding.md`; glossary `single-source-of-truth-of-output`; `shell-function-naming-convention`.

---

**How to use this template**:
1. Keep this file under `docs/templates/requirements/`; specialize into a project `requirement-*-output-requirements.md` when the project needs enforceable output rules.
2. Implement the central output functions early — copy/adapt **§3.1** for POSIX shell (or map equivalents in Node/Python).
3. Enforce that product messages never use raw `echo`/`printf` outside the central module; document §2.1 exceptions in specialized requirements and in the matching function comment blocks.
4. Keep the JSON mode "forces quiet" rule and Protection Rule intact.
5. Product source comments cite the **specialized requirement**, never this template path.
6. Register the requirement in `docs/requirements/index.md` (requirement row only).