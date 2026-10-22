---
name: requirement-class-software-dev
id: LM-REQUIREMENT-CLASS-SOFTWARE-DEV
kind: law-mold
description: >
  Portable law mold. Cite as LM-REQUIREMENT-CLASS-SOFTWARE-DEV (path secondary).
---

**file**: template-requirement-class-software-dev.md  
**Status**: Active (Version 1.7.0 – in-tool sudo residual specializes LM-SHELL-SUDO-COMMAND)  
**Project**: Any CIAO-Lite software-development workspace (reusable template — **no project brand**)  
**Philosophy**: CIAO **v2.10.2** / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered / Over-protect)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

# =============================================================================
# Template: requirement-class-software-dev
# Specialize to: docs/requirements/requirement-class-software-dev.md
# No-hardcode: use {{PLACEHOLDER}} only — never freeze a product name as universal law
# =============================================================================


## Design-time verification

| Gate | Artifact | Phase |
|------|----------|-------|
| Specialize → product suite or checklist | declare TP-IDs or checklist in specialized REQ | Design |
| RTM | `../tests/template-requirement-test-traceability.md` | Design |

When this mold has no executable TP family, mark **n/a** with reason in product `reviews/test-plan.md`.

## How to use this template (authoring only — do not paste this section into claimed-done project law)

1. Confirm project nature is **software-development** (not genesis-template; not server-maintenance).  
2. Copy/specialize to **`docs/requirements/requirement-class-software-dev.md`** only.  
3. Fill **Implementation Notes** with *this* project’s real non-secret stack choices (no-placeholder).  
4. Keep **core rules** portable: languages, compilers, and tools as **declared choices**, not one hard-coded brand as the only possible universe.  
5. **Residual collection rule:** put here only facts **not already owned** by a more specific Active `requirement-*.md`. When a dedicated requirement later owns a topic, **move** detail there and leave a short pointer in this class file (own-or-point).  
6. Register the specialized file in `docs/requirements/index.md` (Area **`class`**).  
7. **Git-surface:** specialized requirement bodies must not list harness paths (`docs/templates/**`, skills, terminologies, …).

**Target basename (fixed):** `requirement-class-software-dev.md`  
**Genesis:** do **not** create this file (or any `requirement-*.md`) in genesis-template.

---

# Requirement: class-software-dev

**Status:** {{STATUS}}  
**Area:** class  
**Key:** `requirement-class-software-dev`  
**Updated:** {{YYYY-MM-DD}}

## 1. Purpose

Declare this workspace as a **software-development** project class and hold the **general residual collection** of software-engineering facts that are **not yet (or not better) recorded** in more specific requirements: primary **programming language(s)**, **target compilers/toolchains** (with or without version constraints), **project/package tools**, and related build/runtime stack defaults.

This file is **class law + residual SSOT**, not a second copy of domain feature catalogs, Type 0 lifecycle tables, or the **coding-style related REQ** (that file **MUST** exist: it is the specialize-in home for portable learned lessons).

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
| **Software-development project** | `docs/terminologies/software-development-project.md` | `product-law` | Class #2 |
| **Project class** | `docs/terminologies/project-class.md` | `product-law` | Eleven-class model (internal name) |
| **Project nature** | `docs/terminologies/project-nature.md` | `product-law` | Daily-life name for **project class** (alias stub) |
| **Project requirements** | `docs/terminologies/project-requirements.md` | `product-law` | Residual REQs |
| **Coding-style requirement** | `docs/terminologies/coding-style-requirement.md` | `product-law` | Class MUST; specialize-in home for portable lessons |

