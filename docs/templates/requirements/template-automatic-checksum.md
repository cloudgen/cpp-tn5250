---
name: automatic-checksum
id: LM-AUTOMATIC-CHECKSUM
kind: law-mold
description: >
  Portable law mold. Cite as LM-AUTOMATIC-CHECKSUM (path secondary).
---

**file**: template-automatic-checksum.md  
**Status**: Active (Version 1.1.1 – Shape A default; optional Shape B pin)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered / Over-protect)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

## 1. Purpose

This template defines **automatic companion-digest integrity** for online install / self-update: the program **downloads** a digest sidecar next to the install artifact, verifies the download, and reports the process **transparently** (companion **link**, expected **value**, verification **result**).

It is the reusable pattern behind “checksum without the operator pasting a hash.”

**Default specialization: Shape A** — automatic companion only, digests as **function-local** variables, **no** public process-env pin.  
An optional env pin (**Shape B**) is an **opt-in** secondary shape for CI/out-of-band freeze only — never primary UX, never `help` / `about`.

**Specialize into:** a project `requirement-*-automatic-checksum.md` (e.g. `requirement-shell-automatic-checksum.md`) with filled Implementation Notes. Prefer language prefix when the law is shell-specific. Verify basename on disk before inventing paths; register in `docs/requirements/index.md` (requirement row only).

**Shared language (terminology):**

| Term | File |
|------|------|
| **Automatic checksum mechanism** | `docs/terminologies/automatic-checksum-mechanism.md` |
| Online install script | `docs/terminologies/online-install-script.md` |
| Script URL (install channel) | `docs/terminologies/script-url.md` |
| Self-management | `docs/terminologies/self-management.md` |

**Related templates (do not duplicate ownership):**

| Topic | Template |
|-------|----------|
| Full online install / one-liner | `template-online-install.md` |
| Self-management lifecycle | `template-self-management.md` |
| Output / human messaging (P5 SSOT) | `template-output-requirements.md` |
| Idempotency (already-good skips download) | `template-idempotency.md` |
| CLI help/about surface (no pin listing) | `template-cli-interface.md` |
| Temps / atomic publish | `template-defensive-practices.md` · Principle **11** (temps) · **22** (modes) |
| CIAO principle index | `template-ciao-principles.md` |

---

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
| **Automatic checksum mechanism** | `docs/terminologies/automatic-checksum-mechanism.md` | `install-channel` | Companion digest integrity |
| **Companion digest file** | `docs/terminologies/companion-digest-file.md` | `install-channel` | Sidecar hash artifact |
| **Script URL** | `docs/terminologies/script-url.md` | `install-channel` | Channel URL SSOT |
| **Online install script** | `docs/terminologies/online-install-script.md` | `install-channel` | Pipe / one-liner distribution |

**SSOT types used:** `install-channel` · `meta-catalog` · `policy`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Core Concepts

| Concept | Meaning |
|---------|---------|
| **Install artifact URL** | `{{SCRIPT_URL}}` / `{{INSTALL_SCRIPT_URL}}` — body of the script or binary being installed |
| **Companion digest URL** | Derived sidecar, default **`{{SCRIPT_URL}}.sha256`** (same channel + `.sha256` suffix, or project-equivalent next to the artifact) |
| **Automatic mode (default)** | Program fetches companion, verifies download; digests held as **function-local** variables — not a public CLI setting |
| **Strict pin mode (optional shape)** | Operator/CI supplies expected digest via process env (e.g. `{{CHECKSUM_ENV}}`) only on install/download path; **not** required for primary one-liner; **not** in help/about |
| **Transparency** | Human (and JSON when designed) surfaces show **where** the digest came from, **what** was expected, and **whether** verification passed |
| **Same-channel trust** | Artifact + sidecar on one unauthenticated channel prove **byte consistency**, not independent authenticity of the host |

**Must not confuse:**

