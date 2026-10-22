---
name: self-management
id: LM-SELF-MANAGEMENT
kind: law-mold
description: >
  Portable law mold. Cite as LM-SELF-MANAGEMENT (path secondary).
---

**file**: template-self-management.md  
**Status**: Active (Version 2.8.2 – self-place family points at **LM-SHELL-CLI-SELF-INSTALL**)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered / Over-protect)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

## 1. Purpose

This template defines **online self-managed** **post-install remote lifecycle** for a CIAO-Lite CLI:

- **`self-install`** — place/ensure the **CLI** (first shot = `curl \| sh` / Type O; room for payload)  
- **`version-check`** — compare local ship-unit version to **remote/latest** on the install channel  
- **`self-update`** — re-fetch from channel (atomic + integrity; reuse install orchestrator)  
- **`self-uninstall`** — remove the **CLI** with confirm / `--force` fail-closed  

It does **not** re-own first-time online install, Type O empty-argv, channel composition, companion-digest algorithms, PATH rc bodies, or local-only copy install. Those live in peer templates (see §2–§3).

**Specialize into:** `requirement-shell-self-management.md` (or project-chosen key) with filled Implementation Notes.

**Do not use this template when** the product is **non-online-installable** (alias **local-only**; no remote channel) — use **`template-shell-local-self-management.md`** instead.

---

## Terminologies (mandatory)

| Term | Path | SSOT type | Role in this template |
|------|------|-----------|------------------------|
| **Where-is-me** | `docs/terminologies/where-is-me.md` | `product-law` | Path-report command (no install mutate) |

| **Project templates** | `docs/terminologies/project-templates.md` | `meta-catalog` | What law molds are; specialize-out target |
| **Docs folder structure** | `docs/terminologies/docs-folder-structure.md` | `policy` | Where this mold lives vs product law / tests |
| **No-hardcode policy** | `docs/terminologies/no-hardcode-policy.md` | `policy` | Placeholders only in portable molds |
| **Dual policies** | `docs/terminologies/dual-policies.md` | `policy` | No-placeholder × no-hardcode balance |
| **Terminology policy for templates** | `docs/terminologies/terminology-policy-for-templates.md` | `policy` | Mandatory Terminologies section rules |
| **SSOT-terminology policy for templates** | `docs/terminologies/ssot-terminology-policy-for-templates.md` | `policy` | SSOT type column on rows || Online self-managed | `docs/terminologies/online-self-managed.md` | product-law / lifecycle mode | **Primary mode** this template implements |
| Self-uninstall | `docs/terminologies/self-uninstall.md` | product-law / command naming | **Mandatory** online remove command name + CLI vs payload |
| Self-management | `docs/terminologies/self-management.md` | product-law / umbrella | Parent vocabulary |
| Online install script | `docs/terminologies/online-install-script.md` | install-channel / distribution | First-time / pipe install (peer) |
| Script URL | `docs/terminologies/script-url.md` | install-channel | Channel URL SSOT (**consume**, do not re-catalog) |
| Repository user / name | `docs/terminologies/repository-user.md`, `repository-name.md` | identity-docs / channel composition | Channel composition inputs (peer online-install) |
| Automatic checksum mechanism | `docs/terminologies/automatic-checksum-mechanism.md` | install-channel / integrity | Companion digest on fetch (peer checksum template) |
| Type O empty argv | `docs/terminologies/type-o-empty-argv.md` | runtime-mode | Empty-argv install-ensure (peer zero-arg + online-install) |
| Ship unit | `docs/terminologies/ship-unit.md` | product artifact | Binary/script lifecycle manages |
| Global / local installation location | location terms | identity-runtime / path | Managed bin destinations (**consume**) |
| Shell path integration | `docs/terminologies/shell-path-integration.md` | runtime-mode / UX | Optional PATH reverse on uninstall |
| Shell function naming convention | `docs/terminologies/shell-function-naming-convention.md` | meta / naming | `inst_*` / `ver_*` / `app_*` |
| Shell CLI config variables | `docs/terminologies/shell-cli-config-variables.md` | meta / config catalog | Full var inventory pointer |
| Local self-managed | `docs/terminologies/local-self-managed.md` | product-law / lifecycle mode | **Contrast** mode |
| **Where-is-me** | `docs/terminologies/where-is-me.md` | `product-law` | Optional path report (either mode) |
| Idempotency rule | `docs/terminologies/idempotency-rule.md` | product-law / re-run | Already-latest / already-uninstalled |
| Interactive vs noninteractive | `docs/terminologies/interactive-vs-noninteractive.md` | runtime-mode | Uninstall confirm vs `--force` |

