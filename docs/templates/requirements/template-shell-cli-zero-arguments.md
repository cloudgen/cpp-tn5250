---
name: shell-cli-zero-arguments
id: LM-SHELL-CLI-ZERO-ARGUMENTS
kind: law-mold
description: >
  Portable law mold. Cite as LM-SHELL-CLI-ZERO-ARGUMENTS (path secondary).
---

**file**: template-shell-cli-zero-arguments.md  
**Status**: Active (Version 3.6.0 – flags-only `--json` / `--quiet` follow the type: Type O ensure, Type N help)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

## 1. Purpose

This template is the portable **Single Source of Truth for empty-argv (no command token after flag parse) dispatcher behavior**. `argc == 0` is **one** form of empty argv; overlay global flags **do not** disqualify it. Products act differently by **distribution type** and, for Type O, by **payload depth**:

| Product type | Empty argv means | When it applies |
|--------------|------------------|-----------------|
| **Type O-S — Online script-alone** | **Ship-unit install-ensure** (not help) | One-liner places/updates the CLI binary only — see `template-online-install.md` |
| **Type O-P — Online payload installer** | **Combined ensure**: ship unit (self-install / non-interactive self-update) **+** payload/environment install | One-liner reduces steps to a full usable stack — term [`payload-installer`](../../terminologies/payload-installer.md); **primary mold** `template-payload-online-install.md` |
| **Type O** (umbrella) | Install-ensure (not help); depth = O-S or O-P | Any product that claims `curl … \| sh` |
| **Type N — Non-online-install** | **Help / usage** (not install) | Package-manager CLI, ops CLI, library wrapper, service CLI **without** one-liner ship unit |

Specialize into a project `requirement-*.md` (e.g. `requirement-shell-cli-zero-arguments.md`) and record **Type O-S**, **Type O-P**, or **Type N** in Implementation Notes. Product source cites the **requirement**, never this template.

**Terminologies:** [`type-o-empty-argv`](../../terminologies/type-o-empty-argv.md) · [`payload-installer`](../../terminologies/payload-installer.md) · [`online-install-script`](../../terminologies/online-install-script.md)

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
| **Type O empty argv** | `docs/terminologies/type-o-empty-argv.md` | `product-law` | Primary empty-argv law |
| **Payload installer** | `docs/terminologies/payload-installer.md` | `product-law` | Type O-P depth |
| **Online install script** | `docs/terminologies/online-install-script.md` | `install-channel` | One-liner surface |
| **Shell CLI bootstrap** | `docs/terminologies/shell-cli-bootstrap.md` | `product-law` | Pipe reaches main |

**SSOT types used:** `install-channel` · `meta-catalog` · `policy` · `product-law`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Type classification (mandatory first step)

### 2.1 How to classify (distribution)

| Signal | → Type |
|--------|--------|
| Product README / help documents `curl -fsSL … \| sh` (or sudo variant) as install | **Type O** (then classify O-S vs O-P) |
| Ship unit is a single-file installer intended to run from stdin pipe | **Type O** |
| `template-online-install.md` is specialized for this product | **Type O** |
| Binary is only obtained via apt/brew/npm/pip/docker, git clone, or manual download — **no** advertised one-liner install | **Type N** |
| Empty argv historically shows help and product has no install-from-pipe path | **Type N** |

### 2.1b How to classify (payload depth — Type O only)

| Signal | → Subclass |
|--------|------------|
| One-liner / empty argv only places the CLI binary; no required toolchain/package setup | **Type O-S (script-alone)** |
| Product purpose is to reduce install steps for an environment/stack (SDKMAN, Java, runtimes, packages, demo project, etc.) | **Type O-P (payload installer)** |
| README promises “installs X, Y, Z” or “ready-to-run environment” from one curl | **Type O-P** |
| Pure Type 0 self-managed CLI with no domain payload | **Type O-S** |

A product **MUST** pick **exactly one** primary distribution type (O or N). Type O products **MUST** also pick **O-S or O-P**. Hybrid products (rare): primary user-facing install path decides; document exceptions in Implementation Notes.

