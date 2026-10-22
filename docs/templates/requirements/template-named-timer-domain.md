---
name: named-timer-domain
id: LM-NAMED-TIMER-DOMAIN
kind: law-mold
description: >
  Portable law mold. Cite as LM-NAMED-TIMER-DOMAIN (path secondary).
---

**file**: template-named-timer-domain.md  
**Status**: Active (Version 1.7.0 – DTV; Type O empty-argv clarity; optional idempotency peer)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered / Over-protect)

## 1. Purpose

This template defines the portable **full-domain [external-timer](../terminologies/external-timer.md)** named-timer feature package for a POSIX shell (or similar) Type 0 CLI: **start / stop / status / list / kill / reset** over **path-safe timer names**, with **volatile vs persistent domain record modes**, human + JSON contracts, and the four **domain-requirements** pillars.

### 1.0 Expansion from internal volatile base (normative layering)

This mold is the **expansion** of the base timer mold [`template-shell-internal-volatile-timer.md`](./template-shell-internal-volatile-timer.md). Agents **MUST** understand domain named-timer as **base + features**, not as an unrelated second family.

```text
template-shell-internal-volatile-timer   ←  base (process epoch, volatile only, helper API)
        │
        │  ADD: multi-name · persistency · CLI subcommands · storage/temp/CLI peers · help/about
        ▼
template-named-timer-domain              ←  THIS FILE (full domain)
```

| Inherited from base (keep spirit) | **Added by this expansion** |
|-----------------------------------|-----------------------------|
| Elapsed wall-clock work-timer idea | User/app **domain verb catalog** (`start`…`reset`) |
| Start / stop / status (or elapsed) semantics | **`list` / `kill` / `reset`** multi-timer ops |
| Fail-closed double-start / missing-stop | Path-safe **user names** + default name |
| Volatile lifetime spirit (as **default** mode) | **Persistent** domain records + global **`--persist`** |
| Output SSOT for any user-facing messages | Four **domain-requirements** pillars (CLI + features + help + about) |
| No domain CLI surface on base | **CLI peer** (dispatch, flags, empty argv) |
| No storage REQ on base | **Storage peer** + domain epoch **files** / resolve |
| No temp REQ on base for timer state | **Temp peer** (install staging; not epoch leaves) |

**Base mold still exists:** products **MAY** keep specialized internal-volatile law + helpers for install/handler probes **alongside** this domain mold. Internal helpers are **not** domain verbs.

**Audience:** users and other applications (full-domain external-timer specialization).  
**Subset base:** [internal-timer](../terminologies/internal-timer.md) volatile mode is defined by `template-shell-internal-volatile-timer` (not this file). Products may still embed internal-timers inside handlers without treating them as domain verbs.

**Specialize into:** exactly one Active `requirement-domain-{{DOMAIN_SUBJECT}}.md` (registered domain SSOT) with filled Implementation Notes. Replace `{{DOMAIN_SUBJECT}}` with the product’s domain subject (path-safe product slug). **Do not** freeze one product basename as universal law in this mold.

### 1.1 Mandatory peers (fail closed)

Specializing this mold **without** these Active registered peers is **incomplete**:

| Peer | Specialize from | Owns |
|------|-----------------|------|
| **CLI interface** | `template-cli-interface.md` → e.g. `requirement-shell-cli-interface.md` | Command table, flags (`--persist`), empty argv, dispatch |
| **Shell CLI storage** | `template-shell-cli-storage.md` → e.g. `requirement-shell-cli-storage.md` | Isolation, resolve priority, central `util_resolve_storage` (or family), fail-closed storage roots |
| **Temp file system** | `template-temp-file-system.md` → e.g. `requirement-shell-temp-file-system.md` | Temp roots, unique names (`mktemp`), cleanup/trap, noexec, atomic stage→publish for **temps** |
| **Output** | `template-output-requirements.md` → output REQ | `out_*` / channel SSOT (when shell) |
| **Idempotency** (recommended) | `template-idempotency.md` → e.g. `requirement-shell-idempotency.md` | Already-running **fail** vs list empty **success**; lifecycle ensure matrices stay on shell REQs |

**Storage + temp + CLI + output requirements are required, not optional**, when this named-timer mold is product law. Idempotency peer is **recommended** when re-run matrices are product-claimed. Domain law may define **timer record** modes and leaf contracts (§5.2) but **MUST NOT** replace or omit specialized storage **or** temp-file-system requirements.

