---
name: privilege-prevention-set
id: LM-PRIVILEGE-PREVENTION-SET
kind: law-mold
description: >
  Portable closed catalog of what a product blocks vs what must stay open after
  elev. Cite as LM-PRIVILEGE-PREVENTION-SET. Elev is approval for every Type 1
  verb — including approve/review. Requiring SUDO_USER=={{LPU_USER}} after
  password sudo is an invented wall (PP-A-17), not helpful checking.
---

**file**: template-privilege-prevention-set.md  
**Mold-ID**: LM-PRIVILEGE-PREVENTION-SET  
**Status**: Active (Version 1.2.0)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered / Over-protect)

**Folder structure (policy):** [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`. Specialize into a project `requirement-privilege-prevention-set.md` (or equivalent key). Product source cites the live requirement, never this mold.

# =============================================================================
# CIAO-Lite Protection Zone
# Closed catalog + must-remain-open. Elev is approval for ALL Type 1 verbs.
# Do not specialize a second actor lock after password sudo / root login.
# =============================================================================

## 1. Purpose

This mold is the portable pattern for **what the product blocks** and **what it must not block** after the operator has already elevated.

It exists so agents cannot:

1. Invent a wall that is not a published block row.  
2. Close a must-remain-open row by “helpful checking.”  
3. Treat **elev is approval** as if it applied only to `setup`, then lock **approve / review** to `SUDO_USER=={{LPU_USER}}`.

Peer molds own the Type map (**`LM-THREE-LAYER-PRIVILEGE-MODEL`**), the LPU account (**`LM-LEAST-PRIVILEGE-USER`**), and the approval machine (**`LM-FILE-BASED-JSON-APPROVAL`**). This mold owns the **catalog pair** (block vs open). A specialize **MUST NOT** publish both “elev is approval” and “already-elevated host admin may not approve.”

## 2. Terminologies

| Term | Path | SSOT type | Role |
|------|------|-----------|------|
| **Elev is approval** | `docs/terminologies/elev-is-approval.md` | `product-law` | Password `sudo` / root login **is** authorization; no second lock |
| **Three-layer privilege** | `docs/terminologies/three-layer-privilege.md` | `product-law` | Type 0 / 1 / 2 map |
| **Least-privilege user** | `docs/terminologies/least-privilege-user.md` | `identity-runtime` | Dedicated operator; not the only Type 1 actor after elev |
| **Least privilege** | `docs/terminologies/least-privilege.md` | `policy` | Size the job **before** elev |
| **LLM pain point** | `docs/terminologies/llm-pain-point.md` | `policy` | **`PP-A-08`** / **`PP-A-17`** invented wall |
| **File-based JSON approval** | `docs/terminologies/file-based-json-approval.md` | `product-law` | When the product is an approval machine |
| **Stay-honest** | `docs/terminologies/stay-honest.md` | `policy` | Do not advertise a live verb that dies after elev |
| **Least privilege (harness)** | `docs/policies/policy-least-privilege.md` | `policy` | No root-by-convenience **and** no unconfirmed walls |
| **SSOT catalog** | `docs/terminologies/ssot-catalog.md` | `meta-catalog` | Inventory |

**SSOT types used:** `product-law` · `identity-runtime` · `policy` · `meta-catalog`

**Primary owner after specialize:** the product `requirement-privilege-prevention-set.md` (or the three-layer REQ if the product keeps one catalog).

**Missing terms:** none

## 3. Core rules (MUST)

### 3.1 Closed-list rule

1. A product **block** exists **only** when it has a row in the specialized § block catalog.  
2. If an action is **not** listed, the product **MUST NOT** stop it — unless this requirement is revised in the **same change** as the new block.  
3. Invented walls include: unpublished live-command whitelist or denylist; Gap stub / “not enabled” after euid 0; env flag that turns off create; a **second actor check** after password `sudo` or a root login (including `SUDO_USER` must equal `{{LPU_USER}}` on approve/review).  
4. The must-remain-open catalog is **product law**. Closing a row is the same class of defect as adding an unlisted block.

### 3.2 Helpful check vs actor override (do not confuse)

| Kind | Examples | After password `sudo` / root? |
|------|----------|-------------------------------|
| **Helpful check** | Schema, visudo, dest name, hostile inode, subject is a login identity (not `ALL`) | **Stay** — they review the **file** |
| **Actor override** | `SUDO_USER` must be `{{LPU_USER}}`; “only the LPU may approve”; extra confirm that is not undo-hard | **Forbidden** — they override the **person** who already elevated |

The operator who typed password `sudo` **is** the approval user. Day-to-day F6 for `{{LPU_USER}}` is an **additional** path, not the exclusive one.

### 3.3 Must remain open (portable defaults)

Specialize these rows. Do **not** drop them unless the user ordered a different model.

| ID | Must stay open | After / when | Why |
|----|----------------|--------------|-----|
| **OPEN-ELEV** | Run the Type 1 job the operator invoked — **including** approve / reject / review | After password `sudo` **or** a root login (`SUDO_USER` may be **any** host admin) | That elev **is** the approval. **MUST NOT** invent a second lock |
| **OPEN-SUDOER-APPR** | Any already euid-0 host admin **MAY** approve / reject / review | Same as OPEN-ELEV | F6 / `{{LPU_USER}}` is **not** the only approver. Requiring `SUDO_USER=={{LPU_USER}}` is **PP-A-17** |
| **OPEN-BOOT-ANY** | Any host admin already euid 0 **MAY** run first-time create / teardown | Bootstrap | `{{LPU_USER}}` does not exist yet |
| **OPEN-USERADD** | Type 1 create **MUST** call `useradd` (password `sudo` OK) | After euid 0 | Account create is a script job, not an F6 Cmnd |
| **OPEN-SUDO** | Ship unit **MAY** invoke password `sudo` | Mix model | “Avoid `sudo -n`” is not “avoid `sudo`” |
| **OPEN-CONFIRM** | The **only** extra gate after elev is TTY confirm or `--force` on **sensitive** undo-hard steps | After euid 0 | Confirm is not a new privilege class |
| **OPEN-DECIDE** | Type 1 accept / decline **MUST** move a regular inbound proposal after euid 0 | After elev | **MUST NOT** fail because file owner ≠ subject or A ≠ B |
| **OPEN-BEHALF** | Type 0 **MAY** submit a grant for another login B; filename uses **B** | Type 0 submit | Forcing A=B or dying owner A ≠ subject B is **PP-A-18** |

### 3.4 What stays blocked (portable defaults)

| ID | What is stopped | Who / when |
|----|-----------------|------------|
| **PREV-T0-USER** | Create or delete the LPU (`useradd` / `userdel`) | Type 0 / ordinary login. An LSU (non-sudoer) **never** creates an account itself |
| **PREV-T1-EUID** | Any Type 1 verb without euid 0 | Any login |
| **PREV-APPR-LPU** | Approve / review as the LPU **euid** (no F6 re-entry) | LPU login without `sudo` |


Do **not** specialize a row named like **PREV-APPR-ACTOR** that stops an already euid-0 host admin whose `SUDO_USER` is not `{{LPU_USER}}`. That row **closes OPEN-ELEV / OPEN-SUDOER-APPR**.

### 3.5 Setup helps submit (when the product is an approval machine)

Type 1 `setup` **MUST**:

1. Be run by a **sudoer** (password `sudo` / already-root).  
2. Create the LPU (Type 0 / LSU **MUST NOT** `useradd`).  
3. **Help** a request get submitted in that same install/setup flow — at least print the submit next-step for the invoking sudoer (`SUDO_USER`). Do not invent a colleague grant body during setup. The next-step **may** name B.

### 3.6 Why this mold exists (CIAO)

- **Principle 2 – Intentional**: Block vs open is a written pair.  
- **Principle 9 – Three Types**: Type 1 after elev is not re-gated by a second principal.  
- **Principle 10 – Least privilege**: Size the job **before** elev. After elev, least privilege is not “invent who may finish.”  
- **Principle 1 / 20**: Fail closed on published rows; over-protect the **open** list so agents cannot lock the operator out (**PP-A-08** / **PP-A-17**).

## 4. Design principles

- **Caution**: Only published rows stop an action.  
- **Intentional**: Helpful file checks ≠ actor override.  
- **Anti-fragile**: Password `sudo` on a real host finishes the Type 1 job.  
- **Over-protect**: Adding a new block without revising this catalog is a privilege regression.

## Under command line for normal user only

When the ship unit detects a **command line for normal user only** (Termux, Git Bash, or the same class — term [`command-line-for-normal-user-only.md`](../../terminologies/command-line-for-normal-user-only.md)):

| MUST | MUST NOT |
|------|----------|
| Keep **normal user privilege** (Type 0) only | Implement or enable **admin privilege** (Type 1) or **dedicated system user privilege** (Type 2) |
| Document Type 1 **unused** and Type 2 **unused** | In-tool `sudo`; wrap `apt` / `dnf` / `yum`; write `/etc` dests; `useradd` / dedicated LPU; Type 2 `sudo -u` switch |
| Termux: named `pkg` as this login remains Type 0 (**`LM-SHELL-TERMUX-ISH`**) | Recommend `sudo curl \| sh` as the install path |
| Git Bash: same privilege ceiling | Invoke Termux `pkg` because Git Bash was detected |

Detect (typical): Termux — `PREFIX` contains `com.termux`; `TERMUX_VERSION` set; `/data/data/com.termux/files/usr` exists. Git Bash — `MSYSTEM` is `MINGW*` / `MSYS*` / `UCRT*` / `CLANG*`; `uname -s` is `MINGW*` / `MSYS*`. Windows cmd — `OS` is `Windows_NT` or `ComSpec`/`COMSPEC` names `cmd.exe` (after excluding Git Bash, Cygwin, WSL).

**This mold:** Type 1/2 unused is the prevention on that class; do not invent a Type 1 actor check there.

## 5. Protection Rule (Sacred)

**Future AI assistants or maintainers MUST NOT**:

1. Specialize **OPEN-ELEV** as “setup only” and then lock approve/review to `SUDO_USER=={{LPU_USER}}`.  
2. Add a **PREV-APPR-ACTOR**-shaped row (already euid 0, `SUDO_USER` not the LPU → fail) without the user ordering a **different** approval model **and** closing OPEN-SUDOER-APPR in the same change.  
3. Call that actor check “helpful checking.” It is blockage of approval.  
4. Let Type 0 / an LSU `useradd` the LPU.  
5. Invent a live-command whitelist or denylist, a Gap stub after elev, or a `LIVE_LPU` create flag.  
6. Use `--force` as the workaround for the actor wall.  
7. Embed **`RQ-*`** or one product’s LPU name as portable law (use `{{LPU_USER}}`).  
8. Cite this mold as product-source authority after specialize.  
9. Dump `docs/templates/**` / `docs/skills/**` / `docs/incidents/**` into versioned `docs/requirements/**`.  
10. Specialize **PREV-BEHALF** or treat A≠B as a convert/submit/approve wall (**PP-A-18**).  
11. Strip the **Under command line for normal user only** section, or invent a Type 1 actor check on that class.

**Violating this rule is a critical invented-wall / privilege regression** (`PP-A-08` · `PP-A-17` · `PP-A-18`).

## 6. How to specialize

1. Copy §3 catalogs into `requirement-privilege-prevention-set.md`. Fill `{{LPU_USER}}` / verb names in Implementation Notes.  
2. Keep OPEN-ELEV + OPEN-SUDOER-APPR + OPEN-DECIDE + OPEN-BEHALF + PREV-T0-USER. Do **not** specialize **PREV-BEHALF**.  
3. Point three-layer + domain authz tables at this catalog — **one** story.  
4. Register the requirement. Product source cites the live file.  
5. Prove with **TP-ELEV-09** / product **TP-PREV-03** (approve gate has no `SUDO_USER=={{LPU_USER}}` after euid 0).

## Design-time verification

| TP family | Proves | Status seed |
|-----------|--------|-------------|
| **TP-ELEV-08** | Bootstrap not `sudo -n`; not locked to the LPU setup creates | todo → have when Type 1 setup exists |
| **TP-ELEV-09** | Approve/review after euid 0 does **not** require `SUDO_USER=={{LPU_USER}}` (**T1-SECOND-LOCK**) | todo → have when approve verbs exist |
| **TP-PREV-01** | No Gap / invented create flag after euid 0 | todo → have |
| **TP-PREV-03** | Product alias of TP-ELEV-09 (static or live) | todo → have |

**Proof mold:** `../tests/template-shell-tty-privilege-test-plan.md` (**PM-SHELL-TTY-PRIVILEGE-TEST-PLAN**)  
**Gate:** **CL-LEAST-PRIVILEGE**

---

**Last Updated**: 2026-08-18  
**Owner**: {{OWNER}}  
**Alignment**: **`LM-THREE-LAYER-PRIVILEGE-MODEL`** · **`LM-LEAST-PRIVILEGE-USER`** · **`LM-FILE-BASED-JSON-APPROVAL`** · term `elev-is-approval` · term `approval-role-table` · **`PP-A-08`** / **`PP-A-17`** / **`PP-A-18`** · CIAO / CIAO-Lite
