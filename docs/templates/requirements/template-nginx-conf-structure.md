---
name: nginx-conf-structure
id: LM-NGINX-CONF-STRUCTURE
kind: law-mold
description: >
  Portable law mold for external Nginx conf artifact types, structural elements
  (server/location blocks, statements), and product location roles. Cite as
  LM-NGINX-CONF-STRUCTURE. Specialize to requirement-nginx-conf.md (not a second
  requirement-domain-* SSOT).
---

**file**: docs/templates/requirements/template-nginx-conf-structure.md  
**Status**: Active (Version 1.2.0)  
**Project**: {{APP_NAME}} – external Nginx conf structure  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile · Over-protect)

**Folder structure (policy):** law molds under `docs/templates/requirements/` per [`policy-docs-folder-structure`](../../policies/policy-docs-folder-structure.md).

**Dual structure:** This mold is **portable** law shape. Specialize to product **`requirement-nginx-conf.md`** (or `requirement-{{APP_NAME}}-nginx-conf.md`) with Area **webserver** — product writers, basenames already live, type-3 generate-or-not, elev model peer. Skills that stage confs are portable procedures with nested product tables.

# Template: Nginx conf structure

## 1. Purpose

Portable **law mold** for products that **generate or own** system Nginx site configuration: which **artifact types** exist, which **structural elements** appear inside them, which **location roles** a default HTTPS vhost must include, and **nginx-domain-root** path/ownership defaults (including frequent-change symlink layout).

This mold **does not** own:

| Concern | Owner |
|---------|--------|
| Domain verbs / cert flow / elev model | Domain SSOT (`requirement-domain-{{PRODUCT_SLUG}}`) |
| Type 0 CLI lifecycle | Shell / install REQs |
| Full Nginx package install sequence | Domain or platform peer |
| Glossary definitions | `docs/terminologies/nginx-conf*.md` |

**Specialize-out target:** `docs/requirements/requirement-nginx-conf.md` (or `requirement-{{APP_NAME}}-nginx-conf.md`) with Area **`webserver`** (or product-chosen non-`domain` area). **MUST NOT** create a second Active `requirement-domain-*`.

## Terminologies

| Term | Path | SSOT type | Role |
|------|------|-----------|------|
| **nginx-conf** | `docs/terminologies/nginx-conf.md` | `term` | Parent: artifacts + elements |
| **nginx-conf-shared-cloudflare** | `docs/terminologies/nginx-conf-shared-cloudflare.md` | `term` | Artifact type 1 |
| **nginx-conf-per-domain-https** | `docs/terminologies/nginx-conf-per-domain-https.md` | `term` | Artifact type 2; basename **`{{domain-name}}.conf`** |
| **nginx-conf-redirect** | `docs/terminologies/nginx-conf-redirect.md` | `term` | Artifact type 3 |
| **nginx-conf-server-block** | `docs/terminologies/nginx-conf-server-block.md` | `term` | Element |
| **nginx-conf-location-block** | `docs/terminologies/nginx-conf-location-block.md` | `term` | Element parent |
| **nginx-conf-location-block-root** | `docs/terminologies/nginx-conf-location-block-root.md` | `term` | Location role |
| **nginx-conf-location-block-acme** | `docs/terminologies/nginx-conf-location-block-acme.md` | `term` | Location role |
| **nginx-conf-location-block-cloudflare-check** | `docs/terminologies/nginx-conf-location-block-cloudflare-check.md` | `term` | Location role |
| **nginx-conf-statement** | `docs/terminologies/nginx-conf-statement.md` | `term` | Directive parent |
| **nginx-domain-root** | `docs/terminologies/nginx-domain-root.md` | `term` | Content path; default `/var/www/{{domain-name}}`; ownership ladder |
| **nginx-adm** | `docs/terminologies/user-nginx-adm.md` | `term` | Conf operator LPU |
| **Project templates** | `docs/terminologies/project-templates.md` | `meta-catalog` | Mold surface |
| **Docs folder structure** | `docs/terminologies/docs-folder-structure.md` | `policy` | Placement |

**SSOT types used:** `term` · `meta-catalog` · `policy`

---

## 2. Core Rules (Mandatory — portable)

### 2.1 Artifact subclasses

Specialization **MUST** state which of the three [nginx-conf](../../terminologies/nginx-conf.md) **artifact** types the product generates:

| Type id | Term | Product MUST generate? (fill) |
|---------|------|-------------------------------|
| `shared-cloudflare` | nginx-conf-shared-cloudflare | {{YES\|NO\|OPTIONAL}} |
| `per-domain-https` | nginx-conf-per-domain-https | {{YES\|NO\|OPTIONAL}} |
| `redirect` | nginx-conf-redirect | {{YES\|NO\|OPTIONAL}} |

Rules:

1. **MUST NOT** invent a fourth portable artifact type without updating the **nginx-conf** glossary parent.  
2. **MUST** document honesty when a type is **taxonomy-only** (host may have it; product does not write it).  
3. **MUST** keep artifact type separate from **structural elements** (blocks/statements).

### 2.2 Per-domain conf naming (type 2)

When the product emits type-2 HTTPS confs, specialization **MUST** fix the **basename convention**:

| Rule | Portable default |
|------|------------------|
| **Pattern** | **`{{domain-name}}.conf`** |
| **`{{domain-name}}`** | Primary domain / FQDN for that vhost (same token as `server_name` primary unless product law says otherwise) |
| **Cardinality** | **Exactly one** conf file per `{{domain-name}}` under the active layout |
| **Layouts** | `{{NGINX_CONF_ROOT}}/sites-available/{{domain-name}}.conf` **or** `{{NGINX_CONF_ROOT}}/conf.d/{{domain-name}}.conf` (document which) |
| **Greenfield** | Always `{{domain-name}}.conf` |
| **Legacy preserve** | If a single existing file already serves the domain under another basename, preserve-first tools may keep it until explicit rename — generators still target `{{domain-name}}.conf` |
| **Forbidden** | Parallel primaries (`{{domain-name}}-v2.conf`, etc.) for the same domain |

Glossary: **nginx-conf-per-domain-https** § Naming convention.  
Staging procedure: **`SK-CREATE-NGINX-PER-DOMAIN-CONF`**.  
Audit: **CL-NGINX-CONF-STRUCTURE**.

### 2.3 Document root path + ownership (type 2 content)

When the product creates or documents domain content trees for type-2 sites, specialization **MUST**:

| Topic | Portable default |
|-------|------------------|
| **Path (conf `root`)** | **`/var/www/{{domain-name}}`** unless specified (`{{NGINX_DOCROOT_BASE}}/{{domain-name}}`) |
| **Default ownership** | **service-lock** → **`www-data:www-data`** (or distro worker); **real** dir at public path |
| **Frequent update need** | **frequent-change** → real tree **`{{home}}/{{domain-name}}`** owned **`{{user}}:www-data`**; **soft link** **`/var/www/{{domain-name}}` → `{{home}}/{{domain-name}}`**; conf still `root`s public path |
| **Security freeze need** | **hard-lock** → **`root:root`** on real `/var/www/{{domain-name}}` |

Rules:

1. **MUST** cite glossary **[nginx-domain-root](../../terminologies/nginx-domain-root.md)** § Defaults + § Frequent-change layout.  
2. **MUST NOT** treat conf LPU (`nginx-adm`) as default content owner unless that leaf truly deploys content.  
3. **MUST** document override tables when paths leave `/var/www/…`.  
4. Blanket recursive chown helpers **MUST** be described honestly (service-lock bias); **MUST NOT** destroy frequent-change symlinks without intent.  
5. When **`{{user}}` is LPU**: **F4** records the soft link; **F5** includes **`/var/www/{{domain-name}}`** (and may include home subtree); **F3** is bare home only — terms `system-user-home` · `system-user-affected-folder` · skill **`SK-CREATE-LEAST-PRIVILEGE-USER-TERMINOLOGY`**.

### 2.4 Structural elements

When the product emits type-2 HTTPS confs, specialization **MUST**:

1. Use basename **`{{domain-name}}.conf`** (§2.2).  
2. Use at least one **[server block](../../terminologies/nginx-conf-server-block.md)** per domain conf.  
3. Default **`root /var/www/{{domain-name}};`** (or base form) unless override (§2.3).  
4. Document required **statements** (listen, server_name, root and/or proxy_pass, TLS paths as designed).  
5. Apply **ownership defaults** when product creates the directory (§2.3).

### 2.5 Location roles (when Cloudflare + static HTTPS template is claimed)

If product claims default Cloudflare-origin static HTTPS vhosts, each type-2 server block **MUST** include (or explicitly opt out with law):

| Role | Term | Typical match |
|------|------|---------------|
| Content | nginx-conf-location-block-root | `location /` |
| ACME | nginx-conf-location-block-acme | `/.well-known/acme-challenge/` |
| CF check | nginx-conf-location-block-cloudflare-check | `= /cloudflare-check` |

