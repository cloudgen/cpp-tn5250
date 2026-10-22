---
name: sky130-pdk-ensure
id: LM-SKY130-PDK-ENSURE
kind: law-mold
description: >
  Portable law mold. Cite as LM-SKY130-PDK-ENSURE (path secondary).
  SkyWater SKY130 open PDK ensure: package map then managed prebuilt (volare);
  probe PDK_ROOT; no open_pdks git+make as default.
---

**file**: template-sky130-pdk-ensure.md  
**Status**: Active (Version 1.0.0)  
**Project**: Any CIAO-Lite Project (reusable template) that ensures **SkyWater SKY130** for open IC design  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

## 1. Purpose

Define portable **Sky130 PDK ensure** law: how a CLI (or installer) makes a **SkyWater 130 nm open process design kit** ready for use with open flows (e.g. xschem-oriented libraries), including:

1. **Probe** success (`PDK_ROOT` + `sky130A` / family layout)  
2. **Ordered ensure strategies** (distro packages → managed prebuilt)  
3. **Idempotent re-run** when already ready  
4. **Fail closed** after all strategies fail — with actionable messages  

**Specialize into:** `requirement-sky130-pdk.md` (or product-chosen key) under `docs/requirements/`.  
**Peers (do not re-own):** domain surface / four pillars → domain requirement; Type O-P command split → `template-payload-online-install.md`; Type 1 elev TTY traps → `template-shell-script-coding.md` §8.1; multi-strategy language → term `payload-ensure-strategy`.

---

## Terminologies

| Term | Path | SSOT type | Role |
|------|------|-----------|------|
| **Payload ensure strategy** | `docs/terminologies/payload-ensure-strategy.md` | `product-law` | Ordered strategies; PES-* failure classes |
| **Payload installer** | `docs/terminologies/payload-installer.md` | `product-law` | Type O-P ship + payload |
| **Domain surface** | `docs/terminologies/domain-surface.md` | `product-law` | Domain commands |
| **Three-layer privilege** | `docs/terminologies/three-layer-privilege.md` | `product-law` | Type 0/1 for packages |
| **Interactive vs noninteractive** | `docs/terminologies/interactive-vs-noninteractive.md` | `runtime-mode` | No hang in machine modes |
| **Docs folder structure** | `docs/terminologies/docs-folder-structure.md` | `policy` | Mold placement |
| **No-hardcode policy** | `docs/terminologies/no-hardcode-policy.md` | `policy` | `{{PLACEHOLDER}}` in molds |
| **Dual policies** | `docs/terminologies/dual-policies.md` | `policy` | Complete specialized REQs |

**Policies:** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

---

## 2. Core rules (mandatory when mold is specialized)

### 2.1 Identity and probe

1. **MUST** treat **Sky130** as a first-class payload component (aliases `pdk` / `sky130` when the product uses those targets).  
2. **Probe success** **MUST** mean a usable PDK tree is detectable:  
   - `PDK_ROOT` set or resolved to a directory containing **`sky130A`** (or product-declared family, e.g. `sky130B`), **or**  
   - managed prefix under `{{PDK_MANAGED_ROOT}}` / product data dir with the same layout.  
3. **MUST NOT** claim PDK success if the probe fails after ensure.  
4. On success, **MUST** print or expose `PDK_ROOT` for operator shell/xschemrc (human and optional JSON).

### 2.2 Ordered ensure strategies

5. Strategies **MUST** run in this order until probe succeeds (or all fail):

| Order | Strategy ID | Behavior | Privilege |
|-------|-------------|----------|-----------|
| **0** | `already-ready` | Probe true → success no-op unless `{{FORCE_REINSTALL}}` / `--force` | Type 0 |
| **1** | `package-map` | If distro package list non-empty → Type 1 package install | Type 1 |
| **2** | `managed-prebuilt-volare` | Managed **volare** prebuilt into managed prefix (private venv under product data dir) | Type 1 only for python3/venv packages; download as invoker |
| — | `fail-closed` | Loud error; list next steps | — |

6. **MUST NOT** use **open_pdks `git clone` + multi-hour `make`** as the **default** strategy.  
7. **Empty package map** **MUST NOT** be the only strategy when Sky130 is in the product’s **default** ensure set (e.g. bare `install` → `all`) — **PES-EMPTYMAP** / **PES-DEFAULTALL** (term `payload-ensure-strategy`).  
8. **MUST** warn that strategy 2 downloads a **large** tree (network + disk + time) before/while enabling.