### 2.2 Authority split

| Template | Owns |
|----------|------|
| **This file** | Empty-argv rules for Type O-S, Type O-P, and Type N |
| **`template-online-install.md` §3.0a / §3.0b** | Makes Type O mandatory for online installers; §3.0b payload class; points here for depth |
| **`template-cli-interface.md`** | Command catalog / privilege — aligns with Type N default help unless product is Type O |
| **`LM-CLI-DEFAULT-INTERACTION`** | Optional TTY **main menu**. When a specialized zero-arg REQ exists (**case 3**), empty argv **stays this mold**; the menu is routed-verb **`menu`/`main`**. When no zero-arg REQ exists, that mold MAY own **interactive** empty argv; Type O **non-interactive** empty argv **stays** check / self-install here |
| **`template-interactive-vs-noninteractive.md`** | No-hang / prompt modes — does not override type classification |
| **`template-self-management.md`** | Post-install lifecycle commands — not empty-argv ownership (O-P may **reuse** self-update on empty argv) |
| **`template-idempotency.md`** | Already-installed / force reinstall semantics for ensure paths |
| Term [`payload-installer`](../../terminologies/payload-installer.md) | Shared name for Type O-P |

---

## 3. Terminology

| Term | Meaning |
|------|---------|
| **Zero-arg / empty argv** | After global-flag parse, **no command token** is present. Overlay flags (`--debug`, `--quiet`/`-q`, `--force`, and product `--global` when designed) **MUST NOT** count as “has argv”. `{{APP_NAME}} --debug` **MUST** follow the same empty-argv law as `{{APP_NAME}}` and as `DEBUG=1 {{APP_NAME}}`. `$# -eq 0` at entry is sufficient but **not** necessary. Type O classic: `curl … \| sh` with no trailing command. Type N classic: `{{APP_NAME}}` with no subcommand. |
| **Type O** | Online-install product type (one-liner distribution). Umbrella for O-S and O-P. |
| **Type O-S** | Script-alone: empty argv = **ship-unit** install-ensure only. |
| **Type O-P** | [Payload installer](../../terminologies/payload-installer.md): empty argv = ship-unit ensure **+** payload/environment ensure. |
| **Type N** | Non-online-install product type. |
| **Ship-unit install-ensure** | Converge to “managed binary present” (install or success no-op / update policy). |
| **Payload ensure** | Converge toolchains, packages, projects, or other product payloads (domain SSOT). **Type O-P.** |
| **Combined ensure** | Ship-unit layer then payload layer without requiring a second user invocation. **Type O-P.** |
| **Help-default** | Empty argv routes to usage / help. **Type N default** (not O-P). |
| **Not installed / Installed (local) / Installed (global)** | Detect cases used by Type O ship-unit matrix. |
| **`--force` / reinstall policy** | Deliberate re-download/replace of ship unit and/or payload reset per product law. |

---

## 4. Side-by-side summary (normative)

| Concern | Type O-S — Script-alone | Type O-P — Payload installer | Type N — Non-online |
|---------|-------------------------|------------------------------|---------------------|
| Empty argv intent | **Ship-unit install-ensure** | **Combined ensure** (self-install/update + payload) | **Help / usage** |
| Not installed | Install binary (TTY may confirm; non-TTY auto) | Install binary **then payload**; **MUST NOT** exit after binary only | Help; **MUST NOT** auto-install |
| Installed local/global | Success no-op “already installed”; **not** help | Non-interactive: **auto-upgrade ship unit when policy**; **always payload ensure**; **not** help | Help (normal CLI UX) |
| Explicit `help` | Always available | Always available | Often same as empty argv |
| Explicit `install` | Same as empty argv (if command exists) | Same combined path when designed | Optional; **not** empty argv |
| Pipe `curl \| sh` | Bootstrap **must** call main; loud outcome | Same + full payload on first and re-run | Not install surface; no silent invent |
| Failures | Install fail → non-zero; **no silent success** | Ship or payload fail → non-zero; **no silent success** | Help → exit 0 unless policy differs |
| Specialize requirement? | **Yes** if online install claimed | **Yes** (online + domain/payload law) | **Yes if** policy documented; else Type N help default |

