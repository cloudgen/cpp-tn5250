---
name: fsm-architecture
id: LM-FSM-ARCHITECTURE
kind: law-mold
description: >
  Portable law mold. Cite as LM-FSM-ARCHITECTURE (path secondary).
---

**file**: docs/templates/requirements/template-fsm-architecture.md  
**Status**: Active (Version 1.0.0 – Generalized from project FSM architecture practice + finite-state-machine-design terminology)  
**Project**: {{PROJECT_NAME}} – {{SHORT_DESCRIPTION}}  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

# Template: FSM Architecture (Multi-Machine System)

## 1. Purpose

This template defines the **official Finite State Machine (FSM) architecture** for a CIAO-Lite project that uses **multiple cooperating state machines**.

It is the Single Source of Truth for how all FSMs in the project are:

- Inventories (closed list of machines)  
- Designed (triad pattern per machine)  
- Validated (transition SSOT)  
- Orchestrated (main loop / scheduler order only)  
- Protected (no merge, no direct mutation, Protection Zones)

**Related terminology:** `docs/terminologies/finite-state-machine-design.md`  
**Related checklist:** `docs/templates/checklists/checklist-fsm-design.md`  
**Related policies:** idempotency-rule, no-hardcode-policy (specialize product names only in the project requirement)

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
| **Finite state machine design** | `docs/terminologies/finite-state-machine-design.md` | `product-law` | Primary FSM vocabulary |
| **Error handling** | `docs/terminologies/error-handling.md` | `product-law` | Invalid transition handling |

**SSOT types used:** `meta-catalog` · `policy` · `product-law`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Core Principles (CIAO-Lite)

| Principle | Rule |
|-----------|------|
| **Independent FSMs** | Each major subsystem has its own dedicated FSM. **Do not merge** machines (e.g. do not combine peer link/control FSMs into one god-machine). |
| **Mutation SSOT** | All state changes **must** go through `change{{FSM_PREFIX}}State()` (or language-equivalent name). |
| **Transition SSOT** | Every transition is validated by `isValid{{FSM_PREFIX}}Transition(from, to)`. |
| **Anti-spam & defensive** | Invalid or repeated noisy transitions are blocked and logged **only once** (anti-duplicate). |
| **Orchestration only** | The main entry (`{{MAIN_LOOP}}`, e.g. `loop()` / app main / scheduler) contains **only** ordered calls to `update{{FSM_PREFIX}}StateMachine()` (plus thin hardware companions if any). **No** business logic and **no** direct state writes in main. |
| **Start / entry state** | Every FSM defines an explicit start state (`{{FSM_PREFIX}}_START` or equivalent). |
| **No permanent stop on error** | `ERROR` / `DEGRADED` are recoverable; the loop keeps ticking machines. |
| **Idempotent re-entry** | Ensure-style transitions and side effects are safe under continuous `update*` (see `docs/terminologies/idempotency-rule.md`). |

## 3. Implemented FSMs (Complete Inventory)

The specialized requirement **must** list the **closed, complete** set of independent FSMs for the project.

**Count:** exactly **{{FSM_COUNT}}** independent FSMs (fill when specializing).

| FSM | Implementation unit | Purpose | Key states (sketch) |
|-----|---------------------|---------|---------------------|
| {{FSM_1_NAME}} | {{FSM_1_FILE}} | {{FSM_1_PURPOSE}} | {{FSM_1_KEY_STATES}} |
| {{FSM_2_NAME}} | {{FSM_2_FILE}} | {{FSM_2_PURPOSE}} | {{FSM_2_KEY_STATES}} |
| {{FSM_3_NAME}} | {{FSM_3_FILE}} | {{FSM_3_PURPOSE}} | {{FSM_3_KEY_STATES}} |
| … | … | … | … |

**Rules:**

- Adding a major subsystem **requires** updating this inventory **and** the orchestration order.  
- Silent extra machines outside the inventory are forbidden.  
- Each machine should have a per-FSM requirement: `requirement-state-machine-{{slug}}.md` (or project naming convention).

## 4. FSM Design Pattern (Strict & Sacred) — the four-class model

Every FSM **must** follow this structure (names adapted per language/runtime):

```text
isValidXxxTransition(from, to)  → SSOT for allowed edges (return true only if permitted)
changeXxxState(newState)        → SSOT for mutation (validate + log + commit)
updateXxxStateMachine()         → main logic: switch on current state; only tick path that calls changeXxxState()
```

Illustrative C-like sketch (not language-mandatory):

```c
/* =========================================================================
 * isValidXxxTransition() - Single Source of Truth for allowed transitions
 * changeXxxState()       - Single Source of Truth for state mutation
 * updateXxxStateMachine()- Main logic (called from {{MAIN_LOOP}})
 * ========================================================================= */
```

**Mandatory behaviors:**

| Function | Must |
|----------|------|
| `isValidXxxTransition` | Encode the documented From → To table only |
| `changeXxxState` | Reject invalid transitions; log once; update state only here |
| `updateXxxStateMachine` | Own the `switch`; apply dependency guards at top; call `change*` for transitions |
| Static / one-shot guards | Prevent debug spam and re-init thrash on high-frequency loops |

**Per-machine rules** (see terminology for full list):

- Explicit `Xxx_START` entry state  
- ERROR/DEGRADED with **outbound** recovery transitions (no absorbing halt)  
- Side effects only inside this FSM’s owning state or helper  
- Protection Zone in each FSM implementation file  
- Debug prefix `[{{FSM_NAME}}]` (+ timestamp when supported)

## 5. Orchestration Order (Critical)

