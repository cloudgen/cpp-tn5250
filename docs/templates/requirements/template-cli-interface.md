---
name: cli-interface
id: LM-CLI-INTERFACE
kind: law-mold
description: >
  Portable law mold. Cite as LM-CLI-INTERFACE (path secondary).
---

**file**: template-cli-interface.md  
**Status**: Active (Version 1.13.0 – Type 0 `self-install` dispatcher examples)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered / Over-protect)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

## 1. Purpose

This template defines the portable **command-line interface** structure: command categories, privilege typing, global flags, dispatcher rules, help surface, and mode contracts for any CIAO-Lite CLI tool.

It is the reusable pattern for how users and automation interact with the tool. Privilege depth for multi-layer products aligns with the **Three-Layer Privilege Model** and **internal escalation** patterns where Type 1/2 exist.

**Specialize into:** a project `requirement-*-cli-interface.md` — shell `requirement-shell-cli-interface.md`, Python `requirement-python-cli-interface.md`, Node `requirement-nodejs-cli-interface.md`, or a future `requirement-<lang>-cli-interface.md`. Fill Implementation Notes (command table, flag wiring, dispatcher acceptance). Dual mention (§4.1) is **language-agnostic** and **MUST** be copied into every language-family CLI mold.

### 1.1 Empty argv (owned by type in zero-arg template)

| Product type (see `template-shell-cli-zero-arguments.md`) | Empty argv | Mandate |
|----------------------------------------------------------|------------|---------|
| **Type N — Non-online-install** (ops, library wrapper, package-only CLI) | **`help`** / usage | Default for general CLIs; this template aligns |
| **Type O — Online-install** (`curl … \| sh`) | **Install-ensure** (not help) for not-installed / local / global | **`template-online-install.md` §3.0a** + Type O rules in `template-shell-cli-zero-arguments.md` |

This CLI-interface template **MUST NOT** force Type O on every product. Classify and specialize the zero-arg template for the correct type.

When **`LM-CLI-DEFAULT-INTERACTION`** is claimed **and** a specialized zero-arg requirement exists, empty argv **stays** the table above; the numbered menu is intended command **`menu`** (`main` MAY alias) — list it on the command table with honest **Gap** until routed.

**Related templates:**

| Topic | Template |
|-------|----------|
| Empty argv Type O / Type N | `template-shell-cli-zero-arguments.md` |
| **Local** self-managed lifecycle (+ local version package) | `template-shell-local-self-management.md` |
| **Online** self-management lifecycle (remote version-check / self-update) | `template-self-management.md` |
| Online install channel | `template-online-install.md` |
| Interactive vs non-interactive | `template-interactive-vs-noninteractive.md` |
| Optional TTY main menu (claimed default function; case 3 = verb `menu`/`main`, not empty argv) | **`LM-CLI-DEFAULT-INTERACTION`** (menu choice **MUST NOT** `$()` a `read` helper — **do-not-capture-read** / **`PP-A-22`**) |
| Output SSOT | `template-output-requirements.md` |
| Idempotency | `template-idempotency.md` |
| Least privilege / three-layer | `template-least-privilege-user.md`, `template-three-layer-privilege-model.md` |
| **Python CLI surface** | **`LM-PYTHON-CLI-INTERFACE`** — inherits dual mention |
| **Node.js CLI surface** | **`LM-NODEJS-CLI-INTERFACE`** — inherits dual mention |

### 1.2 Local Type 0 package vs online Type 0 package

Agents **MUST** choose the lifecycle package that matches product law. Do not mix remote commands into a **non-online-installable** (alias **local-only**) specialization without dual-mode REQs.

| Package | Type 0 commands (typical) | Version feature |
|---------|---------------------------|-----------------|
| **Local self-managed** (`template-shell-local-self-management.md`) | **`install`**, **`uninstall`**, `where-is-me`, **`version` (local)**, `about`, `help` | Pair **`install`/`uninstall` only** — never `self-*` lifecycle names |
| **Online self-managed** (multi-template package) | `curl \| sh` / Type O / **`self-install`**; `version-check` / `self-update` / **`self-uninstall`**; `version` / `about` / `help` | Place/remove = **`self-install`/`self-uninstall`** (not bare `install`/`uninstall`) |

**Must not confuse (command pairs):**

