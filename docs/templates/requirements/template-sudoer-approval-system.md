---
name: sudoer-approval-system
id: LM-SUDOER-APPROVAL-SYSTEM
kind: law-mold
description: >
  Thin dest mold for the sudoer approval system: approval-system subclass
  whose dest is a sudoers grant. File-based JSON; dest LPU is
  {{SUDOER_APPROVER}}. Cite as LM-SUDOER-APPROVAL-SYSTEM.
---

**file**: template-sudoer-approval-system.md  
**Mold-ID**: LM-SUDOER-APPROVAL-SYSTEM  
**Status**: Active (Version 1.0.0)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered / Over-protect)

# Template: Sudoer approval system

## 1. Purpose

Portable dest law for **[sudoer-approval-system](../../terminologies/sudoer-approval-system.md)** — a **subclass of [approval-system](../../terminologies/approval-system.md)** (and of [file-based JSON approval](../../terminologies/file-based-json-approval.md)) whose dest is a **sudoers grant**.

**Peers (do not duplicate):**

| Concern | Owner |
|---------|--------|
| Review order / fence-then-question | **`LM-APPROVAL-SYSTEM`** |
| Folders, verify table, dest fence catalog | **`LM-FILE-BASED-JSON-APPROVAL`** |
| JSON body, kinds, three dests | **`LM-SUDOER-JSON-FILE`** |
| Type 0 submitter product | **`LM-FILE-BASED-JSON-APPROVAL-SUBMITTER`** |

This mold **MUST NOT** invent dest paths as universal law. Specialize `{{SUDOER_APPROVER}}`, inbound names, and `/etc/sudoers.d/{{APP_NAME}}-{{TARGET_USER}}` in product law.

## Terminologies

| Term | Path | SSOT type | Role |
|------|------|-----------|------|
| sudoer-approval-system | [`sudoer-approval-system.md`](../../terminologies/sudoer-approval-system.md) | H1 include | This dest leaf |
| approval-system | [`approval-system.md`](../../terminologies/approval-system.md) | H1 include | Superclass |
| file-based-json-approval | [`file-based-json-approval.md`](../../terminologies/file-based-json-approval.md) | H1 include | Mechanism |
| sudoer-approval-submitter | [`sudoer-approval-submitter.md`](../../terminologies/sudoer-approval-submitter.md) | H1 include | Type 0 caller |
| json-username-field | [`json-username-field.md`](../../terminologies/json-username-field.md) | H1 include | User SSOT (`username`) |
| incorrect-json-format | [`incorrect-json-format.md`](../../terminologies/incorrect-json-format.md) | H1 include | Required dest fence |
| project-templates | [`project-templates.md`](../../terminologies/project-templates.md) | H1 include | Mold surface |
| docs-folder-structure | [`docs-folder-structure.md`](../../terminologies/docs-folder-structure.md) | H1 include | Docs map |
| no-hardcode-policy | [`no-hardcode-policy.md`](../../terminologies/no-hardcode-policy.md) | H1 include | No frozen dest product |
| dual-policies | [`dual-policies.md`](../../terminologies/dual-policies.md) | H1 include | Complete × portable |

## 2. Dest fill

| Piece | This subclass |
|-------|----------------|
| Approver | `{{SUDOER_APPROVER}}` (typical `sudoer-adm`) |
| Subject | sudoer-json-file |
| User SSOT | JSON `username` — **not** the filename token |
| Syntax gate | `visudo -cf` on the rendered text dual |
| Dest after accept | `/etc/sudoers.d/{{APP_NAME}}-{{TARGET_USER}}` (instance fills the three dests) |
| Submitter | sudoer-approval-submitter — **MUST NOT** write `/etc/sudoers.d` |

Dest **MUST** inherit **`LM-APPROVAL-SYSTEM`** review order and **`LM-FILE-BASED-JSON-APPROVAL`** §2.3a. Dest **MUST NOT** drop incorrect JSON format. Dest **MUST NOT** fence on filename subject token ≠ JSON `username`.

## 3. Stay-honest (this workspace)

A software-dev product that only **submits** sudoer JSON **MUST NOT** claim dest Implemented. Dest write stays on the sibling dest product.

## 4. Protection Rule (Sacred)

Future agents **MUST NOT**:

1. Treat `dns-adm` or `nginx-adm` as this dest approver.  
2. Write `/etc/sudoers.d` from a DNS or nginx dest accept.  
3. Fence dest on the filename subject token.  
4. Ask yes/no before fencing.

**Last Updated**: 2026-08-19  
**Owner**: {{OWNER}}  
**Version history:**  
- **1.0.0** (2026-08-19): Named sudoer dest subclass of approval-system.
