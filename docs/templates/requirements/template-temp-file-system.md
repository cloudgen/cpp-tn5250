---
name: temp-file-system
id: LM-TEMP-FILE-SYSTEM
kind: law-mold
description: >
  Portable law mold. Cite as LM-TEMP-FILE-SYSTEM (path secondary).
---

**file**: template-temp-file-system.md  
**Status**: Active (Version 1.3.0 – temp maker may be absent; directory 0600 is not searchable)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

# Template: Temporary File System (SSOT)

## 1. Purpose

This template is the **portable single source of truth (SSOT)** for **temporary / scratch file and directory policy** in CIAO-style projects.

**All other templates, skills, checklists, and terminologies that touch temp paths MUST refer here** for the normative pattern—not restate a second private chain, a second umask policy, or a second cleanup story.

| Layer | Role |
|-------|------|
| **This template** | Reusable **pattern law** (`{{PLACEHOLDER}}`) for agents specializing requirements and implementing code |
| **Terminology** [`temp-file-system.md`](../../terminologies/temp-file-system.md) | Glossary + must-not-confuse; points at this template as pattern SSOT |
| **CIAO principles** (product root `README.md`) | Philosophy: **Principle 11** (temps), **Principle 22** (modes/umask) |
| **Idempotency** [`idempotency-rule.md`](../../terminologies/idempotency-rule.md) | Re-run safety for ensure-style work that uses temps |
| **Atomic-*** terms | How temps are used when **publishing** durable files |
| **Live `requirement-*.md`** | Project specialization (only after fill-in; product law) |

Agents load this file when implementing or reviewing temp creation, install staging, atomic write staging, or Temp singletons. **Do not** paste this path into product source as `ALIGNMENT` authority—specialize a requirement or implement; cite live `requirement-*.md` only in product comments.

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
| **Temp file system** | `docs/terminologies/temp-file-system.md` | `runtime-mode` | Primary scratch policy |
| **Atomic file copy** | `docs/terminologies/atomic-file-copy.md` | `runtime-mode` | Stage then rename |

**SSOT types used:** `meta-catalog` · `policy` · `runtime-mode`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Core invariants (MUST)

1. **Never assume** a temp root exists, is writable, is large enough, or is **exec**-capable (`noexec` mounts exist).  
2. **Never** use predictable sensitive names (e.g. `/tmp/{{APP_NAME}}.tmp`, `/tmp/.cache-$$` alone as the only entropy). Prefer **`mktemp` / `mktemp -d`** or language-equivalent safe APIs.  
3. **Always** try a **documented fallback chain** of roots until one works; if none work, **fail loud** via the project Output SSOT.  
4. **Isolate** multi-user / multi-process use (app identity + user and/or PID or equivalent) when the project’s temp policy requires shared mounts.  
5. **Clean up** temps: `trap` / deferred cleanup / language `finally`—idempotent (safe if already gone).  
6. **Permissions:** follow **CIAO Principle 22** — prefer **`chmod` / `install -m` / API open modes** on the **path**; process **`umask` seldom**; if umask is SET, **always RESET**. Do **not** put sticky `umask 077` at script top as complete policy.  
7. **Atomic publish:** `write temp → verify → mv/rename`. **`mv` keeps mode**—set intended final mode on the file (Principle 22). Prefer same-filesystem staging as the final path when rename atomicity matters.  
8. **Idempotency:** re-runs must not pile orphan temps, thrash, or fail solely because a support dir already exists (`mkdir -p` / ensure style). See [`idempotency-rule.md`](../../terminologies/idempotency-rule.md).  
9. **SSOT of path resolution:** one resolver / Temp module / shell helper family—not ad-hoc `/tmp/...` in every command.  
10. **No-hardcode:** this template stays portable (`{{APP_NAME}}`, `{{TMP_FS}}`, `{{USERNAME}}`, `{{PID}}`, `{{USER_CACHE}}`). Real roots live in Config / specialized requirements / product README—not frozen into this blank.  
11. **Temp maker:** check that `mktemp` exists and can create the leaf before `mktemp` / `mktemp -d`. When it is absent or the create fails, the leaf is a unique subdirectory of the already resolved cache folder. **MUST NOT** fall back to a bare `/tmp/{{APP_NAME}}.tmp`. The name is not a `$$`-only name (**PP-A-29**).  
12. **Directory mode:** `mkdir` and `mktemp -d` apply umask. Mode **0600** (`drw-------`) exists and cannot be searched. `chmod` does not apply umask. Set mode **0700** and require searchable and writable **before** any file. Cleanup sets **0700** again. A fallback **file** is mode **0600**. That file mode is not **PP-A-28** (shebang `chmod +x` → **0711**).

