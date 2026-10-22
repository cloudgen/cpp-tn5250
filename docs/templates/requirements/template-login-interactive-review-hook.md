---
name: login-interactive-review-hook
id: LM-LOGIN-INTERACTIVE-REVIEW-HOOK
kind: law-mold
description: >
  Portable law for a marker-guarded once-per-session login-rc snippet that
  launches an explicit review verb via sudo -n. Cite as
  LM-LOGIN-INTERACTIVE-REVIEW-HOOK. No RQ-* product IDs.
---

**file**: template-login-interactive-review-hook.md
**Mold-ID**: LM-LOGIN-INTERACTIVE-REVIEW-HOOK
**Status**: Active (Version 1.4.0 – [common-login-hook-name](../../terminologies/common-login-hook-name.md) + **MUST** `rc-test` · **`PP-A-24`** / **`PP-A-25`**)
**Project**: Any CIAO-Lite Project (reusable template)
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered / Over-protect)

**Folder structure (policy):** [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md). This file is a **law mold**. Specialize into `docs/requirements/requirement-*.md`. Product source cites the live requirement, never this mold.

## 1. Purpose

Portable MUST/MUST NOT for a [login-interactive-review-hook](../../terminologies/login-interactive-review-hook.md): an **idempotent, marker-guarded** interactive-rc snippet that starts **`{{GLOBAL_BIN}}/{{COMMON_LOGIN_HOOK_NAME}} {{REVIEW_VERB}}`** ([common-login-hook-name](../../terminologies/common-login-hook-name.md) · [login-hook-symlink](../../terminologies/login-hook-symlink.md)) once per TTY login of **one** least-privilege approver.

This mold owns **snippet + rc heal + login-hook-symlink create/rewrite**. It does **not** own dest inbound fence meaning, dest yes/no, or the `login-hook-elev` JSON body (that body **MUST** name the same symlink). Dest domain SSOT **points**; it **MUST NOT** remain the only owner of the snippet.

**Labeled name (sacred):** `{{GLOBAL_BIN}}/{{COMMON_LOGIN_HOOK_NAME}}` (production typical `/usr/local/bin/{{COMMON_LOGIN_HOOK_NAME}}`). Sibling host-mutating CLIs **MUST** reuse that **one** doorbell ([common-login-hook-name](../../terminologies/common-login-hook-name.md) — **`PP-A-25`**). **MUST NOT** invent a per-app `{{APP_NAME}}-hook` as a second live alias. **MUST NOT** overwrite if the common name already exists — a host admin or an earlier sibling **MAY** already point it at another similar program. **MUST NOT** make `{{APP_NAME}}` a symlink to the common name.

**Specialize into:** an **independent** `requirement-login-interactive-review-hook.md` (or `requirement-login-interactive-hook.md`). Dual-mention `{{REVIEW_VERB}}` on the CLI-interface REQ.

## 2. Terminologies

Related glossary entries (disk-truth). **SSOT type** uses the workspace taxonomy.

| Term | Path | SSOT type | Role |
|------|------|-----------|------|
| **Login interactive review hook** | `docs/terminologies/login-interactive-review-hook.md` | `runtime-mode` | Class this mold encodes |
| **Login-hook-symlink** | `docs/terminologies/login-hook-symlink.md` | `runtime-mode` | Alias class (create-if-absent, never overwrite) |
| **Common login-hook name** | `docs/terminologies/common-login-hook-name.md` | `runtime-mode` | Shared doorbell basename the snippet calls |
| **Shell-rc test fixture** | `docs/terminologies/shell-rc-test-fixture.md` | `product-law` | **MUST** `rc-test --root` when this mold is claimed |
| **Login-hook sudoer request** | `docs/terminologies/login-hook-sudoer-request.md` | `product-law` | Grant that makes `sudo -n` succeed — not this snippet |
| **Automatic login-hook sudoer submit** | `docs/terminologies/automatic-login-hook-sudoer-submit.md` | `product-law` | When Type 1 setup queues that grant |
| **Shell bashrc** | `docs/terminologies/shell-bashrc.md` | `runtime-mode` | Default plant file |
| **Shell profile** | `docs/terminologies/shell-profile.md` | `runtime-mode` | Login chain; create-if-absent only |
| **Shell-rc file ownership** | `docs/terminologies/shell-rc-file-ownership.md` | `identity-runtime` | Owner after create/rewrite |
| **Least-privilege-approver** | `docs/terminologies/least-privilege-approver.md` | `identity-runtime` | Whose login is hooked |
| **Interactive vs noninteractive** | `docs/terminologies/interactive-vs-noninteractive.md` | `runtime-mode` | Non-TTY skip |
| **Type O empty argv** | `docs/terminologies/type-o-empty-argv.md` | `product-law` | Empty argv stays help |
| **Least privilege** | `docs/terminologies/least-privilege.md` | `policy` | Only that home |
| **LLM escape** | `docs/terminologies/llm-escape.md` | `policy` | No root-by-convenience |
| **SSOT catalog** | `docs/terminologies/ssot-catalog.md` | `meta-catalog` | Inventory |
| **Docs folder structure** | `docs/terminologies/docs-folder-structure.md` | `policy` | Law vs proof |

