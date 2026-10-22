---
name: nodejs-api-client
id: LM-NODEJS-API-CLIENT
kind: law-mold
description: >
  Portable law mold. Cite as LM-NODEJS-API-CLIENT (path secondary).
---

**file**: docs/templates/requirements/template-nodejs-api-client.md
**Status**: Active (Version 1.0.0 – Generalized from template form docs/templates/requirements/template-nodejs-api-client.md with placeholders; language-specific Node.js template)
**Project**: {{APP_NAME}} – {{PLATFORM_NAME}} Platform Management CLI
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

# Requirement / Template: Official Platform API Client as Source of Truth for Remote Platform Access (Node.js)

## 1. Purpose

This requirement (or template for similar Node.js CLIs) mandates that all future remote/platform data access logic in `{{APP_NAME}}` **must** be designed, documented, and (where feasible) implemented by direct reference to the official upstream {{PLATFORM_NAME}} Platform API Client.

**Primary upstream reference** (studied per git-upstream-skill):
- The platform core repository contains the official Platform API client package: {{REPO_URL}}
- Package: `{{API_CLIENT_PACKAGE}}`

The goal is to eliminate ad-hoc queries, fragile custom protocol assumptions, and placeholder data. The official client (`connect()` / `connectRest()`) is the authoritative, maintained way to speak to the platform's auth service and collaborative data layer.

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
| **Node.js CLI architecture** | `docs/terminologies/nodejs-cli-architecture.md` | `product-law` | Node CLI structure |

**SSOT types used:** `meta-catalog` · `policy` · `product-law`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Mandatory Upstream Study (Non-Negotiable)

Before any new code, requirement, or documentation touching remote data access (findAll, createDoc, notifications, cards, messages, drive objects, calendar/planner events, etc.):

1. **Always follow the upstream git analysis process** defined in `skill-upstream-git-analysis.md`.
2. Perform the analysis against the platform's core monorepo ({{REPO_URL}}), with **special focus on the api-client package**.
3. Read and internalize:
   - The client package README (auth, connect vs connectRest, findAll/findOne, CRUD, collections, mixins, markup)
   - Key source files (client.ts, types.ts, index.ts)
   - Dependencies and authentication flow (token + workspace selection)
   - Markup / CollaborativeDoc handling patterns
4. Document the exact methods, option shapes, and error behaviors used.

**Never** invent a protocol or query shape without cross-referencing the client implementation and its tests.

## 3. Core Rules for {{APP_NAME}}

### 3.1 Authentication & Connection Model
- **Auth service is auth-only**: Use it (or the account-client) exclusively for login, token issuance, workspace listing/selection, etc. (via `{{APP_NAME}} login --endpoint {{ENDPOINT}}`).
- **Data layer / transactor (or equivalent collaborative engine) is required for most system components and platform data**: The collaborative model lives behind the data service. Real remote inspection/mutation **must** use the official client:
  - `const client = await connect(url, { token, workspace });`
  - Then `client.findAll({{CARD_CLASS}}, query)`, `findOne`, `createDoc`, etc.
- Token from auth service + workspace selection is the bridge, but data access is **not** via direct HTTP/RPC to the auth endpoint (that produces method-not-found or simulated results).
- Prefer `connect()` (persistent WebSocket / real-time connection) for complex queries, real-time needs, and most system components. Use `connectRest()` only for simple stateless cases.
- Workspace selection / role / identity context must be handled as the client does (getWorkspaceToken, selectWorkspace, getSocialIds / equivalent).

### 3.2 Data Access Operations
All new remote inspection / mutation features **must** map to the client's public surface **using the data layer**:

- `findAll(_class, query, options)` / `findOne(...)`  
  (e.g. `findAll('{{INBOX_CLASS}}', { attachedTo: userAccountId })` for inbox; `findAll('{{CARD_CLASS}}', query)` for cards — never fake arrays or auth-service RPCs).

  **Cards / unified objects example (data layer required, using previous token + workspace)**:

  ```ts
  import { connect } from '{{API_CLIENT_PACKAGE}}';
  const client = await connect('{{ENDPOINT_BASE}}', { token: previousLoginToken, workspace: '{{WORKSPACE}}' });
  // All items (default workspace-scoped query)
  const allItems = await client.findAll('{{CARD_CLASS}}', {}, { limit: 20 });
  // "My items" (filter by creator from previous token)
  const myItems = await client.findAll('{{CARD_CLASS}}', { createdBy: '{{ACCOUNT_ID_PLACEHOLDER}}' }, { limit: 5 });
  // Title filter (server-side $like)
  const filtered = await client.findAll('{{CARD_CLASS}}', { title: { $like: '{{TITLE_PREFIX}}%' } }, { limit: 10 });
  // Real results from data layer (verified with previous token)
  await client.close();
  ```

  **Event / planner / calendar example (data layer required)**:

  ```ts
  import { connect } from '{{API_CLIENT_PACKAGE}}';
  const client = await connect('{{ENDPOINT_BASE}}', { token: previousLoginToken, workspace: '{{WORKSPACE}}' });
  const events = await client.findAll('{{EVENT_CLASS}}', {}, { limit: 20 });
  // With title or date filter
  const filtered = await client.findAll('{{EVENT_CLASS}}', { title: { $like: '{{TITLE_PREFIX}}%' } }, { limit: 10 });
  await client.close();
  ```

