---
name: least-privilege-user
id: LM-LEAST-PRIVILEGE-USER
kind: law-mold
description: >
  Portable least-privilege user mold (Type 0/1/2, internal sudo, system user).
  Type 1 allowlisted OS-tool elev requires Tables A/B/C via LM-THREE-LAYER-PRIVILEGE-MODEL.
  Cite as LM-LEAST-PRIVILEGE-USER (path secondary).
---

**file**: template-least-privilege-user.md  
**Status**: Active (Version 2.12.0 – dest `{{REVIEW_VERB}}` reviews old product-binary hook; points at LM-LOGIN)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered / Over-protect)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

# =============================================================================
# CIAO DEFENSIVE TEMPLATE - Least Privilege User Policy
# =============================================================================
#
# This is a reusable template for defining least-privilege execution policies
# in defensive CLI, installer, or platform management tools.
# It was converted from an obsolete project-specific requirement to serve
# as a generalized, placeholder-driven template for future CIAO-Lite projects.
#
# All specific values use {{PLACEHOLDER}} syntax. No project names, usernames,
# paths, or endpoints are hardcoded.
#
# Primary audience: General (policy level) — not tied to one runtime/language.
# Therefore the generic `template-` prefix is used per filename discipline.
# =============================================================================

## 1. Purpose

This template establishes the mandatory least-privilege user execution model for tools that must perform a mix of unprivileged and privileged operations. It protects both the end user (who should not need to run the entire tool as root) and any dedicated system accounts used for persistent services or data ownership.

The policy distinguishes command categories by required privilege level and mandates an **internal sudo escalation** pattern for normal users.

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
| **System user** | `docs/terminologies/system-user.md` | `identity-runtime` | Dedicated least-privilege account |
| **Three-layer privilege** | `docs/terminologies/three-layer-privilege.md` | `product-law` | Type 0/1/2 model |
| **Least privilege** | `docs/terminologies/least-privilege.md` | `policy` | Principle + harness local-default / egress envelope |
| **LLM escape** | `docs/terminologies/llm-escape.md` | `policy` | Envelope breach; activity IDs `E-*` (avoid) |
| **LLM pain point** | `docs/terminologies/llm-pain-point.md` | `mention-only` | `PP-A-08` / `PP-A-16` map to privilege and net escape |

**SSOT types used:** `identity-runtime` · `meta-catalog` · `mention-only` · `policy` · `product-law`

**Policies (normative bodies):** `docs/policies/policy-least-privilege.md` (**agent + product least privilege; avoid LLM escape**) · `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md` · `docs/policies/policy-harness-id-notation.md` (cite `PP-*`/`E-*` when reporting)

**Checklists (gates):** **`CL-LEAST-PRIVILEGE`** · **`CL-LLM-ESCAPE`** (agent/Review/Security); product specialize may bind TP families separately

## 2. Core Rules / Requirements (Mandatory)

### 2.1 Command Type Classification (CIAO Principle 9)

All commands exposed by the tool **MUST** be classified into **exactly one** of three types (**CIAO Principle 9 — Three Types of Commands**). Principle **10** (this template’s mechanics) fills in dedicated-user / sudoers details.

| Type | Privilege level | Execution context | Typical responsibilities |
|------|-----------------|-------------------|--------------------------|
| **Type 0** | Any user — **no** special privilege | Direct execution as the **invoking user** | Safe self-management and read-only work: `help`, `version`, `about`, `status`, user-scoped `self-update` / `self-uninstall`, read-only queries |
| **Type 1** | **Elevated** (root / sudo) for **host** preparation | Normal user **may invoke**; tool performs **internal escalation** only for privileged sub-steps | System prep: packages, Docker engine, create system user, host bootstrap |
| **Type 2** | **Dedicated least-privilege system user** | **Must** run **as the dedicated app/system user**; context-switch if invoker is root or another user | App install/configure, service/container lifecycle, data ops under app ownership |

**Mandatory (Principle 9):** classify every command; prefer lowest safe type; Type 1 uses internal escalation; Type 2 uses context switch to `{{SYSTEM_USER}}` / `{{APP_USER}}`; **do not collapse types**; document the map in help/architecture.

