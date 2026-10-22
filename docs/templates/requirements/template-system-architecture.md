---
name: system-architecture
id: LM-SYSTEM-ARCHITECTURE
kind: law-mold
description: >
  Portable law mold. Cite as LM-SYSTEM-ARCHITECTURE (path secondary).
---

**file**: template-system-architecture.md
**Status**: Active (Version 2.1.0 – Type 1 elev Tables A/B/C pointer; glue concept retained)
**Project**: Any CIAO-Lite Project (reusable template)
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

# Template: System Architecture

## 1. Purpose

This template defines the high-level system architecture for CIAO-Lite CLI tools that manage applications on Linux hosts using containers (typically Docker).

It serves as the **central architectural glue** document. Its primary goal is to show how different components (host preparation, dedicated system user, privilege layers, container runtime, and configuration) work together, rather than duplicating detailed rules that belong in more specialized requirements.

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
| **Three-layer privilege** | `docs/terminologies/three-layer-privilege.md` | `product-law` | Architecture layers |
| **System user** | `docs/terminologies/system-user.md` | `identity-runtime` | Dedicated account |
| **Least privilege** | `docs/terminologies/least-privilege.md` | `policy` | Power envelope; local-default agents |
| **LLM escape** | `docs/terminologies/llm-escape.md` | `policy` | Avoid unapproved egress / privilege collapse in design work |
| **Surface ownership matrix** | `docs/terminologies/surface-ownership-matrix.md` | `meta-catalog` | Concern ownership |

**SSOT types used:** `identity-runtime` · `meta-catalog` · `policy` · `product-law`

**Policies (normative bodies):** `docs/policies/policy-least-privilege.md` · `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

**Checklists / skills:** **`CL-LEAST-PRIVILEGE`** · **`CL-LLM-ESCAPE`** · **`SK-SYSTEM-ARCHITECTURE-DESIGN`**

## 2. System Context

The CLI tool runs on a **Linux host** and typically uses Docker (or another container runtime) to operate the target application.

The CLI itself usually runs directly on the host (not inside a container) and is responsible for:
- Preparing the host system
- Creating and using a dedicated least-privilege system user
- Managing application configuration and secrets
- Controlling the lifecycle of application containers

## 3. High-Level Architecture

A well-designed CIAO-Lite CLI typically follows a layered execution model:

```
Linux Host
├── Container Runtime (Docker / Podman)
│   └── Application Container(s)
│
└── CLI Tool
    ├── Type 0 – Any user (self-management)
    ├── Type 1 – Elevated privileges with internal escalation (system preparation)
    └── Type 2 – Dedicated least-privilege system user
        ├── Installation & environment setup
        ├── Configuration & secrets management
        └── Container lifecycle operations