---

## 5. Type O — Online-install rules (mandatory when Type O)

> Applies when §2 classifies the product as Type O (O-S or O-P).  
> Online install is **incomplete** without this section (`template-online-install.md` §3.0a).  
> Payload products **MUST** also satisfy §5.6 (Type O-P).

### 5.0 Empty argv is no command token (both types)

1. Empty argv **MUST** be decided **after** global-flag parse: **no command token** was present.  
2. Overlay flags (`--debug`, `--quiet`/`-q`, `--force`, product `--global` when designed) **MUST NOT** disqualify empty argv. `{{APP_NAME}} --debug` **MUST** match `DEBUG=1 {{APP_NAME}}`.  
3. The dispatcher **MUST NOT** use only `$# -eq 0` before parse so overlay flags fall through to default `COMMAND=help`.  
4. **`--json` and `--quiet` with no command (still empty argv):** those switches **are** empty argv and they **are non-interactive**, including on a TTY. **Type O** **MUST** run install-ensure (`inst_self_install` or the product ensure handler). **Type N** **MUST** run help (JSON help when `--json`). **MUST NOT** the TTY numbered list. **MUST NOT** a JSON-help special case that blocks Type O ensure. Distinct from interactive `menu --json`, which **MUST** still draw when a menu is claimed (force JSON and QUIET off while drawing; restore them before a leaf). Products **MUST** document this split.  
5. Explicit command tokens (`help`, `menu`, `install`, domain verbs) are never empty argv.

### 5.1 Single meaning of empty argv

1. Empty argv **MUST** mean **install-ensure** — not `help`, not unknown-command, not silent no-op — **off-TTY**. Overlay flags-only (`{{APP_NAME}} --debug`) **MUST** still follow empty argv. When a specialized zero-arg REQ **defers TTY empty argv** to **`LM-CLI-DEFAULT-INTERACTION`** (case 3 claimed menu), TTY empty argv **MUST** be the numbered list; off-TTY **MUST** remain Type O ensure.  
2. Explicit `help` **MUST** remain available when invoked.  
3. Empty argv **MUST NOT** fall through to default `COMMAND=help` after install-detect succeeds.  
4. Entry **MUST** reach the dispatcher under `curl | sh` (`$0` is often `sh` / `bash` — no basename-only gate on `{{APP_NAME}}`).  
5. Outcome **MUST** be loud: user-visible success or non-zero failure via output SSOT — never exit 0 with no message and no install.

### 5.2 Case matrix — Type O-S (script-alone)

| Case | Detect | Empty argv, force **off** | Force / reinstall **on** |
|------|--------|---------------------------|---------------------------|
| **A. Not installed** | Install-detect false | **Install** ship unit into privilege-correct path (§5.3) | First placement |
| **B. Installed — local** | `{{USER_BIN}}/{{APP_NAME}}` present | Success no-op: already installed; no re-download; **no help**; exit 0 | Re-download/replace (user path when non-root) |
| **C. Installed — global** | `{{GLOBAL_BIN}}/{{APP_NAME}}` present | Success no-op: already installed; no re-download; **no help**; exit 0 | Re-download/replace (global when root / elevated) |

**Cases B/C (force off, O-S):** human `out_success` already-installed; JSON structured success; tips **MAY** mention force/`self-update` — **MUST NOT** imply force is required for a normal one-liner re-run. Detect **MUST** cover both local and global when dual install is supported.

### 5.2b Case matrix — Type O-P (payload installer)

| Case | Detect | Empty argv, force **off** | Force / reinstall **on** |
|------|--------|---------------------------|---------------------------|
| **A. Not installed** | Install-detect false | Ship-unit install **then payload ensure** (toolchain/packages/project per domain SSOT). **MUST NOT** exit after binary place alone. | First placement + payload |
| **B. Installed — local** | Local managed binary present | (1) Non-interactive: **self-update / ship-unit upgrade** when remote newer or policy requires; (2) **Payload ensure** always. **MUST NOT** help. **MUST NOT** treat as binary-only success no-op. | Force ship-unit replace + payload force/reset per product |
| **C. Installed — global** | Global managed binary present | Same as B for global path | Same as B |