**SSOT types used in this template:** `runtime-mode` | `product-law` | `identity-runtime` | `policy` | `meta-catalog`

**Missing terms:** none

**SSOT classification:**
- Concern: rc snippet text → Type `runtime-mode` → owner = specialized REQ Implementation Notes
- Concern: corresponding-user owner → Type `identity-runtime` → term `shell-rc-file-ownership`
- Concern: empty argv → Type `product-law` → CLI-interface REQ

## 3. Core rules (portable)

### 3.1 When this mold applies

The product **claims** login-time review. If it does not, mark N/A — do **not** plant a hook.

### 3.2 Install table

| File | When to write |
|------|----------------|
| Interactive rc (`{{HOME}}/.bashrc`) | **Always** (create if missing) — default |
| Login rc (`{{HOME}}/.profile`) | **Only if** it does **not** exist. Present → **MUST NOT** overwrite. Uncertain whether it sources bashrc → **do not** also plant the hook there |
| Other users’ rc | **Never** |

### 3.3 Snippet guards (sacred)

| Guard | Rule |
|-------|------|
| **Identity** | `id -un` equals `{{APPROVER}}` |
| **Interactive** | `PS1` set; `$-` contains `i`; `[ -t 0 ]` and `[ -t 1 ]` **in the snippet** (not the CLI `TTY` SSOT) |
| **scp / CI** | Skip when `SSH_ORIGINAL_COMMAND` is set |
| **Session** | Set `{{HOOK_RAN_VAR}}=1` **before** `sudo -n`; second source is a no-op |
| **Binary** | `sudo -n {{GLOBAL_BIN}}/{{COMMON_LOGIN_HOOK_NAME}} {{REVIEW_VERB}}` — [common-login-hook-name](../../terminologies/common-login-hook-name.md). **MUST NOT** copy live `$GLOBAL_BIN`. Type 2 switch stays `{{GLOBAL_BIN}}/{{APP_NAME}}` |
| **Live grant** | Needs `kind=login-hook-elev`. Body: **`LM-SUDOER-JSON-FILE`**. Queue: **`LM-THREE-LAYER-PRIVILEGE-MODEL`**. This mold does **not** write `/etc/sudoers.d` |
| **`sudo -n` fail** | Warning on stderr; login **continues** (`exit` forbidden) |
| **Idempotent file** | Begin/end markers; do not append twice |
| **F7** | Strip the marker block from **whichever** files contain it |
| **Empty argv** | Hook **MUST** call the explicit review verb. Empty argv stays help |
| **Tokens** | **MUST NOT** appear in rc |

Coverage **fails** on a one-liner “install in `.bashrc`”. The specialized REQ **MUST** include the **complete** snippet sample.

### 3.4 Complete snippet sample (template-example-function)

