---
name: cpp-coding-style
id: LM-CPP-CODING-STYLE
kind: law-mold
description: >
  Portable law mold. Cite as LM-CPP-CODING-STYLE (path secondary).
---

**file**: docs/templates/requirements/template-cpp-coding-style.md
**Status**: Active (Version 1.1.0 – C++ coding style; declaration sample; bodies stay in LM-OUTPUT-REQUIREMENTS §3.2)
**Project**: {{APP_NAME}} – C++ console program
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered)

**Folder structure (policy):** law/proof/checklists placement follows [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md) (term `docs-folder-structure`). This file is a **law mold** under `docs/templates/requirements/`.

# Template: C++ coding style

## 1. Purpose

This mold is the C++ language body for a project that comes from cpp-template or cpp-gnome-template.

**Specialize-in (software-development):** product law is one Active `requirement-cpp-coding-style.md`. **Without that REQ, agents bring these learned lessons raw.** Term: `coding-style-requirement`. The cross-language router is `template-coding-style.md`. It is not enough as product law.

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
| **Coding-style requirement** | `docs/terminologies/coding-style-requirement.md` | `product-law` | Specialize-in home for these lessons |
| **Kebab-case** | `docs/terminologies/kebab-case.md` | `product-law` | Path tokens |
| **Camel-case** | `docs/terminologies/camel-case.md` | `product-law` | C++ types, methods, and locals |

**SSOT types used:** `meta-catalog` · `policy` · `product-law`

**Policies (normative bodies):** `docs/policies/policy-docs-folder-structure.md` · `docs/policies/policy-terminology-for-templates.md` · `docs/policies/policy-ssot-terminology-for-templates.md` · `docs/policies/policy-no-hardcode.md`

## 2. Language and files

1. The primary language is C++. The standard is C++17. The ship-unit compiler class is `g++`.
2. A translation unit is `.cpp` unless the specialized requirement names a `.c` file.
3. The ship-unit directory is owned by `template-cpp-folder.md`. Do not copy that directory list into this file.
4. A header is `.h` when the folder requirement names that header. Do not rename a named header to `.hpp`.
5. Shell scripts, build files, and Markdown are not translation units.
6. Do not add a GTK or WebKit callback rule from this mold. A window toolkit is out of scope unless a specialized requirement says otherwise.

## 3. Naming

| Spelling | Use it for |
|----------|------------|
| kebab-case | A multi-word path segment or product token the program creates |
| lower camel-case | A C++ method or a C++ local |
| upper camel-case | A C++ type, class, struct, or enum |
| snake_case | An `extern "C"` function, and a function inside a `.c` file that a requirement names |

Do not put a hyphen in a C++ identifier. Do not put a capital letter in a kebab-case token.

## 4. Logger surface

Console lines go through one logger. The prefix map lives in `template-output-requirements.md`.

| Name | Role |
|------|------|
| `logger_info`, `logger_warn`, `logger_error`, `logger_fatal`, `logger_debug`, `logger_log`, `logger_output_init` | Line and startup functions |
| `logger_set_quiet` | Stores quiet mode. When JSON mode is on, the stored value stays on |
| `logger_get_quiet` | Returns the effective quiet flag |
| `logger_get_debug` | Returns the debug flag captured at init |
| `LOGGER_LEVEL_*` | Level tokens |
| `LoggerOutputLevel` | Level type |

There is no `logger_set_debug`. Debug stays a single environment predicate owned by the specialized debug requirement. Do not introduce `ciao_` or `CIAO_` names.

The functions above are `extern "C"` and stay snake_case. That is the specified exception to lower camel-case methods.

`logger_log` takes `va_list` by value. The body uses `va_copy` before `g_strdup_vprintf`. The signature does not go back to `...`.

Well-known levels are `INFO`, `DEBUG`, `WARNING`, `ERROR`, and `FATAL`. The warning token is `WARNING`. There is no `CRITICAL` token. `logger_fatal` does not exit.

The display gate, the dated file, and the function bodies are `LM-OUTPUT-REQUIREMENTS` §3.2 (`template-output-requirements.md`). Do not paste those bodies into this file.

`printf`, `fprintf`, `g_print`, `g_printerr`, and `perror` stay inside the logger translation unit. The console lines use `g_print` and `g_printerr`. The dated-file append may `fprintf` that same human line.

Sample code (this project), from `src/main/cpp/logger.h`. Bodies stay in §3.2.

```cpp
#ifndef LOGGER_H
#define LOGGER_H

#include <stdbool.h>
#include <stdarg.h>
#include <glib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    LOGGER_LEVEL_INFO,
    LOGGER_LEVEL_WARNING,
    LOGGER_LEVEL_ERROR,
    LOGGER_LEVEL_DEBUG,
    LOGGER_LEVEL_FATAL
} LoggerOutputLevel;

void logger_log(LoggerOutputLevel level, const char *format, va_list ap);
void logger_output_init(int argc, char **argv);
int logger_is_test_verb(void);
void logger_set_quiet(bool quiet);
bool logger_get_quiet(void);
bool logger_get_debug(void);
void logger_info(const char *format, ...);
void logger_warn(const char *format, ...);
void logger_error(const char *format, ...);
void logger_fatal(const char *format, ...);
void logger_debug(const char *format, ...);
void logger_print_help(void);

#ifdef __cplusplus
}
#endif

#endif
```

## 5. Comments and visibility

- A function that another file calls is declared in a header and is not `static`.
- A file-local helper is `static`.
- Every function comment states purpose, parameters, dependencies, why this design, CIAO principles, and a protection rule when one applies.

## 6. Protection rule

Future editors must not treat `template-coding-style.md` alone as the C++ body, must not leave the specialized requirement describing C as the primary language, and must not add a debug setter beside `logger_get_debug`.

## Design-time verification

| Gate | Artifact | Phase |
|------|----------|-------|
| Specialize → product suite or checklist | declare TP-IDs or checklist in specialized REQ | Design |
| RTM | `../tests/template-requirement-test-traceability.md` | Design |

When this mold has no executable TP family, mark **n/a** with reason in product `reviews/test-plan.md`.

**Last Updated**: 2026-10-03
**Owner**: {{OWNER}}
**Alignment**: `docs/templates/requirements/template-coding-style.md`, `docs/templates/requirements/template-cpp-folder.md`, `docs/templates/requirements/template-output-requirements.md`, CIAO / CIAO-Lite