**Type O-P intent:** one-liner and bare empty argv **reduce installation steps** — combined **self-install / self-update + payload install**, not script-alone ensure.

### 5.3 Case A modes (not installed)

| Mode | Behavior |
|------|----------|
| Interactive (TTY, not quiet; not `--json`) | **MAY** confirm via prompt SSOT; yes → install; no → skip (not help) |
| Non-interactive (`curl \| sh`, non-TTY, CI) | **MUST** auto-install; never hang |
| Quiet (`--quiet`, no `--json`) | **MUST** install without prompts (still empty-argv ensure) |
| `--json` or `--quiet` with no command | Non-interactive empty argv (§5.0): **MUST** install. **MUST NOT** JSON help. **MUST NOT** the numbered list |
| Failure (network, checksum, I/O) | Non-zero exit; no fake success; no help-only output |

| Invoker | Target |
|---------|--------|
| root / `… \| sudo sh` | `{{GLOBAL_BIN}}/{{APP_NAME}}` |
| normal user | `{{USER_BIN}}/{{APP_NAME}}` |

### 5.4 Equivalence and forbidden outcomes (Type O)

| Invocation | Intent |
|------------|--------|
| Empty argv | Same ensure as `install` |
| `install` | Explicit ensure |
| `install --force` | Deliberate reinstall |
| `help` | Usage only — **not** empty-argv default |

| Forbidden | Why |
|-----------|-----|
| Full help when Case B or C | Looks broken; invents force dependency |
| Silent success when Case A should install | False confidence |
| Silent success when B/C with no already-installed message | Undebuggable retries |
| Blind re-download every empty-argv run | Breaks idempotency |
| Force required only because already installed | Force is replace, not ensure |
| Basename gate so pipe never reaches main | One-liner dead |

### 5.5 Detection (Type O)

1. Install-detect SSOT (e.g. `inst_is_installed` / version path).  
2. Dual path when designed (global + local).  
3. “Installed” = executable managed binary at recognized path (unless product documents PATH-based detect).

```text
Type O-S — empty argv
        │
        ▼
  install-detect
        │
        ├─ not installed ──► ship-unit install (TTY / auto / quiet|json)
        │                      root→global · user→local
        └─ installed ── force off ──► already installed (not help)
                     └ force on  ──► reinstall ship unit
```

### 5.5b Example: empty-argv split after flag parse (Type O + case-3 TTY menu)

**Kind:** [template-example-function](../../terminologies/template-example-function.md). **Not product law.**  
Place **how:** **`LM-SHELL-CLI-SELF-INSTALL`**. TTY confirm: **`LM-INTERACTIVE-VS-NONINTERACTIVE`** `inst_maybe_install`. Optional numbered menu: **`LM-CLI-DEFAULT-INTERACTION`**.

`COMMAND` empty means **no command token** after overlay flags. **MUST NOT** use only `$# -eq 0` before parse as the **sole** empty-argv detector (overlay `--debug` still Type O). A **bare** `$# -eq 0` block **MAY** still run first for classic `curl | sh` (no flags).

**Type O-S default (no numbered menu claimed):**

```sh
# Classic pipe / checkout with no argv (before flag parse).
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

# After global-flag parse. Overlay --debug / --quiet / --force / --json do not disqualify empty argv.
# --json or --quiet with no command is non-interactive Type O ensure.
if [ -z "${COMMAND}" ]; then
    inst_self_install
    exit $?
fi
```

