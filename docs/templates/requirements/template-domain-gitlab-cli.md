---
name: domain-gitlab-cli
id: LM-DOMAIN-GITLAB-CLI
kind: law-mold
description: >
  Portable law mold for a GitLab Omnibus operator CLI (list users, reset
  password from a numbered list, gitlab-ctl status, gitlab-adm LPU).
  Cite as LM-DOMAIN-GITLAB-CLI (path secondary). Placeholders only.
---

**file**: template-domain-gitlab-cli.md
**Mold-ID**: LM-DOMAIN-GITLAB-CLI
**Status**: Active (Version 1.0.0)
**Project**: Any CIAO-Lite Project (reusable template)
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered / Over-protect)

**Folder structure (policy):** [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

## 1. Purpose

Portable pattern for a **GitLab Omnibus operator** domain on a Type 0 POSIX CLI: list users, reset a user password (numbered list first), `gitlab-ctl` status, optional `gitlab-adm` least-privilege. **MUST NOT** own external Nginx / Certbot / Let's Encrypt.

**Specialize into:** `requirement-domain-{{SUBJECT}}.md` (example stem `gitlab-cli`). Product source cites the **requirement**, never this template.

## Terminologies

| Term | Path | SSOT type | Role |
|------|------|-----------|------|
| **gitlab** | `docs/terminologies/gitlab.md` | `product-law` | Platform product |
| **gitlab-ctl** | `docs/terminologies/gitlab-ctl.md` | `product-law` | Omnibus control CLI |
| **user-gitlab-adm** | `docs/terminologies/user-gitlab-adm.md` | `product-law` | Config operator LPU |
| **Docs folder structure** | `docs/terminologies/docs-folder-structure.md` | `policy` | Where this mold lives |
| **No-hardcode policy** | `docs/terminologies/no-hardcode-policy.md` | `policy` | Placeholders only |

## 2. Probe helpers (sample — not product law)

```sh
# WARNING — illustration. Specialize names/paths in the live requirement.
{{prefix}}_find_gitlab_rails() {
    if [ -n "${GITLAB_RAILS-}" ] && [ -x "${GITLAB_RAILS}" ]; then
        printf '%s' "${GITLAB_RAILS}"
        return 0
    fi
    if command -v gitlab-rails >/dev/null 2>&1; then
        command -v gitlab-rails
        return 0
    fi
    if [ -x /opt/gitlab/bin/gitlab-rails ]; then
        printf '%s' "/opt/gitlab/bin/gitlab-rails"
        return 0
    fi
    return 1
}
```

Missing tool → `out_die` with **Next:** `install GitLab CE, then sudo {{APP_NAME}} list-users`.

## 3. List users (sample)

```ruby
# gitlab-rails runner body (data TSV; not a product message)
User.order(:id).find_each { |u| puts [u.id, u.username, u.email, u.state].join("\t") }
```

Human: one line per user. JSON: `count`, `usernames`, `ids`. **MUST** `check_root` first.

## 4. Reset password (sample)

TTY: print a **numbered user list** first (a **menu layer**). Invalid pick **MUST** `out_error`, reprint **this** layer, re-prompt (**MUST NOT** `out_die`). Exit / `quit` leaves the layer.

Password **MUST** travel in process env, **not** interpolated into the runner argv:

```ruby
u=User.find_by_username(ENV["GL_USER"]); abort("missing") unless u
u.password=ENV["GITLAB_NEW_PASSWORD"]
u.password_confirmation=ENV["GITLAB_NEW_PASSWORD"]
u.password_automatically_set=false
u.save!
```

Username **MUST** match `^[A-Za-z0-9_.][A-Za-z0-9_.-]*$`. **MUST NOT** print the new password.

Off-TTY: username operand + `GITLAB_NEW_PASSWORD` required; **MUST NOT** hang.

## 5. gitlab-ctl status (sample)

```sh
{{prefix}}_status() {
    check_root
    _ctl=$({{prefix}}_find_gitlab_ctl) || out_die "gitlab-ctl not found. Next: install GitLab CE, then sudo {{APP_NAME}} status"
    "${_ctl}" status
}
```

## 6. gitlab-adm sudoers (sample fragment — placeholders)

```text
{{LPU_USER}} ALL=(ALL) NOPASSWD: /usr/bin/gitlab-ctl
{{LPU_USER}} ALL=(ALL) NOPASSWD: /opt/gitlab/bin/gitlab-ctl
{{LPU_USER}} ALL=(ALL) NOPASSWD: /usr/bin/gitlab-rails
{{LPU_USER}} ALL=(ALL) NOPASSWD: /opt/gitlab/bin/gitlab-rails
```

Typical LPU: login `gitlab-adm`, home `/etc/gitlab-adm`, public `/etc/gitlab` symlink. Remove path: sudoers backup → restore `/etc/gitlab` → `userdel -r`.

## 7. How to specialize

1. One Active `requirement-domain-{{SUBJECT}}.md`.
2. Dual-mention every verb on the language CLI-interface REQ.
3. If a numbered main menu is claimed, `list-users` / `reset-password` / `status` **MAY** be rows; `setup` **MUST NOT**.
4. Proof: **`TP-{{SUBJECT}}-NN`** via **`PM-DOMAIN-TEST-PLAN`**. Non-root fail-closed is Core; live Omnibus mutate is optional.

## Under command line for normal user only

When the product may run on Termux, Git Bash, Windows cmd, or the same class: Type 1/2 unused on detect; no in-tool sudo / apt / dedicated system user; no `sudo curl | sh` recommend; Git Bash and Windows cmd do not invoke Termux `pkg`. **This mold:** list-users / reset-password / status / setup / remove-lpu stay unused on that class.

## Design-time verification

| TP family | Intent |
|-----------|--------|
| **TP-{{SUBJECT}}-01** | Help lists GitLab operator verbs; omits Nginx |
| **TP-{{SUBJECT}}-05** | `list-users` non-root fail-closed |
| **TP-{{SUBJECT}}-06** | `reset-password` non-root fail-closed |

**Last Updated**: 2026-09-13
**Owner**: {{OWNER}}
