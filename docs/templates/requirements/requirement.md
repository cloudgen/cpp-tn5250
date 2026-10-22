# Requirement: REQ-<AREA>-<NNN> — <short title>

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

```yaml
id: REQ-<AREA>-<NNN>
title: <short title>
status: draft   # draft | approved | in-progress | done | deprecated | superseded
area: <product|platform|security|ops|...>
owners: []
created: YYYY-MM-DD
updated: YYYY-MM-DD
supersedes: null
superseded_by: null
related: []     # other REQ-IDs
```

## Problem / context

Why this exists. Current pain or gap. Links to incidents or prior docs if any.

## Goals

- …

## Non-goals

- …

## Requirements (normative)

Numbered, testable statements. Prefer “must / must not / should”.

1. **R1** — …
2. **R2** — …

## Acceptance criteria

Checklist-friendly, verifiable outcomes:

- [ ] …
- [ ] …

## Constraints (CIAO-relevant)

Call out anything that touches safety, storage, privileges, backups, multi-env, or protection zones:

- Caution: …
- Intentional: …
- Anti-fragile: …
- Over-protect: …

## Design notes (optional)

High-level approach; not a full design doc. Point to design docs if they exist.

**Versioned surface:** When this file lives under tracked `docs/requirements/`, do **not** list `docs/templates/`, `docs/skills/`, `docs/terminologies/`, `docs/incidents/`, or checklist paths here. Related IDs in front matter and body should be peer requirements / product artifacts only.

## Implementation traceability

| Artifact | Path / ID | Notes |
|----------|-----------|--------|
| Code | | |
| Docs | peer `requirement-*.md` / product paths only on versioned surface | |
| Tests | | |

## Revision history

| Date | Change | Author / agent |
|------|--------|----------------|
| YYYY-MM-DD | Initial draft | |