**Do not use this template for:**

| Concern | Owner instead |
|---------|----------------|
| Local install / uninstall / where-is-me | `template-shell-local-self-management.md` (consumes temp REQ for staging) |
| Online install / self-update / self-uninstall | online-install + self-management templates |
| Full CLI catalog / empty-argv Type N/O | `template-cli-interface.md` / zero-arguments template |
| Full `out_*` catalog | `template-output-requirements.md` |
| Prefix table SSOT | `template-modular-function-design.md` |
| Domain re-run matrix depth | `template-idempotency.md` (+ specialized idempotency REQ) |
| **Standalone storage-only products** | `template-shell-cli-storage.md` alone |
| **Standalone temp-only products** | `template-temp-file-system.md` alone |

**Anti-duplication:** This template owns **domain feature semantics** and **timer record contracts** (epoch files, already-running). **Storage requirement** owns isolation + resolve for durable/scratch roots. **Temp requirement** owns `mktemp` uniqueness, cleanup, temp-root families for staging. Install algorithm stays local-self-management but **must align** with temp REQ.

---

## Terminologies (mandatory)

| Term | Path | SSOT type | Role in this template |
|------|------|-----------|------------------------|
| Domain requirements | `docs/terminologies/domain-requirements.md` | product-law | **Four pillars** this template implements |
| Domain surface | `docs/terminologies/domain-surface.md` | runtime-mode / surface | Runtime ops this law describes |
| External-timer | `docs/terminologies/external-timer.md` | product-law / feature kind | **Family / superset** — this mold = full domain specialization |
| Internal-timer | `docs/terminologies/internal-timer.md` | product-law / feature kind | **Subset** of external-timer — instrumentation only |
| Path-safe name | `docs/terminologies/path-safe-name.md` | product-law / identity | Timer **name** gate before I/O |
| Ship unit | `docs/terminologies/ship-unit.md` | product artifact | Host CLI that dispatches domain |
| Single source of truth of output | `docs/terminologies/single-source-of-truth-of-output.md` | channel-io | Domain messages via Output only |
| Interactive vs noninteractive | `docs/terminologies/interactive-vs-noninteractive.md` | runtime-mode | Domain ops argv-only; no prompts |
| Idempotency rule | `docs/terminologies/idempotency-rule.md` | product-law / re-run | Already-running fail vs list empty success |
| Shell function naming convention | `docs/terminologies/shell-function-naming-convention.md` | meta / naming | `{{DOMAIN_PREFIX}}_*` handlers |
| Shell CLI config variables | `docs/terminologies/shell-cli-config-variables.md` | meta / config | Persist/name/storage vars |
| Local self-managed | `docs/terminologies/local-self-managed.md` | product-law / lifecycle | **Contrast** — not domain verbs |
| Temp file system | `docs/terminologies/temp-file-system.md` | runtime storage | **Required peer** mold — staging temps / `mktemp` |
| Atomic data file | `docs/terminologies/atomic-data-file.md` | product-law / storage | Optional publish pattern for durable records |

**Do not re-own here:** install channel, Type O empty-argv, automatic-checksum, system-user, online self-managed; full storage resolve SSOT (**storage requirement**); full temp-root/`mktemp` policy (**temp requirement**).

---

## 2. Placeholders (specialize only)

| Placeholder | Meaning | Example specialization (not universal law) |
|-------------|---------|-----------------------------------------------|
| `{{APP_NAME}}` | Product / binary identity | project app name |
| `{{DOMAIN_SUBJECT}}` | Domain SSOT basename subject | e.g. product slug → `requirement-domain-<slug>` |
| `{{DOMAIN_PREFIX}}` | Path-safe function prefix | `timer` → `timer_*` (hyphen-free) |
| `{{DEFAULT_TIMER_NAME}}` | Name when operand omitted | `default` |
| `{{VOLATILE_DIR}}` | Default volatile root | `/dev/shm` |
| `{{PERSISTENT_DIR}}` | Default persistent root | `${XDG_CACHE_HOME:-$HOME/.cache}/{{APP_NAME}}` |

---

## 3. Four domain pillars (normative understanding)

Agents specializing domain law **MUST** cover all four (term: domain-requirements):

