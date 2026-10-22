---
name: python-runtime-prerequisites
id: LM-PYTHON-RUNTIME-PREREQUISITES
kind: law-mold
description: >
  Portable law mold for Python pip-product runtime prerequisites (no root system
  installer command). Cite as LM-PYTHON-RUNTIME-PREREQUISITES. Specialize to
  requirement-runtime-prerequisites.md or requirement-python-runtime-prerequisites.md.
---

**file**: docs/templates/requirements/template-python-runtime-prerequisites.md  
**Status**: Active (Version 1.0.0 – Portable runtime honesty for Python PyPI / pip CLI products)  
**Project**: {{APP_NAME}} – Python runtime prerequisites  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered / Over-protect)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

# Template: Python runtime prerequisites (pip product)

## 1. Purpose

Portable **documentation and validation SSOT** for what must already be present to run a **Python pip / local package** product successfully.

This mold is **not** the shell-style privileged `prerequisites` / system package installer command (`template-prerequisites.md`). Default products specializing this mold:

- **Do not** implement a root/sudo OS package installer command.  
- **Do** list interpreter, pip deps, optional system binaries, network needs.  
- **Do** fail closed on missing imports with actionable messages.

## Terminologies

Related glossary entries (**disk-truth**). Templates **point**; they do not redefine terms or act as product law.  
SSOT types follow `docs/policies/policy-ssot-terminology-for-templates.md`.  
Binding rules: `docs/policies/policy-terminology-for-templates.md`.

| Term | Path | SSOT type | Role |
|------|------|-----------|------|
| **Project templates** | `docs/terminologies/project-templates.md` | `meta-catalog` | Law molds |
| **Docs folder structure** | `docs/terminologies/docs-folder-structure.md` | `policy` | Placement |
| **No-hardcode policy** | `docs/terminologies/no-hardcode-policy.md` | `policy` | Placeholders |
| **Dual policies** | `docs/terminologies/dual-policies.md` | `policy` | Balance |
| **Terminology policy for templates** | `docs/terminologies/terminology-policy-for-templates.md` | `policy` | Terminologies rules |
| **SSOT-terminology policy for templates** | `docs/terminologies/ssot-terminology-policy-for-templates.md` | `policy` | SSOT types |
| **Ship unit** | `docs/terminologies/ship-unit.md` | `mention-only` | What ships vs host-provided |
| **Stay-honest** | `docs/terminologies/stay-honest.md` | `policy` | No false auto-install claims |