---

## 2. Feature package (normative understanding)

Agents specializing an **online** Type 0 CLI **MUST** treat the product as a **multi-template package**, not a single monolithic self-management file.

### 2.1 Layer A — Online remote lifecycle (**this template owns**)

| Feature | Command | Meaning |
|---------|---------|---------|
| Self-install | **`self-install`** | Place/ensure the **CLI** (pipe first shot is the same ensure) — term `self-install` |
| Remote version-check | `version-check` | Local `VERSION` vs **remote** latest on channel |
| Self-update | `self-update` | Fetch channel → atomic replace when newer (or `--force`) |
| Self-uninstall | **`self-uninstall`** (**MUST** this exact user-facing name) | Remove the **CLI**; confirm / force; safe PATH reverse — see term `self-uninstall` |

### 2.2 Layer B — Local diagnostics (**CLI interface owns**; still required companions)

| Feature | Command | Meaning |
|---------|---------|---------|
| **Local version** | `version` | Ship-unit `VERSION` only — **no** network |
| About | `about` | Diagnostics; channel presence OK; **no** CHECKSUM pin theater if companion is primary |
| Help | `help` | Lists online package commands honestly |

### 2.3 Layer C — Online install channel (**online-install + peers own**)

| Feature | Owner template | This template |
|---------|----------------|---------------|
| `curl \| sh` one-liner / pipe bootstrap | `template-online-install.md` | **Consume** (must exist for full online product) |
| Type O empty-argv install-ensure | `template-shell-cli-zero-arguments.md` + online-install §3.0a | **Out of ownership** (point only) |
| `SCRIPT_URL` / `REPO_*` composition | `template-online-install.md` §2.3 | **Consume**; empty channel → fail loud on network steps |
| Download + companion `.sha256` | `template-online-install.md` + `template-automatic-checksum.md` | **Reuse** on self-update; do not re-fork algorithms |
| Explicit channel `install` command | online-install / CLI interface | May share orchestrator with self-update |

### 2.4 Layer D — Shared infrastructure (**consume, do not re-own**)

| Concern | Owner |
|---------|--------|
| Output `out_*` | `template-output-requirements.md` |
| Uninstall confirm / non-interactive | `template-interactive-vs-noninteractive.md` (+ uninstall rules here) |
| Idempotency (already-latest, already-uninstalled) | `template-idempotency.md` |
| PATH ensure / reverse bodies | `template-path-and-shell-support.md` (**`LM-PATH-AND-SHELL-SUPPORT`** — bashrc create/modify/no-op + **TP-LC-20..22** when claimed) |
| Bin path defaults | location glossary terms |
| Privilege path resolve helpers | naming convention + location terms; example sketches may live in **one** place only |

### 2.5 Layer E — Local self-managed contrast (**not this mode**)

| Local mode feature | Local template |
|--------------------|----------------|
| Local copy `install` / `uninstall` / `where-is-me` | `template-shell-local-self-management.md` |
| No remote channel | Local template package |
| Type N empty argv (typical) | zero-arg template |

**Dual-mode products** (rare / **discouraged**): Active **both** local and online install. **Default recommendation: stick to online-install only** when a channel exists. Dual-mode only if the user insists **and** a dual-mode matrix is filled (primary path, empty argv, `uninstall` vs `self-uninstall`, refresh) — never silent half-live channel. See requirement skill install-mode gate.

### 2.6 Must not confuse

| Feature | Answers | Network | Owner |
|---------|---------|---------|-------|
| **Local `version`** | What version is **this file**? | No | CLI interface |
| **`version-check`** | Is channel **newer** than local? | Yes | **This template** |
| **`self-update`** | Fetch/replace from channel | Yes | **This template** |
| **`self-uninstall`** | Remove managed install (**online** remove name **MUST**) | No (local disk only) | **This template** · term `self-uninstall` |
| **Local `install` / `uninstall`** | Place/remove from **running ship unit** (local pair) | No | Local self-management — **not** this template |
| **Online `install` / pipe** | Fetch channel to bin | Yes | Online-install template |

**Naming fence:** Online packages use **`self-uninstall`** (never bare `uninstall` as primary). Local packages use **`install` + `uninstall`** (never `self-uninstall` / `self-update` as primary).

