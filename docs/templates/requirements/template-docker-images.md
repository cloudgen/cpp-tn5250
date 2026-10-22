---
name: docker-images
id: LM-DOCKER-IMAGES
kind: law-mold
description: >
  Portable law mold. Cite as LM-DOCKER-IMAGES (path secondary).
---

**file**: template-docker-images.md
**Status**: Active (Version 2.0.0 – Major rewrite with stronger technical focus on Docker, base OS, libc, user mapping, volume/port strategy, and architectural intention)
**Project**: Any CIAO-Lite Project (reusable template)
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

# Template: Docker Images

## 1. Purpose

This template provides guidance on making intentional and technically sound decisions regarding Docker images in CIAO-Lite projects.

It serves as a **technical supplement** to architecture design. While the overall system architecture should not be locked to a single technology, this template focuses specifically on Docker-related concerns to help teams make better image-related decisions.

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
| **Three-layer privilege** | `docs/terminologies/three-layer-privilege.md` | `mention-only` | Image user model |
| **System user** | `docs/terminologies/system-user.md` | `identity-runtime` | Container user |

**SSOT types used:** `identity-runtime` · `mention-only` · `meta-catalog` · `policy`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Docker vs Container: Clarification

It is important to distinguish between the two concepts:

- A **Container** is a running instance of an image. It provides process isolation, its own filesystem view, network stack, and resource limits.
- **Docker** is a popular platform and toolset used to build, ship, and run containers.

**Guidance**:
- Design decisions should primarily focus on **container concepts** (image content, user mapping, volumes, networking, isolation).
- Docker-specific commands and behaviors should be treated as implementation details.
- The template should remain useful even if the project later adopts other container runtimes (e.g., Podman).

## 3. Architectural Intention

Docker image decisions have long-term impact on:

- Security posture
- Compatibility with native modules and libraries
- Image size and attack surface
- Operational complexity (updates, debugging, maintenance)
- Alignment with the dedicated system user (UID/GID mapping)

**Recommended Intention**:
> Image choices should be made intentionally to balance security, compatibility, and maintainability. The selected base image and its configuration should support running the application as a non-root user that aligns with the host’s dedicated system user whenever possible.

## 4. Base Image Technical Considerations

Choosing a base image involves several important technical factors:

### 4.1 Base Operating System and Version
- Different base OS images come with different package versions, security update policies, and lifecycles.
- Projects should consider the stability and support timeline of the chosen OS version.

**Example**:
> Using a documented base image such as `{{BASE_IMAGE}}` (example pattern: a glibc-based Node LTS image) provides a defined support lifecycle compared to minimal Alpine-based images. Record the concrete image tag in the specialized requirement after upstream analysis.

### 4.2 glibc vs musl libc
This is one of the most important technical decisions:

| Aspect                    | glibc (Debian/Ubuntu-based)      | musl libc (Alpine-based)             | Recommendation |
|---------------------------|----------------------------------|--------------------------------------|----------------|
| Native module compatibility | Excellent                       | Can cause issues with some modules   | Prefer glibc when native modules are used |
| Image size                | Larger                           | Significantly smaller                | Alpine preferred only when size is critical |
| Debugging & tooling       | Better tooling availability      | More limited                         | glibc generally easier for production |
| Security surface          | Larger base                      | Smaller base                         | Case-by-case decision |

**Guidance**: Projects should explicitly document their libc choice and the reasoning behind it.

### 4.3 OpenSSL and Cryptographic Libraries
Some applications have strict requirements on OpenSSL versions due to compliance or feature needs.

**Guidance**:
- Document the required OpenSSL version range.
- Be aware that Alpine and Debian-based images ship different default OpenSSL versions.
- When using pre-built images, verify the OpenSSL version included.

## 5. Internal User Account and Namespace Mapping

Running containers with proper user mapping is critical for security and volume permission alignment.

