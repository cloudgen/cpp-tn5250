---
name: cloudflare-dns-approval-system
id: LM-CLOUDFLARE-DNS-APPROVAL-SYSTEM
kind: law-mold
description: >
  Thin dest mold for the Cloudflare DNS approval system: approval-system
  subclass whose dest is a Cloudflare A / mode apply. File-based JSON;
  dest LPU is {{DNS_APPROVER}}. Cite as LM-CLOUDFLARE-DNS-APPROVAL-SYSTEM.
---

**file**: template-cloudflare-dns-approval-system.md  
**Mold-ID**: LM-CLOUDFLARE-DNS-APPROVAL-SYSTEM  
**Status**: Active (Version 1.0.0)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered / Over-protect)

# Template: Cloudflare DNS approval system

## 1. Purpose

Portable dest law for **[cloudflare-dns-approval-system](../../terminologies/cloudflare-dns-approval-system.md)** — a **subclass of [approval-system](../../terminologies/approval-system.md)** (and of [file-based JSON approval](../../terminologies/file-based-json-approval.md)) whose dest is a [Cloudflare DNS request](../../terminologies/cloudflare-dns-request.md) apply.

**Peers (do not duplicate):**

| Concern | Owner |
|---------|--------|
| Review order / fence-then-question | **`LM-APPROVAL-SYSTEM`** |
| Folders, verify table, dest fence catalog | **`LM-FILE-BASED-JSON-APPROVAL`** |
| Four request types + schema | **`LM-CLOUDFLARE-DNS-REQUEST`** |
| Actor table / login hook | specialized `requirement-dns-actor-table` |

This mold **MUST NOT** invent vault keys or zone create as dest.

## Terminologies

| Term | Path | SSOT type | Role |
|------|------|-----------|------|
| cloudflare-dns-approval-system | [`cloudflare-dns-approval-system.md`](../../terminologies/cloudflare-dns-approval-system.md) | H1 include | This dest leaf |
| approval-system | [`approval-system.md`](../../terminologies/approval-system.md) | H1 include | Superclass |
| file-based-json-approval | [`file-based-json-approval.md`](../../terminologies/file-based-json-approval.md) | H1 include | Mechanism |
| cloudflare-dns-request | [`cloudflare-dns-request.md`](../../terminologies/cloudflare-dns-request.md) | H1 include | Queued body |
| json-username-field | [`json-username-field.md`](../../terminologies/json-username-field.md) | H1 include | User SSOT (`subject`) |
| incorrect-json-format | [`incorrect-json-format.md`](../../terminologies/incorrect-json-format.md) | H1 include | Required dest fence |
| project-templates | [`project-templates.md`](../../terminologies/project-templates.md) | H1 include | Mold surface |
| docs-folder-structure | [`docs-folder-structure.md`](../../terminologies/docs-folder-structure.md) | H1 include | Docs map |
| no-hardcode-policy | [`no-hardcode-policy.md`](../../terminologies/no-hardcode-policy.md) | H1 include | No frozen zone ids |
| dual-policies | [`dual-policies.md`](../../terminologies/dual-policies.md) | H1 include | Complete × portable |

## 2. Dest fill

| Piece | This subclass |
|-------|----------------|
| Approver | `{{DNS_APPROVER}}` (this product: `dns-adm`) |
| Subject | cloudflare-dns-request (`add` / `update` / `remove` / `mode`) |
| User SSOT | JSON `subject` — **not** the filename token |
| Dest after accept | Vault DNS / mode verbs. **MUST NOT** write `/etc/passwd` or `/etc/sudoers.d` |
| Type 0 submit | Any login; self-scope is JSON `subject` = `id -un` |

Dest **MUST** inherit **`LM-APPROVAL-SYSTEM`** review order and **`LM-FILE-BASED-JSON-APPROVAL`** §2.3a. Dest **MUST NOT** drop incorrect JSON format. Dest **MUST NOT** fence on filename subject token ≠ JSON `subject`.

## 3. Stay-honest (this workspace)

Dest `submit` / `approve` / `reject` / `interactive` are **Implemented** on `src/dns-cli`. Sibling sudoer dest is **not** this subclass.

## 4. Protection Rule (Sacred)

Future agents **MUST NOT**:

1. Treat `sudoer-adm` as this dest approver.  
2. Write `/etc/sudoers.d` on DNS accept.  
3. Fence dest on the filename subject token.  
4. Ask yes/no before fencing.

**Last Updated**: 2026-08-19  
**Owner**: {{OWNER}}  
**Version history:**  
- **1.0.0** (2026-08-19): Named Cloudflare DNS dest subclass of approval-system.
