---
name: payload-online-install
id: LM-PAYLOAD-ONLINE-INSTALL
kind: law-mold
description: >
  Portable law mold. Cite as LM-PAYLOAD-ONLINE-INSTALL (path secondary).
---

**file**: template-payload-online-install.md  
**Status**: Active (Version 1.0.0)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

## 1. Purpose

This template is the portable **Single Source of Truth for payload online installers** (**Type O-P**): products whose one-liner / empty-argv contract **reduces end-user installation steps** by ensuring both:

1. **Ship unit** (the CLI script/binary on the install channel)  
2. **Payload** (toolchains, packages, projects, runtimes the product exists to set up)

It is **not** the same as **`template-online-install.md`** (Type O-S **script-alone** online install: place/update the CLI only).

| Template | Product class | Empty argv / one-liner |
|----------|---------------|------------------------|
| **`template-online-install.md`** | Type O-S script-alone | Ship-unit install-ensure only |
| **This file** | Type O-P [payload installer](../../terminologies/payload-installer.md) | **Combined ensure**: ship unit + payload |

**Specialize into:** `requirement-shell-payload-online-install.md` (or product-chosen key) + domain requirement for payload pins.

**Peers (consume, do not re-own):**  
- Ship-unit channel / atomic place / checksum → `template-online-install.md` (ship-unit primitives only)  
- Empty-argv matrix depth → `template-shell-cli-zero-arguments.md` § Type O-P  
- Ship-unit lifecycle `self-update` / `self-uninstall` / `version-check` → `template-self-management.md`  
- Output SSOT → `template-output-requirements.md`

---

## Terminologies (mandatory)

| Term | Path | Role |
|------|------|------|

| **Project templates** | `docs/terminologies/project-templates.md` | `meta-catalog` | What law molds are; specialize-out target |
| **Docs folder structure** | `docs/terminologies/docs-folder-structure.md` | `policy` | Where this mold lives vs product law / tests |
| **No-hardcode policy** | `docs/terminologies/no-hardcode-policy.md` | `policy` | Placeholders only in portable molds |
| **Dual policies** | `docs/terminologies/dual-policies.md` | `policy` | No-placeholder × no-hardcode balance |
| **Terminology policy for templates** | `docs/terminologies/terminology-policy-for-templates.md` | `policy` | Mandatory Terminologies section rules |
| **SSOT-terminology policy for templates** | `docs/terminologies/ssot-terminology-policy-for-templates.md` | `policy` | SSOT type column on rows || Payload installer | `docs/terminologies/payload-installer.md` | **Primary class** this template implements |
| Type O empty argv | `docs/terminologies/type-o-empty-argv.md` | Empty-argv umbrella; O-P depth |
| Online install script | `docs/terminologies/online-install-script.md` | Channel / pipe distribution (ship unit) |
| Self-uninstall | `docs/terminologies/self-uninstall.md` | **Ship-unit** remove only (`self-uninstall`) |
| Self-management | `docs/terminologies/self-management.md` | Ship-unit lifecycle umbrella |
| Domain surface | `docs/terminologies/domain-surface.md` | Payload ops surface |
| Ship unit | `docs/terminologies/ship-unit.md` | CLI artifact |
| Shell CLI bootstrap | `docs/terminologies/shell-cli-bootstrap.md` | Pipe must call main; no silent no-op |

---

## 2. Command vocabulary (normative — do not collapse)

Payload online installers expose **two remove/update families**. Mixing them is a critical defect.

### 2.1 Ship-unit commands (CLI self-care)

| Command | Target | Owner template |
|---------|--------|----------------|
| `self-update` | Replace/upgrade the **managed CLI ship unit** from channel | `template-self-management.md` |
| `self-upgrade` | **Optional alias** of `self-update` (same handler) when advertised | this + self-management |
| `self-uninstall` | Remove the **managed CLI binary** only | `template-self-management.md` |
| `version-check` | Local vs remote **ship-unit** VERSION | self-management |
| `version` / `about` / `help` | Diagnostics / usage | CLI interface |

