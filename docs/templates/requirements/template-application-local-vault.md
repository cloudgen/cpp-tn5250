---
name: application-local-vault
id: LM-APPLICATION-LOCAL-VAULT
kind: law-mold
description: >
  Portable law mold: each application declares one local vault directory and
  MAY specify an absolute override. Cite as LM-APPLICATION-LOCAL-VAULT.
---

**file**: template-application-local-vault.md  
**Mold-ID**: LM-APPLICATION-LOCAL-VAULT  
**Status**: Active (Version 1.3.0)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered / Over-protect)

**Folder structure (policy):** [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md). Law mold under `docs/templates/requirements/`.

# Template: Application local vault (specify path)

## 1. Purpose

Portable **path + specify** law for an application’s **local vault** (durable secrets/config on disk). Every dest in this mold **is** [local vaults](../../terminologies/local-vaults.md) of the account that owns the tree. Type-2 dest is the LPU’s local vaults and a [global vault](../../terminologies/global-vault.md) from an ordinary login. **Not** product schema (token fields). **Not** SSH profile vaults. **Not** the GitHub API plane. **Not** scratch. **Not** [global backup](../../terminologies/global-backup.md). Type-0 default lives under the **local vaults root**; Type-2 dest uses the **same family** under `{{SYSTEM_USER_HOME}}`.

**Specialize into:** `requirement-application-local-vault.md`. Product-specific contents stay on a **peer** vault REQ (e.g. API token layout).

---

## Terminologies

| Term | Path | SSOT type | Role |
|------|------|-----------|------|
| **Project templates** | `docs/terminologies/project-templates.md` | `meta-catalog` | Law molds |
| **Docs folder structure** | `docs/terminologies/docs-folder-structure.md` | `policy` | Placement |
| **No-hardcode policy** | `docs/terminologies/no-hardcode-policy.md` | `policy` | Placeholders |
| **Dual policies** | `docs/terminologies/dual-policies.md` | `policy` | Specialize-out complete |
| **Terminology policy for templates** | `docs/terminologies/terminology-policy-for-templates.md` | `policy` | Section rules |
| **SSOT-terminology policy for templates** | `docs/terminologies/ssot-terminology-policy-for-templates.md` | `policy` | Types |
| **Local vaults** | `docs/terminologies/local-vaults.md` | `runtime-mode` | Umbrella class (every dest is this) |
| **Local vaults root** | `docs/terminologies/local-vaults-root.md` | `runtime-mode` | Parent `{{VAULTS_ROOT}}` |
| **Application local vault** | `docs/terminologies/application-local-vault.md` | `runtime-mode` | Path + specify word |
| **Global vault** | `docs/terminologies/global-vault.md` | `runtime-mode` | LPU dest from the ordinary login |
| **Global backup** | `docs/terminologies/global-backup.md` | `runtime-mode` | Fence — archive, not vault dest |
| **GitHub API vault** | `docs/terminologies/github-api-vault.md` | `identity-runtime` | Fence — 1:N tokens per login; not this dest |
| **SSH profile vault** | `docs/terminologies/ssh-profile-vault.md` | `identity-runtime` | Fence — different plane |
| **Temp-file-system** | `docs/terminologies/temp-file-system.md` | `runtime-mode` | Scratch ≠ vault |
| **SSOT catalog** | `docs/terminologies/ssot-catalog.md` | `meta-catalog` | Inventory |

**SSOT types used:** `meta-catalog` · `policy` · `runtime-mode` · `identity-runtime`

**Missing terms:** none

---

## 2. Core rules (portable MUST)

**AV-M1. Declare.** Implementation Notes **MUST** name the **default** local vault directory.

**AV-M2. Default family.** Type 0 (ordinary login / products without an LPU dest) unless notes say otherwise: `{{VAULTS_ROOT}}/{{APP_NAME}}/` with `{{VAULTS_ROOT}}` default `{{HOME}}/.local/vaults` (invoking `{{HOME}}`). Type-2 dedicated-account dest (when product law uses one) **MUST** be `{{SYSTEM_USER_HOME}}/.local/vaults/{{APP_NAME}}/` — same path family, **LPU F3 home** as `{{HOME}}`. **MUST NOT** hardcode `/etc/{{LPU_USER}}/vault/`. **MUST NOT** default Type-2 dest to the invoking user’s `{{HOME}}/.local/vaults/`.

**AV-M3. Specify.** Operator **MAY** set an absolute vault with:
- Flag `{{VAULT_DIR_FLAG}}` (typical `--vault-dir PATH`)
- Env `{{VAULT_DIR_ENV}}` (typical `{{APP}}_VAULT_DIR`)  
Precedence: **flag > env > default**. Specified path **MUST** be absolute.

**AV-M4. Fail closed.** Reject: empty; relative; under `/tmp` or `/dev/shm`; default resolve when `HOME` is unset/empty/`/tmp` (unless a **specified** absolute safe path is in use).

**AV-M5. Isolation.** Vault **MUST NOT** be `EFFECTIVE_STORAGE_DIR`, cache, an SSH profile vault (`{{VAULTS_ROOT}}/ssh/{{SSH_PROFILE_NAME}}/` or legacy `{{HOME}}/.ssh-{{SSH_PROFILE_NAME}}/`), or the GitHub API plane (`{{VAULTS_ROOT}}/github/`).

