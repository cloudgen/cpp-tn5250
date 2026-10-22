---
name: online-install
id: LM-ONLINE-INSTALL
kind: law-mold
description: >
  Portable law mold. Cite as LM-ONLINE-INSTALL (path secondary).
---

**file**: template-online-install.md  
**Status**: Active (Version 1.13.0 – dest mode via `inst_cli_dest_mode`; self-place peer)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

## 1. Purpose

This template defines the official **one-command online installation** behavior for **Type O-S script-alone** products using the `curl | sh` pattern (or `wget` equivalent): channel SSOT, pipe bootstrap, Type O ship-unit install-ensure, atomic place, and install orchestrator primitives.

**This is not the payload online installer template.**  
If the product installs **additional packages/toolchains/projects** on empty argv / one-liner, specialize **`template-payload-online-install.md`** (Type O-P) instead — do not stretch this file into domain payload law.

| Product | Template |
|---------|----------|
| CLI place/update only (script-alone) | **This file** (Type O-S) |
| CLI + environment/payload | **`template-payload-online-install.md`** (Type O-P) |

This is often the primary distribution method for CLI tools and must remain extremely robust, secure, and user-friendly.

**Post-install remote lifecycle** (`version-check`, `self-update`, **`self-uninstall`**) is **not** owned here → **`template-self-management.md`**. Self-update **reuses** this template’s install orchestrator and channel; it must not re-fork channel catalogs.

**Remove command naming (ship unit):** After online install, the managed **CLI** remove verb is **`self-uninstall`** (mandatory) — not bare `uninstall` for the ship unit. Rationale: term [`self-uninstall`](../../terminologies/self-uninstall.md). **Payload** remove uses bare **`uninstall`** only under Type O-P (`template-payload-online-install.md`).

**Local-only install (no channel):** do **not** specialize this template — use **`template-shell-local-self-management.md`**.

**Essential companion:** specializing this template classifies the product as **empty-argv Type O-S** (script-alone) unless the product also specializes the **payload** template. Full dual-axis law: **`template-shell-cli-zero-arguments.md`**. **This online-install template makes Type O ship-unit install-ensure mandatory** for one-liner products.

### 1.0 Ownership map (anti-duplication)

### 1.0a Type O install package triad (specialize together)

For a **Type O-S script-alone** online CLI, treat these as one package (all Active, cross-linked):

| Pillar | Law mold | Proves |
|--------|----------|--------|
| **Channel + place** | **This mold** (`LM-ONLINE-INSTALL`) | `curl|sh`, atomic install, channel SSOT |
| **Empty argv** | `LM-SHELL-CLI-ZERO-ARGUMENTS` | Type O install-ensure matrix |
| **Integrity** | `LM-AUTOMATIC-CHECKSUM` | Companion link/value/result |
| **Temps** | `LM-TEMP-FILE-SYSTEM` | Unique stage leaves under isolated `TMPDIR` |
| **Remote lifecycle** | `LM-SELF-MANAGEMENT` | version-check / self-update / self-uninstall |

Missing integrity or zero-arg while claiming online one-liner = incomplete specialize.


| Concern | Owner |
|---------|--------|
| `curl \| sh` / channel composition / pipe bootstrap / install place | **This template** |
| Type O empty-argv matrix depth | `template-shell-cli-zero-arguments.md` (this template **requires Type O-S** ship-unit ensure when specialized alone) |
| Payload online installer (Type O-P) | **`template-payload-online-install.md`** — not this file |
| Companion digest UX (link/value/result) | `template-automatic-checksum.md` |
| Remote version-check / self-update / **`self-uninstall`** (mandatory name) | `template-self-management.md` · term `self-uninstall` |
| Local version / help / about dispatcher | `template-cli-interface.md` |
| Local copy install (no channel) | `template-shell-local-self-management.md` |
| PATH ensure bodies | `template-path-and-shell-support.md` |
| Output SSOT | `template-output-requirements.md` |

**Shared language (terminology):**

| Term | File |
|------|------|
| Online install script | `docs/terminologies/online-install-script.md` |
| Online self-managed | `docs/terminologies/online-self-managed.md` |
| Script URL (install channel) | `docs/terminologies/script-url.md` |
| Repository user | `docs/terminologies/repository-user.md` |
| Repository name | `docs/terminologies/repository-name.md` |
| Shell CLI bootstrap (entry gate) | `docs/terminologies/shell-cli-bootstrap.md` |
| Appname policy | `docs/policies/policy-appname.md` |
| Global installation location (`GLOBAL_BIN`) | `docs/terminologies/global-installation-location.md` |
| Local installation location (`USER_BIN`) | `docs/terminologies/local-installation-location.md` |
| Shell function naming convention (`inst_*` / `path_*`) | `docs/terminologies/shell-function-naming-convention.md` |
| Shell path integration (`.bashrc` PATH ensure) | `docs/terminologies/shell-path-integration.md` |
| Template example function | `docs/terminologies/template-example-function.md` |
| Template example variable | `docs/terminologies/template-example-variable.md` |
| Shell CLI config variables (full catalog) | `docs/terminologies/shell-cli-config-variables.md` |
| Empty argv / zero-arg ensure | `docs/templates/requirements/template-shell-cli-zero-arguments.md` |

**Blank review form:** `docs/templates/checklists/checklist-online-install-script.md`  

**Agent harness (when on disk):** `docs/skills/skill-online-install-self-management.md` — load for implement/review of online install **and** shared install primitives used by self-update (with **`template-self-management.md`**).

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
| **Online install script** | `docs/terminologies/online-install-script.md` | `install-channel` | Primary one-liner vocabulary |
| **Shell CLI bootstrap** | `docs/terminologies/shell-cli-bootstrap.md` | `product-law` | Pipe entry must call main |
| **Script URL** | `docs/terminologies/script-url.md` | `install-channel` | Channel URL |
| **Type O empty argv** | `docs/terminologies/type-o-empty-argv.md` | `product-law` | Empty argv Type O |
| **Automatic checksum mechanism** | `docs/terminologies/automatic-checksum-mechanism.md` | `install-channel` | Companion integrity |
| **Ship unit** | `docs/terminologies/ship-unit.md` | `identity-runtime` | Installed CLI artifact |