### 2.2 Payload commands (environment / domain)

| Command | Target | Owner |
|---------|--------|-------|
| `install` | **Payload ensure** only (toolchains, packages, project scaffold). **MUST NOT** mean “only download the ship unit” when both layers exist. | **This template** + domain requirement |
| `uninstall` | **Payload remove** only (e.g. managed project/data this product owns). **MUST NOT** remove the CLI ship unit. | **This template** + domain requirement |
| `run` (when designed) | Payload ensure + execute product | domain requirement |
| `reinstall` (when designed) | Force payload re-ensure (and/or ship unit if documented) | product requirement |

### 2.3 Forbidden collapses

| Forbidden | Why |
|-----------|-----|
| `uninstall` removes the CLI binary | Confuses payload with ship unit; use `self-uninstall` |
| `self-uninstall` deletes domain project / SDKMAN home as primary path | Scope creep; payload `uninstall` owns payload |
| `install` only places ship unit then exits on a Type O-P product | Defeats payload installer purpose |
| Documenting Type O-S “already installed” binary no-op as full Type O-P success | Incomplete environment |
| Type N empty argv = help for a payload online product | Wrong UX |

---

## 3. Empty argv / one-liner (Type O-P combined ensure)

### 3.1 Normative flow

```text
curl | sh  OR  bare {{APP_NAME}}  (empty argv)
        │
        ▼
  bootstrap → app_main always runs (no basename gate)
        │
        ├─ SHIP UNIT
        │     missing  → self-install (online-install primitives)
        │     present  → non-interactive: self-update when remote newer / policy
        │
        └─ PAYLOAD
              ensure packages / toolchains / project (domain SSOT)
              optional run when product default is run
```

### 3.2 Case matrix

| Case | Empty argv (force off) |
|------|------------------------|
| **A. Ship unit not installed** | Ship-unit install **then payload ensure** — **MUST NOT** exit after binary only |
| **B/C. Ship unit installed** | Non-interactive ship-unit upgrade policy + **payload ensure** — not help; not binary-only no-op |
| **Failure** | Non-zero; **loud** `out_*` / `out_json_error` — never silent success |

### 3.3 Modes

| Mode | Behavior |
|------|----------|
| Non-interactive / pipe / quiet / json | No hang; auto ship-unit + payload; JSON purity |
| Interactive TTY | MAY confirm ship-unit first install; on accept continue to payload |
| Failure (network, checksum, payload) | Non-zero; visible error |

---

## 4. Success / error message coverage (mandatory)

All user-facing outcomes **MUST** go through output SSOT (`out_success` / `out_info` / `out_warn` / `out_error` / `out_die` / `out_json` / `out_json_error`). Templates and requirements **MUST** cover these cases:

### 4.1 Ship unit

| Case | Human (minimum) | JSON (when `--json`) | Exit |
|------|-----------------|----------------------|------|
| Ship install success | success: installed to path | `out_success` + path | 0 |
| Ship already present (ensure only path) | success or info already installed | `out_success` | 0 |
| Ship install failure (network/checksum/io) | error + reason | `out_error` + code | ≠0 |
| Self-update already latest | success already latest | `out_success` | 0 |
| Self-update upgraded | success new version | `out_success` | 0 |
| Self-update refuse downgrade | warn/error; no silent replace | structured refuse | ≠0 without force |
| Self-uninstall confirm required | error/confirm_required | `confirm_required` | ≠0 |
| Self-uninstall success | success removed | `out_success` | 0 |
| Self-uninstall already absent | success no-op | `out_success` | 0 |

### 4.2 Payload

| Case | Human (minimum) | JSON (when `--json`) | Exit |
|------|-----------------|----------------------|------|
| `install` / payload ensure success | success payload ready (+ project path) | `out_success` + fields | 0 |
| Payload ensure failure | error which step failed | `out_error` + code | ≠0 |
| `uninstall` success | success payload removed | `out_success` | 0 |
| `uninstall` confirm required | refuse without force | `confirm_required` | ≠0 |
| `uninstall` already absent | success no-op | `out_success` | 0 |
| Empty argv combined success | visible ship and/or payload progress + final OK | structured success when json | 0 |
| Empty argv silent no output | **FORBIDDEN** | **FORBIDDEN** | treat as defect |

