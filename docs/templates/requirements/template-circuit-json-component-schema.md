---
name: circuit-json-component-schema
id: LM-CIRCUIT-JSON-COMPONENT-SCHEMA
kind: law-mold
domain_track: domain-circuit
description: >
  Portable law mold. Cite as LM-CIRCUIT-JSON-COMPONENT-SCHEMA (path secondary). Domain-track circuit/SVG.
---

**file**: template-circuit-json-component-schema.md  
**Status**: Active (Version 1.0.0 – Circuit track template; specialize for product law)  
**Project**: Any CIAO-Lite Project with schematic layout tooling (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

## 1. Purpose

This template defines portable rules for **Component Schema JSON**: workspace circuit-json **stage 2** that enriches Topology JSON with orientation, size, center points, connection points, and connection lines derived from **authoritative component symbol tables**.

**Agent harness (when on disk):** `docs/skills/skill-circuit-json-to-component-schema.md`  
**Upstream topology:** `docs/templates/template-circuit-json-topology.md`  
**Symbols:** `docs/templates/template-circuit-component-symbol.md`  
**Shared language:** `docs/terminologies/circuit-json.md`

---

## 2. Core rules

### 2.1 Inputs

- **MUST** accept validated Topology JSON (`components` + `nets`) from the topology stage/skill.  
- **MUST** resolve geometry from component definition tables / symbol files (not free-hand invention).  
- **MUST NOT** invent pin coordinates when a symbol table exists for that type/orientation.

### 2.2 Outputs

Component Schema JSON **MUST** include, per placed component as required by the skill:

| Field area | Intent |
|------------|--------|
| Component id | Matches topology |
| Orientation | e.g. vertical / horizontal / skill-defined set |
| Size | Width/height from symbol table |
| Center point | Layout center `(x, y)` |
| Connection points | Absolute and/or relative per skill |
| Connection lines | Segments consistent with nets |

### 2.3 Geometry integrity

- Absolute pin = center + relative offset (center-point oriented math).  
- Relative connection points **SHOULD** remain within symbol bounds (`±width/2`, `±height/2`) unless symbol rules say otherwise.  
- Connection lines **MUST** respect net membership from topology (no silent rewiring).

### 2.4 Validation

Emit a **Validation Summary** (counts, missing symbols, orientation coverage).  
**Block** completion if required symbol definitions are missing—ask or create via symbol skill/template first.

---

## 3. Pipeline position

```text
Topology JSON
    → Component Schema JSON  (this template)
    → SVG generation / flatten
```

---

## 4. Protection Rule (Sacred)

Future agents **MUST NOT**:

- Invent symbol geometry when tables/skills define it.  
- Change topology net membership silently during enrichment.  
- Skip validation when schema is claimed ready for SVG.  
- Cite this template as product-source law.  
- Invent missing skill/requirement paths.

---



## Design-time verification

**Law mold:** `LM-CIRCUIT-JSON-COMPONENT-SCHEMA`  
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
**Alignment**: `docs/terminologies/circuit-json.md`, `docs/skills/skill-circuit-json-to-component-schema.md`, `docs/templates/template-circuit-json-topology.md`, `docs/templates/template-circuit-component-symbol.md`, CIAO / CIAO-Lite
