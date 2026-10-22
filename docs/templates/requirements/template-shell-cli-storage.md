---
name: shell-cli-storage
id: LM-SHELL-CLI-STORAGE
kind: law-mold
description: >
  Portable law mold. Cite as LM-SHELL-CLI-STORAGE (path secondary).
---

**file**: template-shell-cli-storage.md  
**Status**: Active (Version 1.5.3 – absent temp maker uses a child of the resolved root)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

## 1. Purpose

This template defines **shell CLI storage resolution** for Type 0 / online-install shell tools: where **volatile scratch** and **fallback app-scoped cache** paths live, how they are **isolated per user and app**, who owns path resolution, and what messages go through the **output SSOT**.

It is for **scratch and resolver policy** — not durable package install paths (`~/.local/bin`), not domain project trees (e.g. Spring Boot demos), and not full atomic-publish protocols (those own their own staging rules).

**Specialize into:** `requirement-shell-cli-storage.md` (or language-prefixed equivalent) with filled Implementation Notes (live resolver name, priority chain, call sites, Gaps).

**Author / convert / review skills (when on disk):** `skill-write-template` · `skill-requirement-template-conversion` · `skill-template-review` · specialize via `skill-create-specific-requirement` · implement via `skill-sh-script-coding` · test via `skill-shell-cli-test` (+ `checklist-shell-cli-test` storage section).

**Related templates (specialize separately):** modular function design (`util_*` ownership), output requirements (return-via-stdout vs user messages), path-and-shell-support (PATH after install), online-install / self-management (download `mktemp` staging), project-folder (layout patterns).

---

## Terminologies

Related glossary entries (disk-truth). Templates **point**; they do not replace primary
owner surfaces for live values. SSOT types use the shared taxonomy
(`ssot-terminology-policy-for-templates` / `ssot-catalog` / `skill-create-terminology`).

| Term | Path | SSOT type | Role |
|------|------|-----------|------|
| **No-hardcode policy** | `docs/policies/policy-no-hardcode.md` | `policy` | Portable placeholders; no product brand as universal law |
| **Terminology policy for templates** | `docs/policies/policy-terminology-for-templates.md` | `policy` | This file must keep a Terminologies section |
| **SSOT-terminology policy for templates** | `docs/policies/policy-ssot-terminology-for-templates.md` | `policy` | SSOT type codes + primary owners |
| **SSOT catalog** | `docs/terminologies/ssot-catalog.md` | `meta-catalog` | Inventory of SSOTs (list B) |
| **Temp file system** | `docs/terminologies/temp-file-system.md` | `runtime-mode` | **Primary** scratch/root priority + isolation language |
| **Project-base-path** | `docs/terminologies/project-base-path.md` | `identity-runtime` | Application directory. Not the scratch root this mold resolves |
| **Project-log-path** | `docs/terminologies/project-log-path.md` | `identity-runtime` | Log directory under that base. Not the volatile cache root |
| **Appname policy** | `docs/policies/policy-appname.md` | `identity-runtime` | Path segments keyed by `APP_NAME` |
| **Path-safe name** | `docs/terminologies/path-safe-name.md` | `policy` | Safe identifiers when names become path segments |
| **Atomic data file** | `docs/terminologies/atomic-data-file.md` | `mention-only` | Final data publish ≠ scratch resolve |
| **Atomic file copy** | `docs/terminologies/atomic-file-copy.md` | `mention-only` | Stage on same FS as FINAL when renaming |
| **Ship unit** | `docs/terminologies/ship-unit.md` | `mention-only` | Installable CLI under specialization |
| **SSOT of stdout** | `docs/terminologies/single-source-of-truth-of-stdout.md` | `channel-io` | User messages via output SSOT |

**SSOT types used in this template:** `policy` · `meta-catalog` · `runtime-mode` · `identity-runtime` · `channel-io` · `mention-only`

**Primary owner for live path values when specialized:** ship-unit Config / central resolver helper (not this template).

**Policies:** [`policy-terminology-for-templates.md`](../../policies/policy-terminology-for-templates.md) · [`policy-ssot-terminology-for-templates.md`](../../policies/policy-ssot-terminology-for-templates.md)