- `createDoc`, `updateDoc`, `removeDoc`
- `addCollection`, `updateCollection`, `removeCollection`
- `createMixin`, `updateMixin`
- `getHierarchy()`, `getModel()`, `getAccount()`
- Markup operations (`fetchMarkup`, `uploadMarkup`)

**Anti-fake / honesty rules (critical for defensive integrity)**:
- No command may claim "uses authenticated session", "demonstrates API client / findAll / data layer", or "remote inbox/cards/drive/calendar" unless the code actually performs `client.findAll` (or equivalent) against the data layer using a real token from a prior login.
- Never return hardcoded example data, local database results, or fabricated objects when a valid token + workspace is available. If the client path is not yet wired, explicitly document the limitation and surface the real error/response from any attempted live call.
- Every such feature must be exercised in verification against a real (non-local) instance using the previous token (from `{{APP_NAME}} login --endpoint {{ENDPOINT}}`), showing verbatim real `findAll` output (not "example" or simulated). Bypass techniques are for diagnostics only and never count as proof of the production path.
- Legacy direct database access for platform objects is deprecated for new work and must never be presented as remote/token-based.

Real pattern (correct):
```ts
import { connect } from '{{API_CLIENT_PACKAGE}}'
const client = await connect('{{ENDPOINT_BASE}}', { token, workspace: '{{WORKSPACE}}' })
const items = await client.findAll('{{INBOX_CLASS}}', {}, { limit: 20 })
// Real results: objects with attachedTo, intlParams, isViewed, etc.
await client.close()
```

Fake / unacceptable (what must be avoided):
```js
const exampleItems = [ { id: 'inbox1', title: 'Example item' }, ... ]  // or direct calls to auth endpoint with unsupported methods
```

### 3.3 CLI Implementation Strategy (Node.js)
- The main `{{APP_NAME}}` binary is a Node.js v20+ program.
- All output goes through the centralized Output class (single source of truth; --json forces quiet; all errors/warnings/debug to stderr).
- Version, titles, descriptions, about/diagnostics content come from the About singleton.
- All help/usage/command description text and the `help` command come from the Help singleton.
- Token/endpoint/user and session persistence come from the Session singleton.
- Debug (DEBUG=1 or --debug) is supported but suppressed in --json.
- It uses patterns from the official `{{API_CLIENT_PACKAGE}}`.
- Document in the project API strategy doc.

### 3.4 Workspace & User Context
- Always resolve workspaces via the auth client's `getUserWorkspaces` / `selectWorkspace` flow.
- Use the Account / identity object returned by the client for authorship context.

### 3.5 Error Handling & Resilience
- Map client errors (workspace not found, auth failures, connection issues) to the Output class (errors always to stderr; structured JSON on stderr when --json).
- Support graceful degradation: if data layer is unreachable, clearly state that any local fallback is less safe.

### 3.6 Documentation & Requirements Updates
- All new remote commands must document their data source as "Platform API Client (`{{API_CLIENT_PACKAGE}}` from {{REPO_URL}} — studied via `skill-upstream-git-analysis.md`)" in both the CLI help and the corresponding docs.
- Update the project API strategy doc, cli-interface requirement, and main-requirements index.
- Add this template as an active supporting reference when specializing for a concrete project.

## 4. Non-Negotiable (for any API-related work)

- Do **not** add new direct database queries against platform objects without an accompanying note explaining why the official API client path was not viable.
- Do **not** write custom protocol framing or "findAll" logic without first reproducing the equivalent using the official client in a small test script and documenting the behavior.
- Every token-based command that talks to a remote instance **must** be exercisable against a real instance using the patterns from the api-client (auth via auth service + **data layer connection via connect + findAll/createDoc** on the model). Direct auth-service calls or local fallbacks must be explicitly called out as non-compliant with "remote" claims.
- Verification must include the exact previous token, real public endpoint (no bypasses for final claims), and verbatim real client output.

## 5. Example `_class` / Model Identifiers (Platform Specific)

All model identifiers below **must** be extracted via systematic upstream git analysis (following `skill-upstream-git-analysis.md`) of the platform's model packages. Never hardcode or assume values from memory.

