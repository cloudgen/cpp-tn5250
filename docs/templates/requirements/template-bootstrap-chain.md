---
name: bootstrap-chain
id: LM-BOOTSTRAP-CHAIN
kind: law-mold
description: >
  Portable law mold. Cite as LM-BOOTSTRAP-CHAIN (path secondary).
---

**file**: template-bootstrap-chain.md  
**Status**: Active (Version 1.0.0)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered / Over-protect)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

## 1. Purpose

This template defines the portable **bootstrap chain** pattern: how to **declare, maintain, and change** an ordered product lineage under architecture inheritance (ancestor → descendant only).

**Shared language (terminology):**

| Term | File |
|------|------|
| **Bootstrap chain** | `docs/terminologies/bootstrap-chain.md` |
| Bootstrap origin | `docs/terminologies/bootstrap-origin.md` |
| Bootstrap specialize product | `docs/terminologies/bootstrap-specialize-product.md` |
| Bootstrap origin review | `docs/terminologies/bootstrap-origin-review.md` |
| Architecture inheritance | `docs/terminologies/architecture-inheritance.md` |
| Reverse-copy pollution | `docs/terminologies/reverse-copy-pollution.md` |
| Domain surface | `docs/terminologies/domain-surface.md` |
| Ship unit | `docs/terminologies/ship-unit.md` |

**Related templates / checklists (do not duplicate ownership):**

| Topic | Artifact |
|-------|----------|
| One-edge specialize A→B | `template` peers via skill `skill-bootstrap-specialize-product` · `checklist-bootstrap-specialize-product.md` |
| Origin review from revision report | `checklist-bootstrap-origin-review.md` · skill `skill-bootstrap-origin-review` |
| Shell Type 0 inheritance surfaces | `template-self-management.md`, `template-online-install.md`, `template-output-requirements.md`, `template-modular-function-design.md`, `template-shell-cli-zero-arguments.md`, `template-automatic-checksum.md` |
| Shell CLI entry gate (not chain) | shell-cli-bootstrap term · online-install bootstrap sections |

**Specialize into:** a project `requirement-bootstrap-chain.md` (or area-prefixed variant) with a **filled hop table** for *this* product’s lineage.

---

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
| **Bootstrap chain** | `docs/terminologies/bootstrap-chain.md` | `product-law` | Multi-hop specialize chain |
| **Bootstrap specialize product** | `docs/terminologies/bootstrap-specialize-product.md` | `product-law` | A→B specialize |
| **Genesis template** | `docs/terminologies/genesis-template.md` | `product-law` | Blank harness seed class |

**SSOT types used:** `meta-catalog` · `policy` · `product-law`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Core Concepts

| Concept | Meaning |
|---------|---------|
| **Hop** | One product position on the chain (has identity, optional ship unit, optional law notes) |
| **Edge** | One specialization step parent → child (A→B) |
| **Root** | First hop in the declared chain |
| **Immediate origin** | Direct parent of the product under discussion |
| **Leaf** | End product currently specialized for users / primary review target |
| **Chain declaration** | Explicit ordered list of hops (not inferred only from git log) |
| **Down-chain re-specialize** | After fixing an ancestor, rebuild/refresh descendants A→B only |

**Must not confuse with:**

| Concept | Not the same as |
|---------|-----------------|
| Bootstrap chain | Shell entry gate / pipe bootstrap |
| Chain hop | Random sibling repo without parentage |
| Fix shared bug on leaf only forever | Leave ancestor dirty for next specialization |
| Reverse-copy “sync” | Correct down-chain re-specialize |

---

## 3. Core Rules (Mandatory when a chain is claimed)

### 3.1 Direction

1. Every edge **MUST** be **ancestor → descendant** only.  
2. Plans **MUST NOT** copy a descendant ship unit onto an ancestor path to “share fixes.”  
3. Detected reverse-copy **MUST** be treated as critical pollution (restore ancestor; rebuild child).

### 3.2 Declaration

When a project claims multi-product specialization lineage, it **MUST** declare:

| Field | Required |
|-------|----------|
| Ordered hop list (names) | Yes |
| Root hop | Yes |
| Leaf hop (this product when specialized) | Yes |
| Immediate origin of the leaf | Yes (may equal root on one-edge chains) |
| Ship unit path per hop (or “external / not in tree”) | Yes |
| Channel / script-url ownership per hop | Yes when online install is in scope |
| Domain present? per hop | Yes (yes/no/summary) |

Portable placeholders: `{{CHAIN_HOP_0}}` … `{{CHAIN_HOP_N}}`, `{{BOOTSTRAP_APP}}`, `{{PRODUCT_APP}}`.

### 3.3 Per-edge inheritance