### 2.7 Full online Type 0 command package (recommended inventory)

| Command | Layer | Owner surface |
|---------|-------|---------------|
| *(empty argv — Type O)* | C | zero-arg + online-install |
| `install` (channel) | C | online-install + CLI route |
| `version-check` | A | **this template** |
| `self-update` | A | **this template** |
| `self-uninstall` | A | **this template** |
| `version` | B | CLI interface (**local** version) |
| `about` | B | CLI interface (+ channel-aware notes OK) |
| `help` | B | CLI interface |

Optional: `where-is-me` (path diagnostic) — not a substitute for remote update.

---

## 3. Ownership map (anti-duplication — sacred)

| Concern | Single owner | This template does |
|---------|--------------|--------------------|
| Channel URL / `REPO_*` / composition / README one-liner rules | `template-online-install.md` | **Pointer only** — use Config channel for network steps |
| Type O empty argv | `template-shell-cli-zero-arguments.md` (+ online-install mandate) | **Not redefine** |
| Pipe bootstrap (always `app_main`) | `template-online-install.md` §3.0 | **Not redefine** |
| Companion digest / pin shapes | `template-automatic-checksum.md` | **Require** integrity on self-update download; no re-spec of link/value/result UX |
| Local copy install/uninstall/where-is-me | `template-shell-local-self-management.md` | **Out of mode** |
| Local `version` / dispatcher flags catalog | `template-cli-interface.md` | **Require** local version as companion |
| `out_*` catalog | `template-output-requirements.md` | **Consume** |
| PATH `path_add_*` bodies | `template-path-and-shell-support.md` (**`LM-PATH-AND-SHELL-SUPPORT`**) | **MAY** call reverse on uninstall. When install companion writes bashrc: **MUST** obey that mold’s create / modify-dongle / VERSION+exact-PATH no-op law **and** name **TP-LC-20..22** |
| `GLOBAL_BIN` / `USER_BIN` theory | location terms | **Consume** |
| Uninstall confirm matrix | interactive template + §5 here | Normative fail-closed for self-uninstall only |

**Rule:** If a rule already has a peer owner, this template states **“MUST obey peer X”** — it does **not** paste peer normative tables again.

---

## 4. Command surface (Layer A — normative)

| Command | Purpose | Flags | Handler family |
|---------|---------|-------|----------------|
| `version-check` | Local vs remote version report | `--json`, `--quiet` | `ver_check` / `app_*` thin wrap |
| `self-update` | Channel re-fetch + replace when newer | `--force`, `--json` | `inst_self_update` |
| `self-uninstall` | Remove managed binary | `--force`, `--json` | `inst_self_uninstall` |

**User-facing names** stay short; **functions** use prefixes ([shell-function-naming-convention](../../terminologies/shell-function-naming-convention.md)).

---

## 5. Core rules (Layer A only)

### 5.1 Trusted channel (consume online-install)

1. Remote version-check and self-update **MUST** use the product Config install channel (`SCRIPT_URL` / composed `REPO_*` default) — **not** ad-hoc URLs in helpers.  
2. **Full channel composition, override precedence, companion URL derivation, README one-liner SSOT:** **`template-online-install.md` only** — do not re-list variable catalogs here.  
3. Empty / unreachable channel → network steps **fail loud** (never silent “already latest”).  
4. Terms: [`script-url`](../../terminologies/script-url.md) and peers under online-install.

### 5.2 Version-check (normative)

| Rule | Meaning |
|------|---------|
| Local side | Read ship-unit / installed binary `VERSION` SSOT |
| Remote side | Fetch via **same** channel as install (peer online-install fetch helpers) |
| Compare | Semantic version compare (`ver_gt` / product-equivalent) |
| Output | Human + JSON via `out_*`; include local and remote when designed |
| Offline / empty channel | **Fail closed** — do not invent “latest” |

### 5.3 Self-update (normative)