**Optional case 3** (numbered TTY menu claimed): when `TTY=1` and `JSON=0` and `QUIET=0` and `COMMAND` is empty, call `app_cmd_menu` (current-shell `read`; **MUST NOT** `$()`). `--json` or `--quiet` with no command **MUST** stay `inst_self_install`, even on a TTY. **MUST NOT** send a pipe empty argv to that menu. Named `menu` / `main` off a terminal **MUST** `out_die` (`menu needs a terminal. Next: ${APP_NAME} help`). Interactive `menu --json` still draws.

**MUST NOT** `$()` `app_cmd_menu` / any `read` helper. **MUST NOT** send a pipe empty argv to the TTY menu.

### 5.6 Type O-P — Payload installer rules (mandatory when O-P)

> Term: [`payload-installer`](../../terminologies/payload-installer.md).  
> Online-install template **§3.0b** requires this when the product is a payload installer.

1. Empty argv **MUST** perform **combined ensure**: ship-unit layer then payload layer.  
2. First-time pipe **MUST NOT** stop after self-install of the ship unit when payload is product purpose.  
3. Non-interactive re-run **MUST** upgrade the ship unit when update policy says so (reuse self-update / install orchestrator), then ensure payload.  
4. Interactive re-run **MAY** skip auto-upgrade of the ship unit if policy documents TTY behavior, but **MUST** still payload-ensure (or document a single product exception).  
5. Payload steps **MUST** be idempotent (detect-then-ensure).  
6. Failures in either layer **MUST** exit non-zero with loud `out_*` messages.  
7. Implementation Notes **MUST** name O-P and cite domain/payload requirement for the payload list.

```text
Type O-P — empty argv
        │
        ▼
  bootstrap → dispatcher (always; no basename gate)
        │
        ├─ ship-unit: missing → install; present → non-interactive upgrade policy
        │
        └─ payload: ensure toolchains / packages / project / optional run
```

---

## 6. Type N — Non-online-install rules (default when Type N)

> Applies when §2 classifies the product as Type N.  
> Empty argv **MUST NOT** run install-ensure unless the product is reclassified to Type O.

### 6.1 Single meaning of empty argv

1. Empty argv **MUST** mean **help / usage** (or a documented short usage summary). Overlay flags-only (`{{APP_NAME}} --debug`) **MUST** still mean help under Type N.  
2. Empty argv **MUST NOT** download, install, or reinstall the binary.  
3. Empty argv **MUST NOT** require network or install channel (`SCRIPT_URL` / equivalent).  
4. Explicit `install` (if the product has that command for another purpose) **MUST** be invoked by name — never implied by empty argv.  
5. Interactive vs non-interactive: help still works without hang; JSON mode **MAY** return a short structured help/success object (not an install result).  
6. Empty-argv **shape** (no command token; overlay flags allowed, including `--json` and `--quiet`) is **§5.0** — Type N does not redefine it. Type N empty argv is help. That is not a special case that blocks Type O.

### 6.2 Case matrix (Type N)

| Situation | Empty argv (force off) | Notes |
|-----------|------------------------|-------|
| Binary not on PATH / “not installed” in product sense | **Help** (or usage) | Optional tip: how to install via package manager / docs — **not** silent auto-install |
| Binary present (any path) | **Help** | Normal CLI UX after package install |
| Quiet | Suppress non-error chatter; help body may be empty under quiet policy | Errors still visible |
| JSON | Short help/success object or documented schema | **Not** install-ensure JSON |

### 6.3 What Type N MUST NOT do

| Forbidden | Why |
|-----------|-----|
| Treat empty argv as install-ensure “because Type 0 exists” | Confuses ops CLIs with installers |
| Auto-run `curl` download or self-copy on empty argv | Unexpected mutation |
| Fail review because online-install Case A/B/C is “missing” | Wrong type |
| Copy Type O already-installed success no-op as empty-argv default | Users expect help |

### 6.4 Flow (Type N)

```text
Type N — empty argv
        │
        ▼
   help / usage
   (explicit help command may be identical)
        │
        └─ never install-detect → install path
```

---

## 7. Shared rules (both types)