## 2. Scope split (mandatory)

| In scope | Out of scope (own law / other templates) |
|----------|------------------------------------------|
| Volatile / scratch root resolution | Install binary placement (`USER_BIN` / `GLOBAL_BIN`) |
| Per-user + per-app isolation of storage dirs | Domain product project dirs (e.g. demo app trees) |
| Central resolver helper ownership | Full atomic publish algorithms |
| Fallback chain when preferred mounts missing | Companion checksum integrity |
| Output contract for resolve failures / warnings | PATH shell-rc edits |
| `mktemp` for unique leaves under resolved roots | Secrets storage |

## 3. Core rules (portable)

### 3.1 Single resolver SSOT

1. Shell CLIs **MUST** expose **one** authoritative storage-resolve helper (convention: `util_resolve_storage` or documented product-family equivalent).  
2. Callers that need a scratch/cache root **MUST** use that helper (or `mktemp` under a root it returned) — **MUST NOT** hardcode bare `/tmp/{{APP}}` or bare `/dev/shm` dumps in multiple places.  
3. The resolver **MUST** return a path via **stdout for capture** (`$(util_resolve_storage)`) — that write is a **data return**, not product UI (output exception class B).  
4. User-visible warnings/errors about storage **MUST** go through the product **output SSOT** (`out_*` / `output_*` family as specialized).

### 3.2 Recommended resolve priority (specialize order if needed)

Portable family (first match that exists **and** is writable):

```text
1. /dev/shm exists (mkdir isolated child fail-soft)
2. Detect-specific: Termux $PREFIX/tmp (create); Git Bash $HOME/AppData/Local/Temp/cache
   when that Temp parent exists; else {{GIT_BASH_DRIVE}}/Users/{{USERNAME}}/AppData/Local/Temp/cache
   (default drive /c/)
3. $TEMP defined and exists → mkdir $TEMP/cache (fail-soft)
4. /tmp exists → mkdir /tmp/cache (fail-soft); else /tmp
else fail loud via output SSOT at the END — do not invent world-writable shared dumps
```

**`mkdir` of `cache` MUST NOT abort** the resolver. Isolation (`{{APP_NAME}}-{{USERNAME}}`) lives **under** the chosen cache root. Products **MAY** reorder or drop a tier only when documented in the specialized requirement. **MUST NOT** use `$HOME/.cache` as the Git Bash **volatile** root.

### 3.3 Isolation (mandatory spirit)

| Rule | Why |
|------|-----|
| Include **app identity** (`{{APP_NAME}}` or equivalent) | Avoid tool clashes |
| Include **user identity** (`{{USERNAME}}` / `id -un` equivalent) | Multi-user / sudo / shared hosts |
| Prefer unique leaves via **`mktemp`** under the resolved root when creating files | Symlink / TOCTOU resistance |
| Never assume mount **exists**, is **writable**, or is **executable** | Alpine, containers, `noexec` |
| Do not create shared dirs without ownership awareness | Cross-user permission bugs |

**Forbidden:** “just `mkdir -p /tmp/shared`” without per-user isolation; rewriting the resolver to a single shared world-writable folder “for simplicity.”

### 3.4 Creation and failure (create-before-return — normative)

1. For the **chosen** tier, the resolver **MUST** `mkdir -p` (or equivalent) the **isolated root** and only then print the path.  
2. Creation **MUST** be ownership-aware (per-user path segments). Soft-return of a path that does not exist is **forbidden** (historical dead-util class).  
3. Failure to create **one** cache leaf **MUST NOT** die — try the next root. Failure to obtain **any** usable storage root **MUST** fail closed (non-zero / die) with a clear message via output SSOT — **MUST NOT** silent empty path.  
4. Optional fallbacks **MAY** warn in human mode when leaving a preferred tier; quiet/json **MUST** still be valid (warn suppressed or structured as designed).

### 3.4.1 Wire and diagnostics (normative when specialized)

When this mold is specialized into product law, the live CLI **MUST** wire storage — a defined-but-unused helper is incomplete:

| Surface | Requirement |
|---------|-------------|
| `app_main` (or single entry) | Early: `EFFECTIVE_STORAGE_DIR=$(util_resolve_storage)` (or family); export `EFFECTIVE_STORAGE_DIR`, config fallback `STORAGE_DIR`, and **`TMPDIR=${EFFECTIVE_STORAGE_DIR}`** so `mktemp -t` inherits isolation |
| `app_about` JSON | Include `effective_storage` and `storage_dir` (or documented equivalents); **MUST NOT** include `CHECKSUM` |
| `app_about` human | Show effective storage (and config fallback field) |
| Temp leaves | Unique names under **`LM-TEMP-FILE-SYSTEM`**. This mold owns **roots**, not the install `mktemp` leaf policy. When the temp maker is absent, the leaf is a child of the root this mold resolved (**PP-A-29**). Do not restate that leaf rule here |

### 3.5 Coupling to install / atomic / domain / temp

| Concern | Storage template role |
|---------|----------------------|
| Download install staging | Prefer `mktemp` under exported `$TMPDIR` (see temp mold); may use resolved root — not required to use `/dev/shm` as FINAL |
| Atomic rename to FINAL on disk | Stage on **same filesystem** as FINAL when possible (may **not** be shm) |
| Domain durable project trees | **Not** this resolver — own domain requirement / flags (e.g. `--project-dir`) |
| Temp leaf uniqueness / trap / maker-absent fallback / directory **0700** | **`LM-TEMP-FILE-SYSTEM`** peer — do not restate that leaf rule here |

### 3.6 Helper naming (portable)

| Convention | Example |
|------------|---------|
| Seed modular table | `util_resolve_storage` |
| Product family variants | Documented in specialized Implementation Notes |

Prefix ownership: storage resolve is **util / integrity-adjacent**, not `out_*`, not domain `{{APP_NAME}}_*` business verbs.

### 3.7 Persistence path SSOT

Durable this-login files use one formula. The product name is not written a second time into the path.

| Item | Rule |
|------|------|
| **Formula** | `${HOME}/.local/${APP_NAME}` |
| **Identity owner** | Config `APP_NAME`, one ship-unit assignment `APP_NAME="{{APP_NAME}}"` |
| **Helper** | `util_persistent_storage_dir` prints that formula. `util_resolve_persistent_storage` creates it, then prints it |
| **Path text** | Helpers, about lines, tests, and specialized requirement path rows keep `${APP_NAME}` / `{{APP_NAME}}` |
| **Unset fallback in this mold** | `: "${APP_NAME:=app}"` is a generic empty-name fallback for the example only |
| **Ship unit** | After the one assignment, helpers read `${APP_NAME}`. They do not add `: "${APP_NAME:=<product>}"` |
| **Different variable** | Domain `PERSISTENT_DIR` (often under the user cache) is not this folder |
| **Install bin** | `${HOME}/.local/bin` is not this folder |

## 4. Implementation Notes (fill when specializing)

| Item | Value for this product |
|------|------------------------|
| **Resolver name** | … |
| **Priority chain (live)** | … |
| **Persistence formula** | `${HOME}/.local/${APP_NAME}` (identity field may name live `APP_NAME`; path cell keeps the formula) |
| **Isolation keys** | … |
| **Fallback `STORAGE_DIR` / Config** | … |
| **Call sites** | … (or Gap: defined but unused) |
| **Output SSOT on failure** | … |
| **Tests** | … |

## 5. Why this template exists (CIAO)

- **Caution:** Multi-user machines; never mix users’ scratch files.  
- **Intentional:** One resolver SSOT; explicit fallback chain.  
- **Anti-fragile:** Survive missing `/dev/shm`, read-only `/tmp` quirks via fallback + fail loud.  
- **Over-protect:** Ban AI “mkdir -p shared temp” rewrites that drop isolation.

## 6. Design principles

- Prefer volatile first, durable cache last for **scratch**.  
- Isolation before convenience.  
- Data-return stdout ≠ product banners.  
- Specialize product paths in Implementation Notes only.