| Mode | Place | Remove | Do not use |
|------|-------|--------|------------|
| **Local self-manageable** | `install` (terminal; no curl) | `uninstall` | `self-install`, `self-uninstall`, `self-update` |
| **Online self-manageable** | `self-install` / `curl \| sh` | `self-uninstall` | bare `install`/`uninstall` as CLI place/remove |

| Command / feature | Meaning |
|-------------------|---------|
| `version` | Always **local** ship-unit version report (`app_version`) |
| `version-check` | **Remote** compare against channel latest — online mode only |
| **`install` + `uninstall`** | **Local** self-manageable place/remove (no curl) |
| **`self-install` + `self-uninstall`** | **Online** self-manageable CLI pair — room for payload (terms `self-install` · `self-uninstall`) |
| `where-is-me` | Path report; implied by local self-managed |

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
| **Ship unit** | `docs/terminologies/ship-unit.md` | `identity-runtime` | Installable CLI artifact |
| **CLI dispatcher** | `docs/terminologies/cli-dispatcher.md` | `product-law` | Single post-bootstrap router; help is not this machine |
| **CLI routed-verb** | `docs/terminologies/cli-routed-verb.md` | `product-law` | Dispatcher-accepted command token; help is not a route |
| **Test-purpose verb** | `docs/terminologies/test-purpose-verb.md` | `product-law` | Unit-test routed-verb; local test folder; sudo wrap only chmod/chown of that folder |
| **Operational verb** | `docs/terminologies/operational-verb.md` | `product-law` | Routed-verb that runs the product; Type 0 operational ≠ Type 0 tester |
| **Well-known CLI verb** | `docs/terminologies/well-known-cli-verb.md` | `product-law` | Portable subcommand catalog; each token operational xor test-purpose |
| **CLI gap name** | `docs/terminologies/cli-gap-name.md` | `product-law` | Law-named token the dispatcher rejects; help silent; status Gap |
| **Type O empty argv** | `docs/terminologies/type-o-empty-argv.md` | `product-law` | Empty argv classification |
| **Shell CLI bootstrap** | `docs/terminologies/shell-cli-bootstrap.md` | `product-law` | Pipe must call main |
| **Interactive vs noninteractive** | `docs/terminologies/interactive-vs-noninteractive.md` | `runtime-mode` | TTY vs automation modes |

**SSOT types used:** `identity-runtime` · `meta-catalog` · `policy` · `product-law` · `runtime-mode`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Core Commands (Recommended Structure)

Every CIAO-Lite CLI **SHOULD** organize commands using **CIAO Principle 9** privilege types (0 / 1 / 2). **Not every product needs all types** — Type 0–only self-managed installers are valid.

| Category (UX label) | CIAO P9 type | Privilege Layer | Examples | Typical Flags |
|---------------------|--------------|-----------------|----------|---------------|
| **Local CLI lifecycle + diagnostics** | **Type 0** | Invoking user | `version` (**local**), `about`, `help`, `install` / `uninstall` / `where-is-me` (local self-managed) | `--json`, `--quiet`, `--debug`, `--force` |
| **Online self-management** (only if Active online law) | **Type 0** | Invoking user | `version-check`, `self-update`, `self-uninstall`, channel `install` | `--json`, `--quiet`, `--force` |
| **Host preparation** | **Type 1** | root / sudo (internal escalation) | `prerequisites`, `create-user`, `docker-install` | `--quiet`, `--json` |
| **App install under system user** | **Type 2** | Dedicated least-privilege system user | `install` (app), `configure` | `--project-dir`, `--force` |
| **App operations** (UX subgroup) | **Type 2** | Same dedicated system user | `start`, `stop`, `restart`, `status`, `update`, `backup`, `restore` | `--project-dir`, `--json` |

**Note:** Older docs labeled ops as “Type 3.” Under CIAO v2.10.2 there are **only three** privilege types (0/1/2). App **operations** remain **Type 2** privilege (dedicated system user), not a fifth class.

### 2.2 Verb purpose (orthogonal to Type 0/1/2)

Privilege Type answers **who may run**. **Purpose** answers **why the verb exists**. A Type 0 tester is still Type 0; Type does **not** mean “unit test.”