Rules:

1. **Root location** **MAY** apply origin gate (e.g. require CF header → 403).  
2. **ACME location** **MUST NOT** inherit a gate that blocks HTTP-01 validators when webroot renewal is claimed.  
3. **Cloudflare-check** **MUST** remain open for diagnostics when the product ships it; **MUST NOT** be treated as admin auth.  
4. Additional locations (proxy apps) **MAY** exist without new artifact subclasses.

### 2.6 Deploy hygiene (portable)

1. **MUST** backup existing site confs before rewrite when product rewrites conf.  
2. **MUST** run config test (`nginx -t` or equivalent) before reload/start that applies new conf.  
3. **MUST** fail closed on test failure.

### 2.7 Expandable profiles (portable samples)

When a product treats default nginx conf as **named expandable profiles**, specialization **MUST**:

1. Keep catalog copies under persistence (not filled host paths).  
2. Keep placeholders **`{{domain-name}}`**, **`{{cert-file-location}}`**, **`{{cert-key-location}}`** in those copies.  
3. Ship at least the three portable names when Cloudflare origin + redirect is claimed:

| Profile name | Artifact type | Job |
|--------------|---------------|-----|
| `cloudflared-protected-host` | per-domain-https | HTTPS origin host |
| `all-redirected` | redirect | HTTP → HTTPS |
| `excluded-non-cloudflared-ip` | per-domain-https | Deny non-Cloudflare origin |

**Portable sample (redirect):**

```nginx
server {
    listen 80;
    listen [::]:80;
    server_name {{domain-name}};
    location /.well-known/acme-challenge/ {
        root /var/www/letsencrypt;
        try_files $uri =404;
    }
    location / {
        return 301 https://{{domain-name}}$request_uri;
    }
}
```

**Portable sample (HTTPS origin + optional CF gate):**

```nginx
server {
    listen 443 ssl http2;
    listen [::]:443 ssl http2;
    server_name {{domain-name}};
    root /var/www/{{domain-name}};
    ssl_certificate {{cert-file-location}};
    ssl_certificate_key {{cert-key-location}};
    location = /cloudflare-check { default_type text/html; return 200 '...'; }
    location / {
        # excluded-non-cloudflared-ip only:
        # if ($http_cf_connecting_ip = "") { return 403; }
        try_files $uri $uri/ =404;
    }
    location /.well-known/acme-challenge/ {
        root /var/www/letsencrypt;
        try_files $uri =404;
    }
}
```

Shared type-1 `cloudflare-map.conf` (`set_real_ip_from` ranges) **MUST** stay a helper, not a fourth work-profile name, unless the glossary parent is updated.

### 2.8 Open posture / `--no-cloudflare`

If product documents open origin mode:

1. **MUST** state whether type-2 **body** changes (gate removed) or only messaging changes.  
2. **MUST NOT** claim open mode if the generator still emits the CF gate.

---

## 3. Specialization checklist

| # | Fill |
|---|------|
| 1 | Which artifact types are generated |
| 2 | Default path families (`{{NGINX_CONF_ROOT}}`, `{{NGINX_DOCROOT_BASE}}`) |
| 3 | Type 2 basename = **`{{domain-name}}.conf`** (confirm) |
| 4 | Default root **`/var/www/{{domain-name}}`**; ownership default **www-data:www-data**; frequent → real **`{{home}}/{{domain-name}}`** + symlink from `/var/www/…`; LPU F4/F5 if applicable |
| 5 | Location roles present / omitted |
| 6 | Redirect type 3: generated vs host-only |
| 7 | Link to domain SSOT for elev + cert sequence |
| 8 | Register `RQ-*` row in `docs/requirements/index.md` |
| 9 | Checklist **CL-NGINX-CONF-STRUCTURE** when auditing conf structure |

---

## 4. Protection Rule (mold)

Specializers **MUST NOT**:

1. Make this mold a second Active `requirement-domain-*`.  
2. Cite this mold from ship-unit as product law (only specialized `requirement-*.md`).  
3. Collapse location roles into artifact types.  
4. Freeze one host FQDN as portable law.  
5. Specialize type 2 without the **`{{domain-name}}.conf`** basename rule.

---

**Last Updated:** 2026-09-13  
**Owner:** {{OWNER}}  
**Alignment:** LM-NGINX-CONF-STRUCTURE · nginx-conf glossary family · peer domain SSOT  
