---
name: domain-url-cli
id: LM-DOMAIN-URL-CLI
kind: law-mold
description: >
  Portable law mold for URL-argument domain CLIs (four pillars). Cite as
  LM-DOMAIN-URL-CLI (path secondary). Specialize to requirement-domain-{{PRODUCT_SLUG}}.md.
---

**file**: docs/templates/requirements/template-domain-url-cli.md  
**Status**: Active (Version 1.0.1 – dual mention with language CLI REQ)  
**Project**: {{APP_NAME}} – URL-argument domain CLI  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered / Over-protect)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

# Template: Domain surface — URL-argument CLI (four pillars)

## 1. Purpose

Portable **domain surface SSOT** for products whose primary user operand is a **URL** (series/episode/media page), not a multi-verb Type 0 shell catalog.

This mold owns **what the product is for** (supported hosts, workflow steps, feature catalog, help/about framing). It does **not** own:

- Full CLI argparse tables → specialize `template-python-cli-interface` / language peer (**`LM-CLI-INTERFACE`** §4.1 dual mention still applies: each domain verb **MUST** be named on the language CLI-interface REQ **and** the specialized domain REQ)  
- Full download-engine option graphs → specialize `template-download-ytdlp-pipeline` (or other engine mold)  
- Packaging / version SSOT → packaging peer  

**Exactly one** Active `requirement-domain-*` per product when specialized.

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
| **Project requirements** | `docs/terminologies/project-requirements.md` | `meta-catalog` | Specialized law surface |
| **Registry discipline** | `docs/terminologies/registry-discipline.md` | `policy` | index.md rows for domain file |

**SSOT types used:** `meta-catalog` · `policy`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

---

## 2. Core Rules (Mandatory — portable)

### 2.1 Product shape

1. **MUST** treat the product as a **URL-argument domain CLI** unless specialization explicitly reclassifies.  
2. **MUST** keep exactly **one** Active `requirement-domain-*` after specialize (basename `requirement-domain-{{PRODUCT_SLUG}}.md`).  
3. **MUST NOT** invent a second Active domain file without superseding the first.  
4. **MUST** separate domain catalog from **engine/pipeline** law (download/extract plumbing).

### 2.2 Four pillars (all required when specialized)

| Pillar | Owns | Must not own |
|--------|------|--------------|
| **A — Workflow steps** | Ordered user-visible steps after entry (URL in → outcome) | Full engine option tables |
| **B — Features** | Feature surface map (what is claimed) | Competing second pipeline SSOT |
| **C — Help items** | Help/README domain rows that must match law | Packaging version SSOT alone |
| **D — About items** | Product identity lines (name, domain summary, runtime tools) | Remote version-check / install-channel ads without install REQ |

### 2.3 Pillar A — Workflow steps (portable skeleton)

Specialization **MUST** fill a step table. Portable skeleton:

| Step ID | User action | Inputs | Output / effect | Ops peer |
|---------|-------------|--------|-----------------|----------|
| D-01 | Supply URL | positional `{{URL_ARG}}` from **supported host** | Validate host | CLI + domain |
| D-02 | Detect site / family | URL netloc | Route to extractor | domain |
| D-03 | Optional protect assist | e.g. Cloudflare / UA flags when product has them | Session headers/cookies | domain + pipeline |
| D-04 | Extract media list | page/API | Ordered `(title, source_url[, cookie_dict])` | domain extractors |
| D-05a | Extract-only mode | extract flag | Print sources; **no download** | domain + CLI |
| D-05b | Download mode | default | Fetch via engine | download/pipeline peer |
| D-06 | Report outcome | — | Per-item success/failure | CLI + error peer |

Unsupported hosts **MUST** fail closed.

### 2.4 Host allowlist (portable)

5. **MUST** declare an explicit **supported host family** table (detect rule + extractor role).  
6. **MUST NOT** claim arbitrary-site / whole-web scraper support without updating this domain law, CLI validation, and peers.  
7. **SHOULD** list **non-goals** (batch queue, GUI, DRM break beyond documented assist, multi-host plugin marketplace, root install-ensure, etc.) so agents do not invent scope.

### 2.5 Legal / honesty posture (portable)