1. User-facing messages **MUST** go through the project output SSOT (`out_*` or language equivalent).  
2. Non-interactive / quiet / json **MUST NOT** hang on prompts.  
3. Unknown commands (when a command token is present and unrecognized) still fail loud with pointer to help. Overlay flags without a command token are **empty argv**, not unknown.  
4. Explicit `help` always available when the product documents it.  
5. Product Implementation Notes **MUST** state **Type O-S**, **Type O-P**, or **Type N** (Type O alone is incomplete without O-S/O-P).  
6. Empty argv is **§5.0**: no command token after flag parse. Overlay flags do not disqualify. `--json` or `--quiet` with no command **is** non-interactive empty argv (Type O ensure; Type N help). **MUST NOT** the numbered list. **MUST NOT** a JSON-help special case that blocks Type O.

---

## 8. Why This Template Exists (Direct CIAO Alignment)

- **CIAO Principle 1 – Caution:** Type O retries must not look broken or silent; Type N must not mutate the system on bare invocation.  
- **CIAO Principle 2 – Intentional:** Empty argv has one meaning **per type** — O-S ship-unit ensure, O-P combined ensure, or N help — never ambiguous.  
- **CIAO Principle 3 – Anti-fragile:** Type O covers local/global and pipe; O-P covers full environment; Type N stays safe without network.  
- **CIAO Principle 5 – Single entry:** Dispatcher owns empty-argv branch for all types.  
- **CIAO Principle 16 – Interactive vs non-interactive:** No hang; Type O auto under pipe; O-P non-interactive upgrade policy.  
- **CIAO Principle 4 / CIAO-Lite O · Principle 20 – Over-protect / Protect Against AI:** Protection Rule blocks type confusion and O-P→O-S regressions.

---

## 9. Design Principles (CIAO / CIAO-Lite)

- **Caution:** Fail loud on real Type O install/payload errors; never surprise-install on Type N; never silent empty pipe success.  
- **Intentional:** Classify distribution **and** payload depth first; implement one empty-argv policy.  
- **Anti-fragile:** Type O dual-path detect; O-P second one-liner still converges environment.  
- **Over-protect:** Do not “simplify” Type O to help, Type N to auto-install, or Type O-P to binary-only exit.  
- **SSOT:** One dispatcher empty-argv branch switched by product type (or compile-time/product constants).

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

**This mold:** Type O empty-argv install-ensure stays Type 0; **MUST NOT** become a sudo/apt install path.

---

## 10. Protection Rule (Sacred)

**Future AI assistants, Grok, or maintainers MUST NOT**:

### Type confusion

1. Apply Type O install-ensure to a Type N product (or the reverse) without explicit reclassification and requirement change.  
2. Force Type O rules into general `template-cli-interface.md` / interactive templates as the only allowed empty-argv behavior.  
3. Claim “zero-arg always means install” or “zero-arg always means help” without stating product type.  
4. Collapse **Type O-P** into **Type O-S** (exit after binary place; no payload) when the product is a payload installer.  
5. Treat “online install” as sufficient law without stating **O-S vs O-P**.

### Type O (all)

6. Route empty argv to help when Type O and install/payload should run.  
7. Require `--force` solely because ship unit already installed (for normal ensure re-run).  
8. Handle only “not installed” and leave already-installed as help fallthrough.  
9. Detect only global **or** only local when dual install is supported.  
10. Blind reinstall ship unit every empty-argv run without force (O-S).  
11. Gate the only call to main on `${0##*/}` == `{{APP_NAME}}` under pipe.  
12. Exit **silent success** (no message, no binary, no error) for a claimed one-liner.

### Type O-P only

13. Exit after first-time ship-unit install without running payload ensure.  
14. Skip non-interactive ship-unit upgrade policy on one-liner re-runs when product requires auto-update as part of combined ensure.  
15. Document “already installed” binary no-op as full empty-argv success while payload was never ensured.

### Type N only

16. Auto-install, re-download, or mutate install paths on empty argv.  
17. Fail a Type N review for “missing” online-install Case A/B/C acceptance items.  

### Both