| Concept | Not the same as |
|---------|-----------------|
| Companion sidecar file | Embedding the hash of file *F* **inside** file *F* (circular / forbidden) |
| Automatic fetch (internal) | Requiring the user to `export CHECKSUM=…` for every install |
| Optional env pin | Primary UX or a `help` / `about` Environment line |
| SHA-256 match | Cryptographic signature / cosign / package-manager authenticity |
| Missing sidecar warn+continue | “Always cryptographically verified” |

---

## 3. Specialization shapes (pick one — **Shape A is the default**)

A product **MUST** pick **exactly one** integrity shape for the ship unit and document it in Implementation Notes.

| Shape | Default? | Automatic companion | Env / process pin | When to use |
|-------|----------|---------------------|-------------------|-------------|
| **A — Automatic only (internal)** | **Yes — default** | **Required** | **None** — digests and match flags are **locals** only (`expected`, `actual`, `companion_url`, return codes). No `: "${CHECKSUM:=}"` / public pin env. | **Prefer for all new specializations** and Type 0 CLIs that need no operator integrity knobs |
| **B — Automatic primary + optional pin** | **No — opt-in only** | **Required** when pin unset | Optional `{{CHECKSUM_ENV}}` when **set** → strict pin path; still **not** help/about; still not primary README story | **Only** when the product has a concrete CI/out-of-band freeze need documented in Implementation Notes |

**Default rule:** Specialize as **Shape A** unless the project **explicitly** requires Shape B and records why (owner + freeze use case). Do **not** add an env pin “just in case” or to mirror another product.

**Rules:**

1. Shape A and Shape B both **MUST** implement automatic companion fetch + transparency.  
2. Shape A **MUST NOT** invent a public pin env “for completeness.”  
3. Shape B **MUST** demote pin: empty default, install-path only, no help/about listing; **MUST** state freeze/CI rationale in Implementation Notes.  
4. Agents **MUST NOT** upgrade Shape A → Shape B without explicit product need.  
5. **Review / coverage:** when online install exists, specialized `requirement-*-automatic-checksum` **SHOULD** exist (see `skill-requirement-review.md` Step 1b) — default the new requirement to **Shape A**.

---

## 4. Core Rules (Mandatory when this pattern is claimed)

### 4.1 Automatic path is the default

1. Install / self-update download paths **MUST** attempt automatic companion-digest verification (Shape A always; Shape B when pin env is empty).  
2. Operators **MUST NOT** be required to set a pin for the documented primary online install one-liner to get automatic integrity.  
3. Publisher **MUST** ship companion digest next to the artifact on the release channel (e.g. `{{APP_NAME}}.sha256` beside `{{APP_NAME}}`).  
4. After every published artifact change, regenerate the companion so the channel stays consistent (commit / release hygiene).  
5. Self-update **MUST** reuse the **same** download+verify orchestrator as first install (no parallel unverified curl-to-final-path).

### 4.2 Transparency (sacred emphasis)

When automatic verification runs in **human / normal** mode, the program **MUST** make the integrity step **observable**, not silent magic:

| Element | Requirement |
|---------|-------------|
| **Link** | Show the **companion digest URL** being fetched (full effective URL) |
| **Value** | When the sidecar is obtained, show the **expected digest** (normalized hex used for compare) |
| **Result** | Clear **outcome**: match / mismatch / missing sidecar (**SHOULD** show actual digest on match or mismatch) |

**Normative detail:**

1. **Before or during** companion fetch: info that names the companion URL.  
2. **On successful companion fetch:** show expected; **SHOULD** show actual SHA-256 of the download.  
3. **On match:** success-level message that verification **passed**.  
4. **On mismatch:** fail **loud** via output SSOT; **MUST** abort install; **SHOULD** show expected vs actual.  
5. **On missing sidecar:** project-defined **warn+continue** **or** fail closed — result **must** be explicit (never silent skip).  
6. **Quiet:** may suppress info/success; **MUST** still surface integrity errors.  
7. **JSON:** mismatch / hard fail via structured error (`checksum_mismatch` or equivalent); **no** fake success.

