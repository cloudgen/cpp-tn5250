---
name: shell-termux-ish
id: LM-SHELL-TERMUX-ISH
kind: law-mold
description: >
  Portable law mold. Cite as LM-SHELL-TERMUX-ISH (path secondary).
  Termux-like this-login pkg companion; never default-ban wrapping pkg;
  never wrap apt/dnf as a substitute.
---

**file**: template-shell-termux-ish.md  
**Mold-ID**: LM-SHELL-TERMUX-ISH  
**Status**: Active (Version 1.2.0)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered / Over-protect)

**Folder structure (policy):** [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

# Template: Shell Termux-ish (`pkg` companion)

## 1. Purpose

Portable law for POSIX `/bin/sh` products whose **first home** is **Termux-like userspace**. Wrapping **named** `pkg` ensure as this login **is in scope**. Harness and domain non-goals **MUST NOT** lump wrapping `pkg` with wrapping `apt`/`dnf`.

Specialize into `requirement-shell-termux-ish` when B is Termux-first **or** the stated purpose needs Termux packages. Domain REQ names **which** packages. This mold owns **detect / invoke / fail-closed / not-Type-1**.

**This mold is not product law.** After specialize, product source cites the live `requirement-shell-termux-ish`.

## 2. Terminologies

| Term | Path | SSOT type | Role |
|------|------|-----------|------|
| **Shell Termux-ish** | `docs/terminologies/shell-termux-ish.md` | `product-law` | Class: this-login `$PREFIX` `pkg` |
| **Intention** | `docs/terminologies/intention.md` | `meta-catalog` | Named purpose beats a generic package-wrap ban |
| **Type 0** | `docs/terminologies/type-0.md` | `product-law` | This login; Termux `pkg` stays here |
| **Command line for normal user only** | `docs/terminologies/command-line-for-normal-user-only.md` | `product-law` | Termux instance: Type 1/2 unused |
| **Termux** | `docs/terminologies/termux.md` | `product-law` | Instance detect |
| **Git Bash** | `docs/terminologies/git-bash.md` | `product-law` | Peer instance; **no** `pkg` |
| **Windows cmd** | `docs/terminologies/windows-cmd.md` | `product-law` | Peer instance; **no** `pkg` |
| **Type 1** | `docs/terminologies/type-1.md` | `product-law` | Linux `apt` / sudo / `/etc` — **not** Termux `pkg`; unused on this class |
| **Host-mutating domain** | `docs/terminologies/host-mutating-domain.md` | `product-law` | System packages; excludes userspace `pkg` |
| **Self-management** | `docs/terminologies/self-management.md` | `product-law` | CLI binary lifecycle; calls this companion |
| **Bootstrap specialize product** | `docs/terminologies/bootstrap-specialize-product.md` | `meta-catalog` | A→B must not ban `pkg` when B is this class |
| **Stay-honest** | `docs/terminologies/stay-honest.md` | `policy` | Do not pretend packages exist after `pkg` fail |
| **PRoot** | `docs/terminologies/proot.md` | `product-law` | User-space trampoline `pkg` may install |
| **PRoot exit hang** | `docs/terminologies/proot-exit-hang.md` | `product-law` | Guest already exited; PRoot still waits |
| **Least privilege** | `docs/terminologies/least-privilege.md` | `policy` | No sudo for Termux `pkg` |
| **Project templates** | `docs/terminologies/project-templates.md` | `meta-catalog` | What law molds are |
| **Docs folder structure** | `docs/terminologies/docs-folder-structure.md` | `policy` | Mold vs product law |
| **No-hardcode policy** | `docs/terminologies/no-hardcode-policy.md` | `policy` | Placeholders in this mold |
| **Dual policies** | `docs/terminologies/dual-policies.md` | `policy` | Complete named list after specialize |
| **SSOT catalog** | `docs/terminologies/ssot-catalog.md` | `meta-catalog` | Inventory |

**SSOT types used:** `product-law` · `policy` · `meta-catalog`

**Policies:** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-no-hardcode.md` · `docs/policies/policy-least-privilege.md` · **`PO-NON-EXPOSE-LOCAL-MACHINE`**

## 3. Core rules (portable)

### 3.1 When this mold applies

Specialize when **any** of:

- Product purpose names Termux (or Termux-like userspace) as first home.  
- Domain needs packages that Termux does not ship until `pkg`.  
- Agents would otherwise list wrapping `pkg` as a non-goal because Type 0 parents do not wrap `apt`.

**MUST NOT** skip this mold “because Type 0 / do not mix Type 1 host bootstrap into domain.” Termux `pkg` is **not** Type 1 host bootstrap.

### 3.2 Detect

Implementation Notes **MUST** name detect (typical, not exclusive):

| Signal | Meaning |
|--------|---------|
| `PREFIX` contains `com.termux` | Termux prefix |
| `TERMUX_VERSION` set | Termux environment |
| `/data/data/com.termux/files/usr` exists | Termux usr tree |

Off detect → **MUST NOT** call `pkg`; **MUST NOT** wrap `apt`/`dnf`/`yum`.

On Termux detect, Type 1 and Type 2 **MUST** stay unused (class **command line for normal user only**). Git Bash and Windows cmd are the same class; **MUST NOT** call `pkg` there.

### 3.3 Named package list

Implementation Notes **MUST** print a closed **package table**:

| Column | MUST |
|--------|------|
| Package | Exact `pkg` token (e.g. `openssh`) |
| Why | One line (daemon, auth helper, …) |
| Owner | Domain REQ that named it (or this file if no domain split) |

**MUST NOT** run unnamed / wildcard `pkg` ensure. “Not excluding `pkg`” **MUST NOT** mean every `pkg` subcommand (`upgrade`, unrelated `uninstall`, interactive `search`).

### 3.4 Invoke

| Host | MUST | MUST NOT |
|------|------|----------|
| **Termux-ish** | `pkg install -y {{PKG_LIST}}` (non-interactive). Quiet/json suppress pkg stdout | Hang on prompts; skip because the CLI binary is already placed |
| **Not Termux-ish** | No-op | Wrap `apt` / `dnf` / `yum` as a substitute |
| **`pkg` missing** | Fail closed; Next names the same `pkg install …` line | Pretend payloads are ready |
| **`pkg` non-zero** | Fail closed; same Next | Continue as success |

Call site is typically the install companion (and non-interactive empty-argv ensure). Interactive empty argv **MUST NOT** run package ensure as a side effect unless product law says otherwise.

### 3.5 Privilege fence

| Tool | Privilege | In this mold? |
|------|-----------|----------------|
| Termux `pkg` as this login into `$PREFIX` | Invoker (not Type 1) | **Yes** |
| Linux `apt`/`dnf`/`yum` | Type 1 host mutate | **No** |
| In-tool `sudo` | Separate mold **`LM-SHELL-SUDO-COMMAND`** | **No** |

### 3.6 Example helper (illustration — not product law)

```sh
termux_is_termux() {
    [ -n "${PREFIX:-}" ] && case "${PREFIX}" in *com.termux*) return 0 ;; esac
    [ -n "${TERMUX_VERSION:-}" ] && return 0
    [ -d /data/data/com.termux/files/usr ] && return 0
    return 1
}

