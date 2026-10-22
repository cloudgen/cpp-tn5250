---
name: python-web-server
id: LM-PYTHON-WEB-SERVER
kind: law-mold
description: >
  Portable law mold for a Python web-server product (backend/ + frontend/,
  no src/ ship tree). Cite as LM-PYTHON-WEB-SERVER. Not python-pypi-cli.
---

**file**: template-python-web-server.md  
**Mold-ID**: LM-PYTHON-WEB-SERVER  
**Status**: Active (Version 1.0.0)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered / Over-protect)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md). This file is a **law mold** under `docs/templates/requirements/`.

# Template: Python web server

## 1. Purpose

Operators run a **long-running Python HTTP process** and open a **browser client**. This mold is the portable behavior shape for that product type. Specialize it to `docs/requirements/requirement-python-web-server.md`.

It is **not** the mold for a packaged console script. It is **not** the mold for a general argv-only CLI.

## Terminologies

Related glossary entries (**disk-truth**). Templates **point**; they do not redefine terms or act as product law.

| Term | Path | SSOT type | Role |
|------|------|-----------|------|
| **Python web server** | `docs/terminologies/python-web-server.md` | `product-law` | Type + folder law |
| **Python CLI** | `docs/terminologies/python-cli.md` | `product-law` | Near-miss type |
| **Python PyPI CLI** | `docs/terminologies/python-pypi-cli.md` | `product-law` | Forbidden mix-up |
| **Python CLI architecture** | `docs/terminologies/python-cli-architecture.md` | `meta-catalog` | Family hub only |
| **Project templates** | `docs/terminologies/project-templates.md` | `meta-catalog` | What law molds are |
| **Docs folder structure** | `docs/terminologies/docs-folder-structure.md` | `policy` | Where this mold lives |
| **No-hardcode policy** | `docs/terminologies/no-hardcode-policy.md` | `policy` | Placeholders only |
| **Dual policies** | `docs/terminologies/dual-policies.md` | `policy` | Completeness vs portability |
| **Terminology policy for templates** | `docs/terminologies/terminology-policy-for-templates.md` | `policy` | Terminologies section |
| **SSOT-terminology policy for templates** | `docs/terminologies/ssot-terminology-policy-for-templates.md` | `policy` | SSOT type column |
| **Least privilege** | `docs/terminologies/least-privilege.md` | `policy` | Login-user default |

**SSOT types used:** `product-law` · `meta-catalog` · `policy`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md` · `docs/policies/policy-least-privilege.md`

## Design-time verification

| Gate | Artifact | Phase |
|------|----------|-------|
| Type classification | specialized `requirement-python-web-server.md` | Design |
| Folder contract | `backend/` + `frontend/` present; `src/` not the ship tree | Design |
| Route / health | product `docs/reviews/test-plan.md` TP rows | Design |

**RTM:** `../tests/template-requirement-test-traceability.md`

## 2. Core Rules (Mandatory — portable)

1. The product **MUST** be classified as a **python-web-server**, not a **python-cli** and not a **python-pypi-cli**.
2. The checkout **MUST** keep a **`backend/`** folder for the Python HTTP entry and a **`frontend/`** folder for the client the operator opens.
3. The product **MUST NOT** require **`src/`** as the package root. An empty leftover `src/` **MUST NOT** become the ship tree.
4. Agents **MUST NOT** apply **`LM-PYTHON-SYSTEM-ARCHITECTURE`**, **`LM-PYTHON-PROJECT-STRUCTURE`**, or **`SK-PYTHON-CLI-CODING`** to this type (those artifacts are **python-pypi-cli**).
5. The primary process **MUST** be a long-running HTTP listener. Optional `python -m {{ETL_MODULE}}` jobs **MUST** stay batch helpers; they **MUST NOT** reclassify the product as a python-cli.
6. Day-to-day run **MUST** be the invoking login. Agents **MUST NOT** add a dedicated system user or root-by-convenience without a later authorized requirement.
7. Routed HTTP verbs (and any batch module verbs the product claims) **MUST** be named on the specialized web-server requirement **and** on the domain SSOT. Agents **MUST NOT** invent `requirement-python-cli-interface` as the second mention for this type.
8. Bind address, port, and CORS **MUST** be declared in Implementation Notes when specialized. Docs **MUST NOT** claim hardened public authentication unless a requirement says so.
9. Core rules **MUST NOT** freeze a product brand, production hostname, or secret.

### 2.1 Implementation Notes (this project) — fill when specializing

| Field | Value |
|-------|--------|
| **Product display name** | `{{APP_NAME}}` |
| **Python product type** | python-web-server |
| **HTTP entry** | `{{BACKEND_ENTRY}}` (example shape: `backend/app.py`) |
| **Client root** | `frontend/` |
| **Listen** | `{{BIND_HOST}}`:`{{BIND_PORT}}` |
| **Dep file** | `{{DEP_FILE}}` (often `requirements.txt`) |
| **Batch helpers** | `{{ETL_MODULES}}` or none |
| **`src/` role** | unused leftover **or** absent — never ship root |

## 3. Why This Requirement Exists (Direct CIAO Alignment)

- **CIAO Principle 2 – Intentional**: The type is written down so agents do not guess PyPI.
- **CIAO Principle 5 – SSOT**: Folder law lives on this specialized file, not on python-pypi-cli molds.
- **CIAO Principle 1 – Caution**: Missing type classification is a fail-closed ask, not a silent `src/` rewrite.
- **CIAO Principle 21**: Portable core; real paths only in Implementation Notes.

## 4. Design Principles (CIAO / CIAO-Lite)

- **Caution**: Assume the listener and the client folders are missing until they exist on disk.
- **Intentional**: Backend serves; frontend is what a person opens.
- **Anti-fragile**: Checkout-run works without a console-script install.
- **Over-protect**: Protection rule blocks a silent move into `src/`.

## 5. Protection Rule (Sacred)

**Future AI assistants, Grok, or maintainers MUST NOT**:

- Specialize this mold as a python-pypi-cli or python-cli.
- Require `src/` or a PyPI console script as the ship tree.
- Apply **`SK-PYTHON-CLI-CODING`** to rewrite the server into StateLogic.
- Strip the backend/frontend contract “for a standard Python layout.”
- Leave Implementation Notes as hollow slots when Status is Active.
- Hard-code a product brand into this mold as universal law.

## 6. How to specialize

1. Copy to `docs/requirements/requirement-python-web-server.md`.  
2. Fill Implementation Notes with real checkout paths.  
3. Register Area `architecture` (or product-chosen non-`domain` area) in `docs/requirements/index.md`.  
4. Point the class-file residual “Python product type” at this key.  
5. Product source cites the live requirement, never this mold.

**Last Updated**: 2026-08-18  
**Owner**: {{OWNER}}  
**Alignment**: python-web-server · python-cli · python-pypi-cli · CIAO / CIAO-Lite