### 4.3 Download + verify order

**Shape A (default):**

```text
1. Resolve install channel {{SCRIPT_URL}}
2. Download artifact to mktemp path
3. Fetch {{SCRIPT_URL}}.sha256 with transparent link/value/result (locals only)
4. Match or (missing + documented continue) → atomic install (chmod/mode per P22 when publishing)
5. Mismatch → cleanup temp; non-zero exit; no corrupt final binary
```

**Shape B (opt-in only):** same as Shape A, with step 3a: if pin env non-empty → verify against pin (strict) instead of or before companion path; abort on pin mismatch.

### 4.4 Implementation preference (locals — default Shape A)

| Prefer (default) | Avoid |
|------------------|--------|
| Function-**local** `expected`, `actual`, `companion_url`, `sha_file`, match/return codes | Env pin (`CHECKSUM` / `{{CHECKSUM_ENV}}`) without Shape B rationale |
| Portable digest helper with **SSOT REMARK** (return-via-stdout — not product UI) | Bare `echo` digests as user banners |
| Shared install orchestrator for install + self-update | Second download path that skips verify |
| Shape A unless freeze need is documented | Copying Shape B from another product by habit |

Digest helper output is **SSOT of pipeline** (Principle **5** family) — capture with `$(…)`; do not treat as product messaging (`template-output-requirements.md`).

### 4.5 Forbidden patterns

| Forbidden | Why |
|-----------|-----|
| Embed expected digest of the installable file **inside** that same file and claim self-verify | Circular; useless after edit |
| Primary product docs that force `export CHECKSUM=$(curl same-origin.sha256)` as the **main** install story when automatic mode exists | Same-channel theater; hides automatic path |
| Hide automatic mode and only document external pin | Misleads (“checksum is external-only”) |
| Silent skip when companion is missing | Breaks transparency |
| Claim “cryptographically authenticated channel” from same-host SHA-256 alone | Overclaim |
| Remove automatic companion fetch while still claiming automatic integrity | Hollow claim |
| List pin env in **help** / **about** | Public surface for an internal/advanced variable |

### 4.6 Optional strict pin (Shape B only — not default)

**Skip this entire subsection for Shape A (default).**

When Shape B is explicitly chosen:

- If `{{CHECKSUM_ENV}}` (or equivalent) is **set** in the process environment, install/download verifies against that pin; mismatch aborts.  
- Treat the name as **runtime install variable**, not a public CLI setting (`help` / `about` **MUST NOT** list name or value).  
- Pin lives **outside** the payload (env / CI / out-of-band).  
- Same-origin “curl sidecar into pin then install” is **not** stronger than automatic mode.  
- True out-of-band pins remain valid advanced use — Advanced docs only if needed.

### 4.7 Algorithm and tooling

- Default algorithm: **SHA-256** (or document the real algorithm if different).  
- Prefer portable helpers (`sha256sum` / `shasum -a 256` / `openssl dgst`, or language equivalent).  
- Normalize sidecar input (first field of line, or strip whitespace) before compare for bare-hex or `hash  filename` lines.

---

## 5. Product documentation rules (when specialized)

When a project adopts this template as a live requirement:

1. Product root **`README.md`** **MUST** lead integrity with **automatic** companion verification (algorithm, no pin required for primary story, outcomes).  
2. Product README **MUST** document transparency (link / value / result — or quiet/json differences).  
3. Product README **MUST NOT** push env-first external pin as the **primary** newcomer install integrity method when automatic mode is implemented.  
4. **Default Shape A:** README/SECURITY describe automatic companion only; do **not** invent Advanced pin docs.  
5. Shape B pin (opt-in only): Advanced only — never Quick Installation gate; never help/about Environment line; state freeze/CI rationale.  
6. Agents writing README / SECURITY load specialized requirement + `skill-write-readme.md` / `skill-write-security.md` when on disk.  
7. Product **`SECURITY.md`** (when present) **MUST** state honest **trust bounds** (byte consistency ≠ independent authenticity; automatic primary; pin only if Shape B).

