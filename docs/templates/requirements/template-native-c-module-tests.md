---
name: native-c-module-tests
id: LM-NATIVE-C-MODULE-TESTS
kind: law-mold
description: >
  Portable law mold for automated pure-unit and storage-path tests of C modules
  without a full GUI/engine session. Cite as LM-NATIVE-C-MODULE-TESTS.
---

**file**: template-native-c-module-tests.md  
**Status**: Active (Version 1.0.0)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered / Over-protect)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

## 1. Purpose

Define **automated** verification law for **C (and C-linked) modules** that can be exercised **without** a full GUI or browser-engine UI session.

**Specialize into:** product `docs/requirements/requirement-c-tests.md` (or equivalent) with filled Implementation Notes and real suite inventory.

**Parent strategy mold:** `template-native-c-testing-strategy.md` (**`LM-NATIVE-C-TESTING-STRATEGY`**).  
**Proof mold:** `../tests/template-native-c-module-test-plan.md` (**`PM-NATIVE-C-MODULE-TEST-PLAN`**).

### 1.1 In scope (portable tiers)

| Tier | Subject class | Runner placeholder | Typical deps (specialize) |
|------|---------------|--------------------|---------------------------|
| **A — Pure unit** | path helpers, config parse, output mode init/log, project SSOT macros | `{{UNIT_RUNNER}}` | e.g. `{{UNIT_PKGCONFIG}}` |
| **B — Storage** | storage path init, optional sqlite key/value roundtrip | `{{STORAGE_RUNNER}}` | e.g. unit deps + `{{STORAGE_PKGCONFIG}}` |
| **Combined** | A then B | `{{ALL_RUNNER}}` | union |

### 1.2 Out of scope (this mold)

| Topic | Owner after specialize |
|-------|------------------------|
| Full product build smoke | Strategy REQ (**`LM-NATIVE-C-TESTING-STRATEGY`**) |
| Interactive GUI / login E2E | Strategy / manual |
| Full engine/UI widget mock harnesses | Explicit operator order only |
| Shell Type O TP-CLI / install-lifecycle suites | Shell proof molds |

### 1.3 Runner language note

Runners **may** be shell scripts. The **subject under test** is C module behavior. Do not invent a separate “shell product test” requirement solely because the runner is `.sh`.

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
| **Ship unit** | `docs/terminologies/ship-unit.md` | `identity-runtime` | Product binary (not required to link every pure suite) |
| **Project reviews** | `docs/terminologies/project-reviews.md` | `product-law` | Product verification map after specialize |

**SSOT types used:** `meta-catalog` · `policy` · `identity-runtime` · `product-law`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

---

## 2. CIAO-Lite for C suites

| Letter | Rule |
|--------|------|
| **C** | Suites must not remove or bypass production safety checks to go green |
| **I** | Assert real config section maps, path layouts, and SSOT macros — not idealized APIs |
| **A** | Prefer temporary home/config fixtures; avoid depending on the operator’s real profile |
| **O** | Keep intentional error paths (null buffer, invalid input) and allow expected diagnostic noise |

---

## 3. Core rules (MUST / MUST NOT)

### 3.1 MUST

1. Provide a Tier A runner (`{{UNIT_RUNNER}}`) when pure-unit coverage is claimed.  
2. Provide a Tier B runner (`{{STORAGE_RUNNER}}`) when storage-path / sqlite coverage is claimed.  
3. On **missing development packages**, runners **must** print a clear SKIP message and exit with a **non-zero skip code** (recommended **2**), distinct from assertion failure (**1**).  
4. Isolate fixtures via temporary `HOME` and/or temp config paths when suites touch user storage layout.  
5. Exercise **quote/path pollution defenses** when the product has config→path history of that failure class.  
6. Keep compiled suite binaries out of version control (gitignore product `{{TESTS_DIR}}/bin/` or equivalent).  
7. When linking modules that pull optional engine headers, prefer **compile-time stubs** only for symbols needed to link path/storage units — not as proof of engine correctness.