```sh
# BEGIN {{APP_NAME}} login hook
if [ -z "${{{HOOK_RAN_VAR}}:-}" ] \
    && [ -n "${PS1:-}" ] \
    && [ -t 0 ] && [ -t 1 ] \
    && case "$-" in *i*) true ;; *) false ;; esac \
    && [ "$(id -un)" = "{{APPROVER}}" ] \
    && [ -z "${SSH_ORIGINAL_COMMAND:-}" ]; then
    {{HOOK_RAN_VAR}}=1
    export {{HOOK_RAN_VAR}}
    if ! sudo -n {{GLOBAL_BIN}}/{{COMMON_LOGIN_HOOK_NAME}} {{REVIEW_VERB}}; then
        printf '%s\n' "{{APP_NAME}}: login review hook skipped (sudo -n failed)" >&2
    fi
fi
# END {{APP_NAME}} login hook
```

### 3.5 Complete `.profile` create sample (only when absent)

```sh
# BEGIN {{APP_NAME}} profile source-bashrc
# Created so a bash login shell sources interactive rc (hook lives in .bashrc).
if [ -n "${BASH_VERSION:-}" ]; then
    if [ -f "${HOME}/.bashrc" ]; then
        . "${HOME}/.bashrc"
    fi
fi
# END {{APP_NAME}} profile source-bashrc
```

### 3.6 Heal when interactive and invoker is the approver

When the process is interactive (`TTY=1`) **and** JSON is not 1 **and** `id -un` equals `{{APPROVER}}` (or a named test override):

1. Check `{{HOME}}/.bashrc` for begin/end markers. If missing, **append** the complete snippet (calls the [common-login-hook-name](../../terminologies/common-login-hook-name.md)). If the block is present and still runs `sudo -n {{GLOBAL_BIN}}/{{APP_NAME}} {{REVIEW_VERB}}` **or** `{{APP_NAME}}-hook`, **rewrite** that line to `{{COMMON_LOGIN_HOOK_NAME}}`. Create `.bashrc` if absent. **MUST NOT** duplicate the block.
2. Check `{{HOME}}/.profile`. Absent → create with §3.5. Present → **MUST NOT** overwrite.
3. **MUST NOT** write another user’s home.
4. **MUST NOT** write if `HOME` is `/tmp` or under `/dev/shm`.
5. Heal **MUST** be idempotent (one hook block; one profile create).
6. Heal **MUST NOT** change help/version human output (debug only).
7. After every create or rewrite: align [shell-rc file ownership](../../terminologies/shell-rc-file-ownership.md) to the corresponding user. Writer euid **MUST NOT** remain the owner. `chown` failure is **fail closed** when the account exists. Compose **`SK-CREATE-SHELL-BASHRC`** + **`SK-CREATE-SHELL-PROFILE`**.
8. Type 1 `setup` **MUST** run the same heal on the new `{{APPROVER}}` home.
9. Type 1 `setup`, when `{{GLOBAL_BIN}}/{{APP_NAME}}` exists, **MUST** create the [common-login-hook-name](../../terminologies/common-login-hook-name.md) symlink (`ln -s {{GLOBAL_BIN}}/{{APP_NAME}} {{GLOBAL_BIN}}/{{COMMON_LOGIN_HOOK_NAME}}`) if that name is absent. **MUST NOT** overwrite an existing common name (sibling-app retarget). **MUST NOT** `ln -s` the common name onto `{{APP_NAME}}`. Test-mode **MUST NOT** write the live global name. F7 **MUST NOT** unlink it. Sibling products **MUST** share that **one** filename (**`PP-A-25`**). Dual-mention Type 0 **`rc-test --root`** when this mold is claimed (**`PP-A-24`**).
10. Type 1 `setup` **and** dest `{{REVIEW_VERB}}` **MUST** review `{{APPROVER}}` rc per **§3.9**.

Test override (specialize names): skip TTY when `{{TEST_HEAL_RC}}=1`; override identity with `{{APPROVER_USER_ENV}}`.

### 3.9 Review old product-binary hook on the dedicated account

Type 1 `setup` **and** dest `{{REVIEW_VERB}}` **MUST** review the dedicated approver’s login rc (`{{HOME}}/.bashrc`, and `.profile` when that file contains the hook).

