---
name: cli-default-interaction
id: LM-CLI-DEFAULT-INTERACTION
kind: law-mold
description: >
  Portable law mold. Cite as LM-CLI-DEFAULT-INTERACTION (path secondary).
  Optional TTY main menu when a software-dev CLI claims a default function.
  Three cases: no zero-arg + online-installable; no zero-arg + not
  online-installable; zero-arg exists → menu is verb menu/main.
  Menu labels = cli-routed-verb-table human-readable
  ({{short-descript}}: {{explain}}). MUST NOT list install/setup,
  self-managed, version/about, or test-purpose verbs.
---

**file**: template-cli-default-interaction.md  
**Mold-ID**: LM-CLI-DEFAULT-INTERACTION  
**Status**: Active (Version 1.25.0 – flags-only `--json` follows the zero-arguments mold; named menu off a terminal stops; a populated data picker still prints 0 Back)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered / Over-protect)

**Folder structure (policy):** [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

## 1. Purpose

This mold is the portable pattern for an optional **CLI default interaction** when a **software-development** CLI **claims a default function**. Menu **choice text** **MUST** be the **human-readable** column of the [CLI routed-verb table](../../terminologies/cli-routed-verb-table.md): **`{{short-descript}}: {{explain}}`**, where **short description** **is** the routed-verb. The **front board** **MUST NOT** list **install / setup**, **self-managed** routed-verbs, **diagnostics** (`version`, `about`), or **any test-purpose** verb. Those tokens **MAY** appear only on a **self-management submenu** (parent **8**, children **81…**) when the [CLI main menu hierarchy table](../../terminologies/cli-main-menu-hierarchy-table.md) claims that category. Test-purpose stays off **every** numbered list. When nested, numbers **MUST** follow [CLI main menu numbering](../../terminologies/cli-main-menu-numbering.md). A **data picker** prints item indexes **1…N** and **0** Back. **0**, an empty line, or EOF returns to the parent. An unknown token on a populated picker reprints that picker. **MUST NOT** `out_die` for Back or for that token. An empty live set stays product law. Each row **MUST** be **number** + **bold** short + *italic* long ([default CLI main menu style](../../terminologies/default-cli-main-menu-style.md); also called **default menu style**).

**Where the menu attaches** **MUST** follow the three cases in §3. Empty argv Type O vs Type N stays **`LM-SHELL-CLI-ZERO-ARGUMENTS`**.

**Specialize into:** `requirement-shell-cli-default-interaction.md` (or `requirement-<lang>-cli-default-interaction.md`). Product source cites the **requirement**, never this template.

**Does not own:** Type O vs Type N empty argv when a specialized zero-arg REQ exists (**`LM-SHELL-CLI-ZERO-ARGUMENTS`**); help body (**`LM-CLI-INTERFACE`**); TTY measurement (**`LM-INTERACTIVE-VS-NONINTERACTIVE`** / term `no-retest-tty`). **Does own:** menu **choice `read` call shape** (term **do-not-capture-read**).

### 1.1 Related molds

| Topic | Mold-ID |
|-------|---------|
| Command catalog / dispatcher | **`LM-CLI-INTERFACE`** |
| Empty argv Type O / Type N | **`LM-SHELL-CLI-ZERO-ARGUMENTS`** |
| TTY vs automation / no hang | **`LM-INTERACTIVE-VS-NONINTERACTIVE`** |
| Do not `$()` `read` helpers | **`LM-SHELL-SCRIPT-CODING` §8.1.5** · term **do-not-capture-read** |
| Output | **`LM-OUTPUT-REQUIREMENTS`** |

---

## Terminologies

Related glossary entries (disk-truth). Templates **point**; they do not redefine terms or act as product law.

| Term | Path | SSOT type | Role |
|------|------|-----------|------|
| **CLI default interaction** | `docs/terminologies/cli-default-interaction.md` | `product-law` | This pattern’s word |
| **CLI routed-verb table** | `docs/terminologies/cli-routed-verb-table.md` | `product-law` | Human-readable column = menu labels |
| **CLI routed-verb** | `docs/terminologies/cli-routed-verb.md` | `product-law` | Live command a choice runs; case 3 `menu`/`main` |
| **CLI gap name** | `docs/terminologies/cli-gap-name.md` | `product-law` | Opposite of live — not a menu row |
| **Well-known CLI verb** | `docs/terminologies/well-known-cli-verb.md` | `product-law` | Portable `menu` token |
| **Operational verb** | `docs/terminologies/operational-verb.md` | `product-law` | Main-menu membership |
| **Test-purpose verb** | `docs/terminologies/test-purpose-verb.md` | `product-law` | Omit or list apart from main menu |
| **Type O empty argv** | `docs/terminologies/type-o-empty-argv.md` | `product-law` | Case 1 non-interactive empty argv **MUST** stay ensure |
| **Interactive vs noninteractive** | `docs/terminologies/interactive-vs-noninteractive.md` | `runtime-mode` | No hang |
| **No retest TTY** | `docs/terminologies/no-retest-tty.md` | `runtime-reliability` | Measure `[ -t` outside functions |
| **Do not capture `read`** | `docs/terminologies/do-not-capture-read.md` | `shell-lang-architecture` | Menu choice **MUST NOT** be `$()` of a `read` helper (**`PP-A-22`**) |
| **Prompt-ask-value** | `docs/terminologies/prompt-ask-value.md` | `shell-lang-architecture` | Choice string = `PROMPT_ASK_VALUE` |
| **App-name-version-display** | `docs/terminologies/app-name-version-display.md` | `identity-runtime` | Menu **header** nametag `**{{APP_NAME}}**(*{{VERSION}}*)` |
| **Default CLI main menu style** | `docs/terminologies/default-cli-main-menu-style.md` | `identity-runtime` | TTY look: **number** + **bold** short + *italic* long |
| **CLI main menu hierarchy table** | `docs/terminologies/cli-main-menu-hierarchy-table.md` | `product-law` | Catalog of every numbered layer |
| **CLI main menu numbering** | `docs/terminologies/cli-main-menu-numbering.md` | `product-law` | Unique integers; parent prefix; **0** back |
| **Invalid-choice retry** | `docs/terminologies/invalid-choice-retry.md` | `product-law` | Claimed TTY main menu **MUST use** this retry rule |
| **Menu layer** | `docs/terminologies/menu-layer.md` | `runtime-reliability` | One numbered list that owns the current `read` |
| **Command-finished front board** | `docs/terminologies/command-finished-front-board.md` | `product-law` | After a valid leaf, redisplay the **front** board |
| **Menu-hidden message** | `docs/terminologies/menu-hidden-message.md` | `product-law` | One reason line per hide cause, on that layer, before the numbers |
| **Command-substitution subshell** | `docs/terminologies/command-substitution-subshell.md` | `shell-lang-architecture` | Why `$()` swallows the prompt |
| **Docs folder structure** | `docs/terminologies/docs-folder-structure.md` | `policy` | Where this mold lives |
| **No-hardcode policy** | `docs/terminologies/no-hardcode-policy.md` | `policy` | Placeholders only |
| **Dual policies** | `docs/terminologies/dual-policies.md` | `policy` | Completeness × portability |

**SSOT types used:** `product-law` · `runtime-mode` · `runtime-reliability` · `identity-runtime` · `policy`

**Policies:** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md` · `docs/policies/policy-least-privilege.md`

---

## 2. Claim gate (mandatory)

A product **MUST** record in Implementation Notes whether it **claims** a default function, and which **case** (§3) applies.

| Claim | Effect |
|-------|--------|
| **Yes** | This mold’s **main menu** attaches per §3 |
| **No** | **MUST NOT** attach a menu to empty argv or invent `menu`/`main` |

Type O **non-interactive** empty argv **MUST NOT** be claimed as this menu (**case 1**).

---

## 3. Three cases (mandatory)

Detect: (1) specialized zero-argument requirement present? (2) product **online-installable** (Type O / `curl \| sh`)? Then pick **exactly one** case.

### 3.1 Case 1 — no zero-argument requirement, online-installable

| Mode | Claimed | MUST |
|------|---------|------|
| **Non-interactive** empty argv (`TTY=0`) | yes or no | **Unchanged** Type O **check / self-install**. **MUST NOT** menu. **MUST NOT** replace ensure with help |
| **`--json` or `--quiet` no command** (TTY or not) | yes or no | Non-interactive empty argv on **`LM-SHELL-CLI-ZERO-ARGUMENTS`**: Type O install-ensure; Type N help. **MUST NOT** menu. **MUST NOT** a JSON-help special case that blocks Type O |
| **Interactive** empty argv (`TTY=1`) | **yes** | **Main menu** (§4) |
| **Interactive** empty argv | **no** | **MUST NOT** invent a menu. Align with online-installable UX (typically **help**, or existing Type O interactive ensure) |

### 3.2 Case 2 — no zero-argument requirement, not online-installable

| Claimed | Interactive empty argv | Non-interactive empty argv |
|---------|------------------------|----------------------------|
| **yes** | **Main menu** (§4) | **Help** (human; `--json` → JSON help). **MUST NOT** prompt |
| **no** | **MUST NOT** bind empty argv to a menu. Follow any other zero-argument-related requirement (CLI-interface Type N help). If none, **help** |

### 3.3 Case 3 — zero-argument requirement exists

Empty argv **MUST** follow **`LM-SHELL-CLI-ZERO-ARGUMENTS`** / the specialized zero-arg REQ. This mold **MUST NOT** override empty argv. Empty argv there is **no command token** after flag parse: overlay flags (`--debug`, `--quiet`, `--json`) with no command **MUST** still follow that REQ (TTY menu when that REQ defers TTY empty argv here and quiet and json are off; otherwise Type O/N as that REQ says). `--json` or `--quiet` with no command **is** non-interactive empty argv (Type O install-ensure; Type N help). This mold **MUST NOT** steal it onto the numbered list and **MUST NOT** force JSON help over Type O. Interactive `{{APP_NAME}} menu --json` still ignores `--json` while drawing.

When claimed, the menu **MUST** be routed-verb **`menu`**. **`main` MAY** alias the same handler. List both on the CLI-interface table (honest **Gap** until dispatched).

| `{{APP_NAME}} menu` (or `main`) | `--json` | MUST | MUST NOT |
|---------------------------------|----------|------|----------|
| **Interactive** (`TTY=1`) | **Ignore** | **Main menu** (§4) | JSON help; hang |
| **Non-interactive** (`TTY=0`) | error when `JSON=1` | **Stop**: `out_die` `menu needs a terminal. Next: ${APP_NAME} help` (exit 1) | Menu; hang; help; exit 0 |

`--quiet` off a terminal on **`menu`/`main`** is the same stop (the error stays visible). Overlay `--quiet` / `--debug` / `--json` **with no command token** is empty argv on **`LM-SHELL-CLI-ZERO-ARGUMENTS`**, not this `menu` path. Measure `TTY` **outside functions**. `--json` **is** non-interactive for cases **1–2** empty argv; for case **3** interactive `menu`/`main`, `--json` is **ignored** while drawing. A board that needs a terminal (`self-management` when claimed) uses the same off-terminal stop, with its own noun in the sentence.

---

## 4. Main menu (when the case says menu)

0. **Look (mandatory — default-cli-main-menu-style):** every menu layer **MUST** follow [default CLI main menu style](../../terminologies/default-cli-main-menu-style.md). Header **MUST** print [app-name-version-display](../../terminologies/app-name-version-display.md) **`{{APP_NAME}}({{VERSION}})`** with **bold** name and *italic* version, then the board title. Typical: `out_info "$(util_app_ident) — numbered list of live commands"`. Markdown: `**{{APP_NAME}}**(*{{VERSION}}*)`. Each command row **MUST** be **number** + **bold** `{{short-descript}}` + *italic* `{{explain}}`. Typical helper: `out_menu_choice`. Off-TTY: plain. Submenu headers that lead with `APP_NAME` **MUST** use the same nametag. **MUST NOT** a bare `{{APP_NAME}}` on that header. Proof **TP-CLI-17**.  
0b. **Hierarchy (mandatory when nested):** fill [CLI main menu hierarchy table](../../terminologies/cli-main-menu-hierarchy-table.md) (also called **layered menu design**). Each [menu layer](../../terminologies/menu-layer.md) is a **numbered list of CLI verbs** (a category row opens the next list). Numbers **MUST** follow [CLI main menu numbering](../../terminologies/cli-main-menu-numbering.md) (also called the **non-repeating number prefix**: unique; parent prefix; submenu **0** Back; front Exit **9**). **MUST NOT** restart a submenu at **1**.  
1. Show a **numbered list** at the **beginning** of the interactive menu path.  
2. Front board **MAY** use category rows **1** client-side, **2** server-side, **8** self-management. Leaf rows are live **operational** commands that are **not** excluded below.  
3. **MUST NOT** list **install / setup**, **self-managed** routed-verbs (`install`, `uninstall`, `where-is-me`, `self-install`, `self-uninstall`, `self-update`, `version-check`, `setup`), **diagnostics** (`version`, `about`) on the **front board**. Those **MAY** appear as **81…** on submenu **8** when the hierarchy table claims self-management. Portable seed numbers: [well-known-menu](../../terminologies/well-known-menu.md) — **81** `install` (local CLI place **xor** online payload), **87** `self-install` (online CLI place). **MUST NOT** list **any test-purpose** verb on any numbered list. Those stay on the kept table and on `help` (test-purpose listed apart).  
4. The printed line **MUST** be that command’s **human-readable** value: **`{{short-descript}}: {{explain}}`** (short description = routed-verb).  
5. **MUST NOT** list the routed-verb **`help`**.  
6. **MUST NOT** list gap names, help-only ads, forbidden/retired tokens, test-purpose verbs, or **`menu`/`main` itself**.  
7. Last extra row is **Exit** (not a command token). Exit number **MUST** be:

| Command rows **N** | Exit number |
|--------------------|-------------|
| **N ≤ 8** | **9** |
| **9 ≤ N ≤ 98** | **99** |
| **99 ≤ N ≤ 998** | **999** |
| **N > 998** | next **10^k − 1** with **10^k − 1 > N** |

**MUST NOT** number Exit as **N+1** when the all-nines rule applies (13 commands → **99. Exit**). Unused integers between **N** and Exit are omitted.

8. Accept a **number** or the **verb token**; run the matching handler. Exit number (or `exit` / `quit`) **leaves this menu layer** (top layer → return 0). An empty line on the **front** leaves (Exit). An empty line, EOF, or **0** on a submenu is Back. `q` **MAY** be Exit on the front and Back on a submenu. On a numbered board, row **82** and a typed `version` **MUST** run `about`. Argv `version` stays the thin version line.  
8b. **Do not capture `read` (mandatory — stop repeating `PP-A-22`):** the choice **MUST** be read in the **current shell**. **MUST NOT** `_choice=$(prompt_ask …)` / `_choice=$(prompt_menu_choice …)` / `$()` / backticks of **any** function whose body contains `read`. Value: `prompt_ask "Choice" ""` then `_choice="${PROMPT_ASK_VALUE}"` (term **do-not-capture-read** · **prompt-ask-value**). stderr+$() is **not** a license. Gate **`CL-CLI-DEFAULT-INTERACTION`**. Proof **TP-CLI-16**.  
8c. **Invalid-choice retry (mandatory):** a claimed TTY main menu **MUST use** [invalid-choice retry](../../terminologies/invalid-choice-retry.md) on every [menu layer](../../terminologies/menu-layer.md). A **menu layer** is one numbered list that owns the current `read` (the main menu is a layer; each nested submenu is another). An **invalid choice** is any input that is **not** a listed number, **not** a listed verb token, and **not** this layer’s Exit / `exit` / `quit` (unused integers between **N** and the Exit number count). On an invalid choice the CLI **MUST**: print a loud operator-readable error via `out_error` (not `out_die`); **reprint this layer’s list**; **re-prompt** in the current shell. **MUST NOT** terminate the process. **MUST NOT** leave this layer. **MUST NOT** treat the pick as unknown argv (**TP-CLI-06**). Nested layers obey the same rule; Exit on a submenu returns to the parent layer. EOF / failed `read` **MUST** leave this layer without spinning. Reprint **MUST NOT** re-run a session probe (reuse cache — product maps own that TP-CLI id when a session probe exists). Proof **TP-CLI-19** (product maps **MUST NOT** reuse **TP-CLI-19** when that id already names a different intent — use the next free **TP-CLI-***).  
8d. **Command-finished front board (mandatory when nested):** the default is to go back to the top menu after a command runs. After a **valid leaf** (numbered command, typed verb, or nested action board) finishes, the CLI **MUST** redisplay the **front board**. **MUST NOT** redisplay the submenu that launched that command. **MUST NOT** treat this as invalid-choice retry. **0** / empty / EOF on a submenu still means Back (parent). A typed leaf on the front board itself also redisplays the front board (does not exit). Term [command-finished front board](../../terminologies/command-finished-front-board.md). Typical shape: submenu handlers **return** after a leaf so the front `while` reprints. Proof **TP-CLI-front-after-leaf** (product maps own the **TP-CLI-*** id).  
8e. **Menu-hidden message (mandatory when rows are omitted):** each distinct cause that omits rows of a [menu layer](../../terminologies/menu-layer.md) **MUST** print its own [menu-hidden message](../../terminologies/menu-hidden-message.md) on **that** layer, after the header and before the first numbered item. One cause that omits several rows on the same layer uses one message. A message on a child layer does not cover a hidden row on the parent. The message is not a numbered row. Omitted numbers stay reserved. A later pick of a hidden number is invalid-choice retry (8c). Reprinting the layer reprints the message before the numbers. A token that stays available by name and is absent as a number by design is not this message. Exact sentences belong in the specialized requirement. A cause with no live sentence is a Gap.  
8f. **Data picker (mandatory when the numbered list is live items, not command verbs):** A **data picker** lists hosts, folders, drafts, or extra fields. Item indexes are **1…N** plus **0** Back. Those indexes are not parent-prefix command numbers. **0**, an empty line, or EOF returns to the parent that opened the picker. **MUST NOT** `out_die` for Back. An unknown token on a **populated** picker reprints **this** picker and reads again in the current shell. **MUST NOT** `out_die`. **MUST NOT** leave the process. The loud line on a menu layer stays `out_error`. A data picker **MAY** use `out_warn` when the product requirement names that voice. An **empty** live set is product law (it may fail closed). That failure is not a choice. The front board does not print **0** Back; **0** there is an invalid choice on that menu layer.  
9. Typical handlers: `app_cmd_menu` (front), `app_cmd_menu_client`, `app_cmd_menu_server`, `app_cmd_menu_self` (`app_*`, portable). A product MAY add `app_cmd_menu_language`. Child numbers keep the parent prefix. The default language stays the one existing menu tests match. Language codes, endonyms, and translated strings stay in the product language requirement. That requirement **MUST** include a worked sample of the front board in the default language and in each added language (markdown **bold** short and *italic* long; no raw CSI; the version token is the live `{{VERSION}}`). When human help and human about follow the language, that requirement **MUST** include the opening of each in every accepted language. That requirement **MUST** include a translation table for the language-board longs, the choose-prompt (including a trailing space when the source string has one), Back, Exit, each menu-hidden sentence, each unknown-choice warn, and the sentences that stay in the default language (leaf verb tokens, JSON about fields, the version one-liner). **MUST NOT** invent a sample line the ship unit does not print. **MUST NOT** put these boards under the domain prefix.  
10. Extra fields: TTY **one-at-a-time** with the same call shape, or print `Next: {{APP_NAME}} <verb> …` and return — **MUST NOT** hang off-TTY.

### 4.1 Menu choice sample (illustration — not product law)

```sh
# WARNING — do-not-capture-read (**PP-A-22** / T1-PROMPT-CAPTURE)
# MUST NOT _choice=$(prompt_ask …) / $() / backticks. Body of prompt_ask contains `read`.
# Call in the current shell. Value is PROMPT_ASK_VALUE.
# stderr+$() is NOT a license. Terms: do-not-capture-read · prompt-ask-value · command-substitution-subshell
prompt_ask "Choice" ""
_choice="${PROMPT_ASK_VALUE}"
```

In-shell `read` (same ban — still the **current** shell, never `$()` of this function). Invalid choice **retries this layer** (`out_error` + continue). Nested submenus use the same loop.

```sh
# WARNING — do-not-capture-read (PP-A-22)
# Off a terminal only. Interactive menu --json still draws (force JSON and QUIET off while drawing).
app_cmd_menu() {
    : "${JSON:=0}" : "${QUIET:=0}" : "${TTY:=0}" : "${APP_NAME:=app}" : "${VERSION:=0.0.0}"
    if [ "${TTY}" -ne 1 ]; then
        out_die "menu needs a terminal. Next: ${APP_NAME} help"
    fi
    _menu_json="${JSON}"
    _menu_quiet="${QUIET}"
    JSON=0
    QUIET=0
    while true; do
        out_info "**${APP_NAME}**(*${VERSION}*)"
        out_menu_choice "1" "client-side" "commands that run on this login"
        out_menu_choice "2" "server-side" "commands for a host service when the product claims one"
        out_menu_choice "8" "self-management" "this CLI install, version, update, uninstall"
        out_plain "9. Exit"
        out_msg_n "Choose a number, or type the command name: "
        _choice=""
        if ! read -r _choice; then
            JSON="${_menu_json}"
            QUIET="${_menu_quiet}"
            unset _choice _menu_json _menu_quiet
            return 0
        fi
        case "${_choice}" in
            1|client-side)
                JSON="${_menu_json}"; QUIET="${_menu_quiet}"
                app_cmd_menu_client
                JSON=0; QUIET=0
                continue ;;  # submenu returns after a leaf → front reprints
            2|server-side)
                JSON="${_menu_json}"; QUIET="${_menu_quiet}"
                app_cmd_menu_server
                JSON=0; QUIET=0
                continue ;;
            8|self-management) app_cmd_menu_self; continue ;;
            9|99|exit|quit|Exit|QUIT|""|q|Q)
                JSON="${_menu_json}"
                QUIET="${_menu_quiet}"
                unset _choice _menu_json _menu_quiet
                return 0
                ;;
            *)
                out_error "Unknown menu choice '${_choice}'. That number or name is not on this list. Choose a listed number or command name."
                continue
                ;;
        esac
    done
}
```

Specialized `requirement-*-cli-default-interaction.md` **MUST** copy this ban into the MUST table (product language; **MUST NOT** paste skill/template paths).

---

## 5. Design-time verification (default families)

When specializing, proof **SHOULD** include: case identity recorded; empty argv still matches zero-arg / Type O law; `menu`/`main` TTY menu (case 3); `menu --json` on TTY still menu (case 3); `menu` off-TTY stops (`menu needs a terminal`, exit 1); `menu --json` off-TTY is that stop as a JSON error; an empty line on the front leaves; row **82** and a typed `version` on a board run `about` (argv `version` stays the thin line); **`help` / gap / forbidden / `menu` / install-setup / self-managed / version / about / test-purpose absent** from numbered choices; Exit is **9** when N≤8, **99** when 9≤N≤98; **no `$()` of `read` helpers** on the menu path (**TP-CLI-16** · **TP-ELEV-10**); look **MUST** be **default-cli-main-menu-style** (header `{{APP_NAME}}({{VERSION}})` bold/italic; numbered `{{explain}}` italic + light gray) (**TP-CLI-17**); numbered list **MUST use invalid-choice retry** at any **menu layer** — process stays alive; unused listed-gap integers (example: `3` when `3` is not a row) are invalid (**TP-CLI-19**, or the next free **TP-CLI-*** when **19** already names a different product intent); nested tree **MUST** redisplay the **front board** after a valid leaf (**TP-CLI-front-after-leaf**); each hide cause **MUST** print a **menu-hidden message** before that layer’s numbers (Gap until the ship unit prints the line). A language board **MUST** keep worked samples and a translation table in the product language requirement (not in this mold). A populated **data picker** **MUST** print **0** Back and **MUST NOT** `out_die` on Back or on an unknown token (reprint that picker). Complete **`CL-CLI-DEFAULT-INTERACTION`**. Map TP-IDs on the product test-plan (do not freeze `RQ-*` here).

---

## 6. How to specialize

1. Compose **`SK-CLI-DEFAULT-INTERACTION`**.  
2. Ensure `reviews/cli-routed-verb-table.md` has **human-readable**.  
3. Write `requirement-<lang>-cli-default-interaction.md` via **`SK-CREATE-SPECIFIC-REQUIREMENT`**. Record **case 1 / 2 / 3**.  
4. If case 3: zero-arguments REQ **keeps** empty argv; CLI-interface **lists** `menu`/`main` (Gap until live).  
5. Product source cites the **requirement** only.

---

## Protection Rule (Sacred)

Future agents **MUST NOT**:

1. Invent menu labels instead of table human-readable `{{short-descript}}: {{explain}}`.  
2. Put **`help`**, not-live names, or **`menu`/`main` itself** on the main menu.  
2b. Number **Exit** as **N+1** instead of **9 / 99 / 999 …**.  
2c. Put **install / setup**, **version**, **about**, any **self-managed** routed-verb, or any **test-purpose** verb on the **front board**. Self-management **MAY** live under **8**. Test-purpose stays off every numbered list.  
2d. Restart a submenu at **1** or skip the hierarchy table when the menu is nested.  
2e. Own the numbered tree only on a domain REQ — specialize independent `requirement-*-cli-default-interaction`.  
3. Draw the menu in non-interactive mode.  
3b. Swallow help under `--quiet` on a non-interactive help path.  
3c. Invent a second JSON help catalog instead of the help handler.  
4. Replace Type O **non-interactive** empty argv with a menu or with help (**case 1**).  
5. Override a specialized zero-argument requirement’s empty argv (**case 3**).  
5b. Treat `{{APP_NAME}} --debug` (no command) as help or as a third meaning — overlay flags-only **MUST** follow empty argv on **`LM-SHELL-CLI-ZERO-ARGUMENTS`**.  
5c. Draw this menu for TTY `{{APP_NAME}} --json` (no command), or treat that line as JSON help on a Type O product. That invocation **is** non-interactive empty argv; the outcome is install-ensure.  
6. Attach a menu to empty argv when the product does **not** claim a default function.  
7. Treat interactive case-3 `menu --json` as JSON help.  
8. Print help for non-interactive case-3 `menu`/`main`. Off a terminal, `menu` **MUST** `out_die` (`menu needs a terminal. Next: ${APP_NAME} help`). JSON mode emits the JSON error.  
9. Treat this mold as product-source ALIGNMENT.  
10. Strip the claim gate, three-case split, or no-hang rule.  
11. Capture the menu choice (or extra field) with `$()` / backticks of a `read` helper, or “fix” a freeze by stderr+$() (**`PP-A-22`** / **do-not-capture-read**).  
12. Specialize a default-interaction REQ **without** a MUST row that forbids `$()` of `read` helpers.  
13. Print a main-menu (or APP_NAME-led submenu) header as a bare `{{APP_NAME}}`, or unstyled on TTY — **MUST** use **`{{APP_NAME}}({{VERSION}})`** with **bold** name and *italic* version.  
14. Draw the numbered list off **default-cli-main-menu-style** — **MUST NOT** print short unstyled or long unstyled on a TTY (short **MUST** be **bold**; long **MUST** be *italic* + light gray).  
15. Skip **invalid-choice retry** on a claimed TTY main menu, or **`out_die` / exit** on an invalid TTY menu choice (unused number, unknown name, nested-layer typo) — **MUST** `out_error`, reprint **this** layer, and re-prompt (**TP-CLI-19**). **MUST NOT** collapse that pick into unknown argv (**TP-CLI-06**).  
16. After a **valid leaf** on a nested TTY tree, stay on the submenu that launched it — **MUST** redisplay the **front board** ([command-finished front board](../../terminologies/command-finished-front-board.md); **TP-CLI-front-after-leaf**).  
17. Omit numbered rows without a **menu-hidden message** on that layer, before the numbers — one message per cause. **MUST NOT** print the reason after the numbers or let a child layer’s line cover a parent-layer hide. **MUST NOT** invent a sentence the ship unit does not print.  
18. Add a language board without a product language requirement that holds worked samples of each front board and a translation table for the lines those samples do not show in every language. **MUST NOT** put product sentences in this mold.  
19. `out_die` on **0** Back or on an unknown token of a **populated** data picker — **MUST** print **0** Back, reprint that picker, and read again. An empty live set stays product law. **MUST NOT** give picker rows parent-prefix command numbers.

---

## Under command line for normal user only

When the product may run on Termux, Git Bash, Windows cmd, or the same class: Type 1/2 unused on detect; no in-tool sudo / apt / dedicated system user; no `sudo curl | sh` recommend; Git Bash and Windows cmd do not invoke Termux `pkg`. **This mold:** the numbered list and **invalid-choice retry** stay Type 0 TTY UX on that class — retry **MUST NOT** require elevation.

---

**Last Updated**: 2026-09-30 (v1.25.0 — flags-only `--json` follows the zero-arguments mold; named menu off a terminal stops; empty front line leaves; row **82** on a board runs about; v1.24.0 — a populated data picker prints **0** Back and a bad token reprints that list; v1.23.0 language samples and a translation table stay in the product language requirement; v1.22.0 a product MAY add `app_cmd_menu_language`; v1.21.0 numbered menu handlers are `app_cmd_menu*`; v1.20.0 menu-hidden message before numbered items; v1.19.0 well-known-menu **81** / **87**; v1.18.0 command-finished front board; v1.17.0 hierarchy table)  
**Owner**: {{OWNER}}  
**Alignment**: **`LM-CLI-INTERFACE`** · **`LM-SHELL-CLI-ZERO-ARGUMENTS`** · **`LM-INTERACTIVE-VS-NONINTERACTIVE`** · **`LM-SHELL-SCRIPT-CODING` §8.1.5** · terms `cli-default-interaction` · `well-known-menu` · `well-known-cli-verb` · `invalid-choice-retry` · `menu-layer` · `menu-hidden-message` · `command-finished-front-board` · `default-cli-main-menu-style` · `app-name-version-display` · `do-not-capture-read` · `prompt-ask-value` · `cli-routed-verb-table` · **`CL-CLI-DEFAULT-INTERACTION`** · CIAO / CIAO-Lite