---

## 3. Two legitimate root families (do not collapse)

Projects may need **both**. Name which family a code path uses.

### 3.1 Install / download / config staging (aligns with CIAO Principle 11)

Use when staging a **download or atomic install** that will be promoted to a durable path:

```text
1. $TMPDIR          (if set and usable)
2. /tmp
3. /var/tmp
4. {{USER_CACHE}}   (e.g. $HOME/.cache or ~/Library/Caches — create with ensure/mkdir -p)
5. CWD              (last resort only; warn via Output SSOT)
else fail loud
```

Ship-unit reference shape (pattern, not product law): `secure_mktemp`-style helper in shell self-managed CLIs (e.g. project `examples/*/src/{{APP_NAME}}` when present).

### 3.2 Volatile app scratch / debug captures (shm-first family)

Use for **short-lived app scratch**, prompt files, HTTP debug dumps—not as the only story for install binaries:

```text
1. /dev/shm exists                     mkdir isolated child or …/cache (fail-soft)
2. Detect-specific
   - Termux: $PREFIX/tmp (create if needed)
   - Git Bash: $HOME/AppData/Local/Temp exists → mkdir $HOME/AppData/Local/Temp/cache
     else {{GIT_BASH_DRIVE}}/Users/{{USERNAME}}/AppData/Local/Temp/cache (default /c/)
3. $TEMP defined and exists            mkdir $TEMP/cache (fail-soft)
4. /tmp exists                         mkdir /tmp/cache (fail-soft); else /tmp
else fail loud at the END of the chain
```

**MUST NOT** `out_die` / `exit` because `mkdir` of a `cache` leaf failed. **MUST NOT** use `$HOME/.cache` as the Git Bash **volatile** root.

**Node house pattern (when using singletons):** all temp/debug captures via **Temp** SSOT —  
`{{TMP_FS}}/{{USERNAME}}/{{PID}}/…` — never ad-hoc paths in commands.

### 3.3 Coupling to shell CLI storage (when both Active)

When product law specializes **both** `LM-SHELL-CLI-STORAGE` and this mold:

| Layer | Owner mold | Owns |
|-------|------------|------|
| **Root** | `LM-SHELL-CLI-STORAGE` | Resolve priority, isolation, create-before-return, `EFFECTIVE_STORAGE_DIR` |
| **Leaves** | **This mold** | Unique `mktemp` names, trap/cleanup, modes, atomic stage→publish |

**Normative bridge:** `app_main` (or equivalent) **SHOULD** export `TMPDIR=${EFFECTIVE_STORAGE_DIR}` after storage resolve so `mktemp -t` lands under the isolated product root.  
**MUST NOT** invent a second product-wide root chain that contradicts the storage REQ.  
**MUST NOT** treat domain timer epoch records (named-timer domain) as install temps.  
When the temp maker is absent, the leaf is still a child of the root **`LM-SHELL-CLI-STORAGE`** already resolved (**PP-A-29**). This mold owns that leaf rule. The storage mold does not restate it.

Related: `template-shell-cli-storage.md` · `template-named-timer-domain.md` (domain records ≠ temps).

---

## 4. Isolation rules

| Rule | Why |
|------|-----|
| Include **app** identity (`{{APP_NAME}}`) where shared mounts are used | Avoid tool clashes |
| Include **user** (or equivalent) when multi-user hosts are in scope | Cross-user safety |
| Include **PID** / session id when concurrent processes share a root | Collision resistance |
| Unpredictable leaf names (`mktemp` when the maker works) | CWE-377 / symlink races |
| Scratch directory mode **0700** before any file | Mode **0600** cannot be searched (**PP-A-29**) |
| Do not assume **exec** on temp mounts | `noexec` |

---

## 5. Lifecycle & helpers (portable expectations)

### 5.1 Shell (POSIX `/bin/sh` spirit)