**Recommended Practices**:
- The process inside the container should run as a non-root user.
- The container’s internal UID/GID should preferably align with the dedicated system user on the host (`{{APP_USER_UID}}` / `{{APP_USER_GID}}` — often `1000` when matching common image users; set in Implementation Notes).
- Consider the use of user namespaces if stronger isolation is required.

**Example**:
```dockerfile
# Good practice example
RUN groupadd -g 1000 appuser && \
    useradd -u 1000 -g appuser -m appuser
USER appuser
```

**Important**: Volume permissions on the host must match the internal user for bind mounts to work correctly without excessive permissions.

## 6. Volume Mapping Strategy

Volumes are used for persistence, configuration, and data sharing.

**Key Considerations**:
- Volume paths should be clearly defined and consistent.
- Ownership of host directories must align with the container’s internal user.
- Avoid mounting sensitive host paths unless strictly necessary.

**Example**:
```yaml
volumes:
  - type: bind
    source: {{APP_USER_HOME}}/data
    target: {{CONTAINER_DATA_PATH}}
```

Preparation of these directories (creation + permission setting) should be handled during the installation phase, not at container runtime.

## 7. Port Mapping and Networking Strategy

Port mapping decisions affect both security and deployment architecture.

**Recommended Guidance**:
- Prefer not exposing ports directly from containers in production.
- Route traffic through an external reverse proxy or load balancer when possible.
- Clearly document both the internal container port and the externally accessible port (if any).

**Example**:
> The application listens on port 3000 inside the container. In production, this port is not published directly. Instead, an external reverse proxy (e.g. nginx or Traefik) forwards traffic from port 443 to the container’s port 3000.

## 8. Versioning Strategy

Image versioning has significant operational impact.

**Recommended Practices**:
- Avoid floating `:latest` tags in production environments.
- Prefer digest pinning for reproducibility when stability is critical.
- When using tag-based versioning, clearly document the update and testing process.
- Align base OS version updates with application testing cycles.

## 9. Image Customization and Extension Patterns

When the base image needs to be extended:

- Use multi-stage builds to keep final image size small.
- Separate build-time dependencies from runtime dependencies.
- Document any modifications made to the base image (packages added, configurations changed, users created).

## 10. Security Baseline for Docker Images

**Minimum Expectations**:
- Run the main process as a non-root user.
- Use read-only root filesystem where possible, with writable volumes only for required paths.
- Drop unnecessary Linux capabilities.
- Keep the image minimal (avoid installing unnecessary tools in production images).
- Regularly scan images for known vulnerabilities.

## 11. Protection Rules (Sacred)

When working with Docker images, the following should **not** be done:

- Hardcode secrets inside Docker images or Dockerfiles.
- Run the main application process as root without strong justification.
- Use overly permissive volume mounts (e.g., mounting the entire host filesystem).
- Rely on `:latest` tags without a clear update and testing strategy.
- Ignore UID/GID alignment between host and container when using bind mounts.
- Mix image build logic with runtime container management in operational tools.

---


## Design-time verification

| Gate | Artifact | Phase |
|------|----------|-------|
| Specialize → product suite or checklist | declare TP-IDs or checklist in specialized REQ | Design |
| RTM | `../tests/template-requirement-test-traceability.md` | Design |

When this mold has no executable TP family, mark **n/a** with reason in product `reviews/test-plan.md`.

**Last Updated**: 2026-06-15 (v2.0.0 – Major technical rewrite focusing on base OS, libc, OpenSSL, user mapping, volume/port strategy, and Docker vs Container clarification)
**Owner**: Docker & Image Layer
**Alignment**: Fully synchronized with `template-container-runtime.md`, `template-install.md`, `template-secret-management.md`, `template-least-privilege-user.md`, and **CIAO Principles 1, 2, 3, 4, 9, 10, 20 (v2.10.2)**.

---

**How to use this template**:
1. Adapt it to your project’s needs while keeping the core technical considerations.
2. Document your specific choices for base OS, libc, and user mapping.
3. Use the examples as reference patterns, not as mandatory instructions.
4. Maintain strong alignment between host user permissions and container internal users.