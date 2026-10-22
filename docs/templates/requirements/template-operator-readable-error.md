---
name: operator-readable-error
id: LM-OPERATOR-READABLE-ERROR
kind: law-mold
description: >
  Portable law mold: every operator-facing error is understandable like a
  human-intro page (what happened, what it means, what to do next).
  Cite as LM-OPERATOR-READABLE-ERROR. Does not own out_* channels
  (LM-OUTPUT-REQUIREMENTS) or fail-fast policy (LM-ERROR-HANDLING).
---

**file**: template-operator-readable-error.md  
**Mold-ID**: LM-OPERATOR-READABLE-ERROR  
**Status**: Active (Version 1.1.0)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered / Over-protect)

**Folder structure (policy):** [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

# =============================================================================
# Portable law mold — operator-readable error (human-intro style)
# Specialize into: docs/requirements/requirement-operator-readable-error.md
# (or a § on the output-requirements peer). Product source cites the REQ, not this file.
# =============================================================================

## 1. Purpose

This mold is the portable **wording** law for **operator-facing errors** on software-development CLIs.

Every blocking `[ERROR]` (or product equivalent) **MUST** be understandable the way a `docs/human-intro/` page is: **one concrete sentence first**, then meaning, then a **next step**. Fail-closed stays. Jargon-only breadcrumbs are forbidden.

**Does not own** (point, do not copy):

| Concern | Owner |
|---------|--------|
| Which function prints (`out_die`) and stdout/stderr | **`LM-OUTPUT-REQUIREMENTS`** |
| Fail-fast vs graceful degrade | **`LM-ERROR-HANDLING`** |
| Interactive vs non-interactive hang | **`LM-INTERACTIVE-VS-NONINTERACTIVE`** |

**Specialize into:** `docs/requirements/requirement-operator-readable-error.md` (or a dedicated § on the specialized output REQ). **No `RQ-*` in this mold.**

## 2. Terminologies

Related glossary entries (disk-truth). Templates **point**; they do not redefine terms.

| Term | Path | SSOT type | Role |
|------|------|-----------|------|
| **Operator-readable error** | `docs/terminologies/operator-readable-error.md` | `product-law` | This mold’s primary word |
| **Error-handling** | `docs/terminologies/error-handling.md` | `product-law` | Detect / exit policy (peer) |
| **SSOT of output** | `docs/terminologies/single-source-of-truth-of-output.md` | `channel-io` | Printer family |
| **SSOT of stderr** | `docs/terminologies/single-source-of-truth-of-stderr.md` | `channel-io` | Error channel |
| **Project log content type** | `docs/terminologies/project-log-content-type.md` | `mention-only` | The **error** kind is one row of that catalog. Cite only. |
| **Stay-honest** | `docs/terminologies/stay-honest.md` | `policy` | No false completeness |
| **Docs folder structure** | `docs/terminologies/docs-folder-structure.md` | `policy` | Where this mold lives |
| **No-hardcode policy** | `docs/terminologies/no-hardcode-policy.md` | `policy` | Placeholders only |
| **Project templates** | `docs/terminologies/project-templates.md` | `meta-catalog` | Law-mold surface |
| **SSOT catalog** | `docs/terminologies/ssot-catalog.md` | `meta-catalog` | Inventory |

**SSOT types used:** `product-law` · `channel-io` · `policy` · `meta-catalog`

**Missing terms:** none

**Policies:** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-no-hardcode.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md`

## 3. Core rules (portable)

### 3.1 Sacred shape (human-intro style)

Every **fatal** or **blocking** operator message **MUST** contain these slots (order recommended):

| Slot | Required | Meaning |
|------|----------|---------|
| **What happened** | yes | One concrete sentence a person who just ran the command can parse |
| **What it means** | SHOULD | Plain restatement if the first sentence uses a product noun |
| **What to do next** | yes | A command, a path, or who to ask. TTY **menu** invalid-choice errors **MUST** keep the operator on **this** list (“choose a listed number or command name”) — **MUST NOT** send them only to `{{APP_NAME}} help` as if the session ended |
| **Do not** | when dangerous | Only if a wrong next step exists (e.g. do not approve a file) |

This is the same concreteness as `docs/human-intro/FORMAT.md` sections 1 / 5 / 7 — applied to **live CLI copy**, not a second teaching page per error.

### 3.2 Channel and mode (do not fork)

1. Print through the product output SSOT (`out_error` / `out_die` or language equivalent).  
2. Quiet **MUST** still show the error.  
3. JSON mode: `message` **MUST** be the same operator sentence. Optional `next` field **MAY** hold the next command.  
4. **MUST NOT** invent a second printer for “nicer” wording.

### 3.3 Forbidden as the whole message

**MUST NOT** ship a blocking error whose only content is:

| Token class | Why |
|-------------|-----|
| Internal incident IDs | Agents can cite incidents in docs; operators need a sentence |
| Codec / splitter jargon (`re-encode`, `},{`, `sibling`) | Not operator vocabulary |
| Unexplained queue slang (`inbound grant`, `backup verb`) | Define or replace |
| Guess marks as the only cause (`(sibling re-encode?)`) | State the fact, then the next step |

A parenthetical **MAY** follow **after** the operator sentence.

### 3.4 Fail-closed honesty

1. **MUST NOT** remove a fail-closed check to make the message “friendlier.”  
2. **MUST NOT** claim success when the command wrote a bad artifact.  
3. If a file was already created, the error **MUST** say so and name it when the name is known.

### 3.5 Software-development class

Every **software-development** specialized CLI that emits operator errors **MUST** specialize this mold (own REQ or a § on the output peer). Domain-only REQs **MUST NOT** invent a second wording SSOT.

## 4. Implementation Notes (fill when specializing)

| Item | Placeholder |
|------|-------------|
| **Product** | `{{APP_NAME}}` |
| **Printer** | `out_die` / language equivalent |
| **Worked fatal examples** | 2–3 real `out_die` lines that satisfy §3.1 |
| **Banned jargon (this product)** | list tokens this CLI must not use as the whole message |
| **JSON fields** | `message` (+ optional `next`) |

## 5. CIAO alignment

- **Caution:** Fail loud; still tell the person what to do.  
- **Intentional:** One wording SSOT; channels stay on the output peer.  
- **Anti-fragile:** JSON `message` equals human text.  
- **Over-protect:** Do not drop fail-closed to sound nicer.  
- **P5 / P14:** Still one output module; errors on stderr.  
- **Stay-honest:** Purpose / `[OK]` ≠ completeness.

## 6. Protection Rule (Sacred)

Future agents **MUST NOT**:

1. Ship a blocking error that only insiders can parse.  
2. Use incident IDs or codec jargon as the **only** operator text.  
3. Remove fail-closed checks to “improve UX.”  
4. Duplicate channel/`out_*` law here (**`LM-OUTPUT-REQUIREMENTS`**).  
5. Duplicate fail-fast vs degrade law here (**`LM-ERROR-HANDLING`**).  
6. Give JSON a different story than the human `[ERROR]` line.  
7. Embed **`RQ-*`** as portable vocabulary.  
8. Cite this mold as product-source authority after specialize.

**Violating this rule is an honesty / operator-UX regression.**

## 7. How to specialize

1. Create `docs/requirements/requirement-operator-readable-error.md` via **`SK-CREATE-SPECIFIC-REQUIREMENT`**, **or** add a § on the specialized output REQ and point here.  
2. Fill Implementation Notes (worked `out_die` lines).  
3. Register `docs/requirements/index.md`.  
4. Seed proof from **`PM-OPERATOR-READABLE-ERROR-TEST-PLAN`**.  
5. Audit with **`CL-OPERATOR-READABLE-ERROR`**.  
6. Product source cites the **requirement**, not this template.

## Design-time verification

| TP family (portable) | Intent |
|----------------------|--------|
| **TP-ORE-01** | Fatal error names what happened in operator words |
| **TP-ORE-02** | Fatal error names a next command or who to ask |
| **TP-ORE-03** | That error does not consist only of banned jargon |

Gates: **`CL-OPERATOR-READABLE-ERROR`**. Procedure: **`SK-OPERATOR-READABLE-ERROR`**.

**Last Updated**: 2026-10-04 (v1.1.0 — cite project log content type; TTY menu retry Next stays on this list)  
**Owner**: {{OWNER}}  
**Alignment**: **`LM-OUTPUT-REQUIREMENTS`** · **`LM-ERROR-HANDLING`** · **`SK-OPERATOR-READABLE-ERROR`** · **`PM-OPERATOR-READABLE-ERROR-TEST-PLAN`** · CIAO / CIAO-Lite