| Rule | Meaning |
|------|---------|
| Channel | Same script-url channel as install |
| Newer only | Update when remote **>** local unless `--force` |
| Downgrade | **MUST NOT** without `--force` |
| Start INFO | Proceeding first INFO **MUST** name both versions after remote `VERSION=` is known: `Starting the self-update of {{APP_NAME}}({{local}}) to new version:{{remote}}...`. **MUST NOT** print a version-less start line. Fetch fail / already-at-remote without `--force` **MUST NOT** print that start line. |
| Integrity | **MUST** apply automatic companion (and/or pin) per `template-automatic-checksum.md` |
| Atomic | Reuse install orchestrator (stage → verify → **`chmod 0755`** → `mv`) — **one** download SSOT with online-install. **MUST NOT** `chmod +x` on `mktemp` staging (**0711**). **MUST NOT** `chmod 0755 \|\| chmod +x`. Dest mode lives on location terms. Proof **`TP-LC-10`**. Pain **PP-A-28**. |
| **Global dest mode** | After place or `self-update` onto `{{GLOBAL_BIN}}/{{APP_NAME}}`, dest **MUST** be **0755**. **MUST NOT** treat `{{USER_BIN}}` dest mode as proof (owner still has `r` on 0711). Proof **TP-LC-10** (global install) · **TP-LC-25** (global self-update). The **running** installer applies dest mode — shipping 0755 in N+1 bytes does not protect an N placer |
| **Two jobs** | CLI place success = **binary + integrity**. Host/domain **daemon start** is a **separate** job. **MUST NOT** one exit code for both. |
| **Skip domain start** | When reusing `inst_perform_install`, `self-update` **MUST** set `SKIP_DOMAIN_START=1` (or equivalent) so auto-start / host-daemon config test does **not** run. **MUST NOT** “simplify” by always calling domain start after place. |
| **Host daemon config** | **MUST NOT** `out_die` CLI update because a host daemon config test failed (typical instance: `sshd -t -f /etc/ssh/sshd_config`, missing `/run/sshd`). **MUST NOT** rewrite that host config as a side effect of CLI update. |
| **`sudo` / root** | Means write `GLOBAL_BIN` at dest mode **`0755`**. It is **not** a license to gate CLI update on host daemon config. **MUST NOT** leave `0711`/`0700` on a shebang dest (`sudo` success is not unprivileged proof). |
| Privilege path | Preserve user vs global install target |
| Output | All messages via `out_*`. After `[OK] installed`, **MUST NOT** print `[ERROR]` naming a host daemon config file. |

### 5.4 Self-uninstall (normative)

| Rule | Meaning |
|------|---------|
| **User-facing command name** | **MUST** be **`self-uninstall`** for all online install / online self-managed products ([`self-uninstall.md`](../../terminologies/self-uninstall.md)). **MUST NOT** use bare `uninstall` as the primary online remove command. |
| Function name | `inst_self_uninstall*` (command ≠ function) |
| Target | Managed bin path only (`GLOBAL_BIN` / `USER_BIN` + `APP_NAME`) — location terms |
| Absent | Success no-op (`template-idempotency.md`) |
| Confirm | Interactive unless `--force`; JSON/quiet/non-TTY without force → **`confirm_required`** (interactive template) |
| PATH reverse | Only when safe — `template-path-and-shell-support.md` / shell-path-integration |
| No over-delete | No home trees, domain data, unrelated tools, or OS packages |
| CLI vs payload | Curl install often places a **payload binary** (e.g. language runtime); the **install CLI** still **self-uninstalls** what **it** managed — not distro/`npm uninstall` semantics |
| Local contrast | Local-only products use bare **`uninstall`** (`template-shell-local-self-management.md`) |

### 5.5 About / help honesty (package-level)

- Local `version` remains a separate command (CLI interface).  
- `about` **MAY** show install presence and channel identity when online.  
- **MUST NOT** list optional install-path-only pins such as `CHECKSUM` in help/about when automatic companion is primary (`template-automatic-checksum.md`).  
- **MUST NOT** invent toy `example.com` hosts as product channel law (product README holds real non-secret channel when non-empty — no-hardcode **excluded** for root README/CHANGELOG).

### 5.6 Atomic and shared install orchestrator

Self-update **MUST NOT** introduce a parallel “curl straight to final path” path.  
**Download + place** logic is **shared** with online install (`inst_perform_install*` family or equivalent) — specialize bodies once under product law citing **both** online-install and self-management requirements.  
Place **MUST** set dest mode **`0755`** on staging before `mv` (**`LM-ONLINE-INSTALL`** §3.1). First install and `self-update` are the **same** dest-mode contract.

---

## 6. Function inventory (online mode — names only)

Large bodies are product protection zones. This table is **inventory**, not a second copy of online-install algorithms.