| # | Pillar | This template section |
|---|--------|------------------------|
| 1 | Specialized CLI subcommands | §4 |
| 2 | Specialized features | §5 |
| 3 | Specialized project help items | §6 |
| 4 | Specialized project about items | §7 |

Exactly **one Active** domain-requirements file per specialized product with domain surface.

---

## 4. Specialized CLI subcommands (portable catalog)

Domain verbs **MUST** be stable in specialized law. Dispatch **MUST** run through the single CLI entry (`app_main` or equivalent). Handlers **MUST** live under `{{DOMAIN_PREFIX}}_*`, not under install/lifecycle-only helpers.

| Command | Privilege | Handler family | Operands / flags | Required behavior | Typical non-zero outcomes |
|---------|-----------|----------------|------------------|-------------------|---------------------------|
| `start` | Type 0 | `{{DOMAIN_PREFIX}}_start` | optional `[name]`; global `--persist` | Create running timer record with start epoch; default name `{{DEFAULT_TIMER_NAME}}` when omitted | already running → fail; invalid name → fail; I/O fail → fail |
| `stop` | Type 0 | `{{DOMAIN_PREFIX}}_stop` | optional `[name]` | Remove running timer; report elapsed | no timer → fail |
| `status` | Type 0 | `{{DOMAIN_PREFIX}}_status` | optional `[name]` | Report elapsed **without** stopping | no timer → fail |
| `list` | Type 0 | `{{DOMAIN_PREFIX}}_list` | optional `--persist` | List running timers in selected mode | empty list → **success** |
| `kill` | Type 0 | `{{DOMAIN_PREFIX}}_kill_or_reset kill` | optional `[name]` | Discard without elapsed success report | no timer → fail |
| `reset` | Type 0 | `{{DOMAIN_PREFIX}}_kill_or_reset reset` | optional `[name]` | Discard with reset messaging | no timer → fail |

**Dispatch rules:**

1. Domain commands recognized in the same global flag parse as Type 0 diagnostics/lifecycle.  
2. Free token after a domain command = timer **name** (not a second command).  
3. Unknown tokens fail loud with pointer to `help` (CLI interface owns unknown-command path).  
4. Handlers call a single name-gate (`{{DOMAIN_PREFIX}}_sanitize_name` or equivalent) **before** file I/O.  
5. Storage path via storage SSOT helpers (`{{DOMAIN_PREFIX}}_resolve_base_dir` / `{{DOMAIN_PREFIX}}_get_file` or successors).  
6. All user-facing domain messages via centralized Output (`out_*` when shell).

**Must not appear as domain verbs:** `install`, `uninstall`, `where-is-me`, `self-update`, `self-uninstall`, `version-check`, empty-argv install-ensure.

### 4.1 CLI peer alignment (mandatory — does **not** make this the CLI SSOT)

This template **requires** a specialized **CLI interface** peer (from `template-cli-interface.md`) to stay aligned. Domain law owns **behavior**; CLI law owns **surface routing**.

| Concern | Domain REQ (this pattern) | CLI interface REQ (peer) |
|---------|---------------------------|---------------------------|
| Six domain **command names** | Semantics + handlers + error codes | **MUST** list all eleven in command table with **behavior → domain REQ** |
| Global **`--persist`** | Storage mode meaning | **MUST** parse flag and set domain persist state (e.g. `TIMER_PERSIST=1`); not lifecycle-only |
| Free token after domain verb | Path-safe **timer name** | **MUST** treat as operand name, not second command |
| Unknown command / unknown flag token | — | **MUST** fail loud + pointer to `help` (CLI owns path) |
| Empty argv | **MUST NOT** mean domain list/start | When online-install / self-management peers are Active (typical Type O-S CLI): **MUST** be **Type O install-ensure** (not domain). Type N **help** only when zero-arg law is Type N. See `template-shell-cli-zero-arguments.md` |
| Domain section in human `help` | **Content** of timer rows (§6) | **MUST** include domain section; structure/lifecycle rows CLI-owned |
| JSON `help` | No long domain dump | Short structured note (CLI contract) |
| `about` domain hints | §7 minimum starter rows | `about` command routed by CLI; domain content from domain REQ |
| Single entry `app_main` | Domain routes only after dispatch | Dispatcher SSOT |
| Output modes quiet/json | Domain messages honor modes | Flag parse + mode globals CLI-owned |
| Local install / uninstall / where-is-me | **Not domain verbs** | List + point to local-self-management REQ |
| Online remote lifecycle | **Forbidden** as domain | **MUST NOT** list unless separate online REQs Active |

