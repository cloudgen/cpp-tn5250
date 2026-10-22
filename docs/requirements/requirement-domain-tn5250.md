**file**: docs/requirements/requirement-domain-tn5250.md
**Status**: Active
**Area**: domain
**Key**: requirement-domain-tn5250
**Updated**: 2026-10-22
**Philosophy**: CIAO v2.10.2 / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered / Over-protect)

## 1. Purpose

This file owns the 5250 session inside the GNOME window. The window's main view is the interactive 5250 screen. It is not a WebKit view. The protocol library is `lib5250` at version `0.19.0` (`VERSION` in `config.h`). Product version `1.0.0` stays in `project.h`. `project.h` does not define `VERSION`.

### 1.1 Human-facing

**In one sentence:** You connect to an IBM i host from the GTK window, and the drawing area is the 5250 screen.

| Box | Meaning | Example |
|-----|---------|---------|
| You / this login | The person at the window | You type a host and press Connect |
| The other role | The 5250 session | It speaks the same options as the curses client |
| Not this file | Log lines and install bins | `requirement-cpp-logger.md` and the install requirements |

| Includes | Excludes |
|----------|----------|
| Keys, attributes, terminal types, SSL, maps, trace, macros, ruler, underscores, and `debug:` | Printer daemons `lp5250d`, `scs2ascii`, `scs2pdf`, and `scs2ps` |

## 2. Core rules

### 2.1 Subcommands

Headless verbs run before `gtk_init_check`. They print with `g_print` and do not need a display.

| Verb | What it prints |
|------|----------------|
| `key-plan` | The keyboard map, including Attention, Field Exit, F24, Enter, Roll, and Ctrl+Q |
| `key-check` | `PASS key-check` when keys, attributes, geometry, indicators, and the session form match this file |
| `attribute-plan` | `0 green`, `7 nondisplay`, `16 turquoise`, `31 nondisplay`, and the other attribute names |
| `screen-plan` | `IBM-3179-2 24 80` and `IBM-3477-FC 27 132`, plus the other types below |
| `session-plan` | Passthrough argv after logger flags are removed. No host exits 1 with `session-plan requires a host` |
| `form-plan` | The same options rebuilt from the session form |
| `--version` | `cpp-tn5250 1.0.0` and `tn5250 0.19.0` |
| `--shutdown=N` | Opens the window and leaves after N seconds. Stdout shows `gnome window ready` when `--verbose` is set |

Two plan verbs exit 1 with `one plan command`. Logger flags `--quiet`, `--json`, `--debug`, `--verbose`, `--prefix`, `--home`, and `--log-datestamp` are removed before the tn5250 option parser sees them.

### 2.2 Features

Session startup follows the curses client: load the default config, parse argv, open the stream, configure the display, configure the terminal, optional `debug:` wrap, init, attach the terminal, attach the macro, then `tn5250_session_main_loop`.

The drawing area implements `Tn5250Terminal`. `enhanced()` returns 0. `flags()` returns `TN5250_TERMINAL_HAS_COLOR`. Empty window, scrollbar, and menu callbacks stay installed so a window structured field does not call a null pointer. The same GTK terminal object is reused. Before the display is destroyed, its terminal pointer is cleared when it is that object. A `debug:` wrapper destroys its slave, so the next connect creates a new GTK terminal.

`waitevent` polls the stream socket and iterates the GLib main context, so Disconnect, Ctrl+Q, and the shutdown timer run while the session loop is blocked.

Keys match the curses client with the default parser:

- Return is Enter. Keypad Enter is Field Exit. Keypad + is Field Plus. Keypad - is Field Minus.
- F1 through F12 are F1 through F12. Shift+F1 through Shift+F12 are F13 through F24.
- Page Up rolls down. Page Down rolls up.
- Ctrl+A Attention, Ctrl+C System Request, Ctrl+Q ends the session. Escape or Ctrl+G arms the escape map, including F1 through F24 and the letter aids.
- A mouse click sets the cursor cell.

The attribute index is `(attr - 0x20) & 31`. Index 0 is green. Index 7, 15, 23, and 31 are nondisplay. Index 16 is turquoise. Vertical bars are drawn as underlines. An attribute cell is a blank. Bytes `0x1f` and `0x3f` are a reversed space. Other bytes below `0x40`, and `0xff`, are spaces. The rest go through `tn5250_char_map_to_local`. `+underscores` turns an underlined space into `_`. `+ruler` reverses the cursor row and column.

The status line after the screen shows `5250`, `MW`, `X II`, `X CLOCK`, `X SYSTEM`, `IM`, `FER`, the macro state, and the cursor as `%03d/%03d` at column 72.

Terminal types:

| Type | Rows | Columns |
|------|------|---------|
| `IBM-3179-2` | 24 | 80 |
| `IBM-3196-A1` | 24 | 80 |
| `IBM-5292-2` | 24 | 80 |
| `IBM-5291-1` | 24 | 80 |
| `IBM-5251-11` | 24 | 80 |
| `IBM-3477-FC` | 27 | 132 |
| `IBM-3477-FG` | 27 | 132 |
| `IBM-3180-2` | 27 | 132 |

The library default type is `IBM-3179-2` and the library default map is `37` when the form omits them. SSL prefixes the host with `ssl:` unless it already starts that way. `+ssl_verify_server`, `+ruler`, and `+underscores` are sent only when selected. An explicit off value sends the minus form. `env.DEVNAME` and `trace=` are named fields. Trace opens `tn5250_log_open` when the build is not `NDEBUG`. This product does not define `NDEBUG`.

The curses client also accepts `ssl_ca_file=`, `ssl_cert_file=`, `ssl_pem_pass=`, `ssl_check_exp=`, and any `env.NAME=VALUE`. Those tokens are extra options. The form stores them and appends them after the named fields. `+version` on the curses client is not this product's `--version`.

### 2.5 Sample code (this project)

The same functions are the sample in the domain law mold. `gtkterm_nav_key` and `gtkterm_translate_ctrl` are `src/main/cpp/gtkterm.cpp`. `form_to_args` is `src/main/cpp/gnome_app.cpp`.

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

`SYSCONFDIR` for the config search is `/usr/local/etc`. A missing `tn5250rc` is not an error.

### 2.3 Help

`help` keeps the logger examples, including `--verbose`, `--log-datestamp`, `/var/`, and `/.app/`. After those lines it states that the main view is the interactive 5250 screen and is not a WebKit view, and it names the plan verbs and the keyboard. The window Help menu Keyboard shows the same key plan.

### 2.4 About

The About dialog names `cpp-tn5250`, version `1.0.0`, the tn5250 library `0.19.0`, and the MIT license. The window title is `cpp-tn5250`, and a connected session appends the host.

## 3. Protection rule

Future editors must not replace the drawing area with WebKit or VTE, must not patch `lib5250`, and must not define `VERSION` in `project.h` or `NDEBUG` in the build.

## 4. Related artifacts

| Artifact | Role |
|----------|------|
| `src/main/cpp/gtkterm.cpp` | Terminal, keys, attributes |
| `src/main/cpp/gnome_app.cpp` | Window and session startup |
| `lib5250/` | Protocol library |
| `doc/UPSTREAM-tn5250.md` | Upstream client notes |
| `tests/test-tn5250-terminal.sh` | Headless proof |
| `tests/test-gnome-window.sh` | Window proof |

**Last updated**: 2026-10-22
**Owner**: Domain tn5250
