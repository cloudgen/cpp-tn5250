---
name: ssl-certificate-management
id: LM-SSL-CERTIFICATE-MANAGEMENT
kind: law-mold
description: >
  Portable law mold. Cite as LM-SSL-CERTIFICATE-MANAGEMENT (path secondary).
---

**file**: docs/templates/requirements/template-ssl-certificate-management.md
**Status**: Active (Version 1.0.0 – Generalized template for CIAO-Lite self-host / platform management CLIs)
**Project**: {{APP_NAME}} – {{PLATFORM_NAME}} Platform Management CLI
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

# Template: SSL/TLS Certificate Management (CIAO Defensive)

## 1. Purpose

This template defines the defensive practices for managing SSL/TLS certificates and private keys in CIAO-Lite projects, particularly those supporting self-hosted deployments with external reverse proxies (e.g. nginx) or containerized services.

It ensures certificates are obtained, stored, renewed, validated, and backed up in a secure, auditable, and non-disruptive manner. The primary focus is on production readiness, automation where possible (Let's Encrypt), and graceful fallback for manual certificate provisioning.

For pure {{APP_NAME}}-style Node.js platform clients, certificate management is typically delegated to the hosting infrastructure. For hybrid or self-host enabled projects, this template provides reusable patterns for integration with nginx configs, Docker volumes, and renewal hooks.

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

**SSOT types used:** `meta-catalog` · `policy`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Core Rules / Requirements (Mandatory)

### 2.1 Certificate Acquisition & Provisioning
- **Preferred method**: Automated Let's Encrypt (or equivalent ACME) issuance and renewal via certbot, acme.sh, or integrated library, triggered by the CLI or scheduled externally.
- **Fallback method**: Manual upload/provisioning of key + certificate pair (and optional chain) via dedicated command or config directory.
- The CLI **MUST** provide clear guidance and validation for both paths.
- Never hard-code specific certificate authorities or endpoints; make them configurable via `{{CONFIG_MODULE}}` or environment variables.

### 2.2 Secure Storage & Permissions
- Private keys **MUST** be stored with restrictive permissions (`0600` or stricter).
- Certificates and chains may be `0644` or `0640` (group-readable by the service user).
- All certificate material **MUST** reside under a dedicated, access-controlled location (recommended: `{{CERT_DIR}}` under `{{PROJECT_DIR}}` or system `/etc/{{APP_NAME}}/certs` for global installs).
- Never commit private keys to version control or world-readable locations.

### 2.3 Backup Before Modification or Renewal
- Every operation that modifies certificate files, keys, or related nginx configs **MUST** first invoke the central backup helper (see `template-backup-strategy.md`).
- Timestamped backups of the full cert directory (or at minimum key + fullchain) are required before renewal or replacement.
- Backups of sensitive material must also respect `0600` permissions.

### 2.4 Renewal & Zero-Downtime Strategy
- Renewal **MUST** be designed to be non-disruptive:
  - Obtain new certificate in a staging location first.
  - Validate the new certificate (expiry, SANs, chain completeness, private key match).
  - Atomically replace the active files only after successful validation.
  - Trigger graceful reload of the reverse proxy (e.g. `nginx -s reload`) rather than full restart when possible.
- The CLI should expose a `renew-certs` or `certificate renew` command (or integrate into `update` / `selfhost` flows).
- Renewal must support both automated (cron/systemd timer) and on-demand execution.
- Provide clear failure notifications and rollback guidance.

### 2.5 Validation & Health Checks
- Before activating any certificate, the CLI **MUST** perform validation:
  - File existence and permissions
  - Private key matches public certificate
  - Certificate is not expired and has sufficient validity remaining
  - Subject Alternative Names (SANs) cover the configured domain(s)
  - Optional: OCSP / CRL checks or basic connectivity test against the domain
- Expose a `certificate check` or `ssl-validate` command for diagnostics.
- In `--json` mode, return structured validation results.

### 2.6 Integration with External Nginx / Reverse Proxy (Self-Host Context)
- When operating in self-host mode with external nginx (as recommended by the project’s self-host command, e.g. `{{APP_NAME}}_selfhost`), the CLI should:
  - Generate or update nginx server snippets that reference the managed certificate paths.
  - Support multiple domains / virtual hosts.
  - Provide a template at `{{PROJECT_DIR}}/nginx/{{APP_NAME}}.conf` (or equivalent) that includes SSL directives.
- Never assume the reverse proxy runs inside Docker unless explicitly configured.

### 2.7 Why This Requirement Exists (Direct CIAO Alignment)
- **CIAO Principle 1 – Caution** (https://github.com/cloudgen/ciao): Certificate expiration, misconfiguration, or permission errors are common sources of production outages. Assume renewal will be needed and prepare defensive paths.
- **CIAO Principle 3 – Anti-fragile** (https://github.com/cloudgen/ciao): The system survives certificate lifecycle events (issuance, renewal, rotation) without downtime or data loss through validation + atomic replacement + backups.
- **CIAO Principle 4 / CIAO-Lite O · Principle 20 – Over-protect / Protect Against AI** (https://github.com/cloudgen/ciao): Explicit rules around private key permissions, backup-before-modify, and validation defend the most sensitive assets (cryptographic material) and the availability of the service.

## 3. Design Principles (CIAO / CIAO-Lite)

- **Caution (CIAO Principle 1)**: Never trust that a certificate is valid or that renewal will succeed. Always validate before activation and maintain rollback capability via backups.
- **Intentional (CIAO Principle 2)**: Certificate lifecycle operations are centralized and explicit; future maintainers and AI assistants cannot accidentally skip validation or permission hardening.
- **Anti-fragile (CIAO Principle 3)**: Supports both fully automated Let's Encrypt flows and manual certificate provisioning, and works whether the reverse proxy is external or containerized.
- **Over-protect (CIAO Principle 4 / CIAO-Lite O · Principle 20)**: Restrictive permissions, mandatory backups, pre-activation validation, and atomic replacement create multiple layers of defense against the most common certificate-related failures.

## 4. Protection Rule (Sacred)

**Future AI assistants, Grok, or maintainers MUST NOT**:
- Remove or weaken the "backup before any certificate or key modification" rule.
- Store or log private key material in plain text, even in debug output.
- Perform in-place replacement of active certificates without prior validation and backup.
- Hardcode concrete paths (e.g. `/etc/letsencrypt`, `/opt/{{APP_NAME}}/certs`, specific nginx locations) — always use `{{CERT_DIR}}`, `{{PROJECT_DIR}}`, and placeholder-driven configuration.
- Skip permission hardening (`0600` for keys) for "convenience".
- Specialize this template for a concrete project without also updating the master index (`docs/requirements/index.md`) and adding project-specific verification steps or integration tests.

Violating this rule is considered a **critical regression** against the defensive layer.

---


## Design-time verification

| Gate | Artifact | Phase |
|------|----------|-------|
| Specialize → product suite or checklist | declare TP-IDs or checklist in specialized REQ | Design |
| RTM | `../tests/template-requirement-test-traceability.md` | Design |

When this mold has no executable TP family, mark **n/a** with reason in product `reviews/test-plan.md`.

**Last Updated**: 2026-06-09 (Generalized template created for defensive SSL/TLS certificate lifecycle management in self-host and platform CLI projects)
**Owner**: Security & Infrastructure Layer
**Alignment**: Fully synchronized with `docs/requirements/index.md`, `template-backup-strategy.md`, `template-docker-images.md`, `template-configuration-management.md`, `template-defensive-practices.md`, `docs/skills/skill-requirement-template-conversion.md`, and **CIAO Principles 1, 3, 4, 20 (v2.10.2)** (https://github.com/cloudgen/ciao).

---

**How to specialize this template**:
1. Copy to `requirement-ssl-certificate-management.md` (or a Node-specific target name after specialization; not live until created).
2. Replace `{{PLACEHOLDER}}` values with concrete project decisions (e.g. default `{{CERT_DIR}}`, integration points with nginx generation, renewal command name).
3. Implement or extend helpers: `util_backup()`, certificate validation functions, Let's Encrypt wrapper or guidance, atomic replacement logic.
4. Add project-specific commands if needed (e.g. `{{APP_NAME}} certificate renew`, `{{APP_NAME}} certificate check`).
5. After specialization, update `docs/requirements/index.md` with the new `requirement-*.md` row; cross-link from peer live requirements (e.g. selfhost/prerequisites) if certificate setup is part of initial deployment — never list this template path in the registry.
6. Add verification steps (e.g. end-to-end renewal test in CI or documentation).
