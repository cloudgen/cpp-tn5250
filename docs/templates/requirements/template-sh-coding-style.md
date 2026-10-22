---
name: sh-coding-style
id: LM-SH-CODING-STYLE
kind: law-mold
description: >
  Portable law mold. Cite as LM-SH-CODING-STYLE (path secondary).
---

**file**: template-sh-coding-style.md
**Status**: Active (Version 1.6.0 – Alias; SSOT §8.3 sudo-wrapping function + check before sudo)
**Project**: Any CIAO-Lite Project using POSIX /bin/sh (reusable template)
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

# Template: Shell coding style (alias)

## 1. Purpose

This file is a **findability alias** for POSIX shell coding style under the short `template-sh-*` naming pattern.

**It is not a second coding-style body.**

| Role | Path |
|------|------|
| **SSOT (authoritative full template)** | `docs/templates/requirements/template-shell-script-coding.md` (incl. **§8.1** TTY / Type 1; **§8.1.4** avoid `sudo -n` unless specified; **§8.2** user-owned `.profile` / `.bashrc`; **§8.3** sudo-wrapping function + check before sudo — chmod example) |
| **This alias** | `docs/templates/requirements/template-sh-coding-style.md` |
| **Cross-language coding-style index** | `docs/templates/requirements/template-coding-style.md` |
| **Avoid checklist** | `docs/templates/checklists/checklist-shell-tty-privilege-traps.md` (**CL-SHELL-TTY-PRIVILEGE-TRAPS**) |

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
| **Shell function naming convention** | `docs/terminologies/shell-function-naming-convention.md` | `product-law` | Naming |
| **Ship unit** | `docs/terminologies/ship-unit.md` | `mention-only` | POSIX shell body |

**SSOT types used:** `mention-only` · `meta-catalog` · `policy` · `product-law`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Mandatory behavior for agents

1. **Read and specialize** `template-shell-script-coding.md` for shell coding rules (prefixes, POSIX, Protection Zones, output SSOT pointers). Glossary for prefixes: `docs/terminologies/shell-function-naming-convention.md` (obey unless specialized REQ says otherwise).  
2. **Do not** maintain divergent MUST/SHOULD content in this alias file.  
3. When linking from skills or other templates, prefer citing the **SSOT** path; this alias may appear in inventories for `template-sh-*` discovery.  
4. Product source must never cite this file (or any `template-*`) as behavioral law — only live `requirement-*.md` after specialization.

## 3. How to use

1. Open `docs/templates/requirements/template-shell-script-coding.md`.  
2. Specialize into `docs/requirements/requirement-*.md` using `docs/skills/skill-requirement-template-conversion.md` / `skill-create-specific-requirement.md` when on disk.  
3. Implement with `docs/skills/skill-sh-script-coding.md` when on disk.  
4. Register new requirements in `docs/requirements/index.md` (requirement rows only).

## 4. Protection Rule (Sacred)

Future agents **MUST NOT**:

- Re-expand this alias into a full duplicate of `template-shell-script-coding.md`.  
- Change shell coding law only here while leaving the SSOT stale.  
- Invent additional shell coding SSOTs without explicit user redesign of the template set.

---


## Design-time verification

| TP family / ID | Proof mold | Planned suite |
|----------------|------------|---------------|
| **TP-U-*** (via shell SSOT body) | `../tests/template-set-u-test-plan.md` | `tests/test_cli.sh` |

**RTM:** `../tests/template-requirement-test-traceability.md`

**Last Updated**: 2026-07-26 (v1.2.0 – pointer to SSOT §8.1 + **CL-SHELL-TTY-PRIVILEGE-TRAPS**)  
**Owner**: {{OWNER}}  
**Alignment**: `docs/templates/requirements/template-shell-script-coding.md` (SSOT §8.1), **CL-SHELL-TTY-PRIVILEGE-TRAPS**, `docs/templates/requirements/template-coding-style.md` (router), `docs/skills/skill-sh-script-coding.md` §2.3.2, `docs/skills/skill-requirement-template-conversion.md`, CIAO / CIAO-Lite
