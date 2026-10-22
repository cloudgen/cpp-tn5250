---
name: ciao-principles
id: LM-CIAO-PRINCIPLES
kind: law-mold
description: >
  Portable law mold. Cite as LM-CIAO-PRINCIPLES (path secondary).
---

**file**: template-ciao-principles.md  
**Status**: Active (Version 1.0.0 – Aligned to cloudgen/ciao v2.10.2)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered / Over-protect)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

## 1. Purpose

This template is the **harness SSOT for CIAO principle numbering and meaning** when authoring or reviewing other `template-*.md` files.

**Authoritative upstream:** [cloudgen/ciao](https://github.com/cloudgen/ciao) **v2.10.2** (README principles text).  
**Agent short contract:** [cloudgen/ciao-lite](https://github.com/cloudgen/ciao-lite) — also **Principle 4** in full CIAO.

**Do not invent principle numbers.** When citing “CIAO Principle N”, match the table below (v2.10.2). Older docs that used the pre-2.10 map (e.g. Over-protect as “18”, Least-Privilege as “8”, Interactive as “14”) are **stale**.

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
| **Harness engineering** | `docs/terminologies/harness-engineering.md` | `meta-catalog` | Agent OS framing |
| **Stay-honest** | `docs/terminologies/stay-honest.md` | `policy` | Disk-truth honesty |

**SSOT types used:** `meta-catalog` · `policy`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Principle index (v2.10.2)

| # | Name | One-line intent |
|---|------|-----------------|
| **1** | Caution | Assume nothing; explicit checks; no silent failure |
| **2** | Intentional Verbosity & Transparency | Headers, General Purpose, declared *why* |
| **3** | Anti-fragile & Resilient Design | Survive minimal envs, edge cases, retries |
| **4** | **CIAO-Lite — Simplicity but Safety** | Agent contract C·I·A·**O**ver-protect; surgical change; dual-policy rules 6–7 |
| **5** | **Single Source of Output** | One Output module; stdout / stderr / pipeline family; SSOT remarks |
| **6** | Single Point of Entry | Clear init / dispatcher per major module |
| **7** | General Purpose Requirement | Public/reusable functions state objective |
| **8** | Reusable Function Protection | `!!! DO NOT MODIFY OR SIMPLIFY THIS FUNCTION !!!` |
| **9** | **Three Types of Commands (Type 0 / 1 / 2)** | Privilege class map *who runs what* |
| **10** | Least-Privilege User | Dedicated user, restricted sudo, setup vs ops |
| **11** | Safe Temporary File Handling | `$TMPDIR` → mktemp; trap; atomic; **modes → P22** |
| **12** | Right Backup & Restore Strategy | **Risk-class** recovery — not “backup every touch” |
| **13** | Independent Three-Digit Versioning | Per-component `MAJOR.MINOR.PATCH` when used |
| **14** | Security & Traceability | stdout vs stderr channels; ERROR/WARN/INFO/DEBUG |
| **15** | Multi version-managers & shells | pyenv/conda/nvm/…; sh/bash/zsh/fish/… |
| **16** | Interactive vs Non-Interactive | Never hang automation; safe defaults |
| **17** | Encouraging User Help Functions | Clear help; errors point to safe next steps |
| **18** | Input Pattern Checking | Validate/sanitize args; reject dangerous patterns |
| **19** | Defensive Storage Location Handling | Resolve paths; never hard-code `~/.app/` without resolution |
| **20** | Protect Against AI & Human Modification | Visible headers; sacred safety blocks |
| **21** | Dual Policies: No-Placeholder × No-Hardcode | Completeness at the right layer |
| **22** | File Modes & umask | Prefer `chmod`/`install -m`; umask seldom; always RESET |

---

## 3. Migration from pre-2.10 numbering (common mistakes)

| Stale citation (pre-2.10 map) | Correct v2.10.2 |
|-------------------------------|-----------------|
| “Principle 4 – SSOT of output” | **Principle 5** (Principle 4 is **CIAO-Lite**) |
| “Principle 5 – Single entry” | **Principle 6** |
| “Principle 6 – General Purpose” | **Principle 7** |
| “Principle 7 – Reusable function” | **Principle 8** |
| “Principle 8 – Least-Privilege” | **Principle 10** (Type 0/1/2 map is **Principle 9**) |
| “Principle 9 – Safe temp” | **Principle 11** |
| “Principle 10 – Backup” | **Principle 12** |
| “Principle 11 – Versioning” | **Principle 13** |
| “Principle 12 – Security & traceability” | **Principle 14** |
| “Principle 13 – Multi env / shells” | **Principle 15** |
| “Principle 14 – Interactive” | **Principle 16** |
| “Principle 15 – Help” | **Principle 17** |
| “Principle 16 – Input checking” | **Principle 18** |
| “Principle 17 – Storage” | **Principle 19** |
| “Principle 18 – Over-protect / Protect AI” | **Principle 4 (O)** + **Principle 20** |

---

## 4. Must-not-confuse (v2.10.2 highlights)

| Topic | Correct reading |
|-------|-----------------|
| **Type 0 / 1 / 2** | **Principle 9** architecture map — not the same as Principle 10 mechanics |
| **Type 2** | **Dedicated least-privilege system user** — **not** “root-only” |
| **SSOT of pipeline** | Internal data (`$(…)`, tool pipes, file redirects) — **not** product UX |
| **Backup** | Proportionate to risk class (config/user data hard; temps = cleanup) |
| **umask** | Seldom; path-level modes preferred (**Principle 22**) |
| **JSON newlines** | One success JSON value on stdout is required; trailing newline after value is **allowed** |
| **Harness vs CIAO** | CIAO = code/change philosophy; harness = agent OS that applies it |

---

## 5. How other templates should cite CIAO

1. Philosophy line: `CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered / Over-protect)`  
2. Alignment footer: `CIAO Defensive Programming Principles v2.10.2` + `https://github.com/cloudgen/ciao`  
3. Prefer principle **name + number** from §2 (e.g. “Principle 12 – Right Backup”).  
4. For Over-protect protection zones, cite **Principle 4 (CIAO-Lite O)** and **Principle 20**.  
5. Do not hardcode a foreign product’s paths from upstream examples into portable templates.

**Related topic templates:** `template-output-requirements.md` (P5), `template-cli-interface.md` (P9), `template-least-privilege-user.md` / `template-three-layer-privilege-model.md` (P9–P10), `template-backup-strategy.md` (P12), `template-interactive-vs-noninteractive.md` (P16), `template-file-modes-umask.md` (P22), `template-defensive-practices.md` (router).

---

## 6. Protection Rule (Sacred)

**Future AI assistants, Grok, or maintainers MUST NOT**:

1. Cite pre-2.10 principle numbers as if current.  
2. Call Type 2 “root-only” (contradicts Principle 9).  
3. Require dated `.bak` for every temp/download as “Principle 12 compliance.”  
4. Make process-wide `umask 077` sticky whole-script policy (violates Principle 22).  
5. Treat pipeline `printf` returns as product-output violations when properly SSOT-remarked (Principle 5).  
6. Claim harness templates are ISO/OWASP certification.

---


## Design-time verification

| Gate | Artifact | Phase |
|------|----------|-------|
| Specialize → product suite or checklist | declare TP-IDs or checklist in specialized REQ | Design |
| RTM | `../tests/template-requirement-test-traceability.md` | Design |

When this mold has no executable TP family, mark **n/a** with reason in product `reviews/test-plan.md`.

**Last Updated**: 2026-07-14  
**Owner**: CIAO Alignment Layer (Generalized Template)  
**Alignment**: [cloudgen/ciao](https://github.com/cloudgen/ciao) v2.10.2; [cloudgen/ciao-lite](https://github.com/cloudgen/ciao-lite).
