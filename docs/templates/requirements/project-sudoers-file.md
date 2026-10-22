# project-sudoers-file

**Definition:** A **project sudoers file** (also **project-sudoers-file**, **product sudoers draft**) is the **product-owned plain-text sudoers fragment** for a named CLI that Type 1 / an administrator may validate and install under **`/etc/{{username}}/`**. It is **not** the dest file by default: Type 0 products **emit/write a draft**; **Type 1 / root** copies it to `/etc/{{username}}/{{service}}` after `visudo -c`. **MUST NOT** write `/etc/passwd` or `/etc/sudoers.d`.

**Also called:** sudoers draft, product sudoers fragment, managed sudoers draft, `sudoers.fragment`

## Must not confuse

| Term | Difference |
|------|------------|
| **Project sudoers file** (this term) | Product draft artifact path + install/uninstall workflow for that product’s elev allowlist |
| **Sudoers fragment** ([`sudoers-fragment.md`](./sudoers-fragment.md)) | Portable **content + workflow** language for any fragment; project-sudoers-file is the **product path class** of that fragment |
| **Installed dest** | Host path `/etc/{{username}}/{{APP_NAME}}` after Type 1 / admin install — not Type 0 writable. Never `/etc/sudoers.d/` |
| **print-sudoers** | Type 0 command that **emits** the project-sudoers-file (stdout or draft path) |
| **print-sudoers-install-script** | Type 0 command that **emits an admin shell script** (under `/dev/shm` or temp) which an account with sudo runs to **install or remove** the project-sudoers-file on the host |
| **Elev Tables A/B/C** | Product **law** whitelist/denylist of elev; fragment Cmnds ⊆ Table A when specialized |
| **Trust tier** | production (global binary) vs test_local (user-rewritable local) — independent of file path |

## Primary sources

| Kind | Path |
|------|------|
| **Law mold** | `docs/templates/requirements/template-three-layer-privilege-model.md` (**`LM-THREE-LAYER-PRIVILEGE-MODEL`**) |
| **Product law (when specialized)** | Live `docs/requirements/requirement-three-layer-privilege-model.md` |
| **Procedure (agent create)** | `docs/skills/skill-create-sudoers-file.md` (**`SK-CREATE-SUDOERS-FILE`**) |
| **Operator path** | `docs/skills/skill-folder-archive-backup.md` (**`SK-FOLDER-ARCHIVE-BACKUP`**) |
| **Checklist** | `docs/templates/checklists/checklist-create-sudoers-security.md` (**`CL-CREATE-SUDOERS-SECURITY`**) |
| **Peer term** | [`sudoers-fragment.md`](./sudoers-fragment.md) |

## Portable path shapes

| Role | Portable default |
|------|------------------|
| **Project sudoers file (draft)** | `{{HOME}}/.config/{{APP_NAME}}/sudoers.fragment` or path arg to `print-sudoers` |
| **Installed dest** | `/etc/{{username}}/{{APP_NAME}}` (F6: `/etc/{{LPU_USER}}/sudoers`) |
| **Admin install script (generated)** | Prefer `/dev/shm/{{APP_NAME}}-{{TARGET_USER}}-sudoers-admin.sh`; else product temp/storage root |
| **Mode after admin install** | `0440`, owner `root:root` |

## Rules (portable)

1. **Never write `/etc/passwd` or `/etc/sudoers.d`**. Type 0 writes only the project-sudoers-file (draft) and optional **admin install script** under user-writable or volatile paths. Type 1 dest is `/etc/{{username}}/`. There is **no** blanket “do not write `/etc`”.  
2. **Type 1 / admin installs** dest with `visudo -c` then `install -m 0440` under `/etc/{{username}}/` (or the generated admin script’s `install` action).  
3. **Uninstall** of dest is Type 1 / admin (`rm` of `/etc/{{username}}/{{APP_NAME}}`); Type 0 may **generate** an uninstall script but must not elevate itself.  
4. **test_local** project-sudoers-files **MUST** carry TEST MODE / uninstall-soon guidance; prefer removing the installed fragment when leaving test elevation.  
5. **Replace workflow:** regenerate project-sudoers-file → generate admin script → admin runs `uninstall` then `install` (or `replace`) so stale host fragments (e.g. old local-tier drafts) do not linger.  
6. **Remove draft:** product Type 0 **`remove-project-sudoers`** deletes the project-sudoers-file only; installed host fragment requires admin script `uninstall`.  
7. **No secrets** in the project-sudoers-file or the generated admin script.  
8. Fragment Cmnds **⊆ Table A** when elev law exists; trust tier **S13** still applies (local ≠ production).  
9. Templates/skills use `{{APP_NAME}}` / `{{SUDOERS_DRAFT_PATH}}` / `{{SUDOERS_ADMIN_SCRIPT_PATH}}` — never freeze one product host path as universal law.

## Related

- `sudoers-fragment` · `three-layer-privilege` · `least-privilege` · `llm-escape` · `global-installation-location` · `local-installation-location` · `ship-unit`  
- Product verbs (when specialized): `print-sudoers`, `print-sudoers-install-script`, `remove-project-sudoers`

**Last Updated:** 2026-08-14  
**Dest:** `/etc/{{username}}/{{service}}` — not `/etc/sudoers.d/`  
**Portability:** portable harness term  
