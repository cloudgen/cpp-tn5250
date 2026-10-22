---
name: approval-system
id: LM-APPROVAL-SYSTEM
kind: law-mold
description: >
  Portable superclass mold for any dest approval system: fence first,
  human-facing display if a fencing condition matches, then approval
  questions. File-based JSON is a subclass and MUST include a JSON
  format fence. Cite as LM-APPROVAL-SYSTEM.
---

**file**: template-approval-system.md  
**Mold-ID**: LM-APPROVAL-SYSTEM  
**Status**: Active (Version 1.1.0)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered / Over-protect)

# Template: Approval system (superclass)

## 1. Purpose

Portable law for the **approval-system** superclass. Dest review **MUST**:

1. Handle [approval fencing conditions](../../terminologies/approval-fencing-condition.md) **first**.  
2. If a listed fence **matches**: **display** the match in human-facing words (what happened / what it means / next). **MUST NOT** ask an [approval question](../../terminologies/approval-question.md) for that proposal.  
3. If **no** fence matched: ask the approval question.

[File-based JSON approval](../../terminologies/file-based-json-approval.md) is the **mechanism subclass**. Named dest leaves: [sudoer-approval-system](../../terminologies/sudoer-approval-system.md) · [nginx-conf-approval-system](../../terminologies/nginx-conf-approval-system.md) · [cloudflare-dns-approval-system](../../terminologies/cloudflare-dns-approval-system.md). Specialize folder+JSON law with **`LM-FILE-BASED-JSON-APPROVAL`**. Thin dest molds: **`LM-SUDOER-APPROVAL-SYSTEM`** · **`LM-NGINX-CONF-APPROVAL-SYSTEM`** · **`LM-CLOUDFLARE-DNS-APPROVAL-SYSTEM`**. This mold **MUST NOT** invent dest paths or JSON keys.

## 2. Review order (sacred)

| Step | Dest MUST |
|------|-----------|
| **1. Fencing** | Run the closed dest fence list before any yes/no |
| **2. Match** | Human-facing display; no question; `approve` / `reject` fail closed with the same sentence |
| **3. Questions** | Only when no fence matched |

**MUST NOT** lead the match display with Type 0 / Type 1 / euid / F6 as the only words. Compose **`SK-WRITE-HUMAN-INTRO`** §2 and **`SK-OPERATOR-READABLE-ERROR`**.

## 3. File-based JSON subclass

When the instance is file-based JSON:

| Condition | Dest approve / reject / review |
|-----------|--------------------------------|
| **Incorrect JSON format** | **Fence** — required row |
| File-ownership | **MUST NOT** fence |
| Who submitted / dest Type 0 self-scope | **MUST NOT** fence |
| JSON username field ≠ dest LPU | **MUST NOT** fence |
| Dest-written `submit_by` / missing `submit_by` | **MUST NOT** fence |

Dest **MUST NOT** drop the JSON format row. Dest **MUST NOT** fence on filename subject token ≠ JSON username field. Full verify table lives on **`LM-FILE-BASED-JSON-APPROVAL`** §2.3 / §2.3a.

## 4. Protection Rule (Sacred)

Future agents **MUST NOT**:

1. Ask yes/no before fencing.  
2. Hide a fence match behind jargon-only text.  
3. Drop incorrect JSON format from a file-based JSON dest table.  
4. Add a dest fence this mold / specialized law does not name.

**Last Updated**: 2026-08-19  
**Owner**: {{OWNER}}  
**Version history:**  
- **1.1.0** (2026-08-19): Named dest leaves: sudoer / nginx-conf / cloudflare-dns approval-system.  
- **1.0.0** (2026-08-19): Superclass review order; file-based JSON must include JSON format fence.