| Expectation | Detail |
|-------------|--------|
| Central helper | e.g. `secure_mktemp` / `util_mktemp` — **one** entry for unique files |
| Maker check | Use `mktemp` only when it exists and the create succeeds. Otherwise a unique subdirectory of the resolved cache folder (**PP-A-29**) |
| Fallback loop | Try §3.1 or §3.2 roots; assign path variable **before** use (`skill-sh-script-coding` fallback rule) |
| Register + trap | Track paths; `trap` cleanup on EXIT/INT/TERM; **unregister** after successful `mv` to final install path. Cleanup of a scratch directory sets mode **0700** again |
| Modes | Principle **22**: `chmod` / `install -m` on temp and/or final path. A directory at **0600** is not usable. A fallback file is **0600** |
| Pipeline returns | Path returned via stdout for `$(…)` is **SSOT-of-pipeline**—mark SSOT REMARK; not product UX |

### 5.2 Node / Python / other

| Expectation | Detail |
|-------------|--------|
| Single Temp / path module | Resolves `{{TMP_FS}}` chain once |
| No scatter | Commands must not invent second temp policies |
| Same invariants | Unique names, cleanup, fail loud, Principle 22 modes |

### 5.3 Coupling to atomic publish

```text
template-temp-file-system  →  safe root + unique name + cleanup
        │
        ├── atomic-file-copy / install stage → FINAL
        ├── atomic-data-file
        └── atomic-file-edit (often + backup Principle 12)
```

---

## 6. Anti-patterns (forbidden in specialized code)

| Forbidden | Prefer |
|-----------|--------|
| Fixed `/tmp/{{APP_NAME}}.out` | `mktemp` under resolved root when the maker works; else a mode-**0700** child of that root |
| Call `mktemp` when it is not installed | Check the maker first (**PP-A-29**) |
| Write a file into a directory at **0600** | `chmod 0700` and require search plus write first |
| Bare shared `/tmp` dump without isolation | App + user + PID (or Temp SSOT) |
| Assume `/dev/shm` always exists | Fallback chain + loud fail |
| Sticky process `umask 077` whole script | Path `chmod` / Principle 22 |
| Second private temp policy in a random template | **Refer to this SSOT** |
| Cite this template path as product-source ALIGNMENT | Live `requirement-*.md` only |
| Copy stale `mktemp -t` only, no fallback | Implement §3 chain |

---

## 7. Protection rule (sacred)

**Future AI assistants and maintainers MUST NOT:**

- Remove the fallback chain or replace it with a single hard-coded `/tmp`.  
- Call `mktemp` without checking the maker, or treat a directory at **0600** as usable (**PP-A-29**).  
- Weaken cleanup/trap expectations “for simplicity.”  
- Reintroduce sticky whole-script `umask 077` as the primary temp control.  
- Duplicate a conflicting temp chain in other templates/skills instead of **linking here**.  
- Specialize this template by baking one product’s absolute host paths into the blank SSOT file.

**Direct CIAO alignment:** Principles **1**, **3**, **11**, **22**; Intentional verbosity for Protection Zones on resolvers.

---

## 8. Referrer contract (for other docs)

Any template or skill that mentions temporary files **MUST**:

1. **Link** to `docs/templates/requirements/template-temp-file-system.md` as the pattern SSOT.  
2. **Not** restate a full alternate root chain (one-line “see SSOT §3” is enough).  
3. **Specialize** project choices into `docs/requirements/requirement-*.md` when product law is needed.  
4. Keep **checklists** as gates that point here (unique name, fallback/fail-loud, trap, modes, idempotent re-run).

---

## 9. Definition of done (specialization / implementation)

- [ ] Project documents which family (§3.1 and/or §3.2) each feature uses  
- [ ] Writable-root fallback implemented or fail-loud proven  
- [ ] Unique names (`mktemp` when the maker works; otherwise a token under the cache folder)  
- [ ] Directory mode **0700** and searchable before any file  
- [ ] Cleanup on success and failure paths (scratch directory set to **0700** again)  
- [ ] Final publish modes correct (Principle 22)  
- [ ] Re-run does not orphan temps (idempotency)  
- [ ] No second conflicting temp policy in other modules  
- [ ] If product law written: live `requirement-*.md` registered; this template not cited as runtime authority in source  

