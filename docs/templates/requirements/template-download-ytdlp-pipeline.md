---
name: download-ytdlp-pipeline
id: LM-DOWNLOAD-YTDLP-PIPELINE
kind: law-mold
description: >
  Portable law mold for yt-dlp download ops (engine, cookies, retries, extract boundary).
  Cite as LM-DOWNLOAD-YTDLP-PIPELINE. Specialize to requirement-download-ytdlp-pipeline.md
  (or product-specific download key).
---

**file**: docs/templates/requirements/template-download-ytdlp-pipeline.md  
**Status**: Active (Version 1.0.0 – Portable yt-dlp download pipeline for CIAO-Lite products)  
**Project**: {{APP_NAME}} – download engine ops  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered / Over-protect)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

# Template: Download pipeline — yt-dlp

## 1. Purpose

Portable **operational download SSOT** for products that fetch media with **yt-dlp** after domain extractors produce source URLs (and optional playback cookies).

This mold owns **engine identity, per-item download contract, cookie-header safety, resilience options, extract-only boundary, privilege/network**. It does **not** own:

- Site catalog / host allowlist → domain mold (`template-domain-url-cli` or product domain)  
- Argparse flag tables → CLI peer  
- Package dependency declaration SSOT → packaging peer (this mold states yt-dlp is required at runtime)

## Terminologies

Related glossary entries (**disk-truth**). Templates **point**; they do not redefine terms or act as product law.  
SSOT types follow `docs/policies/policy-ssot-terminology-for-templates.md`.  
Binding rules: `docs/policies/policy-terminology-for-templates.md`.

| Term | Path | SSOT type | Role |
|------|------|-----------|------|
| **Project templates** | `docs/terminologies/project-templates.md` | `meta-catalog` | What law molds are |
| **Docs folder structure** | `docs/terminologies/docs-folder-structure.md` | `policy` | Law vs tests placement |
| **No-hardcode policy** | `docs/terminologies/no-hardcode-policy.md` | `policy` | Placeholders in portable molds |
| **Dual policies** | `docs/terminologies/dual-policies.md` | `policy` | No-placeholder × no-hardcode |
| **Terminology policy for templates** | `docs/terminologies/terminology-policy-for-templates.md` | `policy` | Terminologies section rules |
| **SSOT-terminology policy for templates** | `docs/terminologies/ssot-terminology-policy-for-templates.md` | `policy` | SSOT type column |
| **Stay-honest** | `docs/terminologies/stay-honest.md` | `policy` | No false engine claims |