| Function | Prefix | Role | Body ownership |
|----------|--------|------|----------------|
| `ver_gt` | `ver_` | Pure semver compare | **This template** (example OK) |
| `ver_check` | `ver_` | Local vs remote report | **This template** (orchestrates fetch peer) |
| `util_fetch_remote_version` | `util_` | Channel VERSION fetch | Shared with online-install / product |
| `inst_self_update` | `inst_` | Update orchestrator | **This template** + calls install SSOT |
| `inst_self_uninstall*` | `inst_` | Uninstall steps | **This template** |
| `inst_is_installed` / `inst_get_version` | `inst_` | Detect / read local version | Shared lifecycle |
| `inst_perform_install*` | `inst_` | Download + atomic place | **`template-online-install.md`** |
| `inst_self_install*` / `inst_cli_dest_mode` | `inst_` | CLI self-place / dest mode | **`LM-SHELL-CLI-SELF-INSTALL`** — **do not fork here** |
| `util_get_install_bin_path` | `util_` | Privilege path | Shared; sketch once (local §9.3) — **do not fork here** |
| `util_sha256_file` | `util_` | Digest helper | Checksum / online-install peers |
| `path_add_*` / PATH reverse | `path_` | PATH integration | **path template** |
| `app_version` / `app_about` / `app_help` | `app_` | Local diagnostics | **CLI interface** |

---

## 7. Example shapes (only what this template uniquely needs)

### 7.1 `ver_gt` — pure semver compare

```sh
# return 0 if $1 > $2 (major.minor.patch dotted); equal → return 1
# GENERAL PURPOSE: Safe compare for version-check / self-update gates.
ver_gt() {
    v1=$1
    v2=$2
    while [ -n "$v1" ] || [ -n "$v2" ]; do
        p1=${v1%%.*}; p2=${v2%%.*}
        [ -z "$p1" ] && p1=0
        [ -z "$p2" ] && p2=0
        if [ "$p1" -gt "$p2" ]; then return 0; fi
        if [ "$p1" -lt "$p2" ]; then return 1; fi
        if [ "$v1" = "${v1#*.}" ]; then v1=""; else v1=${v1#*.}; fi
        if [ "$v2" = "${v2#*.}" ]; then v2=""; else v2=${v2#*.}; fi
    done
    return 1
}
```

### 7.2 `inst_get_version` — local version string for compare

```sh
# Class B: print version string or "not installed" for capture
# Does NOT replace user-facing app_version (CLI interface).
inst_get_version() {
    : "${APP_NAME:=app}"
    local bin_path
    bin_path=$(util_get_install_bin_path)
    if [ ! -x "${bin_path}" ]; then
        printf '%s' "not installed"
        return 0
    fi
    grep '^VERSION="' "${bin_path}" 2>/dev/null | head -1 | cut -d'"' -f2 || printf '%s' "unknown"
}
```

### 7.3 `ver_check` — local vs remote report

```sh
ver_check() {
    : "${APP_NAME:=app}" : "${JSON:=0}" : "${QUIET:=0}" : "${SCRIPT_URL:=}"
    REMOTE_VERSION=$(util_fetch_remote_version "${SCRIPT_URL}")
    if [ -z "$REMOTE_VERSION" ]; then
        out_json_error "Failed to fetch remote version" "network_error"
        [ "${JSON}" -eq 1 ] || out_error "Failed to fetch remote version (SCRIPT_URL may be unset or unreachable)"
        return 1
    fi
    local_version=$(inst_get_version)
    if [ "${JSON}" -eq 1 ]; then
        _is_latest="false"
        if [ "$local_version" = "$REMOTE_VERSION" ] || ver_gt "$local_version" "$REMOTE_VERSION" 2>/dev/null; then
            _is_latest="true"
        fi
        out_json "ver_check" "" "local_version" "$local_version" \
            "remote_version" "$REMOTE_VERSION" "is_latest" "${_is_latest}"
        return 0
    fi
    [ "${QUIET}" -eq 1 ] && return 0
    out_info "Local version : ${local_version}"
    out_info "Latest version: ${REMOTE_VERSION}"
}
```

### 7.4 `inst_self_update` — fetch, refuse silent downgrade, reuse install SSOT

