---
name: shell-sudo-command
id: LM-SHELL-SUDO-COMMAND
kind: law-mold
description: >
  Portable law mold. Cite as LM-SHELL-SUDO-COMMAND (path secondary).
  In-tool sudo wrap, check before sudo (C0–C6), studied sudo allow table.
---

**file**: template-shell-sudo-command.md  
**Mold-ID**: LM-SHELL-SUDO-COMMAND  
**Status**: Active (Version 1.2.0)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered / Over-protect)

**Folder structure (policy):** [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

# Template: Shell in-tool sudo command

## 1. Purpose

Portable law for **in-tool sudo**: one wrapping function, **check before sudo**, and a **studied sudo allow table** (what argv is allowed — no guessing dest or operands).

Specialize into `requirement-shell-sudo-command` when the ship unit invokes `sudo`. Coding-style REQ **points** here. **`LM-SHELL-SCRIPT-CODING` §8.3** keeps the chmod **example**. This mold owns the wrap, C0–C6, and allow-table **rules**. **Complete sudoer CLI + emit/wrap samples** (print-sudoers, generate JSON, `util_sudo` with `sudo -n`): **`LM-SHELL-SUDOER`**. Elev deposit that **uses** the wrap: **`LM-SHELL-CONFIG-BACKUP`** (depends on **`LM-SHELL-SUDOER`**). **MUST NOT** duplicate those samples here.

**This mold is not product law.** After specialize, product source cites the live `requirement-shell-sudo-command`.

## 2. Terminologies

| Term | Path | SSOT type | Role |
|------|------|-----------|------|
| **Project templates** | `docs/terminologies/project-templates.md` | `meta-catalog` | What law molds are; specialize-out target |
| **Docs folder structure** | `docs/terminologies/docs-folder-structure.md` | `policy` | Where this mold lives vs product law / tests |
| **No-hardcode policy** | `docs/terminologies/no-hardcode-policy.md` | `policy` | Placeholders only in portable molds |
| **Dual policies** | `docs/terminologies/dual-policies.md` | `policy` | No-placeholder × no-hardcode balance |
| **Terminology policy for templates** | `docs/terminologies/terminology-policy-for-templates.md` | `policy` | Mandatory Terminologies section rules |
| **SSOT-terminology policy for templates** | `docs/terminologies/ssot-terminology-policy-for-templates.md` | `policy` | SSOT type column on rows |
| **Sudo-wrapping function** | `docs/terminologies/sudo-wrapping-function.md` | `product-law` | Only in-tool `sudo` call site |
| **Check before sudo** | `docs/terminologies/check-before-sudo.md` | `runtime-reliability` | Non-sudo probe; skip sudo on match |
| **Sudoers fragment** | `docs/terminologies/sudoers-fragment.md` | `product-law` | Studied Cmnd text |
| **Project-sudoers-file** | `docs/terminologies/project-sudoers-file.md` | `product-law` | Installed dest family |
| **Sudoers exact argv** | `docs/terminologies/sudoers-exact-argv.md` | `product-law` | Verb-only ≠ `verb *` |
| **Three-layer privilege** | `docs/terminologies/three-layer-privilege.md` | `product-law` | Type map; `sudo -n` not suggested |
| **No retest TTY** | `docs/terminologies/no-retest-tty.md` | `runtime-reliability` | Measure `[ -t` outside functions |
| **Shell TTY / privilege traps** | `docs/terminologies/shell-tty-privilege-traps.md` | `runtime-reliability` | T1-N-POLLUTE / T1-HANG |
| **Elev is approval** | `docs/terminologies/elev-is-approval.md` | `product-law` | No second lock after password sudo |
| **Least privilege** | `docs/terminologies/least-privilege.md` | `policy` | Minimum elev |
| **LLM escape** | `docs/terminologies/llm-escape.md` | `policy` | Broad sudoers / OS-tool probe |
| **Coding-style requirement** | `docs/terminologies/coding-style-requirement.md` | `product-law` | Points at the specialized sudo-command REQ |
| **SSOT catalog** | `docs/terminologies/ssot-catalog.md` | `meta-catalog` | Inventory |

**SSOT types used:** `product-law` · `runtime-reliability` · `policy` · `meta-catalog`

**Policies:** `docs/policies/policy-least-privilege.md` · `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-no-hardcode.md` · **`PO-NON-EXPOSE-LOCAL-MACHINE`**

## 3. Core rules (portable)

### 3.1 Wrap + C0–C6 (from **`LM-SHELL-SCRIPT-CODING` §8.3**)

| # | Rule |
|---|------|
| **C0** | Class: every in-tool `sudo <cmd>`. chmod is the **example** on the coding-style mold, not the only case. |
| **C1** | Probe with a **non-sudo** command. Probe is **case-specific**. chmod example: `[ -O path ]`. Compose sibling `backup`: already-root (`id -u` = 0). **MUST NOT** use `[ -O dest]` to skip a deposit that still needs root. |
| **C2** | If the probe **matches** (this login already can): **MUST NOT** `sudo`. |
| **C3** | `sudo <cmd>` **MAY** run only when the probe **misses**. **MUST NOT** default to `sudo -n` (**T1-N-POLLUTE**) unless the allow table row is NOPASSWD and matches the **full argv**. |
| **C4** | **MUST NOT** probe with `sudo` (`sudo true`, `sudo ls`, `sudo stat`, `sudo mkdir`, `sudo cp`). |
| **C5** | Already-root **MUST** run the argv without `sudo`. |
| **C6** | In-tool `sudo` **MUST** go through one [sudo-wrapping function](../../terminologies/sudo-wrapping-function.md) (typical `util_sudo`). **MUST NOT** scatter raw `sudo`. |

### 3.2 Sudo allow table (studied — no guessing)

When this product wraps `sudo` or gates on a sibling grant, Implementation Notes **MUST** print:

| Column | MUST |
|--------|------|
| Binary | Absolute managed path |
| Verb | Exact token |
| Operand | `sudoers(5)` match: `*` / none / one bound path |
| Fragment dest | From sibling/product `print-sudoers` (typical `/etc/sudoers.d/{{APP_NAME}}-{{username}}`) |
| NOPASSWD? | yes / no as studied |
| This wrap? | **yes** only for argv this ship unit may pass to the wrap |
| Study evidence | `print-sudoers` and/or readable fragment and/or `sudo -n -l`. Installed / `-l` win over a wider emit |

**MUST NOT** guess dest as `/etc/{{username}}/{{service}}` when `print-sudoers` installs `/etc/sudoers.d/{{APP_NAME}}-{{username}}`. **MUST NOT** treat a missing guessed path as verb-only.

### 3.3 Runtime (`LM-THREE-LAYER-PRIVILEGE-MODEL` §2.3.6)

| Rule | Detail |
|------|--------|
| **`sudo -n`** | Not suggested. **Only** when the allow table names NOPASSWD for that full argv. Else password `sudo` on TTY, or fail closed off-TTY / `--json`. |
| **This product emit** | If this CLI does **not** emit sudoers: **MUST NOT** write `/etc`. Compose sibling `print-sudoers`. **`CL-CREATE-SUDOERS-SECURITY`** / **`CL-SUDOERS-FILE-CONTENT`** are **N/A**. |
| **Proof** | Operate the allow-table argv. Not `sudo -n true`. |

### 3.4 Example wrap (illustration — not product law)

```sh
util_sudo() {
    if [ "$(id -u 2>/dev/null || echo 1)" -eq 0 ]; then
        "$@"
        return $?
    fi
    command -v sudo >/dev/null 2>&1 || return 1
    sudo "$@"
}
```

NOPASSWD matching the allow table **MAY** use `sudo -n` on that argv only. JSON / off-TTY without that row **MUST** fail closed (no hang).

## 4. How to specialize

1. Create `requirement-shell-sudo-command` via **`SK-CREATE-SPECIFIC-REQUIREMENT` step 22**.  
2. Fill Implementation Notes: wrap name, caller, **studied** allow table.  
3. Coding-style REQ **points**. Class residual **points**.  
4. Checklists: **`CL-LEAST-PRIVILEGE`** · **`CL-SHELL-TTY-PRIVILEGE-TRAPS`**. Emit checklists N/A when this CLI does not write fragments.

## 5. Design-time verification

| Gate | Artifact |
|------|----------|
| Wrap + allow table | product suite (typical TP family for grant-too-narrow / sibling dest / unproven) |
| TTY / `-n` / no hang | **`CL-SHELL-TTY-PRIVILEGE-TRAPS`** · **`PM-SHELL-TTY-PRIVILEGE-TEST-PLAN`** when Type 1 password sudo is claimed |
| Least privilege | **`CL-LEAST-PRIVILEGE`** |
| Emit (only if this CLI prints/installs sudoers) | **`CL-CREATE-SUDOERS-SECURITY`** · **`CL-SUDOERS-FILE-CONTENT`** |

## Under command line for normal user only

When the ship unit detects a **command line for normal user only** (Termux, Git Bash, or the same class — term [`command-line-for-normal-user-only.md`](../../terminologies/command-line-for-normal-user-only.md)):

| MUST | MUST NOT |
|------|----------|
| Keep **normal user privilege** (Type 0) only | Implement or enable **admin privilege** (Type 1) or **dedicated system user privilege** (Type 2) |
| Document Type 1 **unused** and Type 2 **unused** | In-tool `sudo`; wrap `apt` / `dnf` / `yum`; write `/etc` dests; `useradd` / dedicated LPU; Type 2 `sudo -u` switch |
| Termux: named `pkg` as this login remains Type 0 (**`LM-SHELL-TERMUX-ISH`**) | Recommend `sudo curl \| sh` as the install path |
| Git Bash: same privilege ceiling | Invoke Termux `pkg` because Git Bash was detected |

Detect (typical): Termux — `PREFIX` contains `com.termux`; `TERMUX_VERSION` set; `/data/data/com.termux/files/usr` exists. Git Bash — `MSYSTEM` is `MINGW*` / `MSYS*` / `UCRT*` / `CLANG*`; `uname -s` is `MINGW*` / `MSYS*`. Windows cmd — `OS` is `Windows_NT` or `ComSpec`/`COMSPEC` names `cmd.exe` (after excluding Git Bash, Cygwin, WSL).

**This mold:** do **not** specialize an Active in-tool sudo wrap when that class is the product’s ceiling. Type 1 unused → this mold is N/A.

## 6. Protection Rule (Sacred)

Future agents **MUST NOT**:

1. Scatter in-tool `sudo` outside the wrapping function.  
2. Skip C1–C5 (probe / already-can / already-root).  
3. Default to `sudo -n` without a matching NOPASSWD allow-table row (**T1-N-POLLUTE**).  
4. Probe `sudo true` / `mkdir` / `cp` / `ls` / `stat`.  
5. Guess fragment dest or argv.  
6. Mark **This wrap? = yes** for a sibling verb this CLI does not invoke.  
7. Use `[ -O dest]` to skip sudo of a deposit that still needs root.  
8. Treat this mold as product-source authority.  
9. Strip the **Under command line for normal user only** section, or specialize an Active wrap on Termux / Git Bash.

**Last Updated**: 2026-09-12  
**Owner**: {{OWNER}}  
**Version history:**  
- **1.2.0** (2026-09-12): Complete sudoer CLI samples live on **`LM-SHELL-SUDOER`**; this mold keeps wrap/C0–C6. Config deposit depends on that mold.  
- **1.1.0** (2026-09-05): Named section **Under command line for normal user only** — wrap mold is N/A on that class.  
- **1.0.1** (2026-09-02): Bind mandatory mold terms (`project-templates` · `docs-folder-structure` · no-hardcode · dual policies).  
- **1.0.0** (2026-09-02): Dedicated in-tool sudo mold — C0–C6, studied allow table, three-layer §2.3.6, checklist gates.

**Alignment**:  
- **`PO-STAY-IN-PROJECT-SSOT`**  
- **`LM-SHELL-SCRIPT-CODING`** §8.3 · **`LM-THREE-LAYER-PRIVILEGE-MODEL`** §2.3.6 · **`LM-FILE-MODES-UMASK`** U10  
- **`CL-LEAST-PRIVILEGE`** · **`CL-SHELL-TTY-PRIVILEGE-TRAPS`** · **`CL-CREATE-SUDOERS-SECURITY`** (emit only) · **`CL-SUDOERS-FILE-CONTENT`** (emit only)  
- Terms `sudo-wrapping-function` · `check-before-sudo` · `sudoers-exact-argv` · `project-sudoers-file`  
- [CIAO](https://github.com/cloudgen/ciao) **v2.10.2** / CIAO-Lite