**Must not confuse:** Type 2 is **not** “always root.” Root is for controlled Type 1 sub-steps / bootstrap — not routine app ops.

### 2.2 Internal Sudo Escalation Pattern (Sacred for Type 1)
- The tool **MUST** implement internal sudo escalation for Type 1 commands when the invoking user is not root.
- Preferred implementation: re-execute the specific privileged sub-command (or the whole command) via `sudo "$0" "$@"` or targeted `sudo` calls for individual operations.
- The tool **MUST NOT**:
  - Require the user to run the entire CLI as root for routine Type 1 operations.
  - Cache or log the sudo password.
  - Fall back to "please run as root" instructions without attempting internal escalation first.
- Sudo configuration on the target system is the responsibility of the administrator (e.g., passwordless sudo for the dedicated {{SYSTEM_USER}} or appropriate group).

### 2.2a Elev allowlist tables when Type 1 uses allowlisted OS tools / sudoers

When Type 1 uses **sudoers** (`print-sudoers` / F6) **and/or** in-tool password `sudo` (mix model):

1. Specialized product law **MUST** publish elev **Tables A/B/C** per **`LM-THREE-LAYER-PRIVILEGE-MODEL`** §2.2a.  
2. Prefer elev-table SSOT on specialized three-layer privilege REQ; this mold **MUST NOT** invent a second conflicting table.  
3. **Table A** = sudoers fragment lines only — **not** a live-command whitelist. **No user denylist ⇒ no restrict** on live tools. **Table C** (optional) = `sudo useradd` in the script, not in the fragment.  
4. Broaden **Table A** only via table update + security review + fragment reinstall (`E-PRIV-04`).  
5. Fragment Cmnds / `print-sudoers` **MUST** be ⊆ Table A. **MUST NOT** emit `useradd`.  
6. Dest / F6 live under `/etc/{{username}}/` (F6: `/etc/{{LPU_USER}}/sudoers`). **MUST NOT** write `/etc/passwd` or `/etc/sudoers.d`. There is **no** blanket “do not write `/etc`”. F3 prefers `/etc/{{LPU_USER}}`.  
7. When the product installs a login-interactive-review-hook: Type 1 `setup` **MUST** auto-queue `kind=login-hook-elev` **iff** sibling dest CLI + approver + inbound exist (**`LM-THREE-LAYER-PRIVILEGE-MODEL`** §2.3.3e · **`LM-SUDOER-JSON-FILE`** §3.0 / §3.0a / §3.0b / §3.4c). **MUST** write inbound. **MUST NOT** call dest Type 0 `add-sudoer-request`. **MUST NOT** `chown` dest inbound (dest `{{APPROVER}}` takes ownership). Dest Type 0 self-scope **MUST NOT** apply to `setup` (blockage, not dest approval). Missing sibling → skip. **MUST NOT** treat Type 0 `{{SUBMIT_SUDOER_CMD}}` as that path. **Submit vs setup door:** submit = current login, Type 0, no sudo; setup = host admin, Type 1, password `sudo` / already root. Login-hook review **MUST** `chown` to `{{LPU_USER}}` before any product-queue move. Dest **approval fencing conditions** are a closed list (peer **`LM-FILE-BASED-JSON-APPROVAL`** §2.3a). Dest inbound fence is **incorrect JSON format**. Dest **MUST NOT** add extra fences (file-ownership, who submitted, dest Type 0 self-scope, JSON username ≠ dest LPU, filename subject token ≠ JSON username field). Specialized law **MUST** print that table.  
8. **Dest split:** after sibling approve, hook dest is `/etc/sudoers.d/{{APP_NAME}}-{{LPU_USER}}`. Type 0 switch dest is `/etc/sudoers.d/{{APP_NAME}}-{{TARGET_USER}}`. F6 is `/etc/{{LPU_USER}}/sudoers`. Setup/account create **MUST NOT** be described as writing the invoker’s `sudoers.d` file.  
9. Type 2 default dest I/O: if invoker is not `{{LPU_USER}}`, context-switch (`sudo -n -u {{LPU_USER}} {{GLOBAL_BIN}}/{{APP_NAME}}`) or fail closed. Specify path **MUST NOT** switch. That grant is F6 or the **invoker** sibling dest — **not** the hook dest.
10. When the product installs a login-interactive-review-hook: Type 1 `setup` **MUST** create the [login-hook-symlink](../../terminologies/login-hook-symlink.md) `{{GLOBAL_BIN}}/{{APP_NAME}}-hook` when the global product binary exists and that name is absent. **MUST NOT** overwrite an existing hook name. Test-mode **MUST NOT** write the live global name. F7 **MUST NOT** unlink it. Type 1 `setup` **and** dest `{{REVIEW_VERB}}` **MUST** review `{{APPROVER}}` rc: old `{{GLOBAL_BIN}}/{{APP_NAME}} {{REVIEW_VERB}}` **MUST** become `{{APP_NAME}}-hook`; already-new **MUST NOT** rewrite (**`LM-LOGIN-INTERACTIVE-REVIEW-HOOK`** §3.9). Specialize **`LM-LOGIN-INTERACTIVE-REVIEW-HOOK`** into an **independent** product REQ; this LPU mold **points**. Sibling CLIs reuse `/usr/local/bin/{{APP_NAME}}-hook`. Peer: **`LM-LOGIN-INTERACTIVE-REVIEW-HOOK`**.

