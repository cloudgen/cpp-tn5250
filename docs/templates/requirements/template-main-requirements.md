---
name: main-requirements
id: LM-MAIN-REQUIREMENTS
kind: law-mold
description: >
  Portable law mold. Cite as LM-MAIN-REQUIREMENTS (path secondary).
---

**file**: template-main-requirements.md  
**Status**: Active (Version 1.1.0 – Versioned registry surface; no harness path leak)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

## 1. Purpose

This template shapes the **versioned product-law registry** for a project: `docs/requirements/index.md` plus live `requirement-*.md` files.

Under the default docs git policy, **only** `docs/requirements/**` is tracked. The specialized index and requirement files **must be self-contained**: they must not advertise agent harness trees that stay local/gitignored.

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
| **Project requirements** | `docs/terminologies/project-requirements.md` | `product-law` | Requirement surface |
| **Domain requirements** | `docs/terminologies/domain-requirements.md` | `product-law` | Domain law after specialize |
| **Registry discipline** | `docs/terminologies/registry-discipline.md` | `policy` | index.md honesty |

**SSOT types used:** `meta-catalog` · `policy` · `product-law`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Core Project Principles (CIAO / CIAO-Lite)

- **Caution (CIAO Principle 1)**: Assume nothing. Validate storage, handle missing resources, non-interactive shells, permission issues, and external dependency failures.
- **Intentional (CIAO Principle 2)**: Every function, command, configuration, and behavior has a documented purpose.
- **Anti-fragile (CIAO Principle 3)**: The system survives minimal environments (Alpine, dash, Git Bash), optional `curl | sh` execution when online install is in scope, CI/CD pipelines, multi-user systems, and air-gapped networks.
- **Over-protect (CIAO Principle 4 / CIAO-Lite O · Principle 20)**: Verbose comments, Protection Zones, safe defaults, checksum/digest verification, per-user isolation, and well-structured requirement documents are intentional defensive features.

## 3. Recommended specialized layout (versioned surface only)

After specialization, `docs/requirements/index.md` and this folder should look like:

### Master registry

- `docs/requirements/index.md` — **only** rows for live `requirement-*.md` (+ how to use the registry)
- `docs/requirements/README.md` (optional) — purpose and layout of **this folder only**
- `docs/requirements/requirement-*.md` — project-enforceable rules

### Registry table shape (example)

| ID / key | Title | Area | Status | Path | Updated |
|----------|-------|------|--------|------|---------|
| requirement-{{TOPIC}} | {{TITLE}} | {{AREA}} | Active | `docs/requirements/requirement-{{TOPIC}}.md` | YYYY-MM-DD |

### Forbidden in specialized `index.md` / requirements README / Related tables

Do **not** list as navigation or layer maps:

- `docs/templates/**` / bare `template-*.md`
- `docs/skills/**` / bare `skill-*.md`
- `docs/terminologies/**`
- `docs/incidents/**`
- `docs/checklists/**` / checklist forms under templates
- Full `docs/` tree inventories

**While authoring**, agents may load portable templates and skills. **After specialization**, provenance stays out of the versioned Related/Alignment path lists (peer requirements + product paths + public CIAO URLs only).

### Suggested requirement topics (names only — create real files when specializing)

Examples of **requirement file basenames** (not template paths):

- **Class law (software-development):** `requirement-class-software-dev` — specialize from portable `template-requirement-class-software-dev` (residual language, compiler/toolchain, package tools; no product hardcode in core)
- **Class law (server-maintenance):** `requirement-class-server-maintenance` — specialize from portable `template-requirement-class-server-maintenance` (residual OS type, glibc/musl/uClibc, package manager class; no product/host hardcode in core)
- Architecture / privilege: `requirement-least-privilege-user`, `requirement-three-layer-privilege-model`, `requirement-cli-interface` (or language-prefixed variants)
- Install / lifecycle: `requirement-online-install`, `requirement-self-management`, `requirement-path-and-shell-support`
- Output / interaction: `requirement-output-requirements`, `requirement-interactive-vs-noninteractive`, `requirement-error-handling`
- Ops: `requirement-backup-strategy`, `requirement-configuration-management`, `requirement-project-folder`

