---
name: cron-job
id: LM-CRON-JOB
kind: law-mold
description: >
  Portable law mold for a Type 0 user-crontab ensure (typical verb add-crontab).
  Cite as LM-CRON-JOB (path secondary). No RQ-* product IDs. No session Unix login.
---

**file**: template-cron-job.md  
**Mold-ID**: **`LM-CRON-JOB`**  
**Status**: Active (Version 1.0.0)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered / Over-protect)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

## 1. Purpose

This template is the portable **cron-job** pattern: a Type 0 CLI verb that **ensures this login’s user crontab** contains studied lines that invoke **this product’s** live commands on a schedule.

**Specialize into:** `requirement-cron-job.md` or `requirement-{{APP_NAME}}-crontab.md` with filled Implementation Notes (schedules, verbs, grant Cmnd). Product source cites that **requirement** — never this template path.

**Not:** elapsed named-timer domain (**`LM`** peers for external-timer); host `/etc/cron.d`; writing `/etc/sudoers.d`.

---

## Terminologies

Related glossary entries (**disk-truth**). Templates **point**; they do not redefine terms or act as product law.
SSOT types follow `docs/policies/policy-ssot-terminology-for-templates.md`.
Binding rules: `docs/policies/policy-terminology-for-templates.md`.

| Term | Path | SSOT type | Role |
|------|------|-----------|------|
| **Cron-job** | `docs/terminologies/cron-job.md` | `product-law` | Word + fences for user-crontab ensure |
| **Operational verb** | `docs/terminologies/operational-verb.md` | `product-law` | Jobs run live product commands |
| **Idempotency rule** | `docs/terminologies/idempotency-rule.md` | `product-law` | No duplicate crontab lines |
| **Sudoer JSON file** | `docs/terminologies/sudoer-json-file.md` | `product-law` | Grant body the backup-style job needs |
| **Three-layer privilege** | `docs/terminologies/three-layer-privilege.md` | `product-law` | Crontab write is Type 0; sudo job uses approved grant |
| **External-timer** | `docs/terminologies/external-timer.md` | `product-law` | Near-miss: elapsed work clock, not crontab |
| **CLI routed-verb** | `docs/terminologies/cli-routed-verb.md` | `product-law` | Ensure verb must be live |
| **Least privilege** | `docs/terminologies/least-privilege.md` | `policy` | No extra sudoers tools; no other user’s fragment |
| **Non-expose local machine** | `docs/terminologies/non-expose-local-machine.md` | `policy` | `id -un` / `{{USERNAME}}` — no session login in the mold |
| **Project templates** | `docs/terminologies/project-templates.md` | `meta-catalog` | What law molds are |
| **Docs folder structure** | `docs/terminologies/docs-folder-structure.md` | `policy` | Where this mold lives |
| **No-hardcode policy** | `docs/terminologies/no-hardcode-policy.md` | `policy` | Placeholders only |
| **SSOT catalog** | `docs/terminologies/ssot-catalog.md` | `meta-catalog` | Inventory of SSOTs |