---

## 10. Related artifacts

| Artifact | Relationship |
|----------|----------------|
| [`../terminologies/temp-file-system.md`](../../terminologies/temp-file-system.md) | Glossary; defers pattern body to this SSOT |
| [`../terminologies/idempotency-rule.md`](../../terminologies/idempotency-rule.md) | Re-run safety |
| [`../terminologies/atomic-file-copy.md`](../../terminologies/atomic-file-copy.md) | Publish protocol |
| [`template-shell-cli-storage.md`](./template-shell-cli-storage.md) | Root resolve peer when both Active; TMPDIR bridge |
| [`template-online-install.md`](./template-online-install.md) | Must refer here for install staging temps |
| [`template-automatic-checksum.md`](./template-automatic-checksum.md) | Companion download stage temps |
| [`template-self-management.md`](./template-self-management.md) | Shared install primitives |
| [`checklists/checklist-online-install-script.md`](../checklists/checklist-online-install-script.md) | Review gate § temp |
| [`../skills/skill-online-install-self-management.md`](../../skills/skill-online-install-self-management.md) | Agent harness |
| [`../skills/skill-sh-script-coding.md`](../../skills/skill-sh-script-coding.md) | Shell implementation discipline |
| [`../skills/skill-system-architecture-design.md`](../../skills/skill-system-architecture-design.md) | Architecture isolation |
| CIAO product principles | Principle **11** (temps), **22** (modes/umask) |

---


## Design-time verification

| TP family / ID | Proof mold | Planned suite / intent |
|----------------|------------|------------------------|
| **TP-LC-06** / **TP-LC-12** install force / install JSON | `../tests/template-install-lifecycle-test-plan.md` | Download/stage uses unique `mktemp` leaves |
| **TP-CSUM-02..04** companion stage | `../tests/template-checksum-test-plan.md` | Companion sidecar stage temps |
| **TP-CLI-05** storage root for TMPDIR | `../tests/template-shell-cli-test-plan.md` | Effective storage root exists (parent of install temps when wired) |
| **TP-TEMP-01** trap/cleanup matrix (optional) | product suite or checklist | Only if product claims full trap inventory; else **n/a** with reason |
| **TP-TMP-01** static no `$$` scratch | product CLI suite | When convert/scratch is live |
| **TP-TMP-02** convert still works | product domain suite | After leaf change |
| **TP-TX-09** Git Bash AppData Local Temp/cache | `../tests/template-shell-termux-ish-test-plan.md` | When Git Bash is a claimed target |
| **TP-TX-10** mkdir cache fail-soft | same | `cache` as a file must not abort; next root |
| **TP-TX-11** `/c/` detect | same | Source probes `/c/` or `/c` |
| **TP-TX-12** default-drive Temp | same | `/c/Users/{{USERNAME}}/AppData/Local/Temp/cache` |

**RTM:** `../tests/template-requirement-test-traceability.md` · cite **`LM-TEMP-FILE-SYSTEM`**

When a row does not apply, mark **n/a** with reason in product `reviews/test-plan.md`.

**Last Updated**: 2026-09-30  
**Owner**: Defensive core / path & install layer  
**Version history:**  
- **1.3.0** (2026-09-30): Temp maker is not on every OS. A directory at **0600** cannot be searched. Fallback leaf is a mode-**0700** child of the resolved cache folder (**PP-A-29**).  
- **1.2.0**: Git Bash `/c/` cache leaf + mkdir fail-soft (never mid-chain die).  
- **1.1.0**: Storage-root coupling (§3.3); explicit TP DTV (LC/CSUM/CLI-05).  
- **1.0.0**: Initial SSOT chain + invariants.  

**Alignment**: CIAO Principles 11 & 22 (https://github.com/cloudgen/ciao); CIAO-Lite Protection Zones; dual policies (no-hardcode in this blank).

---

**How to use this template**:

1. Keep under `docs/templates/requirements/` as the **only** portable temp-policy body.  
2. Other templates/skills **link here**—do not fork the chain.  
3. Specialize into `docs/requirements/requirement-*.md` when the project needs enforceable product law.  
4. Implement resolvers in code; optional ship-unit demos may illustrate `secure_mktemp`-style helpers.  
5. Run install checklist (or project equivalent) when install staging is in scope.  