**SSOT types used:** `meta-catalog` · `policy` · `product-law`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md` · `docs/policies/policy-non-expose-local-machine.md`

## 2. Core Rules (Mandatory — portable)

### 2.0 Project class membership

1. **MUST** treat this workspace as **software-development** (shippable software), not genesis-template and not server-maintenance.  
2. **MUST** use basename **`requirement-class-software-dev.md`** as the sole Active class-law file for this class.  
3. **MUST NOT** register an Active `requirement-class-server-maintenance.md` while class is software-development.  
4. **MUST** retain portable harness knowledge; specialized product knowledge lives in this and peer `requirement-*.md` files.  
5. **MUST** apply software-development SSOT/gate posture when claimed (identity triad, channel, ship unit, precommit when git is used — as applicable).  
6. **MUST NOT** invent hollow product docs solely to look specialized; collect real values or defer explicitly.

### 2.1 Residual collection principle (SSOT hygiene)

7. **MUST** treat this file as the **default home** for software-stack facts **not owned** by another Active requirement.  
8. **MUST NOT** duplicate full normative tables that already live in a more specific Active requirement (e.g. full Type 0 self-management, domain four pillars, automatic-checksum law). Prefer a **one-line pointer** to the peer requirement key.  
9. When a new specialized requirement **takes ownership** of a topic previously only listed here, **MUST** update this file in the **same change**: remove or shrink the residual entry and point to the new owner.  
10. **MUST NOT** leave contradictory stack facts across this file and peer requirements (e.g. two different “primary language” claims).

### 2.2 Programming language(s)

11. **MUST** declare at least one **primary programming language** (or language family) for the ship unit / product implementation.  
12. **SHOULD** list secondary languages only when they are real product law (e.g. embedded scripts, generators), not incidental docs.  
13. **MUST** state whether the product is primarily: interpreted, compiled, polyglot, or package-multi-language — as a closed choice.  
14. **MUST NOT** freeze a marketing product name as if it were the language name; language identifiers are stack facts (e.g. `python`, `go`, `posix-sh`), not brands of *this* product.

### 2.3 Compilers, interpreters, and toolchains

15. **MUST** declare the **target toolchain class** used to build or run the product (examples of *classes*, not hard-coded product law): system `cc`/`c++`, `go`, `rustc`, `javac`, `tsc`, language VM, or “interpreted — no compile step”.  
16. **MUST** state version policy as one of:  
    - **unconstrained** (any recent toolchain that passes tests),  
    - **minimum version** (`>= X.Y`),  
    - **range** (`>= A, < B`),  
    - **pinned** (exact supported set documented in Implementation Notes).  
17. **SHOULD** record whether cross-compilation is in scope (yes/no) and the intended host/target OS families as choice sets, not one absolute host path.  
18. **MUST** fail closed in CI/docs claims: do not claim “supports all compilers” without tests or explicit unconstrained policy.

### 2.4 Project / package / build tools

19. **MUST** declare the **primary project or package tool** used for dependencies and builds (choice examples: language module system, `make`, `cmake`, `meson`, distro packages only, monorepo tool, none).  
20. **MUST** declare how dependencies are resolved (lockfile required / recommended / not used) when the ecosystem supports lockfiles.  
21. **SHOULD** name the test runner and linter/formatter **classes** when they are project law; linter/formatter **detail** lives on the **mandatory** coding-style related REQ (or a dedicated test REQ), not as a substitute for that REQ.  
22. **MUST NOT** require a secret token or private registry password in this file; document only **registry/tool names** and env **variable names**.

### 2.5 Runtime and platform (residual)

23. **MUST** declare the intended **primary runtime/OS family** choice set (e.g. POSIX Linux, multi-OS, container-only) when not fully owned by another architecture requirement.  
24. **SHOULD** declare minimum CPU/arch support only when it is real product law (e.g. `amd64`/`arm64` choice set).  
25. **MUST** separate **developer machine** toolchain requirements from **end-user runtime** requirements when they differ.

### 2.6 No-hardcode / dual policy (class file)

26. **MUST NOT** hard-code a single product/app brand, one org’s production hostname, personal owner identity, or session `$DISPLAY` / X11 display id (`localhost:11.0`, `:0`) as universal core law.  
26b. **MUST NOT** write session Unix login, literal `$HOME` expansion, or `/home/<login>/…` in core **or** Implementation Notes — **`PO-NON-EXPOSE-LOCAL-MACHINE`**. Workspace: ram-drive-first `/dev/shm/{{PROJECT_BASENAME}}` when present, else `{{PROJECTS_ROOT}}/{{PROJECT_BASENAME}}` (typical `{{HOME}}/prjs/{{PROJECT_BASENAME}}`).  
27. **MUST** put live **product** name, repo slug, and concrete pinned versions in **Implementation Notes** (and product README/Config SSOTs where applicable) after collection — complete, not `TBD`, when Status claims approved/done.  
28. **MUST NOT** store secrets, PATs, or toy credentials in this file.

### 2.8 Actor / role / subject / approver (consider)

29. Every software-development project **MUST** consider an **actor / role / subject / approver** requirement — **even if there is no dest approver**.  
30. **MUST** either publish Active `requirement-actor-role-subject-approver` (product stem allowed) that prints the five-column table (Submitter immediately before Approver), **or** record in this residual: **considered — no dest approver and no approval subject**.  
31. **MUST NOT** skip the consider. **MUST NOT** invent an approver so the table looks complete.  
32. A dest-specific actor table **MAY** exist when dest review is Implemented. That file does **not** replace this consider.

### 2.9 Dest fence conditions (review and convert)

33. Every software-development project **MUST review** whether any dest fencing conditions exist.  
34. Each dest **Fence** row **MUST** be an independent Active requirement (product stem allowed). Dest fence tables **MUST** still print the closed catalog and **point** at those REQs.  
35. Dest **MUST NOT** fence rows stay on dest tables only — they are **not** independent fence requirements.  
36. If none: record in this residual **considered — no dest fence conditions**.  
37. **MUST NOT** skip the review. **MUST NOT** invent a dest fence so the set looks complete.  
38. When dest has **any** dest **Fence**, the product **MUST** ship Type 0 **`fence-test`** (**`LM-FENCE-CONDITION-REQUIREMENT`** FC-M6) as a **test-purpose** verb: **unit test** of dest fence functions against a JSON **file location** in a **local test folder**. **MUST NOT** require `sudo` to run. The only allowed in-tool elev is wrapping **chmod** / **chown** of that folder (check before sudo). **MUST NOT** sudo otherwise. **MUST NOT** queue, dest-write, `setup`, or `approve`. Dest review / queue / host install **MUST NOT** count as that tester. Help **MUST** list test-purpose verbs **apart** from **operational** verbs (convert, submit, setup, dest review). Per-row testers **MAY** also exist and are also test-purpose. Privilege Type 0 does **not** mean “unit test.”

### 2.10 Coding-style related requirement (MUST have)

39. Every software-development project **MUST** have an Active **coding-style related** requirement matching the primary language.  
40. **Intention:** without that REQ, agents bring portable learned lessons **raw** (from coding skills and law molds) and treat them as this product’s law. That REQ is the **specialize-in home** (adopt, point at a peer, or refuse).  
41. Typical basenames: `requirement-shell-script-coding` (POSIX `/bin/sh`), `requirement-python-coding-style`, `requirement-nodejs-coding-style`. A router-only `requirement-coding-style` is **not** enough without the language body.  
42. This class file **MUST point** at that REQ. **MUST NOT** keep the full coding-style body here. **MUST NOT** skip. Honest residual **none** is **not** valid.  
43. **MUST NOT** treat a coding skill or mold as product law because the coding-style REQ is missing.

### 2.1 Implementation Notes (this project) — fill when specializing

| Field | Value (this project — fill real non-secret facts) |
|-------|-----------------------------------------------------|
| **Project display name** | `{{APP_NAME}}` / collect from user → product README SSOT when used |
| **Project class** | software-development |
| **Class requirement basename** | `requirement-class-software-dev.md` |
| **Primary language(s)** | `{{PRIMARY_LANGUAGE}}` (e.g. posix-sh, python, go, …) |
| **Language role** | primary / secondary: `{{LANGUAGE_ROLES}}` |
| **Toolchain / compiler / interpreter** | `{{TOOLCHAIN}}` |
| **Toolchain version policy** | unconstrained \| min `{{MIN_VERSION}}` \| range \| pinned `{{PINNED_VERSIONS}}` |
| **Cross-compile in scope?** | yes / no — `{{CROSS_COMPILE_NOTES}}` |
| **Primary project/package tool** | `{{PACKAGE_TOOL}}` |
| **Lockfile policy** | required / recommended / not used — `{{LOCKFILE_POLICY}}` |
| **Test runner (if law)** | `{{TEST_RUNNER}}` or “see peer requirement …” |
| **Linter/formatter (if law)** | `{{LINTER}}` or “see peer requirement …” |
| **Primary runtime / OS family** | `{{RUNTIME_OS}}` |
| **Architectures supported** | `{{ARCH_SET}}` |
| **Topics owned here (residual)** | list short topics **not** covered by other Active REQs |
| **Topics pointed elsewhere** | table of topic → peer `requirement-*` key |
| **Git surface** | used / not used for product publish |
| **Workspace (host)** | ram-drive-first `/dev/shm/{{PROJECT_BASENAME}}` when present, else `{{PROJECTS_ROOT}}/{{PROJECT_BASENAME}}`. **MUST NOT** `/home/<login>/…` — **`PO-NON-EXPOSE-LOCAL-MACHINE`** |
| **Ship unit / install** | yes/no — detail in peer REQs when present |

**Residual ownership table (maintain when specializing):**

| Topic | Owner (this file \| peer requirement key) | Notes |
|-------|-------------------------------------------|--------|
| Project class membership | **this file** | Fixed |
| Primary language | **this file** until a language-architecture REQ owns it | Prefer single SSOT |
| Compiler/toolchain + version policy | **this file** (residual default) | Move if dedicated toolchain REQ is created |
| Package/build tool + lockfile | **this file** (residual default) | Move if packaging REQ owns it |
| Type 0 / online install / self-management | peer when present | Do not duplicate |
| Domain features / help / about | peer `requirement-domain-*` when present | Do not duplicate |
| Coding-style related REQ | peer **MUST** (`requirement-shell-script-coding` / `requirement-python-coding-style` / `requirement-nodejs-coding-style` / language body) | Specialize-in home for portable learned lessons; **MUST NOT** skip; residual **points** only |
| In-tool sudo | peer `requirement-shell-sudo-command` when the ship unit invokes sudo | Specialize **`LM-SHELL-SUDO-COMMAND`**; coding-style **points**; run **`CL-LEAST-PRIVILEGE`** · **`CL-SHELL-TTY-PRIVILEGE-TRAPS`** on that REQ; emit checklists N/A if this CLI does not write fragments; **MUST NOT** keep wrap bodies only on coding-style |
| Actor / role / subject / approver consider | peer `requirement-actor-role-subject-approver` **or** residual **considered — no dest approver** | MUST consider even if Approver is None |
| Dest fence conditions review | independent REQ per dest **Fence**, or residual **considered — no dest fence conditions**. Any dest Fence set → Type 0 **test-purpose** **`fence-test`** | MUST review; do not invent a dest fence |

## 3. Why This Requirement Exists (Direct CIAO Alignment)

- **CIAO Principle 2 – Intentional**: Class and stack choices are explicit, not assumed from folder names.  
- **CIAO Principle 5 – SSOT**: Residual stack facts have one home until specialized requirements take ownership.  
- **CIAO Principle 1 – Caution**: Version and toolchain policies are declared; agents do not invent compilers.  
- **CIAO Principle 21 / dual policies**: Portable core; filled Implementation Notes; no product brand hardcode in core.

## 4. Design Principles (CIAO / CIAO-Lite)

- **Caution**: Assume toolchain and package tools are missing until declared and verified.  
- **Intentional**: Residual collection is deliberate — not a dump of every possible tool.  
- **Anti-fragile**: Version policies and choice sets survive multi-env builds.  
- **Over-protect**: Protection rule prevents dual stack SSOTs and genesis pollution.

## 5. Protection Rule (Sacred)

**Future AI assistants, Grok, or maintainers MUST NOT**:

- Create this file (or any requirement) while the workspace is **genesis-template**.  
- Rename the specialized basename away from `requirement-class-software-dev.md` without an explicit class-model change.  
- Hard-code one product’s name/host/secret into core rules as universal law.  
- Record a **session Unix login**, **literal home**, or **username-dependent path** — compose **`PO-NON-EXPOSE-LOCAL-MACHINE`**.  
- Duplicate full peer requirement bodies into this residual section.  
- Leave Implementation Notes as hollow `TBD` / bare `{{…}}` when Status claims approved or done.  
- Claim unconstrained toolchain support without tests or explicit unconstrained policy.  
- Treat this file as server-maintenance allowlist law.  
- Skip the actor / role / subject / approver consider, or invent an approver so the table looks complete.  
- Skip dest-fence review, leave a dest **Fence** as only a table cell, invent a dest fence so the set looks complete, leave dest Fences without Type 0 **`fence-test`**, treat `sudo` / a sudoers fragment / the waiting folder as that tester, group testers with operational verbs in help, or `sudo` on a tester except wrapping chmod/chown of the local test folder.  
- Skip the coding-style related REQ, leave writing style only as residual “when present”, or treat coding skills/molds as product law (portable lessons would then arrive **raw**).

**Violating any of these is considered a critical regression.**

## 6. Acceptance criteria (when specialized)

| ID | Criterion |
|----|-----------|
| AC-1 | Active registered `requirement-class-software-dev.md` matches software-development class |
| AC-2 | Primary language + toolchain policy + package tool declared in Implementation Notes (complete when approved) |
| AC-3 | Residual ownership table honest: no silent dual SSOT with peer REQs |
| AC-4 | Core rules remain free of frozen product brand/host/secret hardcodes |
| AC-5 | No class file conflict with `requirement-class-server-maintenance` |
| AC-6 | Actor / role / subject / approver considered (Active catalog REQ or residual **None**) |
| AC-7 | Dest fence conditions reviewed (independent REQ per **Fence**, or residual **none**). Dest Fences ship Type 0 **test-purpose** **`fence-test`** (local test folder; help listed apart from operational) |
| AC-8 | Coding-style related REQ Active (language-matched); class residual **points**; Purpose of that REQ states the specialize-in intention |

## 7. Related requirements (specialized — peer keys only)

| Key pattern | Relationship |
|-------------|--------------|
| `requirement-domain-*` | Domain feature law (when present) — not residual stack dump |
| `requirement-shell-*` / language-prefixed peers | Type 0 or language-specific law when present |
| Coding-style related REQ | **MUST** — `requirement-shell-script-coding` / `requirement-python-coding-style` / `requirement-nodejs-coding-style` / language body |
| Other Active `requirement-*` | Specific owners; residual topics only stay here |

## 8. Status history

| Date | Status | Note |
|------|--------|------|
| {{YYYY-MM-DD}} | {{STATUS}} | Specialized from portable class-software-dev template |

---

**Last Updated**: 2026-09-02  
**Owner**: {{OWNER}}  
**Alignment (template layer only):** portable class law for software-development; dual policies; **`PO-NON-EXPOSE-LOCAL-MACHINE`**; project-class **eleven-class** model; residual stack SSOT pattern; **MUST** coding-style related REQ (specialize-in home); in-tool sudo residual **points** at specialized **`LM-SHELL-SUDO-COMMAND`** + **`CL-LEAST-PRIVILEGE`** / **`CL-SHELL-TTY-PRIVILEGE-TRAPS`**; dest Fences ship Type 0 **test-purpose** **`fence-test`** (local test folder; sudo wrap only chmod/chown of that folder). Specialized files must not re-export harness path inventories.