**SSOT types used:** `identity-runtime` · `install-channel` · `meta-catalog` · `policy` · `product-law`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Supported Installation Methods

### 2.1 User Installation (Recommended)

```sh
curl -fsSL {{INSTALL_SCRIPT_URL}} | sh
```

### 2.2 System-wide Installation

```sh
curl -fsSL {{INSTALL_SCRIPT_URL}} | sudo sh
```

(Optional equivalent: `wget -qO- {{INSTALL_SCRIPT_URL}} | sh` when documented.)

### 2.3 Channel Config composition (recommended SSOT)

Trusted channel values live in **Config** (env-overridable). Prefer composing the default **script-url** from repository identity + app name when the ship unit is raw GitHub content:

```sh
: "${REPO_USER:=…}"    # specialized product default only (not a real org frozen into this template)
: "${REPO_NAME:=…}"
: "${SCRIPT_URL:=https://raw.githubusercontent.com/${REPO_USER}/${REPO_NAME}/main/${APP_NAME}}"
```

| Variable | Role |
|----------|------|
| `REPO_USER` / `{{REPO_USER}}` | Git owner/org segment — term: [`repository-user`](../../terminologies/repository-user.md) |
| `REPO_NAME` / `{{REPO_NAME}}` | Git repo slug — term: [`repository-name`](../../terminologies/repository-name.md) |
| `APP_NAME` / `{{APP_NAME}}` | Binary / raw path file segment when designed that way |
| `SCRIPT_URL` / `{{SCRIPT_URL}}` / `{{INSTALL_SCRIPT_URL}}` | Full install channel URL — term: [`script-url`](../../terminologies/script-url.md) |

**Override precedence (meaning):**

1. Env / Config **`SCRIPT_URL` already set** → wholesale channel (any host).  
2. Else **composed** default from `REPO_USER` + `REPO_NAME` + `APP_NAME` when composition is designed.  
3. Else empty channel → version-check / self-update network steps **fail loud** (never “already latest”).

**Product README:** When the specialized Config default for `SCRIPT_URL` is **non-empty**, primary Quick Installation uses the **literal expanded URL** (not only `"${SCRIPT_URL}"`). Stars / project-repository home (`https://github.com/…`) is **not** automatically the script body URL.

**Companion integrity path:** `${SCRIPT_URL}.sha256` / `{{INSTALL_SCRIPT_URL}}.sha256` (derived from script-url, not from the GitHub HTML homepage alone).

**Automatic companion-digest depth (transparent link / value / result):** see **`template-automatic-checksum.md`**. Specialize that template when the product claims automatic checksum without requiring an external pin.

---

## 3. Core Requirements

> **Essential pillars (online install is not done until all hold):**  
> 1. **§3.0** Pipe-safe bootstrap (dispatcher actually runs under `curl | sh`)  
> 2. **§3.0a** Empty-argv **install-ensure** for not-installed / local / global (**mandatory**; full depth: `template-shell-cli-zero-arguments.md`)  
> 3. **§3.1–3.3** Atomic install, integrity, user vs system paths  
> 4. **§3.4–3.5** Post-install UX + idempotency (aligned with §3.0a)  
> 5. **If Type O-P:** do **not** complete “online install” using this template alone — specialize **`template-payload-online-install.md`**

### 3.0 Shell CLI bootstrap — entry gate (mandatory)

Online install **fails completely** if the script body is fetched and executed but the **dispatcher never runs**. Under classic one-liner install, the process is a **shell reading stdin**, not an executable named `{{APP_NAME}}`.

| How the user runs it | Typical `${0##*/}` | Entry expectation |
|----------------------|--------------------|-------------------|
| Installed binary / `./{{APP_NAME}}` | Often `{{APP_NAME}}` | Call main |
| `sh /path/to/script` | File basename | Call main |
| `curl … \| sh` / `… \| sudo sh` | **`sh`** / **`bash`** / **`dash`** / … | **Must still call main** |

#### 3.0.1 Forbidden bootstrap patterns

**MUST NOT** gate the only call to the main dispatcher solely on process `$0` matching the product filename or Config app name:

```sh
# FORBIDDEN when this product advertises curl | sh install
if [ "${0##*/}" = "{{APP_NAME}}" ] || [ "${0##*/}" = "{{APP_NAME}}.sh" ]; then
  app_main "$@"
fi
```

Also **FORBIDDEN** as the sole gate (same failure mode):

- Hardcoded product basename only (violates pipe **and** no-hardcode when frozen into reusable docs)
- Comparing `$0` to Config `APP_NAME` alone and treating a miss as “do nothing” (silent no-op)

**Why:** Under `curl | sh`, `$0` is the **interpreter**, not app identity. The gate never matches → **silent success with no install** (false confidence).

**Must not confuse:**

| Concept | Source of truth |
|---------|-----------------|
| **App / binary identity** | Config SSOT `APP_NAME` / `{{APP_NAME}}` (paths, install target name) |
| **Process argv0 under pipe** | Shell name — **not** appname ([`shell-cli-bootstrap.md`](../../terminologies/shell-cli-bootstrap.md)) |

#### 3.0.2 Required bootstrap behavior

For a single-file install CLI that claims online one-liner support:

