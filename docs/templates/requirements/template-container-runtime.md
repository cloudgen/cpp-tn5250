---
name: container-runtime
id: LM-CONTAINER-RUNTIME
kind: law-mold
description: >
  Portable law mold. Cite as LM-CONTAINER-RUNTIME (path secondary).
---

**file**: template-container-runtime.md
**Status**: Active (Version 2.0.0 – Major update with stronger architectural intention, container inventory, volume/port strategy, and base image considerations)
**Project**: Any CIAO-Lite Project (reusable template)
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

# Template: Container Runtime Management

## 1. Purpose

This template provides guidance on designing and managing container runtime operations in CIAO-Lite projects. It focuses on creating a clear, intentional, and defensible approach to how containers are used, rather than just listing operational rules.

The goal is to help projects define **how** containers should be used architecturally, not only **what** commands to run.

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
| **Three-layer privilege** | `docs/terminologies/three-layer-privilege.md` | `product-law` | Privilege model in containers |
| **System user** | `docs/terminologies/system-user.md` | `identity-runtime` | Least-privilege app user |

**SSOT types used:** `identity-runtime` · `meta-catalog` · `policy` · `product-law`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Architectural Intention (Core of This Template)

A good container runtime design should be **Intentional**. This means clearly answering:

- What role do containers play in the overall system architecture?
- Why are container operations separated from installation and configuration?
- What mental model should the team follow when working with containers?

**Recommended Intention**:
> Container runtime should be treated as a **distinct operational layer** focused on execution, lifecycle, networking, and observability. It should depend on artifacts prepared by `install` (directories, permissions) and `configure` (secrets and settings), but should not perform those responsibilities itself.

This separation increases clarity, reduces privilege risk, and makes the system easier to reason about and maintain.

## 3. Relationship Between Docker and Containers

Docker is a popular **container runtime platform**, but it is not the same as a "container".

- A **container** is a running instance of an image with its own filesystem, process space, and resource limits.
- **Docker** is one tool to create, manage, and run containers.

**Guidance**:
- The template should remain useful even if the project later adopts other container runtimes (Podman, containerd, etc.).
- Design decisions should focus on **container concepts** (images, volumes, networking, isolation) rather than Docker-specific commands only.

## 4. Container Inventory

One of the most important parts of container architecture is clearly defining **which containers** will exist and what they are responsible for.

**Recommended Practice**:
Every project should maintain a simple container inventory as part of its architecture documentation.

**Example Container Inventory**:

| Container / Service | Purpose                              | Expected Base Image Family | Scaling Expectation | Notes |
|---------------------|--------------------------------------|----------------------------|---------------------|-------|
| `gateway`           | Main API / application entry point   | glibc (Node.js / Python)   | Low to Medium       | Primary service |
| `worker`            | Background job processing            | glibc                      | Medium              | Can be scaled horizontally |
| `scheduler`         | Task scheduling                      | glibc                      | Low                 | Optional |
| `db`                | Database                             | Official PostgreSQL        | Low                 | Prefer external managed DB |

This inventory helps teams make consistent decisions about image choice, resource allocation, and security requirements.

## 5. Base Image Strategy

Choosing a base image has long-term implications on size, security, compatibility, and maintenance.

**Key Considerations**:
- **glibc vs musl libc**: glibc offers better compatibility with native modules. musl (Alpine) produces smaller images but can cause issues with certain native dependencies.
- **Minimal / Distroless images**: Reduce attack surface but may complicate debugging.
- **Official images**: Generally preferred for databases and common runtimes due to maintenance and security updates.

**Guidance**:
Projects should explicitly document their base image strategy and the reasoning behind it.

## 6. Volume Mapping Strategy

Volumes are critical for data persistence, configuration, and sharing data between host and container.

**Recommended Practices**:
- Keep volume paths consistent and well-documented.
- Align host directory ownership with the user inside the container.
- Prefer named volumes or bind mounts with clear purposes.

**Example**:
```yaml
# Good Practice Example
volumes:
  - type: bind
    source: {{APP_USER_HOME}}/data
    target: {{CONTAINER_DATA_PATH}}
    consistency: cached
```

**Important**: Volume preparation (creating directories with correct ownership) should be handled during installation, not at runtime.

## 7. Port Mapping and Networking Strategy

How ports are exposed significantly affects security and deployment flexibility.

**Recommended Guidance**:
- Avoid publishing ports directly from containers in production when possible.
- Prefer routing traffic through an external reverse proxy (nginx, Traefik, Caddy, or cloud load balancer).
- Document both internal container ports and externally exposed ports clearly.

**Example**:
> In production, the gateway container listens on port 3000 internally. Traffic is routed through an external reverse proxy listening on ports 80 and 443. Direct port publishing (`-p 3000:3000`) is only used in development.

## 8. Customization and Image Extension Patterns

When projects need to extend base images, they should follow consistent patterns.

**Recommended Approaches**:
- Use multi-stage builds to keep final images small.
- Clearly separate build-time dependencies from runtime dependencies.
- Document any customizations made to base images.

## 9. Security and Least-Privilege Considerations

Container runtime design must prioritize security.

**Key Requirements**:
- Containers should run as non-root users whenever possible.
- Prefer read-only root filesystems with writable volumes only where needed.
- Avoid running containers with unnecessary capabilities.
- Secrets should be injected via `--env-file`, mounted files, or secret management systems — never hardcoded in commands.

## 10. Idempotency and Lifecycle Management

Container operations should be designed to be safe to run repeatedly.

**Common Pattern**:
Before starting a container, it is acceptable to remove any existing container with the same name to ensure a clean state. This supports reliable restarts and deployments.

## 11. Protection Rules (Sacred)

Future modifications to container runtime logic **MUST NOT**:

- Move container start/stop logic into the installation phase.
- Hardcode secrets directly in container run commands.
- Create or modify persistent directories at runtime (this belongs to installation).
- Allow container operations to run without proper least-privilege context.
- Remove the separation between installation, configuration, and runtime concerns without strong justification.

---


## Design-time verification

| Gate | Artifact | Phase |
|------|----------|-------|
| Specialize → product suite or checklist | declare TP-IDs or checklist in specialized REQ | Design |
| RTM | `../tests/template-requirement-test-traceability.md` | Design |

When this mold has no executable TP family, mark **n/a** with reason in product `reviews/test-plan.md`.

**Last Updated**: 2026-06-15 (v2.0.0 – Major rewrite focusing on architectural intention, container inventory, Docker vs container relationship, volume/port strategy, and base image considerations)
**Owner**: Container & Runtime Layer
**Alignment**: Fully synchronized with `template-install.md`, `template-secret-management.md`, `template-least-privilege-user.md`, `template-system-architecture.md`, and **CIAO Principles 1, 2, 3, 4, 9, 10, 20 (v2.10.2)**.

---

**How to use this template**:
1. Copy and adapt it for your project.
2. Fill in your actual container inventory.
3. Document your base image strategy and networking approach.
4. Keep the Protection Rules and Intentional design sections intact.