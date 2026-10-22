---
name: actor-role-subject-approver
id: LM-ACTOR-ROLE-SUBJECT-APPROVER
kind: law-mold
description: >
  Portable consider catalog: actor, role, subject, approver. Every
  software-development project MUST consider this requirement type.
  Approver MAY be None. Cite as LM-ACTOR-ROLE-SUBJECT-APPROVER.
---

**file**: template-actor-role-subject-approver.md  
**Mold-ID**: LM-ACTOR-ROLE-SUBJECT-APPROVER  
**Status**: Active (Version 1.1.0)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered / Over-protect)

# Template: Actor / role / subject / approver

## 1. Purpose

Portable law for the **actor / role / subject / approver** consider catalog.

Every **software-development** project **MUST** consider this requirement type **even if there is no dest approver**. **None** is a valid Approver (and Subject) fill. Specialize into `requirement-actor-role-subject-approver.md` (product stem allowed).

**Do not use this mold for:** dest login-hook snippets, dest fence tables, Type 0/1/2 elev tables. Those stay on dest actor-table / three-layer / dest approval-system law.

## Terminologies

| Term | Path | SSOT type | Role |
|------|------|-----------|------|
| actor-role-subject-approver | [`actor-role-subject-approver.md`](../../terminologies/actor-role-subject-approver.md) | H1 include | This catalog |
| software-development-project | [`software-development-project.md`](../../terminologies/software-development-project.md) | H1 include | Class that MUST consider |
| named-law-table | [`named-law-table.md`](../../terminologies/named-law-table.md) | H1 include | Confirm-before-write |
| approval-system | [`approval-system.md`](../../terminologies/approval-system.md) | H1 include | Dest review if dest exists |
| least-privilege-approver | [`least-privilege-approver.md`](../../terminologies/least-privilege-approver.md) | H1 include | Account class when dest exists |
| approval-subject | [`approval-subject.md`](../../terminologies/approval-subject.md) | H1 include | Subject when dest exists |
| json-username-field | [`json-username-field.md`](../../terminologies/json-username-field.md) | H1 include | User SSOT on dest JSON |
| project-templates | [`project-templates.md`](../../terminologies/project-templates.md) | H1 include | Mold surface |
| docs-folder-structure | [`docs-folder-structure.md`](../../terminologies/docs-folder-structure.md) | H1 include | Docs map |
| no-hardcode-policy | [`no-hardcode-policy.md`](../../terminologies/no-hardcode-policy.md) | H1 include | No invented `*-adm` |
| dual-policies | [`dual-policies.md`](../../terminologies/dual-policies.md) | H1 include | Complete × portable |

## 2. Core rules (MUST)

**ARSA-M1. Software-dev MUST consider.** A software-development project **MUST** publish **either** this catalog as Active product law **or** the light catalog **`LM-ACTOR-ROLE-SUBJECT`** (`requirement-actor-role-subject`) **or** residual on the class file: **considered — no dest approver and no approval subject**. Use **this** mold when dest review exists (Approver **MAY** still be **None** on some rows). Use the **light** mold when there is **no** dest machine and you do **not** want an Approver column.

**ARSA-M2. None is valid.** Approver **MAY** be **None**. Subject **MAY** be **None**. Submitter **MAY** be **None**. **MUST** write **None** when dest review, dest submit, or a dest subject does not exist. **MUST NOT** invent an approver account.

**ARSA-M2a. Submitter before Approver.** Closed fills: **anyone** · **the actor itself** · **None**.

**ARSA-M3. Five-column table.** Specialized law **MUST** print:

| Actor | Role | Subject | Submitter | Approver |
|-------|------|---------|-----------|----------|
| `{{ACTOR}}` | `{{ROLE}}` | `{{SUBJECT_OR_NONE}}` | `{{SUBMITTER_ANYONE_SELF_OR_NONE}}` | `{{APPROVER_OR_NONE}}` |

Every product verb family that people actually run **MUST** have at least one row. Day-to-day help/install with no dest **MUST** still appear (Approver = **None**).

**ARSA-M4. Dest tables stay dest.** When dest review **is** Implemented, a dest actor table **MAY** own dest who/procedure. This catalog **MUST NOT** absorb dest fence rows or login-hook snippets.

**ARSA-M5. User SSOT on dest rows.** When Subject is a dest request, user identity is the JSON username field, **not** the filename token.

## 3. Class residual (when no dest)

If the product has **no** dest approval machine:

```text
considered — no dest approver and no approval subject
```

That residual **is** the consider. Do **not** skip it.

## 4. Protection Rule (Sacred)

Future agents **MUST NOT**:

1. Skip this consider because dest review is absent.  
2. Invent `{{APPROVER}}` so the table looks complete.  
3. Replace dest actor-table / dest fence law with this catalog.  
4. Apply this consider under genesis-template, policy, or marketing-analysis (zero REQs).

**Last Updated**: 2026-08-19  
**Owner**: {{OWNER}}  
**Version history:**  
- **1.1.0** (2026-08-19): Submitter column immediately before Approver (anyone / the actor itself / None).  
- **1.0.0** (2026-08-19): Software-dev MUST consider; Approver MAY be None.
