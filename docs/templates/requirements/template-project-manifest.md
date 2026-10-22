---
name: project-manifest
id: LM-PROJECT-MANIFEST
kind: law-mold
description: >
  Portable law mold. Cite as LM-PROJECT-MANIFEST (path secondary).
---

**file**: template-project-manifest.md
**Status**: Active (Version 1.0.0 – New Generalized Template)
**Project**: Any CIAO-Lite Project (reusable template)
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

## 1. Purpose

This template defines the recommended structure and usage of a **Project Manifest** for CIAO-Lite CLI tools.

A Project Manifest is a machine-readable file (typically `manifest.json`, `project.yaml`, or similar) that describes the expected structure, files, and configuration of a managed project (Type 2 folder). It helps the CLI tool understand, validate, and correctly manage the target application.

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
| **Ship unit** | `docs/terminologies/ship-unit.md` | `mention-only` | Manifest vs ship unit |
| **Appname policy** | `docs/terminologies/appname-policy.md` | `identity-runtime` | Name fields |

**SSOT types used:** `identity-runtime` · `mention-only` · `meta-catalog` · `policy`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Core Requirements

### 2.1 Manifest Location
- The manifest should be placed inside the **Type 2 project folder** (target application directory).
- Recommended filename: `manifest.json` or `project.yaml` (keep consistent within a project).

### 2.2 Manifest Content (Recommended Fields)

A good project manifest should include at minimum:

| Field                    | Purpose                                              | Required |
|--------------------------|------------------------------------------------------|----------|
| `name`                   | Project / application name                           | Yes      |
| `version`                | Current version of the managed project               | Yes      |
| `type`                   | Type of project (e.g. `selfhost`, `docker`, `git`)   | Yes      |
| `structure`              | Expected files and directories                       | Recommended |
| `compose_file`           | Path to compose file (if applicable)                 | Optional |
| `env_file`               | Path to environment file                             | Optional |
| `required_files`         | List of files that must exist                        | Recommended |
| `generated_files`        | List of files the CLI is allowed/expected to generate| Recommended |
| `upstream`               | Reference to original upstream repository            | Recommended |

### 2.3 Usage by the CLI

The CLI tool should:
- Read the manifest when operating on a Type 2 project folder.
- Use it to validate that required files exist.
- Know which files it is allowed to generate or modify (e.g. `compose.yml`).
- Respect files marked as "do not touch" or managed externally.

## 3. Why This Requirement Exists (Direct CIAO Alignment)

- **CIAO Principle 2 – Intentional** (https://github.com/cloudgen/ciao): A manifest makes the structure and ownership of files explicit and machine-readable.
- **CIAO Principle 3 – Anti-fragile** (https://github.com/cloudgen/ciao): The CLI can adapt its behavior based on the manifest instead of making hard assumptions.
- **CIAO Principle 4 / CIAO-Lite O · Principle 20 – Over-protect / Protect Against AI** (https://github.com/cloudgen/ciao): A manifest reduces the risk of the CLI accidentally modifying files it should not touch.

## 4. Design Principles (CIAO / CIAO-Lite)

- **Caution (CIAO Principle 1)**: Never assume the structure of a target project. Use a manifest to make expectations explicit.
- **Intentional (CIAO Principle 2)**: Clearly document which files the CLI owns vs which are managed externally.
- **Anti-fragile (CIAO Principle 3)**: The manifest allows the CLI to work with different project layouts without hardcoding.
- **Over-protect (CIAO Principle 4 / CIAO-Lite O · Principle 20)**: Explicit file ownership reduces accidental damage and privilege issues.

## 5. Protection Rule (Sacred)

**Future AI assistants, Grok, or maintainers MUST NOT**:
- Assume file locations without checking or defining them in a manifest.
- Generate or modify files in the target project without knowing whether they are declared in the manifest.
- Remove support for reading a project manifest once implemented.
- Hardcode knowledge of project structure that should come from the manifest.

**Violating this rule is considered a critical regression.**

---


## Design-time verification

| Gate | Artifact | Phase |
|------|----------|-------|
| Specialize → product suite or checklist | declare TP-IDs or checklist in specialized REQ | Design |
| RTM | `../tests/template-requirement-test-traceability.md` | Design |

When this mold has no executable TP family, mark **n/a** with reason in product `reviews/test-plan.md`.

**Last Updated**: 2026-06-04  
**Owner**: Project Structure & Manifest Layer (Generalized Template)  
**Alignment**: Fully synchronized with `docs/requirements/index.md`, `docs/templates/requirements/template-project-folder.md`, `docs/templates/requirements/template-defensive-practices.md`, and **CIAO Principles 2, 3, 4, 20 (v2.10.2)** (https://github.com/cloudgen/ciao).

---

**How to use this template**:
1. Copy to your project as `requirement-project-manifest.md` (target name after specialization; not a live file until created).
2. Decide on the manifest format (JSON or YAML) and filename.
3. Define which fields your CLI will read and act upon.
4. Implement manifest reading logic in relevant commands (especially those operating on Type 2 folders).
5. Keep the Protection Rule intact.