### 2.3 Volare managed-prebuilt details (when strategy 2 is claimed)

9. **MUST** resolve the volare sky130 build via remote index when pin is `latest` / empty:  
   `volare ls-remote --pdk sky130` → first line (or product-documented selection).  
10. **MUST NOT** hardcode a **stale** build hash that is not on the remote list as the only default.  
11. Explicit pin env **MAY** be `{{VOLARE_SKY130_VERSION_ENV}}` (e.g. full hash); if missing remotely, **SHOULD** fall back to latest with a warning (or fail closed if product chooses strict pin-only).  
12. **MUST** use a **private venv** under product data (`{{VOLARE_VENV}}`) — not system-wide pip by default on PEP 668 hosts.  
13. Type 1 **MAY** install `python3-venv` / `python3-pip` (or distro equivalents) when required for the venv.  
14. After `volare enable --pdk-root {{PDK_MANAGED_ROOT}} --pdk sky130 <version>`, re-probe and resolve nested `sky130A` if needed.

### 2.4 Commands and multi-component products

15. When the product exposes domain targets, **`install pdk` / `install sky130`** **MUST** ensure Sky130 only; **`install all`** / bare install (if default `all`) **MUST** include Sky130 after peer components (e.g. editor).  
16. Partial multi-target failure: exit ≠0; report which component failed.  
17. Uninstall of PDK **MUST NOT** remove the CLI ship unit; scope **MUST** be managed PDK artifacts only (product-defined).

### 2.5 Review gates

18. When Sky130 ensure is in scope: complete **CL-PAYLOAD-ENSURE-STRATEGIES** (`checklist-payload-ensure-strategies.md`).  
19. Static suite **SHOULD** prove strategy fallthrough exists (not package-map-only). Optional long network download is not Core CI.

---

## 3. Config / env (portable names)

| Placeholder / env | Role | Typical default |
|-------------------|------|-----------------|
| `{{PDK_ROOT}}` / `PDK_ROOT` | Live PDK root after probe | empty until ensure |
| `{{PDK_MANAGED_ROOT}}` | Managed install prefix | `${{DATA_ROOT}}/pdk` or product data dir |
| `{{VOLARE_VENV}}` | Private volare venv | `${{DATA_ROOT}}/.venv-volare` |
| `{{VOLARE_SKY130_VERSION_ENV}}` | Pin or `latest` | `latest` |
| `{{FORCE_REINSTALL}}` | Force re-ensure | `0` |

---

## 4. Protection Rule (Sacred)

Future agents **MUST NOT**:

1. Ship default multi-component install including Sky130 with **only** an empty package map and no managed-prebuilt path.  
2. Fail closed solely on empty package list when strategy 2 is designed.  
3. Hardcode a volare hash that is **not** on `ls-remote` as the sole default without remote resolution.  
4. Make **open_pdks git+make** the silent default without explicit user redesign.  
5. Claim PDK ready when probe fails.  
6. Put secrets in law molds or specialized REQs.  
7. Cite this template as product-source behavioral authority — only live `requirement-*.md`.

---

## Design-time verification

| TP family | Proof mold / suite | Notes |
|-----------|--------------------|-------|
| **TP-PDK-*** strategy static | product suite / `template-shell-tty` peers | fallthrough, no stale pin |
| Optional real enable | product optional job | network, large disk |
| Checklist | **CL-PAYLOAD-ENSURE-STRATEGIES** | when ensure in scope |

**RTM:** `../tests/template-requirement-test-traceability.md`

---

## How to specialize

1. Copy rules into `docs/requirements/requirement-sky130-pdk.md` (or product key).  
2. Fill **Implementation Notes** with real paths, package maps, env names, ship unit.  
3. Register in `docs/requirements/index.md`.  
4. Point domain requirement B2 (or residual) at this peer for depth.  
5. Implement; cite **only** the specialized requirement from product source.

---

**Last Updated**: 2026-07-27  
**Owner**: {{OWNER}}  
**Alignment**: term `payload-ensure-strategy` · CL-PAYLOAD-ENSURE-STRATEGIES · template-payload-online-install · three-layer-privilege · CIAO / CIAO-Lite  