18. Bypass output SSOT for empty-argv user messages.  
19. Strip the **Under command line for normal user only** section, or turn Type O ensure into a sudo/apt install on that class.  
20. Treat overlay flags-only (`--debug`, `--quiet`/`-q`, `--force`) as help or as a third meaning — they **MUST** follow empty argv.  
21. Use only `$# -eq 0` / `argc == 0` before flag parse so `{{APP_NAME}} --debug` falls through to default `COMMAND=help`.  
22. Treat flags-only `--json` or `--quiet` as JSON help, or as the TTY numbered list, on a Type O product. They **are** non-interactive empty argv; the outcome is install-ensure.

**Violating Type O / O-P items on an online-install product is a critical one-liner regression. Violating Type N items is unexpected mutation / wrong UX.**

---

## 11. Acceptance criteria

### 11.1 Both types

- [ ] Implementation Notes state **Type O-S**, **Type O-P**, or **Type N**.  
- [ ] Empty-argv behavior matches the chosen type (§5 / §5.6 or §6).  
- [ ] Empty argv is no command token after flag parse (§5.0); `{{APP_NAME}} --debug` follows empty argv.  
- [ ] `--json` or `--quiet` with no command is non-interactive empty argv: Type O install-ensure; Type N help. **MUST NOT** the numbered list. **MUST NOT** a JSON-help special case that blocks Type O.  
- [ ] Explicit `help` works when documented.  
- [ ] No hang under quiet / json / non-TTY.  
- [ ] Output SSOT used for user-facing text; **no silent no-op one-liner**.

### 11.2 Type O-S only (script-alone)

- [ ] Empty argv + not installed → ship-unit install (modes per §5.3).  
- [ ] Empty argv + local/global installed + force off → already installed; not help.  
- [ ] Install failure → non-zero.  
- [ ] Force only for deliberate reinstall.  
- [ ] `curl \| sh` reaches dispatcher (bootstrap not basename-gated).  
- [ ] Aligned with `template-online-install.md` §3.0a.

### 11.2b Type O-P only (payload installer)

- [ ] All §11.2 ship-unit entry/bootstrap/loudness checks.  
- [ ] First empty argv / pipe when not installed → ship unit **and** payload ensure (no exit after binary only).  
- [ ] Empty argv when installed → payload ensure; non-interactive upgrade policy applied.  
- [ ] Not help; not pure binary “already installed” as sole outcome.  
- [ ] Aligned with `template-online-install.md` §3.0a + §3.0b and term `payload-installer`.  
- [ ] Domain/payload requirement cited for payload list.

### 11.3 Type N only (non-online-install)

- [ ] Empty argv → help/usage (human and JSON policy as designed).  
- [ ] Empty argv does **not** network-install or reinstall.  
- [ ] No requirement to pass online-install Case A/B/C ensure checks.

---

## 12. How to use this template

1. **Classify** product as Type O or Type N (§2); if Type O, classify **O-S or O-P** (§2.1b).  
2. Specialize to `docs/requirements/requirement-shell-cli-zero-arguments.md` (or equivalent) with Implementation Notes: type, handlers, paths, tests, payload list pointer.  
3. Register in `docs/requirements/index.md` when creating product law.  
4. **If Type O:** also specialize / align `template-online-install.md`; wire dispatcher ensure branch; regression tests for Case A failure + B/C behavior.  
5. **If Type O-P:** wire combined ensure; domain/payload requirement mandatory; first-pipe smoke proves binary **and** payload path entered.  
6. **If Type N:** wire empty argv → help; do not import Type O install matrix into code.  
7. Align peer product requirements only for the chosen type (do not rewrite the other type’s general templates).  
8. Product source cites the specialized **requirement** only.

---

## 13. Specialization sketch (Implementation Notes)