**Dest approval fencing conditions (closed).** Dest `approve` / `reject` / review **MUST** fail closed on inbound **only** for **incorrect JSON format**. Dest **MUST NOT** add extra fencing conditions. Peer: **`LM-FILE-BASED-JSON-APPROVAL`** §2.3a.

| Condition | Dest approve / reject / review |
|-----------|--------------------------------|
| **Incorrect JSON format** | **Fence** — fail closed. Independent REQ (specialize **`LM-FENCE-CONDITION-REQUIREMENT`**; dest table still prints) |
| File-ownership | **MUST NOT** fence — take ownership as dest LPU / `{{APPROVER}}` |
| Who submitted / dest Type 0 self-scope | **MUST NOT** fence |
| JSON username field ≠ dest LPU | **MUST NOT** fence |
| Filename subject token ≠ JSON username field | **MUST NOT** fence — user SSOT is the JSON field |

N/A when Type 1 is only whole-tool re-exec via `sudo "$0"` with **no** OS-tool allowlist and **no** product sudoers fragment — still document the Type 1 map.

### 2.3 Dedicated System User for Services
When the tool manages long-running services or persistent data:
- A dedicated, non-login system user ({{SYSTEM_USER}}) **SHOULD** be created during installation / first-run setup.
- All persistent files, volumes, sockets, and service processes **SHOULD** be owned by this dedicated user.
- The CLI itself (when run by a normal human) interacts with these resources via controlled escalation (Type 1) rather than by running as the system user directly.

### 2.4 Protection of the Dedicated System Account
- The dedicated {{SYSTEM_USER}} account **MUST** be locked (no password login, no shell) unless explicitly required for debugging under controlled conditions.
- All management of the account and its resources must go through the tool's Type 1 paths or explicit admin procedures.

