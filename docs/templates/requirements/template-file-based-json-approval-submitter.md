---
name: file-based-json-approval-submitter
id: LM-FILE-BASED-JSON-APPROVAL-SUBMITTER
kind: law-mold
description: >
  Portable law mold for a Type 0 product that queues a self-scoped JSON grant
  into a sibling file-based JSON approval inbound. Cite as
  LM-FILE-BASED-JSON-APPROVAL-SUBMITTER. Not the approval dest.
---

**file**: template-file-based-json-approval-submitter.md  
**Mold-ID**: LM-FILE-BASED-JSON-APPROVAL-SUBMITTER  
**Status**: Active (Version 1.4.0)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered / Over-protect)

**Folder structure (policy):** [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

# =============================================================================
# CIAO DEFENSIVE TEMPLATE - File-based JSON approval submitter
# =============================================================================
#
# Portable law mold for the Type 0 *submitter* role.
# Specialize into: requirement-sudoer-json-file.md (sudoers-grant leaf)
#   plus generate/submit rows on requirement-three-layer-privilege-model.md
#   and requirement-shell-cli-interface.md.
# Do NOT specialize this into the product's requirement-domain-* unless
# that domain *is* the sibling approval dest.
# =============================================================================

## 1. Purpose

This mold is the portable **law** for a **file-based JSON approval submitter**: a Type 0 product (`{{SUBMITTER_APP}}`) that **detects** a sibling approval CLI (`{{APPROVAL_APP}}`) and its inbound folder, then **queues** a self-scoped JSON file. It does **not** create that inbound, **does not** approve, and **does not** write the live dest.

**Sudoers-grant leaf:** `sudoer-approval-submitter` — subject is a **sudoer-json-file**. Typical verbs: `{{GENERATE_SUDOER_CMD}}` / `{{SUBMIT_SUDOER_CMD}}`.

**Does not own:**

| Concern | Owner |
|---------|--------|
| The approval **machine** (folders + verify + move) | **`LM-FILE-BASED-JSON-APPROVAL`** on the **dest** product |
| JSON **body** / command identity | **`LM-SUDOER-JSON-FILE`** (sudoers-grant leaf) |
| Independence + readability of generate dest | **`LM-THREE-LAYER-PRIVILEGE-MODEL`** §2.3.2a |
| Type map / Table A text fragment | **`LM-THREE-LAYER-PRIVILEGE-MODEL`** |
| This product’s domain catalog (DNS, backup, …) | specialized `requirement-domain-*` |

**Do not use this template for:** becoming a sudoers-manager; writing `/etc/sudoers.d`; inventing a second inbound for the same subject; treating generate/submit as trimmed `print-sudoers-install-script` extras.

## 2. Terminologies

| Term | Path | SSOT type | Role |
|------|------|-----------|------|
| **File-based JSON approval submitter** | `docs/terminologies/file-based-json-approval-submitter.md` | `product-law` | **Primary class** |
| **Sudoer approval submitter** | `docs/terminologies/sudoer-approval-submitter.md` | `product-law` | Sudoers-grant **leaf** |
| **File-based JSON approval** | `docs/terminologies/file-based-json-approval.md` | `product-law` | Sibling **machine** |
| **File-based approval submission folder** | `docs/terminologies/file-based-approval-submission-folder.md` | `runtime-mode` | Inbound **role** |
| **Public submission folder** | `docs/terminologies/public-submission-folder.md` | `runtime-mode` | How to **find** inbound |
| **Independent sudoer generate** | `docs/terminologies/independent-sudoer-generate.md` | `product-law` | Readable generate dest |
| **Sudoer JSON file** | `docs/terminologies/sudoer-json-file.md` | `product-law` | Queued **body** |
| **Sudoer request kind** | `docs/terminologies/sudoer-request-kind.md` | `product-law` | Discriminator |
| **Type-2-switch sudoer request** | `docs/terminologies/type-2-switch-sudoer-request.md` | `product-law` | Type 0 submit payload |
| **Automatic login-hook sudoer submit** | `docs/terminologies/automatic-login-hook-sudoer-submit.md` | `product-law` | Type 1 setup path — **not** this Type 0 verb |
| **Self-scope request** | `docs/terminologies/self-scope-request.md` | `product-law` | Invoker = subject |
| **Least-privilege-approver** | `docs/terminologies/least-privilege-approver.md` | `identity-runtime` | Sibling dest’s mover |
| **Three-layer privilege** | `docs/terminologies/three-layer-privilege.md` | `product-law` | Submit = Type 0 |
| **Project templates** | `docs/terminologies/project-templates.md` | `meta-catalog` | Law-mold surface |
| **Docs folder structure** | `docs/terminologies/docs-folder-structure.md` | `policy` | This file’s tree |
| **No-hardcode policy** | `docs/terminologies/no-hardcode-policy.md` | `policy` | Placeholders only |
| **Dual policies** | `docs/terminologies/dual-policies.md` | `policy` | No-placeholder × no-hardcode |
| **Terminology policy for templates** | `docs/terminologies/terminology-policy-for-templates.md` | `policy` | This section |
| **SSOT-terminology policy for templates** | `docs/terminologies/ssot-terminology-policy-for-templates.md` | `policy` | SSOT type column |

**SSOT types used:** `product-law` · `runtime-mode` · `identity-runtime` · `meta-catalog` · `policy`

**Missing terms:** none

**Policies:** `docs/policies/policy-no-hardcode.md` · `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-least-privilege.md`

## 3. Core rules (portable)

### 3.1 Role

| Role | Who | Type | May | Must not |
|------|-----|------|-----|----------|
| **This product** | `{{SUBMITTER_APP}}` | **0** | Detect dest + inbound; generate a local JSON; call dest allocate/submit of **`type-2-switch`** | `mkdir` inbound; `chown` inbound; approve; write `/etc/sudoers.d` / `/etc/passwd`; invent dest basename; queue `login-hook-elev` |
| **Approval dest** | `{{APPROVAL_APP}}` | dest product | Allocate name; own inbound; approve | Be this product |
| **Approver** | `{{APPROVER}}` on the dest | **1** | Move inbound → accepted/declined | File on behalf of a human via this product |

### 3.2 Detect, do not create

| Probe (order) | Fail closed when |
|---------------|------------------|
| `{{APPROVAL_CLI}}` env, then `{{GLOBAL_BIN}}/{{APPROVAL_APP}}`, then `{{USER_BIN}}/{{APPROVAL_APP}}`, then `PATH` | No executable dest CLI |
| `id {{APPROVER}}` (or `{{SUDOER_ADM_USER}}`) | No approver account — next: `sudo {{APPROVAL_APP}} setup` |
| Env inbound override, then `/var/{{APPROVAL_APP}}/{{INBOUND_BASENAME}}`, then F4 view | Missing or not writable — **MUST NOT** `mkdir` |

### 3.3 Generate then submit

1. **Independent generate** (`{{GENERATE_SUDOER_CMD}}`) **MUST** exist when this product emits a sudoer JSON. Dest readable without sudo. **`LM-THREE-LAYER-PRIVILEGE-MODEL`** §2.3.2a.  
2. **Submit** (`{{SUBMIT_SUDOER_CMD}}`) prefers that file. No file → compact **`type-2-switch`** body. Type 0 **MUST** refuse `kind=login-hook-elev` (that grant is Type 1 `setup` — **`LM-THREE-LAYER-PRIVILEGE-MODEL`** §2.3.3e). Type 0 submit is **no sudo**. Type 1 `setup` is **password `sudo` / already root**. Dest Type 0 self-scope **MUST NOT** apply to `setup`.  
3. Body **MUST** satisfy the subject mold (**`LM-SUDOER-JSON-FILE`** for the sudoers-grant leaf), including `kind` when that mold §3.0 applies.  
4. Self-scope: JSON identity = `id -un` (`type-2-switch` only).  
5. Default action: **update** if this user’s sibling dest `/etc/sudoers.d/{{APP_NAME}}-{{TARGET_USER}}` exists; else **add**. `--add` / `--update` override. The hook dest `/etc/sudoers.d/{{APP_NAME}}-{{LPU_USER}}` **MUST NOT** count as that probe.  
6. Call `{{APPROVAL_APP}}` `add-{{SUBJECT}}-request` / `update-{{SUBJECT}}-request` (allocator).  
7. When inbound `${request_id}` is readable, fail closed if required body fields are missing.

### 3.4 Implementation Notes (fill when specializing)

| Item | Placeholder |
|------|-------------|
| **`{{SUBMITTER_APP}}`** | this product |
| **`{{APPROVAL_APP}}`** | sibling dest (conventional `sudoer-cli`) |
| **`{{APPROVER}}`** | dest LPU (conventional `sudoer-adm`) |
| **`{{INBOUND_BASENAME}}`** | conventional `sudoer-request` |
| **Generate / submit verbs** | `{{GENERATE_SUDOER_CMD}}` / `{{SUBMIT_SUDOER_CMD}}` |
| **JSON body peer** | specialized `requirement-sudoer-json-file` |
| **Workflow peer** | specialized `requirement-three-layer-privilege-model` |

## 4. How to specialize

1. Create `docs/requirements/requirement-sudoer-json-file.md` (body).  
2. Add generate/submit rows on `requirement-three-layer-privilege-model` and `requirement-shell-cli-interface`.  
3. Register the JSON REQ. Point class residual at it.  
4. **Do not** add a second Active `requirement-domain-*`.  
5. **Do not** list generate/submit as unknown trimmed extras.  
6. Seed **`TP-SUDOER-JSON-*`** / product `TP-PRIV-*` for generate dest + submit fail-closed + inbound fidelity.

## 5. Protection Rule (Sacred)

Future agents **MUST NOT**:

1. `mkdir` production inbound from this product.  
2. Write `/etc/sudoers.d` or `/etc/passwd` from generate/submit.  
3. Hide generate only inside submit.  
4. Treat this product as `{{APPROVER}}` or as the approval dest.  
5. Fold sibling sudoer inbound into this product’s DNS/nginx/backup domain SSOT.  
6. Classify generate/submit as `print-sudoers-install-script` extras.  
7. Hardcode one sibling pair as universal law in this mold.  
8. Cite this mold as product-source authority after specialize.  
9. Embed **`RQ-*`** as portable vocabulary.  
10. Let Type 0 `{{SUBMIT_SUDOER_CMD}}` queue `login-hook-elev`.  
11. Apply dest Type 0 self-scope to Type 1 `setup`, or confuse who may submit (Type 0, no sudo) with who may setup (Type 1, password `sudo`).  
12. Treat Type 0 submit dest as `/etc/sudoers.d/{{APP_NAME}}-{{LPU_USER}}`. That dest is `login-hook-elev` after setup approve.  
13. `chown` dest inbound JSON. Dest `{{APPROVER}}` takes ownership, then moves.

**Violating this rule is a critical dest-collapse / privilege regression.**

## 6. Related artifacts (harness)

| Artifact | Relationship |
|----------|--------------|
| **`LM-FILE-BASED-JSON-APPROVAL`** | Machine on the **dest** |
| **`LM-SUDOER-JSON-FILE`** | Queued **body** |
| **`LM-THREE-LAYER-PRIVILEGE-MODEL`** | Generate/submit workflow |
| Term `sudoer-approval-submitter` | Sudoers-grant leaf |

## Design-time verification

| TP family (portable) | Intent |
|----------------------|--------|
| **TP-SUDOER-JSON-01** | Generate dest is `{{PRJ_NAME}}` only |
| **TP-SUDOER-JSON-08** | Independent generate dest readable without sudo |
| **TP-PRIV-SUBMIT-01** | Submit fails closed when dest CLI missing |
| **TP-PRIV-SUBMIT-02** | Submit via stub does not write `/etc/sudoers.d` |
| **TP-PRIV-SUBMIT-03** | Generate refuses `/etc` and inbound dests |
| **TP-SUDOER-JSON-12** | Type 0 submit of `login-hook-elev` fails closed |
| **TP-SUDOER-JSON-16** | Dest Type 0 `self_scope` does not block Type 1 setup inbound write |
| **TP-SUDOER-JSON-18** | Setup / Type 0 submit does not `chown` dest inbound |

**Last Updated**: 2026-08-18 (1.4.0 submitter/setup MUST NOT `chown` dest inbound)  
**Owner**: {{OWNER}}  
**Alignment**: term `file-based-json-approval-submitter` · `sudoer-approval-submitter` · **`LM-SUDOER-JSON-FILE`** · **`LM-THREE-LAYER-PRIVILEGE-MODEL`** · [CIAO](https://github.com/cloudgen/ciao) / [CIAO-Lite](https://github.com/cloudgen/ciao-lite)