## Under command line for normal user only

When the ship unit detects a **command line for normal user only** (Termux, Git Bash, or the same class — term [`command-line-for-normal-user-only.md`](../../terminologies/command-line-for-normal-user-only.md)):

| MUST | MUST NOT |
|------|----------|
| Keep **normal user privilege** (Type 0) only | Implement or enable **admin privilege** (Type 1) or **dedicated system user privilege** (Type 2) |
| Document Type 1 **unused** and Type 2 **unused** | In-tool `sudo`; wrap `apt` / `dnf` / `yum`; write `/etc` dests; `useradd` / dedicated LPU; Type 2 `sudo -u` switch |
| Termux: named `pkg` as this login remains Type 0 (**`LM-SHELL-TERMUX-ISH`**) | Recommend `sudo curl \| sh` as the install path |
| Git Bash: same privilege ceiling | Invoke Termux `pkg` because Git Bash was detected |

Detect (typical): Termux — `PREFIX` contains `com.termux`; `TERMUX_VERSION` set; `/data/data/com.termux/files/usr` exists. Git Bash — **primary** folder `/c/` or `/c` (default drive `/c/`); secondary `MSYSTEM` is `MINGW*` / `MSYS*` / `UCRT*` / `CLANG*`; `uname -s` is `MINGW*` / `MSYS*`. Windows cmd — `OS` is `Windows_NT` or `ComSpec`/`COMSPEC` names `cmd.exe` (after excluding Git Bash, Cygwin, WSL). Git Bash volatile Temp: [`git-bash-temp-folder.md`](../../terminologies/git-bash-temp-folder.md).

**This mold:** scratch/cache resolve stays this-login (`$PREFIX` / user cache); **MUST NOT** write `/etc` dests.

## 7. Protection Rule (Sacred)

**Future AI assistants, Grok, or maintainers MUST NOT**:

1. Remove per-user isolation from the resolve chain “for simplicity.”  
2. Hardcode product brands into this **template** as universal law.  
3. Scatter ad-hoc `/tmp/{{APP}}` paths outside the central resolver.  
4. Treat bare shared `/dev/shm` or `/tmp` as a multi-tenant dump.  
5. Use the storage resolver for **install binary** placement or **domain project** roots without explicit specialized design.  
6. Fail open with an empty path when no storage is available.  
7. Emit user-facing storage errors with raw `echo` outside output SSOT.  
8. Assume temp mounts are executable.  
9. Claim this template is product law — only the specialized `requirement-*.md` is.
10. Echo a tier path **without** creating it (or without fail-closed create).
11. Leave the resolver as dead code with no `app_main` / about wire while claiming storage product law.
12. Export install temps under a world-writable shared dump when `EFFECTIVE_STORAGE_DIR` was already resolved.  
13. Strip the **Under command line for normal user only** section, or resolve scratch into `/etc` on that class.
14. Die because `mkdir` of `{{parent}}/cache` failed while another root in the chain is still untried.
15. Use `$HOME/.cache` as the Git Bash volatile root when `$HOME/AppData/Local/Temp` or `/c/Users/{{USERNAME}}/AppData/Local/Temp` exists.
16. Paste a product basename into the persistence path. The formula is `${HOME}/.local/${APP_NAME}` from the one `APP_NAME` assignment.

**Violating this rule is a critical storage/isolation regression.**

---


## Design-time verification

| TP family / ID | Proof mold | Planned suite / intent |
|----------------|------------|------------------------|
| **TP-CLI-05** about storage resolve | `../tests/template-shell-cli-test-plan.md` (`PM-SHELL-CLI-TEST-PLAN`) | `effective_storage` / `storage_dir`; isolation; dir exists after resolve; optional `STORAGE_DIR` override on fallback field |
| **TP-CLI-04** about JSON purity (peer) | same | about **must not** include `CHECKSUM` |
| **TP-LC-*** / **TP-CSUM-*** (peer) | install lifecycle / checksum plans | install staging inherits `TMPDIR` under resolved root when wired |

**RTM:** `../tests/template-requirement-test-traceability.md` · cite **`LM-SHELL-CLI-STORAGE`**

