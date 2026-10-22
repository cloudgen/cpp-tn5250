---
name: milestones
id: LM-MILESTONES
kind: law-mold
description: >
  Portable law mold. Cite as LM-MILESTONES (path secondary).
---

**file**: template-milestones.md
**Status**: Active (Version 1.0.0 – Converted & Generalized from template form docs/templates/requirements/template-milestones.md)
**Project**: Any CIAO-Lite Project (reusable template)
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

## 1. Purpose

This template provides a recommended **milestone structure** for CIAO-Lite projects.

It helps teams plan development in defensive, incremental phases — starting from foundational stability and moving toward advanced features — while maintaining strong alignment with CIAO principles throughout.

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
| **Project requirements** | `docs/terminologies/project-requirements.md` | `mention-only` | Milestone trace to REQs |

**SSOT types used:** `mention-only` · `meta-catalog` · `policy`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Recommended Milestone Phases

### Milestone 1.0 — Foundation (Core Stability)
**Goal**: Establish a solid, defensive base that works reliably in harsh environments.

- Single-file executable with `curl | sh` support
- POSIX `/bin/sh` compatibility (Alpine, dash, Git Bash)
- Safe variable defaults in every function
- Centralized output system (`out_text()`, `--quiet`, `--json`)
- Basic self-management (`self-update`, `self-uninstall`, `version`)
- Initial Protection Zones and defensive comment blocks
- Basic error handling and non-interactive safety

**Status**: Foundation phase

### Milestone 2.0 — Defensive Layer & Documentation
**Goal**: Complete the core defensive architecture and documentation.

- Full set of `requirement-*.md` documents (using exact `requirement-` prefix)
- Complete Protection Zones in all major functions
- Robust error handling and backup strategy
- Least-privilege user model + internal sudo pattern
- Full requirement enforcement checklist
- Enhanced diagnostics (`about` command)
- Consistent behavior in interactive and non-interactive modes

**Target**: Early stable release  
**Status**: In Progress (High Priority)

### Milestone 3.0 — Usability & Configuration
**Goal**: Improve user experience and configuration management.

- Richer CLI experience (progress, themed output where appropriate)
- Configuration file support and environment variable management
- Better help text, examples, and command documentation
- Improved JSON output consistency
- Graceful handling of optional features and fallbacks

**Target**: Stable production release  
**Status**: Planned

### Milestone 4.0 — Advanced Features & Extensibility
**Goal**: Add power-user and automation features.

- Advanced backup/restore strategies
- Plugin or extension support (optional)
- Custom resource and Docker image management
- Better integration with CI/CD, scripts, and monitoring tools
- Interactive menu mode (optional)

**Status**: Planned

### Milestone 5.0+ — Ecosystem & Packaging (Future Vision)
**Goal**: Packaging, distribution, and ecosystem growth.

- Official packages (deb, rpm, brew, etc.)
- Official container images with digest pinning
- System service templates (systemd, etc.)
- Web dashboard or TUI (optional)
- Cross-project collaboration features

**Status**: Future Vision

## 3. Why This Requirement Exists (Direct CIAO Alignment)

- **CIAO Principle 4 / CIAO-Lite O · Principle 20 – Over-protect / Protect Against AI** (https://github.com/cloudgen/ciao): Structured milestones with clear defensive goals prevent chaotic development and repeated regressions.
- **CIAO Principle 2 – Intentional** (https://github.com/cloudgen/ciao): Every phase has explicit goals tied to safety, documentation, and usability.
- **CIAO Principle 3 – Anti-fragile** (https://github.com/cloudgen/ciao): Incremental milestones allow the project to remain stable even as new features are added.

## 4. Design Principles (CIAO / CIAO-Lite)

- **Caution (CIAO Principle 1)**: Foundation and defensive layers come first. Features are added only after the core is stable.
- **Intentional (CIAO Principle 2)**: Each milestone has clear, documented objectives.
- **Anti-fragile (CIAO Principle 3)**: The project improves its ability to survive change and unexpected environments over time.
- **Over-protect (CIAO Principle 4 / CIAO-Lite O · Principle 20)**: Documentation, Protection Zones, and enforcement mechanisms are prioritized early.

## 5. Protection Rule (Sacred)

**Future AI assistants, Grok, or maintainers MUST NOT**:

- Skip or weaken Milestone 1.0 and 2.0 defensive foundations in favor of rushing features.
- Remove or deprioritize Protection Zones, requirement documentation, or the enforcement checklist.
- Reorder milestones in a way that puts advanced features before core stability and least-privilege architecture.
- Treat milestone planning as optional or cosmetic.

**Violating this rule is considered a critical regression.**

---


## Design-time verification

| Gate | Artifact | Phase |
|------|----------|-------|
| Specialize → product suite or checklist | declare TP-IDs or checklist in specialized REQ | Design |
| RTM | `../tests/template-requirement-test-traceability.md` | Design |

When this mold has no executable TP family, mark **n/a** with reason in product `reviews/test-plan.md`.

**Last Updated**: 2026-06-04  
**Owner**: Project Planning & Architecture Layer (Generalized Template)  
**Alignment**: Fully synchronized with `docs/requirements/index.md`, `AGENTS.md` (CIAO Protection Zones) and specialized requirements, `docs/templates/requirements/template-defensive-practices.md`, and **CIAO Principles 1, 2, 3, 4, 20 (v2.10.2)** (https://github.com/cloudgen/ciao).

---

**How to use this template**:
1. Copy to your project as `docs/templates/requirements/template-milestones.md`.
2. Customize milestone names, targets, and specific deliverables to match your project.
3. Keep the overall phased structure (Foundation → Defensive Layer → Usability → Advanced → Ecosystem).
4. Update status and target releases as work progresses.
5. After specialization, register the new `requirement-*.md` in `docs/requirements/index.md` (requirement row only — do not list this template path in the registry).