1. **Entry must invoke** the single dispatcher (e.g. `app_main "$@"`) when the script is executed **or** piped into a shell.  
2. **Preferred:** always call main at end of file for install CLIs (document that `source` is unsupported unless an explicit opt-out exists).  
3. **If a gate remains:** it **MUST** include shell basenames used for piped execution (e.g. `sh`, `bash`, `dash`, `ash`, and login-style variants as needed) **in addition to** product basenames when direct exec is required—and **MUST** fail **loud** (output SSOT) if entry is intentionally refused.  
4. **Empty-argv install-ensure** (§3.0a) lives **inside** the dispatcher **after** bootstrap succeeds—never only behind a basename match that pipe cannot satisfy.  
5. **Regression:** at least one check must feed the script on **stdin** to `sh` (or documented shell) and prove the dispatcher / install-ensure path is entered—not only `./{{APP_NAME}}` direct exec.

Full anti-pattern language: `docs/terminologies/shell-cli-bootstrap.md` and `docs/terminologies/online-install-script.md`.

### 3.0a Empty argv = Type O install-ensure (mandatory / essential)

**Status:** **Essential core requirement** of every online installer that advertises `curl … | sh` (or `… | sudo sh`) with **no trailing command tokens**.  
**Product type:** Specializing this template ⇒ **Type O** in `template-shell-cli-zero-arguments.md` (not Type N help-default).

Without this section, one-liner UX is broken even when bootstrap, checksum, and atomic install are correct: operators re-run the one-liner and get **help**, silence, or a force-required false dependency.

**Full portable SSOT (normative depth):** `docs/templates/requirements/template-shell-cli-zero-arguments.md` § Type O (O-S / O-P).  
**Specialize to:** project `requirement-shell-cli-zero-arguments.md` (or language-prefixed equivalent), mark product type **Type O-S** or **Type O-P**, and cite that requirement from product source—not this template alone.

**Default matrix below is Type O-S (script-alone).** Type O-P products **MUST** apply §3.0b overrides (combined ensure).

#### 3.0a.1 Single meaning of empty argv

| Rule | Requirement |
|------|-------------|
| Empty argv | **MUST** mean **install-ensure**, not `help`, not unknown-command, not silent no-op |
| Explicit help | `help` (or equivalent) remains available when **invoked explicitly** |
| Default fallthrough | Empty argv **MUST NOT** fall through to default `COMMAND=help` after detect says installed |
| Force boundary | `--force` / reinstall policy is for **deliberate replace** only — **MUST NOT** be required solely because the binary already exists |
| Loud outcome | Success and failure **MUST** be visible via output SSOT — silent exit 0 with no binary is forbidden |

#### 3.0a.2 Three detect cases (all mandatory) — Type O-S default

| Case | Detect | Empty argv, force **off** (O-S) | Empty argv / install with force **on** |
|------|--------|--------------------------------|----------------------------------------|
| **A. Not installed** | Install-detect false | **Install** ship unit into privilege-correct path (TTY may confirm; non-TTY / quiet / json **auto**, no hang) | First placement (same as install) |
| **B. Installed — local** | User-path binary present (`{{USER_BIN}}/{{APP_NAME}}`) | **Success no-op**: already installed; **no** re-download; **no** help dump; exit 0 | Deliberate re-download/replace (user path when non-root) |
| **C. Installed — global** | Global-path binary present (`{{GLOBAL_BIN}}/{{APP_NAME}}`) | **Success no-op**: already installed; **no** re-download; **no** help dump; exit 0 | Deliberate re-download/replace (global path when root / elevated) |

**Privilege for Case A placement:**

| One-liner | Typical invoker | Target |
|-----------|-----------------|--------|
| `curl … \| sh` | non-root | `{{USER_BIN}}/{{APP_NAME}}` (e.g. `~/.local/bin`) |
| `curl … \| sudo sh` | root | `{{GLOBAL_BIN}}/{{APP_NAME}}` (e.g. `/usr/local/bin`) |

Detect **MUST** cover **both** local and global when the product supports dual install, so Case B is not misread as Case A (reinstall storm) or Case C ignored.

#### 3.0a.3 Forbidden empty-argv outcomes (online install)

| Forbidden | Why it breaks online install |
|-----------|------------------------------|
| Full help when Case B or C | Looks broken; operators invent `install --force` |
| Silent exit 0 when Case A should install | False confidence (no binary) |
| Silent exit 0 when Case B/C with no “already installed” | Undebuggable one-liner retries |
| Blind re-download every one-liner without force | Breaks idempotency; wasteful |
| Requiring `--force` only because already installed | Force is replace, not ensure |
| Basename gate so pipe never reaches empty-argv branch | §3.0 regression; one-liner dead |

#### 3.0a.4 Equivalence

Empty argv **MUST** share ensure semantics with explicit `install` (same Cases A/B/C). Explicit `install --force` remains the deliberate reinstall path.

#### 3.0a.5 Specialization requirement

Projects that implement this online-install template **MUST**:

1. Keep §3.0a as product law (specialized requirement file registered in `docs/requirements/index.md`).  
2. Wire the dispatcher empty-argv branch before default help.  
3. Regression-test at least: Case A failure (non-zero); Case B or C re-run (not help; O-S already-installed or O-P combined ensure).  
4. State **Type O-S** in Implementation Notes when only this template is specialized. For **Type O-P**, specialize **`template-payload-online-install.md`** (and product requirement `requirement-shell-payload-online-install.md`).

### 3.0b Payload products — pointer only (not owned here)

**Payload online installers (Type O-P)** are defined in **`template-payload-online-install.md`**. That template owns combined ensure, `install`/`uninstall` (payload) vs `self-update`/`self-uninstall` (ship unit), and the payload message matrix. **Do not** implement O-P solely by extending §3.0a Cases B/C no-op text in this file.

### 3.1 Atomic & Safe Installation

- Download to a temporary file using `mktemp` (unique name; no predictable fixed temp path)
- Verify checksum when `CHECKSUM` environment variable is provided
- Automatic verification via `${SCRIPT_URL}.sha256` / `{{INSTALL_SCRIPT_URL}}.sha256` when available
- Atomic move (`mv` / rename) to final location ([`atomic-file-copy`](../../terminologies/atomic-file-copy.md) spirit)
- Set dest mode **0755** on the staging file **before** `mv` (octal `chmod 0755` — **not** `chmod +x`)
- Cleanup staging on failure (`trap` or equivalent where applicable)