**Last Updated**: 2026-09-30 (1.5.3: absent temp maker; leaf stays a child of this mold’s root)  
**Owner**: Shell CLI portable patterns  
**Version history:**  
- **1.5.3** (2026-09-30): When the temp maker is absent, the leaf is a child of the root this mold resolved (**PP-A-29**). Leaf rule stays on **`LM-TEMP-FILE-SYSTEM`**.  
- **1.5.2** (2026-09-23): Persistence path SSOT is `${HOME}/.local/${APP_NAME}` from one `APP_NAME` assignment. Path rows keep the formula.  
- **1.5.1** (2026-09-17): Optional POSIX-only Type 0 resolve chain (`/dev/shm` → `/tmp` → XDG) beside the Git Bash walk.  
- **1.5.0** (2026-09-12): `util_resolve_persistent_storage` — durable `{{HOME}}/.local/{{APP_NAME}}` vs volatile cache.  
- **1.4.0** (2026-09-10): Git Bash `/c/` Temp + mkdir fail-soft; keep this-login section.  
- **1.3.0**: Named section Under command line for normal user only.  
- **1.2.0** (2026-08-18): Full `util_resolve_storage` template-example-function (create-before-return).  
- **1.1.0**: Create-before-return all tiers; main/about wire + TMPDIR export; expanded DTV; temp coupling.  
- **1.0.0**: Initial resolve priority + isolation.  

**Specialize pointer:** `requirement-shell-cli-storage.md` (or project equivalent)


---

## Example util helpers (Type 0 shell CLI storage / shell)

### `util_get_current_shell` — class B return (about diagnostics)

```sh
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
```

### `util_resolve_storage` — class B return (create-before-return)

Type 0 shell CLI storage resolve prefers writable volatile (`/dev/shm`) then Git Bash Temp `cache` then `$TEMP/cache` then `/tmp/cache` with **per-user** isolation (`${APP_NAME}-${USERNAME}`). **`mkdir` of `cache` is fail-soft** (next root; die only at the end). Wire from `app_main` (`EFFECTIVE_STORAGE_DIR` + `TMPDIR`) and expose fields on `about`. Preserve multi-user ownership; return path via stdout (class B). Do not share one world-writable folder across users.

```sh
# GENERAL PURPOSE: Isolated scratch/cache root. Class B stdout for $(…) capture.
# mkdir of one cache leaf MUST NOT abort — walk remaining roots.
util_resolve_storage() {
    : "${USERNAME:=unknown}"
    : "${APP_NAME:=app}"
    : "${HOME:=/tmp}"
    : "${XDG_CACHE_HOME:=${HOME}/.cache}"
    : "${GIT_BASH_DRIVE:=/c}"
    : "${TEMP:=}"

    _storage_root=""
    if [ -d "/dev/shm" ]; then
        mkdir -p "/dev/shm/${APP_NAME}-${USERNAME}" 2>/dev/null || true
        if [ -d "/dev/shm/${APP_NAME}-${USERNAME}" ] && [ -w "/dev/shm/${APP_NAME}-${USERNAME}" ]; then
            _storage_root="/dev/shm/${APP_NAME}-${USERNAME}"
        fi
    fi
    if [ -z "${_storage_root}" ] && [ -d "${HOME}/AppData/Local/Temp" ]; then
        mkdir -p "${HOME}/AppData/Local/Temp/cache/${APP_NAME}-${USERNAME}" 2>/dev/null || true
        if [ -d "${HOME}/AppData/Local/Temp/cache/${APP_NAME}-${USERNAME}" ] && [ -w "${HOME}/AppData/Local/Temp/cache/${APP_NAME}-${USERNAME}" ]; then
            _storage_root="${HOME}/AppData/Local/Temp/cache/${APP_NAME}-${USERNAME}"
        fi
    fi
    if [ -z "${_storage_root}" ] && [ -n "${TEMP}" ] && [ -d "${TEMP}" ]; then
        mkdir -p "${TEMP}/cache/${APP_NAME}-${USERNAME}" 2>/dev/null || true
        if [ -d "${TEMP}/cache/${APP_NAME}-${USERNAME}" ] && [ -w "${TEMP}/cache/${APP_NAME}-${USERNAME}" ]; then
            _storage_root="${TEMP}/cache/${APP_NAME}-${USERNAME}"
        fi
    fi
    if [ -z "${_storage_root}" ] && [ -d "/tmp" ]; then
        mkdir -p "/tmp/cache/${APP_NAME}-${USERNAME}" 2>/dev/null || true
        if [ -d "/tmp/cache/${APP_NAME}-${USERNAME}" ] && [ -w "/tmp/cache/${APP_NAME}-${USERNAME}" ]; then
            _storage_root="/tmp/cache/${APP_NAME}-${USERNAME}"
        fi
    fi
    if [ -z "${_storage_root}" ]; then
        out_die "Cannot create storage directory. Next: mkdir -p \"\${HOME}/AppData/Local/Temp/cache\""
    fi
    echo "${_storage_root}"
    unset _storage_root
    return 0
}
```

