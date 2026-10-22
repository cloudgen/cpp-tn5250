---
name: requirement-class-server-maintenance
id: LM-REQUIREMENT-CLASS-SERVER-MAINTENANCE
kind: law-mold
description: >
  Portable law mold. Cite as LM-REQUIREMENT-CLASS-SERVER-MAINTENANCE (path secondary).
---

**file**: template-requirement-class-server-maintenance.md  
**Status**: Active (Version 1.0.0 – Server-maintenance class law + residual host/OS/libc collection)  
**Project**: Any CIAO-Lite server-maintenance workspace (reusable template — **no project brand / no host hardcode as universal law**)  
**Philosophy**: CIAO **v2.10.2** / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered / Over-protect)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

# =============================================================================
# Template: requirement-class-server-maintenance
# Specialize to: docs/requirements/requirement-class-server-maintenance.md
# No-hardcode: use {{PLACEHOLDER}} only — never freeze product brand or one host path as universal law
# =============================================================================


## Design-time verification

| Gate | Artifact | Phase |
|------|----------|-------|
| Specialize → product suite or checklist | declare TP-IDs or checklist in specialized REQ | Design |
| RTM | `../tests/template-requirement-test-traceability.md` | Design |

When this mold has no executable TP family, mark **n/a** with reason in product `reviews/test-plan.md`.

## How to use this template (authoring only — do not paste this section into claimed-done project law)

1. Confirm project nature is **server-maintenance** (not genesis-template; not software-development).  
2. Copy/specialize to **`docs/requirements/requirement-class-server-maintenance.md`** only.  
3. Fill **Implementation Notes** with *this* environment’s real non-secret host facts (no-placeholder when Status is approved/done).  
4. Keep **core rules** portable: OS families, libc families, and package-manager **classes** as choice models — not one datacenter hostname as universal law.  
5. **Residual collection rule:** put here only host/platform facts **not already owned** by a more specific Active `requirement-*.md` (e.g. full command-whitelist registry lives in its own REQ). When a dedicated requirement later owns a topic, **move** detail there and leave a short pointer (own-or-point).  
6. Register the specialized file in `docs/requirements/index.md` (Area **`class`**).  
7. **Git-surface:** specialized requirement bodies must not list harness paths (`docs/templates/**`, skills, terminologies, …).  
8. **Do not** invent OS/libc facts — collect from the target host (`uname`, `/etc/os-release`, `ldd --version`, `getconf`, package manager probes) or leave an explicit “not yet collected” owner.

**Target basename (fixed):** `requirement-class-server-maintenance.md`  
**Genesis:** do **not** create this file (or any `requirement-*.md`) in genesis-template.  
**Not the software-dev residual template:** do **not** use language/compiler residual tables from `template-requirement-class-software-dev` as this class’s content.

---

# Requirement: class-server-maintenance

**Status:** {{STATUS}}  
**Area:** class  
**Key:** `requirement-class-server-maintenance`  
**Updated:** {{YYYY-MM-DD}}

## 1. Purpose

Declare this workspace as a **server-maintenance** project class and hold the **general residual collection** of **host / platform** facts that are **not yet (or not better) recorded** in more specific requirements: **OS type and family**, **C library (libc)** identity (**glibc** / **musl** / **uClibc** / other), related kernel and userspace constraints, package-manager class, and other environment defaults needed for safe maintenance control.

This file is **class law + residual host SSOT**, not a second copy of the full **command whitelist** registry, privilege-actor design when specialized separately, or software-development ship/git SSOTs.

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
| **Server-maintenance project** | `docs/terminologies/server-maintenance-project.md` | `product-law` | Class #3 |
| **Project class** | `docs/terminologies/project-class.md` | `product-law` | Eleven-class model (internal name) |
| **Project nature** | `docs/terminologies/project-nature.md` | `product-law` | Daily-life name for **project class** (alias stub) |
| **Command whitelist** | `docs/terminologies/command-whitelist.md` | `product-law` | Ops allowlist |

**SSOT types used:** `meta-catalog` · `policy` · `product-law`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Core Rules (Mandatory — portable)

### 2.0 Project class membership

1. **MUST** treat this workspace as **server-maintenance** (ops control plane), not genesis-template and not software-development.  
2. **MUST** use basename **`requirement-class-server-maintenance.md`** as the sole Active class-law file for this class.  
3. **MUST NOT** register an Active `requirement-class-software-dev.md` while class is server-maintenance.  
4. **MUST** retain portable harness knowledge; specialized ops knowledge lives in this and peer `requirement-*.md` files.  
5. **MUST** center specialized control on a **command whitelist** with **deny-by-default** (detail in peer allowlist requirement when present).  
6. **MUST NOT** require software-development-only SSOTs for claimed completeness of this class (README identity triad, Stars, ship unit, online-install channel, precommit READY, companion digest as class requirements).  
7. **MUST** keep git surface **optional**.  
8. **MUST NOT** invent hollow product docs solely to look specialized.

