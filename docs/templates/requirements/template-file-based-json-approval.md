---
name: file-based-json-approval
id: LM-FILE-BASED-JSON-APPROVAL
kind: law-mold
description: >
  Portable law mold for a file-based JSON approval machine (folder = state,
  JSON = checkable proposal). Cite as LM-FILE-BASED-JSON-APPROVAL (path secondary).
  No product brand. Specialize into one Active requirement-domain-*.
---

**file**: template-file-based-json-approval.md  
**Mold-ID**: LM-FILE-BASED-JSON-APPROVAL  
**Status**: Active (Version 1.18.0)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered / Over-protect)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

# =============================================================================
# CIAO DEFENSIVE TEMPLATE - File-based JSON approval
# =============================================================================
#
# Portable law mold. Specialize into exactly one Active:
#   docs/requirements/requirement-domain-{{DOMAIN_SUBJECT}}.md
# Use {{PLACEHOLDER}} only — no product host hardcodes in this mold.
# Do not add a second generic product requirement next to the domain SSOT
# unless the product hosts two instances of this machine.
# =============================================================================

# Template: File-based JSON approval

## 1. Purpose

This template is the portable **law mold** for a **file-based JSON approval** machine — a **subclass** of **`LM-APPROVAL-SYSTEM`** (fence first, human-facing match display, then questions). Named dest leaves: **`LM-SUDOER-APPROVAL-SYSTEM`** · **`LM-NGINX-CONF-APPROVAL-SYSTEM`** · **`LM-CLOUDFLARE-DNS-APPROVAL-SYSTEM`**:

- **Folder = state** (inbound / accepted / declined). Moves change state. There is no ticket table.  
- **JSON = the checkable proposal** (closed schema on disk). CLI `--json` status is **not** the request file.  
- A **normal user** (Type 0) **submits** a self-scoped JSON file into **inbound**.  
- A **least-privilege-approver** (`{{APPROVER}}`) **re-checks** that JSON and **moves** the file to accepted or declined.  
- Every `{{APPROVER}}` leaf **MUST** name **at least one** approval subject (`{{APPROVAL_SUBJECT}}` — the content family it may authorize).  
- Dest writes (if any) are **Type 1 as root** after a narrow elev — the approver is **not** a Type 2 execution context.

**Specialize into:** exactly one Active `requirement-domain-{{DOMAIN_SUBJECT}}.md` (registered domain SSOT). That file **MUST present** this machine in **product language** (named section: one sentence, role table, submit-when, verify table) **plus** the four domain pillars. **Do not** freeze one product’s inbound names, dest paths, or syntax checker as universal law in this mold.

**Audience:** the next product that wants the same machine with a different payload and dest (grants, allowlists, certs, …).

**Do not use this template for:**

| Concern | Owner instead |
|---------|----------------|
| Directory class only (no JSON / no roles) | approval-queue term + instance dir names |
| Type 0/1/2 map, elev Tables A/B/C | **`LM-THREE-LAYER-PRIVILEGE-MODEL`** |
| Approver account F1–F7 | **`LM-LEAST-PRIVILEGE-USER`** |
| Scratch leaves (`mktemp`) | **`LM-TEMP-FILE-SYSTEM`** |
| Storage root resolve | **`LM-SHELL-CLI-STORAGE`** |
| Dispatcher / help catalog | **`LM-CLI-INTERFACE`** |
| Ticket DB / mail / CI queue / whitelist grant / REQ Status `approved` | other approval mechanisms |

### 1.1 Mandatory peers (fail closed)

Specializing this mold **without** these Active registered peers is **incomplete** when the product claims the full machine:

| Peer | Specialize from | Owns |
|------|-----------------|------|
| **Domain SSOT** | **this mold** → `requirement-domain-{{DOMAIN_SUBJECT}}.md` | Named machine + four pillars + instance fills |
| **Three-layer privilege** | **`LM-THREE-LAYER-PRIVILEGE-MODEL`** | Type 0 submit / Type 1 approve; dest writes after euid 0 |
| **Least-privilege user** | **`LM-LEAST-PRIVILEGE-USER`** | `{{APPROVER}}` identity (F1–F7) |
| **CLI interface** | **`LM-CLI-INTERFACE`** | Dispatch; help lists only routed verbs |
| **Output** | **`LM-OUTPUT-REQUIREMENTS`** | `out_*`; `--json` status ≠ request file |
| **Temp leaves** (when convert / syntax-gate uses scratch) | **`LM-TEMP-FILE-SYSTEM`** | `mktemp`; no `$$` names |
| **Storage root** (when queues or scratch share a resolver) | **`LM-SHELL-CLI-STORAGE`** | Isolated root; Type 0 **MUST NOT** `mkdir` production inbound |