```sh
inst_self_update() {
    : "${APP_NAME:=app}" : "${JSON:=0}" : "${FORCE:=0}" : "${SCRIPT_URL:=}"
    [ "${FORCE}" -eq 1 ] && FORCE_REINSTALL=1
    REMOTE_VERSION=$(util_fetch_remote_version "${SCRIPT_URL}")
    if [ -z "$REMOTE_VERSION" ]; then
        out_json_error "Failed to fetch latest version" "network_error"
        return 1
    fi
    local_version=$(inst_get_version)
    if [ "$local_version" = "$REMOTE_VERSION" ] && [ "${FORCE_REINSTALL:-0}" -eq 0 ]; then
        out_json "out_success" "Already running the latest version (${REMOTE_VERSION})."
        return 0
    fi
    if [ "$local_version" != "not installed" ] && [ "$local_version" != "unknown" ] && \
       ver_gt "$local_version" "$REMOTE_VERSION" && [ "${FORCE_REINSTALL:-0}" -eq 0 ]; then
        out_json_error "Refusing downgrade from ${local_version} to ${REMOTE_VERSION} (use --force)" "downgrade_blocked"
        return 1
    fi
    FORCE_REINSTALL=1
    SKIP_DOMAIN_START=1
    inst_perform_install
    SKIP_DOMAIN_START=0
}
```

Download/atomic place stay on **`LM-ONLINE-INSTALL`**. Uninstall confirm uses `prompt_yes_no` in the **current shell** (never `$()`).

### 7.5 `inst_self_uninstall` — current-shell confirm (never `$()`)

```sh
# WARNING — do-not-capture-read (PP-A-22). prompt_yes_no contains read.
inst_self_uninstall() {
    : "${APP_NAME:=app}" : "${FORCE:=0}" : "${JSON:=0}" : "${TTY:=0}"
    : "${HOME:=/tmp}"
    if [ "${FORCE}" -ne 1 ]; then
        if [ "${JSON}" -eq 1 ] || [ "${TTY}" -ne 1 ]; then
            out_json_error "self-uninstall needs --force when not on a terminal" "confirm_required"
            [ "${JSON}" -eq 1 ] || out_error "self-uninstall needs --force when not on a terminal. Next: ${APP_NAME} --force self-uninstall"
            return 1
        fi
        if ! prompt_yes_no "Remove ${APP_NAME} from this login"; then
            out_info "Uninstall cancelled."
            return 0
        fi
    fi
    _bin=$(util_get_install_bin_path)
    if [ ! -e "${_bin}" ]; then
        out_success "Nothing to uninstall."
        unset _bin
        return 0
    fi
    rm -f "${_bin}" || out_die "Could not remove ${_bin}."
    # PATH reverse only when USER_BIN is empty — LM-PATH-AND-SHELL-SUPPORT
    out_success "Removed ${_bin}."
    unset _bin
}
```

### 7.6 `inst_ensure_companion` — PATH then optional domain start

CLI place success is **binary + integrity**. Domain/host daemon start is a **separate** job. `self-update` sets `SKIP_DOMAIN_START=1` before `inst_perform_install`.

```sh
inst_ensure_companion() {
    : "${SKIP_DOMAIN_START:=0}"
    path_add_shell || true
    if [ "${SKIP_DOMAIN_START}" -eq 1 ]; then
        return 0
    fi
    # Product MAY start a domain daemon after install (not after self-update).
    # MUST NOT out_die CLI place because a host daemon config test failed.
    return 0
}
```

Call from `inst_perform_install` **after** atomic place. **`LM-ONLINE-INSTALL`** §3.6.3 orchestrator already comments this skip.

### 7.7 Intentionally not duplicated here

| Example / catalog | Where to find it |
|-------------------|------------------|
| `SCRIPT_URL` / `REPO_*` defaults | `template-online-install.md` §2.3 |
| `curl \| sh` bootstrap | `template-online-install.md` §3.0 |
| Type O empty-argv matrix + dispatcher split | `template-shell-cli-zero-arguments.md` §5.5b |
| Type 0 `app_main` + `rc-test` operands | `template-cli-interface.md` Example `app_main` |
| Companion link/value/result UX | `template-automatic-checksum.md` |
| `util_get_install_bin_path` full sketch | Prefer **one** product helper; portable sketch also in local-self-management install helpers narrative |
| `path_add_*` | `template-path-and-shell-support.md` |
| `out_*` | `template-output-requirements.md` |
| Local copy install | `template-shell-local-self-management.md` |

Online download orchestrators (`inst_perform_install*`, full `inst_self_update`, full `ver_check`) remain **product protection zones** specialized from live REQs — keep **one** install SSOT.

