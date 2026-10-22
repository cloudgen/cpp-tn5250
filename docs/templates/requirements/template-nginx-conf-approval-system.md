---
name: nginx-conf-approval-system
id: LM-NGINX-CONF-APPROVAL-SYSTEM
kind: law-mold
description: >
  Thin dest mold for the nginx-conf approval system: approval-system
  subclass whose dest is an nginx-conf publish. File-based JSON; dest
  LPU is {{NGINX_APPROVER}}. Cite as LM-NGINX-CONF-APPROVAL-SYSTEM.
---

**file**: template-nginx-conf-approval-system.md  
**Mold-ID**: LM-NGINX-CONF-APPROVAL-SYSTEM  
**Status**: Active (Version 1.0.0)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered / Over-protect)

# Template: Nginx-conf approval system

## 1. Purpose

Portable dest law for **[nginx-conf-approval-system](../../terminologies/nginx-conf-approval-system.md)** — a **subclass of [approval-system](../../terminologies/approval-system.md)** (and of [file-based JSON approval](../../terminologies/file-based-json-approval.md)) whose dest is an **[nginx-conf](../../terminologies/nginx-conf.md)** publish.

**Peers (do not duplicate):**

| Concern | Owner |
|---------|--------|
| Review order / fence-then-question | **`LM-APPROVAL-SYSTEM`** |
| Folders, verify table, dest fence catalog | **`LM-FILE-BASED-JSON-APPROVAL`** |
| Conf statement / structure | **`LM-NGINX-CONF-STRUCTURE`** (when present) |
| Type 0 submitter product | **`LM-FILE-BASED-JSON-APPROVAL-SUBMITTER`** |

This mold **MUST NOT** invent dest product verbs as universal law. Specialize `{{NGINX_APPROVER}}` and `{{NGINX_CONF_ROOT}}` in the dest product.

## Terminologies

| Term | Path | SSOT type | Role |
|------|------|-----------|------|
| nginx-conf-approval-system | [`nginx-conf-approval-system.md`](../../terminologies/nginx-conf-approval-system.md) | H1 include | This dest leaf |
| approval-system | [`approval-system.md`](../../terminologies/approval-system.md) | H1 include | Superclass |
| file-based-json-approval | [`file-based-json-approval.md`](../../terminologies/file-based-json-approval.md) | H1 include | Mechanism |
| nginx-conf-approval-submitter | [`nginx-conf-approval-submitter.md`](../../terminologies/nginx-conf-approval-submitter.md) | H1 include | Type 0 caller |
| nginx-config-request-workflow | [`nginx-config-request-workflow.md`](../../terminologies/nginx-config-request-workflow.md) | H1 include | Stage list |
| nginx-conf | [`nginx-conf.md`](../../terminologies/nginx-conf.md) | H1 include | Subject |
| json-username-field | [`json-username-field.md`](../../terminologies/json-username-field.md) | H1 include | User SSOT |
| incorrect-json-format | [`incorrect-json-format.md`](../../terminologies/incorrect-json-format.md) | H1 include | Required dest fence |
| project-templates | [`project-templates.md`](../../terminologies/project-templates.md) | H1 include | Mold surface |
| docs-folder-structure | [`docs-folder-structure.md`](../../terminologies/docs-folder-structure.md) | H1 include | Docs map |
| no-hardcode-policy | [`no-hardcode-policy.md`](../../terminologies/no-hardcode-policy.md) | H1 include | No frozen dest product |
| dual-policies | [`dual-policies.md`](../../terminologies/dual-policies.md) | H1 include | Complete × portable |

## 2. Dest fill

| Piece | This subclass |
|-------|----------------|
| Approver | `{{NGINX_APPROVER}}` (typical `nginx-adm`) |
| Subject | nginx-conf (queued as nginx config request JSON) |
| User SSOT | JSON username field — **not** the filename token |
| Dest after accept | `{{NGINX_CONF_ROOT}}/sites-available/{{domain}}.conf` + `sites-enabled` symlink |
| Submitter | nginx-conf-approval-submitter — **MUST NOT** write live Nginx dest |

Dest **MUST** inherit **`LM-APPROVAL-SYSTEM`** review order and **`LM-FILE-BASED-JSON-APPROVAL`** §2.3a. Dest **MUST NOT** drop incorrect JSON format. Dest **MUST NOT** fence on filename subject token ≠ JSON username field. The approval question is one-off yes/no — dest **MUST NOT** keep skip/quit.

## 3. Stay-honest (this workspace)

If the dest product is **not** in the tree, specialized law **MUST** stay **Gap**. Do not invent dest verbs or claim dest Implemented on a DNS CLI.

## 4. Protection Rule (Sacred)

Future agents **MUST NOT**:

1. Treat `dns-adm` or `sudoer-adm` as this dest approver.  
2. Claim dest Implemented on a product that only submits (or does neither).  
3. Fence dest on the filename subject token.  
4. Ask yes/no before fencing.

**Last Updated**: 2026-08-19  
**Owner**: {{OWNER}}  
**Version history:**  
- **1.0.0** (2026-08-19): Named nginx-conf dest subclass of approval-system.