```text
Product type: Type O-S | Type O-P | Type N
APP_NAME: …
GLOBAL_BIN / USER_BIN: … (Type O dual install if any)
Payload (O-P only): … (cite domain requirement)
Dispatcher empty-argv:
  Type O-S → inst_perform_install / inst_maybe_install (ship unit only)
  Type O-P → ship-unit ensure (+ non-interactive self-update policy) then payload ensure
  Type N → app_help (or equivalent)
Tests:
  Type O-S → zero-arg not-installed fail; zero-arg already-installed not help
  Type O-P → first pipe installs binary + enters payload; re-run not help; loud failure
  Type N → zero-arg shows help; zero-arg no network install
  Curl silent class (Type O): specialize template-online-curl-install-test-plan.md (TP-CURL-*)
```

---


## Design-time verification

| TP family / ID | Proof mold | Planned suite |
|----------------|------------|---------------|
| **TP-CLI-09** zero-arg fail loud | `../tests/template-shell-cli-test-plan.md` | `tests/test_cli.sh` |
| **TP-LC-01** combined ensure | `../tests/template-install-lifecycle-test-plan.md` | `tests/test_install_lifecycle.sh` |
| **TP-LC-09** bad channel empty argv | same | same |
| **TP-CURL-*** one-liner silent class | `../tests/template-online-curl-install-test-plan.md` | `tests/test_online_curl_install.sh` |
| **TP-U-*** nounset (Type O) | `../tests/template-set-u-test-plan.md` | CLI + curl suite |
| Type O-P payload ensure | **TP-PAYLOAD-*** | domain/payload suite |
| Specialized domain (not payload) | **TP-<SUBJECT>-*** if domain SSOT | product domain suite |

**RTM:** `../tests/template-requirement-test-traceability.md`


**Last Updated**: 2026-09-30 (3.6.0: flags-only `--json` / `--quiet` follow the type — Type O ensure, Type N help)  
**Owner**: Shell CLI / Distribution Layer (Generalized Template)  
**Version history:**  
- **3.6.0** (2026-09-30): Flags-only `--json` / `--quiet` are non-interactive empty argv. Type O runs install-ensure. Type N runs help. No JSON-help special case that blocks Type O. Interactive `menu --json` still draws. Named `menu` off a terminal stops.  
- **3.5.0** (2026-09-17): §5.5b Type O-S default uses `inst_self_install` / `inst_maybe_install`; numbered menu is optional case 3.  
- **3.4.0** (2026-09-12): §5.5b empty-argv dispatcher sample — TTY menu vs Type O install-ensure.  
- **3.3.0** (2026-09-07): `--json` with no command **is** empty argv; special case = JSON help on TTY **and** off-TTY (not the list, not Type O ensure).  
- **3.2.0** (2026-09-07): Empty argv = **no command token** after flag parse (not only `argc == 0`). Overlay flags (`--debug`, `--quiet`, `--force`) follow empty argv. `--json` with no command **MAY** stay JSON help (not Type O ensure). Protection Rule 20–22.  
- **3.0.2** (2026-08-23): Related-templates pointer to **`LM-CLI-DEFAULT-INTERACTION`**. Case 3: empty argv stays this mold; the numbered menu is `menu`/`main`. Type O non-interactive empty argv stays check / self-install.  
- **3.0.1** (2026-07-24): Point Type O tests at `../tests/template-online-curl-install-test-plan.md` (TP-CURL silent class).  
- **3.0.0** (2026-07-20): Type O-S vs **Type O-P (payload installer)** axis; combined ensure; loud one-liner; term `payload-installer`.  
- **2.0.0** (2026-07-14): Dual-type model — Type O (online-install install-ensure) vs Type N (non-online-install help-default); side-by-side matrix; separate acceptance and protection rules.  
- **1.1.0** (2026-07-14): Scope: install-ensure only under online install.  
- **1.0.0** (2026-07-14): Initial Case A/B/C matrix (online-install only).  

**Alignment**: `template-online-install.md` §3.0a / §3.0b; `../tests/template-online-curl-install-test-plan.md`; term `payload-installer`; `template-cli-interface.md` / `template-interactive-vs-noninteractive.md` (Type N help-default); `template-idempotency.md`; CIAO Principles 1, 2, 3, 4, 6, 16, 20 (v2.10.2) (https://github.com/cloudgen/ciao)