### 2.1 Residual collection principle (SSOT hygiene)

9. **MUST** treat this file as the **default home** for host/platform facts **not owned** by another Active requirement.  
10. **MUST NOT** duplicate the full allowlist registry or privilege matrix when a peer requirement owns them — **point** to that key.  
11. When a new specialized requirement **takes ownership** of a residual topic, **MUST** update this file in the **same change**: shrink residual entry and point to the new owner.  
12. **MUST NOT** leave contradictory host facts across this file and peer requirements.

### 2.2 Operating system type and family

13. **MUST** declare the **primary OS type** as a closed choice (examples of *classes*, not hard-coded product law): Linux, BSD, Windows Server, other-POSIX, multi-OS fleet.  
14. **MUST** declare the **OS family / distribution class** when applicable (e.g. Debian-family, RHEL-family, Alpine-family, immutable/OSTree-class, generic Linux) — without freezing one org’s hostname as universal law.  
15. **SHOULD** declare version policy for the OS release line as: unconstrained / minimum / range / pinned set (pins live in Implementation Notes).  
16. **MUST** state whether maintenance targets are: single host, homogeneous fleet, or heterogeneous fleet (choice set).  
17. **MUST NOT** invent distro or release strings — collect from host inventory (`/etc/os-release`, equivalent) or mark not-yet-collected.

### 2.3 C library (libc) and ABI environment

18. **MUST** declare the **primary libc family** for the maintenance target as one of:  
    - **glibc** (GNU C Library),  
    - **musl**,  
    - **uClibc** / **uClibc-ng**,  
    - **other** (name the family in Implementation Notes),  
    - **mixed fleet** (document per-class matrix).  
19. **MUST** treat libc identity as **maintenance-relevant law** (package formats, static vs dynamic linking expectations, available tooling) — not optional trivia.  
20. **SHOULD** declare how libc was determined (probe method class: `ldd`, package query, vendor docs) without hard-coding absolute host paths as the only allowed method.  
21. **MUST** state version policy for libc when it constrains tools: unconstrained / minimum / range / pinned (pins in Implementation Notes).  
22. **MUST NOT** claim “any libc” without explicit unconstrained policy and test/ops evidence.  
23. **SHOULD** note related userspace constraints when residual: dynamic linker class, NSS, locale/encoding assumptions, read-only root, container-vs-bare-metal.

### 2.4 Kernel, init, and package manager (residual)

24. **SHOULD** declare **kernel family** (Linux / other) and whether a minimum kernel version is law.  
25. **SHOULD** declare **init / service manager class** when residual (systemd / OpenRC / sysv / other / not applicable).  
26. **MUST** declare the **primary package manager class** used for host maintenance when residual (apt-family, dnf/yum-family, apk, zypper, ports, chocolatey/winget-class, image-rebuild-only, none).  
27. **MUST NOT** put private registry passwords or package-signing secrets in this file — only tool/registry **names** and env **variable names**.

### 2.5 Architecture, privilege, and control-plane residual

28. **MUST** declare CPU/arch support as a choice set when residual (`amd64`/`arm64`/…; multi-arch fleet).  
29. **SHOULD** declare whether maintenance control runs primarily as: root-required, limited sudo, dedicated system-user, invoker — when not fully owned by a privilege requirement.  
30. **MUST** keep **command whitelist** deny-by-default as class posture; full entry registry belongs in the allowlist peer requirement when present.  
31. **MUST NOT** treat unrestricted interactive shell as the default control plane.

### 2.6 No-hardcode / dual policy (class file)

32. **MUST NOT** hard-code a single product brand, personal owner, or one production FQDN as universal core law.  
33. **MUST** put live project display name, concrete OS release strings, libc versions, and host inventory identifiers in **Implementation Notes** after collection — complete when Status claims approved/done (or explicit “not yet collected” with owner).  
34. **MUST NOT** store secrets, tokens, or toy credentials in this file.

### 2.1 Implementation Notes (this project) — fill when specializing

| Field | Value (this project / environment — fill real non-secret facts) |
|-------|------------------------------------------------------------------|
| **Project display name** | `{{PROJECT_DISPLAY_NAME}}` |
| **Project class** | server-maintenance |
| **Class requirement basename** | `requirement-class-server-maintenance.md` |
| **Primary control object** | command whitelist (deny-by-default) |
| **OS type** | `{{OS_TYPE}}` (e.g. Linux) |
| **OS family / distro class** | `{{OS_FAMILY}}` (e.g. Debian-family, Alpine-family, RHEL-family) |
| **OS release / version policy** | unconstrained \| min \| range \| pinned — `{{OS_VERSION_POLICY}}` / `{{OS_RELEASE}}` |
| **Target scope** | single host \| homogeneous fleet \| heterogeneous fleet |
| **Primary libc family** | glibc \| musl \| uClibc/uClibc-ng \| other \| mixed — `{{LIBC_FAMILY}}` |
| **libc version / policy** | `{{LIBC_VERSION_OR_POLICY}}` |
| **How libc was determined** | `{{LIBC_PROBE_METHOD}}` |
| **Kernel family / min version** | `{{KERNEL_NOTES}}` |
| **Init / service manager class** | `{{INIT_CLASS}}` |
| **Package manager class** | `{{PKG_MANAGER_CLASS}}` |
| **CPU architectures** | `{{ARCH_SET}}` |
| **Privilege posture (residual)** | `{{PRIVILEGE_POSTURE}}` or “see peer requirement …” |
| **Git surface** | not required by class / optional if used |
| **Topics owned here (residual)** | short list not covered by other Active REQs |
| **Topics pointed elsewhere** | table of topic → peer `requirement-*` key |