In `{{MAIN_LOOP}}`, FSMs **must** be updated in a **dependency-respecting, requirement-locked** order.

**Template pattern** (replace with concrete `update*` names when specializing):

```text
update{{GATEKEEPER_FSM}}StateMachine();   /* e.g. config validity first */
update{{SELECTOR_FSM}}StateMachine();     /* helpers peers depend on */
update{{DOWNLINK_OR_LOCAL_FSM}}StateMachine();
update{{UPLINK_OR_LINK_FSM}}StateMachine();
update{{SERVICE_FSM}}StateMachine();      /* needs link, e.g. time/sync */
update{{APP_PULSE_FSM}}StateMachine();    /* needs link + services */
update{{OBSERVER_FSM}}StateMachine();     /* read-only peers */
/* optional: update{{OBSERVER_HARDWARE}}();  after logical observer update */
```

**Rules:**

- Prerequisites run **before** dependents in the same cycle so guards see fresh state.  
- Changing order requires **explicit approval** and an update to the specialized architecture requirement.  
- Main remains **orchestration-only**.

## 6. Design Rules (Non-Negotiable)

1. Never modify any `xxxState` variable directly.  
2. All invalid transitions are blocked and logged (anti-fragile).  
3. Every FSM implementation unit contains its own **Protection Zone**.  
4. Debug messages include `[FSM_NAME]` prefix (+ timestamp when available).  
5. Machines are independent: **no cross-FSM calls** except through well-defined dependency guards / shared state reads.  
6. Observer FSMs **must not** mutate peer state.  
7. Continuous `update*` must be **idempotent-safe** for ensure-style work (no thrash when already in target state).  
8. Do not hardcode product names, host paths, or one project’s loop file name into reusable templates—specialize in the project requirement.

## 7. CIAO-Lite Principles Applied

| Principle | Application |
|-----------|-------------|
| **Caution** | Every transition validated; dependency guards fail closed; fixed order |
| **Intentional** | Closed inventory; triad; orchestration-only main; named start states |
| **Anti-fragile** | ERROR/DEGRADED recovery; anti-spam guards; re-entry safety |
| **Over-protect** | Sacred MUST NOTs; Protection Zone per FSM file; no merge; no reorder without approval |

### 7.1 Why This Requirement Exists (Direct CIAO Alignment)

- Multi-FSM systems without architecture SSOT drift into merged machines, illegal transitions, and main-loop business logic.  
- Explicit inventory + order + triad makes AI and human changes auditable and fail-loud.

## 8. Protection Rule (Sacred)

**Future AI assistants, Grok, or maintainers MUST NOT**:

- Merge any two FSMs into a single file or function  
- Modify any state variable except through its dedicated `changeXxxState()` (or equivalent)  
- Remove or weaken `isValidXxxTransition()` validation  
- Add direct state mutation outside the defined triad pattern  
- Change the orchestration order in `{{MAIN_LOOP}}` without explicit approval and requirement update  
- Add a major subsystem FSM without updating the closed inventory and loop order  
- Treat ERROR as a permanent halt that stops ticking the machine  
- Hardcode product-specific names into this template when reusing it for another project  

Violating the above is a **critical architecture regression**.

## 9. Future Enhancements (optional backlog)

Record only when specializing if needed; do not claim done until implemented:

- Visual FSM diagram (e.g. PlantUML)  
- Runtime FSM state reporting  
- Transition history logging for debugging  
- Language/runtime evolution of the four-class model (e.g. class-based FSMs) while preserving rules  

## 10. Specialization checklist

When producing `docs/requirements/requirement-fsm-architecture.md` (or equivalent):

- [ ] Replace all `{{PLACEHOLDER}}` values  
- [ ] Fill complete FSM inventory table with real machines, files, purposes, key states  
- [ ] Set exact `{{MAIN_LOOP}}` and ordered `update*` list  
- [ ] Link each machine to `requirement-state-machine-*.md`  
- [ ] Confirm start states and non-terminal ERROR policy  
- [ ] Update `docs/requirements/index.md`  
- [ ] Run `docs/templates/checklists/checklist-fsm-design.md` on the architecture change  
- [ ] No product hardcodes left in any **template** copy; concrete names only in the specialized requirement  

---

## How to specialize this template

1. Copy to `docs/requirements/requirement-fsm-architecture.md`.  
2. Set `{{PROJECT_NAME}}`, `{{SHORT_DESCRIPTION}}`, `{{FSM_COUNT}}`, `{{MAIN_LOOP}}`.  
3. Replace inventory rows and orchestration order with the project’s real machines (from design + implementation).  
4. Create/update per-machine requirements for each inventory row.  
5. Keep Protection Rule, triad, independence, start-state, and no-permanent-stop-on-error rules intact.  
6. Align with `docs/terminologies/finite-state-machine-design.md` and `idempotency-rule.md`.

---


## Design-time verification

| Gate | Artifact | Phase |
|------|----------|-------|
| Specialize → product suite or checklist | declare TP-IDs or checklist in specialized REQ | Design |
| RTM | `../tests/template-requirement-test-traceability.md` | Design |

When this mold has no executable TP family, mark **n/a** with reason in product `reviews/test-plan.md`.

**Last Updated**: 2026-07-12  
**Owner**: {{OWNER}}  
**Alignment**: `docs/terminologies/finite-state-machine-design.md`, `docs/templates/checklists/checklist-fsm-design.md`, `docs/terminologies/idempotency-rule.md`, `docs/skills/skill-requirement-template-conversion.md`, and **CIAO Principles 1, 2, 3, 4, 20 (v2.10.2)** (https://github.com/cloudgen/ciao)