### 3.2 MUST NOT

1. Treat link stubs as full engine/UI verification.  
2. Commit secrets, real session DBs, or host vault paths into `{{TESTS_DIR}}/`.  
3. Delete defensive production checks “so tests pass.”  
4. Hardcode a single product brand, absolute host path, or host SSH vault basename into this mold.

### 3.3 SHOULD

1. Document product behaviors locked by suites (section map surprises, filename SSOT divergence, mkdir vs final path shape).  
2. Prefer extending Tier A/B over inventing many runners.  
3. Cross-link configuration, output, cookies/database, and coding-style specialized REQs.

---

## 4. Suite inventory shape (specialize — do not freeze counts)

When specialized, product law **must** list live suites or point to a disk-truth inventory:

| Field | Meaning |
|-------|---------|
| Suite id / source | e.g. `test_{{CONCERN}}.c` |
| Tier | A or B |
| Focus | one sentence |
| Runner | which runner builds/runs it |

Portable mold **does not** mandate a fixed suite count. Specialize with real basenames only.

---

## 5. Acceptance criteria (template form)

| Gate | Pass |
|------|------|
| Unit host with deps | `{{UNIT_RUNNER}}` exits 0 |
| Storage host with deps | `{{STORAGE_RUNNER}}` exits 0 |
| Combined (if provided) | `{{ALL_RUNNER}}` exits 0 when both tiers have deps |
| Missing unit deps | unit runner exits skip code + SKIP text |
| Missing storage deps | storage runner exits skip code + SKIP text |
| Fixtures | temp home/config only as primary fixture |

---

## 6. Design-time verification

| Step | Artifact |
|------|----------|
| Default TP families | **TP-CPURE-***, **TP-CSTOR-*** |
| Case catalog | `../tests/template-native-c-module-test-plan.md` |
| RTM | `../tests/template-requirement-test-traceability.md` |
| Product status | specialized C-tests REQ + `{{REVIEWS_DIR}}` rows (`todo` → `have`) |

---

## 7. Specialization notes (Implementation Notes placeholders)

| Placeholder | Fill with |
|-------------|-----------|
| `{{APP_NAME}}` | Product name |
| `{{PROJECT_ID}}` | Product id / storage basename |
| `{{TESTS_DIR}}` | e.g. `tests` |
| `{{UNIT_RUNNER}}` | e.g. `tests/run_unit.sh` |
| `{{STORAGE_RUNNER}}` | e.g. `tests/run_storage.sh` |
| `{{ALL_RUNNER}}` | e.g. `tests/run_all.sh` |
| `{{UNIT_PKGCONFIG}}` | e.g. `glib-2.0` |
| `{{STORAGE_PKGCONFIG}}` | e.g. `sqlite3` |
| `{{SKIP_EXIT}}` | e.g. `2` |
| `{{STUBS_DIR}}` | optional engine header stub path |
| `{{REVIEWS_DIR}}` | e.g. `reviews` |
| `{{OWNER}}` | Requirement owner |

**Related specialized REQs (examples only):** configuration, output, cookies/database, project structure, coding-style, umbrella tests strategy.

---

## 8. Protection Rule (Sacred)

Future agents **MUST NOT**:

1. Cite this mold from product source as behavioral authority (cite specialized `requirement-*` only).  
2. Paste a single product’s full suite list into the mold as universal law.  
3. Confuse **TP-CSTOR-*** (native C storage path suites) with shell domain **TP-STORAGE-*** (dual volatile/persist CLI storage).  
4. Promote full UI/engine mock frameworks as the default portable requirement for pure helpers.

---

**Last Updated**: 2026-08-11  
**Owner**: {{OWNER}}  
**Alignment**: `template-native-c-testing-strategy.md` · `../tests/template-native-c-module-test-plan.md` · `template-configuration-management.md` · `template-output-requirements.md` · [CIAO](https://github.com/cloudgen/ciao) / [CIAO-Lite](https://github.com/cloudgen/ciao-lite)