| Finding | MUST |
|---------|------|
| Rc still `sudo -n`s `{{GLOBAL_BIN}}/{{APP_NAME}} {{REVIEW_VERB}}` (old product-binary hook) **or** `{{APP_NAME}}-hook` | Replace with `{{GLOBAL_BIN}}/{{COMMON_LOGIN_HOOK_NAME}} {{REVIEW_VERB}}` |
| Rc already `sudo -n`s `{{GLOBAL_BIN}}/{{COMMON_LOGIN_HOOK_NAME}} {{REVIEW_VERB}}` | **MUST NOT** rewrite |
| `.profile` sources `.bashrc` and still has the old hook | Strip the profile copy; **MUST NOT** plant a second snippet there |
| Dedicated home missing (tests / not yet created) | No-op |
| Any other user’s rc | **MUST NOT** inspect or write |

Old hosts keep working because the product-binary F6 grant still starts `{{REVIEW_VERB}}`; that run **MUST** then replace the rc so the next login uses the labeled name. **MUST NOT** hang. **MUST NOT** `exit` the login shell.

### 3.7 Review verb (compose, do not fork)

The review verb itself (take file-ownership first, fence first, one-off yes/no) stays on **`LM-FILE-BASED-JSON-APPROVAL`** §2.8. This mold only **starts** that verb.

### 3.8 Language implement skills

How to write heal in product source:

| Language | Skill-ID |
|----------|----------|
| POSIX shell | **`SK-SH-LOGIN-INTERACTIVE-HOOK`** |
| Python PyPI CLI | **`SK-PYTHON-LOGIN-INTERACTIVE-HOOK`** |
| Node.js CLI | **`SK-NODEJS-LOGIN-INTERACTIVE-HOOK`** |
| Rust CLI | **`SK-RUST-LOGIN-INTERACTIVE-HOOK`** |

Day coding skills **compose** those; they do not fork a second guard table.

## 4. How to specialize

1. Collision-check `docs/requirements/index.md`. Prefer **one independent Active** owner of rc heal (`requirement-login-interactive-review-hook`). Domain SSOT **points**.
2. Fill every `{{PLACEHOLDER}}` (`{{APP_NAME}}`, `{{COMMON_LOGIN_HOOK_NAME}}`, `{{APPROVER}}`, `{{REVIEW_VERB}}`, `{{HOOK_RAN_VAR}}`, `{{GLOBAL_BIN}}`, markers).
3. Dual-mention `{{REVIEW_VERB}}` on the CLI-interface REQ **and** this topic-owner.
4. Register the row. Related: **peer requirements only** (git-surface: no `docs/templates/**`).
5. Product source cites the live `requirement-*.md`.
6. Run **`CL-LOGIN-INTERACTIVE-REVIEW-HOOK`**. Proof: **`PM-LOGIN-INTERACTIVE-REVIEW-HOOK-TEST-PLAN`**.

## 5. Design-time verification

Default TP family after specialize: **`TP-HOOK-01..09`** (product may keep an existing family such as **`TP-SR-HOOK-*`**). Gate: **`CL-LOGIN-INTERACTIVE-REVIEW-HOOK`**. Privilege: **`CL-LEAST-PRIVILEGE`**.

| Token | Intent |
|-------|--------|
| HOOK-01 | Interactive approver heals `.bashrc` markers + `sudo -n` + review verb |
| HOOK-02 | Missing `.profile` created and sources `.bashrc` |
| HOOK-03 | Existing `.profile` unchanged |
| HOOK-04 | Non-approver does not write rc |
| HOOK-05 | `--json` / non-interactive does not heal |
| HOOK-06 | Second heal idempotent |
| HOOK-07 | Heal aligns owner (`chown` helper present) |
| HOOK-08 | Heal rewrites old `{{GLOBAL_BIN}}/{{APP_NAME}}` and old `{{APP_NAME}}-hook` lines to `{{COMMON_LOGIN_HOOK_NAME}}`; setup ensure-symlink skips test-mode live `ln`; **MUST NOT** reverse-symlink `{{APP_NAME}}` |
| HOOK-09 | Dest `{{REVIEW_VERB}}` reviews `{{APPROVER}}` rc: old product-binary / `*-hook` becomes `{{COMMON_LOGIN_HOOK_NAME}}`; already-common is not rewritten |