---

## 8. Why this pattern exists (CIAO)

- **Caution:** Fail closed on empty channel; no silent downgrade; uninstall confirm.  
- **Intentional:** Online vs local modes are separate templates; local version ≠ version-check.  
- **Anti-fragile:** Shared install orchestrator for install + self-update **with** `SKIP_DOMAIN_START` on update (domain start must not fail CLI place).  
- **Over-protect:** Checksum + atomic replace; no fake JSON cancel on uninstall.  
- **SSOT:** Channel in online-install Config; output via `out_*`; compare via `ver_*`.

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

**This mold:** `self-update` / `self-uninstall` stay Type 0; **MUST NOT** recommend `sudo curl | sh`.

---

## 9. Protection Rule (Sacred)

Future agents **MUST NOT**:

1. Re-own or re-paste full `SCRIPT_URL` / `REPO_*` catalogs here when online-install already owns them.  
2. Redefine Type O empty-argv or pipe bootstrap in this file.  
3. Remove or weaken integrity verification on self-update downloads.  
4. Allow downgrades without `--force`.  
5. Fake self-uninstall success under JSON without `--force` (`confirm_required` only).  
6. Parallel-curl past the shared install orchestrator.  
7. List CHECKSUM pin theater in help/about when companion is primary integrity.  
8. Treat this template as local-only install law (use local-self-management instead).  
9. Confuse or replace **local `version`** with **`version-check`**.  
10. Use bare **`uninstall`** as the primary remove command on an online install package (must be **`self-uninstall`**).  
11. Treat **`self-uninstall`** as OS package remove or arbitrary payload `rm` outside managed install paths.  
12. Paste this template path into product source as behavioral authority — specialize and cite live requirements.  
13. Hardcode product brands/hosts into this template as universal law.  
14. Strip the **Under command line for normal user only** section, or recommend `sudo curl | sh` on that class.  
15. Fail **`self-update`** after a successful CLI place because a **host daemon config test** failed, or rewrite that host config as a side effect of CLI update.  
16. Reuse `inst_perform_install` on `self-update` **without** skipping domain auto-start (`SKIP_DOMAIN_START` or equivalent).  
17. Treat `sudo` / root on `self-update` as permission to start or validate a host daemon.  
18. Place or `self-update` a Type 0 shebang dest with `chmod +x` on `mktemp` staging (or `chmod 0755 \|\| chmod +x`), or leave dest mode **`0711`/`0700`** (unprivileged `/bin/sh: 0: cannot open …: Permission denied`). Compose **`LM-ONLINE-INSTALL`** §3.1 · **`TP-LC-10`** · **PP-A-28**.  
19. Close dest-mode law on **`{{USER_BIN}}` 0755** without isolated **`GLOBAL_BIN`** proof (**TP-LC-10**) and global **`self-update`** proof (**TP-LC-25**).  
20. Claim that dest mode in version N+1 bytes was applied by a version N `self-update` (the placer is the running binary).

---

## 10. How to specialize (multi-template set)

For a full **online self-managed** product, specialize **all** that apply in the same program of work:

| Step | Template → requirement (typical) |
|------|----------------------------------|
| 1 | `template-online-install.md` → install / channel law |
| 2 | `template-shell-cli-zero-arguments.md` → Type O empty argv |
| 3 | `template-automatic-checksum.md` → when companion integrity claimed |
| 4 | **This template** → version-check / self-update / self-uninstall |
| 5 | `template-cli-interface.md` → dispatcher + **local version** + help/about |
| 6 | output / interactive / idempotency / modular peers as needed |
| 7 | Register every Active REQ in `docs/requirements/index.md` |
| 8 | Product source cites **live REQs only** |

**Local-only fork:** skip steps 1–4 online; use `template-shell-local-self-management.md` + Type N.

---

## 11. Definition of done (online self-managed specialization)

Not done until:

1. Layer A commands work against real Config channel.  
2. Empty channel fails loud on version-check/self-update.  
3. Self-update uses shared install orchestrator + integrity peer **and** skips domain auto-start (`SKIP_DOMAIN_START`). CLI place success does not depend on host daemon config test.  
4. Self-uninstall fail-closed without force; no over-delete.  
5. Layer B **local version** still works offline.  
6. Help lists online package honestly; no local-mode false claims.  
7. No duplicated contradictory channel/path rules vs peer REQs.  
8. Protection Rule items hold.

