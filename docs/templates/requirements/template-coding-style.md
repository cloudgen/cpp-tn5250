---
name: coding-style
id: LM-CODING-STYLE
kind: law-mold
description: >
  Portable law mold. Cite as LM-CODING-STYLE (path secondary).
---

**file**: template-coding-style.md
**Status**: Active (Version 2.2.3 – cite ui-view-for-app-log; C++ display gate stays `template-output-requirements.md` §3.2)
**Project**: Any CIAO-Lite Project (reusable template)
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

# Template: Coding style (cross-language index)

## 1. Purpose

This template is the **language-agnostic entry point** for coding-style patterns. It does **not** own a full language body.

**Use it to choose the correct language-specific SSOT**, then specialize that file into project requirements.

**Class MUST (software-development):** every software-development project **MUST** have an Active language-matched coding-style related REQ. **Intention:** without that REQ, agents bring portable learned lessons **raw**. That REQ is the **specialize-in home**. This router file is **not** enough as product law. Term: `coding-style-requirement`.

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
| **Ship unit** | `docs/terminologies/ship-unit.md` | `mention-only` | Implementation target when specialized |
| **Coding-style requirement** | `docs/terminologies/coding-style-requirement.md` | `product-law` | Software-dev MUST specialize a language body; without it, lessons arrive raw |
| **Project log content type** | `docs/terminologies/project-log-content-type.md` | `mention-only` | Which kinds of message the log file stores. Cite only. The output mold owns the printer. |
| **UI view for an app log** | `docs/terminologies/ui-view-for-app-log.md` | `mention-only` | HTML table for one log file in the main web view. Cite only. Do not paste a product palette. The non-UI show command prints the file bytes unchanged. |

**SSOT types used:** `mention-only` · `meta-catalog` · `policy` · `product-law`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Routing table (disk-truth)

| Runtime / track | Authoritative template (specialize this) | Coding skill (when on disk) |
|-----------------|------------------------------------------|-----------------------------|
| **POSIX `/bin/sh`** | `docs/templates/requirements/template-shell-script-coding.md` | `docs/skills/skill-sh-script-coding.md` |
| Shell findability alias | `docs/templates/requirements/template-sh-coding-style.md` → same SSOT | same |
| **Node.js / JS / TS** | `docs/templates/requirements/template-nodejs-coding-style.md` (+ other `template-nodejs-*` as needed) **when on disk** | `docs/skills/skill-nodejs-cli-coding.md` **when on disk** |
| **Python** | `docs/templates/requirements/template-python-coding-style.md` (+ other `template-python-*` as needed) **when on disk** | `docs/skills/skill-python-cli-coding.md` **when on disk** |
| **C++** | `docs/templates/requirements/template-cpp-coding-style.md` | — |
| Modular design (cross-cutting) | `docs/templates/requirements/template-modular-function-design.md` (and language `template-nodejs-modular-function-design.md` **when on disk**) | language coding skill **when on disk** |
| Output channels | `docs/templates/requirements/template-output-requirements.md` (language variants: `template-nodejs-output-requirements.md`, `template-python-output-requirements.md` **when on disk**) | language coding skill **when on disk** |
| Defensive practices | `docs/templates/requirements/template-defensive-practices.md` | all coding skills |

**Shell SSOT reminder:** Do **not** treat this router file as the POSIX coding-law body. That is **`template-shell-script-coding.md` only** (incl. **§8.1** TTY / `$(…)` / Type 1; gate **CL-SHELL-TTY-PRIVILEGE-TRAPS**).

## 3. Shared principles (all languages)

These apply regardless of runtime; language SSOTs refine them.

1. **CIAO / CIAO-Lite** — Caution, Intentional, Anti-fragile, Over-protect; Protection Zones on critical logic.  
2. **Single sources of truth** — Config/identity, output channels, path resolution; no scattered magic strings for identity.  
3. **No product-source authority from templates/skills** — After specialization, source `ALIGNMENT` / `See` cites only live `docs/requirements/requirement-*.md`.  
4. **No-hardcode in this layer** — Use `{{PLACEHOLDER}}` / patterns; live values in Config and specialized requirements (with parameterization for app type / path choices / privilege actors per `docs/terminologies/project-requirements.md` when present).  
5. **No-placeholder in specialized deliverables** — Requirements and product docs claimed done must be complete.  
6. **UI view for an app log** — When a UI shows one dated log file, follow [ui-view-for-app-log](../../terminologies/ui-view-for-app-log.md): HTML table in the main web view, a distinct header, two body backgrounds, a third hover background, and no enclosure characters `[` `]` `<` `>` `(` `)` `{` `}` in displayed cells. The non-UI show command prints the file bytes unchanged. This mold cites the term. The specialized requirement copies the palette.

## 4. Function / module naming (pointer only)

| Track | Where the full prefix / module rules live |
|-------|-------------------------------------------|
| Shell | `template-shell-script-coding.md` (`out_`, `inst_`, `app_`, `{{APP_NAME}}_`, …) — **live language mold on this kit** |
| C++ | `template-cpp-coding-style.md` for names and linkage. `template-cpp-folder.md` for the ship-unit directory `src/main/cpp`. Translation units are `.cpp` unless the folder requirement names a `.c` file. Function prefix `logger_`. Level prefix `LOGGER_`. Quiet is `logger_set_quiet` and `logger_get_quiet`. Debug is `logger_get_debug` only. Not `ciao_` and not `CIAO_`. The C++ display gate and the C++ example bodies live in `template-output-requirements.md` §3.2. The shell rows in that file stay the shell contract. |
| Node | `template-nodejs-coding-style.md` + `template-nodejs-modular-function-design.md` **when on disk** |
| Python | `template-python-coding-style.md` + `template-python-classes.md` **when on disk** |

## 5. How to use this template

1. Identify the primary runtime.  
2. Open the **authoritative** language template from the routing table.  
3. Specialize into `docs/requirements/requirement-*.md` (conversion / create-specific-requirement skills).  
4. Implement with the matching coding skill.  
5. Register requirements in `docs/requirements/index.md` (requirement rows only — no template path dump).

## 6. Protection Rule (Sacred)

Future agents **MUST NOT**:

- Re-expand this file into a full shell (or Node/Python) coding body that competes with the language SSOTs.  
- Cite this router alone as sufficient shell coding law for implementation.  
- Leave a software-development project without a language-matched coding-style related REQ (portable lessons would then arrive **raw**).  
- Paste `template-*.md` / `skill-*.md` into product source as behavioral authority.  
- Invent language template paths that are not on disk.

---


## Design-time verification

| Gate | Artifact | Phase |
|------|----------|-------|
| Specialize → product suite or checklist | declare TP-IDs or checklist in specialized REQ | Design |
| RTM | `../tests/template-requirement-test-traceability.md` | Design |

When this mold has no executable TP family, mark **n/a** with reason in product `reviews/test-plan.md`.

**Last Updated**: 2026-10-05 (2.2.3 cites ui-view-for-app-log. C++ rows from 2.2.2 stay.)  
**Owner**: {{OWNER}}  
**Alignment**: `docs/templates/requirements/template-shell-script-coding.md`, `docs/templates/requirements/template-sh-coding-style.md`, `docs/templates/requirements/template-nodejs-coding-style.md` **when on disk**, `docs/templates/requirements/template-python-coding-style.md` **when on disk**, `docs/templates/requirements/template-cpp-coding-style.md`, `docs/templates/requirements/template-defensive-practices.md`, `docs/skills/skill-requirement-template-conversion.md`, CIAO / CIAO-Lite