## Under command line for normal user only

When the product may run on Termux, Git Bash, Windows cmd, or the same class: Type 1/2 unused on detect; no in-tool sudo / apt / dedicated system user; no `sudo curl | sh` recommend; Git Bash and Windows cmd do not invoke Termux `pkg`.

**This mold:** do not plant a login hook, do not create `{{GLOBAL_BIN}}/{{COMMON_LOGIN_HOOK_NAME}}`, do not recommend `sudo -n` review on that class.

## 6. Protection Rule (Sacred)

**MUST NOT**:

1. Hijack empty argv as the review verb.
2. Overwrite an existing `.profile` body.
3. Plant the hook in another user’s rc.
4. Hang scp / CI / non-TTY (`sudo` without `-n`, or `exit` on `sudo -n` fail).
5. Put a token in `.bashrc` or `.profile`.
6. Leave rc owned by the writer after create/`mktemp`+`mv`.
7. Treat rc heal as the `login-hook-elev` grant.
8. Claim this mold is product-source behavioral authority.
9. Dump harness paths into versioned `docs/requirements/**`.
10. Write under `/tmp` or `/dev/shm` as `HOME`.
11. Call the product binary from the snippet instead of the [common-login-hook-name](../../terminologies/common-login-hook-name.md), overwrite an existing common name, reverse-symlink `{{APP_NAME}}` onto the doorbell, or create that live name from test-mode.
12. Leave the snippet only on dest domain SSOT after specialize (independent REQ **MUST** own it).
13. Invent a per-app `{{APP_NAME}}-hook` as a second live doorbell so siblings cannot share `{{COMMON_LOGIN_HOOK_NAME}}` (**`PP-A-25`**).
14. After Type 1 `setup` or dest `{{REVIEW_VERB}}`, leave `{{APPROVER}}` rc calling `{{GLOBAL_BIN}}/{{APP_NAME}} {{REVIEW_VERB}}` or `{{APP_NAME}}-hook` instead of `{{COMMON_LOGIN_HOOK_NAME}}`.
15. Rewrite rc that already uses the common name, or inspect another user’s rc.
16. Claim this mold without dual-mentioning Type 0 **`rc-test --root`** (**`PP-A-24`**).

---

**Last Updated**: 2026-09-09
**Version history:**
- **1.4.0** (2026-09-09): Snippet + grant + setup symlink use [common-login-hook-name](../../terminologies/common-login-hook-name.md); siblings **MUST** share one doorbell (**`PP-A-25`**). Dual-mention **`rc-test --root`** (**`PP-A-24`**). **MUST NOT** reverse-symlink `{{APP_NAME}}`. **HOOK-08** / **HOOK-09** rewrite old `*-hook` too.
- **1.3.0** (2026-09-08): **§3.9** dest `{{REVIEW_VERB}}` reviews `{{APPROVER}}` rc; old product-binary hook **MUST** become `{{APP_NAME}}-hook`; already-new **MUST NOT** rewrite. **HOOK-09**.
- **1.2.0** (2026-09-08): Specialize into an **independent** login-hook REQ; sibling CLIs reuse `/usr/local/bin/{{APP_NAME}}-hook`; domain **points**.
- **1.1.0** (2026-09-03): Snippet + grant identity is [login-hook-symlink](../../terminologies/login-hook-symlink.md); setup creates when missing; heal rewrites old binary path; **HOOK-08**.
**Owner**: {{OWNER}}
**Alignment**: term `login-interactive-review-hook` · **`LM-FILE-BASED-JSON-APPROVAL`** §2.8–2.9 · **`SK-CREATE-SHELL-BASHRC`** · **`SK-CREATE-SHELL-PROFILE`** · language skills **`SK-SH-LOGIN-INTERACTIVE-HOOK`** / **`SK-PYTHON-LOGIN-INTERACTIVE-HOOK`** / **`SK-NODEJS-LOGIN-INTERACTIVE-HOOK`** / **`SK-RUST-LOGIN-INTERACTIVE-HOOK`** · [CIAO](https://github.com/cloudgen/ciao)