8. When the product fetches third-party media, specialization **MUST** keep a **personal/educational + ToS/law respect** disclaimer on user docs.  
9. Agents **MUST NOT** expand domain law into bulk commercial piracy tooling without explicit user order and new law.

### 2.6 Implementation Notes (this project) — fill when specializing

| Field | This project |
|-------|----------------|
| **Product / package** | `{{APP_NAME}}` / `{{PACKAGE_NAME}}` |
| **Console script** | `{{CONSOLE_SCRIPT}}` |
| **Domain module(s)** | `{{DOMAIN_MODULES}}` |
| **Supported hosts** | `{{HOST_FAMILIES}}` |
| **Extract flags** | `{{EXTRACT_FLAGS}}` |
| **Protect-assist flags** | `{{PROTECT_FLAGS}}` |
| **Ops / pipeline peer key** | `{{PIPELINE_REQ_KEY}}` |
| **CLI peer key** | `{{CLI_REQ_KEY}}` |
| **User docs** | `{{USER_DOCS}}` |

### 2.7 Why this mold exists (CIAO)

- **Intentional**: Domain surface is explicit and not mixed with full engine options.  
- **SSOT**: One Active domain file for feature catalog.  
- **Caution**: Non-goals and legal posture listed.

---

## 3. Design Principles (CIAO / CIAO-Lite)

- **Caution:** Do not invent a second engine SSOT inside domain.  
- **Intentional:** Pillars A–D only.  
- **Anti-fragile:** Clear ownership vs CLI / pipeline peers.  
- **Over-protect:** Sole Active domain file; supersede before replace.

---

## 4. Protection Rule (Sacred)

**Future AI assistants, Grok, or maintainers MUST NOT**:

1. Duplicate full download-engine option law inside domain once a pipeline peer is Active.  
2. Add online install, bulk piracy queue, or root elevation as silent domain behavior without new requirements.  
3. Create a second Active `requirement-domain-*` without superseding.  
4. Drop a documented host while user docs still advertise it without coordinated update.  
5. Claim arbitrary-site support without domain + CLI + peer updates.  
6. Remove legal disclaimer while the product still downloads third-party media (when applicable).  
7. Silently re-scope the product into an unrelated domain (e.g. local media edit) without rename / new REQs.

**Violating this rule is a critical domain regression.**

---

## 5. Acceptance criteria (when specialized)

| ID | Criterion |
|----|-----------|
| AC-1 | Four pillars present |
| AC-2 | Supported hosts explicit; unsupported fail closed |
| AC-3 | Extract vs download modes documented when both exist |
| AC-4 | Non-goals listed |
| AC-5 | Sole Active domain SSOT registered |
| AC-6 | No competing full engine option body (defers to pipeline peer) |

---

## 6. Related molds (portable peers)

| Mold | Relationship |
|------|--------------|
| `template-python-cli-interface` | Argv / entry for Python products |
| `template-download-ytdlp-pipeline` | yt-dlp ops when that engine is used |
| `template-python-runtime-prerequisites` | Runtime honesty |
| `template-python-error-handling` | Fail-closed reporting |
| `template-named-timer-domain` | **Different** domain shape (timer verbs) — do not use as URL-CLI twin |

---

## 7. How to specialize

1. Copy to `docs/requirements/requirement-domain-{{PRODUCT_SLUG}}.md`.  
2. Fill host table, step table, help/about rows, Implementation Notes (no bare placeholders if claiming done).  
3. Point pipeline/CLI peers to real Active keys.  
4. Register in `docs/requirements/index.md` as **sole** Active domain.  
5. Keep Protection Rule intent.  
6. Product source cites **`requirement-domain-*`**, never this template.

---

## Design-time verification

| Gate | Artifact | Phase |
|------|----------|-------|
| Domain allowlist / extract mode | specialized TP family (e.g. TP-DOMAIN-*) | Design + have |
| CLI peer | CLI TP for URL required | Peer |

**RTM:** `../tests/template-requirement-test-traceability.md` §4.

**Last Updated**: 2026-08-11  
**Owner**: {{OWNER}}  
**Alignment**: Domain four-pillar pattern; **CIAO** (https://github.com/cloudgen/ciao); CIAO-Lite (https://github.com/cloudgen/ciao-lite).
