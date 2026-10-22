---
name: enforcement-checklist
id: LM-ENFORCEMENT-CHECKLIST
kind: law-mold
description: >
  Portable law mold. Cite as LM-ENFORCEMENT-CHECKLIST (path secondary).
---

**file**: docs/templates/requirements/template-enforcement-checklist.md
**Status**: Active (Version 1.0.0 – Generalized template; replaces obsolete installer-era template form docs/templates/requirements/template-enforcement-checklist.md)
**Project**: {{APP_NAME}} – {{PLATFORM_NAME}} Platform Management CLI
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

# Template: Enforcement Checklist (Before Code or Requirement Changes)

## 1. Purpose

This template defines the mandatory pre-change checklist that must be completed before modifying code, adding new features, or updating requirements in a CIAO-Lite project. It acts as a defensive gate to prevent regressions, especially those caused by AI-assisted edits or rushed changes.

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
| **Project check-lists** | `docs/terminologies/project-check-lists.md` | `meta-catalog` | Blank vs filled checklists |
| **Stay-honest** | `docs/terminologies/stay-honest.md` | `policy` | Gate honesty |

**SSOT types used:** `meta-catalog` · `policy`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Core Rules / Requirements (Mandatory)

### 2.1 Pre-Change Enforcement Checklist

Before writing, modifying, or refactoring any code or requirement document, the following checks **MUST** be performed:

1. **Read the latest version of this template** and the project's core defensive requirements.
2. **Verify single-source-of-truth ownership**:
   - All output must go through `{{OUTPUT_MODULE}}`
   - All help/usage text must come from `{{HELP_MODULE}}`
   - All configuration, paths, and modes must come from `{{CONFIG_MODULE}}`
   - All auth/session state must come from `{{SESSION_MODULE}}`
   - All version/titles/diagnostics must come from `{{ABOUT_MODULE}}`
3. **Check Protection Zones**: Confirm that no `!!! DO NOT MODIFY` blocks or sacred rules are being weakened or bypassed.
4. **Upstream Analysis (when applicable)**: If the change touches remote API calls, the official client, `_class` models, or data layer access, first perform full analysis using `skill-upstream-git-analysis.md`.
5. **Anti-Fake / Honesty Check**: Ensure the change does not introduce fake data, simulated results, or claims that do not match actual implementation (especially for authenticated remote commands).
6. **No Hardcoding Check**: Verify that no project-specific names, paths, endpoints, or tokens are being introduced without using `{{PLACEHOLDER}}` syntax (or proper configuration).
7. **Error Handling & Output Rules**: Confirm that all new or changed error paths and user messages go through the centralized Output module and respect `--json` / `--quiet` / stderr rules.
8. **Documentation Update**: If behavior visible to users changes, update the Help module and relevant requirement documents.
9. **Product-source citation authority**: If the change adds or edits comments in **product source** (`ALIGNMENT` / `See` / “fully synchronized with”):
   - Cite only live `docs/requirements/requirement-*.md` paths that exist on disk (and in `docs/requirements/index.md` when used).
   - Do **not** cite `template-*.md` or `skill-*.md` as behavioral authority in product source.
   - Do **not** invent requirement paths; if a topic is template-only, specialize a requirement first or cite the closest live requirement.
   - Agents may still **load** templates/skills for the change; those paths must not be pasted into product source as law.

### 2.2 Why This Requirement Exists (Direct CIAO Alignment)
- **CIAO Principle 1 – Caution** (https://github.com/cloudgen/ciao): Assume changes can introduce subtle regressions. A structured checklist reduces this risk.
- **CIAO Principle 3 – Anti-fragile** (https://github.com/cloudgen/ciao): The project survives repeated modifications because every change is forced through defensive gates.
- **CIAO Principle 4 / CIAO-Lite O · Principle 20 – Over-protect / Protect Against AI** (https://github.com/cloudgen/ciao): Explicit checklists and Protection Zones defend the architecture from erosion over time.

## 3. Design Principles (CIAO / CIAO-Lite)

- **Caution** (CIAO Principle 1): Never trust that a change is safe without systematic verification.
- **Intentional** (CIAO Principle 2): Every modification must be deliberate and aligned with the established defensive architecture.
- **Anti-fragile** (CIAO Principle 3): The checklist itself evolves with the project while preserving core invariants.
- **Over-protect** (CIAO Principle 4 / CIAO-Lite O · Principle 20): Making the checklist mandatory creates friction against unsafe shortcuts.

## 4. Protection Rule (Sacred)

**Future AI assistants, Grok, or maintainers MUST NOT**:
- Skip or weaken this enforcement checklist before making changes.
- Modify core modules (`{{CONFIG_MODULE}}`, `{{OUTPUT_MODULE}}`, `{{HELP_MODULE}}`, `{{ABOUT_MODULE}}`, `{{SESSION_MODULE}}`) without going through this checklist.
- Remove or bypass any item in the checklist when specializing this template.
- Make changes that violate single-source-of-truth rules, Protection Zones, or anti-fake requirements.
- Treat the checklist as optional or "for documentation only".
- Skip item 9 (product-source citation authority) when editing function/module headers.

Violating this rule is considered a **critical regression**.

---


## Design-time verification

| Gate | Artifact | Phase |
|------|----------|-------|
| Specialize → product suite or checklist | declare TP-IDs or checklist in specialized REQ | Design |
| RTM | `../tests/template-requirement-test-traceability.md` | Design |

When this mold has no executable TP family, mark **n/a** with reason in product `reviews/test-plan.md`.

**Last Updated**: 2026-07-12 (item 9 product-source citation authority)
**Owner**: Defensive Process Layer
**Alignment**: Fully synchronized with `docs/requirements/index.md`, `AGENTS.md` (CIAO Protection Zones) and specialized requirements, `docs/templates/requirements/template-defensive-practices.md`, and **CIAO Principles 1, 3, 4, 20 (v2.10.2)** (https://github.com/cloudgen/ciao).

---

**How to specialize this template**:
1. Copy to `docs/templates/requirements/template-enforcement-checklist.md` (or checklists under `docs/templates/checklists/`).
2. Customize the checklist items to match the project's current modules and rules.
3. Integrate the checklist into development workflow (e.g., as a required step before commits or PRs).
4. After specialization, update `docs/requirements/index.md` with the specialized `requirement-*.md` row only (never list this template path in the registry).