**AV-M6. Modes.** Vault dir **`0700`**; secret files **`0600`**.

**AV-M7. Uninstall.** Removing the managed binary **MUST NOT** delete the vault (default or specified).

**AV-M8. Contents.** Schema and verbs live on a **peer** product vault REQ. This mold owns **where** and **how specified**.

**AV-M9. Git surface.** Host-filled vault paths **MUST NOT** be committed as portable law.

**AV-M10. Type-2 dest.** When the product has an LPU dest:
- Production default **MUST** be `{{SYSTEM_USER_HOME}}/.local/vaults/{{APP_NAME}}/` (`0700`).
- `{{SYSTEM_USER_HOME}}` **MUST** come from the LPU F3 home (passwd), not a frozen `/etc/{{LPU_USER}}` string in core rules.
- Type 1 setup **MUST** `mkdir` `{{SYSTEM_USER_HOME}}/.local/vaults/` and the app child (`0700`).
- Specify (`{{VAULT_DIR_FLAG}}`) **MAY** point at the invoking user’s `{{VAULTS_ROOT}}/{{APP_NAME}}/` for Type-0 QA.
- No specify + no LPU → product fail-closed (typical `lpu_missing`).
- **MUST NOT** default production I/O to the invoking user’s tree.

**AV-M10a. Local vs global (relative).** Every dest in this mold **is** local vaults of the account whose `{{HOME}}` owns the tree. When an ordinary login stores a token or key **outside their account** by submitting it to the LPU dest, that dest **is** a **global vault** from the ordinary login. From the LPU it remains local vaults. **MUST NOT** invent `/etc/{{LPU_USER}}/vault/` as “the global vault.” **MUST NOT** treat global backup as the vault dest.

**AV-M11. Peer schema cardinality.** A product vault REQ that stores vendor API tokens **MUST** state its own slot key and token cardinality. It **MUST NOT** copy GitHub API vault 1:N-tokens-per-login unless that is the product. Cloudflare-style: **1 : 1** domain-id ↔ token.

### Example variables

| Name | Pattern | Role |
|------|---------|------|
| `{{VAULT_DIR_FLAG}}` | `--vault-dir` | Specify |
| `{{VAULT_DIR_ENV}}` | `{{APP_NAME}}_VAULT_DIR` style | Specify |
| `{{DEFAULT_VAULT_DIR}}` | `{{VAULTS_ROOT}}/{{APP_NAME}}` | Type-0 default / specify example |
| `{{TYPE2_VAULT_DIR}}` | `{{SYSTEM_USER_HOME}}/.local/vaults/{{APP_NAME}}` | Type-2 dest |

---

## 3. Design-time verification

| Default | Value |
|---------|--------|
| Proof | **`PM-APPLICATION-LOCAL-VAULT-TEST-PLAN`** |
| Checklist | **`CL-APPLICATION-LOCAL-VAULT`** |
| TP tokens | **AV-01** specify flag; **AV-02** env; **AV-03** `/tmp` reject; **AV-04** relative reject; **AV-05** help; **AV-06** specified wins when `HOME=/tmp`; **AV-07** no specify + no LPU fail-closed |

---

## 4. CIAO alignment

- **Caution (1):** Fail closed on `/tmp` vaults.  
- **Intentional (2):** One declared root; specify is explicit.  
- **Anti-fragile (3):** Tests can isolate via `--vault-dir`.  
- **P17 / P22:** Defensive storage; modes.  
- **Dual policies (21):** Placeholders here; filled notes on specialize.

---

## 5. Protection Rule (Sacred)

1. Put application secrets under scratch or `/tmp`.  
2. Use an SSH profile vault as the app vault.  
3. Accept a relative `--vault-dir`.  
4. Wipe the vault on `uninstall`.  
5. Duplicate path SSOT in a domain catalog.  
6. Cite this template from product source.  
7. Hardcode `/etc/{{LPU_USER}}/vault/` as Type-2 dest, or default Type-2 dest to the invoking user’s `{{HOME}}/.local/vaults/`.  
8. Store application API tokens under `{{VAULTS_ROOT}}/github/` or `{{VAULTS_ROOT}}/ssh/`.  
9. Invent a second dest so “global vault” is not the LPU’s local vaults, or treat global backup as the vault dest.

---

## 6. How to specialize

1. `requirement-application-local-vault.md` via specific-requirement skill.  
2. Fill default path, flag, env.  
3. Peer schema REQ **consumes** this file for location.  
4. Register index. Run **`CL-APPLICATION-LOCAL-VAULT`**.  
5. Skills: **`SK-SH-SCRIPT-CODING`** (scratch ≠ vault), **`SK-FILE-LEAKS-CHECK`**, **`SK-SSH-USER-PROFILE`** (other plane).

**Last Updated**: 2026-08-19 (1.3.0 local vaults class; Type-2 dest is LPU local vaults = global vault from ordinary login)  
**Owner**: {{OWNER}}  
**Alignment**: term `application-local-vault` · `local-vaults` · `global-vault` · `local-vaults-root` · `github-api-vault` · **`SK-SH-SCRIPT-CODING`** · **`SK-SSH-USER-PROFILE`**
