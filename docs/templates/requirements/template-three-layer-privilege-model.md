---
name: three-layer-privilege-model
id: LM-THREE-LAYER-PRIVILEGE-MODEL
kind: law-mold
description: >
  Portable law mold for three-layer privilege (Type 0/1/2), sudoers fragment rules,
  and mandatory elev Tables A/B/C (sudoers vs in-tool `sudo <tool>`) against agent jailbreak.
  Cite as LM-THREE-LAYER-PRIVILEGE-MODEL (path secondary).
---

**file**: template-three-layer-privilege-model.md  
**Status**: Active (Version 2.22.0 – shell-sudoer sample home)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered / Over-protect)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

# =============================================================================
# CIAO DEFENSIVE TEMPLATE - Three-Layer Privilege Model + Sudoers Fragments
# =============================================================================
#
# Portable law mold. Specialize into:
#   docs/requirements/requirement-three-layer-privilege-model.md
# Use {{PLACEHOLDER}} only — no project host hardcodes in this mold.
# =============================================================================

# Template: Three-Layer Privilege Model (and sudoers fragment files)

## 1. Purpose

This template is the portable **law mold** for:

1. The **Three-Layer Privilege Model** (Type 0 / Type 1 / Type 2) as product architecture law.  
2. **Working with sudoers fragment files**: emit draft, content constraints, Type 1 dest under `/etc/{{username}}/`, runtime allowlisted elevation, and fail-closed behavior. **MUST NOT** write `/etc/passwd` or `/etc/sudoers.d`. There is **no** blanket “do not write `/etc`”.  
3. **Sudoers fragment contents** (what may appear in the dest file) vs **live commands** the ship unit may run. **Default:** no live-command whitelist. **No denylist ⇒ no invented restrict.**

Specialize into a project `requirement-three-layer-privilege-model.md` (or equivalent key). Domain verbs that *use* elevation stay in `requirement-domain-*` but **must not** invent a second conflicting elev table (single SSOT). Agent **procedure** for security-gated create is skill **`SK-CREATE-SUDOERS-FILE`** (not product-source authority).

**POSIX shell sudoer CLI + sample emit/wrap:** specialize **`LM-SHELL-SUDOER`** (print-sudoers, generate JSON, `util_sudo`). **This-login config deposit** (`backup-config` / `sync-config`) specializes **`LM-SHELL-CONFIG-BACKUP`** and **MUST** depend on **`LM-SHELL-SUDOER`**. **MUST NOT** copy those sample functions into this Type 0/1/2 mold.

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
| **Three-layer privilege** | `docs/terminologies/three-layer-privilege.md` | `product-law` | Primary Type 0/1/2 term (people-facing **who-may-run-what**: **normal user privilege** / **admin privilege** / **dedicated system user privilege**) |
| **Type 0** | `docs/terminologies/type-0.md` | `product-law` | One layer — **normal user privilege** (workshop Type 0) |
| **Type 1** | `docs/terminologies/type-1.md` | `product-law` | One layer — **admin privilege** (workshop Type 1). Dest approve is this layer |
| **Type 2** | `docs/terminologies/type-2.md` | `product-law` | One layer — **dedicated system user privilege** (workshop Type 2) |
| **Command line for normal user only** | `docs/terminologies/command-line-for-normal-user-only.md` | `product-law` | Termux / Git Bash / Windows cmd: Type 1/2 unused on detect |
| **Sudoers fragment** | `docs/terminologies/sudoers-fragment.md` | `product-law` | Draft + admin install allowlist file |
| **Ship unit** | `docs/terminologies/ship-unit.md` | `product-law` | Managed install binary |
| **System user** | `docs/terminologies/system-user.md` | `identity-runtime` | Type 2 user when used |
| **Least privilege** | `docs/terminologies/least-privilege.md` | `policy` | Principle; harness enforcement |
| **LLM escape** | `docs/terminologies/llm-escape.md` | `policy` | **E-PRIV-04** broad sudoers |

**SSOT types used:** `identity-runtime` · `meta-catalog` · `policy` · `product-law`

