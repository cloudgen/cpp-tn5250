---
name: idempotency
id: LM-IDEMPOTENCY
kind: law-mold
description: >
  Portable law mold. Cite as LM-IDEMPOTENCY (path secondary).
---

**file**: template-idempotency.md  
**Status**: Active (Version 1.2.1 – PATH no-op is the exact line from `path_export_line`)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

## 1. Purpose

This template defines the portable **idempotency (re-run safety)** pattern for ensure-style operations: install, PATH integration, self-update, self-uninstall, prerequisites, and similar state-changing commands.

**Informal formula:** for ensure-style operation *f* and system state *x*, **f(f(x)) ≈ f(x)** for the **desired outcome** (logs and timestamps may differ).

**Shared language (terminology):**

| Term | File |
|------|------|
| **Idempotency rule** | `docs/terminologies/idempotency-rule.md` |
| Self-management | `docs/terminologies/self-management.md` |
| Finite state machine (when used) | `docs/terminologies/finite-state-machine-design.md` |

**Related templates (do not duplicate ownership):**

| Topic | Template |
|-------|----------|
| CLI command surface / flags | `template-cli-interface.md` |
| Self-management lifecycle | `template-self-management.md` |
| Empty argv Type O / Type N | `template-shell-cli-zero-arguments.md` |
| Online install | `template-online-install.md` |
| Output / messaging | `template-output-requirements.md` |
| Interactive vs non-interactive | `template-interactive-vs-noninteractive.md` |

**Specialize into:** a project `requirement-*-idempotency.md` (e.g. `requirement-shell-idempotency.md`) with filled Implementation Notes and a product command matrix.

---

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
| **Idempotency rule** | `docs/terminologies/idempotency-rule.md` | `product-law` | Re-run safety |
| **Type O empty argv** | `docs/terminologies/type-o-empty-argv.md` | `product-law` | Ensure re-runs |

**SSOT types used:** `meta-catalog` · `policy` · `product-law`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Core Concepts

| Concept | Meaning |
|---------|---------|
| **Ensure-style op** | Operation that drives the system toward a desired state (install, PATH ensure, update-to-latest, uninstall-to-absent) |
| **Detect** | Query whether the desired state already holds before mutating |
| **Already-achieved success** | When desired state holds: exit success / non-error path; do **not** fail “already exists” |
| **Force / reinstall override** | Explicit flag/policy that re-applies ensure work that would otherwise no-op — still subject to integrity and downgrade policy |
| **Fail closed** | Illegal inputs, missing channel when required, integrity failure, permission errors still fail — idempotency is not “never error” |

**Must not confuse with:**

| Concept | Not the same as |
|---------|-----------------|
| Idempotent ensure | “Never change anything” / immutability |
| Success no-op | Silent success on integrity or network failure |
| Force reinstall | Skip checksum/digest verification |
| Re-run safety | Continuous FSM thrash without edge detection (see FSM term when applicable) |

---

## 3. Core Rules (Mandatory when this pattern is claimed)

### 3.1 What must be idempotent

Every **state-changing** operation that **ensures** a desired configuration **MUST**:

1. **Detect** whether the desired state already holds.  
2. **Skip or no-op** unsafe work when it does.  
3. **Succeed** (exit 0 / non-error path) when already achieved — **MUST NOT** fail solely because state “already exists.”  
4. **Avoid duplicates** (binaries, PATH lines, config blocks, users, containers, resources).  
5. **Leave the system consistent** on every run (including after partial prior installs).  
6. **Communicate** clearly when already done in human mode; still respect quiet/json via the output SSOT.

### 3.2 What a second run must not do

| Forbidden when desired state already holds | Prefer |
|--------------------------------------------|--------|
| Fail with error solely because state exists | Success + “already installed / already latest / nothing to uninstall” |
| Create duplicate binaries, PATH lines, or config blocks | Existence / content checks first |
| Overwrite a correct install without force/reinstall intent | No-op unless force policy or newer-version policy requires replace |
| Thrash network downloads on every “already good” re-run | Skip download when no-op path taken |
| Leave half-applied state worse than start | Atomic steps; cleanup temps; fail loud with recovery path |

### 3.3 Already-achieved behavior (mandatory pattern)

When the desired state is already true:

| Requirement | Detail |
|-------------|--------|
| **Success** | Treat as success (CLI exit 0) |
| **Communicate** | State the current condition in non-quiet human mode |
| **Minimize work** | No unnecessary download, rewrite, or PATH append |
| **Output SSOT** | Use central `out_*` / `out_json` (or language equivalent); respect quiet/json |

### 3.4 Force / reinstall override (portable)

Force policy (e.g. `--force` / `FORCE_REINSTALL=1` / `{{FORCE_FLAG}}`) **MAY** re-apply ensure steps that would otherwise no-op **only** when:

- Documented on the command, and  
- Security checks (e.g. digest when downloading) still apply, and  
- Downgrade / destructive reinstall policy is explicit (not silent).

Force **MUST NOT** be used as a silent way to skip integrity verification.

### 3.5 Layers of application (portable)

| Layer | Idempotent means |
|-------|------------------|
| **CLI / installer** | install, PATH ensure, self-update, self-uninstall, prerequisites |
| **Empty argv (Type O)** | Already installed local/global → success no-op (not help, not blind reinstall) — see `template-shell-cli-zero-arguments.md` |
| **FSM (when used)** | Requested state already held → no-op / self-transition; side effects edge-triggered — see FSM term |
| **Partial failure** | Re-run converges or fails loud; does not pile fixed-name temps |

---

## 4. Specialization sketch (Implementation Notes)

When specializing, fill a **command-level matrix** for *this* product:

| Command / path | Desired state | Re-run when already good | Force / special |
|----------------|---------------|--------------------------|-----------------|
| `install` | Binary / package present | Success no-op | Force reinstall policy |
| Empty argv (Type O only) | Installed local or global | Success no-op “already installed” | Same as install |
| `self-update` | Local equals remote (or policy) | Success no-op “already latest” | Force reinstall; no silent downgrade |
| `self-uninstall` | Binary absent | Success no-op “not installed” | Force may skip confirm only |
| PATH ensure (`path_add_shell`) | The exact line from `path_export_line` (one-directory, or home bin then `/usr/local/bin` when `/bin` is ahead) **and** installer `VERSION` comments current | No rewrite of that exact line; no second copy of it. An older one-directory line stays; append the two-directory line once when it is absent | Create `BASHRC` when missing. Append on `.zshrc`, `.zshenv`, `.profile`, and Fish per **`LM-PATH-AND-SHELL-SUPPORT`**. Keep an existing body |
| PATH cleanup | Dir empty **or** lines already gone | No thrash; keep shared dir PATH | — |

Also record detect helpers, force vars, channel env, and concrete detect→act steps.

---

## 5. Why This Pattern Exists (Direct CIAO Alignment)