**Same-change rule:** Adding, renaming, or removing a domain verb in specialized domain law **MUST** update the CLI interface command table and help in the **same** change (or Block as dual-SSOT drift).

**Specialize order:** temp REQ + storage REQ + CLI REQ + domain REQ all Active and cross-linked before claiming domain surface “done.”

### 4.2 Storage peer alignment (mandatory — **requires** specialized storage REQ)

This mold **requires** an Active registered storage requirement specialized from `template-shell-cli-storage.md` (typical key: `requirement-shell-cli-storage`).

| Concern | Domain REQ (this pattern) | Storage REQ (required peer) |
|---------|---------------------------|------------------------------|
| Isolation (app + user) | Consume for timer base dirs | **Owns** isolation rules for storage roots |
| Resolve priority (shm → tmp → cache) | Domain volatile/persistent **modes** map onto roots | **Owns** portable resolve chain + fail-closed |
| Central scratch/cache helper | **MUST NOT** reimplement generic chain | `util_resolve_storage` (or documented family) |
| Timer base dir helper | `{{DOMAIN_PREFIX}}_resolve_base_dir` for **timer record roots** | Align isolation/fail-closed with storage law |
| Timer file leaf | Deterministic `${APP_NAME}_${USERNAME}_${name}` | Not storage leaf `mktemp` policy |
| Install staging `mktemp` | Out of domain | Out of storage (**temp REQ** + local-self-management) |
| `--persist` meaning | Domain mode | Storage provides durable cache roots when persistent |

**Same-change rule:** Changing storage resolve/isolation **MUST** update storage REQ (and domain notes if timer base mapping changes) together.

### 4.3 Temp peer alignment (mandatory — **requires** specialized temp-file-system REQ)

This mold **requires** an Active registered temp requirement specialized from `template-temp-file-system.md` (typical key: `requirement-shell-temp-file-system`).

| Concern | Domain REQ (this pattern) | Temp REQ (required peer) |
|---------|---------------------------|--------------------------|
| Unique temp leaf names (`mktemp`) | Epoch leaves are **deterministic** (not temps) | **Owns** unique temp naming |
| Temp root families (`$TMPDIR` → `/tmp` … / shm-first scratch) | Domain bases may **use** writable mounts | **Owns** temp-root policy + noexec awareness |
| Cleanup / trap on temps | Timer files are domain state (delete on stop/kill) | **Owns** trap/cleanup for **temps** |
| Install stage temp → `mv` | Out of domain | **Owns** temp rules; local-self-management owns install algorithm |
| Atomic stage for durable publish | Domain may write epoch files | Stage/rename discipline for temps |

**Same-change rule:** Changing install staging or product-wide temp policy **MUST** update temp REQ (and local-self-management notes if install staging changes).

**Block claim “named-timer domain done” if:** no Active **storage** REQ **or** no Active **temp** REQ is registered while this domain mold is specialized.

---

## 5. Specialized features (portable)

### 5.1 Timer identity

| Rule | Meaning |
|------|---------|
| Default name | Omitted/empty after sanitize → `{{DEFAULT_TIMER_NAME}}` |
| Path-safe names | Reject path traversal and shell/path metacharacters (`/`, `\\`, `..`, spaces, quotes, globs, `$`, backticks, pipe, redirect, colon, …) — term path-safe-name |
| Invalid name | Non-zero exit; JSON code **`invalid_name`** |
| Multi-timer | Distinct valid names are independent concurrent timers (same storage mode) |

### 5.2 Domain state storage (volatile vs persistent)

Named-timer storage is **domain state** (running-timer epoch records), **not** the product-wide install-staging temp policy.

#### 5.2.1 Must not confuse (storage kinds)

| Kind | What it is | Owner pattern |
|------|------------|---------------|
| **Domain timer records** | Epoch files + volatile/persistent **modes** + deterministic leaves | **This template** → domain REQ (`{{DOMAIN_PREFIX}}_resolve_base_dir` / `_get_file`) |
| **CLI storage resolve / isolation** | Shared root priority, per-user isolation, fail-closed roots | **Required** storage REQ from `template-shell-cli-storage.md` |
| **Scratch / install staging temp** | `mktemp` leaves for copy-then-`mv` install | `template-temp-file-system.md` (+ local self-management) |

