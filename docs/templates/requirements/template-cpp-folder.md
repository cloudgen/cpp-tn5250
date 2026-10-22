---
name: cpp-folder
id: LM-CPP-FOLDER
kind: law-mold
description: >
  Portable law mold. Cite as LM-CPP-FOLDER (path secondary).
---

**file**: docs/templates/requirements/template-cpp-folder.md
**Status**: Active (Version 1.1.0 – C++ ship-unit directory and example tree)
**Project**: {{APP_NAME}} – C++ console program
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

# Template: C++ source folder

## 1. Purpose

This mold owns the ship-unit source directory for a project that comes from cpp-template or cpp-gnome-template.

**Specialize-in (software-development):** product law is one Active `requirement-cpp-folder.md`. Coding style stays in `template-cpp-coding-style.md`. This file does not restate naming or log-line rules.

## Terminologies

Related glossary entries (**disk-truth**). Templates **point**; they do not redefine terms or act as product law.
SSOT types follow `docs/policies/policy-ssot-terminology-for-templates.md`.
Binding rules: `docs/policies/policy-terminology-for-templates.md`.

| Term | Path | SSOT type | Role |
|------|------|-----------|------|
| **Project templates** | `docs/terminologies/project-templates.md` | `meta-catalog` | What law molds are; specialize-out target |
| **Docs folder structure** | `docs/terminologies/docs-folder-structure.md` | `policy` | Where this mold lives vs product law / tests |
| **No-hardcode policy** | `docs/terminologies/no-hardcode-policy.md` | `policy` | Placeholders only in portable molds |
| **Coding-style requirement** | `docs/terminologies/coding-style-requirement.md` | `product-law` | Spelling and linkage stay in the coding-style REQ |
| **Ship unit** | `docs/terminologies/ship-unit.md` | `mention-only` | Implementation target when specialized |

**SSOT types used:** `mention-only` · `meta-catalog` · `policy` · `product-law`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Directory

1. The ship-unit source directory is `src/main/cpp`.
2. There is one ship-unit source root. Do not keep a second root at `src/main/c`.
3. A translation unit in that directory is `.cpp` unless the specialized requirement names a `.c` file.
4. A header stays `.h` when the specialized requirement names that header.
5. Shell scripts, build files, and Markdown do not go in that directory.
6. The build's source variable points at `src/main/cpp`. The specialized requirement names that variable.
7. A new translation unit is recorded in the specialized requirement and in the build source list in the same change.

### Example tree

The specialized requirement names the files. This tree is the illustrative ship unit:

```text
src/main/cpp/
  main.cpp
  logger.cpp
  logger.h
  project.h
```

## 3. Protection rule

Future editors must not move this directory rule back into `template-cpp-coding-style.md` as a second owner, and must not leave a C++ product with its sources under `src/main/c`.

## Design-time verification

| Gate | Artifact | Phase |
|------|----------|-------|
| Specialize → product suite or checklist | declare TP-IDs or checklist in specialized REQ | Design |
| RTM | `../tests/template-requirement-test-traceability.md` | Design |

When this mold has no executable TP family, mark **n/a** with reason in product `reviews/test-plan.md`.

**Last Updated**: 2026-10-03
**Owner**: {{OWNER}}
**Alignment**: `docs/templates/requirements/template-cpp-coding-style.md`, `docs/templates/requirements/template-coding-style.md`, CIAO / CIAO-Lite