**Related vars:** `USERNAME`, `APP_NAME`, `HOME`, `XDG_CACHE_HOME`, `STORAGE_DIR` — [shell-cli-config-variables](../../terminologies/shell-cli-config-variables.md).

**POSIX-only Type 0 bootstrap (optional simpler chain):** when Git Bash / Windows Temp is **not** in scope, specialize **MAY** use `/dev/shm` → `/tmp` → `XDG_CACHE_HOME` with create-before-return fail-closed. **MUST** keep per-user `${APP_NAME}-${USERNAME}` isolation.

```sh
util_resolve_storage() {
    : "${USERNAME:=unknown}" : "${APP_NAME:=app}" : "${HOME:=/tmp}"
    : "${XDG_CACHE_HOME:=${HOME}/.cache}"
    _storage_candidate=""
    if [ -d "/dev/shm" ] && [ -w "/dev/shm" ]; then
        _storage_candidate="/dev/shm/${APP_NAME}-${USERNAME}"
    elif [ -w "/tmp" ]; then
        _storage_candidate="/tmp/${APP_NAME}-${USERNAME}"
    else
        : "${STORAGE_DIR:=${XDG_CACHE_HOME}/${APP_NAME}-${USERNAME}}"
        _storage_candidate="${STORAGE_DIR}"
    fi
    mkdir -p "${_storage_candidate}" 2>/dev/null || out_die "Cannot create storage directory ${_storage_candidate}"
    echo "${_storage_candidate}"
    unset _storage_candidate
}
```

### `util_resolve_persistent_storage` — durable this-login folder (not `/dev/shm`)

**Kind:** [template-example-function](../../terminologies/template-example-function.md). Volatile cache (`util_resolve_storage`) dies on reboot (`/dev/shm`). Operator-remembered leaves (last remote, per-Host folder list) **MUST** live under `{{HOME}}/.local/{{APP_NAME}}`. **MUST NOT** be `USER_BIN`. The product basename stays in the one `APP_NAME` assignment. This helper reads `${APP_NAME}`.

```sh
# Class B stdout for $(…) capture. mkdir of this leaf MAY fail closed (durable, not a cache walk).
util_persistent_storage_dir() {
    : "${HOME:=/tmp}"
    : "${APP_NAME:=app}"
    printf '%s' "${HOME}/.local/${APP_NAME}"
}

util_resolve_persistent_storage() {
    : "${APP_NAME:=app}"
    : "${HOME:=/tmp}"
    _persist=$(util_persistent_storage_dir)
    case "${_persist}" in
        */.local/bin|*/.local/bin/)
            out_die "Persistence storage must not be the install bin directory"
            ;;
    esac
    if ! mkdir -p "${_persist}" 2>/dev/null || [ ! -w "${_persist}" ]; then
        out_die "Cannot create persistence storage ${_persist}"
    fi
    echo "${_persist}"
    unset _persist
    return 0
}
```

Leaves (mode **600**): `preferred-remote`, per-key remembered paths. **MUST NOT** freeze a session login or LAN address in the mold.

