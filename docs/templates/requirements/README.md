# Requirement templates (law molds)

**Role:** Portable **product-behavior** molds (MUST / MUST NOT, acceptance, protection rules).  
**Specialize into:** `docs/requirements/requirement-*.md` (register in `docs/requirements/index.md`).

**Folder structure policy (SSOT):** [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md)

**Not here:** TP case catalogs, assert code, local-channel recipes → `../tests/`.  
**Not here:** Pass/Fail audit forms → `../checklists/`.

## Naming

| Pattern | Example |
|---------|---------|
| `template-<concern>.md` | `template-shell-cli-zero-arguments.md` |
| Language-prefixed | `template-nodejs-cli-interface.md`, `template-python-error-handling.md` |
| Domain / engine | `template-domain-url-cli.md`, `template-domain-tn5250.md`, `template-download-ytdlp-pipeline.md` |
| Python runtime honesty | `template-python-runtime-prerequisites.md` (not shell Type 1 `template-prerequisites`) |
| **Native C testing** | `template-native-c-testing-strategy.md` (**`LM-NATIVE-C-TESTING-STRATEGY`**), `template-native-c-module-tests.md` (**`LM-NATIVE-C-MODULE-TESTS`**) — proof: `../tests/template-native-c-module-test-plan.md` |

## Cross-links

- Peer law molds: same directory (basename OK).  
- Terminologies: `../../terminologies/`.  
- Proof molds: `../tests/template-*-test-plan.md` (verification pointer only).  
- Checklists: `../checklists/`.

## Authoring reminder

After specialize, product source cites **`requirement-*`**, not these files.

## Design-time verification (tests early)

Every law mold **MUST** declare how it will be proven **before implementation**:

| Step | Artifact |
|------|----------|
| 1. Default TP families / gates | Section **Design-time verification** on this mold |
| 2. Full matrix | `../tests/template-requirement-test-traceability.md` |
| 3. Case catalogs | matching `../tests/template-*-test-plan.md` |
| 4. Product status | specialized REQ + `docs/reviews/test-plan.md` (`todo` → `have`) |

Shell Type O products: at minimum name **TP-CLI** / **TP-LC** / **TP-CURL** (as applicable) when specializing online-install or zero-arguments molds.

## Terminology alignment (mandatory for law molds)

Per [`policy-terminology-for-templates.md`](../../policies/policy-terminology-for-templates.md) and [`policy-ssot-terminology-for-templates.md`](../../policies/policy-ssot-terminology-for-templates.md):

1. Every `template-*.md` **MUST** include a **Terminologies** section (Term | Path | SSOT type | Role).  
2. Paths are **disk-truth** under `docs/terminologies/*.md` only (or create the term same change).  
3. Point — do not paste full definitions.  
4. Always bind at least: `project-templates`, `docs-folder-structure`, `no-hardcode-policy`, `dual-policies`, terminology + SSOT template policies (glossary stubs).  
5. Topic terms match the mold (e.g. online-install → `online-install-script`, empty-argv → `type-o-empty-argv`).  
6. Normative **policy bodies** live under `docs/policies/`; glossary stubs under `docs/terminologies/` may discover them.

**Review:** `skill-template-review` fails missing Terminologies / invented term paths.
