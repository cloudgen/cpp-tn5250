---
name: fence-condition-requirement
id: LM-FENCE-CONDITION-REQUIREMENT
kind: law-mold
description: >
  Portable mold for one dest Fence condition as an independent requirement.
  Software-development projects MUST review dest fences and convert each
  Fence row. Cite as LM-FENCE-CONDITION-REQUIREMENT.
---

**file**: template-fence-condition-requirement.md  
**Mold-ID**: LM-FENCE-CONDITION-REQUIREMENT  
**Status**: Active (Version 1.4.0)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile · Over-engineered / Over-protect)

# Template: Fence-condition requirement

## 1. Purpose

Portable law for **one dest Fence** as its own requirement.

Every **software-development** project **MUST review** whether dest fencing conditions exist. Each dest **Fence** row **MUST** specialize this mold (or an equivalent independent REQ). Dest fence tables **MUST** still print the closed catalog and **point** at those REQs.

**Do not use this mold for:** dest **MUST NOT** fence rows; dest login-hook snippets; actor catalogs.

## Terminologies

| Term | Path | SSOT type | Role |
|------|------|-----------|------|
| fence-condition-requirement | [`fence-condition-requirement.md`](../../terminologies/fence-condition-requirement.md) | H1 include | This class |
| approval-fencing-condition | [`approval-fencing-condition.md`](../../terminologies/approval-fencing-condition.md) | H1 include | Closed dest list |
| incorrect-json-format | [`incorrect-json-format.md`](../../terminologies/incorrect-json-format.md) | H1 include | Typical dest Fence |
| fence-test | [`fence-test.md`](../../terminologies/fence-test.md) | H1 include | Type 0 dest-fence list tester (**test-purpose**) |
| test-purpose-verb | [`test-purpose-verb.md`](../../terminologies/test-purpose-verb.md) | H1 include | Unit-test verb class (local test folder) |
| operational-verb | [`operational-verb.md`](../../terminologies/operational-verb.md) | H1 include | Live product verb class (not a tester) |
| software-development-project | [`software-development-project.md`](../../terminologies/software-development-project.md) | H1 include | Class that MUST review |
| named-law-table | [`named-law-table.md`](../../terminologies/named-law-table.md) | H1 include | Confirm table first |
| project-templates | [`project-templates.md`](../../terminologies/project-templates.md) | H1 include | Mold surface |
| docs-folder-structure | [`docs-folder-structure.md`](../../terminologies/docs-folder-structure.md) | H1 include | Docs map |
| no-hardcode-policy | [`no-hardcode-policy.md`](../../terminologies/no-hardcode-policy.md) | H1 include | No invented dest fence |
| dual-policies | [`dual-policies.md`](../../terminologies/dual-policies.md) | H1 include | Complete × portable |

## 2. Core rules (MUST)

**FC-M1. One Fence, one REQ.** Specialized law **MUST** name **exactly one** dest **Fence** condition. **MUST NOT** fold two dest Fences into one file.

**FC-M2. Dest table still prints.** The dest fence table **MUST** keep a **Fence** row that **points** at this requirement. This file **MUST NOT** delete that table.

**FC-M3. Meaning.** This REQ **MUST** state: what matches, dest fail-closed behavior, human-facing display, and that dest **MUST NOT** ask yes/no on a match.

**FC-M4. Software-dev review.** A software-development project **MUST** either publish one independent REQ per dest **Fence**, **or** residual **considered — no dest fence conditions**. **MUST NOT** invent a dest fence.

**FC-M5. MUST NOT rows stay tables.** Dest **MUST NOT** fence rows **MUST NOT** become this mold.

**FC-M6. Dest Fence Type 0 tester (`fence-test`).** When dest has **any** dest **Fence** row, specialized law **MUST** name Type 0 **`fence-test`** as a **test-purpose** verb: **unit test** of dest fence **functions** against a JSON **file location** in a **local test folder**. Input: stdin **xor** `--file PATH` **xor** `--dir DIR` of regular `*.json`. `--dir` continues after a match. `--expect-match` with `--dir` succeeds only when every file matches a dest Fence. Dual mention: language CLI-interface REQ **and** the dest domain SSOT. Per-row testers **MAY** also exist and are also test-purpose. **MUST NOT** require `sudo` to run. The only allowed in-tool elev is the sudo-wrapping function for **chmod** / **chown** of that local test folder (check before sudo; skip sudo when this login already owns the path). **MUST NOT** sudo otherwise. **MUST NOT** require a sudoers fragment. **MUST NOT** submit, queue, dest-write, `setup`, `approve`, or other **operational** steps. **MUST NOT** treat dest `approve` / `reject` / review, host install, or queue presence as this tester. Help **MUST** list this verb **apart** from operational verbs. Agents add cases by giving a JSON path (or dropping a file in a corpus folder).

## 3. Protection Rule (Sacred)

Future agents **MUST NOT**:

1. Leave a dest **Fence** as only a table cell.  
2. Invent a dest fence so the project has a file.  
3. Convert a **MUST NOT** fence row into a dest Fence REQ.  
4. Drop the dest fence table after extracting this REQ.  
5. Leave dest Fences without Type 0 **`fence-test`**, treat dest review / queue / `sudo` / a sudoers fragment as that tester, require host install to run it, group it with operational verbs in help, or `sudo` except wrapping chmod/chown of the local test folder.

**Last Updated**: 2026-08-21  
**Owner**: {{OWNER}}  
**Version history:**  
- **1.4.0** (2026-08-21): **FC-M6** — `fence-test` is a **test-purpose** verb (unit test; local test folder). Sudo wrap only chmod/chown of that folder. Help lists it apart from operational verbs.  
- **1.3.0** (2026-08-21): **FC-M6** — `fence-test` is JSON-file verification only: **no sudo**, **no sudoers fragment**, **no queue**. Input is a file location.  
- **1.2.0** (2026-08-21): **FC-M6** — any dest Fence set MUST ship Type 0 **`fence-test`** (closed list; `--file` / `--dir` corpus).  
- **1.1.0** (2026-08-20): **FC-M6** — JSON-format dest Fence MUST name a Type 0 test subcommand.  
- **1.0.0** (2026-08-19): Software-dev MUST review dest fences; each Fence row is an independent REQ.