**SSOT types used:** `product-law` · `policy` · `meta-catalog`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md` · `docs/policies/policy-non-expose-local-machine.md` · `docs/policies/policy-least-privilege.md`

**Related molds (do not duplicate ownership):**

| Topic | Mold-ID |
|-------|---------|
| CLI command surface / dual mention | **`LM-CLI-INTERFACE`** |
| Default TTY menu | **`LM-CLI-DEFAULT-INTERACTION`** |
| Re-run safety | **`LM-IDEMPOTENCY`** |
| JSON sudoer grant | **`LM-SUDOER-JSON-FILE`** |
| Privilege / fragment dest | **`LM-THREE-LAYER-PRIVILEGE-MODEL`** |
| Operator fatals | **`LM-OPERATOR-READABLE-ERROR`** |
| Interactive / no hang | **`LM-INTERACTIVE-VS-NONINTERACTIVE`** |

---

## 2. Core Rules (Mandatory when this pattern is claimed)

### 2.1 Verb

1. **MUST** route a live operational verb (typical **`add-crontab`**; product **MAY** name another token).  
2. **MUST** be Type 0 (invoking login). **MUST NOT** require `sudo` to read or write this login’s crontab.  
3. **MUST NOT** write `/etc`, root’s crontab, or `/etc/cron.d`.  
4. Dual mention: CLI-interface REQ **and** the topic-owner cron-job REQ.  
5. Help **MUST** list the verb. Menu membership follows **`LM-CLI-DEFAULT-INTERACTION`** (daily work **MAY** include it; install/setup stay off the main list).

### 2.2 Whose crontab

6. Crontab **MUST** be the invoking login’s user crontab (`crontab -l` / `crontab <file>` as this login).  
7. Unix login **MUST** be resolved at runtime with `id -un`.  
8. **MUST NOT** hard-code a particular login as crontab owner or as the sudoers username.  
9. **MUST NOT** install jobs for a different login than the invoking user.

### 2.3 Sudoers gate (when a job uses sudo)

10. Probe **this** login’s installed fragment first: `{{SUDOERS_D_DIR}}/{{APP_NAME}}-<id -un>` (then a documented legacy unsuffixed path if the product has one). Other users’ `{{APP_NAME}}-<other>` files **MUST NOT** count.  
11. When the fragment is **readable**, it **MUST** contain the studied Cmnd, typically:

```text
<id -un> ALL=(root) NOPASSWD: <GLOBAL_BIN>/<APP_NAME> <elev-verb>
```

12. A readable fragment that exists but **lacks** that line **MUST** fail closed. **MUST NOT** fall through to a sibling login’s grant.  
13. When the fragment **exists** but is **unreadable**, **MAY** corroborate with `sudo -n -l` listing that exact binary+verb. **MUST NOT** probe with `sudo true` or by running the elevated product verb.  
14. Missing fragment **MUST** fail closed. Drafts under `~/.config/` **MUST NOT** count as installed grants.

### 2.4 Job lines

15. Each job **MUST** use the **global** managed path `{{GLOBAL_BIN}}/{{APP_NAME}}` when sudoers grants that path.  
16. **MUST** fail closed if that binary is missing or not executable (when jobs require it).  
17. Unprivileged verbs on the crontab **MUST NOT** use `sudo`. Elevated verbs **MUST** use `sudo` plus the exact grant argv.  
18. **MUST** use `crontab` (override `{{CRONTAB_BIN_ENV}}` for tests). Missing crontab command **MUST** fail closed.  
19. **MUST** preserve other crontab lines.  
20. Re-run **MUST** be idempotent: if the command portion already exists, do not add a second line. Success when all claimed jobs are present.  
21. Off-TTY / `--json` **MUST NOT** hang or prompt.

Schedules and verb list are **Implementation Notes** after specialize (studied host pattern). Portable env names:

| Env | Role | Typical default |
|-----|------|-----------------|
| `{{CRONTAB_BIN_ENV}}` | crontab binary | `crontab` |
| `{{CRON_SCHEDULE_*}}` | per-job schedule | studied 5-field crontab |

### 2.5 Errors

Blocking copy **MUST** say what happened and **Next:** (**`LM-OPERATOR-READABLE-ERROR`**). JSON `message` **MUST** match the human sentence.

| Case | Next (portable) |
|------|-----------------|
| No grant / wrong fragment | generate + submit the JSON grant, then ask the approver |
| Global binary missing | global `install` of `{{APP_NAME}}` |
| crontab command missing | install cron, then re-run the ensure verb |
| crontab install failed | check `crontab -l`, then re-run |

### 2.6 Invocation samples (dual mention)

```text
{{APP_NAME}} add-crontab
{{APP_NAME}} add-crontab --json
```

Worked crontab body shape (no Unix login on the lines — crontab is already per-login):

```text
{{SCHEDULE_ELEV}} sudo {{GLOBAL_BIN}}/{{APP_NAME}} {{ELEV_VERB}}
{{SCHEDULE_USER}} {{GLOBAL_BIN}}/{{APP_NAME}} {{USER_VERB}}
```

---

## 3. Specialization sketch (Implementation Notes)

Fill for *this* product:

| Item | Fill |
|------|------|
| Routed-verb | `add-crontab` or named token |
| Handler prefix | `{{PREFIX}}_add_crontab` |
| Elev job | verb + schedule + `sudo {{GLOBAL_BIN}}/{{APP_NAME}} …` |
| User job | verb + schedule + no sudo |
| Fragment dest | `/etc/sudoers.d/{{APP_NAME}}-<id -un>` |
| Studied Cmnd | exact sudoers(5) line |
| Test isolation | `{{CRONTAB_BIN_ENV}}` fake; `SUDOERS_D_DIR` override |
| Menu | row number if claimed on the main list |

---

## 4. Why This Pattern Exists (Direct CIAO Alignment)

- **Principle 2 – Intentional**: Host timers are product-owned lines, not a hidden operator ritual.  
- **Principle 9 – Three Types of Commands**: crontab write is Type 0; scheduled `sudo` uses an approved grant.  
- **Principle 10 – Least privilege**: no extra OS tools in sudoers; no other user’s fragment.  
- **Principle 16 – Interactive**: no hang off-TTY.  
- **Principle 21 – Dual policies**: core uses `id -un` / `{{GLOBAL_BIN}}`; Implementation Notes fill product schedules without freezing a session login.

---

## 5. Design Principles (CIAO / CIAO-Lite)

- **Caution:** Fail closed without **this** login’s matching grant.  
- **Intentional:** Studied lines only; unprivileged jobs stay unprivileged.  
- **Anti-fragile:** Idempotent; preserve other jobs; tests inject crontab.  
- **Over-protect:** Wrong-user and wrong-argv fragments are refusals.

---

## 6. Protection Rule (Sacred)

Future agents **MUST NOT**:

1. Hard-code a Unix login as crontab owner or sudoers username.  
2. Treat another login’s `{{APP_NAME}}-<other>` fragment as this login’s grant.  
3. Write `/etc`, root’s crontab, or `/etc/cron.d` from the ensure verb.  
4. Put `sudo` on an unprivileged job, or omit `sudo` on the granted elevated job.  
5. Use `{{USER_BIN}}/{{APP_NAME}}` in jobs when sudoers grants `{{GLOBAL_BIN}}`.  
6. Probe the grant by running the elevated product verb or `sudo true`.  
7. Duplicate job lines on re-run.  
8. Hang off-TTY / `--json`.  
9. Paste this template path into product source as behavioral authority — specialize and cite the live `requirement-*.md`.  
10. Collapse this pattern into elapsed **external-timer** domain law.

**Violating this rule is a critical crontab / multi-user regression.**

---

## Design-time verification

| TP family | Proof mold | Design-phase note |
|-----------|------------|-------------------|
| **TP-CRON-*** | **`PM-CRON-JOB-TEST-PLAN`** | Grant gate, isolation, idempotency |
| **TP-CLI-*** (help + menu) | **`PM-SHELL-CLI-TEST-PLAN`** | Verb listed; menu row if claimed |

**RTM:** `template-requirement-test-traceability.md`

---

## 7. How to use this template

1. Confirm the product claims a user-crontab ensure.  
2. Specialize via **`SK-CREATE-SPECIFIC-REQUIREMENT`** (git-surface: no template path in the REQ).  
3. Dual-mention the verb on **`LM-CLI-INTERFACE`**.  
4. If the TTY menu is claimed, add the row per **`LM-CLI-DEFAULT-INTERACTION`**.  
5. Map **TP-CRON-*** into product `TP-<SUBJECT>-*` (do not freeze **`RQ-*`** here).

---

**Last Updated**: 2026-09-02  
**Owner**: {{OWNER}}  
**Alignment**: term `cron-job` · **`PM-CRON-JOB-TEST-PLAN`** · **`LM-IDEMPOTENCY`** · **`LM-SUDOER-JSON-FILE`** · **`PO-NON-EXPOSE-LOCAL-MACHINE`** · **`PO-STAY-IN-PROJECT-SSOT`** · [CIAO](https://github.com/cloudgen/ciao) / [CIAO-Lite](https://github.com/cloudgen/ciao-lite)
