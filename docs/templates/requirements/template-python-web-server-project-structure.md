---
name: python-web-server-project-structure
id: LM-PYTHON-WEB-SERVER-PROJECT-STRUCTURE
kind: law-mold
description: >
  Portable folder mold for python-web-server: backend/ + frontend/, not src/.
  Cite as LM-PYTHON-WEB-SERVER-PROJECT-STRUCTURE.
---

**file**: template-python-web-server-project-structure.md  
**Mold-ID**: LM-PYTHON-WEB-SERVER-PROJECT-STRUCTURE  
**Status**: Active (Version 1.0.0)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered / Over-protect)

**Folder structure (policy):** [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md). This file is a **law mold**.

# Template: Python web-server project structure

## 1. Purpose

This mold states **where files live** for a python-web-server. Specialize to a product requirement only when the product needs a dedicated structure file; otherwise the type mold **`LM-PYTHON-WEB-SERVER`** already carries the folder contract.

## Terminologies

| Term | Path | SSOT type | Role |
|------|------|-----------|------|
| **Python web server** | `docs/terminologies/python-web-server.md` | `product-law` | Type this tree belongs to |
| **Python PyPI CLI** | `docs/terminologies/python-pypi-cli.md` | `product-law` | Uses `src/` — **not** this mold |
| **Python CLI** | `docs/terminologies/python-cli.md` | `product-law` | No required backend/frontend |
| **Project templates** | `docs/terminologies/project-templates.md` | `meta-catalog` | What molds are |
| **Docs folder structure** | `docs/terminologies/docs-folder-structure.md` | `policy` | docs vs product source |
| **No-hardcode policy** | `docs/terminologies/no-hardcode-policy.md` | `policy` | Placeholders |
| **Dual policies** | `docs/terminologies/dual-policies.md` | `policy` | Layer balance |
| **Terminology policy for templates** | `docs/terminologies/terminology-policy-for-templates.md` | `policy` | Terminologies section |
| **SSOT-terminology policy for templates** | `docs/terminologies/ssot-terminology-policy-for-templates.md` | `policy` | SSOT types |

**SSOT types used:** `product-law` · `meta-catalog` · `policy`

## Design-time verification

| Gate | Artifact | Phase |
|------|----------|-------|
| Folders on disk | `backend/` · `frontend/` | Design |
| `src/` not ship root | listing / specialized notes | Design |

## 2. Core Rules (Mandatory)

1. The repository **MUST** contain **`backend/`** (Python HTTP entry) and **`frontend/`** (client assets or pages).
2. The product **MUST NOT** treat **`src/`** as the required package root for this type.
3. Optional **`etl/`**, **`data/`**, and **`rules/`** **MAY** exist. They **MUST NOT** replace `backend/` as the server home.
4. Dependency declaration **SHOULD** be a root `requirements.txt` (or an equivalent declared in Implementation Notes). That file is **not** a PyPI console-script SSOT.
5. Agents **MUST NOT** apply **`LM-PYTHON-PROJECT-STRUCTURE`** (the `src/{{PACKAGE_NAME}}/` tree) to this type.
6. User runtime data **MUST NOT** be committed; paths resolve from the project root or a declared config module.

```text
{{APP_NAME}}/
├── backend/
├── frontend/
├── requirements.txt
├── README.md
├── etl/                 # optional
└── data/                # optional
```

## 3. Protection Rule (Sacred)

**MUST NOT**: move the working server into `src/` to match python-pypi-cli; delete `frontend/` “because the API is enough” without an authorized type change; freeze one product’s extra folders as the only allowed extras.

## 4. How to specialize

Copy only if a second structure REQ is needed. Prefer keeping folder law on `requirement-python-web-server.md`.

**Last Updated**: 2026-08-18  
**Owner**: {{OWNER}}  
**Alignment**: python-web-server · LM-PYTHON-WEB-SERVER · CIAO / CIAO-Lite
