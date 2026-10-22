---
name: upstream-git-analysis
id: LM-UPSTREAM-GIT-ANALYSIS
kind: law-mold
description: >
  Portable law mold. Cite as LM-UPSTREAM-GIT-ANALYSIS (path secondary).
---

**file**: template-upstream-git-analysis.md
**Status**: Active (Version 1.0.0 – Generalized from skill-upstream-git-analysis.md for reusable CIAO-Lite projects)
**Project**: {{APP_NAME}} – {{PLATFORM_NAME}} Platform Management CLI
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

# Template: Upstream Git Repository Deep Analysis (CIAO Defensive)

## 1. Purpose

This template defines the mandatory pre-change process for performing deep, evidence-based analysis of any upstream git repository before writing requirements, code, or giving setup guidance in CIAO-Lite projects. It acts as a defensive gate to prevent assumptions, fake data, incomplete understanding of external dependencies, and regressions caused by rushing or guessing.

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
| **Upstream git analysis** | `docs/terminologies/upstream-git-analysis.md` | `product-law` | Primary term |
| **Stay-honest** | `docs/terminologies/stay-honest.md` | `policy` | Evidence-based analysis |

**SSOT types used:** `meta-catalog` · `policy` · `product-law`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Core Rules / Requirements (Mandatory)

### 2.1 Mandatory Rules (Non-Negotiable)

1. **Read beyond README.md**  
   - Always search for and read **all relevant `*.md` files** in the repository root and key folders that typically contain architecture, installation, prerequisites, build, Docker, or configuration information.
   - Prioritize files describing architecture, installation steps, prerequisites, Docker/compose setup, build process, and configuration.

2. **Focus on discovering real facts** — This is the most important rule.  
   AI assistants frequently skip this step because they are impatient or want to move fast. **You must deliberately and thoroughly search for the following**:

   - Exact file names used for Docker Compose (`.yaml` vs `.yml`)
   - Real prerequisite steps (what packages, tools, and commands are actually required)
   - Real installation and post-installation setup procedures
   - Actual architecture and component relationships (not just diagrams)
   - How the project expects to be run in development versus production/self-host mode
   - **Shell scripts (`*.sh`, `*.bash`)** in the root and `scripts/` folders — these often contain interactive prompts, default value logic, secret generation, volume handling, and configuration collection that markdown files rarely document fully.
   - **Language-specific dependency and manifest files** — These files are critical because they reveal the actual runtime, build tools, dependency strategy, and supported versions. **You must deliberately search for and analyze them.** Do not skip this.

     Common examples include (but are not limited to):
     - **Node.js / JavaScript / TypeScript**: `package.json`, `package-lock.json`, `yarn.lock`, `pnpm-lock.yaml`, `bun.lockb`
     - **Python**: `requirements.txt`, `pyproject.toml`, `setup.py`, `setup.cfg`, `Pipfile`, `poetry.lock`
     - **Java / Kotlin (Maven)**: `pom.xml`
     - **Java / Kotlin (Gradle)**: `build.gradle`, `build.gradle.kts`, `settings.gradle`, `settings.gradle.kts`, `gradle.properties`
     - **Rust**: `Cargo.toml`, `Cargo.lock`
     - **Go**: `go.mod`, `go.sum`
     - **PHP**: `composer.json`, `composer.lock`
     - **Ruby**: `Gemfile`, `Gemfile.lock`
     - **.NET / C#**: `*.csproj`, `Directory.Build.props`, `global.json`
     - **Swift / Objective-C**: `Package.swift`, `Podfile`
     - Any other manifest or lock files that define dependencies or build configuration

   - Any important non-obvious conventions or gotchas

3. **Be extremely cautious**:
   - If something is not clearly documented in `*.md` files, explicitly state: **"Not clearly documented in upstream markdown files. Further investigation needed."**
   - Never invent steps or assume standard practices.
   - When in doubt, quote the exact content from the source files.

### 2.2 Step-by-Step Analysis Process You Must Follow

**Step 1: Repository Overview**
- What is the official repository URL and default branch?
- Are there separate repositories or folders for self-hosting versus development?
- List the most important folders at the root (especially anything related to documentation, scripts, deployment, Docker, build, or configuration).