### 4.2b Curl one-liner silent-failure tests (mandatory when claiming `curl | …`)

Specialize and implement **`../tests/template-online-curl-install-test-plan.md`** (TP-CURL-*):

| Core | Assert |
|------|--------|
| First / second `curl \| bash` (local channel) | Not silent; binary / payload path entered |
| bashrc + vendor init under `set -u` via pipe | Not silent (nounset abort class) |
| Bad channel / refuse URL | Loud transport or product error |
| `curl \| sh` if product requires bash | Explicit bash requirement message |
| `bash -s -- version` | Exit 0 + version text |

Default CI uses **local channel only**; optional published-URL smoke behind env flag.

### 4.3 Shared

| Case | Requirement |
|------|-------------|
| Unknown command | `out_die` / JSON error; pointer to help |
| Quiet mode | Suppress non-error human chatter; errors still visible |
| JSON mode | No human banners on stdout; one JSON object |

---

## 5. Relationship to script-alone online install

| Concern | Type O-S (`template-online-install.md`) | Type O-P (this template) |
|---------|----------------------------------------|---------------------------|
| Purpose | Distribute a CLI | Distribute CLI **and** set up environment |
| Empty argv | Ship-unit ensure | Combined ensure |
| `install` command | May equal ship-unit ensure | **Payload** ensure |
| `uninstall` | Prefer not used online (use `self-uninstall`) | **Payload** remove |
| `self-uninstall` | Remove CLI | Remove CLI only |
| Domain requirement | Optional | **Mandatory** for payload list |

---

## 6. Protection Rule (Sacred)

**MUST NOT:**

1. Specialize this template and then implement Type O-S-only empty argv (binary place + exit).  
2. Use `uninstall` for CLI removal or `self-uninstall` as the only way to remove payload.  
3. Route empty argv to help.  
4. Silent one-liner success (no message, no ship unit, no payload).  
5. Hardcode one product’s payload pins into this template — use `{{…}}` / product requirements.  
6. Re-own ship-unit download algorithms here (reuse online-install + checksum templates).  
7. Skip message coverage for cases in §4.

---

## 7. Acceptance criteria

- [ ] Product Implementation Notes state **Type O-P** and cite this specialized requirement.  
- [ ] Command table separates ship-unit (`self-*`) vs payload (`install` / `uninstall`).  
- [ ] Empty argv combined ensure implemented; first pipe does not exit after binary only.  
- [ ] All §4 cases have message + exit contract.  
- [ ] Tests: stdin pipe smoke; payload `install`/`uninstall`; ship `self-update`/`self-uninstall`; silent-fail detection.  
- [ ] Help lists every routed command; no orphan ads.

---

## 8. How to use

1. Classify product as Type O-P ([payload-installer](../../terminologies/payload-installer.md)).  
2. Specialize this file → `docs/requirements/requirement-shell-payload-online-install.md`.  
3. Keep ship-unit channel law from online-install + self-management requirements.  
4. Domain requirement owns payload pins and order.  
5. Wire dispatcher + tests; cite **requirement**, not this template, from product source.


## Design-time verification

| TP family / ID | Proof mold | Planned suite |
|----------------|------------|---------------|
| **TP-LC-01–03** combined + payload install/uninstall | `../tests/template-install-lifecycle-test-plan.md` | `tests/test_install_lifecycle.sh` |
| **TP-PAYLOAD-*** domain ensure | `../tests/template-domain-test-plan.md` | `tests/test_domain.sh` |
| **TP-CURL-*** one-liner | `../tests/template-online-curl-install-test-plan.md` | `tests/test_online_curl_install.sh` |

**RTM:** `../tests/template-requirement-test-traceability.md`

**Last Updated**: 2026-07-20  
**Version history:**  
- **1.0.0** (2026-07-20): Initial Type O-P template; command split; message matrix; separation from script-alone online-install.
