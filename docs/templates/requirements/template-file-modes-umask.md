---
name: file-modes-umask
id: LM-FILE-MODES-UMASK
kind: law-mold
description: >
  Portable law mold. Cite as LM-FILE-MODES-UMASK (path secondary).
---

**file**: template-file-modes-umask.md  
**Status**: Active (Version 1.3.0 – directory 0600 is not searchable; **PP-A-29**; U6a / **PP-A-28** kept)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered / Over-protect)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

## 1. Purpose

This template specializes **CIAO Principle 22 — File Modes & umask** (cloudgen/ciao v2.10.2):

> **Set the right mode on each path with `chmod` / `install -m` / API open modes. Use process `umask` seldom. If you change umask, always RESET it after use.**

**Related:** Principle **11** (temp location, `mktemp`, trap, atomic write — **not** mode policy) · Principle **12** (backup of durable state) · `template-ciao-principles.md` · `template-defensive-practices.md`.

**Specialize into:** `requirement-*-file-modes-umask.md` only when the product needs enforceable mode law beyond this pattern.

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
| **Temp file system** | `docs/terminologies/temp-file-system.md` | `runtime-mode` | Temp file modes |
| **Three-layer privilege** | `docs/terminologies/three-layer-privilege.md` | `mention-only` | Privilege context for files |
| **Shell profile** | `docs/terminologies/shell-profile.md` | `product-law` | Login rc — owner is the corresponding user |
| **Shell bashrc** | `docs/terminologies/shell-bashrc.md` | `product-law` | Interactive rc — same owner rule |

**SSOT types used:** `mention-only` · `meta-catalog` · `policy` · `runtime-mode`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Core rule

| Prefer | Avoid |
|--------|--------|
| `chmod` / `install -m` / language open modes **on the path** | Process-wide sticky `umask 077` for the whole script |
| Mode adapted to **file type** (private / shared / executable) | One umask as the only policy for all artifacts |
| SAVE → SET → work → **RESET** if umask is used | Leaving a restrictive umask for children / later work |

**One-line:** **chmod for the file type; umask seldom; if umask is used, always RESET.**

---

## 3. Why umask is seldom used

| Reason | Detail |
|--------|--------|
| **Must RESET** | Sticky restrictive umask breaks later normal/shared files and child tools |
| **Mixed types** | Secrets `600`, config `644`, binaries `755` cannot share one process mask honestly |
| **Atomic publish** | `write temp → mv final` **keeps temp mode** — set mode on the file for the intended final type |
| **Children inherit** | Package managers and helpers create files under the active umask |

---

## 4. Mandatory rules (U0–U9)

| # | Rule | Requirement |
|---|------|-------------|
| **U0** | Seldom use process umask | **MUST NOT** make process-wide umask the default habit |
| **U1** | Prefer chmod over umask | Protect sensitivity primarily via path-level modes |
| **U2** | Adapt to file type | Choose mode per artifact class |
| **U3** | Always RESET after use | Restore previous umask on every branch if SET |
| **U4** | SAVE before SET | Capture prior umask before changing |
| **U5** | No sticky whole-script umask | **MUST NOT** set umask at script start and never reset as policy |
| **U6** | `mv` does not fix mode | Set intended final mode before/at publish |
| **U6a** | Shebang dest **0755** | Type 0 `#!/bin/sh` install dest **MUST** be **`0755`**. **MUST NOT** `chmod +x` alone on `mktemp` staging. Global **and** user-bin. First place **and** `self-update`. |
| **U7** | Children inherit umask | Do not run unrelated creators under temporary restrictive umask |
| **U8** | Temps refer here | Principle **11** temps follow this principle for permissions |
| **U9** | User rc owner | `{{HOME}}/.profile` / `.bashrc` created or rewritten as Type 1 **MUST** be `chown`’d to the **corresponding user**. Mode is not enough (`mv` keeps temp owner). |
| **U10** | Check before sudo (chmod example) | Before `sudo chmod`, probe owner with a **non-sudo** command (`[ -O path ]`). If ownership matches, **MUST NOT** `sudo chmod`. Superclass: **check before sudo**. Use the **sudo-wrapping function** / chmod helper. Control-flow SSOT: **`LM-SHELL-SCRIPT-CODING`** §8.3. |

