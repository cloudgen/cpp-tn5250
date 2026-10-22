---
name: stripped-genesis-template
id: LM-STRIPPED-GENESIS-TEMPLATE
kind: law-mold
description: >
  Portable law mold for the stripped-genesis-template subclass of genesis.
  Specialize into dest docs/README.md (template-name + exclusion SSOT) via
  SK-WRITE-README §5.1, then apply SK-GENESIS-TEMPLATE-STRIP. Never specialize
  into docs/requirements/requirement-*.md. Cite as LM-STRIPPED-GENESIS-TEMPLATE.
---

**file**: template-stripped-genesis-template.md  
**Mold-ID**: **`LM-STRIPPED-GENESIS-TEMPLATE`**  
**Status**: Active (Version 1.0.0)  
**Project**: Any CIAO-Lite workspace (reusable — **no product brand**)  
**Philosophy**: CIAO **v2.10.2** / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-protect)

**Folder structure (policy):** [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

# =============================================================================
# Template: stripped-genesis-template (NOT a requirement)
# Specialize into: dest docs/README.md Template identity + Harness-knowledge
#                  exclusion (SSOT) — SK-WRITE-README §5.1
# Apply deletes: SK-GENESIS-TEMPLATE-STRIP + CL-GENESIS-TEMPLATE-STRIP
# Never specialize into docs/requirements/requirement-*.md
# =============================================================================

## Design-time verification

| Gate | Artifact | Phase |
|------|----------|-------|
| Strip apply | **`CL-GENESIS-TEMPLATE-STRIP`** | After confirm |
| Seed audit | **`CL-REVIEW-HARNESS-KNOWLEDGE`** (genesis + subclass rows) | Review |
| RTM | n/a — no product suite at genesis (honest) | — |

## How to use this template (authoring only)

1. Confirm **project nature** is **genesis-template** (class #1). This mold is for the **stripped subclass**, not software-development.  
2. **MUST NOT** create `docs/requirements/requirement-*.md` (including no class file).  
3. Specialize by filling dest **`docs/README.md`** via **`SK-WRITE-README` §5.1** (`{{TEMPLATE_NAME}}` + exclusion table).  
4. Apply leaf deletes with **`SK-GENESIS-TEMPLATE-STRIP`**.  
5. Empty `docs/requirements/` registry remains **required honesty**.

**Target surfaces:** dest `docs/README.md` only (not product-root README).

---

# Stripped-genesis-template (mold)

**Status:** {{STATUS}}  
**Project nature:** genesis-template (class #1)  
**Subclass:** stripped-genesis-template  
**Template name:** {{TEMPLATE_NAME}}  
**Updated:** {{YYYY-MM-DD}}

## 1. Purpose

Name the **thinner genesis kit**: still an empty starter room (zero product law) with **fewer harness drawers**, bound by **template-name** and a **harness-knowledge exclusion SSOT** on dest `docs/README.md`. **Not** a twelfth project nature.

## 2. Terminologies

| Term | Path | SSOT type | Role |
|------|------|-----------|------|
| **Stripped-genesis-template** | `docs/terminologies/stripped-genesis-template.md` | `product-law` | Subclass definition (still class #1) |
| **Genesis template** | `docs/terminologies/genesis-template.md` | `product-law` | Parent nature |
| **Project nature** | `docs/terminologies/project-nature.md` | `product-law` | Daily-life name for class |
| **Project class** | `docs/terminologies/project-class.md` | `product-law` | Eleven peers; this is not #12 |
| **Template name** | `docs/terminologies/template-name.md` | `identity-docs` | Kit identity — live value on `docs/README.md` |
| **Harness-knowledge-blacklist** | `docs/terminologies/harness-knowledge-blacklist.md` | `identity-docs` | Exclusion list — live value on `docs/README.md` |
| **Genesis-template-strip** | `docs/terminologies/genesis-template-strip.md` | `mention-only` | Procedure word |
| **Harness knowledge** | `docs/terminologies/harness-knowledge.md` | `meta-catalog` | Payload being thinned |
| **Docs folder structure** | `docs/terminologies/docs-folder-structure.md` | `policy` | Layout |
| **Stay-honest** | `docs/terminologies/stay-honest.md` | `policy` | Maps match disk |
| **SSOT catalog** | `docs/terminologies/ssot-catalog.md` | `meta-catalog` | **SSOT-template-name** · **SSOT-harness-knowledge-exclusion** |

**SSOT types used:** `product-law` · `identity-docs` · `policy` · `meta-catalog` · `mention-only`

**Policies:** `policy-docs-folder-structure` · `policy-no-hardcode` · `policy-stay-honest` · `policy-dual-policies` · `policy-terminology-for-templates` · `policy-ssot-terminology-for-templates`

## 3. Core rules (mandatory — portable)

### 3.1 Class / subclass

1. **MUST** remain **genesis-template** (project nature #1).  
2. **MUST NOT** invent a twelfth nature named after `{{TEMPLATE_NAME}}`.  
3. **MUST NOT** author any `requirement-*.md` while in this subclass.  
4. **MUST** retain harness knowledge except units matching the dest exclusion SSOT.  
5. Genesis Exceptions A/B (absent product README / identity triad) **still apply**.

### 3.2 Identity + exclusion SSOT

6. **MUST** declare **template-name** `{{TEMPLATE_NAME}}` on dest **`docs/README.md`** (**`SK-WRITE-README` §5.1**).  
7. **MUST** publish a **non-empty** **Harness-knowledge exclusion (SSOT)** table: family id + match prefixes.  
8. **MAY** publish **Harness-knowledge keep (SSOT)** (focus whitelist); **MUST NOT** overlap the exclusion table.  
9. **MUST NOT** put those lists on product-root README or in `docs/requirements/`.  
10. **MUST NOT** list keep-set-floor units as excluded (`AGENTS.md`, dual policies, create-skill / create-terminology / write-readme / write-human-intro, strip/reset/rebind/path-safety, H1/H2, class-model terms).

### 3.3 Apply and hops

11. **MUST** apply matching leaf deletes only via **`SK-GENESIS-TEMPLATE-STRIP`** (compose **`SK-DESTRUCTIVE-PATH-SAFETY`**).  
12. H1/H2 **MUST** review dest keep/deny SSOT and **SKIP_BLACKLIST** matching units — **including** when source is **full** genesis-template (do not restock unrelated knowledge).  
13. **`SK-DEST-SSOT-MAP-REBIND`** **MUST** preserve the identity + keep + exclusion blocks when refreshing counts.  
14. **MUST NOT** use **`SK-RESET-TO-GENESIS-TEMPLATE`** to refresh a stripped kit (that keeps **full** harness).

## 4. SSOT remarks

| Concern | Catalog ID | Live owner |
|---------|------------|------------|
| Kit identity | **SSOT-template-name** | dest `docs/README.md` |
| Focus keep (optional) | **SSOT-harness-knowledge-keep** | dest `docs/README.md` keep table |
| Deny-pack | **SSOT-harness-knowledge-exclusion** | dest `docs/README.md` exclusion table |

Live values are dest fill. This mold uses `{{TEMPLATE_NAME}}` and family placeholders only.

## 5. CIAO alignment

| Letter | Application |
|--------|-------------|
| **C** | Confirm + path-resolve before leaf delete |
| **I** | Subclass stays genesis; exclusion is declared |
| **A** | SKIP_BLACKLIST so hops cannot restock |
| **O** | Keep-set floor; no `rm -rf docs/skills/` |

## Protection Rule (Sacred)

Future agents **MUST NOT**:

1. Specialize this mold into `requirement-*.md`.  
2. Treat `{{TEMPLATE_NAME}}` as a twelfth project nature.  
3. Recursive-delete harness trees.  
4. Restock excluded packs on H1 “to look like full genesis.”  
5. Freeze one kit name (e.g. a single HTML seed) as universal law inside this mold.

## How to specialize

1. **`SK-WRITE-README` §5.1** — write dest `docs/README.md` identity + exclusion.  
2. **`SK-GENESIS-TEMPLATE-STRIP`** + **`CL-GENESIS-TEMPLATE-STRIP`** — confirm, leaf delete, rebind.  
3. **`SK-REVIEW-HARNESS-KNOWLEDGE`** — Pass missing language skills when blacklisted; fail leftover matches and missing floor.

**Last Updated:** 2026-08-28  
**Owner:** {{OWNER}}  
**Alignment:** stripped-genesis-template · template-name · harness-knowledge-blacklist · genesis-template-strip · **`SK-WRITE-README` §5.1** · **`SK-GENESIS-TEMPLATE-STRIP`** · **`CL-GENESIS-TEMPLATE-STRIP`** · **`LM-POLICY-PRINCIPLES`** (zero-REQ specialize pattern)