`mktemp` staging is typically **0600**. POSIX/GNU `chmod +x` adds execute only, so a normal umask (**022** / **0002**) yields **0711** (`rwx--x--x`). A `#!/bin/sh` dest must be **readable** by the invoking user: `/bin/sh` opens the file. **0711** / **0700** on `{{GLOBAL_BIN}}/{{APP_NAME}}` makes `sudo {{APP_NAME}}` work (owner read) while unprivileged `{{APP_NAME}}` prints `/bin/sh: 0: cannot open …: Permission denied`. `chmod 0755` ignores umask. **MUST NOT** fall back to `chmod +x`. Gate: **`CL-ONLINE-INSTALL-SCRIPT`** §4 · proof **`TP-LC-10`**. Pain **PP-A-28**. **MUST NOT** reuse **`TP-LC-23`** / **`TP-LC-24`** (zsh PATH when claimed).

**Global dest is the blocking class.** Owner-read on `{{USER_BIN}}` hides 0711. Proof **MUST** include isolated **`{{GLOBAL_BIN}}`** (**`TP-LC-10`**) and **`self-update`** of that dest (**`TP-LC-25`**). `sudo` success is not unprivileged proof.

### 3.2 Checksum Protection

- **Default:** automatic verification via companion `.sha256` when pin unset (primary path) — depth in **`template-automatic-checksum.md`** (transparency: show companion **link**, expected **value**, **result**)
- If process env pin (e.g. `CHECKSUM=<sha256>`) is set → **strict** verification (**secondary** / install-path runtime only)
- Fail **loudly** on mismatch (security requirement; non-zero exit; output SSOT)
- Product docs **MUST NOT** push env-first / same-origin pin as the primary story when automatic mode exists
- **`help` / `about` MUST NOT** list or print the pin env name/value (avoids misunderstanding; see automatic-checksum template)

### 3.3 User vs System Installation Logic

- Non-root → **local installation location**; root → **global installation location** (defaults + **full shell variable inventories** live only in those glossary terms — do not fork second catalogs here).
- After **user-bin** install: optional **shell-path-integration** — full `path_add_*` examples only in `template-path-and-shell-support.md` §3.1.
- Binary **name** from Config / `APP_NAME` SSOT — not pipe `$0`.
- Install orchestrator functions use `inst_*` prefix ([shell-function-naming-convention](../../terminologies/shell-function-naming-convention.md)).
- Channel-only vars (`SCRIPT_URL`, `REPO_*`, `CHECKSUM`) are **not** install-directory vars (see [shell-cli-config-variables](../../terminologies/shell-cli-config-variables.md)).

### 3.4 Post-Install Actions

- Update shell configuration for PATH when user-bin install requires it
- Print clear success message with next steps (via output SSOT)
- **Zero-argument one-liner** behavior is **§3.0a** (install-ensure for not-installed / local / global)—not only “auto when not installed”
- Non-interactive / quiet / json: **never hang** on prompts ([`interactive-vs-noninteractive`](../../terminologies/interactive-vs-noninteractive.md))

### 3.5 Idempotency

- Already installed (local **or** global) → success no-op on empty argv / `install` unless force/reinstall policy is set (**§3.0a** Cases B/C)
- Re-run of one-liner must not dump help, require force, corrupt install, or leave partial binaries ([`idempotency-rule`](../../terminologies/idempotency-rule.md); full empty-argv matrix: `template-shell-cli-zero-arguments.md`)

### 3.6 Example variables and functions (portable — Type 0 shell CLI online install)

**Kinds:** [template-example-variable](../../terminologies/template-example-variable.md) · [template-example-function](../../terminologies/template-example-function.md).  
**Not product law.** Specialize into live requirements + ship unit. Product ALIGNMENT cites requirements only.

#### 3.6.1 Online-install Config variables (channel + install op)

Full catalogs: [shell-cli-config-variables](../../terminologies/shell-cli-config-variables.md), location terms. **This section owns channel + install-op examples.**

| Variable | Family | Role | Portable default pattern |
|----------|--------|------|--------------------------|
| `APP_NAME` | identity | Binary / raw file segment | hard-assign + `: "${APP_NAME:=app}"` |
| `VERSION` | identity | Local version SSOT; seed for `REMOTE_VERSION` | hard-assign |
| `REPO_USER` | channel | Git owner for composed URL | `: "${REPO_USER:=…}"` (specialize; empty in mold) |
| `REPO_NAME` | channel | Git repo for composed URL | `: "${REPO_NAME:=…}"` |
| `SCRIPT_URL` | channel | Full install channel URL | composed or wholesale env override |
| `CHECKSUM` | integrity | Optional strict pin (secondary) | empty default; not help/about |
| `REMOTE_VERSION` | install op | Version string for install messaging / compare | empty until fetch; else `$VERSION` |
| `FORCE_REINSTALL` | install op | Force re-download/replace | `0` |
| `INST_AUTO_CHECKSUM_OK` | install op | Internal: companion matched | `0` |
| `HOME` | path root | Before `USER_BIN` | resolve under `set -u` |
| `GLOBAL_BIN` / `USER_BIN` | path | Install directories | see location terms |
| `INSTALL_PATH` | path | Resolved full target path | privilege-selected |
| `IS_ROOT` | path | Privilege selector | from `id -u` |
| `JSON` / `QUIET` / `FORCE` | mode | Output / force | `0` |
| `SH` | UX | Shell name in recommended one-liner | `sh` |

**Channel composition example (template-example-variable):**