**Residual ownership table (maintain when specializing):**

| Topic | Owner (this file \| peer requirement key) | Notes |
|-------|-------------------------------------------|--------|
| Project class membership | **this file** | Fixed |
| OS type / family / release policy | **this file** (residual default) | Move if dedicated host-baseline REQ owns it |
| libc family (glibc / musl / uClibc / …) | **this file** (residual default) | Maintenance-relevant ABI law |
| Kernel / init / package manager class | **this file** (residual default) | Until specialized |
| Command whitelist registry | peer when present (e.g. command-whitelist REQ) | Point only — do not duplicate entries |
| Privilege actors / system-user design | peer when present | Point only |
| Software-dev language/compiler/package tools | **N/A** | Wrong class — do not store here |

## 3. Why This Requirement Exists (Direct CIAO Alignment)

- **CIAO Principle 2 – Intentional**: Class and host platform choices are explicit, not assumed from folder names.  
- **CIAO Principle 5 – SSOT**: Residual OS/libc facts have one home until specialized requirements take ownership.  
- **CIAO Principle 1 – Caution**: Agents must not invent distro/libc; unknown is fail-closed or collect-first.  
- **CIAO Principle 8 – Least privilege**: Host facts inform who may run which allowlisted ops.  
- **CIAO Principle 21 / dual policies**: Portable core; filled Implementation Notes; no brand/host secret hardcode in core.

## 4. Design Principles (CIAO / CIAO-Lite)

- **Caution**: Assume host probes may fail; do not invent glibc vs musl.  
- **Intentional**: Residual collection is deliberate — OS/libc matter for safe maintenance.  
- **Anti-fragile**: Choice sets and version policies survive multi-host fleets.  
- **Over-protect**: Protection rule prevents dual host SSOTs, open shell, and genesis pollution.

## 5. Protection Rule (Sacred)

**Future AI assistants, Grok, or maintainers MUST NOT**:

- Create this file (or any requirement) while the workspace is **genesis-template**.  
- Rename the specialized basename away from `requirement-class-server-maintenance.md` without an explicit class-model change.  
- Hard-code one product brand, one production FQDN, or secrets into core rules as universal law.  
- Invent OS type, distro release, or libc family without probe evidence or user-provided fact.  
- Duplicate the full command-whitelist registry into this residual section.  
- Leave Implementation Notes as hollow `TBD` / bare `{{…}}` when Status claims approved or done (use explicit not-yet-collected + owner instead).  
- Apply software-development residual topics (primary language, app compilers, PyPI/npm as class law) as this class’s residual content.  
- Treat unrestricted interactive shell as the default allowed control plane.

**Violating any of these is considered a critical regression.**

## 6. Acceptance criteria (when specialized)

| ID | Criterion |
|----|-----------|
| AC-1 | Active registered `requirement-class-server-maintenance.md` matches server-maintenance class |
| AC-2 | OS type/family and primary libc family declared or explicitly not-yet-collected with owner |
| AC-3 | Residual ownership table honest: no silent dual SSOT with peer REQs |
| AC-4 | Core rules free of frozen product brand / host secret hardcodes |
| AC-5 | No Active conflict with `requirement-class-software-dev` |
| AC-6 | Command-whitelist deny-by-default posture stated; registry detail pointed or owned correctly |

## 7. Related requirements (specialized — peer keys only)

| Key pattern | Relationship |
|-------------|--------------|
| Allowlist / command-whitelist peer | Entry registry + deny-by-default implementation law |
| Privilege / system-user peers when present | Actor models — not OS residual dump |
| Other Active `requirement-*` | Specific owners; residual topics only stay here |

## 8. Status history

| Date | Status | Note |
|------|--------|------|
| {{YYYY-MM-DD}} | {{STATUS}} | Specialized from portable class-server-maintenance template |

---

**Last Updated**: 2026-07-17  
**Owner**: {{OWNER}}  
**Alignment (template layer only):** portable class law for server-maintenance; residual OS/libc/host SSOT; dual policies; project-class **eleven-class** model. Specialized files must not re-export harness path inventories.
