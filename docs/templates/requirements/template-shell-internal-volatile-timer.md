---
name: shell-internal-volatile-timer
id: LM-SHELL-INTERNAL-VOLATILE-TIMER
kind: law-mold
description: >
  Portable law mold. Cite as LM-SHELL-INTERNAL-VOLATILE-TIMER (path secondary).
---

**file**: template-shell-internal-volatile-timer.md  
**Status**: Active (Version 1.2.0 – DTV + expand checklist; Base mold: shell internal-timer, volatile only; domain expands from this)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered / Over-protect)

## 1. Purpose

This template is the portable **base mold** for **shell internal-timer (volatile)**: process/stage elapsed-time instrumentation for **this product’s own** work (install step, handler, pipeline stage, test probe)—**not** a user/app-facing named-timer domain CLI.

**Role in the timer mold family:**

```text
template-shell-internal-volatile-timer   ←  THIS FILE (base)
        │
        │  expand: multi-name · persistency · CLI catalog · storage/temp peers · domain pillars
        ▼
template-named-timer-domain              ←  full-domain external-timer (expanded)
```

| Mold | Audience | Modes | Peers |
|------|----------|-------|-------|
| **This file (base)** | Product-internal instrumentation | **Volatile only** | **None** mandatory |
| `template-named-timer-domain` | Users + other apps | Volatile **+ persistent** | CLI + storage + temp (**required**) |

**Terminology:**

| Term | Role |
|------|------|
| [internal-timer](../terminologies/internal-timer.md) | **Subset** of external-timer; this mold = **volatile** specialization (default mode) |
| [external-timer](../terminologies/external-timer.md) | **Superset** family |
| Expanded domain mold | `template-named-timer-domain.md` — full user/app domain built **on top of** this base |

**Specialize into (product law when claimed):** e.g. `requirement-shell-internal-volatile-timer.md`. **No** domain SSOT required for internal-only probes. **No** storage/CLI/temp requirement peers for this mold alone.

---

## 1.1 What this mold does **not** require

| Peer | Expanded named-timer domain mold | **This base mold** |
|------|----------------------------------|--------------------|
| CLI interface REQ | **Required** | **Not required** — no user domain verb table |
| Storage REQ (`util_resolve_storage` law) | **Required** | **Not required** — volatile state prefers in-process / RAM |
| Temp-file-system REQ | **Required** (install staging peer of domain mold) | **Not required** for the timer itself (install may still have its own temp law) |
| Domain REQ four pillars | **Required** | **Not required** — instrumentation, not domain catalog |

---

## Terminologies (mandatory)

| Term | Path | SSOT type | Role in this template |
|------|------|-----------|------------------------|
| Internal-timer | `docs/terminologies/internal-timer.md` | product-law / feature kind | **This mold** (volatile default mode) |
| External-timer | `docs/terminologies/external-timer.md` | product-law / feature kind | Superset family |
| Single source of truth of output | `docs/terminologies/single-source-of-truth-of-output.md` | channel-io | Optional report of elapsed via Output |
| Shell function naming convention | `docs/terminologies/shell-function-naming-convention.md` | meta / naming | Prefixed helpers (e.g. `util_*` / `{{PREFIX}}_*`) |
| Idempotency rule | `docs/terminologies/idempotency-rule.md` | product-law / re-run | Re-start while running = fail or reset policy |
| Temp file system | `docs/terminologies/temp-file-system.md` | runtime storage | **Contrast** — install temps ≠ timer state |
| Path-safe name | `docs/terminologies/path-safe-name.md` | product-law / identity | Optional stage id; not full domain name catalog |

**Do not re-own here:** full domain help/about, CLI empty-argv, install binary placement, durable persistent internal-timer (separate mold or product law), full-domain persistency.

---

## 2. Placeholders (specialize only)

| Placeholder | Meaning |
|-------------|---------|
| `{{APP_NAME}}` | Product identity (for isolation labels if any) |
| `{{PREFIX}}` | Function prefix for helpers (e.g. `util` or `timer_int`) |
| `{{STAGE_ID}}` | Optional stage label (install, fetch, domain-handler) |

---

## 3. Expansion map (base → named-timer domain)

When specializing **full domain**, start from this base and **add** features (do **not** thin domain down into this mold as the expansion story):

