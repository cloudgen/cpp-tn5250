---
name: circuit-svg-generation
id: LM-CIRCUIT-SVG-GENERATION
kind: law-mold
domain_track: domain-circuit
description: >
  Portable law mold. Cite as LM-CIRCUIT-SVG-GENERATION (path secondary). Domain-track circuit/SVG.
---

**file**: template-circuit-svg-generation.md  
**Status**: Active (Version 1.0.0 – Circuit track template; specialize for product law)  
**Project**: Any CIAO-Lite Project generating schematic SVG (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

## 1. Purpose

This template defines portable rules for **schematic SVG generation** from geometry-aware data (Component Schema JSON / Design JSON) and symbol libraries, including the **three-tier SVG model**.

**Agent harnesses (when on disk):**  
- `docs/skills/skill-circuit-svg-generation.md` (**sole** SVG generation skill)  

**Upstream:** `template-circuit-json-component-schema.md`  
**Flatten:** `template-svg-flatten.md`  
**Terms:** `docs/terminologies/circuit-json.md`, `docs/terminologies/svg-flatten.md`

---

## 2. Three-tier SVG model

| Tier | Form | Typical suffix | Host UI safety |
|------|------|----------------|----------------|
| Multi-symbol | Many `<symbol>` + offset `<use>` | `-multi` | Lower (modular library) |
| Single-symbol / flatten | One master `<symbol id="…-flatten">`, offsets baked | `-flatten` | Medium–high |
| **No-symbol (default)** | No `<defs>`/`<symbol>`/`<use>`; primitives under root `<svg>` | (none) | **Highest** — default for generated circuit diagrams |

**Default for full circuit diagrams:** **No-Symbol** tier unless the user or specialized requirement selects another tier.

---

## 3. Core rules

### 3.1 Center-point math

- Every absolute coordinate **MUST** follow: `component_center + relative_offset`.  
- Moving a component **MUST** update dependent wires via the same rule (no orphan absolute pins).

### 3.2 Naming

- Every generated SVG **MUST** carry a versioned design title pattern such as `design_title_v{version}` in `<title>` (and recommended filename).  
- Symbol reuse **MUST** honor suffix rules (`-multi`, `-flatten`) without mutating immutable library geometry in place.

### 3.3 Design JSON (traceability)

When the skill requires it, maintain machine-readable design data (centers, connections, chosen `svg_type` / tier) as SSOT for the drawing.

### 3.4 Prefer flatten / no-symbol for fragile hosts

- For critical display paths, prefer **No-Symbol** or **Flatten** over deep multi-`<use>` chains.  
- Use `template-svg-flatten.md` / flatten skill when converting composite → single-symbol.

### 3.5 Validation

Emit Validation Summary + center-point table when required by the skill.  
**MUST NOT** invent polarity, pins, or nets not present in upstream schema/topology.

---

## 4. Pipeline position

```text
Component Schema JSON + symbols
    → Schematic SVG (this template)
    → optional flatten (template-svg-flatten)
```

---

## 5. Protection Rule (Sacred)

Future agents **MUST NOT**:

- Default to fragile multi-symbol output when No-Symbol is the project default and host UI is known fragile.  
- Break center-point oriented calculation.  
- Modify library symbol internal geometry while “generating” a circuit (reuse, don’t rewrite).  
- Cite this template as product-source law.  
- Invent missing skill/requirement paths.

---



## Design-time verification

**Law mold:** `LM-CIRCUIT-SVG-GENERATION`  
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
**Alignment**: `docs/skills/skill-circuit-svg-generation.md`, `docs/templates/template-svg-flatten.md`, `docs/terminologies/svg-flatten.md`, CIAO / CIAO-Lite