**SSOT types used:** `meta-catalog` · `policy`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md` · `docs/policies/policy-stay-honest.md` (when present)

---

## 2. Core Rules (Mandatory — portable)

### 2.1 Engine

1. **MUST** use **yt-dlp** (`yt_dlp.YoutubeDL` or documented equivalent entry) as the download engine for non-extract runs.  
2. **MUST NOT** replace yt-dlp with an undocumented custom HTTP streamer as the default download path without updating specialized law and packaging deps.  
3. **MUST** treat yt-dlp as a **pip dependency** unless specialization declares dual install surfaces (system binary + pip) honestly.

### 2.2 Per-item download contract

4. For each extracted item `(title, video_url, special_cookie?)`, **MUST** invoke download with a clear progress / identity log line.  
5. **MUST** set an output template that includes a **sanitized title/episode stem** (placeholder default: `"{{OUTTMPL}}"` e.g. `"{title}.%(ext)s"`).  
6. **MUST** set **Referer** (and other required site headers) appropriate to the source family when known.  
7. **MUST** pass a consistent **User-Agent** (aligned with extraction session when applicable) into yt-dlp HTTP headers.  
8. When `special_cookie` is present, **MUST** pass only the **documented cookie names** as a Cookie header string — do not dump the entire session jar blindly when that reintroduces multi-value name conflicts.

### 2.3 Cookie safety (sacred)

9. **MUST** name the allowed playback cookie keys in specialized Implementation Notes.  
10. **MUST** build cookie header strings without relying on multi-value CookieJar entries that collide under the same name when a single header string is required.  
11. **MUST NOT** log full cookie values at INFO (or quieter) in non-verbose mode; verbose/debug **MAY** log for diagnostics but **MUST NOT** write passwords/tokens unrelated to session cookies.  
12. Operator-supplied challenge cookies (e.g. Cloudflare `cf_clearance`) **MUST** be applied to the **extraction session** when product law says so — not invented as a permanent vaulted secret in the repo.

### 2.4 Resilience options

13. **SHOULD** enable concurrent fragment downloads when the engine supports it (`concurrent_fragment_downloads` specialized).  
14. **SHOULD** set non-zero retries for transient network failures (`retries` specialized).  
15. Verbose product flag **MUST** control yt-dlp verbose mode when wired.

### 2.5 Extract-only boundary

16. When extract-only mode is active, **MUST NOT** call the download pipeline.  
17. Download failures **MUST NOT** be reported as successful completions (error peer).

### 2.6 Privilege and network

18. **MUST** run as the invoking user (Type 0) — no sudo for downloads.  
19. Network egress is inherent; **MUST NOT** claim open proxy/TOR product features unless separately lawed.  
20. **MUST NOT** require Type 1 elevation for default download write paths.

### 2.7 Implementation Notes (this project) — fill when specializing

| Field | This project |
|-------|----------------|
| **Implementation module(s)** | `{{DOWNLOAD_MODULES}}` |
| **Engine** | `yt_dlp.YoutubeDL` |
| **outtmpl** | `{{OUTTMPL}}` |
| **concurrent_fragment_downloads** | `{{CONCURRENT_FRAGMENTS}}` |
| **retries** | `{{RETRIES}}` |
| **Referer rules** | `{{REFERER_RULES}}` |
| **Cookie header keys** | `{{COOKIE_KEYS}}` |
| **API / site notes** | `{{SITE_API_NOTES}}` |
| **Extract-only behavior** | skips this pipeline |
| **Domain peer key** | `{{DOMAIN_REQ_KEY}}` |
| **CLI peer key** | `{{CLI_REQ_KEY}}` |

### 2.8 Why this mold exists (CIAO)

- **SSOT**: One home for download options and cookie plumbing.  
- **Caution**: Cookie collisions and challenge blocks are designed around.  
- **Least privilege**: User-level download only.  
- **Traceability**: Failures attributable per title/item.

---

## 3. Design Principles (CIAO / CIAO-Lite)

- **Caution:** Cookie subset only; fail loudly on API/download errors.  
- **Intentional:** yt-dlp is the named engine.  
- **Anti-fragile:** Retries and concurrent fragments.  
- **Over-protect:** No elev; no silent success on download failure.

---

## 4. Protection Rule (Sacred)

**Future AI assistants, Grok, or maintainers MUST NOT**:

1. Drop cookie-collision safeguards while specialized cookie keys remain required.  
2. Replace yt-dlp silently without updating this specialized REQ and packaging deps.  
3. Write downloads under system directories that require root by default.  
4. Log passwords or permanent secrets.  
5. Download in extract-only mode.  
6. Expand cookie dump to entire jar without law update if that reintroduces name conflicts.  
7. Move full host catalog into this file when a domain peer is Active (pointer only).

**Violating this rule is a critical download regression.**

---

## 5. Acceptance criteria (when specialized)

| ID | Criterion |
|----|-----------|
| AC-1 | yt-dlp is the download engine |
| AC-2 | Cookie header limited to documented names |
| AC-3 | Referer / User-Agent applied per rules |
| AC-4 | Extract-only does not call download |
| AC-5 | No Type 1 elev for download |

---

## 6. Related molds

| Mold | Relationship |
|------|--------------|
| `template-domain-url-cli` | Domain catalog / extractors |
| `template-python-cli-interface` | Flags including extract |
| `template-python-error-handling` | Failure reporting |
| `template-python-runtime-prerequisites` | yt-dlp as pip dep |
| `template-python-coding-style` | Cookie/I/O conventions |

---

## 7. How to specialize

1. Copy to `docs/requirements/requirement-download-ytdlp-pipeline.md` (or product key).  
2. Fill Implementation Notes (modules, cookie keys, referer rules, numbers).  
3. Register in `docs/requirements/index.md`.  
4. Seed TP rows (cookie string, extract-only no YoutubeDL, referer selection).  
5. Product source cites the **requirement** key, not this template.

---

## Design-time verification

| Gate | Artifact | Phase |
|------|----------|-------|
| Cookie subset | specialized suite (e.g. TP-YTDLP-01) | Design + have |
| Extract-only isolation | specialized suite | Design + have |
| Referer / headers | specialized suite | Design + have |

**RTM:** `../tests/template-requirement-test-traceability.md` §4.

**Last Updated**: 2026-08-11  
**Owner**: {{OWNER}}  
**Alignment**: **CIAO** (https://github.com/cloudgen/ciao); CIAO-Lite (https://github.com/cloudgen/ciao-lite).