Domain timer base resolve **MUST** obey storage REQ isolation/fail-closed spirit. It **MUST NOT** invent a second product-wide resolve chain that contradicts the storage requirement.

#### 5.2.2 Modes

| Mode | Trigger | Preferred base | Fallback chain (spirit) |
|------|---------|----------------|-------------------------|
| **Volatile** (default) | No `--persist` | Writable `{{VOLATILE_DIR}}` (often `/dev/shm`) | Git Bash `$HOME/AppData/Local/Temp/cache` or `/c/Users/{{USERNAME}}/AppData/Local/Temp/cache` → `$TEMP/cache` → `/tmp/cache` (mkdir fail-soft) → isolated `/tmp/{{APP_NAME}}_{{USERNAME}}` (or equivalent) → **fail loud** if none writable |
| **Persistent** | `--persist` | `{{PERSISTENT_DIR}}` under user cache / app identity (often `${XDG_CACHE_HOME:-$HOME/.cache}/{{APP_NAME}}`) | Isolated `/tmp/…_persistent` (or equivalent) when `$HOME` unusable → **fail loud** if none |

#### 5.2.3 Resolve rules (normative)

1. **Detect** preferred root exists **and is writable** before use — never assume `/dev/shm` or `$HOME` always work.  
2. **Single domain resolver** for timer base dirs (`{{DOMAIN_PREFIX}}_resolve_base_dir` or successor) — callers **MUST NOT** scatter bare `/tmp/timer` paths.  
3. **Isolation:** final record path **MUST** include app identity + invoker user + path-safe timer name (portable leaf: `${APP_NAME}_${USERNAME}_${name}` under base).  
4. **Deterministic leaf names** for records (same name → same path) so start/stop can find state — this is **not** `mktemp` uniqueness (contrast install staging).  
5. **Warnings** on fallback tiers: human mode via Output SSOT; quiet/json must remain valid (suppress or structure as designed).  
6. **Fail closed** if no writable base — non-zero via Output; never silent empty path.  
7. Domain **MUST NOT** require root or dedicated system user solely for timer storage.  
8. **Do not** use install-staging `mktemp` leaves as the timer record path (different lifecycle and cleanup).

#### 5.2.4 File record contract

1. One file per (user, name, mode family) under resolved base dir.  
2. Body stores start time as Unix epoch seconds for elapsed arithmetic.  
3. Per-user (invoker) — no multi-tenant daemon required.  
4. Create base dir when missing **only** on owned isolated fallback paths (ownership-aware); fail loud if create/write impossible.

### 5.3 Command semantics

| Command | Success | Failure / edge |
|---------|---------|----------------|
| `start` | Create file with current epoch; report started | File exists → **already running** fail; **no** silent overwrite |
| `stop` | Read epoch, delete, report elapsed | Missing → **`no_timer`** |
| `status` | Read epoch, report elapsed; **keep** file | Missing → **`no_timer`** |
| `list` | Enumerate mode; empty → success | Corrupt entry **MAY** skip without failing whole list |
| `kill` | Delete; discarded messaging | Missing → **`no_timer`** |
| `reset` | Delete; reset messaging | Missing → **`no_timer`** |

**Contrast with install already-installed:** domain **already running** on `start` is **fail**; local install already-installed is **success no-op** (different surface).

### 5.4 Machine / mode contracts

| Mode | Domain contract |
|------|-----------------|
| Human | Messages via Output; elapsed minutes + seconds where designed |
| `--json` | Structured via `out_json` / `out_json_error`; no mixed human success on stdout |
| Quiet | Suppress non-error human noise; errors still visible |
| JSON error codes (stable minimum) | `invalid_name`, `no_timer`; I/O → e.g. `io_error` |

JSON success-ish shapes (portable minimum):

| Situation | `type` (or equivalent) | Required fields |
|-----------|------------------------|-----------------|
| start / stop / kill / reset success | `success` | `name` (+ elapsed on stop) |
| status | `status` | `name`, elapsed fields |
| list | `list` | `mode`, `count`, `timers` (array; may be empty) |
| domain error | error object | stable `code` |

### 5.5 Non-goals (explicit)

Domain law **MUST NOT** claim by default:

1. Network time sync / NTP dependency  
2. Multi-host shared timer state  
3. Type 1 host packages / Type 2 system-user services as domain  
4. Calendar/cron replacement  
5. Secrets / encrypted timer payloads  
6. Online install / self-update / self-uninstall / remote version-check as domain verbs  
7. Empty argv = install-ensure (CLI interface / Type O ownership)

---

## 6. Specialized project help items

Human `help` **MUST** list a distinct domain section (e.g. **Timer commands**):

| Help row | Required |
|----------|----------|
| `start [--persist] [name]` | Yes |
| `stop [name]` | Yes |
| `status [name]` | Yes |
| `list [--persist]` | Yes |
| `kill [name]` | Yes |
| `reset [name]` | Yes |
| Global `--persist` | Yes — persistent storage for timer ops |
| Type 0 diagnostics rows | Retained; owned in detail by CLI interface peer |

JSON `help` **MUST NOT** dump long domain text (short structured note — CLI contract).

---

## 7. Specialized project about items

`about` **MUST**:

| Item | Rule |
|------|------|
| Local diagnostics | Version, user, shell, TTY (or equivalent) — no install-channel one-liner as domain UX |
| Domain guidance | At least starter hints: `start`, `stop`, `list` + pointer to `help` |
| Domain storage dump | Optional; not mandatory |
| Online install / SCRIPT_URL / self-update tips | **MUST NOT** as domain about content unless dual-mode product law |
| CHECKSUM / companion digest | **MUST NOT** as domain about content unless product owns online integrity |

---

## 8. Config / variables (portable examples)

| Variable | Role | Default sketch |
|----------|------|----------------|
| `TIMER_NAME` / domain name var | Active timer name after sanitize | `{{DEFAULT_TIMER_NAME}}` |
| `TIMER_PERSIST` / persist flag | Persistent mode | `0` |
| `TIMER_FILE` | Resolved record path | from get-file helper |
| `STORAGE_MODE` | `volatile` / `persistent` | derived |
| `VOLATILE_DIR` | Volatile root | `{{VOLATILE_DIR}}` |
| `PERSISTENT_DIR` | Persistent root | `{{PERSISTENT_DIR}}` |
| `USERNAME` | Invoker id for file pattern | from environment / `id -un` |

Full CLI config inventory: shell-cli-config-variables term — do not duplicate here.

---

## 9. Function catalog sketch (template-example-function style)

| Function | Role |
|----------|------|
| `{{DOMAIN_PREFIX}}_resolve_base_dir` | Volatile/persistent base |
| `{{DOMAIN_PREFIX}}_get_file` | Path for one timer name |
| `{{DOMAIN_PREFIX}}_sanitize_name` | Path-safe gate |
| `{{DOMAIN_PREFIX}}_domain_fail` | Domain error via Output |
| `{{DOMAIN_PREFIX}}_start` / `_stop` / `_status` | Core ops |
| `{{DOMAIN_PREFIX}}_kill_or_reset` | kill vs reset |
| `{{DOMAIN_PREFIX}}_list` | Enumerate mode |

**Pattern:** domain handlers only; install stays `inst_*`; CLI surface `app_*`; messages only via Output.

Illustrative sanitize sketch (portable — specialize codes/messages):

```sh
# GENERAL PURPOSE: Reject unsafe timer names before any path I/O.
# template-example-function — not product law
{{DOMAIN_PREFIX}}_sanitize_name() {
    name="$1"
    case "$name" in
        ""|*/*|*\\*|*..*|*" "*|*\'*|*\"*|*\$*|*\`*|*\|*|*\;*|*\**|*?*|*<*|*>*|*:*)
            {{DOMAIN_PREFIX}}_domain_fail "invalid_name" "Invalid timer name."
            return 1
            ;;
    esac
    TIMER_NAME="$name"
    return 0
}
```

---

## 10. Ownership map (anti-duplication)

| Concern | Owner |
|---------|--------|
| Domain verbs / features / help / about domain rows | **This template** → specialized domain REQ |
| Domain timer **record** modes + leaf pattern | **This template** §5.2 → domain REQ |
| Storage isolation + resolve priority + `util_resolve_storage` | **Required** storage REQ (`template-shell-cli-storage`) |
| Temp roots / `mktemp` / cleanup / noexec | **Required** temp REQ (`template-temp-file-system`) |
| Dispatcher / full command table / empty-argv | CLI interface template / REQ |
| `out_*` / channels | Output template / REQ |
| Prefix table | Modular function design template / REQ |
| Domain re-run matrix | Idempotency template / REQ |
| Local binary install algorithm | Local self-management (temps align with **temp REQ**) |
| Interactive uninstall confirm | Interactive template / REQ |