**Usage in the official API client** (see the client package README and client.ts):
```ts
import { connect } from '{{API_CLIENT_PACKAGE}}'
// import platformModels from '{{PLATFORM_MODEL_PACKAGE}}'  // if provided

const client = await connect('{{ENDPOINT_BASE}}', { token, workspace: '{{WORKSPACE}}' })

// Examples (replace with actual identifiers from upstream study)
const items = await client.findAll('{{CARD_CLASS}}', { title: { $like: 'Example%' } })
const inbox = await client.findAll('{{INBOX_CLASS}}', { attachedTo: docNotifyContextId }, { limit: 50, sort: { createdOn: -1 } })
```

**Typical categories to study and populate** (examples only — replace with real values from the target platform):
- Core system (Doc, Space, Account, Class, Tx* types, etc.)
- Contact / People
- Notification & Inbox (ActivityInboxNotification and related DocNotifyContext)
- Drive / Storage (Drive, Resource, Folder, File, FileVersion)
- Card / Unified Objects (Card, MasterTag, Tag, etc.)
- Activity / Messages
- Task / Tracker / Project
- Document
- Calendar / Planner / Event / Time (Event, ReccuringEvent, ReccuringInstance, ToDo, etc. — note inheritance and date/dueDate fields)
- Other domain-specific classes

**Notes from upstream analysis**:
- Use imported constants from the platform model package rather than raw strings when available.
- Subclasses are automatically included when querying a parent `_class` (via Hierarchy.isDerived or equivalent).
- Workspace scoping is typically handled by the client connection or explicit filters.
- Many inbox-related items are AttachedDoc to a DocNotifyContext.
- For full list and correct attribute types (especially date/time, refs, arrays), always re-run upstream analysis on the model source as new domains are added.

## 6. Protection Rule (Sacred)

**Future AI assistants, Grok, or maintainers MUST NOT**:
- Generate or use this template without first performing full upstream git analysis via `skill-upstream-git-analysis.md` on the target platform's core repository (focus on the api-client package).
- Hardcode any specific project name ({{APP_NAME}}), platform name, endpoint ({{ENDPOINT}}), workspace, package name ({{API_CLIENT_PACKAGE}}), or concrete _class / model identifier inside generated content or derived requirements.
- Use fake data, simulated results, or direct auth-service calls for data queries when a previous token is available.
- Treat bypass / resolve-IP / local-listener success as proof that the production hostname + headers + client path works.
- Skip re-reading related incidents about fake data, verification fidelity, and upstream study failures before modifying client-related code.
- Remove or weaken the anti-fake rules, mandatory upstream study requirement, or the distinction between auth service and data layer.
- Present aspirational "demonstrates API client" claims without working code that actually calls the client with a real token and shows verbatim real output.

Violating any of these is considered a **critical regression** against the project's defensive documentation and implementation integrity layer.

---


## Design-time verification

| Gate | Artifact | Phase |
|------|----------|-------|
| Skill | `skill-nodejs-cli-coding` | Review |

**RTM:** `../tests/template-requirement-test-traceability.md` §4.

**Last Updated**: 2026-06-09 (Generalized template created; all project-specific names, endpoints, incidents, example data, and concrete _class values replaced with placeholders; upstream study and anti-fake rules preserved as core defensive requirements)
**Owner**: Platform Client Layer
**Alignment**: Fully synchronized with `docs/skills/skill-upstream-git-analysis.md`, `docs/skills/skill-requirement-template-conversion.md`, `docs/requirements/index.md`, `docs/templates/requirements/template-cli-interface.md`, `docs/templates/requirements/template-output-requirements.md`, `AGENTS.md` (CIAO Protection Zones) and specialized requirements, and **CIAO Principles 1, 2, 3, 4, 20 (v2.10.2)** (https://github.com/cloudgen/ciao).

---

**How to specialize this template for a concrete project**:
1. Copy to `docs/templates/requirements/template-nodejs-api-client.md` (or equivalent language-specific name).
2. Replace all `{{PLACEHOLDER}}` with concrete values from upstream study.
3. Add project-specific verification examples (using previous token + real public endpoint, no bypasses).
4. After specialization, update `docs/requirements/index.md` with the specialized `requirement-*.md` row only (never list this template path in the registry).
5. Record any new incidents or lessons learned in the Protection Rule or a new incident file.

**Precise diff needed for `docs/requirements/index.md`** (to be applied after specialization):

```diff
diff --git a/docs/requirements/index.md b/docs/requirements/index.md
--- a/docs/requirements/index.md
+++ b/docs/requirements/index.md
@@ -XX,6 +XX,7 @@
 ## 3. Active Supporting Requirements

 - docs/requirements/index.md (this file)
+- docs/templates/requirements/template-nodejs-api-client.md (until specialized to requirement-nodejs-api-client.md)
 - docs/templates/requirements/template-cli-interface.md
 - docs/templates/requirements/template-output-requirements.md
```

**Note**: Keep the template under `docs/templates/requirements/`. When specialized for a project, the target name is typically `docs/requirements/requirement-api-client.md` or `requirement-nodejs-api-client.md` (not live until created). Cite only paths that exist.