**Step 2: Discover All Relevant Documentation**
- List **all `*.md` files** found in the root and key subfolders.
- Identify which ones contain installation, prerequisite, architecture, Docker, compose, or configuration information.
- Read and summarize the key ones (do not stop at README.md).
- Explicitly check for and analyze shell scripts (`setup.sh`, `install.sh`, `init.sh`, or similar).
- **Deliberately search for and list all language-specific manifest and lock files** (see Rule #2 for examples). Do not skip this step.

**Step 3: Prerequisites & Environment**
- Extract the **real, documented prerequisites** (operating system, language runtime version, container runtime, build tools, etc.).
- Review language-specific dependency and manifest files in detail (e.g. `package.json`, `pom.xml`, `build.gradle`, `Cargo.toml`, `pyproject.toml`, `go.mod`, etc.) to understand actual runtime requirements, supported versions, build tooling, and dependency management approach.
- Note exact versions mentioned and any special requirements.
- Identify any post-install or setup scripts that must be run.

**Step 4: Docker / Compose / Containerization**
- What is the **exact filename** of the main compose file(s)? (e.g. `docker-compose.yaml`, `compose.yml`)
- Does the project recommend managing certain services (such as reverse proxy) externally or inside Docker?
- What services are defined? What images or build contexts are used?
- How are environment variables and configuration managed?

**Step 5: Architecture & Component Understanding**
- Summarize the **real architecture** based on documentation (not guesses).
- Identify major components/services and how they communicate.
- Note any important volume mounts, networks, or persistence requirements.

**Step 6: Development vs Production/Self-Host Differences**
- Clearly separate:
  - Development workflow (how developers run it locally)
  - Self-host / Production recommendations
- Note if there is a dedicated self-host repository, folder, or setup path.

**Step 7: Output Format**

You must structure your final answer using the following sections:

```markdown
## Upstream Git Analysis Summary

**Repository**: [URL + branch/commit]
**Analysis Date**: [current date]
**Key Documentation Reviewed**:
- list of important .md files read
- list of important .sh scripts analyzed (if any)
- list of language-specific manifest and lock files reviewed

### 1. Prerequisites (Real Documented Steps)
...

### 2. Installation & Setup Process
...

### 3. Docker / Compose Details
- Main compose filename: `docker-compose.yaml` (or whatever it actually is)
...

### 4. Architecture Overview (from docs)
...

### 5. Important Conventions & Gotchas
...

### 6. Gaps / Areas Not Clearly Documented
- Explicitly list anything that was unclear or missing from markdown files.
```

### 2.3 Why This Requirement Exists (Direct CIAO Alignment)
- **CIAO Principle 1 – Caution** (https://github.com/cloudgen/ciao): Assume nothing about external projects. Validate all facts from source.
- **CIAO Principle 2 – Intentional** (https://github.com/cloudgen/ciao): Every decision must be grounded in real evidence from the upstream repository.
- **CIAO Principle 3 – Anti-fragile** (https://github.com/cloudgen/ciao): The project survives changes in upstream dependencies because analysis is systematic and documented.
- **CIAO Principle 4 / CIAO-Lite O · Principle 20 – Over-protect / Protect Against AI** (https://github.com/cloudgen/ciao): Explicit discovery rules and caution statements defend against silent assumptions and regressions.

## 3. Design Principles (CIAO / CIAO-Lite)

- **Caution (CIAO Principle 1)**: Never trust high-level docs or memory. Always verify with full source inspection including manifest files and scripts.
- **Intentional (CIAO Principle 2)**: The analysis process is deliberate, step-by-step, and produces auditable output.
- **Anti-fragile (CIAO Principle 3)**: Works for any upstream repo, large or small, and survives repeated use and team changes.
- **Over-protect (CIAO Principle 4 / CIAO-Lite O · Principle 20)**: The mandatory checklist and "not clearly documented" rule create friction against rushing or guessing.

## 4. Protection Rule (Sacred)

**Future AI assistants, Grok, or maintainers MUST NOT**:
- Skip or weaken the upstream analysis process when the change touches remote API calls, the official client, `_class` models, data layer access, Docker, compose, installation, paths, or external dependencies.
- Generate requirements, code, or setup guidance based on assumptions, README-only reading, or memory.
- Invent steps or use memory instead of quoting source files.
- Remove the "Focus on discovering real facts" rule or the language-specific manifest file discovery requirement.
- Treat the analysis as optional or "for documentation only".

Violating this rule is considered a **critical regression**.

---


## Design-time verification

| Gate | Artifact | Phase |
|------|----------|-------|
| Specialize → product suite or checklist | declare TP-IDs or checklist in specialized REQ | Design |
| RTM | `../tests/template-requirement-test-traceability.md` | Design |

When this mold has no executable TP family, mark **n/a** with reason in product `reviews/test-plan.md`.

**Last Updated**: 2026-06-09 (Generalized into canonical template format from skill-upstream-git-analysis.md; added full CIAO structure, {{PLACEHOLDER}} support, and specialization instructions)

**Owner**: Defensive Process Layer

**Alignment**: Fully synchronized with `docs/requirements/index.md`, `docs/templates/requirements/template-enforcement-checklist.md` (or checklists under `docs/templates/checklists/`), `docs/skills/skill-requirement-template-conversion.md`, `docs/skills/skill-upstream-git-analysis.md`, and **CIAO Principles 1, 2, 3, 4, 20 (v2.10.2)** (https://github.com/cloudgen/ciao).

---

**How to specialize this template**:
1. Copy to `docs/terminologies/upstream-git-analysis.md` + `skill-upstream-git-analysis.md`.
2. Customize any project-specific examples or add integration points with your CLI commands (e.g. "must be run before `{{APP_NAME}} install` or `configure` when touching Docker/compose logic").
3. Integrate the checklist into development workflow (e.g., as a required step before any PR or change touching external deps).
4. After specialization, update `docs/requirements/index.md` with the specialized `requirement-*.md` row only (never list this template path in the registry).
