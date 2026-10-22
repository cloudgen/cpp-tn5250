---
name: selfmanaged-example
id: LM-SELFMANAGED-EXAMPLE
kind: law-mold
description: >
  Portable law mold. Cite as LM-SELFMANAGED-EXAMPLE (path secondary).
---

```
#!/bin/sh
# =============================================================================

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

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
| **Online self-managed** | `docs/terminologies/online-self-managed.md` | `product-law` | Example mode |
| **Self-management** | `docs/terminologies/self-management.md` | `product-law` | Lifecycle umbrella |
| **Ship unit** | `docs/terminologies/ship-unit.md` | `identity-runtime` | Example ship unit body |

**SSOT types used:** `identity-runtime` · `meta-catalog` · `policy` · `product-law`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## Sample map (Type 0 online selfmanaged package)

**Kind:** [template-example-function](../../terminologies/template-example-function.md). This mold is a **worked ship-unit illustration**. Full function bodies live on **one owner** mold — copy from there; do not fork a second copy here.

| Concern | Owner mold | Sample to copy |
|---------|------------|----------------|
| Empty argv (TTY confirm vs Type O ensure) | **`LM-SHELL-CLI-ZERO-ARGUMENTS`** §5.5b | `inst_maybe_install` / `inst_self_install` |
| Type 0 dispatcher | **`LM-CLI-INTERFACE`** Example `app_main` | `app_main` · `app_help` · `app_version` |
| CLI self-place (`$0` copy / dest 0755·0700) | **`LM-SHELL-CLI-SELF-INSTALL`** §3 | `inst_self_install` · `inst_cli_dest_mode` |
| Numbered TTY menu (`read` in current shell) | **`LM-CLI-DEFAULT-INTERACTION`** §4.1 | `app_cmd_menu` (optional; not Type O-S default) |
| `self-update` + `SKIP_DOMAIN_START` | **`LM-SELF-MANAGEMENT`** §7.4 | `inst_self_update` |
| `self-uninstall` confirm (never `$()`) | **`LM-SELF-MANAGEMENT`** §7.5 | `inst_self_uninstall` |
| Companion after place (PATH; skip domain start on update) | **`LM-SELF-MANAGEMENT`** §7.6 | `inst_ensure_companion` |
| Channel + atomic install | **`LM-ONLINE-INSTALL`** §3.6 | `inst_perform_install` · `inst_perform_install_atomic_install` |
| PATH ensure + `rc-test --root` | **`LM-PATH-AND-SHELL-SUPPORT`** §3.1 | `path_add_bashrc` · `path_rc_test` |
| Volatile cache vs durable `{{HOME}}/.local/{{APP_NAME}}` | **`LM-SHELL-CLI-STORAGE`** | `util_resolve_storage` · `util_resolve_persistent_storage` |
| `out_*` | **`LM-OUTPUT-REQUIREMENTS`** §3.1 | `out_text` · `util_json_escape` |
| `prompt_yes_no` / `prompt_ask` / first-shot | **`LM-INTERACTIVE-VS-NONINTERACTIVE`** | current-shell call · `inst_maybe_install` |

Specialize into live `requirement-*.md`. Product ALIGNMENT cites those files only — never this mold.

# selfmanaged - Shell script bootstrap for self Installation & Maintenance
# =============================================================================
#
# FULL FEATURED SELF-MANAGED PROGRAM (CIAO / CIAO-Lite Compliant)
#
# This is the single executable POSIX /bin/sh implementation of the selfmanaged
# tool. Project requirements (docs/requirements/ only — never cite templates here):
# - requirement-shell-cli-interface.md
# - requirement-shell-idempotency.md
# - requirement-shell-self-management.md
# - requirement-shell-modular-function-design.md
# - requirement-shell-output-requirements.md
# - requirement-shell-interactive-vs-noninteractive.md
# Plus CIAO Protection Zones and "DO NOT MODIFY" rules.
#
# Philosophy: CIAO (Caution • Intentional • Anti-fragile • Over-engineered)
# Single file for curl | sh compatibility.
#
# APP NAME: selfmanaged via APP_NAME (Config SSOT; safe default below).
# REPO_USER / REPO_NAME: GitHub owner/repo identity for the install channel.
# SCRIPT_URL: product channel SSOT — composed from repo identity + APP_NAME (raw content URL).
#   Override SCRIPT_URL with env for a full custom channel; or override REPO_* before first use
#   so the composed default follows a fork. Empty SCRIPT_URL disables version-check / self-update network steps.
#
# =============================================================================

set -u  # Treat unset variables as error (defensive)
# Note: We do NOT use set -e globally. We use explicit error handling via out_die.

# =============================================================================
# GLOBAL SAFE DEFAULTS (Single Source of Truth for configuration)
# =============================================================================
: "${APP_NAME:=selfmanaged}"
: "${APP_DESC:=Shell script bootstrap for self Installation & Maintenance}"
: "${SHORT_DESCRIPTION:=${APP_DESC}}"
: "${DESCRIPTION:=POSIX /bin/sh Type 0 CLI: install, version-check, self-update, self-uninstall, and about.}"
# Product version SSOT (first-commit baseline 1.0.0). Extractors use: grep '^VERSION="'
VERSION="1.0.0"
: "${VERSION:=1.0.0}"

# Runtime flags (safe defaults)
: "${QUIET:=0}"
: "${JSON:=0}"
: "${FORCE:=0}"
: "${FORCE_REINSTALL:=0}"
: "${DEBUG:=0}"
: "${TTY:=0}"

# ----------------------------- Safe Variable Defaults ------------------------
: "${GLOBAL_BIN:=/usr/local/bin}"
: "${USER_BIN:=${HOME}/.local/bin}"
: "${INSTALL_PATH:=${GLOBAL_BIN}/${APP_NAME}}"
# Repository identity → install channel (raw.githubusercontent.com composition)
: "${REPO_USER:=cloudgen}"
: "${REPO_NAME:=selfmanaged}"
: "${SCRIPT_URL:=https://raw.githubusercontent.com/${REPO_USER}/${REPO_NAME}/main/${APP_NAME}}"
: "${CHECKSUM:=}"

[ -t 0 ] && [ -t 1 ] && TTY=1
USERNAME="$(id -un 2>/dev/null || echo "unknown")"
# =============================================================================
# out_text() - SINGLE SOURCE OF TRUTH FOR ALL OUTPUT
# =============================================================================
#
# GENERAL PURPOSE:
# Centralized output handler for all human-readable messages.
# Respects --quiet, --json, and TTY detection for colors.
# All user-facing text (out_info, out_success, out_warn, out_error, etc.) MUST go through this
# function to maintain consistency and JSON-mode compatibility.
#
# INTENTIONAL DESIGN:
# This is the single source of truth for all terminal output in the project.
# Never use raw echo/printf for product user messages elsewhere.
#
# PRINTF EXCEPTION (class A – inside output SSOT):
# This function MAY call printf to fd 1/2 for product human messages.
# That is intentional: out_text is the authorized human emitter.
# Other code must not copy these printf lines for banners/status; call out_* instead.
# See requirement-shell-output-requirements.md §2.1.1 (printf exceptions).
#
# Applied exactly as required by requirement-shell-output-requirements.md
# Last reviewed: 2026-07-12
# Lessons Learned (CIAO Reflection):
# 2026-07-12: Quiet mode previously suppressed warnings; requirement says
#             quiet MUST show errors and SHOULD show warnings on stderr.
#             Added out_debug (stderr, DEBUG=1 only, suppressed under JSON).
# 2026-07-12: Documented that not every printf is banned — only product messaging
#             that bypasses this SSOT (return-via-stdout, file I/O, tool pipes allowed).
# =============================================================================
out_text() {
    local level="$1" msg="$2"
    : "${JSON:=0}" : "${QUIET:=0}" : "${DEBUG:=0}"
    # JSON mode: never emit human-readable lines (machines use out_json*)
    [ "${JSON}" -eq 1 ] && return 0

    case "${level}" in
        out_error)
            # Always shown (even under --quiet)
            ;;
        out_warn)
            # Shown under --quiet (diagnostics stay on stderr)
            ;;
        out_debug)
            [ "${DEBUG}" -eq 1 ] || return 0
            ;;
        *)
            [ "${QUIET}" -eq 1 ] && return 0
            ;;
    esac

    local RED='' GREEN='' YELLOW='' BLUE='' NC=''
    [ "${TTY:-0}" -eq 1 ] && [ "${QUIET}" -eq 0 ] && [ "${JSON}" -eq 0 ] && {
        RED='\033[0;31m'; GREEN='\033[0;32m'; YELLOW='\033[1;33m'; BLUE='\033[0;34m'; NC='\033[0m'
    }

    case "${level}" in
        out_error)   printf >&2 "${RED}[ERROR]${NC} %s\n" "${msg}" ;;
        out_warn)    printf >&2 "${YELLOW}[WARN]${NC} %s\n" "${msg}" ;;
        out_debug)   printf >&2 "${BLUE}[DEBUG]${NC} %s\n" "${msg}" ;;
        out_info)    printf "${GREEN}[INFO]${NC} %s\n" "${msg}" ;;
        out_success) printf "${GREEN}[OK]${NC} %s\n" "${msg}" ;;
        plain)       printf "%s\n" "${msg}" ;;
        plain_n)     printf "%s" "${msg}" ;;
        *)           printf "%s\n" "${msg}" ;;
    esac
}

# =============================================================================
# out_debug() - Debug diagnostics on stderr (DEBUG=1 only; never under --json)
# =============================================================================
out_debug() { out_text out_debug "$*"; }

# =============================================================================
# out_success()
# =============================================================================
#
# GENERAL PURPOSE:
# Convenience wrappers around out_text() for common message types.
# 
# - out_success()   → green [OK]
#
# CRITICAL RULE:
# These are the ONLY allowed ways to produce product user-visible messages
# (see §2.1.1 for non-product printf exceptions: return values, file I/O, pipes).
# All product output must respect --quiet and --json via out_text.
#
# INTENTIONAL DESIGN:
# Short, readable calls throughout the script while keeping all real logic
# inside out_text() as Single Source of Truth.
#
# Last reviewed: 2026-07-12
# =============================================================================
out_success() { out_text out_success "$*"; }

# =============================================================================
# out_info()
# =============================================================================
#
# GENERAL PURPOSE:
# Convenience wrappers around out_text() for common message types.
# 
# - out_info()      → green [INFO]
#
# CRITICAL RULE:
# These are the ONLY allowed ways to produce product user-visible messages
# (see §2.1.1 for non-product printf exceptions: return values, file I/O, pipes).
# All product output must respect --quiet and --json via out_text.
#
# INTENTIONAL DESIGN:
# Short, readable calls throughout the script while keeping all real logic
# inside out_text() as Single Source of Truth.
#
# Last reviewed: 2026-07-12
# =============================================================================
out_info() { out_text out_info "$*"; }

# =============================================================================
# out_warn()
# =============================================================================
#
# GENERAL PURPOSE:
# Convenience wrappers around out_text() for common message types.
# 
# - out_warn()      → yellow [WARN]
#
# CRITICAL RULE:
# These are the ONLY allowed ways to produce product user-visible messages
# (see §2.1.1 for non-product printf exceptions: return values, file I/O, pipes).
# All product output must respect --quiet and --json via out_text.
#
# INTENTIONAL DESIGN:
# Short, readable calls throughout the script while keeping all real logic
# inside out_text() as Single Source of Truth.
#
# Last reviewed: 29 April 2026
# =============================================================================
out_warn() { out_text out_warn "$*"; }

out_error()   { out_text "out_error"   "$*"; }
# =============================================================================
# out_die()
# =============================================================================
#
# GENERAL PURPOSE:
# Convenience wrappers around out_text() for common message types.
# 
# - out_die()       → out_error + exit(1)  (also triggers JSON out_error)
#
# CRITICAL RULE:
# These are the ONLY allowed ways to produce product user-visible messages
# (see §2.1.1 for non-product printf exceptions: return values, file I/O, pipes).
# All product output must respect --quiet and --json via out_text.
#
# INTENTIONAL DESIGN:
# Short, readable calls throughout the script while keeping all real logic
# inside out_text() as Single Source of Truth.
#
# Last reviewed: 29 April 2026
# =============================================================================
out_die() { out_json_error "$*"; out_text out_error "$*"; exit 1; }

# =============================================================================
# out_plain() - Output plain text
# =============================================================================
#
# GENERAL PURPOSE:
# Convenience function to output plain text (no prefix, no color).
# Part of the standardized out_* output system.
#
# CRITICAL RULE:
# All product user-facing text MUST go through the output system.
# (see §2.1.1 for non-product printf exceptions: return values, file I/O, pipes).
#
# INTENTIONAL DESIGN:
# Short, readable call while keeping real logic in out_text().
#
# Last reviewed: 2026-07-12
# =============================================================================

out_plain() {
    out_text plain "$*"
}

# =============================================================================
# out_msg_n() - Output message WITHOUT trailing newline (for interactive prompts)
# =============================================================================
#
# GENERAL PURPOSE:
# Convenience wrapper around out_text() for printing prompts that require
# user input on the SAME line (e.g. "Continue? (y/N)? ").
# Used exclusively by prompt_yes_no() and any future interactive prompts.
#
# CRITICAL RULE:
# This is the ONLY allowed way to produce non-newline product prompt text.
# WARNING — do-not-capture-read (**PP-A-22**): prompt_ask MUST NOT return via
# class-B $() / printf. Value is PROMPT_ASK_VALUE in the current shell.
# All product output must respect --quiet and --json (never shown in those modes).
#
# INTENTIONAL DESIGN:
# Short, readable call while keeping real logic in out_text() as Single
# Source of Truth. Uses the existing 'plain_n' level already supported
# by out_text().
#
# CIAO PRINCIPLES APPLIED:
# - Caution: Never breaks prompt flow in non-interactive/curl | sh mode
# - Intentional: Explicitly named for prompt usage (not generic plain_n)
# - Anti-fragile: Works with TTY detection, colors, and JSON/quiet guards
# - Over-protect: Follows exact same pattern as out_plain/out_info/etc.
#
# ALIGNMENT (live requirements only):
# - requirement-shell-output-requirements.md (out_* SSOT, plain_n)
# - requirement-shell-interactive-vs-noninteractive.md (prompt fragments)
#
# !!! DO NOT MODIFY OR SIMPLIFY THIS FUNCTION !!!
# Designed to be reusable in other CIAO-Lite projects.
#
# Lessons Learned (CIAO Reflection):
# 2026-05-31: Added this missing convenience wrapper after prompt_yes_no()
#             was referencing a non-existent helper. Prevents regression
#             in interactive confirmation flow.
# 2026-07-12: ALIGNMENT corrected to live docs/requirements/ paths only.
#
# Last reviewed: 2026-07-12
# =============================================================================
out_msg_n() { out_text plain_n "$*"; }

# =============================================================================
# out_empty_line()
# =============================================================================
#
# GENERAL PURPOSE:
# Convenience wrappers around out_text() for common message types.
# 
# - out_empty_line() → visual separators
#
# CRITICAL RULE:
# These are the ONLY allowed ways to produce product user-visible messages
# (see §2.1.1 for non-product printf exceptions: return values, file I/O, pipes).
# All product output must respect --quiet and --json via out_text.
#
# INTENTIONAL DESIGN:
# Short, readable calls throughout the script while keeping all real logic
# inside out_text() as Single Source of Truth.
#
# Last reviewed: 29 April 2026
# =============================================================================
out_empty_line() { out_text plain ""; }


# =============================================================================
# out_double_line()
# =============================================================================
#
# GENERAL PURPOSE:
# Convenience wrappers around out_text() for common message types.
# 
# - out_double_line() → visual separators
#
# CRITICAL RULE:
# These are the ONLY allowed ways to produce product user-visible messages
# (see §2.1.1 for non-product printf exceptions: return values, file I/O, pipes).
# All product output must respect --quiet and --json via out_text.
#
# INTENTIONAL DESIGN:
# Short, readable calls throughout the script while keeping all real logic
# inside out_text() as Single Source of Truth.
#
# Last reviewed: 29 April 2026
# =============================================================================
out_double_line() { out_text plain "=================================================="; }

# =============================================================================
# out_json() - JSON output helper
# =============================================================================
#
# GENERAL PURPOSE:
# Emits clean, machine-readable JSON when --json flag is used.
# Used by all command modes that support structured output.
#
# INTENTIONAL DESIGN:
# Keeps JSON output minimal, consistent, and escaped safely.
# Must be used together with out_json_error() for errors.
#
# PRINTF EXCEPTION (class A – inside output SSOT):
# This function MAY printf product JSON to stdout. Nested
# printf|sed is only for field escaping (tool pipe, still SSOT-owned).
# Command logic must not emit JSON with raw printf; call out_json instead.
# See requirement-shell-output-requirements.md §2.1.1.
#
# Last reviewed: 2026-07-12
# =============================================================================

out_json() {
    [ "${JSON}" -eq 0 ] && return 0
    local type="$1" message="$2"; shift 2
    # Success/status JSON on stdout (SSOT-of-stdout; pure for pipes)
    printf '{'
    printf '"type":"%s"' "$type"
    [ -n "$message" ] && printf ',"message":"%s"' "$(printf '%s' "$message" | sed 's/"/\\"/g')"
    while [ $# -ge 2 ]; do printf ',"%s":"%s"' "$1" "$2"; shift 2; done
    printf '}\n'
}

# =============================================================================
# out_json_error() - JSON error on stderr (SSOT-of-stderr)
# =============================================================================
#
# GENERAL PURPOSE:
# Emit a structured error object in JSON mode on **stderr** so success
# consumers can use:  tool --json … > out.json 2> err.log
#
# PRINTF EXCEPTION (class A – inside output SSOT):
# This function MAY printf structured error JSON to stderr (product machine
# channel). Nested printf|sed is escape-only. Callers use out_json_error /
# out_die — never hand-roll JSON with printf in command logic.
# See requirement-shell-output-requirements.md §2.1.1.
#
# Lessons Learned (CIAO Reflection):
# 2026-07-12: Previously delegated to out_json (stdout), which mixed errors
#             into the success channel. Errors now always go to stderr.
#
# Last reviewed: 2026-07-12
# =============================================================================

out_json_error() {
    [ "${JSON}" -eq 0 ] && return 0
    local message="$1" code="${2:-unknown}"
    printf >&2 '{'
    printf >&2 '"type":"%s"' "out_error"
    [ -n "$message" ] && printf >&2 ',"message":"%s"' "$(printf '%s' "$message" | sed 's/"/\\"/g')"
    printf >&2 ',"code":"%s"' "$code"
    printf >&2 '}\n'
}

# =============================================================================
# inst_perform_install() - Perform the actual installation (v2 with checksum)
# =============================================================================
#
# GENERAL PURPOSE:
# Orchestrates the complete installation flow:
#   1. Privilege-aware path setup (root → /usr/local/bin, normal user → ~/.local/bin)
#   2. Early exit if already installed (unless --force / FORCE_REINSTALL=1)
#   3. Target directory preparation
#   4. Secure download with layered checksum verification:
#        - If CHECKSUM env var is set → strict verification (user/CI pinned version)
#        - Otherwise → best-effort verification via ${SCRIPT_URL}.sha256 (if present)
#   5. Atomic move + chmod + PATH update via inst_perform_install_atomic_install()
#
# This is the SINGLE SOURCE OF TRUTH for all installation operations
# (initial install, self-update, and forced reinstall).
#
# CIAO PRINCIPLES APPLIED:
# - Caution (Principle 1): Never trust network download without verification when possible.
#   Always use mktemp, explicit error checks, and atomic mv.
# - Intentional (Principle 2): Clear step-by-step flow with explicit if/then blocks.
#   Behavior is fully predictable in interactive, quiet, JSON, and non-TTY modes.
# - Anti-fragile (Principle 3): Works for both root and normal users, survives partial
#   failures, and maintains backward compatibility when no CHECKSUM is provided.
# - Over-protect (Principle 4 / CIAO-Lite O · Principle 20): Strong Protection Zone, safe defaults, checksum layers,
#   and cleanup on every error path. Designed to be reusable across CIAO-Lite projects.
#
# !!! DO NOT MODIFY OR SIMPLIFY THIS FUNCTION !!!
# This is the central installation orchestrator. Any change must preserve the
# checksum decision logic, atomic install step, and variable scoping for helpers.
#
# Lessons Learned (CIAO Reflection):
# 2026-06-26:
#   - Original implementation was a stub (created tmp_file then returned 0).
#     This made self-update and the core install path completely non-functional.
#   - Updated to wire the existing v2 download helpers + atomic install helper.
#   - Changed mktemp error handling to explicit if (matching the style enforced
#     in inst_perform_install_download_without_checksum).
#   - Added safe defaults for FORCE_REINSTALL and CHECKSUM.
#   - Ensured tmp_file is always cleaned on failure paths.
#   - Preserved full original defensive header and only appended this Lessons Learned section.
#
# Last reviewed: 2026-06-26
# =============================================================================

inst_perform_install() {
    # --- Safe Variable Defaults ---
    : "${GLOBAL_BIN:=/usr/local/bin}"
    : "${USER_BIN:=${HOME}/.local/bin}"
    : "${INSTALL_PATH:=${GLOBAL_BIN}/${APP_NAME}}"
    : "${FORCE_REINSTALL:=0}"
    : "${CHECKSUM:=}"
    : "${SCRIPT_URL:=}"
    : "${REMOTE_VERSION:=}"

    if [ "$(id -u)" -eq 0 ]; then
        IS_ROOT=1
        INSTALL_PATH="${GLOBAL_BIN}/${APP_NAME}"
    else
        IS_ROOT=0
        INSTALL_PATH="${USER_BIN}/${APP_NAME}"
    fi

    if [ -z "$REMOTE_VERSION" ]; then
        REMOTE_VERSION=${VERSION}
    fi

    if [ "${JSON}" -eq 0 ]; then
        out_info "Starting installation of ${APP_NAME} ${REMOTE_VERSION}..."
    fi

    if inst_is_installed && [ "${FORCE_REINSTALL}" -eq 0 ]; then
        if [ "${JSON}" -eq 1 ]; then
            out_json "out_success" "${APP_NAME} is already installed."
        else
            # Type O ensure no-op: re-run one-liner does not require --force.
            out_success "${APP_NAME} is already installed."
            out_info "Use --force only to reinstall deliberately (or run: ${APP_NAME} self-update)."
        fi
        return 0
    fi

    # Step 1: Prepare target folder
    if ! inst_perform_install_prepare_target; then
        return 1
    fi

    local tmp_file
    tmp_file=$(mktemp -t "${APP_NAME}.XXXXXX")
    if [ -z "${tmp_file}" ]; then
        if [ "${JSON}" -eq 1 ]; then
            out_json_error "Failed to create temporary file" "io_error"
        else
            out_error "Failed to create temporary file"
        fi
        return 1
    fi

    local downloaded_checksum_ok=0

    if [ -n "${CHECKSUM}" ]; then
        # Strict user/CI-provided checksum (highest security)
        if inst_perform_install_download_with_checksum "${tmp_file}"; then
            downloaded_checksum_ok=1
        else
            rm -f "${tmp_file}" 2>/dev/null || true
            return 1
        fi
    else
        # Best-effort automatic verification via .sha256 (backward compatible)
        if ! inst_perform_install_download_without_checksum "${tmp_file}"; then
            rm -f "${tmp_file}" 2>/dev/null || true
            return 1
        fi
        downloaded_checksum_ok=0
    fi

    # Step 4: Atomic move to final location + PATH update + success message
    if ! inst_perform_install_atomic_install "${tmp_file}" "${downloaded_checksum_ok}"; then
        rm -f "${tmp_file}" 2>/dev/null || true
        return 1
    fi

    return 0
}

# =============================================================================
# inst_perform_install_prepare_target() - Step 1: Target folder preparation
# =============================================================================
#
# GENERAL PURPOSE:
# Creates the correct installation directory (global or user) with proper
# permissions check.
#
# Last reviewed: 29 April 2026
# =============================================================================

inst_perform_install_prepare_target() {
    if [ "$IS_ROOT" -eq 1 ]; then
        if ! mkdir -p "${GLOBAL_BIN}" 2>/dev/null; then
            if [ "${JSON}" -eq 1 ]; then
                out_json_error "Failed to create ${GLOBAL_BIN}" "io_error"
            else
                out_error "Failed to create ${GLOBAL_BIN}"
            fi
            return 1
        fi
    else
        if ! mkdir -p "${USER_BIN}" 2>/dev/null; then
            if [ "${JSON}" -eq 1 ]; then
                out_json_error "Failed to create ${USER_BIN}" "io_error"
            else
                out_error "Failed to create ${USER_BIN}"
            fi
            return 1
        fi
    fi
    return 0
}

# =============================================================================
# inst_perform_install_download_with_checksum() - Step 2: Download with explicit CHECKSUM
# =============================================================================
#
# GENERAL PURPOSE:
# Downloads the script and verifies it against user-provided CHECKSUM (strict).
#
# PRINTF EXCEPTION (class D – tool protocol / computation pipe):
# printf '%s  %s\n' … | sha256sum -c feeds the verifier only (not product UI).
# Status/errors still go through out_* / out_json_error / out_die.
# See requirement-shell-output-requirements.md §2.1.1.
#
# Last reviewed: 2026-07-12
# =============================================================================

inst_perform_install_download_with_checksum() {
    local tmp_file="$1"

    if [ "${JSON}" -eq 0 ]; then
        out_info "Verifying download against provided CHECKSUM..."
    fi

    if command -v curl >/dev/null 2>&1; then
        curl -fsSL "${SCRIPT_URL}" -o "${tmp_file}" || {
            if [ "${JSON}" -eq 1 ]; then
                out_json_error "Download failed (curl)" "network_error"
            else
                out_error "Download failed (curl)"
            fi
            return 1
        }
    elif command -v wget >/dev/null 2>&1; then
        wget -qO "${tmp_file}" "${SCRIPT_URL}" || {
            if [ "${JSON}" -eq 1 ]; then
                out_json_error "Download failed (wget)" "network_error"
            else
                out_error "Download failed (wget)"
            fi
            return 1
        }
    else
        if [ "${JSON}" -eq 1 ]; then
            out_json_error "Neither curl nor wget found" "missing_dependency"
        else
            out_error "Neither curl nor wget found"
        fi
        return 1
    fi

    # Verify provided CHECKSUM
    if printf '%s  %s\n' "${CHECKSUM}" "${tmp_file}" | sha256sum -c - >/dev/null 2>&1; then
        if [ "${JSON}" -eq 0 ]; then
            out_success "Checksum verification passed (user-provided CHECKSUM)."
        fi
        return 0
    else
        if [ "${JSON}" -eq 1 ]; then
            out_json_error "Checksum verification failed (provided CHECKSUM does not match)" "checksum_mismatch"
        else
            out_die "Checksum verification failed. The downloaded file does not match the provided CHECKSUM. Installation aborted for security."
        fi
        return 1
    fi
}

# =============================================================================
# inst_perform_install_download_without_checksum() - Step 3: Download with automatic .sha256
# =============================================================================
#
# GENERAL PURPOSE:
# Downloads the script and attempts best-effort verification via ${SCRIPT_URL}.sha256.
# Falls back gracefully if no .sha256 file exists (backward compatible).
# Uses robust, auditable hash comparison that actually works.
#
# CIAO PRINCIPLES APPLIED:
# - Caution (Principle 1): Never trust download without verification when possible.
# - Intentional (Principle 2): Explicit HTTP code capture and clear hash comparison.
#   All error handling uses explicit if/then blocks (no || {} or compact || return).
# - Anti-fragile (Principle 3): Tolerates minor whitespace in .sha256 file.
# - Over-protect (Principle 4 / CIAO-Lite O · Principle 20): Security-critical install path now has working
#   verification and follows current coding standards.
#
# ALIGNMENT (live requirements only):
# - requirement-shell-self-management.md (install download / integrity path)
# - requirement-shell-output-requirements.md (out_* status and errors)
# - requirement-shell-modular-function-design.md (inst_* ownership, headers)
# Source comments cite only files under docs/requirements/ that exist on disk.
#
# !!! DO NOT MODIFY OR SIMPLIFY THIS FUNCTION !!!
# Designed to be reusable in other CIAO-Lite projects.
#
# Lessons Learned (CIAO Reflection):
# 2026-06-07:
#   - Fixed fundamentally broken verification: `sha256sum -c ... < "${tmp_file}"`
#     does not work as intended.
#   - Removed all `|| {}` and `|| return 1` patterns in this function to comply
#     with updated coding standard.
#   - Both curl and wget paths now use consistent, explicit error handling.
# 2026-07-12: ALIGNMENT retargeted to live docs/requirements/ files only;
#             removed citations to non-existent requirements / templates.
#
# Last reviewed: 2026-07-12
# =============================================================================

inst_perform_install_download_without_checksum() {
    local tmp_file="$1"

    if [ "${JSON}" -eq 0 ]; then
        out_info "No CHECKSUM provided → attempting automatic verification via ${SCRIPT_URL}.sha256"
    fi

    if command -v curl >/dev/null 2>&1; then
        if ! curl -fsSL "${SCRIPT_URL}" -o "${tmp_file}"; then
            if [ "${JSON}" -eq 1 ]; then
                out_json_error "Download failed (curl)" "network_error"
            else
                out_error "Download failed (curl)"
            fi
            return 1
        fi

        local sha_file
        sha_file=$(mktemp -t "${APP_NAME}.sha256.XXXXXX")
        if [ -z "${sha_file}" ]; then
            if [ "${JSON}" -eq 1 ]; then
                out_json_error "Failed to create temporary file for checksum" "io_error"
            else
                out_error "Failed to create temporary file for checksum"
            fi
            return 1
        fi

        # Capture HTTP code cleanly
        local http_code
        http_code=$(curl -fsSL -w "%{http_code}" "${SCRIPT_URL}.sha256" -o "${sha_file}" 2>/dev/null)

        if [ "${http_code}" = "200" ]; then
            # Robust verification
            local expected actual
            expected=$(tr -d '[:space:]' < "${sha_file}")
            actual=$(sha256sum "${tmp_file}" | cut -d' ' -f1)

            if [ -n "${expected}" ] && [ "${expected}" = "${actual}" ]; then
                if [ "${JSON}" -eq 0 ]; then
                    out_success "Automatic checksum verification passed (${SCRIPT_URL}.sha256)."
                fi
            else
                rm -f "${sha_file}"
                if [ "${JSON}" -eq 1 ]; then
                    out_json_error "Automatic checksum verification failed" "checksum_mismatch"
                else
                    out_die "Checksum verification failed (mismatch with ${SCRIPT_URL}.sha256). Installation aborted for security."
                fi
                return 1
            fi
        else
            if [ "${JSON}" -eq 0 ]; then
                out_warn "No .sha256 file found at ${SCRIPT_URL}.sha256 → continuing without automatic verification."
            fi
        fi
        rm -f "${sha_file}" 2>/dev/null || true

    elif command -v wget >/dev/null 2>&1; then
        if ! wget -qO "${tmp_file}" "${SCRIPT_URL}"; then
            if [ "${JSON}" -eq 1 ]; then
                out_json_error "Download failed (wget)" "network_error"
            else
                out_error "Download failed (wget)"
            fi
            return 1
        fi

        local sha_file
        sha_file=$(mktemp -t "${APP_NAME}.sha256.XXXXXX")
        if [ -z "${sha_file}" ]; then
            if [ "${JSON}" -eq 1 ]; then
                out_json_error "Failed to create temporary file for checksum" "io_error"
            else
                out_error "Failed to create temporary file for checksum"
            fi
            return 1
        fi

        if wget -q --server-response "${SCRIPT_URL}.sha256" -O "${sha_file}" 2>&1 | grep -q "HTTP/1.1 200"; then
            local expected actual
            expected=$(tr -d '[:space:]' < "${sha_file}")
            actual=$(sha256sum "${tmp_file}" | cut -d' ' -f1)

            if [ -n "${expected}" ] && [ "${expected}" = "${actual}" ]; then
                if [ "${JSON}" -eq 0 ]; then
                    out_success "Automatic checksum verification passed."
                fi
            else
                rm -f "${sha_file}"
                if [ "${JSON}" -eq 1 ]; then
                    out_json_error "Automatic checksum verification failed" "checksum_mismatch"
                else
                    out_die "Checksum verification failed. Installation aborted for security."
                fi
                return 1
            fi
        else
            if [ "${JSON}" -eq 0 ]; then
                out_warn "No .sha256 file found → continuing without automatic verification."
            fi
        fi
        rm -f "${sha_file}" 2>/dev/null || true

    else
        if [ "${JSON}" -eq 1 ]; then
            out_json_error "Neither curl nor wget found" "missing_dependency"
        else
            out_error "Neither curl nor wget found"
        fi
        return 1
    fi

    return 0
}

# =============================================================================
# inst_perform_install_atomic_install() - Step 4: Atomic copy to target location
# =============================================================================
#
# GENERAL PURPOSE:
# Sets dest mode 0755 (not chmod +x) and atomically moves it to the final
# INSTALL_PATH. Also handles PATH addition for user installs and out_success output.
#
# Last reviewed: 29 April 2026
# =============================================================================

inst_perform_install_atomic_install() {
    local tmp_file="$1"
    local downloaded_checksum_ok="$2"

    chmod 0755 "${tmp_file}" || {
        rm -f "${tmp_file}"
        if [ "${JSON}" -eq 1 ]; then
            out_json_error "Cannot set dest mode 0755 on staging file" "io_error"
        else
            out_error "Cannot set dest mode 0755 on staging file"
        fi
        return 1
    }

    rm -f "${INSTALL_PATH}" 2>/dev/null
    if ! mv "${tmp_file}" "${INSTALL_PATH}" 2>/dev/null; then
        rm -f "${tmp_file}"
        if [ "${JSON}" -eq 1 ]; then
            out_json_error "Failed to move to ${INSTALL_PATH}" "io_error"
        else
            out_error "Failed to move to ${INSTALL_PATH}"
        fi
        return 1
    fi

    # Add ~/.local/bin to PATH for normal user installs
    if [ "$IS_ROOT" -eq 0 ]; then
        path_add_shell
    fi
    
    if [ "${JSON}" -eq 1 ]; then
        out_json "out_success" "${APP_NAME} ${REMOTE_VERSION} successfully installed to ${INSTALL_PATH}" "path" "${INSTALL_PATH}"
    else
        out_success "${APP_NAME} ${REMOTE_VERSION} successfully installed to ${INSTALL_PATH}"
        if [ "${downloaded_checksum_ok}" -eq 1 ]; then
            out_success "✓ Download was cryptographically verified."
        fi
    fi
    return 0
}

# =============================================================================
# inst_maybe_install() - Friendly installation prompt
# =============================================================================
#
# Respects both --quiet and --json modes.
# In JSON mode we skip the interactive prompt entirely.
# Now uses prompt_yes_no() as single source of truth for confirmation.
#
# !!! DO NOT MODIFY OR SIMPLIFY !!!
# Designed to be reusable in other projects.
#
# Last reviewed: 29 April 2026
# =============================================================================

inst_maybe_install() {
    : "${QUIET:=0}"
    : "${JSON:=0}"
    : "${FORCE_REINSTALL:=0}"
    
    if inst_is_installed && [ "${FORCE_REINSTALL}" -eq 0 ]; then
        return 0
    fi
    # In JSON mode or quiet mode we do not show interactive prompts
    if [ "${JSON}" -eq 1 ] || [ "${QUIET}" -eq 1 ]; then
        return 0
    fi
    out_empty_line
    out_plain "Note: '${APP_NAME}' is not installed yet."
    out_plain "     Version: ${VERSION}"
    out_empty_line
    out_plain "Recommended installation command:"
    out_empty_line

    if [ "$IS_ROOT" -eq 1 ]; then
        out_plain "     sudo curl -fsSL ${SCRIPT_URL} | sudo ${SH}"
    else
        out_plain "     curl -fsSL ${SCRIPT_URL} | ${SH}"
    fi
    out_empty_line

    local should_install=false

    if [ -t 0 ] && [ -t 1 ]; then
        # Use single source of truth for the yes/no prompt
        # WARNING — do-not-capture-read (**PP-A-22**): MUST NOT _y=$(prompt_yes_no …)
        if prompt_yes_no "Install ${APP_NAME} ${VERSION} now?"; then
            should_install=true
        else
            should_install=false
            out_plain "Installation skipped by user."
            return 0 
        fi
    else
        out_plain "Non-interactive mode detected → installing automatically..."
        should_install=true
    fi

    if [ "$should_install" = "true" ]; then
        inst_perform_install
        exit 0
    fi
}

# =============================================================================
# inst_self_update() - Perform atomic self-update to latest version
# =============================================================================
#
# GENERAL PURPOSE:
# Orchestrates self-update for the installed ${APP_NAME} binary.
# Fetches the remote VERSION string, compares it with the locally installed
# version, and (if different or --force) delegates to inst_perform_install
# with FORCE_REINSTALL=1. Designed to be safe, idempotent-friendly, and
# respectful of the current installation type (user vs global).
#
# CIAO PRINCIPLES APPLIED:
# - Caution (Principle 1): Never downgrades without explicit FORCE; always
#   verifies remote version before proceeding; uses centralized output.
# - Intentional (Principle 2): Clear separation between version check and
#   actual install; explicit variable handling and error paths.
# - Anti-fragile (Principle 3): Works for both root and normal users;
#   survives missing SCRIPT_URL (graceful error) and network failures.
# - Over-protect (Principle 4 / CIAO-Lite O · Principle 20): Full CIAO header, safe defaults, Protection
#   Zone comment, and Lessons Learned traceability. Reusable pattern for
#   other CIAO-Lite self-managed tools.
#
# ALIGNMENT (live requirements only):
# - requirement-shell-self-management.md
# - requirement-shell-cli-interface.md
# - requirement-shell-output-requirements.md
# - requirement-shell-idempotency.md
#
# !!! DO NOT MODIFY OR SIMPLIFY THIS FUNCTION !!!
# This is the canonical self-update entry point. Any change must preserve
# the REMOTE_VERSION visibility contract with inst_perform_install and
# the centralized output discipline.
#
# Lessons Learned (CIAO Reflection):
# 2026-06-26: Original implementation was a stub. Updated to call the v2
#             inst_perform_install path with checksum support.
# 2026-06-26 (correction): Removed accidental `local` on REMOTE_VERSION
#             (was invisible to inst_perform_install). Added safe default
#             for SCRIPT_URL and explicit comment about distribution URL
#             requirement. No hard-coded project-specific values introduced.
#
# Last reviewed: 2026-06-26
# =============================================================================

inst_self_update() {
    # --- Safe Variable Defaults ---
    : "${APP_NAME:=selfmanaged}"
    : "${JSON:=0}"
    : "${QUIET:=0}"
    : "${FORCE:=0}"
    : "${FORCE_REINSTALL:=0}"
    : "${SCRIPT_URL:=}"

    # Align force aliases (CLI --force sets both)
    if [ "${FORCE}" -eq 1 ]; then
        FORCE_REINSTALL=1
    fi

    # NOTE (Distribution URL requirement):
    # For reliable self-update after installation, SCRIPT_URL must be set
    # to the canonical public location of the install script (e.g. raw GitHub
    # URL or equivalent). This value is intentionally left empty by default
    # to avoid hard-coding any project-specific URL. Distributors or
    # advanced users should export SCRIPT_URL before running self-update,
    # or implement URL embedding during the atomic install step.
    # Fetch remote VERSION= first. Proceeding start INFO names both versions;
    # do not print a version-less start line.

    REMOTE_VERSION=$(curl -fsSL "${SCRIPT_URL}" 2>/dev/null | grep '^VERSION="' | cut -d'"' -f2 || echo "")

    if [ -z "$REMOTE_VERSION" ]; then
        if [ "${JSON}" -eq 1 ]; then
            out_json_error "Failed to fetch latest version" "network_error"
        else
            out_error "Failed to fetch latest version (SCRIPT_URL may be unset or unreachable)"
        fi
        return 1
    fi

    local local_version
    local_version=$(inst_get_version)

    if [ "$local_version" = "$REMOTE_VERSION" ] && [ "${FORCE_REINSTALL}" -eq 0 ]; then
        if [ "${JSON}" -eq 1 ]; then
            out_json "out_success" "Already running the latest version (${REMOTE_VERSION})."
        else
            out_success "Already running the latest version (${REMOTE_VERSION})."
        fi
        return 0
    fi

    # No silent downgrade: remote older than local requires --force
    # (requirement-shell-self-management.md)
    if [ "$local_version" != "not installed" ] && \
       [ "$local_version" != "unknown" ] && \
       ver_gt "$local_version" "$REMOTE_VERSION" && \
       [ "${FORCE_REINSTALL}" -eq 0 ]; then
        if [ "${JSON}" -eq 1 ]; then
            out_json_error "Refusing downgrade from ${local_version} to ${REMOTE_VERSION} (use --force)" "downgrade_blocked"
        else
            out_error "Refusing silent downgrade: local ${local_version} is newer than remote ${REMOTE_VERSION}."
            out_info "Re-run with --force to reinstall/downgrade deliberately."
        fi
        return 1
    fi

    if [ "${JSON}" -eq 0 ]; then
        out_info "Starting the self-update of ${APP_NAME}(${local_version}) to new version:${REMOTE_VERSION}..."
    fi

    if [ "$local_version" != "$REMOTE_VERSION" ] && [ "${JSON}" -eq 0 ]; then
        if ver_gt "$REMOTE_VERSION" "$local_version" 2>/dev/null || [ "$local_version" = "not installed" ]; then
            out_info "Updating from ${local_version} → ${REMOTE_VERSION}"
        else
            out_warn "Force reinstall/downgrade: ${local_version} → ${REMOTE_VERSION}"
        fi
    fi

    FORCE_REINSTALL=1
    inst_perform_install
}

# =============================================================================
# inst_self_uninstall() - Main orchestrator for uninstallation
# =============================================================================
#
# GENERAL PURPOSE:
# Removes the installed git-sync binary (global or user) and optionally
# cleans up PATH entries.
#
# Respects --force, --quiet, and --json.
# Works for both root and user installations.
#
# DESIGN:
# Split into three clear steps for readability while preserving original
# behavior and safety.
#
# Last reviewed: 29 April 2026
# =============================================================================

inst_self_uninstall() {
    # Align force aliases (CLI --force)
    : "${FORCE:=0}"
    : "${FORCE_REINSTALL:=0}"
    if [ "${FORCE}" -eq 1 ]; then
        FORCE_REINSTALL=1
    fi

    if [ "${JSON}" -eq 0 ]; then
        out_info "Starting self-uninstall of ${APP_NAME}..."
    fi

    # Step 1: Determine which installation to remove
    local bin_path
    bin_path=$(inst_self_uninstall_determine_bin)
    if [ -z "$bin_path" ]; then
        if [ "${JSON}" -eq 1 ]; then
            out_json "out_success" "${APP_NAME} is not installed. Nothing to uninstall."
        else
            out_warn "${APP_NAME} is not installed. Nothing to uninstall."
        fi
        return 0
    fi

    # Step 2: Confirm (if needed) and perform removal
    if ! inst_self_uninstall_confirm_and_remove "$bin_path"; then
        return 1
    fi

    # Step 3: Clean up PATH entries (user installs only)
    inst_self_uninstall_cleanup_path

    if [ "${JSON}" -eq 1 ]; then
        out_json "out_success" "${APP_NAME} has been uninstalled."
    else
        out_success "${APP_NAME} has been uninstalled."
    fi
    return 0
}

# =============================================================================
# inst_self_uninstall_determine_bin() - Step 1: Determine which installation to remove
# =============================================================================
#
# GENERAL PURPOSE:
# Decides the correct binary path to remove based on current user,
# FORCE_GLOBAL, and actual file presence.
#
# Returns the full path to remove, or empty string if nothing to uninstall.
#
# PRINTF EXCEPTION (class B – function return-via-stdout):
# Final printf '%s' "$bin_path" is a data return for $(…) capture by the
# uninstall orchestrator — not a product user message. User-facing text in
# this helper uses out_warn. Callers must capture the path; do not treat
# this printf as a substitute for out_*.
# See requirement-shell-output-requirements.md §2.1.1.
#
# CRITICAL: Respects root vs user logic exactly as before.
#
# Last reviewed: 2026-07-12
# =============================================================================

inst_self_uninstall_determine_bin() {
    local bin_path=""

    if [ "$(id -u)" -eq 0 ] || [ "${FORCE_GLOBAL:-0}" -eq 1 ]; then
        # Global (root) uninstall
        if [ -f "${GLOBAL_BIN}/${APP_NAME}" ]; then
            bin_path="${GLOBAL_BIN}/${APP_NAME}"
        fi
    else
        # User uninstall - prefer local, fallback to global
        if [ -f "${USER_BIN}/${APP_NAME}" ]; then
            bin_path="${USER_BIN}/${APP_NAME}"
        elif [ -f "${GLOBAL_BIN}/${APP_NAME}" ]; then
            bin_path="${GLOBAL_BIN}/${APP_NAME}"
            if [ "${JSON}" -eq 0 ]; then
                out_warn "Global installation found. Removing it (you may need sudo next time)."
            fi
        fi
    fi

    printf '%s' "$bin_path"
}

# =============================================================================
# inst_self_uninstall_confirm_and_remove() - Step 2: Confirm and remove binary
# =============================================================================
#
# GENERAL PURPOSE:
# Handles confirmation (unless --force) and actual file removal.
# Uses prompt_yes_no() as SINGLE SOURCE OF TRUTH.
#
# Returns 0 on out_success, non-zero on failure/cancel.
#
# Last reviewed: 28 April 2026
# =============================================================================

inst_self_uninstall_confirm_and_remove() {
    local bin_path="$1"

    # Confirm before removal (unless --force / FORCE_REINSTALL or non-interactive)
    if [ "${FORCE_REINSTALL:-0}" -eq 0 ] && [ "${FORCE:-0}" -eq 0 ]; then
        # WARNING — do-not-capture-read (**PP-A-22**): MUST NOT _y=$(prompt_yes_no …)
        if prompt_yes_no "This will remove: ${bin_path}"; then
            :  # confirmed
        else
            if [ "${JSON}" -eq 1 ]; then
                out_json "out_success" "Uninstall cancelled by user."
            else
                out_plain "Uninstall cancelled by user."
            fi
            return 1
        fi
    fi

    # Remove the binary
    if rm -f "$bin_path" 2>/dev/null; then
        return 0
    else
        if [ "${JSON}" -eq 1 ]; then
            out_json_error "Failed to remove ${bin_path} (permission denied?)" "permission_denied"
        else
            out_error "Failed to remove ${bin_path} (permission denied?)"
        fi
        return 1
    fi
}

# =============================================================================
# inst_self_uninstall_cleanup_path() - Step 3: Clean up PATH entries
# =============================================================================
#
# GENERAL PURPOSE:
# Removes installer-added PATH entries from shell config files
# (bash, zsh, fish) for user-level installations **only if** ~/.local/bin
# is empty or does not exist.
#
# SAFETY RULE (new):
# If ~/.local/bin still contains other files (other tools, scripts, etc.),
# we deliberately keep the PATH entry to avoid breaking the user's environment.
# This follows CIAO-Lite "Caution" and "Anti-fragile" principles.
#
# Last reviewed: 28 April 2026
# =============================================================================

inst_self_uninstall_cleanup_path() {
    # Only attempt cleanup for non-root installs
    if [ "$(id -u)" -eq 0 ]; then
        return 0
    fi

    local bin_dir="${HOME}/.local/bin"
    local should_clean_path=1

    # === SAFETY CHECK: Only clean PATH if ~/.local/bin is empty ===
    if [ -d "$bin_dir" ]; then
        if [ -n "$(ls -A "$bin_dir" 2>/dev/null)" ]; then
            # Directory exists and is not empty → keep PATH for other tools
            should_clean_path=0
            if [ "${JSON}" -eq 0 ]; then
                out_warn "Keeping ~/.local/bin in PATH because it still contains files."
            fi
        fi
    fi

    if [ "$should_clean_path" -eq 0 ]; then
        return 0
    fi

    # Directory is empty or missing → safe to remove our PATH entries
    local cleaned=0

    for config in "${HOME}/.bashrc" "${HOME}/.zshrc" "${HOME}/.config/fish/config.fish"; do
        if [ -f "$config" ]; then
            if sed -i.bak '/# Added by .* installer/d' "$config" 2>/dev/null && \
               sed -i.bak '/\.local\/bin:.*PATH/d' "$config" 2>/dev/null; then
                cleaned=1
            fi
            rm -f "${config}.bak" 2>/dev/null || true
        fi
    done

    if [ "$cleaned" -eq 1 ] && [ "${JSON}" -eq 0 ]; then
        out_plain "→ Cleaned ${APP_NAME} PATH entries from shell config files"
        out_plain "→ You may want to restart your terminal"
    fi
}

# =============================================================================
# inst_is_installed() - Robust installation check
# =============================================================================
#
# GENERAL PURPOSE:
# Checks whether the program is already installed, supporting both root
# and normal user installations with safe fallbacks.
#
# Please don't modify this code for root-only installed
# You can check [ "$(id -u)" -eq 0 ] before calling / excuting 
#   this function
#
# !!! DO NOT MODIFY OR SIMPLIFY THIS FUNCTION !!!
# Designed to be reusable in other projects.
#
# Last reviewed: 29 April 2026
# =============================================================================

inst_is_installed() {
    version=$(inst_get_version)
    if [ "${version}" = "not installed"  ]; then 
        return 1
    else
        return 0
    fi
}

# =============================================================================
# inst_get_version() - Extract version from installed binary
# =============================================================================
#
# GENERAL PURPOSE:
# Safely reads the VERSION constant from the installed script.
# Used by --version-check and --self-update.
#
# Safe Variable Defaults
#
# !!! DO NOT MODIFY OR SIMPLIFY THIS FUNCTION !!!
# Designed to be reusable in other projects.
#
# CRITICAL WARNING - VERSION EXTRACTION IS ESSENTIAL FOR SELF-UPDATE:
# Knowing the exact installed version is not optional — it is the foundation
# of safe self-update and version-check logic.
#
# Without a reliable inst_get_version(), self-update cannot properly
# compare local version against remote, leading to:
# - Unnecessary re-downloads
# - Failed updates
# - Silent failures
# - Potential downgrade or broken installation
#
# AI assistants frequently fail to respect this importance. They often
# overlook, simplify, or remove version extraction logic because they
# consider it "minor" or try to replace the entire self-update flow with
# a simpler approach. This always breaks the self-update mechanism.
#
# This function is battle-field tested and intentionally simple/robust
# (grep + cut on the VERSION= line). Any attempt to rewrite or bypass it
# risks destroying the self-update safety net.
#
# We must intentionally preserve and reuse this exact function instead of
# replacing it. Respecting version awareness is a core part of CIAO
# Caution and Anti-fragility.
#
# PRINTF/ECHO EXCEPTION (class B – function return-via-stdout):
# echo "unknown" / echo "not installed" / grep|cut pipeline output are data
# returns for $(inst_get_version) capture — not product banners. Callers
# pass the string into out_* / out_json when displaying to the user.
# See requirement-shell-output-requirements.md §2.1.1.
#
# Last reviewed: 2026-07-12
# =============================================================================

inst_get_version() {
    # --- Safe Variable Defaults ----
    # Defensive defaults - never assume globals are set
    : "${APP_NAME:=app}"
    : "${IS_ROOT:=0}"
    : "${GLOBAL_BIN:=/usr/local/bin}"
    : "${USER_BIN:=${HOME}/.local/bin}"

    local bin_path
    if [ "$IS_ROOT" -eq 1 ] || [ -x "${GLOBAL_BIN}/${APP_NAME}" ]; then
        bin_path="${GLOBAL_BIN}/${APP_NAME}"
    else
        bin_path="${USER_BIN}/${APP_NAME}"
    fi

    if [ -x "$bin_path" ]; then
        grep '^VERSION="' "$bin_path" 2>/dev/null | cut -d'"' -f2 || echo "unknown"
    else
        echo "not installed"
    fi
}

# =============================================================================
# ver_gt() - Pure POSIX semantic version comparison
# =============================================================================
#
# GENERAL PURPOSE:
# Returns 0 (true) if ver1 > ver2, otherwise returns 1 (false).
# Used by ver_check() and inst_self_update() to prevent incorrect downgrades.
#
# Safe Variable Defaults
# Respects CIAO zero-dependency rule — no external tools (no sort -V).
#
# CRITICAL DESIGN CHOICE:
# This function was added because previous AI suggestions using `sort -V`
# were not portable enough for harsh environments (Alpine ash, busybox,
# minimal containers, Git Bash, etc.).
#
# !!! DO NOT MODIFY OR SIMPLIFY THIS FUNCTION !!!
# Past AI assistants have repeatedly tried to replace this with:
#   - `sort -V` one-liners
#   - Inline string comparisons
#   - "Cleaner" but less robust logic
#
# Any such change re-introduces downgrade bugs and breaks portability.
# This function must remain pure POSIX and self-contained.
#
# AI assistants are explicitly required to:
# - Never remove or inline this function
# - Always use it for all version comparisons in grokrec
# - Preserve all defensive comments
# - Study the test script provided by the user before suggesting changes
#
# This is part of the battle-field-tested defensive layer.
#
# Last reviewed: 29 April 2026
# =============================================================================

ver_gt() {
    # --- Safe Variable Defaults ----
    v1=$1
    v2=$2

    while [ -n "$v1" ] || [ -n "$v2" ]; do
        p1=${v1%%.*}
        p2=${v2%%.*}

        [ -z "$p1" ] && p1=0
        [ -z "$p2" ] && p2=0

        if [ "$p1" -gt "$p2" ]; then
            return 0
        fi
        if [ "$p1" -lt "$p2" ]; then
            return 1
        fi

        if [ "$v1" = "${v1#*.}" ]; then
            v1=""
        else
            v1=${v1#*.}
        fi

        if [ "$v2" = "${v2#*.}" ]; then
            v2=""
        else
            v2=${v2#*.}
        fi
    done

    return 1    # versions are equal
}

# =============================================================================
# ver_check() - Check for newer version from remote source
# =============================================================================
#
# GENERAL PURPOSE:
# Compares the locally installed version of ${APP_NAME} against the remote
# version available at SCRIPT_URL. Supports both human-readable output and
# clean JSON mode. Used by the `version-check` command and as a helper for
# self-update decision logic.
#
# CIAO PRINCIPLES APPLIED:
# - Caution (Principle 1): Never assumes SCRIPT_URL is set; graceful failure
#   with actionable error when remote version cannot be fetched.
# - Intentional (Principle 2): Explicit safe defaults, clear separation of
#   version fetching vs comparison, and consistent behavior in JSON/quiet modes.
# - Anti-fragile (Principle 3): Works whether the tool is installed globally,
#   per-user, or not yet installed; survives network or parsing failures.
# - Over-protect (Principle 4 / CIAO-Lite O · Principle 20): Full defensive header, Protection Zone,
#   Lessons Learned traceability, and strict avoidance of hard-coded
#   project-specific URLs or repository paths.
#
# ALIGNMENT (live requirements only):
# - requirement-shell-self-management.md
# - requirement-shell-cli-interface.md
# - requirement-shell-output-requirements.md
#
# !!! DO NOT MODIFY OR SIMPLIFY THIS FUNCTION !!!
# This function is the single source of truth for remote version comparison.
# Any change must preserve the SCRIPT_URL handling contract and the exact
# JSON output shape expected by consumers.
#
# Lessons Learned (CIAO Reflection):
# 2026-06-26: Original version contained a hardcoded project-specific default
#             URL pointing to an unrelated repository (porting artifact).
#             Corrected to empty safe default + explicit comment. Removed
#             all hard-coded distribution details to comply with generalization
#             and hardcoding-prevention rules.
#
# Last reviewed: 2026-06-26
# =============================================================================

ver_check() {
    # --- Safe Variable Defaults ----
    # Defensive defaults - never assume globals are set
    : "${APP_NAME:=selfmanaged}"
    : "${JSON:=0}"
    : "${QUIET:=0}"
    : "${SCRIPT_URL:=}"

    # NOTE (Distribution URL requirement):
    # For version-check and self-update to work after installation,
    # SCRIPT_URL must be set to the canonical public location of the
    # install script. This value is intentionally left empty by default
    # to avoid embedding any project-specific URL. Set SCRIPT_URL in the
    # environment before running `version-check` or `self-update`, or
    # implement URL embedding during atomic installation.

    # Fetch remote version
    REMOTE_VERSION=$(curl -fsSL "${SCRIPT_URL}" 2>/dev/null | grep '^VERSION="' | cut -d'"' -f2 || echo "")

    if [ -z "$REMOTE_VERSION" ]; then
        if [ "${JSON}" -eq 1 ]; then
            out_json_error "Failed to fetch remote version" "network_error"
        else
            out_error "Failed to fetch remote version (SCRIPT_URL may be unset or unreachable)"
        fi
        return 1
    fi

    local local_version
    local_version=$(inst_get_version)

    if [ "${JSON}" -eq 1 ]; then
        out_json "ver_check" \
            "local_version" "$local_version" \
            "remote_version" "$REMOTE_VERSION" \
            "is_latest" "$( [ "$local_version" = "$REMOTE_VERSION" ] && echo "true" || \
                           (ver_gt "$local_version" "$REMOTE_VERSION" && echo "true" || echo "false") )"
    else
        if [ "${QUIET}" -eq 0 ]; then
            out_info "Checking latest version of ${APP_NAME}..."
            out_plain "Local version : ${local_version}"
            out_plain "Latest version: ${REMOTE_VERSION}"
            out_empty_line

            if [ "$local_version" = "$REMOTE_VERSION" ]; then
                out_success "You are running the latest version."
            elif ver_gt "$local_version" "$REMOTE_VERSION"; then
                out_success "You are running a newer development version (${local_version} > ${REMOTE_VERSION})"
            elif [ "$local_version" = "not installed" ]; then
                out_warn "${APP_NAME} is not installed yet."
            else
                out_warn "A newer version is available (${REMOTE_VERSION})"
            fi
        fi
    fi
}


# =============================================================================
# path_add_bashrc() - Add ~/.local/bin to ~/.bashrc
# =============================================================================
#
# GENERAL PURPOSE:
# Appends the PATH export to ~/.bashrc only if not already present.
#
# Returns 0 if added (or was already present), 1 if file missing or failed.
#
# PRINTF EXCEPTION (class C – file I/O redirect):
# printf … >> "$bashrc" writes shell config content to a file, not product
# stdout/stderr. User-visible “→ Added …” lines use out_plain.
# See requirement-shell-output-requirements.md §2.1.1.
#
# Last reviewed: 2026-07-12
# =============================================================================

path_add_bashrc() {
    local bashrc="${HOME}/.bashrc"
    if [ ! -f "$bashrc" ]; then
        return 1
    fi

    if ! grep -qF 'export PATH="$HOME/.local/bin:$PATH"' "$bashrc" 2>/dev/null; then
        printf "\n# Added by %s installer (%s)\n" "$APP_NAME" "$VERSION" >> "$bashrc"
        printf 'export PATH="$HOME/.local/bin:$PATH"\n' >> "$bashrc"
        if [ "${JSON}" -eq 0 ]; then
            out_plain "→ Added ~/.local/bin to PATH for bash"
        fi
        return 0
    fi
    return 1  # already present
}

# =============================================================================
# path_add_zshrc() - Add ~/.local/bin to ~/.zshrc
# =============================================================================
#
# GENERAL PURPOSE:
# Appends the PATH export to ~/.zshrc only if not already present.
#
# Returns 0 if added (or was already present), 1 if file missing or failed.
#
# PRINTF EXCEPTION (class C – file I/O redirect):
# printf … >> "$zshrc" writes shell config content to a file, not product
# stdout/stderr. User-visible “→ Added …” lines use out_plain.
# See requirement-shell-output-requirements.md §2.1.1.
#
# Last reviewed: 2026-07-12
# =============================================================================

path_add_zshrc() {
    local zshrc="${HOME}/.zshrc"
    if [ ! -f "$zshrc" ]; then
        return 1
    fi

    if ! grep -qF 'export PATH="$HOME/.local/bin:$PATH"' "$zshrc" 2>/dev/null; then
        printf "\n# Added by %s installer (%s)\n" "$APP_NAME" "$VERSION" >> "$zshrc"
        printf 'export PATH="$HOME/.local/bin:$PATH"\n' >> "$zshrc"
        if [ "${JSON}" -eq 0 ]; then
            out_plain "→ Added ~/.local/bin to PATH for zsh"
        fi
        return 0
    fi
    return 1  # already present
}

# =============================================================================
# path_add_fish() - Add ~/.local/bin to Fish config
# =============================================================================
#
# GENERAL PURPOSE:
# Creates ~/.config/fish directory if needed and appends the PATH setting
# to config.fish only if not already present.
#
# Returns 0 if added (or was already present), 1 if failed.
#
# PRINTF EXCEPTION (class C – file I/O redirect):
# printf … >> "$fish_config" writes shell config content to a file, not
# product stdout/stderr. User-visible “→ Added …” lines use out_plain.
# See requirement-shell-output-requirements.md §2.1.1.
#
# Last reviewed: 2026-07-12
# =============================================================================

path_add_fish() {
    local fish_config="${HOME}/.config/fish/config.fish"

    # Ensure directory exists
    if [ ! -d "${HOME}/.config/fish" ] && ! mkdir -p "${HOME}/.config/fish" 2>/dev/null; then
        return 1
    fi

    if [ -f "$fish_config" ] && grep -qF 'set -gx PATH $HOME/.local/bin $PATH' "$fish_config" 2>/dev/null; then
        return 1  # already present
    fi

    printf "\n# Added by %s installer (%s)\n" "$APP_NAME" "$VERSION" >> "$fish_config"
    printf 'set -gx PATH $HOME/.local/bin $PATH\n' >> "$fish_config"

    if [ "${JSON}" -eq 0 ]; then
        out_plain "→ Added ~/.local/bin to PATH for fish shell"
    fi
    return 0
}

# =============================================================================
# path_add_shell() - Main orchestrator: Add ~/.local/bin to shell PATHs
# =============================================================================
#
# GENERAL PURPOSE:
# Adds ~/.local/bin to bash, zsh, and fish configuration files if not already
# present. Acts as a thin orchestrator after splitting the long function.
#
# Respects --json mode (silent in JSON).
#
# Last reviewed: 29 April 2026
# =============================================================================

path_add_shell() {
    local added=0
    local shell_config="N/A"

    # Bash
    if path_add_bashrc; then
        added=1
        shell_config="${HOME}/.bashrc"
    fi

    # Zsh
    if path_add_zshrc; then
        added=1
        if [ "$shell_config" = "N/A" ]; then
            shell_config="${HOME}/.zshrc"
        else
            shell_config="${shell_config} ${HOME}/.zshrc"
        fi
    fi

    # Fish
    if path_add_fish; then
        added=1
        if [ "$shell_config" = "N/A" ]; then
            shell_config="${HOME}/.config/fish/config.fish"
        else
            shell_config="${shell_config} ${HOME}/.config/fish/config.fish"
        fi
    fi

    if [ "$added" -eq 1 ] && [ "${JSON}" -eq 0 ]; then
        out_plain "→ Restart your terminal or run: source ${shell_config}"
    fi
}

# =============================================================================
# util_get_install_bin_path() - Return the correct binary path to operate on
# =============================================================================
#
# GENERAL PURPOSE:
# Returns the full path to the ${APP_NAME} binary that should be used for
# install/uninstall/update operations.
#
# Safe Variable Defaults
#
# Respects --force and --json.
# Respects root vs non-root isolation, --force-user, --force-global.
#
# For non-root: prefers ~/.local/bin, falls back to /usr/local/bin if present.
# For root: always uses /usr/local/bin.
#
# !!! DO NOT MODIFY OR SIMPLIFY THIS FUNCTION !!!
# This is a minimal defensive helper to reduce repetition while preserving
# the strict root/non-root separation that has been battle-field tested.
#
# CRITICAL: Any change here must maintain zero cross-contamination between
# user and global installations.
#
# PRINTF EXCEPTION (class B – function return-via-stdout):
# Final printf '%s' "${bin_path}" is a data return for $(…) capture — not
# product UI. Warnings use out_warn. Callers must capture the path.
# See requirement-shell-output-requirements.md §2.1.1.
#
# Last reviewed: 2026-07-12
# =============================================================================

util_get_install_bin_path() {
    # --- Safe Variable Defaults ----
    # Defensive defaults - never assume globals are set
    : "${APP_NAME:=app}"
    : "${JSON:=0}"
    : "${QUIET:=0}"
    : "${FORCE_USER:=0}"
    : "${FORCE_GLOBAL:=0}"
    : "${GLOBAL_BIN:=/usr/local/bin}"
    : "${USER_BIN:=${HOME}/.local/bin}"
    : "${HOME:="/tmp"}"

    local bin_path=""

    # Explicit force flags take precedence
    if [ "${FORCE_USER}" -eq 1 ]; then
        bin_path="${USER_BIN}/${APP_NAME}"
    elif [ "${FORCE_GLOBAL}" -eq 1 ] || [ "$(id -u)" -eq 0 ]; then
        bin_path="${GLOBAL_BIN}/${APP_NAME}"
    else
        # Normal non-root behavior: prefer user-local, fallback to global
        if [ -f "${USER_BIN}/${APP_NAME}" ]; then
            bin_path="${USER_BIN}/${APP_NAME}"
        elif [ -f "${GLOBAL_BIN}/${APP_NAME}" ]; then
            bin_path="${GLOBAL_BIN}/${APP_NAME}"
            if [ "${JSON}" -eq 0 ] && [ "${QUIET}" -eq 0 ]; then
                out_warn "Global installation found. Operating on it (you may need sudo for uninstall)."
            fi
        else
            bin_path="${USER_BIN}/${APP_NAME}"
        fi
    fi

    printf '%s' "${bin_path}"
}

# =============================================================================
# util_backup() - Create dated backup before any modification
# =============================================================================
#
# GENERAL PURPOSE:
# Creates a dated backup of important RuoYi configuration files or directories
# before destructive or modifying operations (rm -rf, sed, DB config changes).
#
# This implements CIAO Principle 12 (Right Backup & Restore Strategy).
#
# ────────────────────────────────────────────────
# CIAO PRINCIPLES APPLIED (v2.10.2)
# ────────────────────────────────────────────────
# Principle 1  (Caution)               - Safe path validation
# Principle 2  (Intentional Verbosity) - Full header + comments
# Principle 3  (Anti-fragile)          - Survives missing files gracefully
# Principle 8 (Reusable)              - Designed for reuse in other projects
# Principle 11 (Safe Temporary Files)  - Uses mktemp where needed
# Principle 12 (Backup Strategy)       - Dated backup with counter
#
# CRITICAL DEFENSIVE RULES:
# - Never modify files without creating backup first.
# - Refuse dangerous paths (/, $HOME, empty).
# - Backup name format: <name>.YYYYMMDD-N.bak
# - All messages go through out_text helpers only.
#
# !!! DO NOT MODIFY OR SIMPLIFY THIS FUNCTION !!!
# This is the central backup mechanism. Any change must preserve dated backup
# naming and safety checks to prevent accidental data loss.
#
# Last reviewed: 29 April 2026
# =============================================================================

util_backup() {
    # --- Safe Variable Defaults ---
    : "${APP_NAME:=app}"
    : "${PROJECT_NAME:=${APP_NAME}-demo}"
    : "${PROJECT_DIR:=${HOME}/${PROJECT_NAME}}"
    : "${JSON:=0}"
    : "${QUIET:=0}"

    local target="$1"
    local reason="${2:-pre-change}"

    if [ -z "$target" ]; then
        return 1
    fi

    # Safety check
    if [ "$target" = "/" ] || [ "$target" = "${HOME}" ] || [ -z "$target" ]; then
        out_warn "Refusing to backup dangerous path: $target"
        return 1
    fi

    local timestamp
    timestamp=$(date +%Y%m%d)
    local counter=1
    local backup_path

    if [ -d "$target" ]; then
        backup_path="${target}.${timestamp}-${counter}.bak"
        while [ -e "$backup_path" ]; do
            counter=$((counter + 1))
            backup_path="${target}.${timestamp}-${counter}.bak"
        done
        cp -a "$target" "$backup_path" 2>/dev/null && \
            out_info "Backup created: $backup_path (reason: $reason)" || \
            out_warn "Failed to create backup of directory $target"
    elif [ -f "$target" ]; then
        backup_path="${target}.${timestamp}-${counter}.bak"
        while [ -e "$backup_path" ]; do
            counter=$((counter + 1))
            backup_path="${target}.${timestamp}-${counter}.bak"
        done
        cp "$target" "$backup_path" 2>/dev/null && \
            out_info "Backup created: $backup_path (reason: $reason)" || \
            out_warn "Failed to create backup of file $target"
    fi
}

# =============================================================================
# util_resolve_storage() - Storage resolver
# =============================================================================
#
# GENERAL PURPOSE:
# Returns the best available volatile storage directory for prompt files.
# Prefers /dev/shm (fastest, in-memory) → /tmp → fallback to XDG_CACHE_HOME.
# All paths include ${USERNAME} to isolate per-user storage.
#
# Safe Variable Defaults
#
# CIAO PRINCIPLES APPLIED:
# - Caution: Must work correctly when the same computer is used by multiple
#   different users (normal user, sudo, root, shared servers, containers).
# - Intentionality: Never allow one user's files to be readable/writable by
#   another user. Every directory creation must be ownership-aware.
# - Anti-fragile: Survive permission conflicts and multi-user environments.
#
# CRITICAL WARNING - MULTI-USER PROBLEM AI FREQUENTLY OVERLOOKS:
# Many good applications on a computer are run by different users over time
# (e.g. normal user → sudo → another login account). 
#
# AI assistants often simply "add mkdir -p" when solving a storage task without
# considering ownership and cross-user write privilege. This approach is
# untested and problematic — it can create directories owned by one user that
# another user cannot read/write, or allow unintended access between users.
#
# That is why we intentionally isolate folders per user (${APP_NAME}-${USERNAME})
# and why any change to this function must preserve strict per-user isolation.
# Rewriting this with a generic shared folder is forbidden and has caused
# permission bugs in the past.
#
# !!! DO NOT MODIFY OR SIMPLIFY THIS FUNCTION !!!
# Designed to be reusable in other projects.
#
# ECHO EXCEPTION (class B – function return-via-stdout):
# echo of storage paths is a data return for $(util_resolve_storage) capture,
# not a product user message. Failures use out_die.
# See requirement-shell-output-requirements.md §2.1.1.
#
# Last reviewed: 2026-07-12
# =============================================================================
util_resolve_storage() {
    # --- Safe Variable Defaults ----
    # Defensive defaults - never assume globals are set
    : "${USERNAME:=unknown}"
    : "${APP_NAME:=app}"

    if [ -d "/dev/shm" ] && [ -w "/dev/shm" ]; then
        echo "/dev/shm/${APP_NAME}-${USERNAME}"
        return
    fi
    if [ -w "/tmp" ]; then
        echo "/tmp/${APP_NAME}-${USERNAME}"
        return
    fi
    mkdir -p "${STORAGE_DIR}" 2>/dev/null || out_die "Cannot create storage directory ${STORAGE_DIR}"
    echo "${STORAGE_DIR}"
}

# =============================================================================
# prompt_ask() - Defensive general-purpose interactive prompt with default
# =============================================================================
#
# GENERAL PURPOSE:
# Displays a message, shows current/default values if available, and waits
# for user input. Returns the answer (or the default if user presses Enter).
# Fully respects --quiet, --json, and non-TTY environments.
# Uses the centralized output system (out_info / out_msg_n).
#
# This is the **Single Source of Truth** for all simple value prompts in the project.
#
# CIAO PRINCIPLES APPLIED:
# - Caution (Principle 1): Multiple guards prevent prompting in non-interactive contexts.
# - Intentional (Principle 2): Clear behavior for TTY vs non-TTY and quiet/JSON modes.
# - Anti-fragile (Principle 3): Works reliably across different terminals and invocation methods.
# - Over-protect (Principle 4 / CIAO-Lite O · Principle 20): Trusts explicit INTERACTIVE=1 from caller when low-level TTY check is flaky.
#
# !!! DO NOT MODIFY OR SIMPLIFY THIS FUNCTION !!!
# Past AI assistants have repeatedly broken this by using raw printf/echo + read,
# which violates the single output system, quiet/json handling, and TTY detection.
#
# WARNING — do-not-capture-read (**PP-A-22** / T1-PROMPT-CAPTURE)
# MUST NOT _x=$(prompt_ask …) / $() / backticks. This body contains `read`.
# Call in the current shell. Value is PROMPT_ASK_VALUE (term prompt-ask-value).
# stderr+$() is NOT a license. Do NOT return the answer via class-B printf.
# Terms: do-not-capture-read · command-substitution-subshell
#
# Last updated: 2026-09-02
# =============================================================================

prompt_ask() {
    # --- Safe Variable Defaults ---
    : "${JSON:=0}"
    : "${QUIET:=0}"
    : "${PROMPT_ASK_VALUE:=}"

    local message="$1"
    local default="$2"
    local current="$3"

    PROMPT_ASK_VALUE="${default}"

    # Never prompt in non-interactive modes
    if [ "${JSON}" -eq 1 ] || [ "${QUIET}" -eq 1 ]; then
        return 0
    fi

    # Must have a real TTY (unless caller explicitly set INTERACTIVE=1)
    if ! [ -t 0 ] || ! [ -t 1 ]; then
        if [ "${INTERACTIVE:-0}" -ne 1 ]; then
            return 0
        fi
    fi

    # Show current value if present
    if [ -n "${current}" ]; then
        out_info "Current: ${current}"
    fi

    # Show default
    if [ -n "${default}" ]; then
        out_info "Default: ${default}"
    fi

    out_msg_n "${message}: "

    local answer=""
    read -r answer || true

    if [ -n "${answer}" ]; then
        PROMPT_ASK_VALUE="${answer}"
    fi
    return 0
}

# =============================================================================
# prompt_yes_no() - Defensive interactive yes/no confirmation prompt
# =============================================================================
#
# GENERAL PURPOSE:
# Displays a message and waits for (y/N) confirmation.
# Returns 0 if user says yes, returns 1 (non-zero) if user says no or cancels.
#
# CRITICAL DEFENSIVE RULES (DO NOT VIOLATE):
# 1. Must ALWAYS go through single source of truth (out_msg_n + out_text)
# 2. Must respect --quiet and --json (never show prompt in those modes)
# 3. Must NEVER use raw printf/echo for user-visible prompt text (product UI)
#    (class-B return-via-stdout does not apply here — this helper uses exit status)
# 4. Must work correctly in non-interactive / curl | sh environments
# 5. Must preserve TTY detection and color handling via out_text
# 6. This is the SINGLE SOURCE OF TRUTH for all yes/no confirmations in the project.
#
# !!! DO NOT MODIFY OR SIMPLIFY THIS FUNCTION !!!
# Past AI assistants have repeatedly replaced this kind of prompt with
# raw printf + read, breaking consistency with out_text(), --quiet,
# --json, TTY detection, and the overall defensive design.
#
# This helper exists specifically to prevent that regression and to enforce
# CIAO-Lite principles of Caution, Intentionality, and Over-protect.
#
# WARNING — do-not-capture-read (**PP-A-22** / T1-PROMPT-CAPTURE)
# MUST NOT _y=$(prompt_yes_no …) / $() / backticks. This body contains `read`.
# Call: if prompt_yes_no "…"; then …  stderr+$() is NOT a license.
#
# Last updated: 2026-09-02
# =============================================================================

prompt_yes_no() {
    # --- Safe Variable Defaults ----
    # Defensive defaults - never assume globals are set
    : "${JSON:=0}"
    : "${QUIET:=0}"

    local message="$1"

    # Never show prompt in quiet or json mode
    if [ "${JSON}" -eq 1 ] || [ "${QUIET}" -eq 1 ]; then
        return 1   # treat as "no" in non-interactive modes
    fi

    # Must be interactive TTY
    if ! [ -t 0 ] || ! [ -t 1 ]; then
        return 1
    fi

    out_msg_n "${message} (y/N)? "

    local answer=""
    read -r answer || true

    case "$answer" in
        [Yy]*|[Yy][Ee][Ss]*)
            return 0
            ;;
        *)
            return 1
            ;;
    esac
}


# =============================================================================
# app_about() - Display diagnostic information about the current environment
# =============================================================================
#
# GENERAL PURPOSE:
# Shows detailed diagnostic information: version, installation status (global + local),
# current shell, TTY/interactive status, user, and helpful next steps.
#
# Fully respects --quiet and --json modes.
# In JSON mode: outputs exactly ONE clean, machine-readable JSON object.
# In quiet mode: prints nothing.
#
# This function provides real value to users (unlike the previous overly simple version)
# and should be kept in sync with the overall CIAO design and README.md.
#
# !!! DO NOT MODIFY OR SIMPLIFY THIS FUNCTION !!!
# Designed to be reusable in other CIAO projects.
# Last reviewed: April 2026
# =============================================================================

# =============================================================================
# util_get_current_shell() - Detect current / parent shell name
# =============================================================================
#
# GENERAL PURPOSE:
# Returns a best-effort shell command name for diagnostics (about).
# Prefer parent shell when the current process is sh/dash/ash/the app itself.
#
# PRINTF EXCEPTION (class B – function return-via-stdout):
# Final printf '%s' "$shell" (and echo fallbacks inside $(…)) are data
# returns for capture by app_about — not product messages. Display uses out_*.
# See requirement-shell-output-requirements.md §2.1.1.
#
# !!! DO NOT MODIFY OR SIMPLIFY THIS FUNCTION !!!
# Nested functions are not portable POSIX; this must stay top-level.
#
# Last reviewed: 2026-07-12
# =============================================================================
util_get_current_shell() {
    local shell="unknown"
    shell=$(ps -p $$ -o comm= 2>/dev/null | tr -d '()' || echo "unknown")

    if [ "$shell" = "${APP_NAME}" ] || [ "$shell" = "sh" ] || \
       [ "$shell" = "dash" ] || [ "$shell" = "ash" ]; then
        local parent_pid
        parent_pid=$(ps -p $$ -o ppid= 2>/dev/null | tr -d ' ')
        if [ -n "$parent_pid" ]; then
            shell=$(ps -p "$parent_pid" -o comm= 2>/dev/null | tr -d '()' || echo "$shell")
        fi
    fi
    printf '%s' "$shell"
}

app_about() {
    # --- Safe Variable Defaults ---
    : "${JSON:=0}"
    : "${QUIET:=0}"
    : "${APP_NAME:=selfmanaged}"
    # Version comes from global SSOT (VERSION="1.0.0" near top); default only if unset
    : "${VERSION:=1.0.0}"
    : "${GLOBAL_BIN:=/usr/local/bin}"
    : "${USER_BIN:=${HOME}/.local/bin}"
    : "${SCRIPT_URL:=}"

    if [ "${JSON}" -eq 1 ]; then
        # === JSON MODE - Clean, machine-friendly output ===
        local installed="false"
        inst_is_installed && installed="true"

        local global_ver="not found"
        if [ -x "${GLOBAL_BIN}/${APP_NAME}" ]; then
            global_ver=$(grep '^VERSION="' "${GLOBAL_BIN}/${APP_NAME}" 2>/dev/null | cut -d'"' -f2 || echo "unknown")
        fi

        local local_ver="not found"
        if [ -x "${USER_BIN}/${APP_NAME}" ]; then
            local_ver=$(grep '^VERSION="' "${USER_BIN}/${APP_NAME}" 2>/dev/null | cut -d'"' -f2 || echo "unknown")
        fi

        local current_shell
        current_shell=$(util_get_current_shell)

        local interactive="false"
        [ -t 1 ] && interactive="true"

        local current_user
        current_user="$(id -un 2>/dev/null || echo "unknown")"

        out_json "about" "" \
            "app" "${APP_NAME}" \
            "version" "${VERSION}" \
            "installed" "${installed}" \
            "global_version" "${global_ver}" \
            "local_version" "${local_ver}" \
            "shell" "${current_shell}" \
            "interactive" "${interactive}" \
            "user" "${current_user}"
        return 0
    fi

    # === Normal Human-readable Mode ===
    [ "${QUIET}" -eq 1 ] && return 0

    out_info "=== ${APP_NAME} ${VERSION} - About / Diagnostics ==="
    out_empty_line

    # Installation status
    if inst_is_installed; then
        out_success "${APP_NAME} is properly installed."
    else
        out_warn "${APP_NAME} is NOT installed in your PATH."
        if [ -n "${SCRIPT_URL}" ]; then
            out_info "   Recommended: curl -fsSL ${SCRIPT_URL} | sh"
        else
            out_info "   Set SCRIPT_URL to the install script URL, then: curl -fsSL \"\${SCRIPT_URL}\" | sh"
        fi
    fi

    out_empty_line

    # Global vs Local installation details
    if [ -x "${GLOBAL_BIN}/${APP_NAME}" ]; then
        global_ver=$(grep '^VERSION="' "${GLOBAL_BIN}/${APP_NAME}" 2>/dev/null | cut -d'"' -f2 || echo "unknown")
        out_info "Global install  (${GLOBAL_BIN}/${APP_NAME}):   ${global_ver}"
    else
        out_info "Global install  (${GLOBAL_BIN}/${APP_NAME}):   not found"
    fi

    if [ -x "${USER_BIN}/${APP_NAME}" ]; then
        local_ver=$(grep '^VERSION="' "${USER_BIN}/${APP_NAME}" 2>/dev/null | cut -d'"' -f2 || echo "unknown")
        out_info "Local install   (${USER_BIN}/${APP_NAME}):    ${local_ver}"
    else
        out_info "Local install   (${USER_BIN}/${APP_NAME}):    not found"
    fi

    out_empty_line

    local current_user
    current_user="$(id -un 2>/dev/null || echo "unknown")"
    out_info "Current user:      ${current_user}"

    if [ "$(id -u)" -eq 0 ]; then
        out_success "Execution context: root (global install path available)"
    else
        out_info "Execution context: normal user (Type 0 CLI self-management)"
    fi

    out_empty_line

    local current_shell
    current_shell=$(util_get_current_shell)

    out_info "Current shell:     ${current_shell}"

    if [ -t 1 ]; then
        out_info "TTY / Interactive: yes"
    else
        out_info "TTY / Interactive: no (non-interactive / scripted mode)"
    fi

    out_empty_line
    out_info "Useful commands:"
    out_info "   ${APP_NAME} help           → Full usage"
    out_info "   ${APP_NAME} self-update    → Update to latest version"
    out_info "   ${APP_NAME} self-uninstall → Clean removal from system"
    out_info "   ${APP_NAME} --json         → Machine-readable output"

    out_empty_line
    out_info "Run '${APP_NAME} help' for complete usage information."
}

app_version() {
    if [ "${JSON}" -eq 1 ]; then
        out_json "version" "${VERSION}"
    else
        out_plain "${APP_NAME} version ${VERSION}"
    fi
}

# =============================================================================
# app_help() - Display help for selfmanaged
# =============================================================================
#
# Shows usage, available commands, and global flags.
# Fully respects --quiet and --json modes.
#
# In --json mode: returns a minimal success object instead of long text.
# In --quiet mode: prints nothing (silent).
#
# Keep in sync with requirement-shell-cli-interface.md command table.
# =============================================================================

app_help() {
    : "${SHORT_DESCRIPTION:=${APP_DESC:-Shell script bootstrap for self Installation & Maintenance}}"
    : "${DESCRIPTION:=POSIX /bin/sh Type 0 CLI: install, version-check, self-update, self-uninstall, and about.}"

    if [ "${JSON}" -eq 1 ]; then
        out_json "success" "Help text available in human-readable mode. Run without --json." \
            "command" "help" \
            "note" "Use --json with version, about, version-check, install, self-update, self-uninstall."
        return 0
    fi

    if [ "${QUIET}" -eq 1 ]; then
        return 0
    fi

    out_info "${APP_NAME} — ${SHORT_DESCRIPTION}"
    out_plain "${DESCRIPTION}"
    out_empty_line

    out_info "Usage:"
    out_plain "  ${APP_NAME} [command] [options]"
    out_empty_line

    out_info "Self-Management (Type 0 - any user):"
    out_plain "  install              Install ${APP_NAME} (root→global, user→~/.local/bin)"
    out_plain "  version              Show current version"
    out_plain "  about                Show detailed diagnostics"
    out_plain "  version-check        Compare local vs remote version (needs SCRIPT_URL)"
    out_plain "  self-update          Update ${APP_NAME} to a newer remote version"
    out_plain "  self-uninstall       Remove ${APP_NAME} (safe PATH cleanup)"
    out_plain "  help                 Show this help"
    out_empty_line

    out_info "Global Options:"
    out_plain "  --quiet, -q          Suppress info/success (errors and warnings still shown)"
    out_plain "  --json               Machine-readable JSON (implies --quiet)"
    out_plain "  --force              Force reinstall / skip uninstall confirm / allow downgrade"
    out_plain "  --debug              Debug diagnostics on stderr"
    out_empty_line

    # Channel vars only — CHECKSUM is install-path runtime pin, not help/about surface
    # (template-automatic-checksum / specialized automatic-checksum requirement).
    out_info "Environment:"
    out_plain "  REPO_USER            GitHub owner (composes default SCRIPT_URL)"
    out_plain "  REPO_NAME            GitHub repo name (composes default SCRIPT_URL)"
    out_plain "  SCRIPT_URL           Canonical install script URL (required for version-check/self-update)"
    out_empty_line
}


# =============================================================================
# app_main() - Main entrypoint and command dispatcher
# =============================================================================
#
# GENERAL PURPOSE:
# Thin dispatcher for the selfmanaged CLI.
# Handles:
#   - Type O empty argv = install-ensure (curl | sh): not-installed / local / global
#   - Global flag parsing (--quiet, --json, --debug, --force)
#   - Command routing for all Type 0 self-management commands
#
# This is the single entry point when the script is executed directly.
#
# CIAO PRINCIPLES APPLIED:
# - Caution (Principle 1): Never call undefined functions. Always use inst_is_installed.
#   Empty-argv ensure block is kept at the very top as required by existing comments.
# - Intentional (Principle 2): All supported commands from
#   requirement-shell-cli-interface.md and app_help() are recognized and routed.
# - Anti-fragile (Principle 3): Works correctly in interactive TTY, quiet, JSON,
#   and non-interactive `curl | sh` environments.
# - Over-protect (Principle 4 / CIAO-Lite O · Principle 20): Explicit if/then logic, safe defaults, and centralized
#   output via out_die for unknown commands.
#
# !!! DO NOT MODIFY OR SIMPLIFY THIS FUNCTION !!!
# This is the central command dispatcher. Changes here affect every execution path.
#
# Lessons Learned (CIAO Reflection):
# 2026-06-26:
#   - Original version called non-existent functions and only recognized
#     version/about/help; expanded routing and safe defaults.
# 2026-07-12:
#   - Wired --force → FORCE=1 and FORCE_REINSTALL=1 (requirement-shell-cli-interface).
# 2026-07-14:
#   - Type O: empty argv is always install-ensure (not help when already installed).
#     Aligns with template-shell-cli-zero-arguments.md / template-online-install §3.0a.
#
# Last reviewed: 2026-07-14
# =============================================================================

app_main() {
    # --- Safe Variable Defaults ---
    : "${COMMAND:=help}"
    : "${QUIET:=0}"
    : "${JSON:=0}"
    : "${DEBUG:=0}"
    : "${FORCE:=0}"
    : "${FORCE_REINSTALL:=0}"

    # === ZERO-ARG = Type O install-ensure (curl | sh contract) ===
    # Empty argv always means ensure installed, never help.
    # - not installed → install (TTY via inst_maybe_install; quiet/json direct)
    # - already installed (local or global) → success no-op via inst_perform_install
    # Exit status must reflect install outcome (failed download/checksum → non-zero).
    if [ $# -eq 0 ]; then
        if [ "${JSON}" -eq 1 ] || [ "${QUIET}" -eq 1 ]; then
            inst_perform_install
            exit $?
        elif inst_is_installed; then
            inst_perform_install
            exit $?
        else
            inst_maybe_install
            exit $?
        fi
    fi

    # === Argument parsing: flags and commands (order-independent) ===
    while [ $# -gt 0 ]; do
        case "$1" in
            --quiet|-q) QUIET=1 ;;
            --json)     JSON=1; QUIET=1 ;;
            --debug)    DEBUG=1 ;;
            --force)    FORCE=1; FORCE_REINSTALL=1 ;;
            version|about|help|version-check|self-update|self-uninstall|install)
                COMMAND="$1"
                ;;
            *)
                out_die "Unknown command or flag: $1. See '${APP_NAME} help'."
                ;;
        esac
        shift
    done

    # Export force into install/uninstall paths via globals already set
    out_debug "dispatch command=${COMMAND} quiet=${QUIET} json=${JSON} force=${FORCE}"

    case "${COMMAND}" in
        version)
            if [ "${JSON}" -eq 1 ]; then
                out_json "version" "" "app" "${APP_NAME}" "version" "${VERSION}"
            else
                out_info "${APP_NAME} version ${VERSION}"
            fi
            ;;
        about)
            app_about
            ;;
        version-check)
            ver_check
            ;;
        self-update)
            inst_self_update
            ;;
        self-uninstall)
            inst_self_uninstall
            ;;
        install)
            inst_perform_install
            ;;
        help|*)
            app_help
            ;;
    esac
}

# =============================================================================
# BOOTSTRAP
# =============================================================================
#
# Always invoke the single dispatcher. Do NOT gate on ${0##*/} matching APP_NAME:
# under curl | sh / stdin pipe, $0 is the shell (sh/bash/…), not the product
# filename — a basename gate causes silent no-op and breaks one-liner install.
# See docs/terminologies/shell-cli-bootstrap.md and INC-20260712-001.
#
# Single-file install CLI: source-as-library is unsupported; main always runs.
# =============================================================================
app_main "$@"

# End of selfmanaged - Full featured CIAO-compliant implementation
```

## Design-time verification

| Gate | Artifact | Phase |
|------|----------|-------|
| Specialize → product suite or checklist | declare TP-IDs or checklist in specialized REQ | Design |
| RTM | `../tests/template-requirement-test-traceability.md` | Design |

When this mold has no executable TP family, mark **n/a** with reason in product `reviews/test-plan.md`.