```sh
# Specialize REPO_* / SCRIPT_URL in product Config — not frozen brands in this mold.
: "${REPO_USER:=}"
: "${REPO_NAME:=}"
: "${APP_NAME:=app}"
: "${SCRIPT_URL:=}"
# When product designs GitHub raw composition (after specialize):
# : "${SCRIPT_URL:=https://raw.githubusercontent.com/${REPO_USER}/${REPO_NAME}/main/${APP_NAME}}"
: "${CHECKSUM:=}"
: "${FORCE_REINSTALL:=0}"
: "${REMOTE_VERSION:=}"
: "${INST_AUTO_CHECKSUM_OK:=0}"
: "${HOME:=/tmp}"
: "${GLOBAL_BIN:=/usr/local/bin}"
: "${USER_BIN:=${HOME}/.local/bin}"
if [ "$(id -u 2>/dev/null || echo 1)" -eq 0 ]; then
    IS_ROOT=1
    INSTALL_PATH="${GLOBAL_BIN}/${APP_NAME}"
else
    IS_ROOT=0
    INSTALL_PATH="${USER_BIN}/${APP_NAME}"
fi
: "${IS_ROOT:=0}"
```

#### 3.6.2 Online-install function inventory (Type 0 shell CLI)

| Function | Role | Example depth here |
|----------|------|--------------------|
| `inst_perform_install` | Orchestrator: detect → prepare → download → atomic | **Sketch** (§3.6.3) |
| `inst_perform_install_prepare_target` | Ensure `GLOBAL_BIN` or `USER_BIN` exists | **Full sketch** |
| `inst_perform_install_download_with_checksum` | curl/wget + strict `CHECKSUM` | **Sketch** |
| `inst_perform_install_download_without_checksum` | curl/wget + optional `${SCRIPT_URL}.sha256` | **Sketch** |
| `inst_perform_install_atomic_install` | dest-mode `chmod` + `mv` + optional `path_add_shell` | **Sketch** (mode from **`LM-SHELL-CLI-SELF-INSTALL`** `inst_cli_dest_mode`) |
| `inst_maybe_install` | TTY confirm when not installed | Peer: **`LM-INTERACTIVE-VS-NONINTERACTIVE`** |
| `inst_self_install` / `$0` copy / dest helper | CLI self-place (copy vs download) | Peer: **`LM-SHELL-CLI-SELF-INSTALL`** — **do not fork here** |
| `inst_is_installed` / `inst_get_version` | Detect / read installed VERSION | Peer: self-management template |
| `util_sha256_file` | Portable SHA-256 of a file | **Full sketch** |
| `util_fetch_remote_version` | Fetch remote `VERSION="…"` from channel | **Full sketch** |
| `util_get_install_bin_path` | Privilege path resolve | Peer: local-self-management §9.3 |
| `path_add_shell` | User PATH after install | **Owner:** path template §3.1 only |
| `out_*` | All messages | **Owner:** output template §3.1 only |

#### 3.6.3 Example function sketches (portable)

```sh
# --- util_sha256_file: class B return (digest for capture) ---
util_sha256_file() {
    local file="${1-}" dig=""
    [ -n "${file}" ] && [ -f "${file}" ] || return 1
    if command -v sha256sum >/dev/null 2>&1; then
        dig=$(sha256sum "${file}" 2>/dev/null | awk '{ print $1; exit }')
    elif command -v shasum >/dev/null 2>&1; then
        dig=$(shasum -a 256 "${file}" 2>/dev/null | awk '{ print $1; exit }')
    elif command -v openssl >/dev/null 2>&1; then
        dig=$(openssl dgst -sha256 "${file}" 2>/dev/null | awk '{ print $NF; exit }')
    else
        return 1
    fi
    [ -n "${dig}" ] || return 1
    printf '%s\n' "${dig}"
}

# --- util_fetch_remote_version: class B return from SCRIPT_URL body ---
util_fetch_remote_version() {
    local url="${1-}" body=""
    [ -n "${url}" ] || return 1
    if command -v curl >/dev/null 2>&1; then
        body=$(curl -fsSL "${url}" 2>/dev/null) || body=""
    elif command -v wget >/dev/null 2>&1; then
        body=$(wget -qO- "${url}" 2>/dev/null) || body=""
    else
        return 1
    fi
    [ -n "${body}" ] || return 1
    printf '%s\n' "${body}" | grep '^VERSION="' | head -n1 | cut -d'"' -f2
}

# --- inst_perform_install_prepare_target ---
inst_perform_install_prepare_target() {
    : "${IS_ROOT:=0}"
    : "${GLOBAL_BIN:=/usr/local/bin}"
    : "${USER_BIN:=${HOME}/.local/bin}"
    if [ "${IS_ROOT}" -eq 1 ]; then
        mkdir -p "${GLOBAL_BIN}" 2>/dev/null || {
            out_error "Failed to create ${GLOBAL_BIN}"
            return 1
        }
    else
        mkdir -p "${USER_BIN}" 2>/dev/null || {
            out_error "Failed to create ${USER_BIN}"
            return 1
        }
    fi
    return 0
}

# --- inst_perform_install: orchestrator sketch (protection zone in products) ---
inst_perform_install() {
    : "${FORCE_REINSTALL:=0}"
    : "${SKIP_DOMAIN_START:=0}"
    : "${CHECKSUM:=}"
    : "${SCRIPT_URL:=}"
    : "${VERSION:=0.0.0}"
    : "${REMOTE_VERSION:=}"
    : "${JSON:=0}"

    if [ "$(id -u)" -eq 0 ]; then
        IS_ROOT=1
        INSTALL_PATH="${GLOBAL_BIN}/${APP_NAME}"
    else
        IS_ROOT=0
        INSTALL_PATH="${USER_BIN}/${APP_NAME}"
    fi
    : "${REMOTE_VERSION:=${VERSION}}"

    if inst_is_installed && [ "${FORCE_REINSTALL}" -eq 0 ]; then
        out_success "${APP_NAME} is already installed."
        return 0
    fi
    inst_perform_install_prepare_target || return 1

    local tmp_file downloaded_checksum_ok=0
    tmp_file=$(mktemp -t "${APP_NAME}.XXXXXX") || return 1

    if [ -n "${CHECKSUM}" ]; then
        # Strict pin path: download + util_sha256_file match CHECKSUM or fail loud
        # inst_perform_install_download_with_checksum "${tmp_file}" || { rm -f "${tmp_file}"; return 1; }
        downloaded_checksum_ok=1
    else
        # Automatic companion: fetch SCRIPT_URL then best-effort SCRIPT_URL.sha256
        # inst_perform_install_download_without_checksum "${tmp_file}" || { rm -f "${tmp_file}"; return 1; }
        :
    fi

    # Atomic: dest-mode chmod (inst_cli_dest_mode: 0755 global / 0700 local) + mv.
    # MUST NOT chmod +x on mktemp 0600 (0711). Body of dest helper: LM-SHELL-CLI-SELF-INSTALL.
    # inst_perform_install_atomic_install "${tmp_file}" "${downloaded_checksum_ok}" || { rm -f "${tmp_file}"; return 1; }
    # Domain auto-start is NOT CLI-place success. self-update sets SKIP_DOMAIN_START=1.
    # if [ "${SKIP_DOMAIN_START}" -ne 1 ]; then domain_start_after_install; fi
    return 0
}

# --- inst_perform_install_atomic_install (dest mode from peer helper) ---
inst_perform_install_atomic_install() {
    local tmp_file="$1"
    local downloaded_checksum_ok="${2:-0}"
    local _mode
    _mode=$(inst_cli_dest_mode)
    chmod "${_mode}" "${tmp_file}" 2>/dev/null || true
    rm -f "${INSTALL_PATH}" 2>/dev/null
    mv "${tmp_file}" "${INSTALL_PATH}" || {
        rm -f "${tmp_file}"
        out_error "Failed to move to ${INSTALL_PATH}"
        return 1
    }
    chmod "${_mode}" "${INSTALL_PATH}" 2>/dev/null || true
    [ "${IS_ROOT:-0}" -eq 0 ] && path_add_shell
    out_success "${APP_NAME} successfully installed to ${INSTALL_PATH}"
    return 0
}
```