- **CIAO Principle 1 – Caution** (https://github.com/cloudgen/ciao): Assume re-runs, CI, scripts, and `curl | sh` retries; never fail “already exists” as if it were corruption.  
- **CIAO Principle 2 – Intentional** (https://github.com/cloudgen/ciao): Clear detect vs act vs force override.  
- **CIAO Principle 3 – Anti-fragile** (https://github.com/cloudgen/ciao): Converge from partial installs; tolerate second run after success.  
- **CIAO Principle 11 – Safe temporary file handling** (https://github.com/cloudgen/ciao): Temps cleaned so re-entry does not pile up or race on fixed names.  
- **CIAO Principle 12 – Backup & restore** (https://github.com/cloudgen/ciao): When ensure steps edit existing configs, backup-before-write remains required.  
- **CIAO Principle 4 / CIAO-Lite O · Principle 20 – Over-protect / Protect Against AI** (https://github.com/cloudgen/ciao): Existence checks and no-op success paths are Protection Zone material — not “simplify away.”

---

## 6. Design Principles (CIAO / CIAO-Lite)

- **Caution:** Prefer detect-before-create; fail closed on integrity and network when action is required.  
- **Intentional:** Separate already-done success from forced reinstall and from real failure.  
- **Anti-fragile:** Re-run after success is safe; re-run after partial failure converges or errors clearly.  
- **Over-protect:** Do not remove early-exit detect guards, PATH duplicate guards, or empty-dir PATH cleanup safety.  
- **SSOT:** One detect helper family per concern; messages via output SSOT.  
- **Output modes:** No-op success still honors quiet/json.

---

## Under command line for normal user only

When the ship unit detects a **command line for normal user only** (Termux, Git Bash, or the same class — term [`command-line-for-normal-user-only.md`](../../terminologies/command-line-for-normal-user-only.md)):

| MUST | MUST NOT |
|------|----------|
| Keep **normal user privilege** (Type 0) only | Implement or enable **admin privilege** (Type 1) or **dedicated system user privilege** (Type 2) |
| Document Type 1 **unused** and Type 2 **unused** | In-tool `sudo`; wrap `apt` / `dnf` / `yum`; write `/etc` dests; `useradd` / dedicated LPU; Type 2 `sudo -u` switch |
| Termux: named `pkg` as this login remains Type 0 (**`LM-SHELL-TERMUX-ISH`**) | Recommend `sudo curl \| sh` as the install path |
| Git Bash: same privilege ceiling | Invoke Termux `pkg` because Git Bash was detected |

Detect (typical): Termux — `PREFIX` contains `com.termux`; `TERMUX_VERSION` set; `/data/data/com.termux/files/usr` exists. Git Bash — `MSYSTEM` is `MINGW*` / `MSYS*` / `UCRT*` / `CLANG*`; `uname -s` is `MINGW*` / `MSYS*`. Windows cmd — `OS` is `Windows_NT` or `ComSpec`/`COMSPEC` names `cmd.exe` (after excluding Git Bash, Cygwin, WSL).

**This mold:** re-run ensure stays Type 0; **MUST NOT** wrap `apt` on a second run of that class.

---

## 7. Protection Rule (Sacred)

**Future AI assistants, Grok, or maintainers MUST NOT**:

1. Remove or weaken “already installed / already latest / nothing to uninstall” success paths so that re-runs fail when healthy.  
2. Make install always re-download when the target is already present without force/reinstall policy.  
3. Append duplicate PATH / config blocks on every re-run.  
3b. Claim bashrc PATH ensure without named tests for create-if-missing, modify dongle/existing, and no-op when `VERSION` + exact `export PATH=` already match (**TP-LC-20** / **TP-LC-21** / **TP-LC-22**).  
4. Strip shared bin directories from PATH when other tools still use them.  
5. Treat force as a way to skip checksum/digest verification.  
6. Fail uninstall solely because the tool is already absent (must be success no-op).  
7. Paper over missing remote version / channel as “already latest.”  
8. Weaken re-run safety rules without explicit project approval when specializing.  
9. Paste this template path into product source as behavioral authority — specialize and cite the live `requirement-*-idempotency.md` instead.

**Violating this rule is a critical re-run-safety regression.**

---

## 8. How to use this template

1. Keep this file under `docs/templates/requirements/`; specialize into a project `requirement-*-idempotency.md` when the product needs enforceable re-run law.  
2. Fill Implementation Notes with a **full command matrix** (no hollow “TBD” rows when claiming done).  
3. Align force flags with the CLI-interface specialization; align already-done messaging with the output specialization.  
4. Register the new requirement in `docs/requirements/index.md` (requirement row only — do not list this template path in the registry).  
5. Product source cites the specialized **requirement** only.

---


## Design-time verification

| TP family / ID | Proof mold | Planned suite |
|----------------|------------|---------------|
| **TP-LC-01,05,10** ensure re-run / already-latest / re-install | `../tests/template-install-lifecycle-test-plan.md` | `tests/test_install_lifecycle.sh` |
| **TP-LC-13,20,21,22** bashrc PATH: no duplicate; create-if-missing; modify dongle; VERSION+exact-PATH no-op | `../tests/template-install-lifecycle-test-plan.md` · **`LM-PATH-AND-SHELL-SUPPORT`** | `tests/test_install_lifecycle.sh` — **Core when bashrc PATH ensure is claimed** |
| **TP-CURL-03** second pipe | `../tests/template-online-curl-install-test-plan.md` | curl suite |

**RTM:** `../tests/template-requirement-test-traceability.md`


**Last Updated**: 2026-09-29 (1.2.1 — PATH ensure no-op is `path_export_line`, including the two-directory line)  
**Owner**: Lifecycle / Ensure-ops Layer (Generalized Template)  
**Alignment**: `docs/terminologies/idempotency-rule.md`; peer templates in §1; **CIAO Principles 1, 2, 3, 4, 11, 12, 20 (v2.10.2)** (https://github.com/cloudgen/ciao); CIAO-Lite (https://github.com/cloudgen/ciao-lite).
