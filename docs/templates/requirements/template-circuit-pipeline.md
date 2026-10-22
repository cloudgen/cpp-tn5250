---
name: circuit-pipeline
id: LM-CIRCUIT-PIPELINE
kind: law-mold
domain_track: domain-circuit
description: >
  Portable law mold. Cite as LM-CIRCUIT-PIPELINE (path secondary). Domain-track circuit/SVG.
---

**file**: template-circuit-pipeline.md  
**Status**: Active (Version 1.0.0 – Circuit track **router** / pipeline index)  
**Project**: Any CIAO-Lite Project with schematic circuit tooling (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

## 1. Purpose

This template is the **pipeline index** for the workspace circuit/SVG track. It does not replace stage templates; it routes agents to the correct specialize-able pattern and skill.

**Shared language:** `docs/terminologies/circuit-json.md`, `docs/terminologies/svg-flatten.md`

---

## 2. Pipeline (disk-truth)

```text
Circuit description
    → Topology JSON
         template: template-circuit-json-topology.md
         skill:    skill-circuit-json-topology-generation.md
    → Component Schema JSON
         template: template-circuit-json-component-schema.md
         skill:    skill-circuit-json-to-component-schema.md
         symbols:  template-circuit-component-symbol.md
                   skill-create-component-symbol.md
    → Schematic SVG
         template: template-circuit-svg-generation.md
         skills:   skill-circuit-svg-generation.md
    → Optional flatten
         template: template-svg-flatten.md
         skill:    skill-svg-flatten.md
```

**MUST** verify each path exists before citing. **MUST NOT** invent stage files.

---

## 3. Disambiguation

| If the user means… | Use |
|--------------------|-----|
| Workspace topology / schema JSON | This pipeline |
| tscircuit industry Circuit JSON (element array) | External spec; not these templates without a converter |
| Only flatten an existing SVG | `template-svg-flatten.md` + flatten skill |

---

## 4. Specialization

- Product law: specialize stage templates into `docs/requirements/requirement-*.md` when acceptance-tested behavior is required.  
- Empty requirements are valid at genesis; skills + templates remain the design harness.  
- Product source cites live requirements only—not this router or skills.

---

## 5. Protection Rule (Sacred)

Future agents **MUST NOT**:

- Skip stages that the requested output depends on (e.g. SVG without schema when schema is required).  
- Treat this router as the full rule body for any single stage.  
- Invent template/skill basenames not on disk.

---



## Design-time verification

**Law mold:** `LM-CIRCUIT-PIPELINE`  
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
**Alignment**: All `template-circuit-*` / `template-svg-flatten.md`, circuit/SVG skills under `docs/skills/`, `docs/terminologies/circuit-json.md`, `docs/terminologies/svg-flatten.md`, CIAO / CIAO-Lite
