---
name: native-c-testing-strategy
id: LM-NATIVE-C-TESTING-STRATEGY
kind: law-mold
description: >
  Portable law mold for overall verification strategy of native C/C++ (and C-linked)
  desktop or library products with heavy GUI/engine coupling. Cite as LM-NATIVE-C-TESTING-STRATEGY.
---

**file**: template-native-c-testing-strategy.md  
**Status**: Active (Version 1.0.0)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered / Over-protect)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

## 1. Purpose

Define a **layered verification strategy** for products implemented primarily in **C/C++** (optionally with GObject/GTK/WebKit or other heavy runtime coupling) where **full UI/engine isolation is costly**.

**Specialize into:** product `docs/requirements/requirement-tests.md` (or `requirement-{{APP_NAME}}-tests.md`) with filled Implementation Notes.

**Peer law mold (automated pure/storage suites):** `template-native-c-module-tests.md` (**`LM-NATIVE-C-MODULE-TESTS`**).  
**Proof mold:** `../tests/template-native-c-module-test-plan.md` (**`PM-NATIVE-C-MODULE-TEST-PLAN`**).

**Not for:** shell Type O CLI ship units as the primary product class (use shell CLI + install proof molds).

### 1.1 Intention

- Keep **full-build** and **manual/integration** gates honest for coupled surfaces.  
- Allow **focused pure-module** automation where isolation is real.  
- Forbid “mock the entire engine/UI” as the default path without explicit operator order.  
- Never weaken production safety to make tests pass.

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
| **Ship unit** | `docs/terminologies/ship-unit.md` | `identity-runtime` | Binary / library under full-build gate |
| **Project reviews** | `docs/terminologies/project-reviews.md` | `product-law` | Product TP / verification map after specialize |
| **Ready ship** | `docs/terminologies/ready-ship.md` | `identity-runtime` | Release-minded gates (when claimed) |

**SSOT types used:** `meta-catalog` · `policy` · `identity-runtime` · `product-law`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

---

## 2. CIAO-Lite testing philosophy (portable)

| Letter | Application |
|--------|-------------|
| **C** | Tests must not weaken production safety checks |
| **I** | Test the real architecture, not a fantasy modularization |
| **A** | Suites should survive refactors without constant rewrites |
| **O** | Do not delete defensive code “to make tests pass” |

---

## 3. Verification layers (specialize names)

| Layer | Intent | Typical proof |
|-------|--------|----------------|
| **L0 — Full build** | Ship unit compiles/links | Product build entry (e.g. `{{BUILD_CMD}}`) |
| **L1 — Pure C unit** | Isolated pure helpers (no UI session) | **`LM-NATIVE-C-MODULE-TESTS`** Tier A + **TP-CPURE-*** |
| **L2 — Storage / persistence path** | Path + optional sqlite without full UI | **`LM-NATIVE-C-MODULE-TESTS`** Tier B + **TP-CSTOR-*** |
| **L3 — Combined pure+storage** | Convenience runner | Product `{{ALL_RUNNER}}` when specialized |
| **L4 — Integration / manual** | Cookies, login, UI smoke | Operator scenarios in specialized REQ |
| **L5 — Full engine/UI E2E or heavy mocks** | Deferred by default | Explicit operator order only |

**Naming clarity (must specialize):** product runners that only run pure/storage suites **must not** be described as “full GUI E2E” without separate true E2E law.

---

## 4. Core rules (MUST / MUST NOT)

### 4.1 MUST

1. Declare which layers are **ship gates** vs **optional when deps present**.  
2. Keep full-build (L0) as the baseline for release-minded changes when a ship unit exists.  
3. When pure/storage suites are claimed, specialize **`LM-NATIVE-C-MODULE-TESTS`** and name runners + missing-dep skip policy.  
4. Prefer temp home/config fixtures for automated suites (no pollution of operator profile as primary fixture).  
5. Document manual/integration scenarios for coupled surfaces (login, persistence, debug dumps) when those features are Active law.

### 4.2 MUST NOT

1. Require full WebKit/GTK (or equivalent engine) **widget mocks** as the only automated path without explicit operator approval.  
2. Add test-only hooks that weaken production path, cookie, or security checks.  
3. Claim automated pure/storage coverage without running the specialized runners (or recording an honest SKIP for missing dev packages).  
4. Freeze product brand, absolute host paths, or particular SSH vault basenames into this mold (no-hardcode).

### 4.3 SHOULD

1. Split umbrella strategy (this mold) from detailed pure/storage suite law (**`LM-NATIVE-C-MODULE-TESTS`**).  
2. Point product verification maps at both strategy and suite REQs after specialize.

---

## 5. Minimum acceptance checklist (template form)

| Check | Pass criteria (specialize) |
|-------|----------------------------|
| Build | Clean compile of chosen method |
| Pure unit (if claimed + deps) | Unit runner exit 0, or documented SKIP |
| Storage (if claimed + deps) | Storage runner exit 0, or documented SKIP |
| Start | Ship unit starts without immediate crash (when built) |
| Persistence | Paths honest per storage/config REQs after first run |
| Output modes | Help / quiet / machine modes do not crash (when claimed) |

---

## 6. Design-time verification

| Step | Artifact |
|------|----------|
| Default TP families | **TP-CPURE-***, **TP-CSTOR-*** via peer proof mold; L0/L4 via build + manual (no TP required) |
| Full matrix | `../tests/template-requirement-test-traceability.md` |
| Case catalog | `../tests/template-native-c-module-test-plan.md` |
| Product status | specialized strategy + C-module test REQs (product IDs) + `{{REVIEWS_DIR}}` verification map |

**RTM cite:** **`LM-NATIVE-C-TESTING-STRATEGY`** → **`PM-NATIVE-C-MODULE-TEST-PLAN`** (for L1–L3 automation only).

---

## 7. Specialization notes (Implementation Notes placeholders)

| Placeholder | Fill with |
|-------------|-----------|
| `{{APP_NAME}}` | Product display / package name |
| `{{PROJECT_ID}}` | Product id string / storage basename |
| `{{BUILD_CMD}}` | Primary build command |
| `{{TESTS_DIR}}` | Product test root (often `tests`) |
| `{{UNIT_RUNNER}}` | Tier A runner path |
| `{{STORAGE_RUNNER}}` | Tier B runner path |
| `{{ALL_RUNNER}}` | Combined runner path |
| `{{REVIEWS_DIR}}` | Product reviews path (often `reviews`) |
| `{{OWNER}}` | Requirement owner |

**Example specialize targets (not universal law):** `requirement-tests.md` (strategy) + `requirement-c-tests.md` (suites).

---

## 8. Protection Rule (Sacred)

Future agents **MUST NOT**:

1. Treat this mold as product law without specializing into `requirement-*.md`.  
2. Copy product suite inventories or brand names into this mold as universal defaults.  
3. Collapse shell **TP-CLI** / domain **TP-STORAGE** families into native C TP-CPURE/TP-CSTOR without renaming.  
4. Require full engine mock harnesses as seed default for every C desktop product.

---

**Last Updated**: 2026-08-11  
**Owner**: {{OWNER}}  
**Alignment**: `template-native-c-module-tests.md` · `../tests/template-native-c-module-test-plan.md` · `template-requirement-class-software-dev.md` · `template-coding-style.md` · [CIAO](https://github.com/cloudgen/ciao) / [CIAO-Lite](https://github.com/cloudgen/ciao-lite)