### 2.5 Why This Pattern Exists (Direct CIAO Alignment)
- **CIAO Principle 9 – Three Types of Commands** (https://github.com/cloudgen/ciao): Architecture map of *who runs what* (Type 0 / 1 / 2).  
- **CIAO Principle 10 – Least-Privilege User** (https://github.com/cloudgen/ciao): Dedicated non-root user, restricted ownership, restricted sudoers, setup vs routine ops.  
- **CIAO Principle 1 – Caution**: Assume the invoking user is a normal account; do not assume root.  
- **CIAO Principle 3 – Anti-fragile**: Internal escalation and context switch survive interactive and automated use.  
- **CIAO Principle 4 / CIAO-Lite O · Principle 20**: Privilege map and internal-sudo patterns are Protection Zone material.

## 3. Design Principles (CIAO / CIAO-Lite)

- **Caution (CIAO Principle 1)**: Never assume the CLI starts with root privileges. Always provide a safe path for normal users via internal escalation.
- **Intentional (CIAO Principle 2)**: Command types (Type 0/1/2) are explicitly documented and enforced so that future maintainers and AI assistants cannot accidentally weaken the privilege model.
- **Anti-fragile (CIAO Principle 3)**: The policy works across interactive terminals, `curl | sh` installers, CI/CD pipelines, and containers without requiring constant root.
- **Over-protect (CIAO Principle 4 / CIAO-Lite O · Principle 20)**: The internal sudo pattern and dedicated system user rules are protected zones; they must not be simplified or removed for "convenience."

## Under command line for normal user only

When the ship unit detects a **command line for normal user only** (Termux, Git Bash, or the same class — term [`command-line-for-normal-user-only.md`](../../terminologies/command-line-for-normal-user-only.md)):

| MUST | MUST NOT |
|------|----------|
| Keep **normal user privilege** (Type 0) only | Implement or enable **admin privilege** (Type 1) or **dedicated system user privilege** (Type 2) |
| Document Type 1 **unused** and Type 2 **unused** | In-tool `sudo`; wrap `apt` / `dnf` / `yum`; write `/etc` dests; `useradd` / dedicated LPU; Type 2 `sudo -u` switch |
| Termux: named `pkg` as this login remains Type 0 (**`LM-SHELL-TERMUX-ISH`**) | Recommend `sudo curl \| sh` as the install path |
| Git Bash: same privilege ceiling | Invoke Termux `pkg` because Git Bash was detected |

Detect (typical): Termux — `PREFIX` contains `com.termux`; `TERMUX_VERSION` set; `/data/data/com.termux/files/usr` exists. Git Bash — `MSYSTEM` is `MINGW*` / `MSYS*` / `UCRT*` / `CLANG*`; `uname -s` is `MINGW*` / `MSYS*`. Windows cmd — `OS` is `Windows_NT` or `ComSpec`/`COMSPEC` names `cmd.exe` (after excluding Git Bash, Cygwin, WSL).

**This mold:** Type 2 LPU is unused on that class; do not `useradd` a dedicated account.

## 4. Protection Rule (Sacred)

**Future AI assistants, Grok, or maintainers MUST NOT**:

- Remove or weaken the Type 0 / Type 1 / Type 2 classification.
- Replace the internal sudo escalation pattern with instructions that tell the user to "run the whole command as root".
- Redefine **Type 2** as “root-only” (violates CIAO Principle 9 — Type 2 is the dedicated system user).
- Hardcode concrete usernames, project-specific paths, or service names inside the generated content (use `{{SYSTEM_USER}}` / `{{PLACEHOLDER}}` instead).
- Assume the tool always runs as root or always runs as a normal user — both paths must be supported.
- Collapse all operations into a single privilege class for “simplicity.”
- Delete or bypass the "Why This Requirement Exists (Direct CIAO Alignment)" subsection.
- Convert this template back into a project-specific requirement without re-applying the full upstream analysis and placeholder discipline.
- Violate harness **[`policy-least-privilege.md`](../../policies/policy-least-privilege.md)** while authoring or implementing: root-by-convenience (`PP-A-08` / `E-PRIV-*`), unapproved external egress (`PP-A-16` / `E-NET-*`), or skip **`CL-LEAST-PRIVILEGE`** / **`CL-LLM-ESCAPE`** when privilege or escape risk is in scope.
- Claim allowlisted Type 1 / sudoers elev complete without elev **Tables A/B/C** (or with hollow “uses sudo”) — residual power for agent script edits (**E-PRIV-04**).
- Widen elev in ship unit without updating Table A + security review + dest under `/etc/{{username}}/`.  
- Write `/etc/passwd` or `/etc/sudoers.d`, or invent a blanket “do not write `/etc`” that blocks `/etc/{{username}}/`.  
- Treat Type 1 `setup` as installing `/etc/sudoers.d/{{APP_NAME}}-{{TARGET_USER}}`, or Type 2 default-ops as using `/etc/sudoers.d/{{APP_NAME}}-{{LPU_USER}}` (hook only).  
- Add a dest inbound fence that is not **incorrect JSON format** (who submitted, dest Type 0 self-scope, JSON username ≠ dest LPU).  
- Strip the **Under command line for normal user only** section, or `useradd` an LPU on Termux / Git Bash.

Violating any of the above is considered a **critical regression** against the project's defensive documentation layer and **LLM escape / least-privilege policy**.


## Design-time verification

| Gate | Artifact | Phase |
|------|----------|-------|
| Specialize → product suite or checklist | declare TP-IDs or checklist in specialized REQ | Design |
| RTM | `../tests/template-requirement-test-traceability.md` | Design |

When this mold has no executable TP family, mark **n/a** with reason in product `reviews/test-plan.md`.

**Last Updated**: 2026-09-08  
**Owner**: Defensive Policy Layer (Generalized Template)  
**Version history:**  
- **2.12.0** (2026-09-08): Dest `{{REVIEW_VERB}}` reviews `{{APPROVER}}` rc; old product-binary hook → `{{APP_NAME}}-hook`; **points** at **`LM-LOGIN-INTERACTIVE-REVIEW-HOOK`** §3.9.  
- **2.11.0** (2026-09-05): Named section Under command line for normal user only.  
- **2.10.0** (2026-09-03): Setup creates [login-hook-symlink](../../terminologies/login-hook-symlink.md) when missing; F7 does not unlink.  
- **2.9.0** (2026-08-19): Dest Fence row points at independent REQ (`LM-FENCE-CONDITION-REQUIREMENT`).  
- **2.8.0** (2026-08-19): Dest MUST NOT fence on filename subject token; user SSOT is the JSON username field.  
- **2.7.0** (2026-08-18): Dest approval fencing conditions closed; dest inbound fence is incorrect JSON format.  
- **2.6.0** (2026-08-18): Setup MUST NOT `chown` dest inbound; login-hook review `chown`s to `{{LPU_USER}}` before queue move.  
- **2.5.0** (2026-08-18): Type 2 default-ops switch; hook dest `{{APP_NAME}}-{{LPU_USER}}` ≠ switch dest `{{APP_NAME}}-{{TARGET_USER}}`.  
- **2.4.0** (2026-08-18): Submit-vs-setup door; dest Type 0 self-scope MUST NOT apply to setup.  
- **2.3.0** (2026-08-18): Setup auto-queues `login-hook-elev` when a login hook + sibling dest exist.  
- **2.2.0** (2026-08-14): Dest `/etc/{{username}}/`; F6 `/etc/{{LPU_USER}}/sudoers`; never write `/etc/passwd` or `/etc/sudoers.d`.  
- **2.1.0** (2026-08-07): §2.2a elev Tables A/B/C when allowlisted OS-tool / sudoers Type 1; anti jailbreak protection rules.  
- **2.0.0**: CIAO v2.10.2 Principles 9 + 10 Type map. 
**Version history:**  
- **2.0.0** (2026-07-14): CIAO v2.10.2 — Principle 9 Type map; Principle 10 least-privilege; Type 2 = dedicated system user (not root-only).  
- **1.0.0**: Initial generalized conversion.  

**Alignment**: [cloudgen/ciao](https://github.com/cloudgen/ciao) v2.10.2 Principles 9–10; **`LM-THREE-LAYER-PRIVILEGE-MODEL`**; **`LM-REQUIREMENT-SYSTEM-USER`**; harness **`policy-least-privilege`**; terms `least-privilege` · `llm-escape`; gates **`CL-LEAST-PRIVILEGE`** · **`CL-LLM-ESCAPE`**; `template-cli-interface.md` when present.

---

**How to use this template**:
1. Keep under `docs/templates/requirements/`; specialize into a project `requirement-*-least-privilege-user.md` when needed.  
2. Classify every public command as Type 0 / 1 / 2 (Principle 9).  
3. Fill `{{SYSTEM_USER}}` / paths only in the specialized requirement Implementation Notes.  
4. Register specialized requirements in `docs/requirements/index.md` (requirement rows only).  
5. Obey harness **`policy-least-privilege`** (local-default agents; no unapproved egress) while specializing/implementing; run **`CL-LEAST-PRIVILEGE`** when Review/Security gates privilege.
