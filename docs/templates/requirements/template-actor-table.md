---
name: actor-table
id: LM-ACTOR-TABLE
kind: law-mold
description: >
  Portable law mold for a product actor table (who may submit vs approve)
  and the login-time interactive review hook. Cite as LM-ACTOR-TABLE.
  No product brand. Specialize into product law; do not replace the
  file-based JSON approval machine mold.
---

**file**: template-actor-table.md  
**Mold-ID**: LM-ACTOR-TABLE  
**Status**: Active (Version 1.2.0)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered / Over-protect)

# =============================================================================
# CIAO DEFENSIVE TEMPLATE - Actor table + login review hook
# =============================================================================
#
# Portable. Specialize into product law (domain SSOT or a dedicated
# requirement-{{STEM}}-actor-table.md that the domain SSOT consumes).
# Use {{PLACEHOLDER}} only.
# =============================================================================

## 1. Purpose

This mold is the portable **dest actor table**: which identities may **submit** a request, which identities may **approve** or reject it, and how an approver is prompted after **TTY login** (interactive hook). The class **consider** catalog (Approver **MAY** be **None**) is **`LM-ACTOR-ROLE-SUBJECT-APPROVER`**. This mold assumes dest review exists.

It does **not** own JSON schema, dest grammar, or vault layout. The approval **machine** (folder = state, JSON = proposal) is **LM-FILE-BASED-JSON-APPROVAL**. This mold owns **who** and the **login procedure**.

**Do not use this mold for:** Type 0/1/2 elev tables (three-layer); LPU F1–F7 (least-privilege-user); request JSON schema.

## 2. Core rules (MUST)

### 2.1 Actor table (portable)

The specialized REQ **MUST** publish this table with **product names** filled (no empty roles):

| Role | Who | Type | May | Must not |
|------|-----|------|-----|----------|
| **Submitter** | Ordinary login `{{SUBJECT}}` (not `{{APPROVER}}`) | **0** | Submit a self-scoped JSON request into inbound | Submit for another identity; approve/reject; write the live dest; choose the dest basename; hold the API token |
| **Subject** | Same person as the submitter | — | Appear in the allocated basename and JSON identity fields | Be another login the submitter does not own |
| **Approver** | Least-privilege-approver `{{APPROVER}}` | **1** (after a narrow elev, or euid 0) | Re-check JSON + name; **move** inbound → accepted/declined; on accept, apply dest | File a request on behalf of a human; Type 2 dest-write as `{{APPROVER}}`; be the Type 2 vault operator `{{TYPE2_OPERATOR}}` |
| **Allocator** | Product CLI Type 0 path | **0** | Allocate the request basename | Trust a caller-supplied dest basename |
| **Root session** | euid 0 | **1** | Same Type 1 verbs as approver | Submit a body whose subject is someone else |

**ACT-M1.** Submitter and approver **MUST** be distinct roles. **MUST NOT** collapse them into one account.

**ACT-M2.** The Type 2 vault/DNS operator (`{{TYPE2_OPERATOR}}`) **MUST NOT** be the approver unless the product **explicitly** redesigns both LPU laws.

**ACT-M3.** Empty argv **MUST NOT** submit or approve.

### 2.2 Account map

| Role | Account |
|------|---------|
| Submitter / subject | Ordinary login `{{SUBJECT}}` |
| Approver | `{{APPROVER}}` (LPA leaf; host create may be Gap) |
| Type 2 operator | `{{TYPE2_OPERATOR}}` (not an approver) |
| Root session | euid 0 |

### 2.3 Submit-when / not-a-submit

Type 0 submit is allowed only when **all** hold: invoker is a login user; self-scope (subject = `id -un`); inbound exists (Type 0 **MUST NOT** `mkdir` it); body matches the product request schema; allocator owns the basename.

**Not a submit:** on-behalf-of; wanting dest written immediately; running approve as a normal user; read-only verbs (`status` / `show` / `ip`); vault store (`vault account add`).

### 2.4 Approval procedure (interactive hook after login)

When the product claims login-time review: **compose `LM-LOGIN-INTERACTIVE-REVIEW-HOOK`** (specialize into an independent REQ). This mold **MUST NOT** fork snippet text, labeled `{{GLOBAL_BIN}}/{{APP_NAME}}-hook`, or old-hook review.

1. Approver logs in on a **TTY** as `{{APPROVER}}`.  
2. Rc hook runs **once** per session via `sudo -n {{GLOBAL_BIN}}/{{APP_NAME}}-hook {{REVIEW_VERB}}`.  
3. Dest `{{REVIEW_VERB}}` **MUST** review `{{APPROVER}}` rc: old `{{GLOBAL_BIN}}/{{APP_NAME}} {{REVIEW_VERB}}` **MUST** become `{{APP_NAME}}-hook`; already-new **MUST NOT** rewrite (**`LM-LOGIN-INTERACTIVE-REVIEW-HOOK`** §3.9).  
4. Dest loop (fence first, one-off yes/no) stays on **`LM-FILE-BASED-JSON-APPROVAL`** §2.8. **MUST NOT** skip / quit / maybe.  
5. Empty argv of `{{APP_NAME}}` stays **help**.

`{{REVIEW_VERB}}` consumes product `TTY`. Non-TTY / `--json` → fail closed. `--force` **MUST NOT** auto-accept.

### 2.4.1 Rc heal (when interactive and invoker is the approver)

**Compose `LM-LOGIN-INTERACTIVE-REVIEW-HOOK`** §3.6 / §3.9. This mold **MUST NOT** re-own `.bashrc` / `.profile` plant, labeled symlink create, or old product-binary rewrite.

### 2.5 Implementation Notes (fill on specialize)

| Item | Placeholder |
|------|-------------|
| Product | `{{APP_NAME}}` |
| Submitter example | `{{SUBJECT}}` |
| Approver | `{{APPROVER}}` |
| Type 2 operator | `{{TYPE2_OPERATOR}}` |
| Review verb | `{{REVIEW_VERB}}` |
| Hook variable | `{{HOOK_RAN_VAR}}` |
| Ship-unit status | Implemented / **Gap** |

## 3. Protection Rule (Sacred)

**MUST NOT**: collapse submitter and approver; make `{{TYPE2_OPERATOR}}` the approver without redesign; hijack empty argv as review; hang scp/CI; paste tokens into the actor table or hook snippet; fork snippet / `{{APP_NAME}}-hook` / old-hook review from **`LM-LOGIN-INTERACTIVE-REVIEW-HOOK`**; offer skip / quit / maybe on dest review.

**Last Updated**: 2026-09-08
**Version history:**
- **1.2.0** (2026-09-08): Hook path is `{{APP_NAME}}-hook`; dest `{{REVIEW_VERB}}` old-hook review **points** at **`LM-LOGIN-INTERACTIVE-REVIEW-HOOK`** §3.9; dest question is one-off yes/no.