For each edge A→B, B **MUST**:

1. **Inherit** A’s structural architecture contracts (output SSOT family, install/lifecycle family, entry gate, empty-argv type, integrity pattern, modular prefixes — as applicable to product type).  
2. **Retarget** identity and install channel for B only.  
3. **Extend** domain only on B (or document intentional domain-thin B).  
4. Keep **distinct** ship unit and tests ownership from A.

### 3.4 Shared defect handling

| Situation | Required approach |
|-----------|-------------------|
| Defect in shared architecture surface | Prefer fix on **earliest responsible hop**; then re-specialize down if descendants need the fix |
| Defect only in leaf domain | Fix leaf only; do not push domain DNA onto ancestors |
| Leaf report used to audit parent | Use origin-review classification; require parent path:line evidence |
| “Fix parent by pasting leaf” | Forbidden (reverse-copy) |

### 3.5 Documentation SSOT for the chain

| Surface | Owns |
|---------|------|
| Specialized requirement | Enforceable hop table + rules for *this* project |
| Product source comments | May name live requirement key only — not harness paths |
| README | Optional human-facing “specialized from …” line; must not reverse direction language |
| Ship unit headers | May note immediate bootstrap honestly; must not claim reverse parentage |

### 3.6 What a chain is not required to be

- Not every monorepo folder  
- Not git branch topology alone  
- Not external dependency graphs (use upstream analysis when those matter)  
- Not shell CLI bootstrap / Type 1 host bootstrap

---

## 4. Specialization sketch (Implementation Notes)

When specializing, fill:

### 4.1 Hop table

| # | Hop name | Position | Ship unit path | Channel owner | Domain? | Notes |
|---|----------|----------|----------------|---------------|---------|-------|
| 0 | `{{CHAIN_HOP_0}}` | root | … | … | no / thin | … |
| 1 | `{{CHAIN_HOP_1}}` | intermediate / immediate | … | … | yes | … |
| N | `{{PRODUCT_APP}}` | leaf | `./{{PRODUCT_APP}}` | … | yes | this product |

### 4.2 Edges

| Edge | Inherit contracts | Retarget identity/channel | Domain extend |
|------|-------------------|---------------------------|---------------|
| hop0 → hop1 | yes | yes | … |
| hop1 → leaf | yes | yes | … |

### 4.3 Origin-review defaults

| Default | Value |
|---------|-------|
| Default origin-review hop for leaf reports | immediate / root / ask |
| Multi-hop review policy | … |

### 4.4 Forbidden reverse statements (examples to ban in product docs)

- “Bootstrap was created by trimming the specialized product”  
- “Update origin by copying leaf then rename”  

---

## 5. Checklist sketch (agent gate)

- [ ] Ordered hops named  
- [ ] Root and leaf identified  
- [ ] Immediate origin of leaf identified  
- [ ] Direction A→B only on every edge  
- [ ] No reverse-copy plan  
- [ ] Ship units / channels not merged by accident  
- [ ] Shared bugs assigned to responsible hop  
- [ ] Requirement registered when chain is product law  

Blank form companion (when on disk): `docs/templates/checklists/checklist-bootstrap-chain.md`.

---

## 6. CIAO alignment (portable)

| Letter / principle | Application |
|--------------------|-------------|
| **Caution** | Do not assume parentage; declare hops; fail closed on reverse direction |
| **Intentional** | Every edge has inherit / retarget / domain decisions |
| **Anti-fragile** | Multi-hop survival; fix ancestor so future specializations stay healthy |
| **Over-protect** | Direction and reverse-copy rules are Protection Zone material |
| **SSOT** | One declared hop table in specialized requirement |
| **Protect against AI** | Ban reverse-copy “sync” language and wrong-parent rewrites |

---

## 7. Protection Rule (template sacred)

When this pattern is specialized, agents **MUST NOT**:

1. Reverse-copy a descendant onto an ancestor.  
2. Leave the hop table empty while claiming a multi-product bootstrap lineage.  
3. Treat shell entry bootstrap or genesis wipe as the product chain.  
4. Merge install channels of distinct hops without explicit authorization.  
5. Push leaf domain DNA into root “cleanup.”  

---


## Design-time verification

| Gate | Artifact | Phase |
|------|----------|-------|
| Specialize → product suite or checklist | declare TP-IDs or checklist in specialized REQ | Design |
| RTM | `../tests/template-requirement-test-traceability.md` | Design |

When this mold has no executable TP family, mark **n/a** with reason in product `reviews/test-plan.md`.

**Last Updated**: 2026-07-15  
**Owner**: {{OWNER}}  
**Alignment**: term `bootstrap-chain`; specialize / origin-review skills; architecture-inheritance; reverse-copy-pollution