**Git-surface:** specialized requirement bodies cite peer **requirements** + product paths + public CIAO URLs — not harness path inventories.

---

## 6. Specialization sketch (Implementation Notes)

When specializing, fill at least:

| Item | Example content |
|------|-----------------|
| **Shape** | **A (default)** automatic only — or B only with freeze rationale |
| **Ship unit** | `./{{APP_NAME}}` |
| **Channel SSOT** | `SCRIPT_URL` composition / default |
| **Companion URL** | `${SCRIPT_URL}.sha256` |
| **In-repo publisher file** | `{{APP_NAME}}.sha256` |
| **Orchestrator function(s)** | e.g. `perform_self_install` / `inst_perform_install*` |
| **Digest helper** | e.g. `util_sha256_file` (pipeline SSOT remark; locals for expected/actual) |
| **Missing-sidecar policy** | warn+continue **or** fail closed |
| **Pin env name** | **Omit for Shape A.** Shape B only: e.g. `CHECKSUM` — empty default; not help/about; why freeze |
| **Quiet / JSON integrity errors** | codes such as `checksum_mismatch` |

---

## 7. Why This Pattern Exists (Direct CIAO Alignment)

- **CIAO Principle 1 – Caution** (https://github.com/cloudgen/ciao): Network bytes are untrusted; mismatch aborts.  
- **CIAO Principle 2 – Intentional** (https://github.com/cloudgen/ciao): Shape A (default automatic/locals) vs opt-in Shape B pin are deliberate; transparency makes intent visible.  
- **CIAO Principle 3 – Anti-fragile** (https://github.com/cloudgen/ciao): Missing companion policy explicit; portable digest tools; whitespace-tolerant parse.  
- **CIAO Principle 4 / CIAO-Lite O · Principle 20** (https://github.com/cloudgen/ciao): Do not strip automatic verify or transparency for “simplicity.”  
- **CIAO Principle 5 – Single Source of Output** (https://github.com/cloudgen/ciao): Link/value/result via output SSOT; digest helper is pipeline data with SSOT remarks.  
- **CIAO Principle 11 – Safe temps** (https://github.com/cloudgen/ciao): Companion and artifact temps cleaned; no fixed predictable names.  
- **CIAO Principle 21 – Dual policies** (https://github.com/cloudgen/ciao): Template stays portable (`{{PLACEHOLDER}}`); specialized requirements fill real channel/companion facts.

---

## 8. Design Principles (CIAO / CIAO-Lite)

- **Caution:** Fail closed on mismatch; never install known-bad bytes.  
- **Intentional:** Shape A vs B recorded; messages distinguish match / missing / mismatch.  
- **Anti-fragile:** Curl and wget paths; multiple digest tools; best-effort missing-sidecar when chosen.  
- **Over-protect:** Shared orchestrator; Protection Zone on verify; no second unverified download path.  
- **Output SSOT:** Product integrity messages through central emitters.  
- **No-hardcode (template):** Placeholders here; real URLs only in specialized notes / product README (excluded from no-hardcode).

---

## 9. Protection Rule (Sacred)

**Future AI assistants, Grok, or maintainers MUST NOT**:

1. Remove automatic companion-digest fetch while automatic integrity remains claimed.  
2. Embed the expected digest of the installable artifact **inside** that artifact as “verification.”  
3. Make external env pin the **only** integrity path when automatic mode exists.  
4. Default new specializations to Shape B, or add env pin without freeze rationale — **Shape A is the default**.  
5. **List or print** pin env name/value in **`help` or `about`**.  
6. Document same-origin pin-from-sidecar as higher assurance than automatic companion verify.  
7. Drop transparency (hide companion URL, expected value, and outcome) from the human automatic path without explicit redesign.  
8. Claim always-verified when missing-sidecar continues with only a warning.  
9. Put secrets or private tokens into digest URLs or docs.  
10. Paste this template path into product source as behavioral authority — specialize and cite the live `requirement-*-automatic-checksum.md`.

**Violating this rule is a critical integrity / trust regression.**

---

## 10. Verification (minimum)

| Check | Intent |
|-------|--------|
| Install with pin unset + published sidecar | Fetches companion; shows link/value/result; match → install |
| Sidecar digest ≠ artifact | Abort; no final corrupt binary; mismatch visible |
| Sidecar missing | Documented warn+continue **or** fail; never silent no-op |
| Shape B only: pin set to wrong hex | Abort on strict path |
| Quiet / JSON | Errors still usable; no success on mismatch |
| Product README | Automatic mode primary; no env-first pin as newcomer path |
| `help` / `about` | No pin env name/value listed |
| Self-update | Reuses same verify orchestrator |

---

## 11. Dual policy (this template)

| Policy | How it applies here |
|--------|---------------------|
| **No-hardcode** | Use `{{APP_NAME}}`, `{{SCRIPT_URL}}`, `{{INSTALL_SCRIPT_URL}}`, `{{CHECKSUM_ENV}}`, path patterns — not frozen product hosts/orgs/digests as universal law |
| **No-placeholder (after specialize)** | Implementation Notes **filled** (shape, companion path, function names, channel) when claiming done |

Allowed philosophy links: https://github.com/cloudgen/ciao · https://github.com/cloudgen/ciao-lite  

---

## 12. How to use this template

1. Confirm product has online install / self-update download (else N/A).  
2. **Default to Shape A** (automatic only, locals). Adopt Shape B **only** with documented freeze/CI need.  
3. Specialize into `requirement-*-automatic-checksum.md` with **Shape: A** (or B + rationale); register in `docs/requirements/index.md` (requirement row only).  
4. Implement shared install orchestrator + portable digest helper + transparency (locals for digests).  
5. Ship `{{APP_NAME}}.sha256` on the release channel next to the artifact.  
6. Align product README / SECURITY with automatic-primary honesty (`skill-write-readme` / `skill-write-security` when on disk).  
7. On **requirement review**, if install exists but no specialized automatic-checksum requirement → **gap finding**; recommend **Shape A** by default (`skill-requirement-review.md` Step 1b).  
8. Product source cites the **live requirement**, never this template path.

---


## Design-time verification

| TP family / ID | Proof mold | Planned suite |
|----------------|------------|---------------|
| **TP-CSUM-01..05** companion + pin + hide | `../tests/template-checksum-test-plan.md` | CLI + lifecycle |
| **TP-LC-06** transparency on force reinstall | `../tests/template-install-lifecycle-test-plan.md` | lifecycle |

**RTM:** `../tests/template-requirement-test-traceability.md`


**Last Updated**: 2026-07-14  
**Owner**: Install Integrity Layer (Generalized Template)  
**Version history:**  
- **1.1.1** (2026-07-14): **Shape A is the default** specialization; Shape B opt-in only with freeze rationale; agents must not add env pin by habit.  
- **1.1.0** (2026-07-14): Peer-template alignment; Shape A vs B; CIAO v2.10.2; pipeline SSOT; requirement-review coverage pointer.  
- **1.0.2** (2026-07-13): Product docs rule for **`SECURITY.md`** trust bounds.  
- **1.0.1** (2026-07-13): Optional pin is runtime install variable only; **MUST NOT** appear in `help` / `about`.  
- **1.0.0** (2026-07-13): Initial template — automatic companion digest, transparency, secondary optional pin, README primary-path rules.  

**Alignment**: `docs/terminologies/automatic-checksum-mechanism.md`; peer templates in §1; [cloudgen/ciao](https://github.com/cloudgen/ciao) **v2.10.2** Principles **1, 2, 3, 4, 5, 11, 20, 21**; CIAO-Lite (https://github.com/cloudgen/ciao-lite).