**Download helpers (normative behavior — implement fully in product):**

| Helper | Behavior |
|--------|----------|
| `…_download_with_checksum` | `curl -fsSL` or `wget` → `${SCRIPT_URL}`; `util_sha256_file` must equal `CHECKSUM` or **abort** (no final binary) |
| `…_download_without_checksum` | Download body; if companion `${SCRIPT_URL}.sha256` present, verify (set `INST_AUTO_CHECKSUM_OK=1` on match); mismatch → **abort**; missing companion → warn + continue only if product law allows |
| `…_atomic_install` | `inst_cli_dest_mode` (`0755` global / `0700` local; not `chmod +x`) → `mv` onto `INSTALL_PATH`; user install → optional `path_add_shell` |

**Do not re-copy:** full `out_*` → output template §3.1; full `path_add_*` → path template §3.1; local-only copy install → `template-shell-local-self-management.md`.

---

## 4. Why This Requirement Exists (Direct CIAO Alignment)

- **CIAO Principle 1 – Caution** (https://github.com/cloudgen/ciao): Network downloads can be tampered with. Checksum verification and atomic operations protect against corruption and attacks. Entry gates that silently skip main, and empty-argv paths that dump help when already installed, are also Caution failures (false confidence / wrong operator action).
- **CIAO Principle 2 – Intentional** (https://github.com/cloudgen/ciao): Clear separation between user and system installation paths prevents permission issues. App identity vs process `$0` must stay intentional and separate. Empty argv has one intentional meaning: install-ensure.
- **CIAO Principle 3 – Anti-fragile** (https://github.com/cloudgen/ciao): Must work reliably on fresh systems, minimal containers, Alpine Linux, behind proxies, under stdin pipe execution, **and** on one-liner re-runs when local or global install already exists—not only first-time Case A.
- **CIAO Principle 5 / 14 – Entry + modes** (https://github.com/cloudgen/ciao): Dispatcher owns empty argv before help; non-interactive one-liner never hangs.
- **CIAO Principle 4 / CIAO-Lite O · Principle 20 – Over-protect / Protect Against AI** (https://github.com/cloudgen/ciao): Multiple layers of verification, safe temporary file handling, pipe-safe bootstrap, and **mandatory empty-argv case matrix** defend against installation failures and false confidence.

---

## 5. Design Principles (CIAO / CIAO-Lite)

- **Caution:** Checksum verification, atomic install, **loud** failure on integrity or entry refusal, clear already-installed success on re-run.
- **Intentional:** User vs system paths; Config owns `APP_NAME`; bootstrap owns “call main”; empty argv owns install-ensure (not help).
- **Anti-fragile:** Fresh systems, minimal shells, **curl \| sh**, dual path detect, optional wget path.
- **Over-protect:** Temp safety, checksum layers, PATH handling, pipe-safe entry, §3.0a matrix, regression for stdin + already-installed.

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

**This mold:** channel is user `curl | sh`, never `sudo curl | sh`; place into this-login `USER_BIN`.

---

## 6. Protection Rule (Sacred)

**Future AI assistants, Grok, or maintainers MUST NOT**:

- Remove checksum verification logic (both explicit `CHECKSUM` and `.sha256` support)
- Change the atomic install pattern (temp file → verify → `chmod 0755` → `mv`) without an explicit redesign order
- Use **`chmod +x` alone** (or `chmod 0755 \|\| chmod +x`) on `mktemp` staging for a `#!/bin/sh` dest (`mktemp` 0600 + `chmod +x` → **0711**; interpreter cannot open; unprivileged `Permission denied`)
- Treat **`{{USER_BIN}}` dest 0755** as proof that a **global** shebang dest is readable — the blocking class is **`{{GLOBAL_BIN}}`** (**TP-LC-10** install · **TP-LC-25** self-update)
- Remove PATH addition for user binary directory when user-bin install is supported
- Simplify or remove user vs system installation logic without explicit redesign
- Break `curl | sh` compatibility in any way
- Remove or weaken safe temporary file handling using `mktemp`
- **Remove, weaken, or “simplify away” §3.0a empty-argv install-ensure** (not-installed / local / global) without an explicit redesign order and specialized requirement change
- Implement Type O-P payload one-liner behavior **only** in this template without specializing `template-payload-online-install.md`
- Route empty argv to **help** when the product advertises a zero-arg one-liner (Case B/C must not dump usage)
- Require `--force` solely because detect says already installed (local or global)
- Handle only “not installed” empty-argv and leave already-installed as accidental help fallthrough
- Detect only global **or** only local when dual install is supported, so the wrong §3.0a case runs
- **Gate the only call to the main dispatcher solely on `${0##*/}` equaling `{{APP_NAME}}` / `{{APP_NAME}}.sh` (literal or Config-backed) when online one-liner install is advertised**
- Treat process `$0` under a piped shell as Config **app name** / binary identity
- Leave a failed or skipped one-liner entry as a **silent success** (no install, exit 0, no error / no message)
- Put **toy install hosts** (`example.com`, `your-domain`, `changeme`) in product user Install docs when online install is in scope
- Soft-frame product Install as “when you publish only” while the binary already implements the method
- Apply no-hardcode to **product README** as a reason to omit or fake this project’s install URL/method
- Document only the non-root one-liner when the product also implements a root/elevated path (or claim both without implementing)
- Leave product install docs out of sync with `help` / `about` / installer-emitted recommended commands
- When Config default for `SCRIPT_URL` / `{{INSTALL_SCRIPT_URL}}` is **non-empty**, omit a **simple literal** product one-liner `curl -fsSL <that URL> | sh` (and elevated shape when implemented) or force env-only `"${SCRIPT_URL}"` as the primary newcomer path
- When channel composition is designed (`REPO_USER` / `REPO_NAME` → `SCRIPT_URL`), scatter ad-hoc owner/repo/URL strings outside Config SSOT, or document a homepage HTML URL as if it were the script body
- Use live HTTP **404** or “not yet committed” to strip a Config-default / owner-planned channel URL from product docs
- When automatic companion-digest verification is implemented (e.g. `${SCRIPT_URL}.sha256` when pin unset), omit product README documentation of algorithm, automatic-when-unset, and match/mismatch/missing outcomes
- List or print optional pin env (`CHECKSUM` / equivalent) in **`help` or `about`** when automatic companion mode is the primary integrity path
- Strip the **Under command line for normal user only** section, or recommend `sudo curl | sh` on Termux / Git Bash
- Fail CLI **install** / **self-update** after a successful binary place because a **host daemon config test** failed (typical: `sshd -t` of `/etc/ssh/sshd_config`, missing `/run/sshd`)
- Ignore `SKIP_DOMAIN_START` (or equivalent) when `self-update` reuses this orchestrator — **`LM-SELF-MANAGEMENT`** §5.3
- Rewrite host daemon config (`/etc/ssh/sshd_config` or product equivalent) as a side effect of CLI place

**The one-liner online installation is one of the most important user-facing features and must be defended aggressively—including the bootstrap entry gate, §3.0a empty-argv install-ensure, §3.0b payload combined ensure when Type O-P, and product install-doc truth (Config channel SSOT → simple README one-liner).**

---

## 7. Verification (minimum)

| Check | Intent |
|-------|--------|
| `curl -fsSL {{INSTALL_SCRIPT_URL}} \| sh` (or local `sh < script` / `cat script \| sh`) when **not** installed | Case A: enters install path; places binary or clear interactive confirm; failure → non-zero; **visible messages** |
| Same (Type O-P) | Case A also **enters payload ensure** after ship unit; does not exit binary-only |
| Same one-liner when **local** install already present (force off) | O-S: already-installed success; O-P: upgrade policy + payload ensure; **not** help |
| Same one-liner (or elevated) when **global** install already present (force off) | Same as local case for global path |
| Direct `./{{APP_NAME}}` or path exec after install | Lifecycle commands still work; explicit `help` still works |
| Already installed + `install` (no force) | Same ensure semantics as empty argv for that product type |
| `install --force` / documented reinstall only when deliberate replace is intended | Force boundary respected |
| Bad `CHECKSUM` | Loud fail; no corrupt final binary |
| Non-interactive (pipe / quiet / json) | No hang on prompts |
| Empty/failed curl feed to shell | Does **not** look like successful product install (prefer non-zero / loud fail) |
| Dest mode after atomic place | **0755** (other-read + exec). Isolated **`GLOBAL_BIN`** (**`TP-LC-10`**) and global **`self-update`** (**`TP-LC-25`**). USER_BIN-only does **not** close the class. `sudo` success is not unprivileged proof |

Use blank form: `docs/templates/checklists/checklist-online-install-script.md` (section on empty argv / zero-arg is **blocking**).

---

## 8. No-hardcode (this template)

This template is **project-independent**. Use `{{APP_NAME}}`, `{{REPO_USER}}`, `{{REPO_NAME}}`, `{{INSTALL_SCRIPT_URL}}`, `{{USER_BIN}}`, `{{GLOBAL_BIN}}`, `{{SCRIPT_URL}}`. Do not freeze one product’s binary brand, release host, owner/repo, or machine path as universal law. Specialize real URLs and names in project `requirement-*.md` Implementation Notes, product root **`README.md` / `CHANGELOG.md`** (both **excluded from no-hardcode**), and Config/code SSOT—not by baking brands into this template.

**Product docs exception (defensive):** When specializing for a project that implements this template’s method, product user docs **must** document the real install surfaces (user and elevated one-liners if both exist). **Read Config first:** resolve composed or literal `SCRIPT_URL` / `{{INSTALL_SCRIPT_URL}}` (including `REPO_USER` / `REPO_NAME` when composition is used). If default is **non-empty**, product README **must** show simple literal one-liners using that URL; if **empty**, document empty + how to set—never `example.com`. Checksum modes may sit under Advanced. Pre-publish 404 does not veto Config/owner channel. See `docs/terminologies/online-install-script.md` § Product docs alignment; `docs/terminologies/script-url.md`; `docs/skills/skill-write-readme.md`. Doc-side bullets live in §6 Protection Rule.

---


## Design-time verification

| TP family / ID | Proof mold | Planned suite |
|----------------|------------|---------------|
| **TP-LC-*** install lifecycle | `../tests/template-install-lifecycle-test-plan.md` | `tests/test_install_lifecycle.sh` |
| **TP-LC-10** shebang dest mode 0755 (global install) | same | `tests/test_install_lifecycle.sh` |
| **TP-LC-25** global dest 0755 after `self-update` | same | `tests/test_install_lifecycle.sh` |
| **CL-ONLINE-INSTALL-SCRIPT** §4 dest mode | `../checklists/checklist-online-install-script.md` | review gate (not a suite) |
| **TP-CURL-*** pipe one-liner | `../tests/template-online-curl-install-test-plan.md` | `tests/test_online_curl_install.sh` |
| **TP-CSUM-*** companion / pin | `../tests/template-checksum-test-plan.md` | CLI + lifecycle |

**RTM:** `../tests/template-requirement-test-traceability.md`

**Last Updated**: 2026-09-17 (v1.13.0 dest mode via `inst_cli_dest_mode`)  
**Owner**: Installation & Distribution Layer (Generalized Template)  
**Version history:**  
- **1.13.0** (2026-09-17): Atomic place uses **`inst_cli_dest_mode`** (0755/0700); self-place family owned by **`LM-SHELL-CLI-SELF-INSTALL`**.  
- **1.12.1** (2026-09-15): Isolated **`GLOBAL_BIN`** dest **0755** is Core (**TP-LC-10** install, **TP-LC-25** self-update). USER_BIN-only does not close the class. **MUST NOT** `chmod +x` fallback.  
- **1.12.0** (2026-09-15): Shebang dest-mode proof id **`TP-LC-10`** (was colliding with zsh **`TP-LC-23`**). Pain **PP-A-28**. Location terms own dest mode **0755**.  
- **1.11.0** (2026-09-09): CLI place vs domain/host daemon start; orchestrator honors `SKIP_DOMAIN_START`; **MUST NOT** fail CLI install/`self-update` on host daemon config test; **MUST NOT** rewrite that config as a place side effect.  
- **1.9.0** (2026-07-20): This template = **Type O-S script-alone only**; Type O-P moved to `template-payload-online-install.md`.  
- **1.8.0** (2026-07-20): Interim §3.0b payload notes (superseded by dedicated payload template in 1.9.0).  
- **1.6.0** (2026-07-17): **§3.6** template-example-variable (channel/path install vars) + template-example-function (util_sha256_file, util_fetch_remote_version, prepare_target, install orchestrator sketch).  
- **1.5.1** (2026-07-14): Scope note — this template is the **sole** harness authority that makes empty-argv install-ensure mandatory; general CLI templates must not.  
- **1.5.0** (2026-07-14): **§3.0a Empty argv = install-ensure** elevated to **essential core** of online install (not-installed / local / global); mandatory companion `template-shell-cli-zero-arguments.md`; Protection Rule + verification + pillar list.  
- **1.4.0** (2026-07-13): Channel composition `REPO_USER` / `REPO_NAME` → `SCRIPT_URL` (raw GitHub content shape); terms script-url / repository-user / repository-name; Protection Rule + no-hardcode placeholders.  
- **1.3.0** (2026-07-12): Config channel SSOT → simple product one-liner; ban 404 veto; Protection Rule docs bullets.  
- **1.2.0** (2026-07-12): Product docs alignment exception; ban toy hosts in specialized install docs; Protection Rule docs bullets; README specialization pointer.  
- **1.1.0** (2026-07-12): Shell CLI bootstrap section (§3.0); forbid `$0`/appname entry gate; verification + checklist link; terminology links; no-hardcode note.  
- **1.0.0**: Initial generalized online-install template.  

**Alignment**: `online-install-script`, `script-url`, `online-self-managed`, `template-example-function`, `template-example-variable`, `shell-cli-config-variables`, location terms, `shell-cli-bootstrap`, `skill-write-template` (example rules), `skill-online-install-self-management`, `template-shell-cli-zero-arguments`, `template-self-management`, `template-path-and-shell-support` §3.1, `template-output-requirements` §3.1, checklist-online-install-script; CIAO v2.10.2.

---

**How to use this template**:

1. Keep this file under `docs/templates/requirements/` as the reusable pattern (placeholders stay).  
2. Specialize project facts in `docs/requirements/requirement-*.md` Implementation Notes / Config **and** product README install truth—not by baking brands into this template.  
3. **Specialize and register** empty-argv law from `template-shell-cli-zero-arguments.md` → `requirement-shell-cli-zero-arguments.md` (or equivalent); mark **Type O-S or Type O-P**; implement §3.0a (and §3.0b if O-P) in the dispatcher.  
4. Implement atomic download + checksum + **pipe-safe bootstrap** using **§3.6** examples + product protection zones.  
5. Support user and system installation paths with PATH handling (`path_add_*` from path template only).  
6. Run `docs/templates/checklists/checklist-online-install-script.md` before claiming install-path done (**§2 zero-arg is blocking**).  
7. Keep the Protection Rule, §3.0a, and checksum requirements intact.  
8. Align product Install docs with implemented one-liners (no toy hosts).
