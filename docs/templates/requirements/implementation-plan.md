# Implementation plan: <title>

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

> Use this shape for session plan mode (`plan.md`) **and** any durable plan saved under `docs/`.
> Plan mode must design work **and** update `docs/requirements/` when intent changes.

```yaml
status: draft   # draft | approved | in-progress | done | abandoned
created: YYYY-MM-DD
related_requirements: []   # REQ-IDs — required for non-trivial work
```

## Context

Why this change. User ask in one sentence. Current system state.

## Requirements impact

| REQ-ID | Action | Notes |
|--------|--------|--------|
| REQ-… | create / update / no-change / deprecate | |

- [ ] `docs/requirements/index.md` updated if any create/status change (**requirement rows only** — no template/skill/terminology paths in the registry)
- [ ] Versioned requirements files pass git-surface filter (no harness path leak; see plan-and-requirements checklist)
- [ ] Requirement files written or revised from `docs/templates/requirements/requirement.md`
- [ ] If **no requirements impact**, explicit rationale: …

## Recommended approach

Single recommended path (not a menu of equals). Why this approach.

## Critical files

| Path | Change type | Reason |
|------|-------------|--------|
| | create / edit / delete | |

## Reuse

Existing functions, modules, patterns to reuse (with paths).

## CIAO considerations

| Principle | Plan item |
|-----------|-----------|
| **C** Caution | Validation, errors, fail-loud points |
| **I** Intentional | Intent comments, preserve existing “why” |
| **A** Anti-fragile | Paths, env, backups, fallbacks |
| **O** Over-protect | Protection zones to leave untouched; new zones if needed |

## Out of scope

…

## Risks and open questions

| Item | Severity | Mitigation / who decides |
|------|----------|--------------------------|
| | | |

## Verification

How to prove done end-to-end (commands, manual checks, acceptance criteria from REQ-IDs).

## Review gates (after implement)

- [ ] `docs/templates/checklists/implementation-ciao.md`
- [ ] `docs/templates/checklists/code-review.md`
- [ ] `docs/templates/checklists/security-review.md` (if auth, data, secrets, network, or privileges touched)
- [ ] No-placeholder policy satisfied (`AGENTS.md`) — no `TODO`/`TBD`/stubs/dummy content left in delivered paths