| Purpose | Job | Target | In-tool sudo | Examples |
|---------|-----|--------|--------------|----------|
| **Test-purpose** | **Unit test** of a product function | **Local test folder** (checkout fixtures; `--file` / `--root` under it) | **Only** the sudo-wrapping function for **chmod** / **chown** of that folder ([check before sudo](../../terminologies/check-before-sudo.md)). Skip sudo when this login already owns the path. **MUST NOT** sudo otherwise. | `fence-test`, `test-json-format`, **`rc-test`** (when any [shell-rc feature](../../terminologies/shell-rc-feature.md) is claimed — **`PP-A-24`**) |
| **Operational** | **Run the product** | Queues, dest, install, live review | Type-appropriate (Type 0 operational: no host write; Type 1: outer/in-tool elev as designed) | convert, submit, list, `setup`, `approve` |

**Help MUST** list test-purpose verbs **apart** from operational verbs (separate heading). Dual mention (§4.1) still applies to both classes.

**MUST NOT** treat a test-purpose verb as submit / dest review / `setup` / host install. **MUST NOT** grow operational steps onto a tester.

**Execution rules (core):**

1. Type 0 commands **MUST** run as the invoker without requiring a dedicated system user.  
2. Type 1 (when present) **MAY** use controlled internal escalation; normal users **MUST NOT** be forced to manually prefix every privileged sub-step as a permanent UX rule.  
3. Type 2 (when present) **MUST** run as the dedicated least-privilege system user (`{{SYSTEM_USER}}` / `{{APP_USER}}`).  
4. Privilege type for each command **MUST** be documented in help and in the specialized requirement’s Implementation Notes.  
5. Mixing Type 1 host bootstrap with Type 2 app toolchain in one confused install path is **forbidden**.

### 2.1 Why This Pattern Exists (Direct CIAO Alignment)

