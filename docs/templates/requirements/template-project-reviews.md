---
name: project-reviews
id: LM-PROJECT-REVIEWS
kind: law-mold
description: >
  Portable law mold. Cite as LM-PROJECT-REVIEWS (path secondary).
---

**file**: template-project-reviews.md  
**Status**: Active (Version 1.0.1 – cite ui-view-for-app-log)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered / Over-protect)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

## 1. Purpose

Portable pattern for a **public, git-tracked reviews folder** at the product root — peer of `{{TESTS_DIR}}` — holding:

1. **What to review** (living checklist)  
2. **Test plan** mapping findings → automated cases  
3. **Lessons** from prior reports (regression prevention)  
4. **Committed reports** of review runs  

**Terminology:** `docs/terminologies/project-reviews.md`

**Specialize into:** project `{{REVIEWS_DIR}}/` (default `reviews/`) with product-specific open items and reports.

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
| **Project reviews** | `docs/terminologies/project-reviews.md` | `product-law` | reviews/ surface |
| **Review report** | `docs/terminologies/review-report.md` | `product-law` | Single review record |
| **Project review folder** | `docs/terminologies/project-review-folder.md` | `product-law` | Folder rules |
| **UI view for an app log** | `docs/terminologies/ui-view-for-app-log.md` | `mention-only` | When a review covers an app-log UI, check this rule. Cite only. |

**SSOT types used:** `mention-only` · `meta-catalog` · `policy` · `product-law`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Layout (mandatory when this surface is claimed)

```text
{{REVIEWS_DIR}}/
  README.md                 # purpose + agent rules
  index.md                  # registry of plans + reports
  what-to-review.md         # living checklist (+ prior lessons callout)
  test-plan.md              # TP-* rows → {{TESTS_DIR}}
  lessons.md                # P-* prior-report failure modes
  reports/
    YYYY-MM-DD-<scope>.md   # durable run summaries
```

Optional: `reports/README.md` one-liner.

---

## 3. Core rules

1. **Git-tracked** — root `.gitignore` **MUST NOT** ignore `{{REVIEWS_DIR}}/**` by default (same class as `tests/`).  
2. **Ephemeral ≠ durable** — session scratch (`/tmp/…`) **MAY** feed a run; durable outcomes **MUST** be written under `{{REVIEWS_DIR}}` when the review is product-relevant.  
3. **Prior lessons mandatory** — every new review **MUST** load `lessons.md` (or equivalent) and re-check listed items.  
4. **Test plan coupling** — every open **bug** **SHOULD** have a TP row (have / TODO / n/a). Closing a bug updates TP status and preferably adds a test under `{{TESTS_DIR}}`.  
5. **No secrets** in committed reports.  
6. **No harness path inventories** as navigation (skills/templates/terminologies tree dumps). Cite live `requirement-*.md` and product paths.  
7. **Registry discipline** — `index.md` rows match files on disk.  
8. **Bootstrap products** — when chain exists, reports may be leaf full-product or origin-hop; lessons include inheritance / reverse-copy rules without reverse-copying ship units.  
9. **UI view for an app log** — a review of that view uses [ui-view-for-app-log](../../terminologies/ui-view-for-app-log.md) and **`CL-UI-VIEW-FOR-APP-LOG`**. The HTML table has a distinct header, two body backgrounds, and a third hover background. Displayed cells omit `[` `]` `<` `>` `(` `)` `{` `}`. The non-UI show command still prints the file bytes unchanged. The review does not paste a product palette into this mold.

---

## 4. File responsibilities

| File | Must contain |
|------|----------------|
| README | Layout, how agents use it, commit rules |
| index | Table of plans/reports + open-item summary |
| what-to-review | Surfaces, high-risk paths, pre-flight, publish steps; for **shell Type 1 elevation** include TTY/`$(…)` false fail-closed traps (see `skill-shell-cli-test` §0.1 / **CL-SHELL-TTY-PRIVILEGE-TRAPS**) |
| test-plan | Baseline coverage + TP-* from findings; shell Type 1 → dual elevation TP rows (negative fail + positive interactive mode probe) |
| lessons | P-* table: failure mode + re-check |
| reports/* | Summary + issues or classification; link P-* / TP-* |

---

## 5. Agent procedure (after any review)

1. Write/update `reports/YYYY-MM-DD-<scope>.md`.  
2. Update `index.md`.  
3. Merge new modes into `lessons.md`.  
4. Add/update `test-plan.md` rows.  
5. Adjust `what-to-review.md` if a new permanent surface appeared.  
6. Leave scratch files out of git.

---

## 6. CIAO alignment

| Principle | Application |
|-----------|-------------|
| Caution | Lessons force re-check of past failures |
| Intentional | Explicit checklist + TP registry |
| Anti-fragile | Knowledge survives sessions and clones |
| Over-protect | Mandatory promote-to-reviews after durable runs |
| SSOT | index + lessons + test-plan |

---

## 7. Protection Rule

Agents **MUST NOT**:

1. Claim a product review “done” with only `/tmp` artifacts when `{{REVIEWS_DIR}}` exists or is required.  
2. Gitignore the whole reviews tree as “agent junk.”  
3. Skip `lessons.md` on subsequent reviews.  
4. Commit secrets into reports.  
5. Replace live requirements with reviews-only law.

---


## Design-time verification

| Gate | Artifact | Phase |
|------|----------|-------|
| Specialize → product suite or checklist | declare TP-IDs or checklist in specialized REQ | Design |
| RTM | `../tests/template-requirement-test-traceability.md` | Design |

When this mold has no executable TP family, mark **n/a** with reason in product `reviews/test-plan.md`.

**Last Updated**: 2026-10-05  
**Owner**: {{OWNER}}