**Anti-duplication:** this mold owns the **machine** (roles, submit-when, verify class, allocator-owned basename class, dest **transform class**). Three-layer owns privilege types. LPU owns the approver account. Domain instance fills schema keys, dest grammar, and verb names.

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
| **File-based JSON approval** | `docs/terminologies/file-based-json-approval.md` | `product-law` | **Primary class** this mold encodes |
| **Approval-queue** | `docs/terminologies/approval-queue.md` | `runtime-mode` | Directory class (inbound / accepted / declined) |
| **File-based approval submission folder** | `docs/terminologies/file-based-approval-submission-folder.md` | `runtime-mode` | Inbound **folder role** (`{{QUEUE_ROOT}}/{{INBOUND_BASENAME}}`) — no product / LPU login |
| **File-based JSON approval submitter** | `docs/terminologies/file-based-json-approval-submitter.md` | `product-law` | Sibling Type 0 **product** that calls this machine — `{{SUBMITTER_APP}}` |
| **Public submission folder** | `docs/terminologies/public-submission-folder.md` | `runtime-mode` | Recommended **hosting** of that inbound |
| **Request-filename-grammar** | `docs/terminologies/request-filename-grammar.md` | `product-law` | Allocated basename class |
| **Request-sequence-number** | `docs/terminologies/request-sequence-number.md` | `product-law` | `n` over that instance’s three dirs |
| **Self-scope-request** | `docs/terminologies/self-scope-request.md` | `product-law` | Submitter = JSON username field (submit only) |
| **JSON username field** | `docs/terminologies/json-username-field.md` | `product-law` | Body subject key (`username` / `subject`) |
| **File-ownership** | `docs/terminologies/file-ownership.md` | `runtime-mode` | Unix owner; dest takes, does not fence |
| **Approval fencing condition** | `docs/terminologies/approval-fencing-condition.md` | `product-law` | Closed dest fail-closed list |
| **Incorrect JSON format** | `docs/terminologies/incorrect-json-format.md` | `product-law` | The dest inbound fence |
| **Submit by** | `docs/terminologies/submit-by.md` | `product-law` | Dest-written original Unix owner after format |
| **Submit app** | `docs/terminologies/submit-app.md` | `product-law` | Type 0 CLI identity stamp (`APP_NAME`) |
| **Submit version** | `docs/terminologies/submit-version.md` | `product-law` | Type 0 CLI version stamp (`VERSION`) |
| **Least-privilege-approver** | `docs/terminologies/least-privilege-approver.md` | `identity-runtime` | Who may move / authorize |
| **Least-privilege user** | `docs/terminologies/least-privilege-user.md` | `identity-runtime` | Approver account class |
| **Three-layer privilege** | `docs/terminologies/three-layer-privilege.md` | `product-law` | Type 0 submit / Type 1 approve |
| **Installed-artifact-basename-transform** | `docs/terminologies/installed-artifact-basename-transform.md` | `product-law` | Request name → dest basename |
| **Atomic-data-file** | `docs/terminologies/atomic-data-file.md` | `runtime-mode` | Structured-record class (not the workflow) |
| **Domain requirements** | `docs/terminologies/domain-requirements.md` | `product-law` | Specialize-out: one Active domain SSOT |
| **Least privilege** | `docs/terminologies/least-privilege.md` | `policy` | Principle; harness enforcement |
| **LLM escape** | `docs/terminologies/llm-escape.md` | `policy` | Broad admin / on-behalf-of as escape |

