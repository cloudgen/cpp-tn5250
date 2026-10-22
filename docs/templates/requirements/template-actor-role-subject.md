---
name: actor-role-subject
id: LM-ACTOR-ROLE-SUBJECT
kind: law-mold
description: >
  Portable light consider catalog: actor, role, subject — no Approver column.
  Use when dest review does not exist. Cite as LM-ACTOR-ROLE-SUBJECT.
---

**file**: template-actor-role-subject.md  
**Mold-ID**: LM-ACTOR-ROLE-SUBJECT  
**Status**: Active (Version 1.0.0)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered / Over-protect)

# Template: Actor / role / subject (light table)

## 1. Purpose

Portable law for the **actor / role / subject** light consider catalog.

Use this mold when the product has **no dest approver**. Specialize into `requirement-actor-role-subject.md`.

When dest review **is** Implemented, specialize **`LM-ACTOR-ROLE-SUBJECT-APPROVER`** instead. **MUST NOT** add an Approver column here.

**Do not use this mold for:** dest login-hook snippets, dest fence tables, Type 0/1/2 elev tables, or the routed-verb catalog.

## Terminologies

| Term | Path | SSOT type | Role |
|------|------|-----------|------|
| actor-role-subject | [`actor-role-subject.md`](../../terminologies/actor-role-subject.md) | H1 include | This light catalog |
| actor-role-subject-approver | [`actor-role-subject-approver.md`](../../terminologies/actor-role-subject-approver.md) | H1 include | Full catalog when dest exists |
| software-development-project | [`software-development-project.md`](../../terminologies/software-development-project.md) | H1 include | Class that MUST consider |
| named-law-table | [`named-law-table.md`](../../terminologies/named-law-table.md) | H1 include | Confirm-before-write |
| cli-routed-verb-table | [`cli-routed-verb-table.md`](../../terminologies/cli-routed-verb-table.md) | H1 include | Commands, not who |

## 2. Core rules (MUST)

**ARS-M1. Software-dev MUST consider.** A software-development project **MUST** publish **either** this light catalog **or** `requirement-actor-role-subject-approver` **or** class residual **considered — no dest approver and no approval subject**.

**ARS-M2. No Approver column.** Specialized law **MUST** print:

| Actor | Role | Subject |
|-------|------|---------|
| `{{ACTOR}}` | `{{ROLE}}` | `{{SUBJECT_OR_NONE}}` |

**MUST NOT** add Submitter or Approver. **MUST NOT** invent `{{APPROVER}}`.

**ARS-M3. CLI verb families.** Every product verb family people actually run **MUST** have at least one row. Day-to-day help/install with no dest **MUST** still appear (Subject = **None**).

**ARS-M4. Upgrade when dest exists.** If dest review becomes Implemented, **MUST** specialize **`LM-ACTOR-ROLE-SUBJECT-APPROVER`** and **MUST NOT** keep this three-column table as dest coverage.

## 3. Design-time verification

| Family | Intent |
|--------|--------|
| **TP-ARS-*** | Table present; three columns only; help/install rows; no invented approver |

Proof catalog: product `reviews/test-plan.md` after specialize. Superclass RTM: `../tests/template-requirement-test-traceability.md`.

## 4. Protection Rule (Sacred)

Future agents **MUST NOT**:

1. Skip this consider because dest review is absent.  
2. Add Approver “for completeness.”  
3. Use this mold when dest review is Implemented.  
4. Apply this consider under genesis-template, policy, or marketing-analysis (zero REQs).

**Last Updated**: 2026-08-28  
**Owner**: {{OWNER}}  
**Version history:**  
- **1.0.0** (2026-08-28): Light three-column catalog; CLI skills consider ARS **or** ARSA.