| This mold (internal volatile base) | Expanded: `template-named-timer-domain` |
|------------------------------------|------------------------------------------|
| API helpers only: start/stop/status/elapsed | **+** user CLI verbs `start`/`stop`/`status`/`list`/`kill`/`reset` |
| Optional stage id | **+** path-safe **user** multi-timer names + default name |
| **Volatile only** (in-process epoch / RAM) | **+** domain **persistent** mode + `--persist` |
| In-process shell vars (or optional shm probe) | **+** durable epoch **files** + `{{DOMAIN_PREFIX}}_resolve_base_dir` |
| **No** storage/CLI/temp REQ peers | **+** mandatory CLI + storage + temp REQs |
| **No** domain help/about pillars | **+** four domain-requirements pillars |
| Double-start fail-closed | **Keep** as already-running fail on domain `start` |
| Stop/status without start fail-closed | **Keep** as `no_timer` on domain stop/status/kill/reset |

**Direction rule:** Internal volatile is the **foundation**. Named-timer domain is the **expansion**. Do not reverse the story to “domain is parent and this is only a thin bootstrap copy” as product-law framing (historical derivation of text is fine; **normative** layering is base → expand).

---

## 4. Core contracts (normative)

### 4.1 Mode

1. This mold is **internal-timer** + mode **volatile** only.  
2. **Default** for internal-timer family is volatile — this mold **is** that default.  
3. **MUST NOT** claim persistent/durable internal-timer under this mold alone (use product law or a persistence-focused mold later).

### 4.2 Lifecycle API (helpers — not user CLI)

| Operation | Required behavior | Typical non-zero |
|-----------|-------------------|------------------|
| **start** | Record start epoch (monotonic or `date +%s` as designed); mark running | already running → fail (or document reset) |
| **stop** | Compute elapsed; clear running state; return/report elapsed | not running → fail |
| **status** / **elapsed** | Report elapsed **without** clearing (if designed) | not running → fail or zero per law |
| **reset** / **cancel** | Clear without success elapsed (optional) | — |

**Not required:** `list` multi-name catalog, path-safe user names, `--persist`, domain help rows.

### 4.3 State (volatile)

| Rule | Meaning |
|------|---------|
| Holding place | Shell globals / function-local state, or process memory — **lost on process exit** |
| Optional RAM file | Product **MAY** use `/dev/shm` for multi-function visibility in one process tree — **still volatile**; **MUST NOT** invent a mandatory storage REQ for this mold |
| Isolation | If using shared mounts, include app identity (and user if multi-user) |
| Not durable domain files | **MUST NOT** use full-domain timer leaf catalog as the only internal probe design |

### 4.4 Output

1. Elapsed **MAY** go to debug/log only (`out_debug`) or structured fields when product wants metrics.  
2. User-facing product messages still go through Output SSOT when emitted.  
3. **MUST NOT** require JSON domain types (`list`/`status` domain objects) unless product also has full domain law.

### 4.5 Fail-closed

| Case | Prefer |
|------|--------|
| Start while already running | Fail closed (or explicit reset then start) — no silent overwrite |
| Stop/status with no start | Fail closed or documented zero |
| Clock / epoch unreadable | Fail closed |

---

## 5. Function sketch (template-example-function)

Portable illustration only — not product law:

```sh
# GENERAL PURPOSE: Volatile internal-timer start (process-scoped epoch).
# Base mold: no CLI domain verbs, no storage REQ peer.
{{PREFIX}}_int_timer_start() {
    : "${{{PREFIX}}_INT_TIMER_RUNNING:=0}"
    : "${{{PREFIX}}_INT_TIMER_EPOCH:=0}"
    if [ "${{{PREFIX}}_INT_TIMER_RUNNING}" -eq 1 ]; then
        out_debug "internal volatile timer already running"
        return 1
    fi
    {{PREFIX}}_INT_TIMER_EPOCH=$(date +%s 2>/dev/null) || return 1
    {{PREFIX}}_INT_TIMER_RUNNING=1
    return 0
}

{{PREFIX}}_int_timer_stop() {
    : "${{{PREFIX}}_INT_TIMER_RUNNING:=0}"
    : "${{{PREFIX}}_INT_TIMER_EPOCH:=0}"
    : "${{{PREFIX}}_INT_TIMER_LAST_ELAPSED:=0}"
    now=$(date +%s 2>/dev/null) || return 1
    if [ "${{{PREFIX}}_INT_TIMER_RUNNING}" -ne 1 ]; then
        out_debug "internal volatile timer not running"
        return 1
    fi
    elapsed=$((now - {{PREFIX}}_INT_TIMER_EPOCH))
    # Primary return: global (MUST use bare call — not $(stop) — so state clears here)
    {{PREFIX}}_INT_TIMER_LAST_ELAPSED="${elapsed}"
    {{PREFIX}}_INT_TIMER_RUNNING=0
    {{PREFIX}}_INT_TIMER_EPOCH=0
    printf '%s\n' "${elapsed}"   # optional mirror; not SSOT under command substitution
    return 0
}
```

