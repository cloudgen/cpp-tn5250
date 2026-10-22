---
name: webserver-management
id: LM-WEBSERVER-MANAGEMENT
kind: law-mold
description: >
  Portable law mold. Cite as LM-WEBSERVER-MANAGEMENT (path secondary).
---

**file**: docs/templates/requirements/template-webserver-management.md
**Status**: Active (Version 1.0.0 – Generalized template for webserver / reverse proxy management)
**Project**: {{APP_NAME}} – {{PLATFORM_NAME}} Platform Management CLI
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

# Template: Webserver Management (CIAO Defensive)

## 1. Purpose

This template defines the defensive practices for managing webserver configuration (nginx, Caddy, Traefik, or equivalent reverse proxy) in CIAO-Lite projects. It is especially relevant for self-host capable tools that recommend or support an **external webserver** for production deployments (virtual hosting, TLS termination, WebSocket upgrades, security headers, and multi-domain routing).

For pure Node.js platform client projects, this template provides guidance for generating safe example configurations and health-check endpoints. For hybrid or self-host installer projects, it governs safe editing, validation, and backup of reverse proxy configuration.

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
| **Three-layer privilege** | `docs/terminologies/three-layer-privilege.md` | `mention-only` | Service privilege |
| **System user** | `docs/terminologies/system-user.md` | `identity-runtime` | Service account |

**SSOT types used:** `identity-runtime` · `mention-only` · `meta-catalog` · `policy`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Core Rules / Requirements (Mandatory)

### 2.1 Always Backup Before Modification
- **Every** write operation that modifies webserver configuration files **MUST** first create a timestamped backup using the central backup helper (see `docs/templates/requirements/template-backup-strategy.md` or equivalent).
- Never perform in-place edits on live nginx / Caddy / Traefik configuration without a known-good rollback path.

### 2.2 Syntax Validation Before Reload / Restart
- After any configuration change, the CLI **MUST** validate syntax before suggesting or performing a reload/restart.
  - nginx: `nginx -t` (or equivalent for the webserver in use)
  - Caddy: `caddy validate`
- Only proceed with reload/restart if validation succeeds. On failure, show the exact error and the path to the backup.

### 2.3 Prefer External Webserver Mode for Production
- The project **SHOULD** treat external reverse proxy (nginx, Caddy, cloud load balancer, etc.) as the recommended production deployment model.
- The CLI should generate ready-to-use virtual host / server block examples with:
  - Correct `proxy_pass` / upstream targets for all platform services
  - WebSocket upgrade headers (`Upgrade`, `Connection`)
  - Recommended security headers (HSTS, CSP, X-Frame-Options, etc.)
  - Proper `client_max_body_size` and timeout settings for large file / realtime workloads
- Docker-internal webserver setups are acceptable for development or simple single-domain cases but must be clearly documented as non-recommended for multi-tenant or high-availability production use.

### 2.4 SSL / Certificate Handling
- Prefer external certificate management (Let's Encrypt / Certbot, Caddy automatic HTTPS, cloud provider certs).
- If the CLI manages certificates or private keys, files **MUST** be created with restrictive permissions (0600 or 0640).
- Always back up certificate files and configuration before any renewal or change operation.

### 2.5 Virtual Hosting & Multi-Domain Support
- Provide clear, copy-paste-ready examples for multiple domains / subdomains.
- Document the mapping between platform services (frontend, API, realtime / collaboration engine, etc.) and proxy locations or subdomains.
- Support both path-based routing (`/api`, `/realtime`) and subdomain-based routing when appropriate.

### 2.6 Why This Requirement Exists (Direct CIAO Alignment)
- **CIAO Principle 1 – Caution** (https://github.com/cloudgen/ciao): Webserver misconfiguration is one of the most common causes of self-host outages. Backup + validation prevents silent breakage.
- **CIAO Principle 3 – Anti-fragile** (https://github.com/cloudgen/ciao): External webserver mode survives container restarts, image updates, and allows professional operations teams to manage TLS, routing, and WAF rules independently.
- **CIAO Principle 4 / CIAO-Lite O · Principle 20 – Over-protect / Protect Against AI** (https://github.com/cloudgen/ciao): Explicit backup-before-edit, syntax validation gates, and high-quality example configuration generation defend both the tool and the user's production environment from common reverse-proxy pitfalls.

## 3. Design Principles (CIAO / CIAO-Lite)

- **Caution (CIAO Principle 1)**: Assume every webserver change can break production traffic. Never mutate live configuration without validation and rollback.
- **Intentional (CIAO Principle 2)**: Provide clear, well-commented, ready-to-deploy example configuration blocks instead of vague instructions.
- **Anti-fragile (CIAO Principle 3)**: The guidance works whether the user runs nginx, Caddy, Traefik, or a cloud-managed load balancer.
- **Over-protect (CIAO Principle 4 / CIAO-Lite O · Principle 20)**: Syntax validation + backup + restrictive permissions on sensitive files are non-negotiable defensive layers.

## 4. Protection Rule (Sacred)

**Future AI assistants, Grok, or maintainers MUST NOT**:

- Edit or generate webserver configuration without first calling the project's central backup helper.
- Skip syntax validation (`nginx -t`, equivalent) before suggesting a reload or restart.
- Hardcode concrete product site filenames or install roots — always use `{{NGINX_SITES_AVAILABLE}}`, `{{PROJECT_DIR}}`, `{{APP_NAME}}.conf`, or equivalent placeholders.
- Remove or weaken the recommendation for external reverse proxy in production deployments.
- Assume a Docker-internal webserver is the default or only supported model.
- Generate configuration that bypasses the centralized output system or backup strategy.

Violating any of the above is considered a **critical regression** against the project's defensive infrastructure layer.

---


## Design-time verification

| Gate | Artifact | Phase |
|------|----------|-------|
| Specialize → product suite or checklist | declare TP-IDs or checklist in specialized REQ | Design |
| RTM | `../tests/template-requirement-test-traceability.md` | Design |

When this mold has no executable TP family, mark **n/a** with reason in product `reviews/test-plan.md`.

**Last Updated**: 2026-06-09 (Generalized webserver / reverse proxy management template created; adapted from self-host installer patterns to current platform client + external nginx model)
**Owner**: Infrastructure & Reverse Proxy Layer
**Alignment**: Fully synchronized with `docs/requirements/index.md`, `template-docker-images.md`, `template-configuration-management.md`, `template-backup-strategy.md`, `AGENTS.md` (CIAO Protection Zones) and specialized requirements, and **CIAO Principles 1, 3, 4, 20 (v2.10.2)** (https://github.com/cloudgen/ciao).

---

**How to specialize this template**:

1. Copy to `docs/requirements/requirement-webserver-management.md` (or a Node-specific target name after specialization; not live until created).
2. Replace all `{{PLACEHOLDER}}` values with concrete paths, commands, and service names for your project.
3. Implement or extend the backup helper, config generation functions, and syntax validation wrappers.
4. Add any project-specific commands (e.g. `{{APP_NAME}} webserver generate`, `{{APP_NAME}} webserver validate`, `{{APP_NAME}} nginx reload`).
5. After specialization, update `docs/requirements/index.md` with a row for the new `requirement-*.md` only (never list this template path).
