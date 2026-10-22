---
name: domain-tn5250
id: LM-DOMAIN-TN5250
kind: law-mold
description: >
  Law mold for a GNOME 5250 terminal whose main view replaces a web view.
  Cite as LM-DOMAIN-TN5250 (path secondary). Specialize to requirement-domain-tn5250.md.
---

**file**: docs/templates/requirements/template-domain-tn5250.md
**Status**: Active (Version 1.0.0)
**Project**: cpp-tn5250
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered / Over-protect)

# Template: Domain surface — GNOME 5250 terminal

## 1. Purpose

This mold owns the 5250 session inside the GTK window. The window's main view is the interactive 5250 screen. Product law is one Active `requirement-domain-tn5250.md`. Printer daemons stay outside this mold.

The coverage list is the curses client's option syntax: `map=`, `env.DEVNAME=`, `trace=`, `ssl:` plus `+ssl_verify_server`, `ssl_ca_file=`, `ssl_cert_file=`, `ssl_pem_pass=`, `ssl_check_exp=`, `+underscores`, `+ruler`, `env.TERM=`, and any other `env.NAME=VALUE`.

## 2. Sample code (this project)

These functions are the ship unit. The same text is the sample in `requirement-domain-tn5250.md`. `gtkterm_nav_key` and `gtkterm_translate_ctrl` are `src/main/cpp/gtkterm.cpp`. `form_to_args` is `src/main/cpp/gnome_app.cpp`.

```cpp
static int gtkterm_nav_key(unsigned keyval)
{
    switch (keyval) {
    case GDK_KEY_Left:
    case GDK_KEY_KP_Left:
        return K_LEFT;
    case GDK_KEY_Right:
    case GDK_KEY_KP_Right:
        return K_RIGHT;
    case GDK_KEY_Up:
    case GDK_KEY_KP_Up:
        return K_UP;
    case GDK_KEY_Down:
    case GDK_KEY_KP_Down:
        return K_DOWN;
    case GDK_KEY_Home:
    case GDK_KEY_KP_Home:
        return K_HOME;
    case GDK_KEY_End:
    case GDK_KEY_KP_End:
        return K_END;
    case GDK_KEY_Page_Up:
    case GDK_KEY_KP_Page_Up:
        return K_ROLLDN;
    case GDK_KEY_Page_Down:
    case GDK_KEY_KP_Page_Down:
        return K_ROLLUP;
    case GDK_KEY_Insert:
    case GDK_KEY_KP_Insert:
        return K_INSERT;
    case GDK_KEY_KP_Add:
        return K_FIELDPLUS;
    case GDK_KEY_KP_Subtract:
        return K_FIELDMINUS;
    default:
        return 0;
    }
}
```

```cpp
static int gtkterm_translate_ctrl(unsigned keyval, int *key_out, int *quit_out)
{
    switch (gtkterm_upper_key(keyval)) {
    case GDK_KEY_A: *key_out = K_ATTENTION; return 1;
    case GDK_KEY_B: *key_out = K_ROLLDN; return 1;
    case GDK_KEY_C: *key_out = K_SYSREQ; return 1;
    case GDK_KEY_D: *key_out = K_ROLLUP; return 1;
    case GDK_KEY_E: *key_out = K_ERASE; return 1;
    case GDK_KEY_F: *key_out = K_ROLLUP; return 1;
    case GDK_KEY_H: *key_out = K_BACKSPACE; return 1;
    case GDK_KEY_K: *key_out = K_FIELDEXIT; return 1;
    case GDK_KEY_L: *key_out = K_REFRESH; return 1;
    case GDK_KEY_O: *key_out = K_HOME; return 1;
    case GDK_KEY_P: *key_out = K_PRINT; return 1;
    case GDK_KEY_Q: *quit_out = 1; return 1;
    case GDK_KEY_R: *key_out = K_RESET; return 1;
    case GDK_KEY_S: *key_out = K_MEMO; return 1;
    case GDK_KEY_T: *key_out = K_TESTREQ; return 1;
    case GDK_KEY_U: *key_out = K_ROLLDN; return 1;
    case GDK_KEY_W: *key_out = K_EXEC; return 1;
    case GDK_KEY_X: *key_out = K_FIELDPLUS; return 1;
    default: return 0;
    }
}
```

```cpp
static int form_to_args(const struct session_form *form, char **args, int max_args)
{
    int count = 0;
    char host[600];
    int extra_count = 0;
    char **extra_argv = NULL;
    GError *error = NULL;
    int index;

    if (form->host[0] == '\0') {
        return -1;
    }
    if (push_pair(args, &count, max_args, "map", form->map_name) != 0 ||
        push_pair(args, &count, max_args, "env.TERM", form->term_type) != 0 ||
        push_pair(args, &count, max_args, "env.DEVNAME", form->devname) != 0 ||
        push_pair(args, &count, max_args, "trace", form->trace) != 0 ||
        push_flag(args, &count, max_args, form->ssl_verify, "ssl_verify_server") != 0 ||
        push_flag(args, &count, max_args, form->underscores, "underscores") != 0 ||
        push_flag(args, &count, max_args, form->ruler, "ruler") != 0) {
        return -1;
    }
    if (form->extra[0] != '\0') {
        if (!g_shell_parse_argv(form->extra, &extra_count, &extra_argv, &error)) {
            if (error != NULL) {
                g_error_free(error);
            }
            if (push_arg(args, &count, max_args, form->extra) != 0) {
                return -1;
            }
        } else {
            for (index = 0; index < extra_count; index++) {
                if (push_arg(args, &count, max_args, extra_argv[index]) != 0) {
                    g_strfreev(extra_argv);
                    return -1;
                }
            }
            g_strfreev(extra_argv);
        }
    }
    if (form->ssl && strncmp(form->host, "ssl:", 4) != 0) {
        snprintf(host, sizeof host, "ssl:%s", form->host);
    } else {
        snprintf(host, sizeof host, "%s", form->host);
    }
    if (push_arg(args, &count, max_args, host) != 0) {
        return -1;
    }
    return count;
}
```

## 3. Protection rule

Future editors must not replace the drawing area with WebKit or VTE, must not patch `lib5250`, and must not let this sample drift from the ship unit.

## Design-time verification

| Gate | Artifact |
|------|----------|
| Headless option round trip | `tests/test-tn5250-terminal.sh` |
| Window open | `tests/test-gnome-window.sh` |

**Last Updated**: 2026-10-22
**Owner**: Domain tn5250