termux_pkg_ensure() {
    termux_is_termux || return 0
    command -v pkg >/dev/null 2>&1 || return 1
    pkg install -y {{PKG_A}} {{PKG_B}}
}
```

Replace `{{PKG_A}}` / `{{PKG_B}}` in Implementation Notes. Prefix the live helper with the product domain prefix when specialized.

### 3.7 PRoot exit hang (when wrapping a Linux guest)

When this product runs a static Linux `ET_EXEC` through **PRoot** (term `proot` · hang class `proot-exit-hang`):

1. The guest may **already have exited** while PRoot stays in `do_wait`. **MUST NOT** diagnose leftover guest helpers as the root cause.  
2. One-shot (`-p` / `--single`) **MUST** dispatch: if `command -v proot` succeeds, use a **reaper** (guest death or idle stdout → kill only **new** `runsvdir` PIDs → SIGKILL PRoot if it still will not exit). If `proot` is **not** on PATH, run the **simple** one-shot.  
3. Leftover discovery **MUST** match **args / exe paths**. **MUST NOT** match truncated `comm`.  
4. Nested PRoot **MUST NOT** run (inner PRoot + guest → `ptrace_stop`).  
5. `--kill-on-exit` **MUST NOT** be treated as a guest-exit detector (`-k` is `--kernel-release`).

## 4. How to specialize

1. Create `requirement-shell-termux-ish` via **`SK-CREATE-SPECIFIC-REQUIREMENT`** (Termux-ish step).  
2. Fill Implementation Notes: detect, helper name, **named** package table, call site (`install` / empty-argv).  
3. Domain REQ names **which** packages and **MUST NOT** list wrapping `pkg` as a non-goal.  
4. CLI-interface REQ: Termux `pkg` is **not** a Type 1 verb. Dual mention `install` companion.  
5. Self-management REQ: orchestrator **calls** the helper; this REQ owns invoke contract.  
6. Class residual **points** here.  
7. Proof: **`PM-SHELL-TERMUX-ISH-TEST-PLAN`** (not-Termux: `pkg` not invoked; Termux mock: exact `pkg install -y …` argv).

## 5. Design-time verification

| Gate | Artifact |
|------|----------|
| Not Termux-ish: `pkg` not invoked | typical **TP-LC-15** family |
| Termux mock: `pkg install -y` + named list | typical **TP-LC-16** family |
| `pkg` fail / missing → fail closed | product suite **todo** unless already have |

## Under command line for normal user only

When the ship unit detects a **command line for normal user only** (Termux, Git Bash, Windows cmd, or the same class — term [`command-line-for-normal-user-only.md`](../../terminologies/command-line-for-normal-user-only.md)):

| MUST | MUST NOT |
|------|----------|
| Keep **normal user privilege** (Type 0) only | Implement or enable **admin privilege** (Type 1) or **dedicated system user privilege** (Type 2) |
| Document Type 1 **unused** and Type 2 **unused** | In-tool `sudo`; wrap `apt` / `dnf` / `yum`; write `/etc` dests; `useradd` / dedicated LPU; Type 2 `sudo -u` switch |
| Termux: named `pkg` as this login remains Type 0 (**this mold**) | Recommend `sudo curl \| sh` as the install path |
| Git Bash: same privilege ceiling | Invoke Termux `pkg` because Git Bash was detected |
| Windows cmd: same privilege ceiling | Invoke Termux `pkg` because Windows cmd was detected |

Detect (typical): Termux — `PREFIX` contains `com.termux`; `TERMUX_VERSION` set; `/data/data/com.termux/files/usr` exists. Git Bash — `MSYSTEM` is `MINGW*` / `MSYS*` / `UCRT*` / `CLANG*`; `uname -s` is `MINGW*` / `MSYS*`. Windows cmd — `OS` is `Windows_NT` or `ComSpec`/`COMSPEC` names `cmd.exe` (after excluding Git Bash, Cygwin, WSL).

**This mold:** `pkg` companion is Termux-only Type 0; Git Bash and Windows cmd are the same privilege class and **MUST NOT** call `pkg`. **MUST NOT** invoke `systemctl` on this class (a POSIX Linux host supervisor belongs on domain law, not here).

## 6. Protection Rule (Sacred)

**Future AI assistants MUST NOT**:

1. Treat wrapping Termux `pkg` as a default non-goal or as Type 1 host bootstrap.  
2. Equate Termux `pkg` with Linux `apt`/`dnf`/`yum`.  
3. Wrap Linux `apt` “because `pkg` is in scope.”  
4. Skip named `pkg` ensure because the CLI binary is already placed.  
5. Run unbounded `pkg` of unnamed packages.  
6. Claim this mold is product-source authority after specialize.  
7. Freeze one product’s package names as universal mold law.  
8. Strip the **Under command line for normal user only** section.  
9. Treat leftover guest helpers as the hang cause when the guest already exited, match leftovers by truncated `comm`, skip the reaper when `proot` is on PATH, or skip the simple one-shot when `proot` is absent.  
10. Invoke `systemctl` on Termux, Git Bash, or Windows cmd.

**Last Updated**: 2026-09-07  
**Owner**: {{OWNER}}  
**Alignment**: term `shell-termux-ish` · **`SK-CREATE-SPECIFIC-REQUIREMENT`** · **`SK-BOOTSTRAP-SPECIALIZE-PRODUCT`** · **`SK-WRITE-TEMPLATE`** · **`PO-STAY-IN-PROJECT-SSOT`** · CIAO / CIAO-Lite