---

## 11. How to specialize

1. Create/update Active **temp** REQ from `template-temp-file-system.md` (register it).  
2. Create/update Active **storage** REQ from `template-shell-cli-storage.md` (register it).  
3. Create/update **one** Active `docs/requirements/requirement-domain-{{DOMAIN_SUBJECT}}.md`.  
4. Fill Implementation Notes; domain notes **point** to storage REQ (isolation/resolve) and temp REQ (mktemp/cleanup).  
5. Register domain in `docs/requirements/index.md` (Area **domain**).  
6. Same change: CLI interface lists domain rows, wires `--persist`, free-token name rule (§4.1).  
7. Implement `{{DOMAIN_PREFIX}}_*` handlers + `util_resolve_storage`; install staging honors temp REQ; product source cites **live requirements** only.  
8. Optional domain proof suite (when claimed): start/stop/status/list, JSON, persist, kill/reset, invalid name, already-running, no_timer.  
9. Do **not** invent a second Active domain SSOT.

---

## 12. Definition of done (specialization)

Not done until:

1. All six domain commands specialized with §5 semantics.  
2. Path-safe names + dual storage modes.  
3. Human/JSON contracts and stable error codes.  
4. Help §6 + about §7.  
5. Registry lists Active domain SSOT **and** Active storage REQ **and** Active temp REQ.  
6. **CLI peer aligned** per §4.1.  
7. **Storage peer aligned** per §4.2.  
8. **Temp peer aligned** per §4.3 (`mktemp`/cleanup/temp roots).  
9. Protection Rule not violated.

---

## 13. Why this pattern exists (CIAO)

- **Caution:** Path-safe names; fail closed on missing timer / already-running start.  
- **Intentional:** Six verbs + two storage modes are explicit product promise.  
- **Anti-fragile:** Volatile fallback; empty list is success; no root required.  
- **SSOT of output:** Domain messaging via Output only.  
- **Single entry:** Domain routes through `app_main` (or equivalent).  
- **Type 0 only:** Domain remains invoker ops (Principle 9).  
- **Over-protect:** Domain law in one SSOT; not only in README/tests.

---

## 14. Protection Rule (Sacred)

Future agents **MUST NOT**:

1. Remove domain verbs without superseding domain law.  
2. Put domain business logic under install-only prefixes.  
3. Allow path-unsafe timer names.  
4. Silently overwrite an already-running timer on `start`.  
5. Report missing timer as success for stop/status/kill/reset.  
6. Require root/system-user solely for named-timer domain.  
7. Drop dual storage modes without explicit law change.  
8. Emit domain UX with raw `echo`/`printf` outside Output.  
9. Freeze a single product brand as universal law in this template.  
10. Create parallel Active domain-requirements files without supersession.  
11. Confuse domain already-running **fail** with local install already-installed **success no-op**.  
12. Assume `/dev/shm` or `$HOME` always writable without fallback/fail-closed.  
13. Replace domain timer records with install-staging `mktemp` temps, or restate full temp-file-system install chain as domain law.  
14. Drop app+user isolation from timer leaf paths “for simplicity.”  
15. Specialize domain verbs without aligning CLI command table / `--persist` / free-token / help section (dual-SSOT drift).  
16. Move domain **behavior** law into the CLI interface REQ (CLI routes; domain owns semantics).  
17. Specialize this mold **without** an Active storage REQ (from `template-shell-cli-storage`) — storage peer is **mandatory**.  
18. Duplicate a conflicting product-wide resolve chain inside domain law that ignores the storage REQ.  
19. Specialize this mold **without** an Active temp REQ (from `template-temp-file-system`) — temp peer is **mandatory**.  
20. Treat deterministic timer epoch leaves as if they were install-staging temps (wrong layer).

**Violating this rule is a critical domain-pattern regression.**

---

## 15. Related portable artifacts

