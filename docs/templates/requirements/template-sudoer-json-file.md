---
name: sudoer-json-file
id: LM-SUDOER-JSON-FILE
kind: law-mold
description: >
  Portable law mold for the JSON sudoer file (and matching sudoers(5) text dual).
  Grant is {{PRJ_NAME}} only — no cp/mkdir/tar/rm. Cite as LM-SUDOER-JSON-FILE.
---

**file**: template-sudoer-json-file.md  
**Mold-ID**: LM-SUDOER-JSON-FILE  
**Status**: Active (Version 1.14.0)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered / Over-protect)

**Folder structure (policy):** [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

# =============================================================================
# Portable law mold — sudoer JSON file ({{PRJ_NAME}} only)
# Specialize into: docs/requirements/requirement-sudoer-json-file.md
# Use {{PLACEHOLDER}} only. Product source cites the specialized requirement, not this file.
# =============================================================================

## 1. Purpose

This mold is the portable **law** for the **JSON-type sudoer file**: the machine encoding of a product elevation grant. When a product has **more than one** grant, field **`kind`** ([`sudoer-request-kind`](../../terminologies/sudoer-request-kind.md)) **MUST** split them. Do **not** reuse `action` (`add`/`update`) or a domain request type as that discriminator.

The grant **MUST** name only the project command **`{{PRJ_NAME}}`** (same value as `{{APP_NAME}}` / ship-unit basename). It **MUST NOT** allowlist other shell or OS tools (`cp`, `mkdir`, `install`, `chmod`, `tar`, `rm`, shells). Those extra tools **increase design complexity and thereby weaken security**.

**Does not own** (point, do not copy):

| Concern | Owner mold / term |
|---------|-------------------|
| Type 0/1/2 map, print-sudoers **workflow**, independent generate dest, Type 0 submit vs Type 1 hook auto-queue, trust tiers | **`LM-THREE-LAYER-PRIVILEGE-MODEL`** §2.3.2a / §2.3.3c–e |
| **POSIX shell CLI emit + wrap samples** (`print-sudoers`, `generate-sudoer-request`, `util_sudo`) | **`LM-SHELL-SUDOER`** (copy those functions; do not reinvent) |
| This-login **config deposit** that uses the grant (`backup-config` / `sync-config`) | **`LM-SHELL-CONFIG-BACKUP`** (depends on **`LM-SHELL-SUDOER`**) |
| Draft/installed **path class** | term `project-sudoers-file` |
| Approval folders + roles | term `file-based-json-approval` |
| Domain verbs / help / about | specialized `requirement-domain-*` |
| Backup / restore **ops** | **`LM-FOLDER-ARCHIVE-BACKUP`** when present |

Specialize into `requirement-sudoer-json-file.md` (or project-equivalent key). **No `RQ-*` in this mold.**

## 2. Terminologies

| Term | Path | SSOT type | Role |
|------|------|-----------|------|
| **Sudoer JSON file** | `docs/terminologies/sudoer-json-file.md` | `product-law` | This mold’s primary word |
| **Sudoer request kind** | `docs/terminologies/sudoer-request-kind.md` | `product-law` | Field `kind` |
| **Type-2-switch sudoer request** | `docs/terminologies/type-2-switch-sudoer-request.md` | `product-law` | Operator → LPU grant |
| **Login-hook sudoer request** | `docs/terminologies/login-hook-sudoer-request.md` | `product-law` | LPU hook grant |
| **Automatic login-hook sudoer submit** | `docs/terminologies/automatic-login-hook-sudoer-submit.md` | `product-law` | Type 1 setup queues hook grant iff sibling dest exists |
| **Sudoer file** | `docs/terminologies/sudoer-file.md` | `product-law` | `sudoers(5)` text dual |
| **Sudoers fragment** | `docs/terminologies/sudoers-fragment.md` | `product-law` | Superclass (plain-text class) |
| **Project sudoers file** | `docs/terminologies/project-sudoers-file.md` | `product-law` | Draft/installed **path** |
| **Elev is approval** | `docs/terminologies/elev-is-approval.md` | `policy` | Live mkdir/cp/tar after elev ≠ grant |
| **Least privilege** | `docs/terminologies/least-privilege.md` | `policy` | Smallest F6 |
| **LLM escape** | `docs/terminologies/llm-escape.md` | `policy` | **E-PRIV-04** broad sudoers |
| **Three-layer privilege** | `docs/terminologies/three-layer-privilege.md` | `product-law` | Type 0 submit / Type 1 elev |
| **File-based JSON approval** | `docs/terminologies/file-based-json-approval.md` | `product-law` | Queue machine |
| **Request filename grammar** | `docs/terminologies/request-filename-grammar.md` | `product-law` | Queued basename class |
| **Self-scope request** | `docs/terminologies/self-scope-request.md` | `product-law` | Subject = invoker |
| **Global installation location** | `docs/terminologies/global-installation-location.md` | `identity-runtime` | `{{GLOBAL_BIN}}` |
| **Ship unit** | `docs/terminologies/ship-unit.md` | `identity-runtime` | `{{PRJ_NAME}}` basename |
| **SSOT catalog** | `docs/terminologies/ssot-catalog.md` | `meta-catalog` | Inventory |
| **Project templates** | `docs/terminologies/project-templates.md` | `meta-catalog` | Law-mold surface |
| **Docs folder structure** | `docs/terminologies/docs-folder-structure.md` | `policy` | This file’s tree |
| **No-hardcode policy** | `docs/terminologies/no-hardcode-policy.md` | `policy` | Placeholders only |

**SSOT types used:** `product-law` · `policy` · `identity-runtime` · `meta-catalog`

**Missing terms:** none

**Policies:** `docs/policies/policy-least-privilege.md` · `docs/policies/policy-no-hardcode.md` · `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md`

## 3. Core rules (portable)

### 3.0 Sudoer request kind (sacred when two grants exist)

A product that queues **both** an operator Type 2 switch **and** a login-hook `sudo -n` grant **MUST** emit `kind`. Products with a **single** grant (Type 1 deposit only) **MAY** omit `kind` and follow §3.2 `{{RUNAS}}` rules — they **MUST NOT** label that deposit `login-hook-elev`.

| `kind` | `username` | `commands[].runas` | `commands[].args` | Who queues |
|--------|------------|--------------------|-------------------|------------|
| **`type-2-switch`** | Invoker (`id -un`, self-scope) | Dedicated LPU (`{{SYSTEM_USER}}` / `{{LPU_USER}}`) | `[]` **MAY** when Table A is the whole managed binary | Type 0 `{{GENERATE_SUDOER_CMD}}` / `{{SUBMIT_SUDOER_CMD}}` |
| **`login-hook-elev`** | The LPU (`{{LPU_USER}}`) | `root` | **MUST** be `["{{REVIEW_VERB}}"]` (typical `interactive`) | Type 1 `setup` auto-queue when sibling dest exists ([`automatic-login-hook-sudoer-submit`](../../terminologies/automatic-login-hook-sudoer-submit.md)). Type 0 submit **MUST** refuse |
| *(omit / Type 1 deposit only)* | Invoker | `root` | **MUST** be verb-bound product elev verbs (`{{ELEV_CMD}}`) | Type 0 submit of that **one** grant. **MUST NOT** use `login-hook-elev` |

**MUST NOT** collapse the two named kinds. **MUST NOT** grant whole-CLI-as-root.

### 3.0a Submit vs setup door (sacred)

| Door | Who | How | What | Dest Type 0 `username` == `id -un` |
|------|-----|-----|------|-------------------------------------|
| **`{{SUBMIT_SUDOER_CMD}}`** | Current login | Type 0. **No sudo.** | `type-2-switch` only | Applies (human files for self) |
| **`setup`** | Host admin | Type 1. **Password `sudo` / already root.** | Write `login-hook-elev` into inbound (dest request-id grammar). **MUST NOT** call dest Type 0 `add-sudoer-request`. **MUST NOT** `chown` inbound | **MUST NOT** apply. That dest check is a **blockage**, not a safety net. Dest approval reviews the JSON and does **not** test who submitted |

### 3.0b Queue ownership (sacred)

Type 0 `{{SUBMIT_SUDOER_CMD}}` and Type 1 `setup` **MUST NOT** `chown` dest inbound JSON. Dest `{{APPROVER}}` (typical `sudoer-adm`) **takes** [file-ownership](../../terminologies/file-ownership.md), then moves. The JSON [username field](../../terminologies/json-username-field.md) is **not** the Unix owner. A queue move **MUST** assume that previous ownership change — or dest takes it in the same step when run as `{{APPROVER}}`. Term: [`approval-queue-move`](../../terminologies/approval-queue-move.md). Portable peer: **`LM-FILE-BASED-JSON-APPROVAL`** §2.3a / §2.5a.

**Dest approval fencing conditions (closed).** Dest `approve` / `reject` / review **MUST** fail closed on inbound **only** when a listed [approval fencing condition](../../terminologies/approval-fencing-condition.md) holds. Dest inbound fence is **[incorrect JSON format](../../terminologies/incorrect-json-format.md)**. Dest **MUST NOT** add extra fences. Specialized law **MUST** print this table.

| Condition | Dest approve / reject / review |
|-----------|--------------------------------|
| **[Incorrect JSON format](../../terminologies/incorrect-json-format.md)** | **Fence** — fail closed. Independent REQ (specialize **`LM-FENCE-CONDITION-REQUIREMENT`**; dest table still prints) |
| File-ownership | **MUST NOT** fence — take ownership as `{{APPROVER}}` |
| Who submitted / dest Type 0 self-scope | **MUST NOT** fence |
| JSON username field ≠ dest LPU | **MUST NOT** fence |
| Filename subject token ≠ JSON username field | **MUST NOT** fence — user SSOT is the JSON field |

**Incorrect JSON format** includes: not a regular file; not one parseable JSON object; closed-schema fail; field types/enums invalid; basename grammar fail; basename **action** ≠ JSON `action`. Dest **MUST NOT** take the user from the filename; user SSOT is the JSON username field. Type 0 submit self-scope and Type 1 **authz** are **not** dest inbound-file fences.

Workflow detail: **`LM-THREE-LAYER-PRIVILEGE-MODEL`** §2.3.3c / §2.3.3e.

### 3.1 Command identity — `{{PRJ_NAME}}` only (sacred)

| Rule | Detail |
|------|--------|
| **Identity** | `type-2-switch` `commands[].path` **MUST** be `{{GLOBAL_BIN}}/{{PRJ_NAME}}`. `login-hook-elev` path **MUST** be the [login-hook-symlink](../../terminologies/login-hook-symlink.md) `{{GLOBAL_BIN}}/{{APP_NAME}}-hook`. **MUST NOT** copy live `$GLOBAL_BIN`. |
| **Basename** | `type-2-switch`: `{{PRJ_NAME}}`. `login-hook-elev`: `{{APP_NAME}}-hook` |
| **Service** | JSON `service` **MUST** equal `{{PRJ_NAME}}` |
| **One program** | **MUST NOT** list any other executable |
| **No local binary** | **MUST NOT** elevate `{{USER_BIN}}/{{PRJ_NAME}}` |
| **No OS tools** | **MUST NOT** list `cp`, `mkdir`, `install`, `chmod`, `tar`, `rm`, `ln`, `mv`, `chown`, `dd`, or shells (`sh`, `bash`, `dash`) — including `/bin/*` and `/usr/bin/*` twins |
| **No ALL** | **MUST NOT** use `ALL`, `NOPASSWD: ALL`, or an empty command set |

**Why OS-tool grants are forbidden:** each helper adds lines, path twins, dest wildcards, and filename patterns. The user can then run those tools as root **without** `{{PRJ_NAME}}`. Complexity is a **security defect**.

After elev, the ship unit **MAY** mkdir/copy/tar/rm **internally** ([`elev-is-approval`](../../terminologies/elev-is-approval.md)). Those live tools are **Table C**, not this JSON.

### 3.2 Arguments — product verbs, no path or filename hardcode

1. `commands[].args` **MAY** name only product verbs that need elevation (`{{ELEV_CMD}}` — e.g. `{{BACKUP_CMD}}` / `{{RESTORE_CMD}}` when those verbs exist).  
2. When `{{RUNAS}}` is **`root`**: **MUST** be **verb-bound** — **MUST NOT** grant `{{PRJ_NAME}}` with no verb (whole CLI as root).  
3. When `{{RUNAS}}` is a **dedicated LPU** and Table A is the whole managed binary: `args` **MAY** be `[]` so `sudo -u {{RUNAS}} {{PRJ_NAME}} --json <verb>` still matches.  
4. **MUST NOT** put deposit paths, stage paths, host HOME, archive filenames, or a **cwd file list** in `args`.  
5. **MUST NOT** grant Type 0 verbs (`install`, `uninstall`, `print-sudoers`, `generate-sudoer-request`, `submit-sudoer-request`, …) as elevated commands. Type 1 bootstrap (`setup` / `remove-lpu`) **MUST NOT** appear when product law requires password `sudo` for those verbs.  
6. **One filesystem operand per `commands[].args` array** when specialized law is one recursive **folder** (take-ownership): `--path` is **one directory**, `--ownership` is **one** `user:group`. **MUST NOT** put two folders or any files on that array / that sudoers **line**.  
7. A **later** directory is a **later submit**. Generate **MUST** read unique prior `--path` values, skip duplicates, and emit a **replacement** (1 folder → 1 line, 2 folders → 2 lines, …). **MUST NOT** use `"*"` as a file glob, as “all folders,” or as [ownership representation](../../terminologies/ownership-representation.md) (`--ownership` **MUST** be `{{USER}}:{{GROUP}}` — not [ownership wildcard](../../terminologies/ownership-wildcard.md)).

### 3.3 Closed schema

| Field | Required | Rule |
|-------|----------|------|
| `schema_version` | yes | `1` |
| `kind` | yes on emit when §3.0 applies | See §3.0. Missing on input: treat as `type-2-switch` only if `runas` is the LPU and `args` is `[]`; else fail closed unless the product’s **only** grant is Type 1 deposit. **MUST NOT** reuse `action` or a domain request type |
| `purpose` | yes | Human; no secrets |
| `username` | yes | Per §3.0. Not `ALL` |
| `service` | yes | `{{PRJ_NAME}}` |
| `action` | yes | `add` or `update` (submit **default** from host dest probe is the privilege-workflow peer — not this mold) |
| `commands` | yes | Non-empty; every element obeys §3.1–3.2 |
| `commands[].runas` | yes | Per §3.0. **MUST NOT** be `ALL` |
| `commands[].tags` | yes | `NOPASSWD` **MUST** when a login hook uses `sudo -n` |
| `commands[].path` | yes | `type-2-switch`: `{{GLOBAL_BIN}}/{{PRJ_NAME}}`. `login-hook-elev`: `{{GLOBAL_BIN}}/{{APP_NAME}}-hook` |
| `commands[].args` | yes | Per §3.0. **MUST NOT** grant `{{PRJ_NAME}}` with no verb when `runas` is `root` |

### 3.4 Text dual ([`sudoer-file`](../../terminologies/sudoer-file.md))

If a `sudoers(5)` text file represents the **same** grant, it **MUST** be equivalent:

```text
{{TARGET_USER}} ALL=({{RUNAS}}) NOPASSWD: {{GLOBAL_BIN}}/{{PRJ_NAME}} {{ELEV_CMD}}
```

`type-2-switch` dual: `{{TARGET_USER}} ALL=({{LPU_USER}}) NOPASSWD: {{GLOBAL_BIN}}/{{PRJ_NAME}}`  
`login-hook-elev` dual: `{{LPU_USER}} ALL=(root) NOPASSWD: {{GLOBAL_BIN}}/{{APP_NAME}}-hook {{REVIEW_VERB}}`  
Type 1 deposit (no `login-hook-elev`): `{{TARGET_USER}} ALL=(root) NOPASSWD: {{GLOBAL_BIN}}/{{PRJ_NAME}} {{ELEV_CMD}}`

A text file that allowlists `mkdir`/`cp`/… **MUST NOT** be treated as a valid dual of a compliant JSON sudoer file.

### 3.4a Re-encode / convert fidelity

Pretty-printed JSON (newlines/spaces between `commands[]` objects) and compact JSON are **the same grant**.

1. Decode / convert / re-encode **MUST** preserve every `commands[]` object (`path`, `args`, `runas`, `tags`).  
2. **MUST NOT** silently drop objects so `purpose` still lists verbs that `commands` lost. Purpose is not completeness.  
3. A splitter that only recognizes the token `},{` is non-compliant (`}, {` and `},\n{` are legal).  
4. If the codec cannot represent the full array, **fail closed**. Last-`args`-wins is forbidden.  
5. `[OK] submitted` is not proof the queued body equals the emit dual.

### 3.4b Independent generate dest

This JSON **MUST** be writable by a Type 0 **subcommand** (`{{GENERATE_SUDOER_CMD}}`) **without** submit, inbound, or `/etc` install. Dest **MUST** be invoking-user readable so tests and review can `cat` it without sudo. Submit temp and inbound are **not** that dest. Generate **MUST** write `kind` when §3.0 applies; `--kind {{KIND}}` **MAY** emit the hook fixture without queueing. Workflow/readability: **`LM-THREE-LAYER-PRIVILEGE-MODEL`** §2.3.2a · term `independent-sudoer-generate`.

### 3.5 Portable samples (replace every `{{…}}` on specialize)

**`type-2-switch` add:**

```json
{
  "schema_version": 1,
  "kind": "type-2-switch",
  "purpose": "Allow {{TARGET_USER}} to run {{PRJ_NAME}} as {{LPU_USER}}.",
  "username": "{{TARGET_USER}}",
  "service": "{{PRJ_NAME}}",
  "action": "add",
  "commands": [
    {
      "runas": "{{LPU_USER}}",
      "tags": ["NOPASSWD"],
      "path": "{{GLOBAL_BIN}}/{{PRJ_NAME}}",
      "args": []
    }
  ]
}
```

**`login-hook-elev` add:**

```json
{
  "schema_version": 1,
  "kind": "login-hook-elev",
  "purpose": "Allow {{LPU_USER}} login hook to run {{PRJ_NAME}} {{REVIEW_VERB}} via sudo -n.",
  "username": "{{LPU_USER}}",
  "service": "{{PRJ_NAME}}",
  "action": "add",
  "commands": [
    {
      "runas": "root",
      "tags": ["NOPASSWD"],
      "path": "{{GLOBAL_BIN}}/{{APP_NAME}}-hook",
      "args": ["{{REVIEW_VERB}}"]
    }
  ]
}
```

**Update JSON:** same object for that kind; `"action": "update"` only.

**Withdrawn:** `"path": "/usr/bin/mkdir"` (and `cp` / `tar` / `rm` / `install` / `chmod` siblings) · `login-hook-elev` with `args: []` · `type-2-switch` with `runas: "root"`.

Queued **inbound basename** stays sibling/allocator-owned ([`request-filename-grammar`](../../terminologies/request-filename-grammar.md)). This mold **does** name the **installed sibling dest class** after approve (§3.4c).

### 3.4c Sibling dest after approve (sacred — three dests)

The **JSON `username`** keys the sibling dest. **MUST NOT** collapse these with each other or with F6.

| Kind / dual | JSON `username` | Installed dest after sibling approve (sibling writes) | What it allows |
|-------------|-----------------|------------------------------------------------------|----------------|
| **`type-2-switch`** | Invoker `{{TARGET_USER}}` (`id -un`) | `/etc/sudoers.d/{{APP_NAME}}-{{TARGET_USER}}` | `sudo -n -u {{LPU_USER}} {{GLOBAL_BIN}}/{{APP_NAME}} …` |
| **`login-hook-elev`** | The LPU `{{LPU_USER}}` | `/etc/sudoers.d/{{APP_NAME}}-{{LPU_USER}}` | `sudo -n {{GLOBAL_BIN}}/{{APP_NAME}}-hook {{REVIEW_VERB}}` |
| **F6 group dual** (not JSON) | n/a — group `%sudo` | `/etc/{{LPU_USER}}/sudoers` (this product Type 1 `setup` / `print-sudoers`) | `%sudo ALL=({{LPU_USER}}) NOPASSWD: {{GLOBAL_BIN}}/{{APP_NAME}}` |

**MUST NOT** treat Type 1 `setup` / account create as writing `/etc/sudoers.d/{{APP_NAME}}-{{TARGET_USER}}`. Setup queues **`login-hook-elev`**; after approve the dest is **`{{APP_NAME}}-{{LPU_USER}}`**.

**MUST NOT** treat Type 0 `{{SUBMIT_SUDOER_CMD}}` as writing `/etc/sudoers.d/{{APP_NAME}}-{{LPU_USER}}`. That verb queues **`type-2-switch`**; after approve the dest is **`{{APP_NAME}}-{{TARGET_USER}}`**.

This product **MUST NOT** write `/etc/sudoers.d`. Sibling dest write is dest Type 1.

### 3.4d visudo-legal text dual (sacred)

Whenever a product **materializes** `sudoers(5)` text (convert, submit add/update, dest-write add/update) — including a dest that writes **sibling** grants whose `commands[].path` is **not** `{{GLOBAL_BIN}}/{{PRJ_NAME}}` — that text **MUST** be visudo-legal.

1. Cmnd **args** that contain sudoers-special characters (`:`, `#`, `,`, `\`) **MUST** be backslash-escaped so visudo can parse them (`user\:group`). Escape order **MUST** be: backslash first, then `:`, `#`, `,`. Round-trip unescape **MUST** restore the JSON arg.  
2. A trailing sudoers `*` operand **MUST NOT** be expanded as a shell glob. Render and parse **MUST** disable globbing while splitting args (`set -f` on POSIX sh). JSON `"*"` stays a quoted string. This is **not** permission to use `"*"` as [ownership representation](../../terminologies/ownership-representation.md) — `--ownership` **MUST** stay `{{USER}}:{{GROUP}}`.  
3. Parse of a `NOPASSWD:` line **MUST** split after `NOPASSWD:` — **MUST NOT** split on the last colon (args may contain `\:`).  
4. **MUST** run `visudo -cf` on a **private** `mktemp` copy (never in-place `/etc/sudoers` or `/etc/sudoers.d`) at convert, submit add/update, and dest-write add/update. Comment-only remove **MUST** skip visudo. JSON is **never** fed to visudo.  
5. If `visudo` is **not** on `PATH`, skip `-cf` (debug). **MUST NOT** invent a substitute checker named “host validation”.  
6. If visudo rejects the text: fail closed. Operator copy **MUST** follow **`LM-OPERATOR-READABLE-ERROR`**: what happened (**visudo rejected this grant**), quote visudo’s syntax line when present, what it means (the sudoers file would be illegal; do not approve), what to do next (convert again until visudo accepts). **MUST NOT** say “host validation” or “host sudoers checker”. **MUST NOT** dest-write. **MUST NOT** queue.  
7. visudo reject is **not** a dest Fence (no display-then-rejected drain solely because visudo failed).

This subsection **does not** change §3.1 command identity for a product’s **own** elev JSON. A dest that writes sibling service grants **MUST** still apply §3.4d to those grants.

### 3.6 Implementation Notes (fill when specializing)

| Item | Placeholder |
|------|-------------|
| **`{{PRJ_NAME}}` / `{{APP_NAME}}`** | ship-unit basename |
| **`{{GLOBAL_BIN}}`** | typically `/usr/local/bin` |
| **Elevated path** | `{{GLOBAL_BIN}}/{{PRJ_NAME}}` |
| **Kinds specialized** | `type-2-switch` · `login-hook-elev` · (omit if Type 1 deposit only) |
| **`{{LPU_USER}}` / `{{SYSTEM_USER}}`** | dedicated LPU login |
| **`{{REVIEW_VERB}}`** | typical `interactive` |
| **`{{RUNAS}}`** | per kind (§3.0) |
| **Allowed args** | per kind |
| **Submit verb** | `{{SUBMIT_SUDOER_CMD}}` — Type 0 **`type-2-switch` only** when both kinds exist |
| **Generate verb** | `{{GENERATE_SUDOER_CMD}}` — independent dest; `--kind` for fixtures |
| **Generate dest (switch)** | `{{GENERATE_SUDOER_DEST}}` |
| **Generate dest (hook)** | `{{GENERATE_HOOK_SUDOER_DEST}}` |
| **Sibling dest after approve (switch)** | `/etc/sudoers.d/{{APP_NAME}}-{{TARGET_USER}}` |
| **Sibling dest after approve (hook)** | `/etc/sudoers.d/{{APP_NAME}}-{{LPU_USER}}` |
| **F6 dest** | `/etc/{{LPU_USER}}/sudoers` — not either JSON dest |
| **Workflow peer** | specialized `requirement-three-layer-privilege-model` |
| **Stay-honest gap** | If live emit still lists OS tools, say so — do not claim compliance |

## 4. CIAO alignment

- **Caution:** Refuse OS-tool JSON even if an older fragment used it. visudo before queue and dest-write.  
- **Intentional:** `service` and `path` basename are `{{PRJ_NAME}}` for **own** elev JSON; dest sibling grants still apply visudo-legal text dual.  
- **Anti-fragile:** Paths/names stay in Config; changing `{{BACKUP_ROOT}}` must not require a new grant. Convert/submit/dest-write share one visudo check.  
- **Over-protect:** Verb-bound when `{{RUNAS}}` is root; empty args only for Type 2 LPU + Table A whole-binary; no `USER_BIN`; no ALL.  
- **P10 / E-PRIV-04:** One binary; `{{RUNAS}}` is the smallest actor that can do the job.  
- **P21:** Placeholders here; filled Implementation Notes after specialize.

## 5. Protection Rule (Sacred)

Future agents **MUST NOT**:

1. Put `cp`, `mkdir`, `install`, `chmod`, `tar`, `rm`, or a shell in JSON `commands`.  
2. Treat dest wildcards or `*.tar.gz` as a substitute for `{{PRJ_NAME}}`-only.  
3. Hardcode deposit, stage, HOME, or archive filenames into `path` or `args`.  
4. Elevate `{{USER_BIN}}/{{PRJ_NAME}}`.  
5. Grant `{{PRJ_NAME}}` with no verb when `{{RUNAS}}` is `root`. Empty `args` is legal **only** for Type 2 LPU + Table A whole-binary.  
6. Duplicate submit/install workflow law here (**`LM-THREE-LAYER-PRIVILEGE-MODEL`**).  
7. Embed **`RQ-*`** as portable vocabulary.  
8. Cite this mold as product-source authority after specialize.  
9. Store secrets in the JSON body.  
10. Treat a re-encode that dropped `commands[]` objects as the same grant because `purpose` survived.  
11. Mark emit-only substring tests as inbound fidelity.  
12. Require minified `},{` only so a whitespace-intolerant decoder can stay.  
13. Make submit, inbound, or a deleted temp the only way to obtain this JSON for tests or review.  
14. Collapse `type-2-switch` and `login-hook-elev` into one body, drop `kind` when both grants exist, or let Type 0 `{{SUBMIT_SUDOER_CMD}}` queue `login-hook-elev`.  
15. Label a Type 1 deposit grant (`username` = invoker, `runas` = root, elev verbs) as `login-hook-elev`.  
16. Apply dest Type 0 self-scope (`username` == `id -un`) to Type 1 `setup`, call dest Type 0 `add-sudoer-request` for `login-hook-elev`, or treat that dest check as a safety net.  
17. Confuse **who may submit** (current login, Type 0, no sudo) with **who may setup** (host admin, Type 1, password `sudo` / already root).  
18. Treat Type 1 `setup` dest as `/etc/sudoers.d/{{APP_NAME}}-{{TARGET_USER}}`, or Type 0 submit dest as `/etc/sudoers.d/{{APP_NAME}}-{{LPU_USER}}`. Hook dest is **`{{LPU_USER}}`**; switch dest is the **invoker**.  
19. `chown` dest inbound JSON from Type 1 `setup` or Type 0 submit. Dest `{{APPROVER}}` takes ownership.  
20. Add a dest inbound fence that is not **incorrect JSON format** (who submitted, dest Type 0 self-scope, JSON username ≠ dest LPU).  
21. Emit Cmnd args with raw `:`, `#`, or `,` (unescaped `user:group` is illegal sudoers).  
22. Expand a trailing `*` as a shell glob when rendering or parsing.  
23. Split a `NOPASSWD` Cmnd on the **last** colon (that breaks `\:` in args).  
24. Say “host validation” or “host sudoers checker” when visudo rejects.  
25. Dest-write or queue add/update when visudo rejects.  
26. Use `"*"` as `--ownership` or as [ownership wildcard](../../terminologies/ownership-wildcard.md). `--ownership` **MUST** be `{{USER}}:{{GROUP}}`.
27. Emit `login-hook-elev` `commands[].path` as `{{GLOBAL_BIN}}/{{PRJ_NAME}}` (it **MUST** be the [login-hook-symlink](../../terminologies/login-hook-symlink.md)), overwrite an existing hook name, or create that live name from test-mode.

**Violating this rule is a critical privilege / complexity-as-insecurity regression.**

## 6. How to specialize

1. Create `docs/requirements/requirement-sudoer-json-file.md` via **`SK-CREATE-SPECIFIC-REQUIREMENT`**.  
2. Fill Implementation Notes (`{{PRJ_NAME}}`, `{{GLOBAL_BIN}}`, `{{RUNAS}}`, args). **A Type 2 / LPU product MUST specialize this file** — do not leave JSON submit only on a sibling deposit product.  
2a. A **dest** that materializes sibling grants **MUST** specialize §3.4d (visudo-legal text dual) even when inbound `commands[].path` is not `{{GLOBAL_BIN}}/{{PRJ_NAME}}`. Stay-honest: do not claim §3.1 command identity for those sibling grants.  
3. Point three-layer / domain REQs at that file for **JSON body** (own-grant products) or at the dest grant-file REQ for **text dual / visudo** (dest products).  
4. Register `docs/requirements/index.md`.  
5. Seed proof from **`PM-SUDOER-JSON-FILE-TEST-PLAN`**.  
6. Product source cites the **requirement**, not this template.

## Design-time verification

| TP family (portable) | Intent |
|----------------------|--------|
| **TP-SUDOER-JSON-01** | `type-2-switch` path is `{{GLOBAL_BIN}}/{{PRJ_NAME}}`; `login-hook-elev` path is `{{GLOBAL_BIN}}/{{APP_NAME}}-hook` |
| **TP-SUDOER-JSON-02** | No `mkdir`/`cp`/`tar`/`rm`/`install`/`chmod` in JSON |
| **TP-SUDOER-JSON-03** | No deposit/stage path and no `*.tar.gz` in JSON |
| **TP-SUDOER-JSON-06** | Pretty multi-command JSON survives convert / submit re-encode (every `args`) |
| **TP-SUDOER-JSON-08** | Independent generate dest is invoking-user readable; suite `cat`s without sudo |
| **TP-SUDOER-JSON-10** | Generate writes `kind` when §3.0 applies |
| **TP-SUDOER-JSON-11** | `--kind login-hook-elev` body: LPU username, `runas` root, args `{{REVIEW_VERB}}`, path `{{APP_NAME}}-hook` |
| **TP-SUDOER-JSON-12** | Type 0 submit of `login-hook-elev` fails closed |
| **TP-SUDOER-JSON-13** | Type 1 setup auto-queues hook kind when sibling dest exists |
| **TP-SUDOER-JSON-14** | Setup skips auto-queue when sibling dest is missing |
| **TP-SUDOER-JSON-15** | Specialized law names both kinds (when both grants exist) |
| **TP-SUDOER-JSON-17** | Specialized law names both sibling dests + F6 (do not collapse) |
| **TP-SUDOER-JSON-18** | Setup / Type 0 submit does not `chown` dest inbound |
| **TP-SUDOER-JSON-20** | Dest inbound fence is incorrect JSON format only (closed table) |
| **TP-SUDOER-JSON-21** | Convert emits escaped colon args (`user\:group`); visudo -cf Pass |
| **TP-SUDOER-JSON-22** | Trailing `*` operand is not glob-expanded; visudo -cf Pass |
| **TP-SUDOER-JSON-23** | visudo reject names visudo; quotes syntax; Next convert; no “host validation” |

Product suites **SHOULD** rename to `TP-<SUBJECT>-*` after specialize. Proof mold: **`PM-SUDOER-JSON-FILE-TEST-PLAN`**. Gates: **`CL-CREATE-SUDOERS-SECURITY`** (**S14** emit / kind split · **S15** inbound/convert fidelity · **S16** independent generate dest) · **`CL-LEAST-PRIVILEGE`** · **`CL-LLM-ESCAPE`**.

**Last Updated**: 2026-09-12 (1.14.0 shell CLI emit/wrap samples on **`LM-SHELL-SUDOER`**; config deposit **`LM-SHELL-CONFIG-BACKUP`**)  
**Owner**: {{OWNER}}  
**Alignment**: **`LM-THREE-LAYER-PRIVILEGE-MODEL`** · **`LM-FILE-BASED-JSON-APPROVAL-SUBMITTER`** · **`SK-CREATE-SUDOERS-FILE`** · **`PM-SUDOER-JSON-FILE-TEST-PLAN`** · terms `ownership-representation` · `ownership-wildcard` · [CIAO](https://github.com/cloudgen/ciao) / [CIAO-Lite](https://github.com/cloudgen/ciao-lite)