**SSOT types used:** `meta-catalog` · `policy` · `product-law` · `runtime-mode` · `identity-runtime`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md` · `docs/policies/policy-least-privilege.md`

**Checklists:** **`CL-FILE-BASED-JSON-APPROVAL`** · **`CL-LEAST-PRIVILEGE`** · **`CL-LLM-ESCAPE`** · **`CL-HOST-MUTATING-DOMAIN`** (when dest writes exist)  
**Skills (procedure, not product law):** **`SK-CREATE-SPECIFIC-REQUIREMENT`** · **`SK-REQUIREMENT-SUFFICIENT-CHECK`** (Step 3e)

**Missing terms:** none

**Primary owner after specialize:** the product’s Active `requirement-domain-{{DOMAIN_SUBJECT}}.md`. Live inbound paths, schema keys, dest grammar, and verb names **MUST NOT** stay only in this mold.

---

## 2. Core rules (MUST)

### 2.0 Named machine (specialize into the domain REQ)

The specialized domain REQ **MUST** present this design in **product language** (no glossary-path dump):

1. One sentence: folder = state; JSON = the checkable proposal.  
2. Role table (product names).  
3. When a Type 0 submit is allowed **and** not-a-submit cases.  
4. Verify table at submit **and again at approve**.

Mechanics (filename grammar, sample bodies, dest transform) stay under Specialized features. Coverage review (**SK-REQUIREMENT-SUFFICIENT-CHECK** Step 3e) **Fails** when verbs/schema exist but this named section is missing.

### 2.1 Role table (portable)

| Role | Who | Type | May | Must not |
|------|-----|------|-----|----------|
| **Submitter** | **Normal user** — ordinary login (`id -un`), not `{{APPROVER}}` | **0** | Submit a self-scoped JSON request into **inbound**; convert if the product has a text dual | Submit **for** another identity; approve/reject; write the live dest; choose the dest basename |
| **Subject** | Same person as the submitter | — | Appear in the allocated basename and in JSON identity fields | Be another login the submitter does not own |
| **Approver** | A least-privilege-approver (`{{APPROVER}}`) | **1** (after a narrow elev, or euid 0) | Re-check JSON + name; **move** inbound → accepted/declined; on accept, install or delete `{{DEST}}` | File a request **on behalf of** a human; unrestricted admin; Type 2 “run as `{{APPROVER}}`” for dest writes |
| **Allocator** | The product CLI Type 0 path | **0** | Allocate the request basename; write JSON into inbound | Trust a caller-supplied dest basename; skip self-scope |
| **Root session** | euid 0 | **1** (no elev needed) | Same Type 1 verbs as approver | Submit a body whose subject is someone else (self-scope: root files **as root** only) |

Dest writes are **Type 1 as root**. The approver LPU is **not** a Type 2 execution context.

#### Account map (placeholders)

| Role | Account |
|------|---------|
| Submitter / subject | Ordinary login `{{SUBJECT}}` |
| Approver | `{{APPROVER}}` (an LPU leaf) |
| Root session | euid 0 |

### 2.2 When a normal user may submit

Type 0 submit is allowed **only when all** hold:

1. Invoker is a login user (not required to be `{{APPROVER}}`).  
2. **Self-scope:** the [JSON username field](../../terminologies/json-username-field.md) equals `id -un`. That field is the **user SSOT**. On-behalf-of → fail closed. **MUST NOT** take the user from the filename. **MUST NOT** treat [file-ownership](../../terminologies/file-ownership.md) as part of this submit fence.  
3. The request encodes **one** product-defined kind (`{{KIND}}`). Mixed kinds → reject.  
4. **Inbound** is writable (product default or an explicit queue override). The CLI **allocates** the name.  
5. Input is the product JSON schema, or a documented text dual the CLI converts first.  
6. Product **remove** / revoke shape is honored (often purpose-only; extra grant/payload fields fail closed).

**Not a submit situation:** a change for a colleague; wanting the live dest written immediately; running approve as a normal user.

### 2.3 How JSON is verified

The queued file is the **evidence**. Approvers do **not** trust an inbound drop at face value. Checks at submit **and again at approve**:

| Check | What JSON (and name) must satisfy |
|-------|-----------------------------------|
| **Closed schema** | Product `schema_version`; unknown keys fail closed |
| **Identity match** | User SSOT is the JSON username field, **not** the filename token. Basename **action** MAY still match JSON `action` |
| **Self-scope** | JSON username field = invoker at submit. Dest **MUST** read the user from that field, **not** the filename. **MUST NOT** require file-ownership = that field |
| **File-ownership** | Dest **MUST NOT** fence on Unix owner. When the approval app runs as `{{APPROVER}}`, it **MUST take** file-ownership, then move |
| **Purpose / revoke shape** | Purpose required when the product requires it; revoke must not carry extra grant/payload arrays |
| **Payload rules** | Absolute paths / no broad-rights tokens — **instance law** fills the list |
| **Syntax gate** | If a text dual exists, render JSON → private text, then `{{SYNTAX_GATE}}` (instance fills the tool). **Never** feed raw JSON to that checker |
| **Dest** | Accept maps basename → `{{DEST}}` via the installed-artifact transform. Portable dest class: **`/etc/{{SUBJECT}}/{{KIND}}`**. Never install a revoke-shaped dest name. **MUST NOT** write `/etc/passwd` or `/etc/sudoers.d`. |
| **Re-validate** | Approve **re-runs** these checks. Tamper in inbound fails at approve, not at dest write |

CLI `--json` is **status** only. It is **not** the request file.

### 2.3a Approval fencing conditions (closed, sacred)

Dest `approve` / `reject` / `{{REVIEW_VERB}}` **MUST** run this list **before** any [approval question](../../terminologies/approval-question.md) (**`LM-APPROVAL-SYSTEM`**). This subclass **MUST** include **incorrect JSON format**. Dest **MUST** fail closed on inbound **only** when a listed [approval fencing condition](../../terminologies/approval-fencing-condition.md) holds. When a fence **matches**, dest **MUST display** the match in human-facing words and **MUST NOT** ask yes/no for that file. Specialized law **MUST** print this table in product language. Each dest **Fence** row **MUST** point at an independent REQ (specialize **`LM-FENCE-CONDITION-REQUIREMENT`**). Coding **MUST NOT** add a dest fence that law does not name.

| Condition | Dest approve / reject / `{{REVIEW_VERB}}` |
|-----------|-------------------------------------------|
| **[Incorrect JSON format](../../terminologies/incorrect-json-format.md)** | **Fence** — fail closed. Independent REQ (specialize **`LM-FENCE-CONDITION-REQUIREMENT`**; dest table still prints) |
| File-ownership | **MUST NOT** fence — take ownership as `{{APPROVER}}` |
| Who submitted / dest Type 0 self-scope | **MUST NOT** fence |
| JSON username field ≠ dest LPU | **MUST NOT** fence |
| Filename subject token ≠ JSON username field | **MUST NOT** fence — user SSOT is the JSON field |
| Dest-written `submit_by` / missing `submit_by` | **MUST NOT** fence — dest interactive writes it after format check |
| `submit_app` ≠ dest `APP_NAME` / `submit_version` ≠ dest `VERSION` | **MUST NOT** fence — sibling submitters and mixed versions are dest-legal JSON |

**Incorrect JSON format** includes: not a regular file; not one parseable JSON object; closed-schema fail; field types/enums invalid; basename grammar fail; basename **action** ≠ JSON `action`; missing / non-string / empty `submit_app` or `submit_version` on add/update. It **does not** include basename **subject token** ≠ JSON username field — user SSOT is the JSON field. It **does not** include `submit_app` ≠ dest product or `submit_version` ≠ dest `VERSION`.

Type 0 submit self-scope (invoker = JSON username field) is **not** a dest approval fencing condition. Type 1 **authz** (who may run dest verbs) is **not** an inbound-file fence.

Specialized law **MAY** add a dest fence **only** with explicit user order and a new named row.

### 2.4 Filename class (allocator-owned)

```text
{{PREFIX}}{{YYYYMMDD}}-{{SUBJECT}}-{{KIND}}-{{ACTION}}-{{N}}{{SUFFIX}}
```

| Part | Rule |
|------|------|
| `{{PREFIX}}` / `{{SUFFIX}}` | Product literals (or explicit **none**) |
| `{{YYYYMMDD}}` | Host-local date unless product law says otherwise |
| `{{SUBJECT}}` | Invoker login; path-safe |
| `{{KIND}}` | One product-defined family |
| `{{ACTION}}` | Closed set (typical: `add` \| `update` \| `remove`) |
| `{{N}}` | 1-based, no leading zeros; counted over **inbound ∪ accepted ∪ declined** for the same date+subject+kind+action |

`request_id` **is** that full basename (prefix **and** suffix when declared). Allocator **MUST NOT** take a caller-supplied dest basename.

**Worked sample (placeholders filled in the specialized REQ, not here as product fact):**

```text
{{PREFIX}}20260814-{{SUBJECT}}-{{KIND}}-add-1{{SUFFIX}}
```

### 2.5 Queue instance

One approval-queue **instance** per surface: `{{INBOUND}}` / `{{ACCEPTED}}` / `{{DECLINED}}`.  
`{{INBOUND}}` **is** a file-based approval submission folder (`{{QUEUE_ROOT}}/{{INBOUND_BASENAME}}`). Recommended hosting is a public submission folder. Type 1 creates the dir; Type 0 **MUST NOT** `mkdir` it.

| Check | Rule |
|-------|------|
| Path | **Absolute**; last component **MUST NOT** be a symlink |
| Distinct | Three resolved realpaths **MUST** differ |
| Type 0 | **MUST NOT** `mkdir` the production trio; missing dir fails closed |
| Sequence | `n` walks **all three** resolved dirs |
| Hostile inbound | Copy inode under Type 1 lock; require regular file; re-run validators on the private copy |

Default modes (when Type 1 setup creates them) **SHOULD** be: inbound sticky+setgid dropbox; accepted/declined not world-writable. Instance fills octals.

### 2.5a Queue move ownership (sacred)

A queue **move** (inbound → accepted/declined, or dest approved/rejected) **MUST** assume a **previous** ownership change to the **approver** — or the approval app **takes** that change in the same step when it runs as `{{APPROVER}}`. Terms: [`approval-queue-move`](../../terminologies/approval-queue-move.md) · [`file-ownership`](../../terminologies/file-ownership.md) · [`json-username-field`](../../terminologies/json-username-field.md).

| Actor | Ownership |
|-------|-----------|
| Type 0 submit / Type 1 setup write | **MUST NOT** `chown` the inbound file. Writer leaves ownership as created (`0640`). The JSON username field is **not** file-ownership. |
| Approver (`{{APPROVER}}`) | **MUST NOT** fence or fail because file-ownership ≠ the JSON username field. **MUST** take file-ownership (`chown` to `{{APPROVER}}`) **first**, then move. Fail closed if that `chown` fails. Login-hook review (`sudo -n` as euid 0) **MUST** take file-ownership of inbound as `{{APPROVER}}` **at the beginning**, then review. Queue move assumes that previous change. |
| Sticky inbound (`3773`) | Only owner or root can unlink. That is why dest **takes** ownership instead of testing the previous owner. |

A product that is a **submitter** toward a sibling dest **MUST** leave dest-inbound ownership to that dest’s approver. A product that **is** the dest **MUST** take ownership when run as its LPU — **not** wall on the current owner.

### 2.6 Dest transform class

One live dest **per (`{{SUBJECT}}`, `{{KIND}}`)** unless instance law says otherwise.

| Request action | Live dest |
|----------------|-----------|
| add | install `{{DEST}}` (portable class `/etc/{{SUBJECT}}/{{KIND}}`); backup previous same dest |
| update | replace `{{DEST}}`; backup previous |
| remove | delete `{{DEST}}` only; **never** install a revoke-shaped dest name |

Foreign files that are not this product’s dest names **MUST NOT** be deleted. **MUST NOT** write `/etc/passwd` or `/etc/sudoers.d`.

### 2.7 Schema shape (portable sample — not product law)

Instance law **MUST** replace keys and add a **complete sample per variant**. Field tables alone are not enough.

```json
{
  "schema_version": 1,
  "purpose": "{{PURPOSE_ONE_LINE}}",
  "subject": "{{SUBJECT}}",
  "kind": "{{KIND}}",
  "action": "add",
  "submit_app": "{{APP_NAME}}",
  "submit_version": "{{VERSION}}",
  "payload": {}
}
```

```json
{
  "purpose": "{{PURPOSE_REVOKE_ONE_LINE}}"
}
```

If a text dual exists, the specialized REQ **MUST** include the **paired** text for the same grant.

### 2.8 Interactive review loop (when the product claims a TTY review verb)

If the product exposes `{{REVIEW_VERB}}` (typical name `interactive`):

1. Same Type 1 authorization as accept/decline.  
2. Consume `TTY` / `JSON` / `QUIET`. If `TTY` is not `1`, or `JSON=1`, **fail closed** — no hang. `--force` **MUST NOT** auto-accept.  
3. **At the beginning:** for each inbound request file, dest **MUST** read original [file-ownership](../../terminologies/file-ownership.md), take file-ownership as `{{APPROVER}}` (the corresponding LPU), review JSON format, and if the JSON is correct **MUST** add `submit_by` (human: submit by) set to that original owner. Dest **MUST NOT** add `submit_by` when format fails. Type 0 submit **MUST NOT** include `submit_by`. Fail closed if that `chown` fails. Type 0 submit **MUST** stamp `submit_app` / `submit_version` from live Config (overwrite on queue). Dest **MUST NOT** dest-write those keys.  
4. Prompt only through `prompt_*`.  
5. Empty inbound → success, exit 0.  
6. For each pending id: **fence first** (this subclass includes incorrect JSON format). If a fence **matches**: display the match in human-facing words; **MUST NOT** ask yes/no; continue to the next file. Dest **MUST NOT** treat dest-written `submit_by` as an unknown key. Dest **MUST** treat `submit_app` / `submit_version` as known. Dest **MUST NOT** fence because those values ≠ dest identity.  
7. If **no** fence matched: show purpose + body; display `queued by {submit_app} {submit_version}` when those strings are present; ask the **approval question** ([`approval-question`](../../terminologies/approval-question.md)): **one-off yes/no**. **Yes** = approve. **No** (including Enter) = reject. **MUST NOT** offer skip / quit / maybe. Queue move **MUST** assume the ownership change in step 3.  
8. Empty argv **MUST NOT** reach this handler.

### 2.9 Login hook (when the product claims login-time review)

If the product installs an rc hook for `{{APPROVER}}`: **specialize `LM-LOGIN-INTERACTIVE-REVIEW-HOOK` into an independent REQ** (`requirement-login-interactive-review-hook`). Dest domain SSOT **points**; it **MUST NOT** remain the only owner of the snippet.

| Guard | Rule |
|-------|------|
| **Owner** | Independent login-hook REQ (snippet, `.profile`, labeled name) |
| **Binary** | `sudo -n {{GLOBAL_BIN}}/{{APP_NAME}}-hook {{REVIEW_VERB}}` — [login-hook-symlink](../../terminologies/login-hook-symlink.md). Sibling CLIs reuse `/usr/local/bin/{{APP_NAME}}-hook`. **MUST NOT** overwrite a retargeted name |
| **Live grant** | The hook needs a **`login-hook-elev`** sudoer JSON whose `commands[].path` is the labeled hook name. That grant is **not** the operator `type-2-switch` JSON and **not** the F6 group dual. Queue: **`LM-THREE-LAYER-PRIVILEGE-MODEL`** §2.3.3e. Body: **`LM-SUDOER-JSON-FILE`** §3.0 |
| **Empty argv** | Hook calls the explicit review verb. Empty argv stays help |
| **Old-hook review** | Dest `{{REVIEW_VERB}}` **MUST** review `{{APPROVER}}` rc: old `{{GLOBAL_BIN}}/{{APP_NAME}} {{REVIEW_VERB}}` **MUST** become `{{APP_NAME}}-hook`; already-new **MUST NOT** rewrite. Owner: **`LM-LOGIN-INTERACTIVE-REVIEW-HOOK`** §3.9 |
| **Loop** | Fence first / one-off yes/no stay on this dest mold §2.8 |

The independent hook REQ **MUST** include a **complete snippet sample**. Coverage fails on a one-liner “install in `.bashrc`”.

---

## 3. How to specialize

**First decide which dest this product is.** Do not skip this fork.

| This product is… | Specialize from | Published law |
|------------------|-----------------|---------------|
| **Approval dest** (owns inbound + approve + dest write) | **this mold** | one Active `requirement-domain-{{DOMAIN_SUBJECT}}.md` |
| **Sudoer-approval-submitter** (Type 0 queues a sudoers grant into a **sibling** dest) | **`LM-FILE-BASED-JSON-APPROVAL-SUBMITTER`** + **`LM-SUDOER-JSON-FILE`** + **`LM-THREE-LAYER-PRIVILEGE-MODEL`** §2.3.2a / §2.3.3c / §2.3.3d | `requirement-sudoer-json-file.md` + three-layer generate/submit rows. **Do not** fold the sibling machine into this product’s domain SSOT. |
| **Other-subject submitter** (nginx-conf, …) | **`LM-FILE-BASED-JSON-APPROVAL-SUBMITTER`** + the subject body mold | same pattern; different subject |

A product **MAY** be both an approval dest for **its** subject **and** a sudoer-approval-submitter toward a sibling. Those are **two** machines. dns-request inbound ≠ sudoer-request inbound.

**Approval dest path:**

1. **Collision-check** `docs/requirements/index.md` — prefer updating the one Active domain SSOT.  
2. Copy §2.0–2.3 into that file in **product language**; replace every `{{PLACEHOLDER}}`.  
3. Fill four pillars (verbs, filename+samples, help, about).  
4. Register / bump the registry row. Related artifacts: **peer requirements only** (git-surface: no `docs/templates/**` paths).  
5. Product source cites the live `requirement-domain-*.md` — **never** this mold.  
6. **Do not** create `requirement-file-based-json-approval.md` on a product that has only **one** instance of this machine.  
7. Run **`CL-FILE-BASED-JSON-APPROVAL`**. Coverage: **SK-REQUIREMENT-SUFFICIENT-CHECK** Steps 3c + 3e.

**Submitter path:** follow **`LM-FILE-BASED-JSON-APPROVAL-SUBMITTER`**. Do **not** treat generate/submit as trimmed sudoers-manager extras.

---

## 4. Design principles (CIAO / CIAO-Lite)

- **Caution**: never trust a world-writable inbound inode; re-validate at approve.  
- **Intentional**: name the machine; one Type per verb; allocator owns the basename.  
- **Anti-fragile**: convert may work without queues; list/show may use a sidecar without readdir.  
- **Over-protect**: help does not advertise unrouted verbs; Type 0 never writes the live dest.

**Principles:** **1** Caution · **2** Intentional · **5** output SSOT (`--json` ≠ request file) · **9** Type 0/1/2 · **10** least privilege.

---

## 5. Protection Rule (Sacred)

**Future AI assistants or maintainers MUST NOT**:

1. Hardcode one product’s approver name, inbound dir, dest path, or syntax checker as universal law in this mold.  
2. Specialize by adding a **second** Active generic product requirement that duplicates the domain SSOT.  
3. Collapse submitter and approver into one role.  
4. Replace this machine with a ticket table, mail queue, or database without revising the specialized domain REQ.  
5. Skip approve-time re-validation.  
6. Install a revoke-shaped dest name.  
7. Allow on-behalf-of submit.  
8. Feed raw JSON to `{{SYNTAX_GATE}}` without materializing the text dual.  
9. Let Type 0 `mkdir` production inbound or write the live dest.  
10. Treat the approver LPU as a Type 2 euid for dest writes.  
11. Cite this mold as product-source behavioral authority after specialize.  
12. Dump `docs/templates/**` / `docs/terminologies/**` / `docs/skills/**` paths into versioned `docs/requirements/**`.  
13. Embed **`RQ-*`** product IDs as portable vocabulary.  
14. Strip Terminologies or this Protection Rule for brevity.  
15. Specialize a login hook that hangs `scp` or hijacks empty argv.  
16. Claim TTY-login review complete without a snippet sample and a consume-`TTY` review loop.  
17. Treat the operator `type-2-switch` sudoer JSON (or F6 `%group ALL=(LPU)`) as the hook’s `sudo -n` grant.  
18. `chown` inbound JSON from Type 0 submit or Type 1 setup write. The **approver** takes ownership.  
19. Move inbound → accepted/declined (or dest approved/rejected) **without** a prior ownership change to `{{APPROVER}}`.  
20. Fence dest approve / reject / `{{REVIEW_VERB}}` on [file-ownership](../../terminologies/file-ownership.md) (owner ≠ JSON username field, or owner ≠ approver). Dest **takes** ownership as `{{APPROVER}}`.  
21. Add a dest inbound fence that is not on §2.3a (who submitted, dest Type 0 self-scope, JSON username ≠ dest LPU, filename subject token ≠ JSON username field). Dest inbound fence is **incorrect JSON format**. User SSOT is the JSON field.

**Violating this rule is a critical portability / domain-SSOT / privilege regression.**

---

## 6. Related artifacts (harness — not product Related tables)

| Artifact | Relationship |
|----------|----------------|
| **`LM-THREE-LAYER-PRIVILEGE-MODEL`** | Type map + dest writes after euid 0 |
| **`LM-LEAST-PRIVILEGE-USER`** | `{{APPROVER}}` account |
| **`LM-CLI-INTERFACE`** | Dispatcher / help honesty |
| **`LM-OUTPUT-REQUIREMENTS`** | `--json` status |
| **`LM-TEMP-FILE-SYSTEM`** | Convert / syntax-gate scratch |
| **`LM-SHELL-CLI-STORAGE`** | Queue / scratch roots |
| **`CL-FILE-BASED-JSON-APPROVAL`** | Review gate |
| **`PM-DOMAIN-TEST-PLAN`** | Specialize **`TP-<SUBJECT>-*`** |
| Term `file-based-json-approval` | Class glossary |
| **`LM-FILE-BASED-JSON-APPROVAL-SUBMITTER`** | Type 0 sibling that **calls** this machine |

---

## Design-time verification

| TP family / ID | Proof mold | Planned suite / intent |
|----------------|------------|------------------------|
| **`TP-<DOMAIN_SUBJECT>-01`** | **`PM-DOMAIN-TEST-PLAN`** | Basename grammar: prefix / suffix / `n` |
| **`TP-<DOMAIN_SUBJECT>-02`** | **`PM-DOMAIN-TEST-PLAN`** | Closed schema; revoke shape; unknown keys |
| **`TP-<DOMAIN_SUBJECT>-03`** | **`PM-DOMAIN-TEST-PLAN`** | Self-scope fail; on-behalf-of rejected |
| **`TP-<DOMAIN_SUBJECT>-04`** | **`PM-DOMAIN-TEST-PLAN`** | Type 0 never writes `{{DEST}}`; Type 1 fail-closed without euid 0 |
| **`CL-FILE-BASED-JSON-APPROVAL`** | this checklist | Named machine present in domain REQ (roles / submit-when / verify) |
| **`TP-<DOMAIN_SUBJECT>-INT-*`** | **`PM-DOMAIN-TEST-PLAN`** | Review verb without euid 0; non-TTY fail closed; hook skip |

Replace `{{DOMAIN_SUBJECT}}` in the **TP family token** with the product domain slug. **Do not** freeze a shared **`TP-DOM-*`** or a product **`RQ-*`** here.

**RTM:** `../tests/template-requirement-test-traceability.md` · cite **`LM-FILE-BASED-JSON-APPROVAL`**

When a row does not apply, mark **n/a** with reason in product `reviews/test-plan.md`.

---

**Last Updated**: 2026-09-08  
**Owner**: {{OWNER}}  
**Version history:**  
- **1.18.0** (2026-09-08): §2.9 dest `{{REVIEW_VERB}}` old-hook review **points** at **`LM-LOGIN-INTERACTIVE-REVIEW-HOOK`** §3.9.  
- **1.17.0** (2026-09-08): §2.9 specializes **`LM-LOGIN-INTERACTIVE-REVIEW-HOOK`** into an independent REQ; snippet uses `{{APP_NAME}}-hook`; domain **points**.  
- **1.16.0** (2026-08-21): Type 0 stamps `submit_app` / `submit_version` from live Config. Dest-known; missing/non-string on add/update is format. Dest **MUST NOT** fence if value ≠ dest identity. Display `queued by {app} {version}` before yes/no. Terms `submit-app` · `submit-version`.  
- **1.15.0** (2026-08-19): Dest **Fence** row MUST point at an independent REQ (`LM-FENCE-CONDITION-REQUIREMENT`).  
- **1.14.0** (2026-08-19): Interactive take-ownership records original file-ownership, takes as LPU, format-checks, then dest-writes `submit_by`.  
- **1.13.0** (2026-08-19): Named dest leaves LM-SUDOER / LM-NGINX-CONF / LM-CLOUDFLARE-DNS-APPROVAL-SYSTEM.  
- **1.12.0** (2026-08-19): §2.3a dest MUST NOT fence on filename subject token ≠ JSON username field.  
- **1.11.0** (2026-08-19): User SSOT is the JSON username field, not the filename subject token.  
- **1.10.0** (2026-08-19): Subclass of **`LM-APPROVAL-SYSTEM`**: fence first, human-facing match display, then questions. JSON format fence required.  
- **1.9.0** (2026-08-19): §2.8 approval question is one-off yes/no (yes=approve, no=reject); term `approval-question`.  
- **1.8.0** (2026-08-19): §2.8 login-hook / `{{REVIEW_VERB}}` takes inbound file-ownership as `{{APPROVER}}` **at the beginning**.  
- **1.7.0** (2026-08-18): §2.3a closed dest approval fencing conditions; dest fence is incorrect JSON format.  
- **1.6.0** (2026-08-18): Dest MUST NOT fence on file-ownership; LPU takes ownership. Terms `file-ownership` · `json-username-field`.  
- **1.5.0** (2026-08-18): §2.5a queue move assumes prior `chown` to `{{APPROVER}}`; submitter/setup MUST NOT `chown`.  
- **1.4.0** (2026-08-18): §2.9 hook `sudo -n` needs `login-hook-elev` grant — not Type 0 `type-2-switch`.  
- **1.3.0** (2026-08-18): Specialize fork — approval dest vs sudoer-approval-submitter; do not treat generate/submit as trimmed extras.  
- **1.1.0** (2026-08-14): Interactive review loop + login-hook guards; snippet sample required.  
- **1.0.0** (2026-08-14): Initial portable machine — named design, roles, submit-when, verify, allocator basename, dest class; specialize into one domain SSOT.

**Alignment**: term `file-based-json-approval` · `file-based-approval-submission-folder` · `public-submission-folder` · approval-queue · self-scope-request · least-privilege-approver · three-layer-privilege · CIAO Principles 1, 2, 5, 9, 10 · CIAO-Lite (https://github.com/cloudgen/ciao-lite)

---

**How to use this template**:

1. Keep under `docs/templates/requirements/` as the **only** portable body of this machine.  
2. Specialize into the product domain SSOT — do not leave a second generic `requirement-*.md` for one instance.  
3. Fill Implementation Notes with real `{{APPROVER}}`, inbound names, schema, dest, and `{{SYNTAX_GATE}}`.  
4. Product source cites the live requirement only.  
5. Run **`CL-FILE-BASED-JSON-APPROVAL`**.
