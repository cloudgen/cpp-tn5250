---
name: external-ipv4
id: LM-EXTERNAL-IPV4
kind: law-mold
description: >
  Portable law mold for public/external IPv4 lookup, validation, override, and
  a vault-free display verb. Cite as LM-EXTERNAL-IPV4 (path secondary). No RQ-*.
---

**file**: template-external-ipv4.md  
**Mold-ID**: LM-EXTERNAL-IPV4  
**Status**: Active (Version 1.0.0)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered / Over-protect)

**Folder structure (policy):** [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

# Template: External / public IPv4 lookup

## 1. Purpose

Portable **pattern law** for obtaining a host’s **external IPv4** (public/WAN address) so Type 0 products can **display** it and **write** it into DNS or similar records without inventing a second lookup per verb.

**Specialize into:** `requirement-external-ipv4.md` (or product-chosen kebab). **Not** a second Active `requirement-domain-*` catalog — domain SSOT **consumes** this capability.

Agents load this mold when authoring. Product source cites the **live requirement**, never this file.

---

## Terminologies

| Term | Path | SSOT type | Role |
|------|------|-----------|------|
| **Project templates** | `docs/terminologies/project-templates.md` | `meta-catalog` | What law molds are |
| **Docs folder structure** | `docs/terminologies/docs-folder-structure.md` | `policy` | Mold vs product law vs tests |
| **No-hardcode policy** | `docs/terminologies/no-hardcode-policy.md` | `policy` | Placeholders in this mold |
| **Dual policies** | `docs/terminologies/dual-policies.md` | `policy` | Complete specialize-out |
| **Terminology policy for templates** | `docs/terminologies/terminology-policy-for-templates.md` | `policy` | Terminologies section rules |
| **SSOT-terminology policy for templates** | `docs/terminologies/ssot-terminology-policy-for-templates.md` | `policy` | SSOT type column |
| **External IPv4** | `docs/terminologies/external-ipv4.md` | `runtime-mode` | Address class + lookup word |
| **Domain surface** | `docs/terminologies/domain-surface.md` | `product-law` | Verbs that consume the address |
| **Domain requirements** | `docs/terminologies/domain-requirements.md` | `product-law` | Catalog owner — not this mold |
| **Temp-file-system** | `docs/terminologies/temp-file-system.md` | `runtime-mode` | Scratch for HTTPS body |
| **Least privilege** | `docs/terminologies/least-privilege.md` | `policy` | Documented egress only |
| **LLM escape** | `docs/terminologies/llm-escape.md` | `policy` | No improvised extra fetches |
| **SSOT catalog** | `docs/terminologies/ssot-catalog.md` | `meta-catalog` | Inventory of SSOTs |

**SSOT types used:** `meta-catalog` · `policy` · `runtime-mode` · `product-law`

**Policies:** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-no-hardcode.md` · `docs/policies/policy-least-privilege.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md`

**Missing terms:** none

---

## 2. Core rules (portable MUST)

**IP-M1. One lookup helper.** A single function family (e.g. `{{IP_LOOKUP_FN}}`) **MUST** resolve the public IPv4. Mutating and display verbs **MUST** call it — **MUST NOT** each open a private HTTPS path.

**IP-M2. Documented source.** Unless an override flag is set, lookup **MUST** be HTTPS `GET {{IP_LOOKUP_URL}}` and extract field `{{IP_JSON_FIELD}}` (default shape: JSON `ip`). The URL **MUST** be named in specialized Implementation Notes. Agents **MUST NOT** invent a second echo service.

**IP-M3. Override.** Flag `{{IP_OVERRIDE_FLAG}}` (typical `--ip`) **MUST** skip the network, validate the operand, and record source `override`.

**IP-M4. Validate IPv4.** Accept only dotted-quad IPv4. **MUST** reject: `127.0.0.0/8`, `0.0.0.0`, `255.255.255.255`, multicast `224.0.0.0/4`, link-local `169.254.0.0/16`. Specialized law **MAY** also reject RFC1918 if the product writes global DNS.

**IP-M5. Fail closed.** HTTP not 200, HTTP 429, missing field, or invalid address → stable code `{{IP_FAIL_CODE}}` (typical `ip_lookup_failed`). **MUST NOT** retry in a loop on 429.

**IP-M6. Display verb.** A Type 0 verb (typical `ip`) **MUST** print the same lookup (human + `--json`) **without** requiring product vault/credentials and **without** calling the domain API. JSON **MUST** include `public_ip` and `source` (`ipinfo` / provider name or `override`).

**IP-M7. No vault for the body.** Lookup response temps **MUST** use scratch / `{{EFFECTIVE_STORAGE_DIR}}` / `TMPDIR` (`LM-TEMP-FILE-SYSTEM` leaves). **MUST NOT** require the product vault directory.

**IP-M8. Empty argv.** Zero arguments **MUST NOT** perform the lookup (Type N help / product empty-argv law).

**IP-M9. IPv6 / AAAA.** **Out of scope** unless a later Active requirement adds them.

**IP-M10. Output.** All user messaging via the product `out_*` SSOT. Token/secret material **MUST NOT** appear on the lookup `curl` argv.

### Example variables (not product law)

| Name | Default pattern | Role |
|------|-----------------|------|
| `{{IP_LOOKUP_URL}}` | HTTPS echo JSON | Documented GET |
| `{{IP_JSON_FIELD}}` | `ip` | JSON field |
| `{{IP_OVERRIDE_FLAG}}` | `--ip` | Skip network |
| `{{IP_FAIL_CODE}}` | `ip_lookup_failed` | `out_die_code` |
| `{{IP_DISPLAY_VERB}}` | `ip` | Vault-free display |

### Example helper shape

```sh
{{IP_LOOKUP_FN}}() {
    if [ -n "${{{IP_OVERRIDE_VAR}}:-}" ]; then
        {{VALIDATE_IPV4}} "${{{IP_OVERRIDE_VAR}}}" || {{DIE_CODE}} {{IP_FAIL_CODE}} "invalid IPv4"
        {{PUBLIC_IP_VAR}}="${{{IP_OVERRIDE_VAR}}}"
        {{IP_SOURCE_VAR}}="override"
        return 0
    fi
    _body=$(mktemp "${EFFECTIVE_STORAGE_DIR}/.ip.XXXXXX") || {{DIE_CODE}} {{IP_FAIL_CODE}} "temp"
    # GET {{IP_LOOKUP_URL}} → extract {{IP_JSON_FIELD}}; validate; set source
}
```

Specialization replaces placeholders. Product source cites the live requirement only.

---

## 3. Design-time verification

| Default | Value |
|---------|--------|
| Proof mold | **`PM-EXTERNAL-IPV4-TEST-PLAN`** |
| Checklist | **`CL-EXTERNAL-IPV4`** |
| TP family | **`TP-<SUBJECT>-IP-*`** or product **`TP-CF-IP-*`** after specialize |
| Core cases | override without network; live path hits only the documented URL; reject loopback; 429 fail-closed; empty argv does not look up |

Gate: **`CL-LEAST-PRIVILEGE`** / **`CL-LLM-ESCAPE`** when reviewing unapproved extra egress.

---

## 4. CIAO alignment

- **Caution (1):** Fail closed on bad/private addresses and 429.  
- **Intentional (2):** One helper; display verb is not the DNS mutate verb.  
- **Anti-fragile (3):** `--ip` for offline tests.  
- **Over-protect (4/20):** No vault for lookup temps; no token on argv.  
- **SSOT of output (5):** `out_*` only.  
- **Type 0 (9):** Lookup and display stay invoking-user.  
- **Least privilege (10):** One documented URL.  
- **Temps (11):** Scratch, not vault.  
- **Dual policies (21):** Placeholders here; filled Implementation Notes on specialize.

---

## 5. Protection Rule (Sacred)

Future agents **MUST NOT**:

1. Invent a second public-IP URL without updating specialized Implementation Notes.  
2. Treat `hostname -I` / LAN / loopback as external IPv4.  
3. Require the product vault for the display verb.  
4. Call the domain API from the display verb.  
5. Retry 429 in a loop.  
6. Put secrets on lookup argv.  
7. Perform the lookup on empty argv.  
8. Specialize this mold as a second Active `requirement-domain-*` catalog.  
9. Cite this template from product source as behavioral authority.

---

## 6. How to specialize

1. Create `requirement-external-ipv4.md` via the specific-requirement skill.  
2. Fill Implementation Notes (`{{IP_LOOKUP_URL}}`, verb name, handler, TP-IDs).  
3. Domain SSOT **points here** for lookup; it does not duplicate the table.  
4. Register `docs/requirements/index.md`.  
5. Run **`CL-EXTERNAL-IPV4`**. Prove with **`PM-EXTERNAL-IPV4-TEST-PLAN`**.

**Last Updated**: 2026-08-17  
**Owner**: {{OWNER}}  
**Alignment**: term `external-ipv4` · **`PM-EXTERNAL-IPV4-TEST-PLAN`** · **`CL-EXTERNAL-IPV4`** · **`LM-TEMP-FILE-SYSTEM`** · [CIAO](https://github.com/cloudgen/ciao)