---

## 5. Typical mode classes (portable examples)

| Class | Example mode | Notes |
|-------|--------------|--------|
| Secret / session / token file | `600` | Never world-readable `.bak` of secrets |
| Shared config (non-secret) | `644` | Project policy may tighten |
| Installable executable | **`0755`** | After atomic install. Type 0 **shebang** dest: octal `chmod 0755` — **not** `chmod +x` on `mktemp` **0600** (yields **`0711`**; `/bin/sh` cannot open). **`LM-ONLINE-INSTALL`** §3.1 · **`TP-LC-10`** · **PP-A-28**. |
| Private temp directory | **0700** | `mkdir` / `mktemp -d` apply umask. Mode **0600** (`drw-------`) exists and cannot be searched. `chmod 0700` and require searchable and writable before any file. Cleanup sets **0700** again. **PP-A-29**. A private file stays **0600**. |
| Private temp file | `600` | Prefer chmod on path; trap cleanup (P11). Not a usable directory mode. |

Use `{{PLACEHOLDER}}` modes in project specialization when needed — do not freeze one product’s layout as universal law.

---

## 6. Protection zone (recommended)

```text
# =============================================================================
# CIAO-Lite Protection Zone — File Modes & umask (Principle 22)
# Prefer chmod/install -m per path and file type
# umask seldom — always RESET after any SET
# =============================================================================
```

---

## 7. CIAO alignment

- **Principle 22** — File Modes & umask (this template).  
- **Principle 11** — Temp location/lifecycle; points here for permissions.  
- **Principle 4 / CIAO-Lite O** — Do not “simplify” mode policy for cleanliness.  
- **Principle 1 – Caution** — Wrong modes leak secrets or break shared tools.  
- **Principle 5 – Single Source of Output** — Log mode failures via Output SSOT when product messaging applies.

---

## 8. Protection Rule (Sacred)

**Future AI assistants, Grok, or maintainers MUST NOT**:

1. Mandate sticky whole-script `umask 077` as “CIAO security.”  
2. Skip RESET after any intentional umask SET.  
3. Rely on umask alone so atomic `mv` publishes wrong modes.  
4. Leave secrets world-readable.  
5. Paste this template path into product source as law — specialize if needed; cite live requirement.  
6. Run `sudo chmod` when a non-sudo owner probe already shows this login owns the path — **U10** / check-before-sudo / **`LM-SHELL-SCRIPT-CODING`** §8.3.  
7. Use **`chmod +x` alone** on `mktemp` staging for a Type 0 shebang dest, or treat `sudo` / `[ -x ]` as dest-mode proof (**U6a** / **PP-A-28** / **`TP-LC-10`**).  
8. Treat a directory at **0600** as private-and-usable (**PP-A-29**). A private **file** at **0600** stays correct.

---


## Design-time verification

| Gate | Artifact | Phase |
|------|----------|-------|
| Specialize → product suite or checklist | declare TP-IDs or checklist in specialized REQ | Design |
| RTM | `../tests/template-requirement-test-traceability.md` | Design |

When this mold has no executable TP family, mark **n/a** with reason in product `reviews/test-plan.md`.

**Last Updated**: 2026-09-30  
**Owner**: Filesystem Safety Layer (Generalized Template)  
**Alignment**: [cloudgen/ciao](https://github.com/cloudgen/ciao) v2.10.2 Principle 22; `template-ciao-principles.md`; **`LM-ONLINE-INSTALL`** dest mode; **PP-A-28**; **PP-A-29**.  
**Version history:**  
- **1.3.0** (2026-09-30): A directory at **0600** cannot be searched. Private temp directory is **0700**. **PP-A-29**. U6a / **PP-A-28** unchanged.  
- **1.2.0** (2026-09-15): U6a shebang dest **0755**. **PP-A-28**.