```

### 3.1 Key Components and Responsibilities

| Component                        | Type   | Execution Context                        | Responsibility                                                                 | Related Template / Requirement |
|----------------------------------|--------|------------------------------------------|--------------------------------------------------------------------------------|--------------------------------|
| **Prerequisites**                | Type 1 | Root / Internal sudo                     | Install container runtime, system packages, and prepare the host               | `template-prerequisites.md` |
| **Install**                      | Type 2 | Dedicated system user                    | Create dedicated user, directories, and base environment                       | `template-install.md` |
| **Configure**                    | Type 2 | Dedicated system user                    | Manage secrets and application configuration                                   | `template-configuration-management.md`, `template-secret-management.md` |
| **Container Runtime**            | Type 2 | Dedicated system user                    | Start, stop, and manage application containers                                 | `template-container-runtime.md` |
| **Privilege Model**              | All    | All contexts                             | Enforce Type 0/1/2 boundaries; Type 1 allowlisted elev via **Tables A/B/C** (**`LM-THREE-LAYER-PRIVILEGE-MODEL`** §2.2a); harness `policy-least-privilege` | **`LM-LEAST-PRIVILEGE-USER`**, **`LM-THREE-LAYER-PRIVILEGE-MODEL`**, **`CL-LEAST-PRIVILEGE`** / **`CL-LLM-ESCAPE`** / **`CL-CREATE-SUDOERS-SECURITY`** |
| **Container Images**             | Type 2 | Dedicated system user                    | Define and align with target container image (including UID/GID matching)      | `template-docker-images.md` |

## 4. Core Architectural Principles

### 4.1 Dedicated System User

The CLI **SHOULD** create and operate under a dedicated, non-login system user. This user should own persistent data and run application containers.

When using containers, it is strongly recommended to align the host system user's UID/GID with the internal user of the target container image. This enables clean volume mounting without requiring overly permissive permissions (e.g., `chmod 777`).

### 4.2 Context Switching for Type 2 Operations

Type 2 operations **MUST** execute under the dedicated system user. When the CLI is invoked by root or a normal user, it should perform context switching (e.g., using `sudo su - {{SYSTEM_USER}} -c "..."`).

This ensures correct file ownership and access rights while maintaining the principle of least privilege.

### 4.3 Container Runtime as a Separate Layer

Application containers should be treated as a distinct operational layer. The CLI is responsible for managing their lifecycle, but container operations must respect the dedicated system user context.

### 4.4 Separation of Concerns

- **Type 1** operations should focus on host system preparation.
- **Type 2** operations should focus on application-level setup and runtime under the dedicated user.
- External infrastructure (reverse proxies, databases, monitoring systems) should be clearly identified as out of scope or explicitly integrated.

### 4.5 Type 1 elev allowlist (when claimed)

When architecture claims allowlisted Type 1 elev (sudoers / deposit / package host prep with fixed Cmnds):

1. Specialized **`LM-THREE-LAYER-PRIVILEGE-MODEL`** (or single elev-table SSOT peer) **MUST** own elev **Tables A/B/C**.  
2. This architecture mold **maps** components to layers — it **MUST NOT** become a second elev whitelist.  
3. Ship unit elev outside Table A is an architecture defect (closed elev set; anti agent jailbreak).

## 5. Role as Architectural Glue

This document should serve as the **central map** of the system. It should:

- Show how major components connect and depend on each other.
- Explain the flow from host preparation → dedicated user setup → configuration → container runtime.
- Reference other requirements/templates without duplicating their detailed rules.
- Make the overall architecture understandable at a high level.

## 6. Design Principles (CIAO / CIAO-Lite)

- **Caution (CIAO Principle 1)**: Assume operations may be invoked from different user contexts. Enforce strict context switching and least privilege.
- **Intentional (CIAO Principle 2)**: Every major component has a defined type, owner, and responsibility. The architecture clearly explains *why* components are separated.
- **Anti-fragile (CIAO Principle 3)**: The architecture supports different Linux distributions and container runtimes through clear abstraction and UID alignment.
- **Over-protect (CIAO Principle 4 / CIAO-Lite O · Principle 20)**: Key architectural decisions (dedicated user model, context switching, UID alignment with container images) are protected from simplification.

## 7. Protection Rule (Sacred)

**Future AI assistants, Grok, or maintainers MUST NOT**:

- Remove or weaken the dedicated system user model and UID alignment with container images.
- Remove or weaken the context switching requirement for Type 2 operations.
- Turn this document into a duplicate of `template-least-privilege-user.md` or `template-three-layer-privilege-model.md`.
- Remove the "glue" responsibility — this template must continue to explain how components connect at a system level.
- Delete the Relationships / Component table or make the document purely privilege-focused.
- Claim Type 1 allowlisted elev architecture complete without Tables A/B/C on the elev SSOT mold.
- Invent a second elev allowlist in this glue document that conflicts with three-layer SSOT.

Violating any of the above is considered a **critical regression**.

---


## Design-time verification

| Gate | Artifact | Phase |
|------|----------|-------|
| Specialize → product suite or checklist | declare TP-IDs or checklist in specialized REQ | Design |
| RTM | `../tests/template-requirement-test-traceability.md` | Design |

When this mold has no executable TP family, mark **n/a** with reason in product `reviews/test-plan.md`.

**Last Updated**: 2026-08-07 (v2.1.0 – §4.5 elev Tables A/B/C single SSOT; privilege row + protection rules)  
**Owner**: System Architecture Layer  
**Alignment**: Fully synchronized with `template-least-privilege-user.md`, `template-three-layer-privilege-model.md`, `template-container-runtime.md`, `template-docker-images.md`, `template-prerequisites.md`, and **CIAO Principles 1, 2, 3, 4, 9, 10, 20 (v2.10.2)**.