**Subshell rule:** Call stop/elapsed bare, then read `{{PREFIX}}_INT_TIMER_LAST_ELAPSED`. Do not rely on `$(stop)` to mutate process state.

Prefix ownership: prefer `util_*` or a dedicated internal prefix—not install-only `inst_*`, not user domain catalog as CLI verbs.

---

## 6. Ownership map

| Concern | Owner |
|---------|--------|
| Internal volatile start/stop/elapsed | **This template** → product REQ when specialized |
| Full user/app named-timer domain (expansion) | `template-named-timer-domain` + domain REQ + CLI/storage/temp peers |
| Install binary / `mktemp` stage | Local self-management + temp REQ (when claimed) |
| Generic storage resolve law | Storage REQ (when claimed)—**not** required by this mold |

---

## 7. How to specialize

1. Create `requirement-shell-internal-volatile-timer.md` (recommended when product claims internal probes as law) **or** document helpers under modular notes only for informal use.  
2. Implement `{{PREFIX}}_int_timer_*` (or `util_int_timer_*`) in ship unit.  
3. Call from install/handlers/tests — **do not** register as domain CLI commands unless full domain law also exists.  
4. Cite live requirements in product source only.  
5. **Do not** invent storage/CLI/temp REQs solely because this mold is used.  
6. When expanding to full domain, specialize `template-named-timer-domain` **plus** its peers — keep this base law for internal probes if still claimed.

---

## 8. Definition of done (specialization)

- [ ] Volatile-only internal start/stop (or equivalent) implemented  
- [ ] Double-start policy fail-closed (or explicit reset)  
- [ ] Stop without start fail-closed (or documented)  
- [ ] No mandatory storage/CLI/temp peers claimed for this mold alone  
- [ ] Not confused with full-domain external-timer help/command table  
- [ ] If product law written: registered `requirement-*.md`; this template not product-source authority  

---

## 9. Protection Rule (Sacred)

Future agents **MUST NOT**:

1. Reintroduce **mandatory** storage or CLI requirement peers for this mold “to match named-timer domain.”  
2. Turn internal volatile helpers into user domain verbs without full-domain law + CLI/storage/temp peers.  
3. Silently overwrite an already-running internal timer without policy.  
4. Claim **persistence** under this volatile-only mold without a separate persistence design.  
5. Hardcode product brands into this blank as universal law.  
6. Use install-staging `mktemp` temps as the internal-timer state SSOT without distinguishing temp law.  
7. Invert layering so full domain is treated as the **base** and this mold as a disposable thin copy with no product-law role.

**Violating this rule is a critical internal-timer mold regression.**

---

## 10. Related portable artifacts

| Artifact | Role |
|----------|------|
| `template-named-timer-domain.md` | **Expansion** of this base (full domain; storage/CLI/temp requires) |
| `template-shell-cli-storage.md` | Full-domain peer only — **not** required here |
| `template-cli-interface.md` | Full-domain peer only — **not** required here |
| `template-temp-file-system.md` | Install temps — orthogonal |
| `template-output-requirements.md` | Optional elapsed reporting |
| Term `internal-timer` | Subset + volatile default |
| Term `external-timer` | Superset family |

---


## Design-time verification

**Law mold:** `LM-SHELL-INTERNAL-VOLATILE-TIMER`  
**Expansion mold:** `LM-NAMED-TIMER-DOMAIN`

| Gate | Intent | Guidance |
|------|--------|----------|
| Internal probe | start/stop/elapsed for product-own work | product suite or checklist |
| No domain verbs | Do not expose user `start|list|…` from this mold alone | review |
| Debug elapsed | `--debug` named-stage elapsed on stderr when claimed | product TP-CLI family |
| Expand checklist | Before full domain claim | section below |

### Expand-to-domain checklist (base → full)

Use `template-named-timer-domain.md` for user-facing named timers:

- [ ] Multi-name + path-safe gate  
- [ ] Persistent mode + `--persist`  
- [ ] CLI + storage + temp + output peers Active  
- [ ] Four domain pillars  
- [ ] `TP-<SUBJECT>-*` under `PM-DOMAIN-TEST-PLAN`  

**RTM:** `../tests/template-requirement-test-traceability.md`


**Last Updated**: 2026-08-11  
**Owner**: {{OWNER}}  
**Version history:**  
- **1.2.0**: Design-time verification + expand-to-domain checklist.
- **1.1.0**: Reframe as **base mold**; named-timer domain **expands from** this (persistency, CLI, peers).  
- **1.0.0**: Initial volatile internal-timer only; **no** storage/CLI (or temp) requirement peers.

**Alignment**: internal-timer ⊆ external-timer · volatile default · base → expand to template-named-timer-domain · output SSOT · shell-function-naming-convention · CIAO v2.10.2 / CIAO-Lite