- **CIAO Principle 9 – Three Types of Commands** (https://github.com/cloudgen/ciao): Classify every command Type 0 / 1 / 2.  
- **CIAO Principle 10 – Least-Privilege User** (https://github.com/cloudgen/ciao): Dedicated user mechanics; setup vs routine ops.  
- **CIAO Principle 2 – Intentional** (https://github.com/cloudgen/ciao): Every command has a clearly documented execution context.  
- **CIAO Principle 1 – Caution** (https://github.com/cloudgen/ciao): Prevent privilege escalation mistakes and poor UX regressions.  
- **CIAO Principle 6 – Single Point of Entry** (https://github.com/cloudgen/ciao): One dispatcher SSOT.

---

## 3. Global Flags (Recommended)

| Flag | Env / state | Behavior |
|------|-------------|----------|
| `--quiet`, `-q` | `QUIET=1` | Suppress non-error human output; errors and fatal paths still visible |
| `--json` | `JSON=1` (implies quiet) | Machine-readable structured output; no human banner text |
| `--debug` | `DEBUG=1` | Extra diagnostics when designed (must not break JSON purity on stdout) |
| `--force` | Force/reinstall policy vars | Skip safe confirms or force reinstall only where documented; never silent security bypass |
| `--project-dir PATH` | Working dir (when Type 2/3) | Custom project/data directory |

Additional domain/feature flags **MAY** be added only when documented in the specialized requirement and wired in the dispatcher.

---

## 4. Dispatcher and entry rules (portable)

1. **Single entry:** A single main dispatcher **MUST** parse global flags and route commands. Language examples: POSIX `app_main`; Python `cli.main` / argparse / click; Node `index.js` / commander.  
2. **Unknown command:** **MUST** fail loudly with a clear error and pointer to `help` (via output SSOT). This is the **argv** path (proof **TP-CLI-06**). A TTY **menu** invalid choice is **not** an unknown command — that pick retries **this** menu layer (`out_error` + reprint; **MUST NOT** `out_die`). Law **`LM-CLI-DEFAULT-INTERACTION`** §4 item 8c. Proof **TP-CLI-19**.  
3. **Empty argv:** Follow Type O install-ensure or Type N help per zero-arg specialization — never invent a third meaning. Empty argv is **no command token after flag parse** (`LM-SHELL-CLI-ZERO-ARGUMENTS` §5.0): overlay flags (`--debug`, `--quiet`, `--force`) **MUST NOT** disqualify it. `--json` with no command **is** empty argv; **special case** = JSON help on TTY **and** off-TTY (not Type O ensure, not the TTY list). Decide empty argv **after** parse — **MUST NOT** use only `$# -eq 0` so `{{APP_NAME}} --debug` falls through to help.  
4. **Idempotent install skip:** Ensure-style install **MUST** no-op when already installed unless force/reinstall policy is set (`template-idempotency.md`).  
5. **No raw user I/O:** User-facing messages **MUST** go through the centralized output system (`template-output-requirements.md` or the language peer).  
6. **Help ↔ route sync:** Every listed command is routed; every routed command is listed.  
7. **Dual mention:** **MUST** follow §4.1 (all CLI languages).

### 4.1 Dual mention (all CLI languages — sacred)

Every routed product verb (subcommand, console-script action, or parser dest) **MUST** be named in **at least two** Active specialized `requirement-*.md` files:

| Mention | File | Owns |
|---------|------|------|
| **1. CLI-interface** | `requirement-shell-cli-interface` · `requirement-python-cli-interface` · `requirement-nodejs-cli-interface` · or `requirement-<lang>-cli-interface` | Dispatch / help honesty |
| **2. Topic-owner** | lifecycle, privilege, domain, vault, session/auth, request, actor, … | Behavior |

**MUST NOT** leave a verb only on the CLI-interface file. That file is rewritten per product and is not a portable inventory. Adding a verb to Implementation Notes **MUST** name it on the topic-owner REQ in the same change.

**Help code is not the second mention.** Runtime help catalogs (POSIX `app_help`, argparse/click help, Node Help singleton) are **usage-text** SSOT. They **MUST NOT** be counted as a requirement mention.

**Language family:** **`LM-PYTHON-CLI-INTERFACE`** and **`LM-NODEJS-CLI-INTERFACE`** **MUST** restate this section. A future `requirement-<lang>-cli-interface` **MUST** too. Dual mention is not a shell-only rule.

For shell one-liners: bootstrap **MUST** reach the dispatcher under `curl | sh` (no basename/`$0` APP_NAME gate that blocks stdin install).

---

## 5. Output and mode contracts (portable)

| Mode | Contract |
|------|----------|
| Human (default TTY) | Prefixed messages via output SSOT; colors only when TTY and not quiet/json |
| Quiet | Suppress info/success noise; still show errors / fatal |
| JSON | Force quiet; emit structured JSON; no mixed human lines on success path |
| Non-interactive | Never hang on prompts; use safe defaults or `--force`/env policy (`template-interactive-vs-noninteractive.md`) |

Destructive Type 0 actions (e.g. uninstall) **MUST** confirm when interactive unless force policy is set; non-interactive **MUST NOT** block on stdin (fail closed with `confirm_required` when confirm is required).

---

## 6. Help surface (portable)

`help` **MUST** list:

- Usage line  
- Every supported command with one-line purpose  
- Privilege category (at least Type 0 vs elevated vs system-user when those exist)  
- **Verb purpose:** when test-purpose verbs exist, list them under a **separate heading** from operational verbs (local test folder vs live product). **MUST NOT** mix `fence-test` / other testers into submit / review grouping.  
- Global flags  

In JSON mode, help **MUST NOT** dump long human text; return a short structured success/note object instead.

Help / about **MUST NOT** list optional install-path-only pins (e.g. `CHECKSUM`) when automatic companion integrity is the primary story (`template-automatic-checksum.md`).

### About diagnostics (portable)

`about` **MUST** print live session facts, not frozen host values.

| Field | Rule |
|-------|------|
| **`$DISPLAY`** (GUI / X11 products) | Print the live `${DISPLAY:-}` value (or unset). **MUST NOT** `: "${DISPLAY:=localhost:11.0}"` or any host display id as Config. **`PO-NO-HARDCODE`**. |
| **Repository / Install channel** | **Online-installable** products **MAY** show a live channel when `SCRIPT_URL` is the install SSOT. **Local-only** products **MUST NOT** productize **Repository:** or **Install channel:** rows in `about` (empty-channel text is not operator diagnostics). |

---

## 7. User Privilege & UX Policy (when Type 1+ present)

**Core UX Principle** (multi-layer products):

- Normal users **should** run most Type 1 commands without manually typing `sudo` when internal escalation is designed.  
- Never return an immediate hard error + exit for normal users on privileged commands as the only permanent UX.  
- After a dedicated system user is created, Type 2 and Type 3 operations execute under that user.

Type 0–only products document “no Type 1/2” in Implementation Notes and skip inventing a system user solely for binary lifecycle.

### 7.1 Host supervisor dispatch (optional)

When specialized **product law** claims a host service manager (for example systemd `systemctl`) for **existing** operational verbs:

| MUST | MUST NOT |
|------|----------|
| Invoke the manager **internally** from those verbs (`start` / `stop` / `restart` or the product equivalent) | Add a **routed verb** named after the manager |
| Fail closed without in-tool `sudo` when the manager needs a **root login** | Wrap `sudo`; `enable` / `disable` / `mask` unless product law names those verbs |
| Skip the manager on a **command line for normal user only** | Invoke `systemctl` because Termux, Git Bash, or Windows cmd was detected |
| Keep an OpenSSH-style (or other) fallback when the manager or unit is absent | Pretend a unit exists |

Specialize the unit-name probe, privilege, and human copy in the **domain** requirement. This mold only forbids a second dispatcher token.

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

**This mold:** command-table Type 1 / Type 2 rows stay unused on detect; do not add Type 1 verbs because Linux could have them later.

---

## 8. Protection Rule (Sacred)

**Future AI assistants, Grok, or maintainers MUST NOT**:

- Change command execution context notes to force manual `sudo` prefixing for normal users when internal escalation is the designed pattern.  
- Remove or weaken the internal escalation pattern where it is required.  
- Re-introduce immediate “error + exit” behavior for privileged commands when run by normal users (Type 1+ products).  
- Allow Type 2 or Type 3 commands to perform actions that require root without a controlled path.  
- Force Type O empty-argv install-ensure on Type N products (or force Type N help on Type O products) without explicit reclassification.  
- Break `--json` implies quiet and machine-oriented output.  
- Bypass the output SSOT for normal product messages.  
- Strip the **Under command line for normal user only** section, or enable Type 1/2 on Termux / Git Bash.  
- Document flags in help that the dispatcher does not parse.  
- Paste this template path into product source as behavioral authority — specialize and cite the live requirement instead.  
- Skip dual mention (§4.1) on Python, Node, or any other language-family CLI mold.  
- Treat a Help module / argparse help / `app_help` as the second requirement mention.  
- Mix **test-purpose** verbs into **operational** help grouping, or treat a tester as submit / dest review / `setup` / host install.  
- `sudo` on a test-purpose verb except the wrapping function for **chmod** / **chown** of the **local test folder** (check before sudo).  
- Add a routed verb named `systemctl` (or `enable-service`) when product law only allows **internal** supervisor dispatch; invoke `systemctl` on Termux / Git Bash / Windows cmd.

**Violating this rule is considered a critical regression.**

---

## 9. How to use this template

1. Keep under `docs/templates/requirements/`; specialize to `requirement-*-cli-interface.md` (shell / python / nodejs / `<lang>`) with a full command table and flag wiring.  
2. Classify empty-argv Type O vs Type N and specialize `template-shell-cli-zero-arguments.md` accordingly.  
3. Implement a single dispatcher; keep help and routing synchronized.  
4. Dual-mention every verb (§4.1) on the CLI REQ **and** the topic-owner REQ.  
5. Register the requirement in `docs/requirements/index.md` (requirement row only).  
6. Keep the Protection Rule and CIAO citations intact.  
7. Language-family molds (**`LM-PYTHON-CLI-INTERFACE`**, **`LM-NODEJS-CLI-INTERFACE`**) **MUST** keep §4.1 in their own words.

---


## Design-time verification

| TP family / ID | Proof mold | Planned suite |
|----------------|------------|---------------|
| **TP-CLI-01..04,06,07,11** core surface | `../tests/template-shell-cli-test-plan.md` | `tests/test_cli.sh` |
| **TP-CLI-05** storage (when shell storage claimed) | same | same |
| **TP-CLI-08** / **TP-U-01** nounset HOME | same + set-u plan | same |
| **TP-CLI-09** zero-arg fail loud | same | same |
| **TP-CLI-10** vendor init under set -u | same | optional / n/a if no path |
| **TP-CLI-12** out_json `@key` (when claimed) | same | same |
| **TP-CLI-14** dual mention (§4.1) | same | same — scan `requirement-*.md`, not help source |
| **TP-CLI-15** topic-owner invocation sample | same | same — `{{APP_NAME}} …` line on topic-owner, not table-only |
| Domain help verbs after specialize | product **`TP-<SUBJECT>-*`** (not **TP-DOM**) | domain suite |

**RTM:** `../tests/template-requirement-test-traceability.md`  
**Specialize status into:** product `reviews/test-plan.md` (have/todo).


**Last Updated**: 2026-09-17 (1.13.0: Type 0 `self-install` dispatcher; no product brand)  
**Owner**: CLI & User Experience Layer (Generalized Template)  
**Version history:**  
- **1.13.0** (2026-09-17): Example-sync Type 0 POSIX CLI — `self-install`/`install` → `inst_self_install`; empty argv → `inst_maybe_install` / `inst_self_install`; `app_help`/`app_version` sketches; drop frozen product name.  
- **1.12.0** (2026-09-13): TTY menu typo ≠ unknown argv; **TP-CLI-19**.  
- **1.11.0** (2026-09-12): Type 0 `app_main` sample — `rc-test` operands, empty-argv pointer to **`LM-SHELL-CLI-ZERO-ARGUMENTS`** §5.5b.  
- **1.10.2** (2026-09-09): When any shell-rc feature is claimed, dual-mention Type 0 **`rc-test --root`** (**`PP-A-24`**).  
- **1.10.1** (2026-09-07): `--json` with no command is 0-argv special case: JSON help on TTY and off-TTY.  
- **1.10.0** (2026-09-07): Empty argv after flag parse; overlay `--debug` follows 0-argv; `app_main` sketch no longer uses only `$# -eq 0`.  
- **1.8.1** (2026-08-23): Pointer to **`LM-CLI-DEFAULT-INTERACTION`**. When that mold is claimed **and** a specialized zero-arg REQ exists, empty argv stays the Type O/N table; the numbered menu is routed-verb **`menu`** (`main` MAY alias), listed with honest Gap until dispatched.  
- **1.8.0** (2026-08-21): §2.2 **test-purpose** vs **operational** verbs (orthogonal to Type 0/1/2). Help lists testers apart. Sudo wrap on testers only chmod/chown of the local test folder.  
- **1.7.0** (2026-08-18): `app_main` sketch shows dispatcher + routed-verb `case` + gap-name `*)` (example-sync from `SK-REVIEW-SKILLS`).  
- **1.6.0** (2026-08-18): Dual mention is language-agnostic; Python/Node molds inherit; help-code ≠ second REQ.  
- **1.5.0** (2026-08-18): Dual mention — every routed verb in ≥2 REQs (CLI + topic owner).  
- **1.4.0**: Local Type 0 package vs online; local version clarity.  
- **1.2.0** (2026-07-14): Dispatcher rules; `--debug`; Type 0 install/version-check examples; Type O/N empty-argv ownership; idempotency/output pointers; Type 0–only products allowed.  
- **1.1.0**: Empty argv Type O / Type N ownership pointer.  
- **1.0.0**: Initial privilege-typed command structure.  

**Alignment**: Peer templates in §1.1; **CIAO Principles 1, 2, 5, 8, 14, 18** (https://github.com/cloudgen/ciao); CIAO-Lite (https://github.com/cloudgen/ciao-lite).


---

## Example `app_*` surface (Type 0 shell CLI)

| Function | Role |
|----------|------|
| `app_main` | Single dispatcher: flags, empty-argv policy, command route |
| `app_help` | Human/JSON help |
| `app_version` | Local version |
| `app_about` | Diagnostics |

**Dispatch vars:** `COMMAND`, `QUIET`, `JSON`, `DEBUG`, `FORCE`, domain flags — [shell-cli-config-variables](../../terminologies/shell-cli-config-variables.md).

### `app_main` — Type 0 dispatcher (illustration — not product law)

Single **cli-dispatcher**. Tokens the `case` **accepts** are **cli-routed-verbs**. A law-named token **not** in this `case` is a **cli-gap-name** (help stays silent; status Gap). Help listing is **not** a route.

Empty-argv **body** (TTY confirm vs Type O ensure): **`LM-SHELL-CLI-ZERO-ARGUMENTS`** §5.5b. Place how: **`LM-SHELL-CLI-SELF-INSTALL`**. Optional numbered menu **read**: **`LM-CLI-DEFAULT-INTERACTION`**. `self-update` / `self-uninstall`: **`LM-SELF-MANAGEMENT`**. Optional `rc-test`: **`LM-PATH-AND-SHELL-SUPPORT`**.

```sh
app_main() {
    : "${APP_NAME:=app}"
    : "${QUIET:=0}" : "${JSON:=0}" : "${DEBUG:=0}" : "${FORCE:=0}"
    : "${FORCE_REINSTALL:=0}" : "${COMMAND:=}"
    : "${HOME:=/tmp}" : "${USERNAME:=unknown}"
    : "${XDG_CACHE_HOME:=${HOME}/.cache}"
    : "${STORAGE_DIR:=${XDG_CACHE_HOME}/${APP_NAME}-${USERNAME}}"
    EFFECTIVE_STORAGE_DIR=$(util_resolve_storage)
    export EFFECTIVE_STORAGE_DIR STORAGE_DIR
    export TMPDIR="${EFFECTIVE_STORAGE_DIR}"

    # Type O: empty argv before overlay flags still means CLI place (curl|sh).
    # Overlay-flag empty argv (COMMAND empty after parse): LM-SHELL-CLI-ZERO-ARGUMENTS §5.5b.
    if [ $# -eq 0 ]; then
        if [ "${JSON}" -eq 1 ] || [ "${QUIET}" -eq 1 ]; then
            inst_self_install
            exit $?
        elif inst_is_installed; then
            inst_self_install
            exit $?
        else
            inst_maybe_install
            exit $?
        fi
    fi

    while [ $# -gt 0 ]; do
        case "$1" in
            --debug) DEBUG=1 ;;
            --json) JSON=1; QUIET=1 ;;
            --quiet|-q) QUIET=1 ;;
            --force) FORCE=1; FORCE_REINSTALL=1 ;;
            version|about|help|version-check|self-update|self-uninstall|self-install|install)
                COMMAND="$1"
                ;;
            # Specializee MAY add domain verbs here (e.g. start|stop). Bootstrap Type 0: none.
            *)
                out_die "Unknown command or flag: $1. Next: ${APP_NAME} help"
                ;;
        esac
        shift
    done

    case "${COMMAND}" in
        help) app_help ;;
        version) app_version ;;
        about) app_about ;;
        self-install|install) inst_self_install ;;
        version-check) ver_check ;;
        self-update) inst_self_update ;;
        self-uninstall) inst_self_uninstall ;;
        *)
            out_die "Unknown command '${COMMAND}'. Next: ${APP_NAME} help"
            ;;
    esac
}

# Always: app_main "$@" at end of ship unit (no ${0##*/} APP_NAME gate — curl|sh).
```

### `app_version` / `app_help` (Type 0 sketches)

```sh
app_version() {
    : "${APP_NAME:=app}" : "${VERSION:=0.0.0}" : "${JSON:=0}"
    if [ "${JSON}" -eq 1 ]; then
        out_json "version" "" "app" "${APP_NAME}" "version" "${VERSION}"
    else
        out_info "${APP_NAME} version ${VERSION}"
    fi
}

app_help() {
    : "${APP_NAME:=app}" : "${JSON:=0}" : "${QUIET:=0}"
    if [ "${JSON}" -eq 1 ]; then
        out_json "success" "Help text available in human-readable mode." "command" "help"
        return 0
    fi
    [ "${QUIET}" -eq 1 ] && return 0
    out_info "Usage:"
    out_plain "  ${APP_NAME} [command] [options]"
    out_info "Self-Management (Type 0):"
    out_plain "  self-install         Place ${APP_NAME} (copy when \$0 is this file; pipe downloads)"
    out_plain "  install              Same as self-install (compatibility alias)"
    out_plain "  version              Show current version"
    out_plain "  about                Show diagnostics"
    out_plain "  version-check        Compare local vs remote VERSION"
    out_plain "  self-update          Replace from the channel"
    out_plain "  self-uninstall       Remove the managed binary"
    out_plain "  help                 Show this help"
    # Domain rows: specializee injection after Type 0. Testers (rc-test) apart if claimed.
}
```

When `rc-test` is claimed, help **MUST** list it under a heading **apart** from operational verbs. **MUST NOT** number `install` / `self-install` / `self-update` / `self-uninstall` / `rc-test` on a TTY main menu.

