---
name: defensive-practices
id: LM-DEFENSIVE-PRACTICES
kind: law-mold
description: >
  Portable law mold. Cite as LM-DEFENSIVE-PRACTICES (path secondary).
---

**file**: template-defensive-practices.md  
**Status**: Active (Version 2.1.0 – pointer: non-sudo owner probe before `sudo chmod`)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered / Over-protect)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

## 1. Purpose

This template is the **defensive practices router** for CIAO-Lite projects, aligned to [cloudgen/ciao](https://github.com/cloudgen/ciao) **v2.10.2**.

It ensures tools survive harsh environments (minimal containers, Alpine, non-interactive shells, multi-user systems) and prevents AI-assisted regressions. Full principle numbering lives in **`template-ciao-principles.md`**.

**CIAO-Lite (Principle 4) every change:** Caution · Intentional · Anti-fragile · **Over-protect** — Simplicity but Safety; surgical edits; no unfinished deliverables; no hardcodes in reusable layers.

## Terminologies

Related glossary entries (**disk-truth**). Templates **point**; they do not redefine terms or act as product law.
SSOT types follow `docs/policies/policy-ssot-terminology-for-templates.md`.
Binding rules: `docs/policies/policy-terminology-for-templates.md`.

| Term | Path | SSOT type | Role |
|------|------|-----------|------|
| **Project templates** | `docs/terminologies/project-templates.md` | `meta-catalog` | What law molds are; specialize-out target |
| **Docs folder structure** | `docs/terminologies/docs-folder-structure.md` | `policy` | Where this mold lives vs product law / tests |
| **No-hardcode policy** | `docs/terminologies/no-hardcode-policy.md` | `policy` | Placeholders only in portable molds |
| **Dual policies** | `docs/terminologies/dual-policies.md` | `policy` | No-placeholder × no-hardcode balance |
| **Terminology policy for templates** | `docs/terminologies/terminology-policy-for-templates.md` | `policy` | Mandatory Terminologies section rules |
| **SSOT-terminology policy for templates** | `docs/terminologies/ssot-terminology-policy-for-templates.md` | `policy` | SSOT type column on rows |
| **Error handling** | `docs/terminologies/error-handling.md` | `product-law` | Fail-loud patterns |
| **Stay-honest** | `docs/terminologies/stay-honest.md` | `policy` | No theater |

**SSOT types used:** `meta-catalog` · `policy` · `product-law`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Core Defensive Principles (Mandatory)

### 2.1 Safe Variable Defaults (Mandatory in Every Function)

Every function **must** begin with explicit safe defaults. Under **`set -u` / nounset**, **order matters**: default environment roots (e.g. `HOME`) **before** any path that expands them. Re-detect privilege when it steers install location; do not rely on a sibling function having set the flag.

```sh
# --- Safe Variable Defaults (HOME before path roots under set -u) ---
: "${HOME:=/tmp}"
: "${PROJECT_DIR:=${HOME}/my-project}"
: "${QUIET:=0}"
: "${JSON:=0}"
: "${FORCE:=0}"
# ... every other variable this function bare-expands
```

This pattern prevents "unbound variable" / `parameter not set` errors in strict POSIX shells (dash, ash, etc.). Full review gate: `docs/templates/checklists/checklist-set-u-variable-defaults.md` (defaults **and** third-party `source` under nounset — §8 silent-abort class). Agent harness: `docs/skills/skill-sh-script-coding.md` §2.3.1.

**Also mandatory under `set -u`:** do not `source` user rc or vendor inits without temporarily disabling nounset (safe helper). `source f 2>/dev/null` does **not** catch nounset process abort and can yield **zero product output** on `curl|bash` re-runs.

### 2.2 Single Source of Output (CIAO Principle 5)

- All **product** messaging **MUST** go through one Output module (`out_*` / language equivalent).
- Do not confuse product SSOT with **pipeline** data returns — see `template-output-requirements.md` (SSOT family + **SSOT REMARK** blocks).
- Respect `--quiet` and `--json` modes everywhere.

### 2.3 Backup by risk class (CIAO Principle 12)

- **Not** “backup every filesystem touch.” Classify data first (EPHEMERAL / REGENERABLE / CONFIGURATION / PERSISTENT_USER_DATA / CREDENTIAL / DESTRUCTIVE_UNINSTALL).
- Durable config and user data **must** have recovery before mutate; temps need cleanup (Principle **11**), not dated museum copies.
- See `template-backup-strategy.md`.

### 2.4 Storage & Project Isolation

- Always respect `--project-dir` (or equivalent flag).
- Never hardcode paths — use centralized resolver helpers.
- Enforce strict per-user isolation for configuration, cache, and data.
- Provide graceful fallbacks for missing directories or permission issues.

### 2.5 Non-Interactive Awareness

- Detect TTY with `[ -t 0 ] && [ -t 1 ]`
- Never hang in `curl | sh`, CI/CD, Docker build, or other non-interactive environments.
- Provide safe automatic defaults and behavior when running in scripted/automated contexts.

### 2.6 POSIX Compatibility

- Default shell must be `/bin/sh`
- Minimize Bashisms
- Test on Alpine (ash), dash, BusyBox, and Git Bash

### 2.6b File modes & umask (CIAO Principle 22)

- Prefer `chmod` / `install -m` per path and file type.
- Process `umask` **seldom**; if SET, always **RESET**.
- Atomic `mv` does not fix mode — set final mode on the published path.
- **Check before sudo:** probe **without sudo** first; skip `sudo` on match. **Example:** `sudo chmod` / `[ -O path ]`. See **`LM-SHELL-SCRIPT-CODING`** §8.3.
- See `template-file-modes-umask.md`.

### 2.6c Dual policies (CIAO Principle 21)

- **No-placeholder** in claimed project deliverables; **no-hardcode** in reusable templates/skills.
- Placeholders in reusable layers; real values in specialization / Config / product README·CHANGELOG.
- Never invent toy hosts or dummy secrets to “look complete.”

### 2.6d Privilege map (CIAO Principles 9–10)

- Classify commands Type **0 / 1 / 2** (Principle 9). Type 2 = dedicated system user — **not** “root-only.”
- Least-privilege user mechanics (Principle 10): dedicated user, restricted ownership, setup vs ops.
- See `template-least-privilege-user.md`, `template-cli-interface.md`.

### 2.7 Product-source documentation authority (defensive)

**Product source** (application scripts/modules — not files under `docs/`) **MUST** treat only **live specialized requirements** as behavioral authority in comments (`ALIGNMENT`, `See`, `Related`, “fully synchronized with”).

| Layer | Agents may load when implementing | Allowed as authority in **product source** comments? |
|-------|------------------------------------|------------------------------------------------------|
| Portable templates (`template-*.md`) | Yes (pattern / specialize) | **No** |
| Agent skills (`skill-*.md`) | Yes (how-to harness) | **No** |
| Live `docs/requirements/requirement-*.md` (on disk + listed in `docs/requirements/index.md`) | Yes | **Yes** |
| Terminologies / incidents | Context / lessons | Short incident IDs OK for lessons; behavior authority prefers requirements |

**Rules (mandatory):**

1. Do **not** write `template-*.md` or template tree paths into product source as implementation authority.  
2. Do **not** write `skill-*.md` into product source `ALIGNMENT` blocks as a substitute for requirements.  
3. Do **not** invent `requirement-*.md` paths — verify the file exists under `docs/requirements/` and is registered in `index.md`.  
4. If only a template exists for a topic: specialize a requirement first, **or** cite the closest **live** requirement — never paste the template path into source to look complete.  
5. Stale short names after renames (e.g. missing language/prefix) are the same class of failure as phantom paths.

**Why:** Templates and skills guide agents; they are not project law. False citations create phantom compliance and hide missing specialization (see project incidents on source citation when present).

### 2.8 Versioned requirements surface (defensive — no harness leak)

Default docs git policy tracks **`docs/requirements/**` only** and ignores agent harness trees. Files under the tracked surface (`index.md`, optional requirements `README.md`, `requirement-*.md`) **MUST NOT** re-export ignored docs as navigation.

| Allowed in tracked requirements files | Forbidden as navigation / Related / layer maps |
|---------------------------------------|------------------------------------------------|
| Peer `docs/requirements/requirement-*.md`, `index.md` | `docs/templates/**`, `docs/skills/**` |
| Product paths (`./{{APP_NAME}}`, root README when needed) | `docs/terminologies/**`, `docs/incidents/**`, checklists |
| Public CIAO / CIAO-Lite URLs | Full `docs/` tree inventories |

**Rules (mandatory):**

1. Do **not** put harness path inventories into specialized `docs/requirements/index.md` or requirements README.  
2. Do **not** list template/skill/terminology/incident paths in requirement Purpose “specialized from …”, Related artifacts, or Alignment as things to open.  
3. Agents **may load** templates/skills while authoring; provenance belongs in commit notes / local harness — not the published requirement body.  
4. Forbid-rules may say “do not cite templates/skills as product law” **without** listing concrete harness file paths.  
5. After specializing a template → requirement, run a path audit before claiming done.

**Why:** Publishing harness maps through the only versioned docs tree defeats gitignore intent and gives clones a false inventory (requirements-registry exposure class of incident).

## 3. Common Defensive Patterns

```sh
# Safe defaults at top of every function (HOME before path roots under set -u)
: "${HOME:=/tmp}"
: "${PROJECT_DIR:=${HOME}/my-project}"

# Always quote variables
if [ -d "${PROJECT_DIR}" ]; then ...

# Centralized error handling
command || out_die "Descriptive message with recovery hint"
```

## 4. Design Principles (CIAO / CIAO-Lite)

- **Caution (CIAO Principle 1)**: Assume nothing about the environment, storage availability, external services, or user privileges.
- **Intentional (CIAO Principle 2)**: Every defensive layer must have a clear, documented reason.
- **Anti-fragile (CIAO Principle 3)**: The system must survive missing tools, complex existing setups, non-interactive shells, and repeated modifications.
- **Over-protect (CIAO Principle 4 / CIAO-Lite O · Principle 20)**: Repetition of safe defaults, verbose comments, and Protection Zones is deliberate and required.

### 4.1 Why This Requirement Exists (Direct CIAO Alignment)
- **CIAO Principle 4 / CIAO-Lite O · Principle 20 – Over-protect / Protect Against AI** (https://github.com/cloudgen/ciao): Explicit protection zones, safe defaults, and verbose comments defend against accidental or AI-induced regressions.
- **CIAO Principle 3 – Anti-fragile** (https://github.com/cloudgen/ciao): The tool must survive harsh and unexpected environments through strong, consistent defensive patterns.
- **CIAO Principle 1 – Caution** (https://github.com/cloudgen/ciao): Assume the worst-case environment and prevent common classes of failure (unbound variables, path issues, output pollution, privilege mistakes).

## 5. Protection Rule (Sacred)

**Future AI assistants, Grok, or maintainers MUST NOT**:
- Remove safe variable default blocks (`: "${VAR:=default}"`) from functions
- Replace the centralized `out_text()` / `out_json()` system with raw `echo` / `printf`
- Delete or weaken Protection Zones and `!!! DO NOT MODIFY !!!` comments
- Hardcode paths instead of using centralized resolvers and `--project-dir`
- Introduce non-POSIX features that break compatibility with Alpine/dash/ash
- Simplify or remove per-project isolation and graceful fallbacks
- "Clean up" the script by removing defensive verbosity or repetition
- Require dated `.bak` for every temp as false “Principle 12 compliance,” or skip required config/user-data recovery
- Mandate sticky whole-script `umask 077` as security policy (violates Principle 22)
- Call Type 2 “root-only” (violates Principle 9)
- Cite `template-*.md` or `skill-*.md` as behavioral authority in **product source** comments (§2.7)
- Invent or leave stale `requirement-*.md` paths in product source that are not on disk
- Cite pre-2.10 principle numbers as if current (see `template-ciao-principles.md` §3)

**Verbosity, repetition, and strict defensive patterns are deliberate features — not technical debt.**

---


## Design-time verification

| TP family / ID | Proof mold | Planned suite |
|----------------|------------|---------------|
| **TP-U-*** set -u / Case C | `../tests/template-set-u-test-plan.md` | `tests/test_cli.sh` + curl suite |
| **TP-CLI-06,09** loud failures | `../tests/template-shell-cli-test-plan.md` | `tests/test_cli.sh` |

**RTM:** `../tests/template-requirement-test-traceability.md`

**Last Updated**: 2026-07-14  
**Owner**: Defensive Core Layer (Generalized Template)  
**Version history:**  
- **2.0.0** (2026-07-14): Router to CIAO v2.10.2 — P5/P9–12/P21–22; risk-class backup; dual policies; file modes.  
- **1.0.0**: Initial defensive practice set.  

**Alignment**: [cloudgen/ciao](https://github.com/cloudgen/ciao) **v2.10.2**; `template-ciao-principles.md`; peer templates for output, backup, privilege, file modes.

---

**How to use this template**:
1. Keep under `docs/templates/requirements/`; load with `template-ciao-principles.md` for numbering.  
2. Enforce safe defaults, Output SSOT, risk-class backup, modes, and privilege map in reviews.  
3. Keep the Protection Rule and "Safe Variable Defaults" requirement intact.  
4. After specialization, register new `requirement-*.md` in `docs/requirements/index.md` (requirement rows only).