Specialize from matching portable templates when present; register only the resulting `requirement-*.md` in the index.

## 4. Non-Negotiable Core Rules

- The main CLI script (when **online install / Type O** is applicable) should remain a **single executable** file for `curl | sh` compatibility; empty-argv policy then follows Type O install-ensure (`template-shell-cli-zero-arguments.md`), not Type N help-default.
- Primary runtime is declared per project (`{{PRIMARY_RUNTIME}}`). Remote platform access (if any) **MUST** use the project’s official API client package (`{{API_CLIENT_PACKAGE}}`), not ad-hoc HTTP.
- All user-facing output must go through a centralized output system.
- **Backup before any modification** to persistent files or state.
- Strict separation of privilege layers (specialize least-privilege / three-layer rules when needed).
- All requirement files must use the exact `requirement-` prefix (with language prefix when appropriate).
- The master index (`docs/requirements/index.md`) must be updated when adding significant new requirements (**requirement rows only**).
- **Git-surface filter:** versioned requirements content must not expose default-ignored harness docs (see §3 Forbidden).

## 5. Why This Requirement Exists (Direct CIAO Alignment)

- **CIAO Principle 4 / CIAO-Lite O · Principle 20 – Over-protect / Protect Against AI** (https://github.com/cloudgen/ciao): A single, well-maintained master requirements registry with clear cross-references protects the project from fragmented, contradictory, or forgotten rules — without publishing local harness maps.
- **CIAO Principle 2 – Intentional** (https://github.com/cloudgen/ciao): Every major decision and defensive rule is documented and discoverable from one versioned place.
- **CIAO Principle 1 – Caution** (https://github.com/cloudgen/ciao): Centralized documentation prevents silent drift; git-surface filter prevents false clone inventory.
- **CIAO Principle 5 – SSOT**: Product law for git is `docs/requirements/**`; harness trees remain local authoring inputs.

## 6. Protection Rule (Master Sacred Rule)

**Any AI assistant, Grok, or maintainer working on this project MUST**:

- Consult `docs/requirements/index.md` and all linked `requirement-*.md` documents before making significant changes.
- Never weaken or remove any Protection Zone without explicit justification and approval.
- Preserve the single-file executable nature and POSIX compatibility of the main script when that is product law.
- Update the master index when adding new major requirements (**append requirement rows only**).
- Respect "DO NOT MODIFY" blocks and historical lessons recorded in the code and requirements.
- Only act on explicit user instructions containing clear action words.
- **MUST NOT** put `docs/templates/`, `docs/skills/`, `docs/terminologies/`, `docs/incidents/`, or checklist paths into specialized `index.md`, requirements README, or requirement Related/Alignment navigation.
- **MUST NOT** use the registry as a backdoor index of ignored workspace knowledge.

**Violating this rule is considered a critical regression.**

---


## Design-time verification

| Gate | Artifact | Phase |
|------|----------|-------|
| Specialize → product suite or checklist | declare TP-IDs or checklist in specialized REQ | Design |
| RTM | `../tests/template-requirement-test-traceability.md` | Design |

When this mold has no executable TP family, mark **n/a** with reason in product `reviews/test-plan.md`.

**Last Updated**: 2026-07-12  
**Owner**: Project Lead / Documentation Layer (Generalized Template)  
**Alignment**: Fully synchronized with specialized `requirement-*.md` patterns and **CIAO Principles v2.10.2** (https://github.com/cloudgen/ciao).

---

**How to use this template**:

1. Specialize into the project as `docs/requirements/index.md` (registry) — do not leave this file full of `template-*` path lists.
2. Populate the registry table with **actual** `requirement-*.md` files only.
3. Keep Core Principles, Non-Negotiable Rules, and Protection Rule largely intact; drop harness inventories.
4. Update the index whenever you add or significantly change requirement documents.
5. Cross-link **between** live requirements and product paths — not to portable templates/skills inside the versioned surface.
6. Keep agent harness maps in local process docs (ignored by default), not in this registry.
