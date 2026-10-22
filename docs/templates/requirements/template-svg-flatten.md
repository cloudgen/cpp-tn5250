---
name: svg-flatten
id: LM-SVG-FLATTEN
kind: law-mold
domain_track: domain-circuit
description: >
  Portable law mold. Cite as LM-SVG-FLATTEN (path secondary). Domain-track circuit/SVG.
---

**file**: template-svg-flatten.md  
**Status**: Active (Version 1.0.0 – Circuit track template; specialize for product law)  
**Project**: Any CIAO-Lite Project shipping schematic SVG for host UI / docs (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

## 1. Purpose

This template defines portable rules for **SVG flatten**: bake translation offsets from offset `<use>` elements, inline referenced geometry into one preferred top-level `<symbol>`, and produce host-UI-safe single-symbol (or equivalent) output **without inventing geometry**.

**Agent harness (when on disk):** `docs/skills/skill-svg-flatten.md`  
**Shared language:** `docs/terminologies/svg-flatten.md`  
**Related generation:** `docs/templates/template-circuit-svg-generation.md`

---

## 2. Core rules

### 2.1 Transform definition

| Step | Rule |
|------|------|
| **Bake** | For `<use x="TX" y="TY">`, add TX/TY to every X/Y coordinate inside the referenced symbol (recursively if nested) |
| **Inline** | Replace `<use>` with baked geometry content |
| **Prefer** | One top-level `<symbol id="…-flatten">`; outer simple `<use>` without layout x/y when a wrapper is needed |
| **Verify** | Mandatory verification tables for non-zero translations: Original → ΔX/ΔY → New; **no negative** artifacts unless already present and intentional |

### 2.2 Non-goals

- **MUST NOT** redesign the schematic or invent new paths while flattening.  
- Flatten is **not** general minification; visual result **MUST** stay pixel-perfect vs composite source.  
- **MUST NOT** confuse CSS transform flattening with this structural bake/inline standard.

### 2.3 When required

- Prefer flatten (or No-Symbol generation) for host UI, chat renderers, and any path known to drop nested `<defs>`/`<use>` chains.  
- Component libraries **MAY** publish `-flatten` variants alongside modular symbols.

### 2.4 Validation

- Produce verification tables + one-line Validation Summary (elements processed, negatives, pixel-perfect confirmation).  
- **Block** claim of complete flatten if tables are omitted for non-zero translations.

---

## 3. Protection Rule (Sacred)

Future agents **MUST NOT**:

- Invent geometry during flatten.  
- Drop verification tables for non-zero translations.  
- Claim flatten when multi-offset `<use>` chains remain for the critical drawing.  
- Cite this template as product-source ALIGNMENT.  
- Invent missing skill/requirement paths.

---



## Design-time verification

**Law mold:** `LM-SVG-FLATTEN`  
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
**Alignment**: `docs/terminologies/svg-flatten.md`, `docs/skills/skill-svg-flatten.md`, `docs/templates/template-circuit-svg-generation.md`, CIAO / CIAO-Lite