---

## 12. Verification (minimum)

| Check | Peer / note |
|-------|-------------|
| `version` offline | CLI interface |
| `version-check` with channel | This template |
| `version-check` empty channel fails | This template |
| `self-update` already-latest no-op | Idempotency + this template |
| `self-update` integrity fail aborts | automatic-checksum |
| `self-update` still succeeds when host daemon config test would fail | this template §5.3 two jobs |
| Dest after `self-update` is **0755** (not 0711); unprivileged run of a global dest works | **`TP-LC-25`** (global self-update) · **`TP-LC-10`** (global install) · **`LM-ONLINE-INSTALL`** §3.1 |
| `self-uninstall --json` no force → confirm_required | interactive |
| Pipe install / Type O | online-install + zero-arg |
| Local-only product does not claim this REQ | registry honesty |

---


## Design-time verification

| TP family / ID | Proof mold | Planned suite |
|----------------|------------|---------------|
| **TP-LC-04..08,10,11,12** version-check / update / dest mode 0755 / uninstall / downgrade / install | `../tests/template-install-lifecycle-test-plan.md` | `tests/test_install_lifecycle.sh` |
| **TP-LC-25** global dest **0755** after `self-update` | same | `tests/test_install_lifecycle.sh` |
| **TP-LC-20,21,22** bashrc PATH ensure (`BASHRC` temp-folder create / modify dongle / VERSION+exact-PATH no-op) | `../tests/template-install-lifecycle-test-plan.md` · bodies **`LM-PATH-AND-SHELL-SUPPORT`** | `tests/test_install_lifecycle.sh` — **Core when companion writes bashrc** |
| **TP-CLI-11** self-uninstall refuse | `../tests/template-shell-cli-test-plan.md` | `tests/test_cli.sh` |
| **TP-CURL-02,07** pipe ensure / pipe version | `../tests/template-online-curl-install-test-plan.md` | curl suite |

**RTM:** `../tests/template-requirement-test-traceability.md`


**Last Updated**: 2026-09-17  
**Owner**: {{OWNER}}  
**Version history:**  
- **2.8.2** (2026-09-17): Inventory points `inst_self_install*` / `inst_cli_dest_mode` at **`LM-SHELL-CLI-SELF-INSTALL`** (no second body).  
- **2.8.1** (2026-09-15): Global dest is the blocking class (**TP-LC-10** install · **TP-LC-25** self-update). USER_BIN-only is not proof. **MUST NOT** `chmod +x` fallback. Running placer applies dest mode.  
- **2.8.0** (2026-09-15): §5.3 / §5.6 dest mode **0755** on shared place; Protection 18; **`TP-LC-10`** (not **`TP-LC-23`**, zsh PATH). Pain **PP-A-28**.  
- **2.7.0** (2026-09-12): §7.5 `inst_self_uninstall` current-shell confirm; §7.6 `inst_ensure_companion` + `SKIP_DOMAIN_START`.  
- **2.6.0** (2026-09-09): §5.3 two jobs — CLI place vs domain/host daemon start; `self-update` **MUST** `SKIP_DOMAIN_START`; **MUST NOT** fail CLI update on host daemon config test.  
- **2.5.0** (2026-09-09): Example-sync `ver_check` / `inst_self_update`.  
- **2.4.0** (2026-09-09): When install companion writes bashrc, **TP-LC-20..22** are Core (create / modify dongle / no-op). Bodies remain **`LM-PATH-AND-SHELL-SUPPORT`**.  
- **2.3.0** (2026-09-07): Proceeding `self-update` first INFO names local and remote VERSION after channel `VERSION=` is fetched.  
- **2.1.0** (2026-07-17): Mandatory user command `self-uninstall` for all online packages; term `self-uninstall` (CLI vs payload).  
- **2.0.0** (2026-07-17): Feature package + ownership map; strip channel/path/catalog duplication; align with local-self-management package style.  
- **1.3.0**: Local version ≠ version-check.  
- **1.2.0**: Scope = online only; local lifecycle split out.  
- **1.1.0 / 1.0.0**: Earlier self-management sets.

**Alignment**: terms `online-self-managed`, `self-management`, `script-url`; peers `template-online-install`, `template-automatic-checksum`, `template-shell-cli-zero-arguments`, `template-shell-local-self-management`, `template-cli-interface`, path/output/interactive/idempotency; CIAO v2.10.2.
