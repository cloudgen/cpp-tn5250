---
name: circuit-component-symbol
id: LM-CIRCUIT-COMPONENT-SYMBOL
kind: law-mold
domain_track: domain-circuit
description: >
  Portable law mold. Cite as LM-CIRCUIT-COMPONENT-SYMBOL (path secondary). Domain-track circuit/SVG.
---

**file**: template-circuit-component-symbol.md  
**Status**: Active (Version 1.0.0 – Circuit track template; specialize for product law)  
**Project**: Any CIAO-Lite Project with schematic symbol libraries (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

## 1. Purpose

This template defines portable rules for **component symbol definition** artifacts (typically Markdown with JSON metadata + SVG) used by topology→schema→SVG pipelines.

**Agent harness (when on disk):** `docs/skills/skill-create-component-symbol.md`  
**Consumers:** component-schema and SVG generation templates/skills  
**Related:** `docs/terminologies/circuit-json.md`, `docs/terminologies/svg-flatten.md`

---

## 2. Core rules

### 2.1 Artifact content

Each symbol definition **MUST** include:

| Element | Intent |
|---------|--------|
| Identity | Component kind + orientation (or orientation variants) |
| Geometry metadata | Size, center point, connection points (relative and/or absolute per skill) |
| SVG | Visual definition consistent with metadata |
| Orientation support | Declared set (e.g. vertical, horizontal, up, down, transistor pin orders, …) |

### 2.2 Consistency

- Connection point names **MUST** match names used in Topology JSON pin references where applicable.  
- Center point is the origin for relative offsets used by layout skills.  
- **MUST NOT** silently change published symbol geometry that downstream designs already reference without versioning/migration notes.

### 2.3 Variants

- Multi-symbol library form and **flatten** (`-flatten`) variants **MAY** ship when host UI or docs require them (see `template-svg-flatten.md`).  
- Suffix rules for multi vs flatten **MUST** stay consistent with `template-circuit-svg-generation.md`.

### 2.4 No invented geometry in reusable layer

Templates/skills **MUST NOT** hardcode a single product’s library path as universal law; use `{{SYMBOL_LIBRARY_DIR}}` / project Selection tables when specializing.

---

## 3. Protection Rule (Sacred)

Future agents **MUST NOT**:

- Emit symbol files without connection metadata required by schema conversion.  
- Drift pin names between symbols and topology without an explicit rename plan.  
- Cite this template as product-source ALIGNMENT.  
- Invent missing skill/requirement paths.

---



## Design-time verification

**Law mold:** `LM-CIRCUIT-COMPONENT-SYMBOL`  
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
**Alignment**: `docs/skills/skill-create-component-symbol.md`, `docs/templates/template-circuit-json-component-schema.md`, `docs/templates/template-svg-flatten.md`, CIAO / CIAO-Lite