| Artifact | Role |
|----------|------|
| `template-cli-interface.md` | Routing / flags / help shape — **required peer** (§4.1) |
| `template-shell-cli-storage.md` | Isolation + resolve — **required peer** (§4.2) |
| `template-temp-file-system.md` | Temp roots / `mktemp` / cleanup — **required peer** (§4.3) |
| `template-output-requirements.md` | Output SSOT |
| `template-modular-function-design.md` | Domain prefix placement |
| `template-idempotency.md` | Re-run matrices |
| `template-interactive-vs-noninteractive.md` | No domain prompts |
| `template-shell-local-self-management.md` | Contrast lifecycle; install stage (uses temp REQ) |
| Term `domain-requirements` | Four pillars |
| Term `external-timer` / `internal-timer` | Feature kinds (subset relationship) |
| `template-shell-internal-volatile-timer.md` | **Base mold** this file expands from (volatile internal; **no** storage/CLI peers) |
| Term `path-safe-name` | Name gate |
| Term `temp-file-system` | Temp policy glossary |

---


## Design-time verification

**Law mold:** `LM-NAMED-TIMER-DOMAIN`  
**Base mold:** `LM-SHELL-INTERNAL-VOLATILE-TIMER`  
**Proof mold:** `../tests/template-domain-test-plan.md` (`PM-DOMAIN-TEST-PLAN`)

| TP family / ID | Intent | Planned suite |
|----------------|--------|---------------|
| **TP-<SUBJECT>-01** | Help lists domain verbs/flags | product domain suite |
| **TP-<SUBJECT>-02** | start / status / list / stop human | same |
| **TP-<SUBJECT>-03** | already-running start fails | same |
| **TP-<SUBJECT>-04** | JSON contracts + numeric elapsed / nested list | same |
| **TP-<SUBJECT>-05** | `no_timer` codes | same |
| **TP-<SUBJECT>-06** | kill / reset | same |
| **TP-<SUBJECT>-07** | `invalid_name` | same |
| **TP-STORAGE-01** | Volatile domain record path | shared dual-storage cases |
| **TP-STORAGE-02** | `--persist` start/list/stop | same |
| **TP-STORAGE-03** | Corrupted state | **n/a** unless product claims |
| **TP-PAYLOAD-*** | Type O-P payload | **n/a** unless Type O-P |
| **TP-CLI-05** | Shell about storage (peer) | CLI suite — not domain records |

Replace `<SUBJECT>` with domain basename subject (e.g. `TIMER`, `POMO`, `COUNTDOWN`).  
**MUST NOT** ship product maps as **`TP-DOM-*`**.

**RTM:** `../tests/template-requirement-test-traceability.md`

**Specialize checklist (fail closed):**

- [ ] Exactly one Active `requirement-domain-{{DOMAIN_SUBJECT}}.md` (Area `domain`)  
- [ ] CLI peer lists domain verbs + `--persist`  
- [ ] Storage peer wired (main + about) — not dead util  
- [ ] Temp peer Active; `TMPDIR` inherits storage root when both wired  
- [ ] Output peer Active  
- [ ] DTV rows above mapped in product `reviews/test-plan.md`  
- [ ] Suite green for claimed TP rows  


**Last Updated**: 2026-08-11  
**Owner**: {{OWNER}}  
**Version history:**  
- **1.7.0**: Design-time verification + specialize checklist; Type O empty-argv clarity; optional idempotency peer.
- **1.6.0**: **Expansion framing** — full domain = base internal-volatile + persistency + CLI + peers (§1.0).  
- **1.5.0**: **Mandatory temp-file-system REQ peer** (§1.1, §4.3) alongside storage + CLI.  
- **1.4.0**: **Mandatory storage REQ peer** (§1.1, §4.2).  
- **1.3.1**: Terminology: **internal-timer ⊆ external-timer** (subset); this mold = full domain specialization.  
- **1.3.0**: Terminology link external-timer / internal-timer.  
- **1.2.0**: §4.1 CLI peer alignment contract.  
- **1.1.0**: §5.2 domain state storage vs temp/scratch ownership.  
- **1.0.0**: Initial portable named-timer domain features.

**Alignment**: external-timer · internal-timer · base template-shell-internal-volatile-timer · domain-requirements · domain-surface · path-safe-name · temp-file-system · shell-function-naming-convention · output SSOT · idempotency-rule · interactive-vs-noninteractive · local-self-managed (contrast) · template-cli-interface · template-shell-cli-storage (**required**) · template-temp-file-system (**required**) · CIAO v2.10.2 / CIAO-Lite
