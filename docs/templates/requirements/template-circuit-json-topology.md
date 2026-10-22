---
name: circuit-json-topology
id: LM-CIRCUIT-JSON-TOPOLOGY
kind: law-mold
domain_track: domain-circuit
description: >
  Portable law mold. Cite as LM-CIRCUIT-JSON-TOPOLOGY (path secondary). Domain-track circuit/SVG.
---

**file**: template-circuit-json-topology.md  
**Status**: Active (Version 1.0.0 – Circuit track template; specialize for product law)  
**Project**: Any CIAO-Lite Project with schematic/topology tooling (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

## 1. Purpose

This template defines portable **MUST/SHOULD** rules for **Topology JSON**: the workspace circuit-json **stage 1** intermediate (`components` + `nets` + validation), not tscircuit’s industry element-array Circuit JSON.

**Agent harness (when on disk):** `docs/skills/skill-circuit-json-topology-generation.md`  
**Shared language:** `docs/terminologies/circuit-json.md`

---

## 2. Scope and non-goals

| In scope | Out of scope |
|----------|--------------|
| Logical connectivity JSON schema rules | Inventing pin geometry without symbol tables |
| Exclusive net naming conventions | Treating this schema as tscircuit Circuit JSON without an explicit converter |
| Validation checklist expectations | PCB copper / Gerber generation |

---

## 3. Core rules

### 3.1 Schema shape

- Topology output **MUST** be a JSON object with at least:
  - `components` — array of component objects with unique uppercase `id`
  - `nets` — array of net objects with exclusive standard names and pin references
- Pin references in nets **MUST** use `ComponentID.PinName` only (e.g. `R1.pin2`, `LED1.anode`).
- Component `id` values **MUST** be unique uppercase short identifiers (e.g. `R1`, `LED1`, `VCC`).

### 3.2 Net naming (exclusive patterns)

Agents **MUST** use only project-approved exclusive net name patterns (skill/term SSOT). Typical categories:

| Category | Pattern intent | Examples (illustrative) |
|----------|----------------|-------------------------|
| Power | Fixed power rails | `VCC_NET`, `VDD_NET`, … |
| Ground | Fixed ground | `GND_NET` |
| Signal | Descriptive, not `net1`/`nodeA` | Domain signal names per skill rules |

**MUST NOT** invent arbitrary `net1`, `nodeA`, `sig1` style names when exclusive patterns apply.

### 3.3 Validation

Before finalizing topology, agents **MUST** run quantitative + qualitative checks (component count, net count, dangling pins, power/ground presence as required) and emit a **Validation Summary**.

### 3.4 Disambiguation

When “circuit-json” is ambiguous, agents **MUST** resolve: workspace Topology JSON vs industry tscircuit Circuit JSON (`docs/terminologies/circuit-json.md`). Do not claim interchangeability without an explicit mapping task.

---

## 4. Pipeline position

```text
Human/agent circuit description
        → Topology JSON  (this template + topology skill)
        → Component Schema JSON  (template-circuit-json-component-schema)
        → Schematic SVG / flatten  (template-circuit-svg-generation, template-svg-flatten)
```

---

## 5. Specialization notes (project requirements)

When specializing into `requirement-*.md`:

- State app type if tooling is productized (e.g. schematic pipeline CLI vs docs-only).  
- Keep net naming and schema rules complete (no hollow TBD).  
- Live product paths for symbol libraries → Selection/defaults or Config; not frozen as sole universal path in core if multiple roots are allowed.  
- Product source cites only live requirements after specialization—not this template or skills.

---

## 6. Protection Rule (Sacred)

Future agents **MUST NOT**:

- Skip validation checklist/summary for topology claimed complete.  
- Mix tscircuit element-array schema with this topology object schema without an explicit converter.  
- Invent geometry here that belongs in symbol tables / component schema stage.  
- Cite this template as product-source ALIGNMENT authority.  
- Invent missing skill/requirement paths.

---



## Design-time verification

**Law mold:** `LM-CIRCUIT-JSON-TOPOLOGY`  
**Track:** domain-circuit (default SKIP_DOMAIN on H1 unless named)

| Gate | Artifact | Status guidance |
|------|----------|-----------------|
| Specialize product law | `requirement-*` under product domain when claimed | design |
| Skill / suite | matching `SK-CIRCUIT-*` / `SK-SVG-*` when on disk | design / have |
| RTM | `../tests/template-requirement-test-traceability.md` | design |

When product does not claim circuit/SVG surface, mark **n/a** on product maps.

**Last Updated**: 2026-08-11 (LM-ID + DTV stub for ID-notation / track hygiene)  

**Last Updated**: 2026-07-12  
**Owner**: {{OWNER}}  
**Alignment**: `docs/terminologies/circuit-json.md`, `docs/skills/skill-circuit-json-topology-generation.md`, `docs/templates/template-circuit-json-component-schema.md`, CIAO / CIAO-Lite