**SSOT types used:** `mention-only` · `meta-catalog` · `policy`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md` · `docs/policies/policy-stay-honest.md` (when present)

**Peer mold (different product shape):** `template-prerequisites.md` — Type 1 system package / Docker install command. **Do not** confuse with this mold.

---

## 2. Core Rules (Mandatory — portable)

### 2.1 Scope (honest product mode)

1. **MUST** document all external tools and libraries required at runtime.  
2. **MUST NOT** claim the product auto-installs system packages via root/sudo unless a future Active elev + install requirement is added and this specialization is updated.  
3. **MUST** separate **pip-installable** Python deps from true **system binaries**.  
4. **MUST NOT** use this file as a second packaging dependency SSOT that contradicts `pyproject.toml` — packaging peer remains primary for declared deps; this file is runtime honesty + validation narrative.

### 2.2 Required runtime components (skeleton)

Specialization **MUST** fill a table of this shape:

| Component | Kind | Required for | Install surface |
|-----------|------|--------------|-----------------|
| CPython (≥ `{{MIN_PYTHON}}`) | interpreter | package import + CLI | OS / pyenv / system Python |
| `{{PIP_DEP_1}}` | pip package | … | `pyproject.toml` / pip |
| … | … | … | … |
| Network egress (if needed) | host capability | … | operator environment |
| Optional system binary (if any) | system tool | … | OS package manager (user installs) |

### 2.3 Validation expectations

5. **MUST** fail with an actionable message when required Python modules are missing (import gates at entry or equivalent).  
6. **MUST** document operator-supplied challenge cookies or browser assists when the product depends on them (e.g. Cloudflare) — not as auto-fetched privileged secrets.  
7. **MUST** point supported hosts / network scope to the domain peer when domain law exists.

### 2.4 Privilege

8. **MUST NOT** require root to satisfy runtime prerequisites for normal use of a pip CLI.  
9. Type 1 elevation for OS package install is **out of scope** unless specialization explicitly adds elev law (rare for pure PyPI tools).

### 2.5 Implementation Notes (this project) — fill when specializing

| Field | This project |
|-------|----------------|
| **Python package install** | `{{INSTALL_HINT}}` |
| **Declared pip deps** | `{{PIP_DEPS}}` |
| **System binaries** | `{{SYSTEM_BINARIES}}` (or **none** beyond CPython) |
| **Auto OS install command** | **none** (default) or named elev command if lawed |
| **Platform notes** | `{{PLATFORM_NOTES}}` |
| **Startup checks** | `{{IMPORT_GATES}}` |
| **User docs** | `{{USER_DOCS}}` |
| **Product version** | `{{VERSION}}` |

### 2.6 Why this mold exists (CIAO)

- **Caution**: Assume deps may be missing.  
- **Least privilege**: No forced root prerequisites command.  
- **Intentional**: Pip vs system deps separated.  
- **Stay-honest**: No fake auto root-install claims.

---

## 3. Design Principles (CIAO / CIAO-Lite)

- **Caution:** Document before fail.  
- **Intentional:** No fake root install claim.  
- **Anti-fragile:** Works wherever Python + declared deps + network exist.  
- **Over-protect:** No silent elev install.

---

## 4. Protection Rule (Sacred)

**Future AI assistants, Grok, or maintainers MUST NOT**:

1. Claim OS packages are installed by `pip install {{PACKAGE_NAME}}` alone when not true.  
2. Add root package-manager elev without elev allowlist law and user order.  
3. Drop declared pip deps from tables while code still imports them.  
4. Store secrets in this file.  
5. Invent hard product gates for optional third-party tools (e.g. ffmpeg) unless code paths actually require a product-level check.  
6. Specialize from `template-prerequisites` (system installer) without rewriting privilege scope for pip products.

**Violating this rule is a critical honesty regression.**

---

## 5. Acceptance criteria (when specialized)

| ID | Criterion |
|----|-----------|
| AC-1 | All pip deps listed (aligned with packaging) |
| AC-2 | Network egress noted when required |
| AC-3 | No false auto root-install claim |
| AC-4 | Import gates / validation documented |

---

## 6. Related molds

| Mold | Relationship |
|------|--------------|
| `template-python-packaging` | Declared deps SSOT |
| `template-python-cli-interface` | Import gates at entry |
| `template-download-ytdlp-pipeline` | Engine as pip dep |
| `template-domain-url-cli` | Host / network scope |
| `template-prerequisites` | **Different** — Type 1 system installer |

---

## 7. How to specialize

1. Copy to `docs/requirements/requirement-runtime-prerequisites.md` (or `requirement-python-runtime-prerequisites.md`).  
2. Fill component table + Implementation Notes from real `pyproject.toml` and entry gates.  
3. Register in `docs/requirements/index.md`.  
4. Seed TP for missing-module message path.  
5. Product source cites the **requirement** key, not this template.

---

## Design-time verification

| Gate | Artifact | Phase |
|------|----------|-------|
| Missing module path | specialized suite (e.g. TP-RT-01) | Design + have |
| Dep table vs packaging | packaging peer review | Review |

**RTM:** `../tests/template-requirement-test-traceability.md` §4.

**Last Updated**: 2026-08-11  
**Owner**: {{OWNER}}  
**Alignment**: **CIAO** (https://github.com/cloudgen/ciao); CIAO-Lite (https://github.com/cloudgen/ciao-lite).