**Policies (normative bodies):** `docs/policies/policy-least-privilege.md` · `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

**Checklists:** **`CL-LEAST-PRIVILEGE`** · **`CL-LLM-ESCAPE`** · **`CL-CREATE-SUDOERS-SECURITY`** (pre-emit sudoers draft)  
**Skills (procedure, not product law):** **`SK-CREATE-SUDOERS-FILE`**

---

## 2. Core Rules / Requirements (Mandatory)

### 2.1 Layer map (specialize)

| Layer | Privilege | Typical actor | Typical responsibilities (fill per product) |
|-------|-----------|---------------|-----------------------------------------------|
| **Type 0** (**normal user privilege**) | Invoking user | End user / automation | Self-management, diagnostics, **unprivileged** domain work, **print/write draft** sudoers fragment |
| **Type 1** (**admin privilege**) | Elevated (password `sudo` / already-root / F6) | Any host admin, or LPU via Table A | **Bootstrap** (`setup`): outer or **in-tool** password `sudo`; Table C `sudo useradd`. **Day-to-day**: Table A F6 only |
| **Type 2** (**dedicated system user privilege**) | Dedicated least-privilege system user | `{{SYSTEM_USER}}` | Long-running app ownership — **or** document **Not used** |

**Mandatory:**

1. Classify every product command into exactly one layer (or document hybrid with an explicit elevated sub-step).  
2. Prefer the lowest safe layer.  
3. Type 1 **MAY** use in-tool password `sudo` (mix model). **MUST NOT** invent “ship unit MUST NOT invoke `sudo`” as default law. Routine Type 0 ops stay unprivileged.  
4. Do not collapse Type 0/1/2 for convenience (`PP-A-08` / `E-PRIV-*`).  
5. When the product **emits a sudoers fragment**, say what that fragment contains (Table A = those lines). Do **not** require a whitelist of every live command the script may exec. Do **not** invent a denylist the user did not publish.  
6. When the product has a Type 2 default dest owned by `{{LPU_USER}}`: unspecified verbs that use that dest **MUST** run as `{{LPU_USER}}`. If `id -un` is not `{{LPU_USER}}`, re-exec `sudo -n -u {{LPU_USER}} {{GLOBAL_BIN}}/{{APP_NAME}}` or fail closed (`{{LPU_REQUIRED_CODE}}`, typical `lpu_required`). A Type 0 specify path **MUST NOT** switch. The live grant for that re-exec is F6 **or** `/etc/sudoers.d/{{APP_NAME}}-{{TARGET_USER}}` (`type-2-switch`). It is **not** `/etc/sudoers.d/{{APP_NAME}}-{{LPU_USER}}` (`login-hook-elev` only).  
7. **Command line for normal user only** (Termux, Git Bash, Windows cmd, or the same class): on detect, Type 1 (**admin privilege**) and Type 2 (**dedicated system user privilege**) **MUST** be **unused**. **MUST NOT** implement or enable in-tool `sudo`, wrap `apt`/`dnf`/`yum`, write `/etc` dests, `useradd` / dedicated LPU, or Type 2 `sudo -u` switch. Termux named `pkg` as this login remains Type 0 (**`LM-SHELL-TERMUX-ISH`**). Git Bash and Windows cmd **MUST NOT** invoke `pkg`.

### 2.1a Command line for normal user only (detect → Type 1/2 unused)

Specialize detect (typical):

| Instance | Signals (any one) |
|----------|-------------------|
| **Termux** | `PREFIX` contains `com.termux`; `TERMUX_VERSION` set; `/data/data/com.termux/files/usr` exists |
| **Git Bash** | **Primary:** folder `/c/` or `/c` (default drive `/c/`). Secondary: `MSYSTEM` is `MINGW*` / `MSYS*` / `UCRT*` / `CLANG*`; `uname -s` is `MINGW*` / `MSYS*`. Exclude WSL. Scratch: [`git-bash-temp-folder.md`](../../terminologies/git-bash-temp-folder.md) |
| **Windows cmd** | `OS` is `Windows_NT`, or `ComSpec` / `COMSPEC` names `cmd.exe` — after excluding Git Bash, Cygwin, WSL |

On detect **MUST NOT:** recommend `sudo curl \| sh` as the install path; wrap Linux package managers; create a dedicated system user; add Type 1 `setup` / dest approve verbs.

On detect **MUST:** document Type 1 **Not used** and Type 2 **Not used** in the layer map.

### 2.2 Least-privilege rules (portable)

1. **MUST NOT** grant unrestricted shell, unrestricted package install, or filesystem-wide write via product sudoers.  
2. **MUST** put **only Table A** in sudoers / `print-sudoers`. Table C jobs (`sudo useradd`) run **in the ship unit**, not as sudoers Cmnds.  
3. **MUST NOT** open unapproved network egress as part of privilege design unless a separate approved requirement says so.  
4. Broadening elev later **MUST**: add/change **Table A** rows + security review Pass (**`CL-CREATE-SUDOERS-SECURITY`**) + admin fragment reinstall **before** ship unit uses the new elev (`E-PRIV-04` if skipped).  
5. Putting Table C tools **into sudoers**, or writing “MUST NOT invoke `sudo`” without user order, is a **defect**. Widening **Table A** still needs review + fragment reinstall.  
6. **print-sudoers** / installed fragment Cmnds **MUST** be ⊆ Table A (never wider than product law).

### 2.2a Sudoers tables vs live commands (default: no restrict)

**Default (normative):** **Elev is approval** (term `elev-is-approval`): password `sudo` or a root login **is** the authorization. Do **not** invent a second lock. Sensitive steps: TTY confirm or `--force`. The user did **not** order a whitelist of live commands. If they also did **not** publish a live-command denylist, agents **MUST NOT** invent restrict. The ship unit **MAY** invoke the OS tools Type 1 work needs (password `sudo` OK; `-n` not suggested).

**Table A** is **only** what a product **sudoers fragment** emits (if it emits one). It is **not** a closed catalog of every binary the CLI may run.

**Table B** is **only** what must **not** appear **in sudoers** — and **only** when the user/product named those rows. It is **not** a live-command blacklist unless the user said so.

**Table C** (optional notes) names jobs the **script** runs (`sudo useradd`, …). Those jobs **MUST NOT** be copied into sudoers. Listing them does **not** forbid other unlisted live commands.

Portable **column contract** when a fragment exists (this mold keeps `{{PLACEHOLDER}}`):

**Table A — Sudoers Cmnd set (fragment contents only — not a live-command whitelist)**

| ID | Job / sub-step | Binary (absolute) | Fixed args | Source path pattern | Dest path pattern | Invoker CLI | Run-as | NOPASSWD? | Sudoers line shape |
|----|----------------|-------------------|------------|---------------------|-------------------|-------------|--------|-----------|--------------------|
| ELEV-… | {{JOB}} | `/usr/bin/…` | … | `{{STAGE}}/*` or — | `{{ELEVATED_DEST_DIR}}/…` | `{{CMD}}` | root | yes/no | one-line Cmnd |

**Table B — Forbidden in sudoers (only if the product/user named a denylist)**

| ID | Forbidden | Why |
|----|-----------|-----|
| FORB-01 | `rm` / recursive delete via sudo on durable trees | Destroy elev not default |
| FORB-02 | Bare `/bin/sh` / `/bin/bash` as Cmnd | Residual shell / LLM escape |
| FORB-03 | `ALL=(ALL) ALL` / `NOPASSWD: ALL` | Broad admin |
| FORB-04 | Unbound package managers (unless separate package-elev law with its own Table A) | Wrong surface |
| FORB-05 | Write outside `{{ELEVATED_DEST_DIR}}` / documented stages | Bound dest |
| FORB-06 | Elevate non-managed ad-hoc binaries under `/tmp` | Install gate |

**Table C — Script jobs (not sudoers; not a closed live set)**

| Rule | Requirement |
|------|-------------|
| Default | No live-command whitelist. No denylist ⇒ no invented restrict |
| Script | **MAY** `sudo <tool>` (password; not `-n`) for Type 1 work |
| Sudoers | **MUST NOT** copy Table C tools into the fragment |
| print-sudoers | Emitted lines = Table A (the fragment) only |

**Single elev-table SSOT:** Exactly one Active product file owns Tables A/B/C (prefer this specialized three-layer REQ). Ops/domain peers **MUST** point here — no dual conflicting tables.

---

### 2.3 Working with sudoers fragment files (normative — portable)

This section is product **behavior law** when specialized. Procedure detail for agents lives in **`SK-CREATE-SUDOERS-FILE`**; specialized requirements **MUST** still state the obligations below so ship units and tests can cite them.

#### 2.3.1 Roles and artifacts

| Role | May | Must not |
|------|-----|----------|
| **End user / automation** | Run product print/emit command; run elevated ops **after** Type 1 dest install | Write `/etc/passwd` or `/etc/sudoers.d`; write dest as Type 0 |
| **CLI (Type 0)** | Emit fragment to **stdout** or **user-writable draft path** | Write `/etc/passwd`, `/etc/sudoers.d`, or `/etc/{{username}}/` |
| **Admin / Type 1** | `visudo -c`, install dest under `/etc/{{username}}/` with mode `0440` | Write `/etc/passwd` or `/etc/sudoers.d`; install fragments that grant shell / `ALL` |
| **Agent (harness)** | Follow **`SK-CREATE-SUDOERS-FILE`** + **`CL-CREATE-SUDOERS-SECURITY`** | Auto-write `/etc/passwd` or `/etc/sudoers.d`; emit without Pass review |

| Artifact | Portable location pattern | Authority |
|----------|---------------------------|-----------|
| **Draft fragment** | stdout **or** `{{SUDOERS_DRAFT_PATH}}` (e.g. `{{HOME}}/.config/{{APP_NAME}}/sudoers.fragment`) | Type 0 write only |
| **Installed dest** | `/etc/{{username}}/{{service}}` (F6: `/etc/{{LPU_USER}}/sudoers`) | Type 1 / admin; mode `0440` |
| **Security review (pre-emit)** | `{{REVIEWS_DIR}}/reports/YYYY-MM-DD-sudoers-security-{{APP_NAME}}.md` and/or filled checklist | Required before **agent create** of a new draft |
| **External sudoers audit record** | `docs/whitelists/external-sudoers/records/WS-*.md` | Optional audit; **no secrets** |

#### 2.3.1a Install trust tiers for elevation (portable)

| Trust tier | Managed install | Meaning |
|------------|-----------------|---------|
| **`production`** | Executable `{{GLOBAL_BIN}}/{{APP_NAME}}` not writable by target user | Production-eligible for durable sudoers |
| **`test_local`** | Only `{{USER_BIN}}/{{APP_NAME}}` (user-rewritable) | **TEST MODE ONLY** — user can replace code and jailbreak elevating designs |
| **`unmanaged`** | Neither path | Fail closed for agent create; product emit only with explicit test allow |

**MUST NOT** claim production-secure elevation for local-only installs. Prefer global install before Type 1 dest install under `/etc/{{username}}/`. Elevating `{{USER_BIN}}/{{APP_NAME}}` is forbidden for production Pass. Checklist **S13** (trust tier) is independent of elev **Tables A/B/C** (S11–S12).

#### 2.3.2 Operator workflow (mandatory order)

| Step | Who | Action |
|------|-----|--------|
| 1 | User / admin | Prefer **global** managed install for hosts that will keep sudoers; local OK for Type 0-only |
| 2 | User | Run `{{APP_NAME}} {{PRINT_SUDOERS_CMD}}` (optional draft path; test_local may require `{{ALLOW_TEST_LOCAL_FLAG}}`) |
| 3 | CLI (Type 0) | Emit **narrow** fragment for the **target user**; report trust tier + warnings |
| 4 | User | Optionally `{{APP_NAME}} print-sudoers-install-script` → admin script under `/dev/shm` or temp (**project-sudoers-file** handoff). **N/A** when the product omits that extra. |
| 4a | User | **Independent generate:** `{{APP_NAME}} {{GENERATE_SUDOER_CMD}}` `[path]` — write the JSON grant to a dest **readable without sudo** (tests/review). Not inbound. Not `/etc`. Term: `independent-sudoer-generate`. |
| 4b | User | Optionally `{{APP_NAME}} {{SUBMIT_SUDOER_CMD}}` `[file]` — sibling allocates inbound JSON. Type 0 **MUST NOT** `mkdir` inbound or write `/etc/sudoers.d`. |
| 5 | **Admin** | Review draft; `sudo sh {{SUDOERS_ADMIN_SCRIPT_PATH}} install\|replace` **or** `visudo -c` + `install -m 0440` **or** sibling Type 1 approve |
| 6 | **Admin** | Optional: pre-create `{{ELEVATED_DEST_DIR}}` with safe ownership/mode |
| 7 | User | Run elevated product ops; Type 1 sub-steps use **only** **Table A** allowlisted sudo commands |
| 8 | Admin (test_local) | Uninstall soon: `sudo sh {{SUDOERS_ADMIN_SCRIPT_PATH}} uninstall` (or rm installed fragment) |

**Specialize fork (sacred — do not collapse):**

| This product is… | Specialize | Must not |
|------------------|------------|----------|
| **Sudoers-manager / approval dest** | Domain SSOT from **`LM-FILE-BASED-JSON-APPROVAL`** | Pretend a Type 0 sibling is the dest |
| **Sudoer-approval-submitter** (Type 0 product that queues a grant) | **`LM-FILE-BASED-JSON-APPROVAL-SUBMITTER`** + **`LM-SUDOER-JSON-FILE`** + this mold §2.3.2a / §2.3.3c / §2.3.3d / §2.3.3e | Treat generate/submit as “sudoers-manager extras”; hide JSON generate inside submit only; fold the machine into the product’s domain SSOT; collapse `type-2-switch` and `login-hook-elev` |

`print-sudoers-install-script` / `remove-project-sudoers` **MAY** stay Absent. **Independent generate + JSON submit are not those extras.** A product that emits a sudoer artifact **MUST** still offer §2.3.2a.

#### 2.3.2a Independent sudoer generate (sacred)

**Purpose:** **Any** sudoer artifact this product generates (text fragment, JSON grant, or a future dual) **MUST** be producible by a **Type 0 subcommand** that writes the file **independently** of submit, approve, and dest install. Tests and review **MUST** open that file **without sudo**.

Applies to every generate surface. Typical specialize names: `{{PRINT_SUDOERS_CMD}}` (text dual + pretty `.json`) and `{{GENERATE_SUDOER_CMD}}` (compact JSON grant). A later generate verb is in scope the day it is added.

| Rule | Detail |
|------|--------|
| **Subcommand** | Routed, help-listed Type 0 verb. A helper used only inside `{{SUBMIT_SUDOER_CMD}}` is **not** independent generate. |
| **Independent** | Writes the artifact and returns. Does **not** queue inbound, write `/etc/sudoers.d`, or require sibling allocate. |
| **Readable dest** | After return, the invoking user **MUST** be able to read the dest (`[ -r ]` / `cat` **without** sudo). Suite and review use that dest as the fixture. |
| **Default dest** | Deterministic; fill in Implementation Notes. Optional path operand **MUST** override so tests isolate under `$HOME`, suite temp, or `/dev/shm`. |
| **Forbidden dest** | `/etc/passwd`; `/etc/sudoers.d`; sibling inbound (`/var/{{APPROVAL_APP}}/…`); a mode the invoking user cannot read; a submit scratch temp **deleted** before return. |
| **Status** | `--json` **MUST** report `path`. Human output **MUST** print that path. |
| **Not a substitute** | Submit temp, inbound after queue, and `purpose` text are **not** the review/test fixture. |

**Normative:**

1. **MUST NOT** make submit, inbound, or admin install the only way to obtain a sudoer body for tests or review.  
2. JSON **body** stays on **`LM-SUDOER-JSON-FILE`**. This section owns **independence and readability**.  
3. Review / suite **MUST** `cat` the generate dest (or an explicit path operand) without sudo.

#### 2.3.3 Print / emit command (Type 0) rules

1. **MUST** emit reviewable plain text suitable for `sudoers(5)` (no passwords, tokens, or private keys).  
2. **MUST NOT** write `/etc/passwd` or `/etc/sudoers` (main file). Type 0 **MUST NOT** write `/etc/sudoers.d`. Type 1 dest default is `/etc/{{username}}/{{service}}`. A specialized **sudoers-manager** product **MAY** declare Type 1 **copy / overwrite / remove** of **product-owned** names under `/etc/sudoers.d/` (F6 `{{LPU_USER}}`; grant `{{service}}-{{username}}`). There is **no** blanket “do not write `/etc`”.  
3. **MUST** bind User lines to the **intended login** (default: invoking user).  
4. **MUST** include short **admin steps** in human output (`visudo -c`, mode `0440`, install path).  
5. Path argument → write **only** that user-writable path; no path → stdout (plus `out_*` status).  
6. Re-emit **MUST** be safe (does not mutate dest under `/etc/{{username}}/`).  
7. Fragment paths **MUST** match **runtime** stage and destination paths used by the elevated implementation (wildcards must actually match).  
8. Fragment Cmnds **MUST** be ⊆ specialized **Table A** (same binaries, args, path patterns) — never emit elev wider than product law.  
9. **MUST** classify trust tier (production vs test_local).  
10. test_local emit **MUST** warn **TEST MODE ONLY / uninstall soon** and **SHOULD** require an explicit allow flag/env when specialized.  
11. JSON (when offered) **SHOULD** include `trust_tier` and `test_mode`.

#### 2.3.3a Admin install-script command (Type 0) — portable

**Purpose:** When the product specializes an admin handoff verb (typical name `print-sudoers-install-script`), Type 0 **MUST** generate a shell script so an account **with sudo** can install, uninstall, or replace the **project-sudoers-file** under `/etc/{{username}}/` without writing `/etc/passwd` or `/etc/sudoers.d`. Term: **`project-sudoers-file`**.

| Rule | Detail |
|------|--------|
| **Refresh draft first** | **MUST** write/refresh the project-sudoers-file (draft) using the **same trust rules** as `{{PRINT_SUDOERS_CMD}}` before writing the admin script |
| **Script location** | Prefer `/dev/shm/{{APP_NAME}}-{{TARGET_USER}}-sudoers-admin.sh`; else product temp/storage — **MUST NOT** write `/etc/passwd` or `/etc/sudoers.d` |
| **No Type 0 dest write** | Script generation **MUST NOT** install dest as a Type 0 side effect. Dest is `/etc/{{username}}/{{service}}` |
| **Actions** | Script **MUST** support at least: `install` (visudo-check draft → `install -m 0440` → re-check), `uninstall` (remove installed fragment), `replace` (uninstall then install), `status` (draft + installed presence; may run without root) |
| **Root for mutate** | `install` / `uninstall` / `replace` **MUST** require root (e.g. `sudo sh {{SUDOERS_ADMIN_SCRIPT_PATH}} …`) |
| **No secrets** | Generated script **MUST NOT** embed passwords, keys, or tokens |
| **Human handoff** | Product output **MUST** print admin handoff lines for install/uninstall/replace |
| **JSON (when offered)** | **SHOULD** include `script_path`, `project_sudoers_file` (or draft path), `installed_path`, `trust_tier` |
| **test_local** | Same TEST MODE / uninstall-soon posture as print/emit; uninstall action is the preferred leave-test path |

**Checklist IDs (portable, match skill):** **S11–S12** = elev Table A bind / no silent widen when elev law claimed; **S13** = install trust tier (always for production claims).

#### 2.3.3b Remove project-sudoers-file (Type 0) — portable

When the product specializes a remove-draft verb (typical name `remove-project-sudoers`):

| Rule | Detail |
|------|--------|
| **Target** | **Project-sudoers-file** draft only (`{{SUDOERS_DRAFT_PATH}}` default); optional path arg |
| **Not dest** | **MUST NOT** delete `/etc/passwd`, `/etc/sudoers.d`, or dest under `/etc/{{username}}/` (point admin to install-script `uninstall`) |
| **Absent** | Success no-op |
| **Confirm** | Interactive confirm unless force; non-interactive without force fails closed |
| **Honesty** | On remove, **MUST** warn installed `/etc/{{username}}/{{APP_NAME}}` is not removed |

#### 2.3.3c Submit sudoer request (Type 0) — portable

When the product specializes a submit verb (typical name `{{SUBMIT_SUDOER_CMD}}` / `submit-sudoer-request`):

| Rule | Detail |
|------|--------|
| **Role** | Type 0 **submitter** — detect sibling approval CLI + inbound; hand a self-scoped **`type-2-switch`** grant. **MUST NOT** `mkdir` inbound, write `/etc/sudoers.d`, approve, invent the queued basename, or queue `login-hook-elev`. |
| **Kind** | Body **MUST** be `kind=type-2-switch` when **`LM-SUDOER-JSON-FILE`** §3.0 applies. Type 0 **MUST** refuse `login-hook-elev` (next: Type 1 `setup` auto-queue). |
| **Input** | Prefer a file from `{{GENERATE_SUDOER_CMD}}`. No file → compact **`type-2-switch`** body for the invoker. |
| **Default action** | **update** when this user’s sibling dest `/etc/sudoers.d/{{APP_NAME}}-{{TARGET_USER}}` exists; else **add**. `--add` / `--update` override. Other users’ dests and `/etc/sudoers.d/{{APP_NAME}}-{{LPU_USER}}` do **not** count. Product F6 dest is **not** that probe. |
| **Inbound fidelity** | When `${inbound}/${request_id}` is readable, fail closed if a required field (`service`, `path`, `runas`, `kind` when present) is missing. Fatal copy **MUST** be operator-readable and point at independent generate. |

JSON **body** remains **`LM-SUDOER-JSON-FILE`**. Sibling dest write after approve is **that** product’s Type 1 — not a violation of this product’s “MUST NOT write `/etc/sudoers.d`”. After approve, Type 0 submit dest is **`/etc/sudoers.d/{{APP_NAME}}-{{TARGET_USER}}`**. Setup dest is **`/etc/sudoers.d/{{APP_NAME}}-{{LPU_USER}}`**. **MUST NOT** collapse them (**`LM-SUDOER-JSON-FILE`** §3.4c).

#### 2.3.3d Generate sudoer request (Type 0) — portable

When the product specializes an independent JSON generate verb (typical name `{{GENERATE_SUDOER_CMD}}` / `generate-sudoer-request`):

1. **MUST** obey §2.3.2a (independent, readable dest).  
2. Default dest **MUST** be documented (`{{GENERATE_SUDOER_DEST}}` for `type-2-switch`; a distinct dest for `login-hook-elev`). Path operand overrides.  
3. Body **MUST** satisfy **`LM-SUDOER-JSON-FILE`**. Generate **MUST** write `kind` when §3.0 applies. `--kind` **MAY** emit the hook fixture without queueing. After write, dest **MUST** stay owner-readable; verify required fields.  
4. When sibling convert CLI is present, **SHOULD** fail closed if convert drops `path` / `runas` / `service` on `type-2-switch`. Missing convert CLI **MUST NOT** block generate. Convert fail on `login-hook-elev` **MUST NOT** block generate (sibling may not convert hook grants yet).  
5. Human output **MUST** name the path. For `type-2-switch`, name the next submit command. For `login-hook-elev`, say Type 0 submit will refuse. `--json` **MUST** include `path` and `kind`.  
6. Suite / review **MUST** open this dest without sudo.

#### 2.3.3e Automatic login-hook sudoer submit (Type 1) — portable

When the product installs a [login-interactive-review-hook](../../terminologies/login-interactive-review-hook.md) that runs `sudo -n {{GLOBAL_BIN}}/{{APP_NAME}}-hook {{REVIEW_VERB}}` ([login-hook-symlink](../../terminologies/login-hook-symlink.md)):

| Rule | Detail |
|------|--------|
| **Body** | `kind=login-hook-elev` — **`LM-SUDOER-JSON-FILE`** §3.0 |
| **When** | Type 1 `setup` (or dedicated hook-config verb) **MUST** queue that JSON **iff** sibling dest CLI + dest approver + writable inbound exist. Term: `automatic-login-hook-sudoer-submit` |
| **Skip** | Any of the three missing → **skip**. Setup **MUST NOT** fail. **MUST NOT** `mkdir` inbound |
| **Queue fail** | **Warn**; setup still reports LPU created/healed. **MUST NOT** write `/etc/sudoers.d` as a fallback |
| **Action** | **update** when sibling dest `/etc/sudoers.d/{{APP_NAME}}-{{LPU_USER}}` exists; else **add** |
| **Not Type 0** | `{{SUBMIT_SUDOER_CMD}}` **MUST NOT** become this path |
| **Write inbound** | Type 1 `setup` **MUST** write dest request-id grammar into inbound. **MUST NOT** call dest Type 0 `add-sudoer-request` / `update-sudoer-request`. **MUST NOT** `chown` inbound (dest `{{APPROVER}}` takes ownership) |
| **Queue ownership** | Submitter/setup **MUST NOT** `chown`. Dest approver **MUST** take ownership when run as `{{APPROVER}}`, then move. Login-hook review (`sudo -n` as euid 0) **MUST** `chown` to `{{LPU_USER}}` before any product-queue move. Terms: `approval-queue-move` · `file-ownership` · `json-username-field` |
| **Dest approval fencing conditions** | Closed list. Dest inbound fence is **incorrect JSON format**. Dest **MUST NOT** add extra fences. Specialized law **MUST** print the table below |
| **Submit vs setup door** | **Submit** = current login, Type 0, **no sudo**, `type-2-switch` only. **Setup** = host admin, Type 1, **password `sudo` / already root**. Dest approval reviews the JSON and does **not** test who submitted |
| **Forbidden dest check** | Dest Type 0 self-scope (`username` == `id -un`) **MUST NOT** apply to `setup`. That check is a **blockage**, not a safety net and not dest approval |
| **`--json`** | **MUST** include `login_hook_sudoer` = `submitted` \| `skipped` \| `failed` |
| **Rc / labeled name** | Snippet, `.profile`, `{{APP_NAME}}-hook` create/rewrite, and old-hook review are **owned by** **`LM-LOGIN-INTERACTIVE-REVIEW-HOOK`**. This mold **points**. Type 1 `setup` **and** dest `{{REVIEW_VERB}}` **MUST** replace `{{GLOBAL_BIN}}/{{APP_NAME}} {{REVIEW_VERB}}` in `{{APPROVER}}` rc with `{{APP_NAME}}-hook` |

**Dest approval fencing conditions (closed, sacred).** Dest `approve` / `reject` / `{{REVIEW_VERB}}` **MUST** fail closed on inbound **only** when a listed [approval fencing condition](../../terminologies/approval-fencing-condition.md) holds. Dest inbound fence is **[incorrect JSON format](../../terminologies/incorrect-json-format.md)**. Dest **MUST NOT** add extra fences. Specialized law **MUST** print this table. Peer: **`LM-FILE-BASED-JSON-APPROVAL`** §2.3a.

| Condition | Dest approve / reject / `{{REVIEW_VERB}}` |
|-----------|-------------------------------------------|
| **[Incorrect JSON format](../../terminologies/incorrect-json-format.md)** | **Fence** — fail closed. Independent REQ (specialize **`LM-FENCE-CONDITION-REQUIREMENT`**; dest table still prints) |
| File-ownership | **MUST NOT** fence — take ownership as dest LPU / `{{APPROVER}}` |
| Who submitted / dest Type 0 self-scope | **MUST NOT** fence |
| JSON username field ≠ dest LPU | **MUST NOT** fence |
| Filename subject token ≠ JSON username field | **MUST NOT** fence — user SSOT is the JSON field |

**Incorrect JSON format** includes: not a regular file; not one parseable JSON object; closed-schema fail; field types/enums invalid; basename grammar fail; basename **action** ≠ JSON `action`. Dest **MUST NOT** take the user from the filename; user SSOT is the JSON username field. Type 0 submit self-scope and Type 1 **authz** are **not** dest inbound-file fences.

N/A when the product has no login-time review hook.

#### 2.3.4 Fragment content constraints (mandatory)

| Rule | Detail |
|------|--------|
| **Table A bound** | Every Cmnd line maps to a Table A elev-ID; no orphan elev in fragment or ship unit |
| **User-bound** | Named user or documented User_Alias — not unrestricted `ALL` users unless explicit product redesign |
| **Cmnd absolute** | Absolute binary paths only (no PATH-relative Cmnds) |
| **Destination-bound** | When grant is the **project command**, dest bounds are enforced **in-tool** (Table C) — not extra OS-tool Cmnds. Do **not** add `mkdir`/`cp` dest wildcards to the fragment. |
| **Stage-bound** | Source operands limited to product staging roots for that user (e.g. `{{STAGE_ROOT_PATTERN}}`) |
| **No broad rights** | **MUST NOT** include `ALL=(ALL) ALL`, `NOPASSWD: ALL`, unrestricted shells as bare Cmnd, or unrestricted destructive tools over `/` (align **Table B**) |
| **NOPASSWD scope** | `NOPASSWD:` **MAY** apply **only** to listed Cmnds when product law requires non-interactive `sudo -n`; residual risk **MUST** appear in the security review |
| **No secrets** | Never in fragment or review |
| **Comments** | Header **SHOULD** state purpose, `{{APP_NAME}}`, date/generator, **trust tier**, and admin `visudo -c` duty |
| **test_local banner** | When tier is test_local, header **MUST** warn TEST MODE ONLY and uninstall-soon |
| **No local binary Cmnd (production)** | **MUST NOT** elevate `{{USER_BIN}}/{{APP_NAME}}` under production Pass |

#### 2.3.4a Example sudoers fragment (portable mold)

**Illustrative shape only** — specialize by replacing every `{{PLACEHOLDER}}` with project-real values in the specialized requirement.  
Admin **MUST** still run `visudo -c` on the target host. **MUST NOT** paste this mold block into `/etc` with unresolved placeholders.

```sudoers
# {{APP_NAME}} — project command only (review before install)
# Generated: {{FRAGMENT_DATE}}
# Skill: SK-CREATE-SUDOERS-FILE (when agent-authored)
# Security review: Pass ({{SUDOERS_SECURITY_REVIEW_PATH}})
# Target user: {{TARGET_USER}}
# Trust tier: production | test_local
# Managed binary: prefer {{GLOBAL_BIN}}/{{APP_NAME}} (production); {{USER_BIN}} = TEST MODE ONLY
# WARNING if test_local: user can rewrite local binary — uninstall fragment soon
# DO NOT use without: sudo visudo -c -f <this-file>
# Admin / Type 1 dest:
#   sudo install -m 0440 <this-file> /etc/{{TARGET_USER}}/{{APP_NAME}}
# MUST NOT write /etc/passwd or /etc/sudoers.d
#
# Scope: elevate {{GLOBAL_BIN}}/{{APP_NAME}} verbs from Table A.
# Withdrawn: OS-tool Cmnds (mkdir/cp/tar/rm/install/chmod).
# No full shell. No ALL. No NOPASSWD: ALL.

{{TARGET_USER}} ALL=(root) NOPASSWD: {{GLOBAL_BIN}}/{{APP_NAME}} {{BACKUP_CMD}}
{{TARGET_USER}} ALL=(root) NOPASSWD: {{GLOBAL_BIN}}/{{APP_NAME}} {{RESTORE_CMD}}
```

**Placeholder map for the example**

| Placeholder | Meaning when specializing |
|-------------|---------------------------|
| `{{APP_NAME}}` | Product / fragment file under `/etc/{{TARGET_USER}}/` |
| `{{TARGET_USER}}` | Login allowed to elevate (default: invoking user) |
| `{{ELEVATED_DEST_DIR}}` | Only writable destination tree (no trailing-slash-free host root) |
| `{{STAGE_ROOT_SHM}}` | e.g. `/dev/shm/{{APP_NAME}}-{{TARGET_USER}}` |
| `{{STAGE_ROOT_TMP}}` | e.g. `/tmp/{{APP_NAME}}-{{TARGET_USER}}` |
| `{{STAGE_ROOT_CACHE}}` | e.g. `{{XDG_CACHE_HOME}}/{{APP_NAME}}-{{TARGET_USER}}` |
| `{{USER_BIN}}` / `{{GLOBAL_BIN}}` | Managed install locations |
| `{{SUDOERS_SECURITY_REVIEW_PATH}}` | Review report path after Pass |
| `{{FRAGMENT_DATE}}` | Generation date |

**Omit from every specialized example:** `NOPASSWD: ALL`, bare shell Cmnds, package managers, and stage wildcards that cover all of `/tmp/*` or `$HOME/*`.

#### 2.3.5 Admin install rules

1. Admin **MUST** validate with `visudo -c -f <file>` before install.  
2. Admin **MUST** install with restrictive mode (typically **`0440`**, owner `root:root`).  
3. Preferred dest: **`/etc/{{TARGET_USER}}/{{APP_NAME}}`**. F6: **`/etc/{{LPU_USER}}/sudoers`**. **MUST NOT** write `/etc/passwd` or `/etc/sudoers.d`.  
4. Product CLI and agents **MUST NOT** perform this install as a silent Type 0 side effect.  
5. Destination trees **MAY** be created **in-tool** after elev (Table C). Admin **MAY** pre-create them. **MUST NOT** add `mkdir` to the fragment as a portable grant.

#### 2.3.6 Runtime elevation after install

| Rule | Detail |
|------|--------|
| **Bootstrap** | Type 1 `setup` that **creates** Table A: already-root, outer password `sudo`, **or in-tool** password `sudo` (e.g. `sudo useradd`). **MUST NOT** be `sudo -n` or require the LPU the grant creates (**T1-BOOTSTRAP-N**) |
| **Invocation (post-grant)** | **`sudo -n` is not suggested.** Use it **only** when specialized law names a NOPASSWD allowlist / hook. Otherwise password `sudo` or already-root. |
| **Scope** | **Table A** = sudoers Cmnds. **Table C** = in-tool `sudo <tool>` (not in the fragment) |
| **Root path** | If already root, product **MAY** still call `sudo useradd` (mix model) or run the tool directly. Still no Table B ops. |
| **Logging** | `out_*` only; never print sudo passwords |
| **Probe honesty** | Status probes **SHOULD NOT** treat failure of `sudo -n true` or `sudo -n mkdir` as “no elevation”. Proof is running a **Table A project verb** with password `sudo` (`sudo {{GLOBAL_BIN}}/{{APP_NAME}} {{BACKUP_CMD}}`). **`sudo -n` is not suggested.** OS-tool probes are withdrawn. |

#### 2.3.7 Fail-closed (mandatory)

If sudo is missing, unauthorized for the Cmnd, or the destination cannot be written:

1. Elevated sub-step **MUST** fail with non-zero exit.  
2. Human error **MUST** point to `{{PRINT_SUDOERS_CMD}}` + dest under `/etc/{{username}}/`.  
3. **MUST NOT** silently skip the elevated sub-step and claim overall success.  
4. **MUST NOT** unprivileged-write into a root-owned destination tree when that is the product contract.

#### 2.3.8 Agent / harness create path

When an agent **creates or materially revises** a sudoers draft (beyond re-running the product print command):

1. **MUST** follow **`SK-CREATE-SUDOERS-FILE`**.  
2. **MUST** complete **`CL-CREATE-SUDOERS-SECURITY`** with **Pass** or **Pass (test only)** before writing the draft (incl. **S11–S12** when elev REQs exist; **S13** trust tier always).  
3. **MUST** identify **target user** (default: current user).  
4. **MUST** prove **managed binary** install when elevating `{{APP_NAME}}`. Portable default grant is `{{GLOBAL_BIN}}/{{APP_NAME}}` verbs — **MUST NOT** emit OS-tool-only (`mkdir`/`cp`/`tar`/`rm`) as the backup/deposit grant.  
5. **MUST** take proposed Cmnds **only from Table A** (or authorize Table A update first — never silent widen).  
6. **MUST** publish security review under `{{REVIEWS_DIR}}/reports/` (or filled checklist).  
7. **MUST NOT** write `/etc/passwd` or `/etc/sudoers.d`. Dest default is `/etc/{{username}}/{{service}}`.  
8. **MUST NOT** claim production Pass for local-only managed installs.  
9. **SHOULD** record applied fragments under `docs/whitelists/external-sudoers/` (no secrets); test_local → status test / to-uninstall.

---

### 2.4 Implementation Notes (fill when specializing — no-placeholder)

| Item | Placeholder / example shape |
|------|-----------------------------|
| **Product** | `{{APP_NAME}}` |
| **Print command** | `{{PRINT_SUDOERS_CMD}}` (e.g. `print-sudoers`) |
| **Generate command** | `{{GENERATE_SUDOER_CMD}}` (e.g. `generate-sudoer-request`) — independent JSON dest |
| **Generate dest** | `{{GENERATE_SUDOER_DEST}}` (owner-readable; path operand for suite) |
| **Submit command** | `{{SUBMIT_SUDOER_CMD}}` (e.g. `submit-sudoer-request`) |
| **Approval dest product** | `{{APPROVAL_APP}}` (conventional `sudoer-cli`) — detect, do not own |
| **Admin install-script command** | e.g. `print-sudoers-install-script` (§2.3.3a) or **N/A** if product omits handoff |
| **Draft path (project-sudoers-file)** | `{{SUDOERS_DRAFT_PATH}}` |
| **Admin script path** | `{{SUDOERS_ADMIN_SCRIPT_PATH}}` (prefer `/dev/shm/…`) |
| **Installed dest** | `/etc/{{username}}/{{service}}` (F6: `/etc/{{LPU_USER}}/sudoers`) |
| **Elevated destination** | `{{ELEVATED_DEST_DIR}}` |
| **Stage roots** | `{{STAGE_ROOT_PATTERN}}` |
| **Type 2** | `{{SYSTEM_USER}}` or **Not used** |
| **Tables A/B/C** | **Filled** per §2.2a (absolute paths; no hollow TBD when claiming done) |
| **Elev-table SSOT** | This file **or** pointer to single peer that owns tables |
| **Trust tier / S13** | production vs test_local; local-only not production-secure |
| **Allow-test flag** | `{{ALLOW_TEST_LOCAL_FLAG}}` / env when specialized |
| **NOPASSWD?** | yes/no + residual risk note |
| **WS / review paths** | Project-real paths after specialize |
| **Example fragment** | Specialize §2.3.4a with real user/paths; lines ⊆ Table A (no bare `{{…}}` in claimed-done law) |

### 2.4.1 Specialize checklist (elev tables)

When specializing this mold (or declaring elev SSOT on a peer):

1. If the product emits sudoers: Table A = **those fragment lines only**. Do **not** list every live command the script runs.  
2. Table B only if the user/product named sudoers-forbidden rows. Do **not** invent a live-command denylist.  
3. Table C (optional) = example script jobs (`sudo useradd`). Unlisted tools are **not** forbidden.  
4. Align `print-sudoers` to Table A (the fragment).  
5. If the product is a **sudoer-approval-submitter**, specialize generate + submit in the **same change** as the JSON body REQ. Do **not** mark those verbs “folder-backup only.”  
6. If ops/domain REQ also mentions elev → **one** SSOT + pointer only.

---

### 2.5 Role in broader architecture (balance)

The privilege model and sudoers files govern **how the CLI escalates**. Broader architecture (components, data flow, containers) **MUST NOT** be replaced by this document alone. Peer molds: `template-system-architecture.md`, `template-least-privilege-user.md`, `template-requirement-system-user.md`.

---

## 3. Design Principles (CIAO / CIAO-Lite)

- **Caution:** Do not invent a live-command whitelist or denylist. Fragment contents stay honest.  
- **Intentional:** Type map + Tables A/B/C + print vs install vs elevate are explicit.  
- **Anti-fragile:** Draft outside `/etc/passwd` and `/etc/sudoers.d`; dest under `/etc/{{username}}/`; works offline.  
- **Over-protect:** No `NOPASSWD: ALL`; security review before agent create; law > script (anti jailbreak).

---

## Under command line for normal user only

When the ship unit detects a **command line for normal user only** (Termux, Git Bash, Windows cmd, or the same class — term [`command-line-for-normal-user-only.md`](../../terminologies/command-line-for-normal-user-only.md)):

| MUST | MUST NOT |
|------|----------|
| Keep **normal user privilege** (Type 0) only | Implement or enable **admin privilege** (Type 1) or **dedicated system user privilege** (Type 2) |
| Document Type 1 **unused** and Type 2 **unused** | In-tool `sudo`; wrap `apt` / `dnf` / `yum`; write `/etc` dests; `useradd` / dedicated LPU; Type 2 `sudo -u` switch |
| Termux: named `pkg` as this login remains Type 0 (**`LM-SHELL-TERMUX-ISH`**) | Recommend `sudo curl \| sh` as the install path |
| Git Bash: same privilege ceiling | Invoke Termux `pkg` because Git Bash was detected |
| Windows cmd: same privilege ceiling | Invoke Termux `pkg` because Windows cmd was detected |

Detect (typical): Termux — `PREFIX` contains `com.termux`; `TERMUX_VERSION` set; `/data/data/com.termux/files/usr` exists. Git Bash — `MSYSTEM` is `MINGW*` / `MSYS*` / `UCRT*` / `CLANG*`; `uname -s` is `MINGW*` / `MSYS*`. Windows cmd — `OS` is `Windows_NT` or `ComSpec`/`COMSPEC` names `cmd.exe` (after excluding Git Bash, Cygwin, WSL). Detail: §2.1a.

**This mold:** layer map + sudoers dests **MUST** stay unused on that class; do not specialize Type 1/2 rows as Active wrap law there.

---

## 4. Protection Rule (Sacred)

**Future AI assistants, Grok, or maintainers MUST NOT**:

1. Grant `ALL=(ALL) ALL`, `NOPASSWD: ALL`, or unrestricted shell Cmnds in product-generated fragments.  
2. Write `/etc/passwd` or `/etc/sudoers.d`, or invent a blanket “do not write `/etc`” that blocks `/etc/{{username}}/`.  
3. Collapse Type 0/1/2 for convenience or open unapproved egress while designing (`PP-A-08` / `PP-A-16` / `E-PRIV-*` / `E-NET-*`).  
4. Emit a **new** agent-authored fragment without **Pass** on **`CL-CREATE-SUDOERS-SECURITY`**.  
5. Put passwords or private keys in fragments, reviews, or specialized requirements.  
6. Hardcode one product’s host paths into **this mold** (use `{{PLACEHOLDER}}`).  
7. Mark elevated success when the elevated sub-step failed.  
8. Treat this mold or skills as product-source behavioral authority after specialize (source cites live `requirement-*.md`).  
9. Invent a **live-command whitelist** or treat Table A as “every binary the script may run” (**PP-A-17**).  
10. Invent a **live-command denylist** the user did not publish, or treat “no blacklist” as “deny all unlisted” (**PP-A-17**).  
11. Put `useradd` / Table C tools into sudoers.  
12. Write “ship unit MUST NOT invoke `sudo`” or “elev calls ⊆ Table A” as default law.  
13. Claim production-secure elevation for **local-only** (`{{USER_BIN}}`) managed installs.  
14. Elevate `{{USER_BIN}}/{{APP_NAME}}` under a production Pass.  
15. Omit TEST MODE / uninstall-soon warnings for test_local fragments.  
16. Hide sudoer generate only inside submit (no independent Type 0 subcommand).  
17. Treat inbound, `/etc/sudoers.d`, or a deleted submit temp as the **review/test fixture** for a generated sudoer file.  
18. Classify `generate-sudoer-request` / `submit-sudoer-request` as trimmed “sudoers-manager extras.” Those extras are `print-sudoers-install-script` / `remove-project-sudoers` only.  
19. Let Type 0 `{{SUBMIT_SUDOER_CMD}}` queue `login-hook-elev`, or fail `setup` solely because the sibling dest is absent.  
20. Collapse `type-2-switch` and `login-hook-elev` into one JSON body.  
21. Apply dest Type 0 self-scope (`username` == `id -un`) to Type 1 `setup`, call dest Type 0 `add-sudoer-request` for `login-hook-elev`, or treat that dest check as a safety net.  
22. Confuse **who may submit** (current login, Type 0, no sudo) with **who may setup** (host admin, Type 1, password `sudo` / already root).  
23. Treat Type 1 `setup` as writing `/etc/sudoers.d/{{APP_NAME}}-{{TARGET_USER}}`, or Type 0 submit as writing `/etc/sudoers.d/{{APP_NAME}}-{{LPU_USER}}`. Hook dest is the **LPU**; switch dest is the **invoker**.  
24. Use `/etc/sudoers.d/{{APP_NAME}}-{{LPU_USER}}` as the Type 2 default-ops grant (that dest is hook `sudo -n {{REVIEW_VERB}}` only).  
25. `chown` dest inbound JSON from Type 1 `setup` or Type 0 submit. Dest `{{APPROVER}}` takes ownership.  
26. Move a product inbound queue **without** a prior `chown` to the approver (login-hook `{{REVIEW_VERB}}` **MUST** `chown` to `{{LPU_USER}}` first).  
27. Add a dest inbound fence that is not **incorrect JSON format** (who submitted, dest Type 0 self-scope, JSON username ≠ dest LPU).  
28. Strip the **Under command line for normal user only** section, or enable Type 1/2 on Termux / Git Bash.

**Violating this rule is a critical privilege / LLM-escape class regression.**

---

## 5. Acceptance criteria (portable — specialize IDs)

| ID | Criterion |
|----|-----------|
| AC-1 | Layer map documents Type 0 / Type 1 / Type 2 (or explicit Not used) |
| AC-2 | Print/emit does not write `/etc/passwd` or `/etc/sudoers.d` |
| AC-3 | Elevated sub-step fails closed without working allowlisted sudo |
| AC-4 | Fragment is narrow (no ALL ALL / NOPASSWD: ALL) |
| AC-5 | Admin install (`visudo -c`, mode `0440`) documented |
| AC-6 | Fragment paths align with runtime stage/dest |
| AC-7 | Host-dependent: allowlisted non-root elevation works after admin install |
| AC-8 | Agent create requires security review Pass |
| AC-9 | If a fragment is emitted: Table A = those sudoers lines (not a live-command whitelist) |
| AC-10 | Specialized law includes **Table B** denylist (no shell / ALL / unbound destroy) |
| AC-11 | No invented live-command whitelist/denylist; Table C (if present) is examples, not a closed set |
| AC-12 | `print-sudoers` ⊆ Table A. Table C is `sudo <tool>` in the script, **not** in the fragment |
| AC-13 | Trust tier classified; production Pass requires global managed binary (**S13**) |
| AC-14 | test_local emit has TEST MODE / uninstall-soon warnings (and optional allow flag) |
| AC-15 | When product offers admin install-script: Type 0 writes script under `/dev/shm` or temp only; dest is `/etc/{{username}}/`; does not write `/etc/passwd` or `/etc/sudoers.d` (§2.3.3a) |
| AC-16 | Checklist IDs: **S11–S12** elev Table A bind when elev law claimed; **S13** trust tier for production claims |
| AC-17 | When product offers remove-draft: Type 0 removes project-sudoers-file only; refuses `/etc/passwd` / `/etc/sudoers.d` / dest; confirm/force (§2.3.3b) |
| AC-18 | When the product generates a sudoer file: an independent Type 0 subcommand writes an invoking-user-readable dest (not inbound, not `/etc/sudoers.d`, not a deleted temp). Suite/review `cat` that dest without sudo (§2.3.2a) |
| AC-19 | When the product is a sudoer-approval-submitter: Type 0 `{{SUBMIT_SUDOER_CMD}}` detects sibling CLI + inbound, fails closed if missing, and does not write `/etc/sudoers.d` |
| AC-20 | When both JSON kinds exist: specialized law names switch dest `/etc/sudoers.d/{{APP_NAME}}-{{TARGET_USER}}`, hook dest `/etc/sudoers.d/{{APP_NAME}}-{{LPU_USER}}`, and F6 separately (§3.4c) |
| AC-21 | When Type 2 default dest exists: unspecified ops as a non-`{{LPU_USER}}` re-exec or fail `{{LPU_REQUIRED_CODE}}`; specify does not switch |

---

## 6. Related molds / peers

| Mold / artifact | Relationship |
|-----------------|--------------|
| **`LM-LEAST-PRIVILEGE-USER`** | Internal sudo pattern; Type map mechanics |
| **`LM-REQUIREMENT-SYSTEM-USER`** | Type 2 identity when used |
| System architecture mold | Broader component map |
| Proof / suite | Product `reviews/test-plan.md` + domain/elev TP families |
| Checklist **`CL-CREATE-SUDOERS-SECURITY`** | Pre-emit gate |
| Skill **`SK-CREATE-SUDOERS-FILE`** | Agent procedure (not product law) |

---

## Design-time verification

| Gate | Artifact | Phase |
|------|----------|-------|
| Specialize → product suite | declare TP-IDs (print-sudoers, fail-closed, elev success when available) | Design |
| RTM | `../tests/template-requirement-test-traceability.md` | Design |
| Sudoers pre-emit | **`CL-CREATE-SUDOERS-SECURITY`** when creating fragments | Design / implement |
| Product status | specialized REQ + `reviews/test-plan.md` (`todo` → `have`) | Design |

Suggested TP themes when specializing deposit-style products:

| Theme | Intent |
|-------|--------|
| Print/emit | Fragment on stdout/file; no Type 0 `/etc` write |
| Narrow content | No `NOPASSWD: ALL` / no shell Cmnd; fragment ⊆ Table A |
| Fail-closed | Deposit/elev fails without working sudo |
| Elev success | Root, password `sudo`, or specified F6 `-n` |
| Elev closed set | No `sudo -n` except specified hook/grant; Table C uses password `sudo`; fragment has no `useradd` |
| Next-N / idempotent elev side effects | As product domain requires |

---

## How to use this template

1. Copy structure into `docs/requirements/requirement-three-layer-privilege-model.md` (or project key).  
2. Fill **Tables A/B/C** (§2.2a) with **real** elev rows — required when Type 1 claimed.  
3. Fill **Implementation Notes** with **real** product paths/users (no bare `{{…}}` in claimed-done law).  
4. Keep core rules portable where possible; put host facts only in notes.  
5. Wire **Design-time verification** to suite TP rows (incl. elev closed-set when practical).  
6. For agent-authored drafts, run **`SK-CREATE-SUDOERS-FILE`** + checklist **Pass** (**S11–S12** elev when claimed; **S13** trust tier) before file create; Cmnds from Table A only.  
7. Register the specialized requirement in `docs/requirements/index.md`.  
8. Ops/domain peers that use elev **point** here (or reverse: this file points to single peer SSOT).

---

**Last Updated**: 2026-09-12  
- **2.21.0** (2026-09-10): §2.1a Git Bash **primary** detect folder `/c/` or `/c`; default drive `/c/`; scratch [`git-bash-temp-folder.md`](../../terminologies/git-bash-temp-folder.md).  
- **2.20.0** (2026-09-08): §2.3.3e rc / labeled `{{APP_NAME}}-hook` / old-hook review **points** at **`LM-LOGIN-INTERACTIVE-REVIEW-HOOK`**.  
- **2.19.1** (2026-09-05): Named section **Under command line for normal user only** (exact heading; §2.1a stays detect detail).  
- **2.19.0** (2026-09-05): §2.1 rule 7 + §2.1a — **command line for normal user only** (Termux, Git Bash): Type 1/2 unused on detect.  
- **2.18.1** (2026-09-05): Layer map + Terminologies name **normal user privilege** / **admin privilege** / **dedicated system user privilege**. Workshop Type 0/1/2 stay.  
- **2.18.0** (2026-09-03): §2.3.3e hook `sudo -n` uses [login-hook-symlink](../../terminologies/login-hook-symlink.md) `{{APP_NAME}}-hook`.  
**Owner**: {{OWNER}}  
**Version history:**  
- **2.17.1** (2026-08-21): Probe honesty = password `sudo` of the project verb; `-n` not suggested (align §2.3.6).  
- **2.17.0** (2026-08-21): §2.3.4a example is project `{{BACKUP_CMD}}`/`{{RESTORE_CMD}}` only; withdraw OS-tool `mkdir`/`cp`/`tar` fragment; probe honesty = project verb not `mkdir`.  
- **2.16.0** (2026-08-19): Dest Fence row points at independent REQ (`LM-FENCE-CONDITION-REQUIREMENT`).  
- **2.15.0** (2026-08-19): Dest MUST NOT fence on filename subject token; user SSOT is the JSON username field.  
- **2.14.0** (2026-08-18): §2.3.3e dest approval fencing conditions closed; dest inbound fence is incorrect JSON format.  
- **2.13.0** (2026-08-18): §2.3.3e setup MUST NOT `chown` dest inbound; queue move assumes prior ownership change.  
- **2.12.0** (2026-08-18): Type 2 default-ops re-exec; switch dest `{{APP_NAME}}-{{TARGET_USER}}` ≠ hook dest `{{APP_NAME}}-{{LPU_USER}}` (§3.4c).  
- **2.11.0** (2026-08-18): §2.3.3e submit-vs-setup door; dest Type 0 self-scope MUST NOT apply to setup (blockage).  
- **2.10.0** (2026-08-18): §2.3.3c Type 0 submit is `type-2-switch` only; §2.3.3e setup auto-queues `login-hook-elev` when sibling dest exists.  
- **2.9.0** (2026-08-18): Specialize fork (approval dest vs submitter); generate/submit are **not** sudoers-manager extras; AC-18/19.  
- **2.8.0** (2026-08-17): §2.3.2a independent sudoer generate (readable dest); §2.3.3c/d submit/generate verbs; AC-18; term `independent-sudoer-generate`.  
- **2.6.0** (2026-08-14): Dest `/etc/{{username}}/{{service}}`; F6 `/etc/{{LPU_USER}}/sudoers`; never write `/etc/passwd` or `/etc/sudoers.d`; no blanket `/etc` ban.  
- **2.5.0** (2026-08-14): Default **no live-command whitelist**; **no denylist ⇒ no restrict**; Table A = fragment only.  
- **2.4.0** (2026-08-14): Mix model — password `sudo` OK in ship unit; Table C ≠ sudoers; do not write “MUST NOT invoke sudo” as default; `-n` not suggested.  
- **2.1.0** (2026-08-07): Elev **Tables A/B/C** as core SSOT (§2.2a); Type 1 / print-sudoers / fragment / runtime bound to Table A; anti agent jailbreak (law > script); AC-9…12; peer mold alignment.  
- **2.0.1** (2026-08-03): Sudoers fragment law + deposit-style example.  
 
**Version history:**  
- **2.0.1** (2026-08-03): §2.3.4a **example sudoers fragment** (portable `{{PLACEHOLDER}}` shape + placeholder map).  
- **2.0.0** (2026-08-03): Added full **working with sudoers fragment files** law (§2.3); roles, content, admin install, fail-closed, agent security gate; terminologies include `sudoers-fragment`; dual-policy notes.  
- **1.0.0** (2026-06-15): Initial architecture-oriented three-layer guidance.

**Alignment**: **`LM-LEAST-PRIVILEGE-USER`** · **`LM-REQUIREMENT-SYSTEM-USER`** · harness **`policy-least-privilege`** · **`CL-LEAST-PRIVILEGE`** · **`CL-LLM-ESCAPE`** · **`CL-CREATE-SUDOERS-SECURITY`** · **`SK-CREATE-SUDOERS-FILE`** · term `sudoers-fragment` · CIAO Principles 1, 2, 3, 4, 9, 10, 20 (v2.10.2).
