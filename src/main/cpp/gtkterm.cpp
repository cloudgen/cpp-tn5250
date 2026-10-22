// gtkterm.cpp
// Draws the 5250 display and maps keys the same way the curses client does.
// The widget replaces a WebKit view. It is not a web view.

#define _TN5250_TERMINAL_PRIVATE_DEFINED
#include "tn5250-private.h"
#include "gtkterm.h"

#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <string.h>
#include <stdio.h>

#define GTKTERM_MAX_COLS 132
#define GTKTERM_MAX_ROWS 27
#define GTKTERM_KEYQ 64

enum gtkterm_color {
    GTKTERM_GREEN = 0,
    GTKTERM_WHITE,
    GTKTERM_RED,
    GTKTERM_TURQUOISE,
    GTKTERM_YELLOW,
    GTKTERM_PINK,
    GTKTERM_BLUE
};

struct gtkterm_attr {
    unsigned char color;
    unsigned char reverse;
    unsigned char underline;
    unsigned char blink;
    unsigned char hidden;
    const char *name;
};

struct gtkterm_cell {
    char text[4];
    unsigned char color;
    unsigned char reverse;
    unsigned char underline;
    unsigned char blink;
};

struct _Tn5250TerminalPrivate {
    GtkWidget *widget;
    Tn5250Display *display;
    int underscores;
    int ruler;
    int quit_flag;
    int escape_pending;
    int key_queue[GTKTERM_KEYQ];
    int key_head;
    int key_tail;
    int cols;
    int rows;
    int cursor_x;
    int cursor_y;
    int cell_w;
    int cell_h;
    int blink_on;
    char status[96];
    struct gtkterm_cell cells[GTKTERM_MAX_ROWS][GTKTERM_MAX_COLS];
};

static const struct gtkterm_attr k_attrs[32] = {
    { GTKTERM_GREEN, 0, 0, 0, 0, "green" },
    { GTKTERM_GREEN, 1, 0, 0, 0, "green-reverse" },
    { GTKTERM_WHITE, 0, 0, 0, 0, "white" },
    { GTKTERM_WHITE, 1, 0, 0, 0, "white-reverse" },
    { GTKTERM_GREEN, 0, 1, 0, 0, "green-underline" },
    { GTKTERM_GREEN, 1, 1, 0, 0, "green-underline-reverse" },
    { GTKTERM_WHITE, 0, 1, 0, 0, "white-underline" },
    { GTKTERM_GREEN, 0, 0, 0, 1, "nondisplay" },
    { GTKTERM_RED, 0, 0, 0, 0, "red" },
    { GTKTERM_RED, 1, 0, 0, 0, "red-reverse" },
    { GTKTERM_RED, 0, 0, 1, 0, "red-blink" },
    { GTKTERM_RED, 1, 0, 1, 0, "red-blink-reverse" },
    { GTKTERM_RED, 0, 1, 0, 0, "red-underline" },
    { GTKTERM_RED, 1, 1, 0, 0, "red-underline-reverse" },
    { GTKTERM_RED, 0, 1, 1, 0, "red-underline-blink" },
    { GTKTERM_GREEN, 0, 0, 0, 1, "nondisplay" },
    { GTKTERM_TURQUOISE, 0, 1, 0, 0, "turquoise" },
    { GTKTERM_TURQUOISE, 1, 1, 0, 0, "turquoise-reverse" },
    { GTKTERM_YELLOW, 0, 1, 0, 0, "yellow" },
    { GTKTERM_YELLOW, 1, 1, 0, 0, "yellow-reverse" },
    { GTKTERM_TURQUOISE, 0, 1, 0, 0, "turquoise-underline" },
    { GTKTERM_TURQUOISE, 1, 1, 0, 0, "turquoise-underline-reverse" },
    { GTKTERM_YELLOW, 0, 1, 0, 0, "yellow-underline" },
    { GTKTERM_GREEN, 0, 0, 0, 1, "nondisplay" },
    { GTKTERM_PINK, 0, 0, 0, 0, "pink" },
    { GTKTERM_PINK, 1, 0, 0, 0, "pink-reverse" },
    { GTKTERM_BLUE, 0, 0, 0, 0, "blue" },
    { GTKTERM_BLUE, 1, 0, 0, 0, "blue-reverse" },
    { GTKTERM_PINK, 0, 1, 0, 0, "pink-underline" },
    { GTKTERM_PINK, 1, 1, 0, 0, "pink-underline-reverse" },
    { GTKTERM_BLUE, 0, 1, 0, 0, "blue-underline" },
    { GTKTERM_GREEN, 0, 0, 0, 1, "nondisplay" }
};

static const char *k_key_plan =
    "Enter sends the screen (K_ENTER).\n"
    "Keypad Enter is Field Exit.\n"
    "Keypad + is Field Plus. Keypad - is Field Minus.\n"
    "Tab and Shift+Tab move between fields.\n"
    "F1 through F12 are F1 through F12.\n"
    "Shift+F1 through Shift+F12 are F13 through F24.\n"
    "Roll down is Page Up. Roll up is Page Down.\n"
    "Ctrl+A Attention.\n"
    "Ctrl+B roll down. Ctrl+D or Ctrl+F roll up. Ctrl+U roll down.\n"
    "Ctrl+C System Request. Ctrl+E Erase. Ctrl+H Backspace.\n"
    "Ctrl+K Field Exit. Ctrl+L Refresh. Ctrl+O Home. Ctrl+P Print.\n"
    "Ctrl+R Reset. Ctrl+S macro record. Ctrl+T Test Request.\n"
    "Ctrl+W macro execute. Ctrl+X Field Plus.\n"
    "Ctrl+Q ends the session.\n"
    "Escape, or Ctrl+G, then 1 through 0, -, = selects F1 through F12.\n"
    "Escape then ! @ # $ % ^ & * ( ) _ + selects F13 through F24.\n"
    "Escape then A Attention, C Clear, D Duplicate, H Help, I Insert,\n"
    "L Refresh, M Field Minus, P Print, R Reset, S System Request,\n"
    "T Toggle, X Field Exit, Q end the session.\n"
    "Escape then Ctrl+U next field, Ctrl+H previous field, Ctrl+F field home,\n"
    "Ctrl+J newline.\n"
    "A mouse click moves the cursor.\n";

static const char *k_screen_plan =
    "IBM-3179-2 24 80\n"
    "IBM-3196-A1 24 80\n"
    "IBM-5292-2 24 80\n"
    "IBM-5291-1 24 80\n"
    "IBM-5251-11 24 80\n"
    "IBM-3477-FC 27 132\n"
    "IBM-3477-FG 27 132\n"
    "IBM-3180-2 27 132\n";

static void gtkterm_rgb(int color, double *red, double *green, double *blue)
{
    switch (color) {
    case GTKTERM_WHITE: *red = 1; *green = 1; *blue = 1; break;
    case GTKTERM_RED: *red = 1; *green = 0.25; *blue = 0.25; break;
    case GTKTERM_TURQUOISE: *red = 0; *green = 0.85; *blue = 0.85; break;
    case GTKTERM_YELLOW: *red = 1; *green = 1; *blue = 0.2; break;
    case GTKTERM_PINK: *red = 1; *green = 0.45; *blue = 0.75; break;
    case GTKTERM_BLUE: *red = 0.35; *green = 0.55; *blue = 1; break;
    default: *red = 0; *green = 1; *blue = 0; break;
    }
}

static void gtkterm_store_byte(struct gtkterm_cell *cell, unsigned char glyph)
{
    if (glyph < 0x80) {
        cell->text[0] = (char)glyph;
        cell->text[1] = '\0';
    } else {
        cell->text[0] = (char)(0xc0 | (glyph >> 6));
        cell->text[1] = (char)(0x80 | (glyph & 0x3f));
        cell->text[2] = '\0';
    }
}

static void gtkterm_blank(struct _Tn5250TerminalPrivate *data)
{
    int row;
    int col;

    for (row = 0; row < data->rows; row++) {
        for (col = 0; col < data->cols; col++) {
            struct gtkterm_cell *cell = &data->cells[row][col];
            gtkterm_store_byte(cell, ' ');
            cell->color = GTKTERM_GREEN;
            cell->reverse = 0;
            cell->underline = 0;
            cell->blink = 0;
        }
    }
}

static void gtkterm_queue(Tn5250Terminal *term)
{
    if (term->data->widget != NULL) {
        gtk_widget_queue_draw(term->data->widget);
        gtk_widget_set_size_request(term->data->widget,
                                    term->data->cols * term->data->cell_w,
                                    (term->data->rows + 1) * term->data->cell_h);
    }
}

static int gtkterm_push_key(struct _Tn5250TerminalPrivate *data, int key)
{
    int next = (data->key_tail + 1) % GTKTERM_KEYQ;
    if (next == data->key_head) {
        return 0;
    }
    data->key_queue[data->key_tail] = key;
    data->key_tail = next;
    return 1;
}

static int gtkterm_pop_key(struct _Tn5250TerminalPrivate *data)
{
    int key;
    if (data->key_head == data->key_tail) {
        return -1;
    }
    key = data->key_queue[data->key_head];
    data->key_head = (data->key_head + 1) % GTKTERM_KEYQ;
    return key;
}

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

static unsigned gtkterm_upper_key(unsigned keyval)
{
    if (keyval >= GDK_KEY_a && keyval <= GDK_KEY_z) {
        return keyval - GDK_KEY_a + GDK_KEY_A;
    }
    return keyval;
}

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

static int gtkterm_translate_escape(unsigned keyval, unsigned state, int *key_out, int *quit_out)
{
    unsigned key;

    if ((state & GDK_CONTROL_MASK) != 0) {
        switch (gtkterm_upper_key(keyval)) {
        case GDK_KEY_U: *key_out = K_NEXTFLD; return 1;
        case GDK_KEY_H: *key_out = K_PREVFLD; return 1;
        case GDK_KEY_F: *key_out = K_FIELDHOME; return 1;
        case GDK_KEY_J: *key_out = K_NEWLINE; return 1;
        default: return 0;
        }
    }
    if (keyval == GDK_KEY_Delete || keyval == GDK_KEY_KP_Delete) {
        *key_out = K_INSERT;
        return 1;
    }
    key = gtkterm_upper_key(keyval);
    switch (key) {
    case GDK_KEY_1: *key_out = K_F1; return 1;
    case GDK_KEY_2: *key_out = K_F2; return 1;
    case GDK_KEY_3: *key_out = K_F3; return 1;
    case GDK_KEY_4: *key_out = K_F4; return 1;
    case GDK_KEY_5: *key_out = K_F5; return 1;
    case GDK_KEY_6: *key_out = K_F6; return 1;
    case GDK_KEY_7: *key_out = K_F7; return 1;
    case GDK_KEY_8: *key_out = K_F8; return 1;
    case GDK_KEY_9: *key_out = K_F9; return 1;
    case GDK_KEY_0: *key_out = K_F10; return 1;
    case GDK_KEY_minus: *key_out = K_F11; return 1;
    case GDK_KEY_equal: *key_out = K_F12; return 1;
    case GDK_KEY_exclam: *key_out = K_F13; return 1;
    case GDK_KEY_at: *key_out = K_F14; return 1;
    case GDK_KEY_numbersign: *key_out = K_F15; return 1;
    case GDK_KEY_dollar: *key_out = K_F16; return 1;
    case GDK_KEY_percent: *key_out = K_F17; return 1;
    case GDK_KEY_asciicircum: *key_out = K_F18; return 1;
    case GDK_KEY_ampersand: *key_out = K_F19; return 1;
    case GDK_KEY_asterisk: *key_out = K_F20; return 1;
    case GDK_KEY_parenleft: *key_out = K_F21; return 1;
    case GDK_KEY_parenright: *key_out = K_F22; return 1;
    case GDK_KEY_underscore: *key_out = K_F23; return 1;
    case GDK_KEY_plus: *key_out = K_F24; return 1;
    case GDK_KEY_A: *key_out = K_ATTENTION; return 1;
    case GDK_KEY_C: *key_out = K_CLEAR; return 1;
    case GDK_KEY_D: *key_out = K_DUPLICATE; return 1;
    case GDK_KEY_H: *key_out = K_HELP; return 1;
    case GDK_KEY_I: *key_out = K_INSERT; return 1;
    case GDK_KEY_L: *key_out = K_REFRESH; return 1;
    case GDK_KEY_M: *key_out = K_FIELDMINUS; return 1;
    case GDK_KEY_P: *key_out = K_PRINT; return 1;
    case GDK_KEY_R: *key_out = K_RESET; return 1;
    case GDK_KEY_S: *key_out = K_SYSREQ; return 1;
    case GDK_KEY_T: *key_out = K_TOGGLE; return 1;
    case GDK_KEY_X: *key_out = K_FIELDEXIT; return 1;
    case GDK_KEY_Q: *quit_out = 1; return 1;
    default: return 0;
    }
}

extern "C" {

int gtkterm_translate(unsigned keyval, unsigned state, int *escape_pending,
                      int *key_out, int *quit_out)
{
    int nav;

    *quit_out = 0;
    if (*escape_pending) {
        *escape_pending = 0;
        return gtkterm_translate_escape(keyval, state, key_out, quit_out);
    }
    if (keyval == GDK_KEY_Escape ||
        ((state & GDK_CONTROL_MASK) != 0 && gtkterm_upper_key(keyval) == GDK_KEY_G)) {
        *escape_pending = 1;
        return 0;
    }
    if ((state & GDK_CONTROL_MASK) != 0 && (state & GDK_MOD1_MASK) == 0) {
        return gtkterm_translate_ctrl(keyval, key_out, quit_out);
    }
    if ((state & GDK_MOD1_MASK) != 0) {
        return 0;
    }
    nav = gtkterm_nav_key(keyval);
    if (nav != 0) {
        *key_out = nav;
        return 1;
    }
    if ((state & GDK_SHIFT_MASK) != 0 && keyval >= GDK_KEY_F1 && keyval <= GDK_KEY_F12) {
        *key_out = K_F13 + (int)(keyval - GDK_KEY_F1);
        return 1;
    }
    if (keyval >= GDK_KEY_F1 && keyval <= GDK_KEY_F12) {
        *key_out = K_F1 + (int)(keyval - GDK_KEY_F1);
        return 1;
    }
    if (keyval == GDK_KEY_Return) {
        *key_out = K_ENTER;
        return 1;
    }
    if (keyval == GDK_KEY_KP_Enter) {
        *key_out = K_FIELDEXIT;
        return 1;
    }
    if (keyval == GDK_KEY_ISO_Left_Tab ||
        (keyval == GDK_KEY_Tab && (state & GDK_SHIFT_MASK) != 0)) {
        *key_out = K_BACKTAB;
        return 1;
    }
    if (keyval == GDK_KEY_Tab) {
        *key_out = K_TAB;
        return 1;
    }
    if (keyval == GDK_KEY_BackSpace) {
        *key_out = K_BACKSPACE;
        return 1;
    }
    if (keyval == GDK_KEY_Delete || keyval == GDK_KEY_KP_Delete) {
        *key_out = K_DELETE;
        return 1;
    }
    if (keyval >= GDK_KEY_KP_0 && keyval <= GDK_KEY_KP_9) {
        *key_out = '0' + (int)(keyval - GDK_KEY_KP_0);
        return 1;
    }
    if (keyval == GDK_KEY_KP_Decimal) {
        *key_out = '.';
        return 1;
    }
    if (keyval >= 0x20 && keyval <= 0xff) {
        *key_out = (int)keyval;
        return 1;
    }
    return 0;
}

void gtkterm_geometry_for_type(const char *type_name, int *rows, int *cols)
{
    *rows = 24;
    *cols = 80;
    if (type_name == NULL || type_name[0] == '\0') {
        return;
    }
    if (strcmp(type_name, "IBM-3477-FC") == 0 ||
        strcmp(type_name, "IBM-3477-FG") == 0 ||
        strcmp(type_name, "IBM-3180-2") == 0) {
        *rows = 27;
        *cols = 132;
    }
}

void gtkterm_format_indicators(char *buf, size_t buflen, int indicators,
                               int cursor_x, int cursor_y, const char *macro_text)
{
    if (buflen < 81) {
        if (buflen > 0) {
            buf[0] = '\0';
        }
        return;
    }
    memset(buf, ' ', 80);
    buf[80] = '\0';
    memcpy(buf, "5250", 4);
    if ((indicators & TN5250_DISPLAY_IND_MESSAGE_WAITING) != 0) {
        memcpy(buf + 23, "MW", 2);
    }
    if ((indicators & TN5250_DISPLAY_IND_INHIBIT) != 0) {
        memcpy(buf + 9, "X II", 4);
    } else if ((indicators & TN5250_DISPLAY_IND_X_CLOCK) != 0) {
        memcpy(buf + 9, "X CLOCK", 7);
    } else if ((indicators & TN5250_DISPLAY_IND_X_SYSTEM) != 0) {
        memcpy(buf + 9, "X SYSTEM", 8);
    }
    if ((indicators & TN5250_DISPLAY_IND_INSERT) != 0) {
        memcpy(buf + 30, "IM", 2);
    }
    if ((indicators & TN5250_DISPLAY_IND_FER) != 0) {
        memcpy(buf + 33, "FER", 3);
    }
    if ((indicators & TN5250_DISPLAY_IND_MACRO) != 0 && macro_text != NULL) {
        memcpy(buf + 54, macro_text, 11);
    }
    snprintf(buf + 72, buflen - 72, "%03d/%03d", cursor_x + 1, cursor_y + 1);
}

static void gtkterm_apply_style(struct gtkterm_cell *cell, const struct gtkterm_attr *style,
                                unsigned char glyph, int reverse)
{
    cell->color = style->color;
    cell->reverse = (unsigned char)(reverse || style->reverse);
    cell->underline = style->underline;
    cell->blink = style->blink;
    gtkterm_store_byte(cell, glyph);
}

static void gtkterm_paint_display(Tn5250Terminal *term, Tn5250Display *display)
{
    struct _Tn5250TerminalPrivate *data = term->data;
    unsigned char attr = 0x20;
    int width;
    int height;
    int row;
    int col;
    const char *macro_text = NULL;

    width = tn5250_display_width(display);
    height = tn5250_display_height(display);
    if (width < 1) {
        width = 80;
    }
    if (height < 1) {
        height = 24;
    }
    if (width > GTKTERM_MAX_COLS) {
        width = GTKTERM_MAX_COLS;
    }
    if (height > GTKTERM_MAX_ROWS) {
        height = GTKTERM_MAX_ROWS;
    }
    data->cols = width;
    data->rows = height;
    data->cursor_x = tn5250_display_cursor_x(display);
    data->cursor_y = tn5250_display_cursor_y(display);
    data->display = display;

    for (row = 0; row < height; row++) {
        for (col = 0; col < width; col++) {
            unsigned char byte = tn5250_display_char_at(display, row, col);
            struct gtkterm_cell *cell = &data->cells[row][col];
            int ruler = data->ruler && (col == data->cursor_x || row == data->cursor_y);
            const struct gtkterm_attr *style;

            if ((byte & 0xe0) == 0x20) {
                attr = byte;
                style = &k_attrs[0];
                gtkterm_apply_style(cell, style, ' ', ruler);
                cell->underline = 0;
                cell->blink = 0;
                continue;
            }
            style = &k_attrs[(attr - 0x20) & 31];
            if (style->hidden) {
                gtkterm_apply_style(cell, &k_attrs[0], ' ', ruler);
                cell->underline = 0;
                cell->blink = 0;
                continue;
            }
            {
                unsigned char glyph = byte;
                int reverse = 0;
                int underline = style->underline;
                if (glyph == 0x1f || glyph == 0x3f) {
                    glyph = ' ';
                    reverse = 1;
                } else if ((glyph < 0x40 && glyph > 0x00) || glyph == 0xff) {
                    glyph = ' ';
                } else if (tn5250_display_char_map(display) != NULL) {
                    glyph = tn5250_char_map_to_local(tn5250_display_char_map(display), glyph);
                }
                if (data->underscores && underline && glyph == ' ') {
                    glyph = '_';
                    underline = 0;
                }
                gtkterm_apply_style(cell, style, glyph, reverse || ruler);
                cell->underline = (unsigned char)underline;
            }
        }
    }
    if ((tn5250_display_indicators(display) & TN5250_DISPLAY_IND_MACRO) != 0 &&
        display->macro != NULL) {
        macro_text = tn5250_macro_printstate(display);
    }
    gtkterm_format_indicators(data->status, sizeof data->status,
                              tn5250_display_indicators(display),
                              data->cursor_x, data->cursor_y, macro_text);
    gtkterm_queue(term);
}

static void gtk_terminal_init(Tn5250Terminal *This)
{
    (void)This;
}

static void gtk_terminal_term(Tn5250Terminal *This)
{
    This->data->display = NULL;
    This->data->quit_flag = 0;
    This->data->escape_pending = 0;
    This->data->key_head = 0;
    This->data->key_tail = 0;
    This->conn_fd = -1;
}

static void gtk_terminal_destroy(Tn5250Terminal *This)
{
    if (This->data != NULL) {
        This->data->widget = NULL;
        This->data->display = NULL;
        free(This->data);
    }
    free(This);
}

static int gtk_terminal_width(Tn5250Terminal *This)
{
    return This->data->cols;
}

static int gtk_terminal_height(Tn5250Terminal *This)
{
    return This->data->rows + 1;
}

static int gtk_terminal_flags(Tn5250Terminal *This)
{
    (void)This;
    return TN5250_TERMINAL_HAS_COLOR;
}

static void gtk_terminal_update(Tn5250Terminal *This, Tn5250Display *display)
{
    if (display == NULL) {
        return;
    }
    gtkterm_paint_display(This, display);
}

static void gtk_terminal_update_indicators(Tn5250Terminal *This, Tn5250Display *display)
{
    gtk_terminal_update(This, display);
}

static int gtk_terminal_waitevent(Tn5250Terminal *This)
{
    struct _Tn5250TerminalPrivate *data = This->data;

    while (1) {
        int result = 0;
        if (data->quit_flag) {
            return TN5250_TERMINAL_EVENT_QUIT;
        }
        if (data->key_head != data->key_tail) {
            result |= TN5250_TERMINAL_EVENT_KEY;
        }
        if (This->conn_fd >= 0) {
            GPollFD pollfd;
            gint ready;
            pollfd.fd = This->conn_fd;
            pollfd.events = G_IO_IN | G_IO_HUP | G_IO_ERR;
            pollfd.revents = 0;
            ready = g_poll(&pollfd, 1, result != 0 ? 0 : 30);
            while (g_main_context_pending(NULL)) {
                g_main_context_iteration(NULL, FALSE);
            }
            if (data->quit_flag) {
                return TN5250_TERMINAL_EVENT_QUIT;
            }
            if (data->key_head != data->key_tail) {
                result |= TN5250_TERMINAL_EVENT_KEY;
            }
            if (ready > 0 && (pollfd.revents & (G_IO_IN | G_IO_HUP | G_IO_ERR)) != 0) {
                result |= TN5250_TERMINAL_EVENT_DATA;
            }
            if (ready < 0 && errno != EINTR) {
                return TN5250_TERMINAL_EVENT_QUIT;
            }
        } else {
            g_main_context_iteration(NULL, result == 0);
            if (data->key_head != data->key_tail) {
                result |= TN5250_TERMINAL_EVENT_KEY;
            }
        }
        if (result != 0) {
            return result;
        }
    }
}

static int gtk_terminal_getkey(Tn5250Terminal *This)
{
    return gtkterm_pop_key(This->data);
}

static void gtk_terminal_beep(Tn5250Terminal *This)
{
    if (This->data->widget != NULL) {
        gtk_widget_error_bell(This->data->widget);
    }
}

static int gtk_terminal_enhanced(Tn5250Terminal *This)
{
    (void)This;
    return 0;
}

static int gtk_terminal_config(Tn5250Terminal *This, Tn5250Config *config)
{
    if (tn5250_config_get(config, "underscores")) {
        This->data->underscores = tn5250_config_get_bool(config, "underscores");
    }
    if (tn5250_config_get(config, "ruler")) {
        This->data->ruler = tn5250_config_get_bool(config, "ruler");
    }
    return 0;
}

static void gtk_terminal_create_window(Tn5250Terminal *This, Tn5250Display *display,
                                       struct _Tn5250Window *window)
{
    (void)This;
    (void)display;
    (void)window;
}

static void gtk_terminal_destroy_window(Tn5250Terminal *This, Tn5250Display *display,
                                        struct _Tn5250Window *window)
{
    (void)This;
    (void)display;
    (void)window;
}

static void gtk_terminal_create_scrollbar(Tn5250Terminal *This, Tn5250Display *display,
                                          struct _Tn5250Scrollbar *scrollbar)
{
    (void)This;
    (void)display;
    (void)scrollbar;
}

static void gtk_terminal_destroy_scrollbar(Tn5250Terminal *This, Tn5250Display *display)
{
    (void)This;
    (void)display;
}

static void gtk_terminal_create_menubar(Tn5250Terminal *This, Tn5250Display *display,
                                        struct _Tn5250Menubar *menubar)
{
    (void)This;
    (void)display;
    (void)menubar;
}

static void gtk_terminal_destroy_menubar(Tn5250Terminal *This, Tn5250Display *display,
                                         struct _Tn5250Menubar *menubar)
{
    (void)This;
    (void)display;
    (void)menubar;
}

static void gtk_terminal_create_menuitem(Tn5250Terminal *This, Tn5250Display *display,
                                         struct _Tn5250Menuitem *menuitem)
{
    (void)This;
    (void)display;
    (void)menuitem;
}

static void gtk_terminal_destroy_menuitem(Tn5250Terminal *This, Tn5250Display *display,
                                          struct _Tn5250Menuitem *menuitem)
{
    (void)This;
    (void)display;
    (void)menuitem;
}

Tn5250Terminal *gtkterm_new(void)
{
    Tn5250Terminal *term = tn5250_new(Tn5250Terminal, 1);
    if (term == NULL) {
        return NULL;
    }
    term->data = tn5250_new(struct _Tn5250TerminalPrivate, 1);
    if (term->data == NULL) {
        free(term);
        return NULL;
    }
    term->conn_fd = -1;
    term->data->cell_w = 9;
    term->data->cell_h = 18;
    term->data->cols = 80;
    term->data->rows = 24;
    term->data->blink_on = 1;
    gtkterm_blank(term->data);
    gtkterm_format_indicators(term->data->status, sizeof term->data->status, 0, 0, 0, NULL);
    term->init = gtk_terminal_init;
    term->term = gtk_terminal_term;
    term->destroy = gtk_terminal_destroy;
    term->width = gtk_terminal_width;
    term->height = gtk_terminal_height;
    term->flags = gtk_terminal_flags;
    term->update = gtk_terminal_update;
    term->update_indicators = gtk_terminal_update_indicators;
    term->waitevent = gtk_terminal_waitevent;
    term->getkey = gtk_terminal_getkey;
    term->putkey = NULL;
    term->beep = gtk_terminal_beep;
    term->enhanced = gtk_terminal_enhanced;
    term->config = gtk_terminal_config;
    term->create_window = gtk_terminal_create_window;
    term->destroy_window = gtk_terminal_destroy_window;
    term->create_scrollbar = gtk_terminal_create_scrollbar;
    term->destroy_scrollbar = gtk_terminal_destroy_scrollbar;
    term->create_menubar = gtk_terminal_create_menubar;
    term->destroy_menubar = gtk_terminal_destroy_menubar;
    term->create_menuitem = gtk_terminal_create_menuitem;
    term->destroy_menuitem = gtk_terminal_destroy_menuitem;
    return term;
}

void gtkterm_set_widget(Tn5250Terminal *term, void *widget)
{
    if (term == NULL || term->data == NULL) {
        return;
    }
    term->data->widget = (GtkWidget *)widget;
    gtkterm_queue(term);
}

void gtkterm_request_quit(Tn5250Terminal *term)
{
    if (term != NULL && term->data != NULL) {
        term->data->quit_flag = 1;
    }
}

void gtkterm_set_geometry(Tn5250Terminal *term, int rows, int cols)
{
    if (term == NULL || term->data == NULL) {
        return;
    }
    if (rows < 1) {
        rows = 24;
    }
    if (cols < 1) {
        cols = 80;
    }
    if (rows > GTKTERM_MAX_ROWS) {
        rows = GTKTERM_MAX_ROWS;
    }
    if (cols > GTKTERM_MAX_COLS) {
        cols = GTKTERM_MAX_COLS;
    }
    term->data->rows = rows;
    term->data->cols = cols;
    term->data->cursor_x = 0;
    term->data->cursor_y = 0;
    gtkterm_blank(term->data);
    gtkterm_format_indicators(term->data->status, sizeof term->data->status, 0, 0, 0, NULL);
    gtkterm_queue(term);
}

void gtkterm_draw(Tn5250Terminal *term, void *cairo_context)
{
    cairo_t *cr = (cairo_t *)cairo_context;
    struct _Tn5250TerminalPrivate *data;
    cairo_text_extents_t extents;
    int row;
    int col;

    if (term == NULL || term->data == NULL || cr == NULL) {
        return;
    }
    data = term->data;
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_paint(cr);
    cairo_select_font_face(cr, "monospace", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, 16);
    cairo_text_extents(cr, "M", &extents);
    if (extents.x_advance > 1) {
        data->cell_w = (int)extents.x_advance;
    }
    if (extents.height > 1) {
        data->cell_h = (int)extents.height + 6;
    }
    for (row = 0; row < data->rows; row++) {
        for (col = 0; col < data->cols; col++) {
            struct gtkterm_cell *cell = &data->cells[row][col];
            double left = col * data->cell_w;
            double top = row * data->cell_h;
            double red;
            double green;
            double blue;
            int reverse = cell->reverse;
            int cursor = (row == data->cursor_y && col == data->cursor_x);
            if (cursor) {
                reverse = !reverse;
            }
            gtkterm_rgb(cell->color, &red, &green, &blue);
            if (reverse) {
                cairo_set_source_rgb(cr, red, green, blue);
            } else {
                cairo_set_source_rgb(cr, 0, 0, 0);
            }
            cairo_rectangle(cr, left, top, data->cell_w, data->cell_h);
            cairo_fill(cr);
            if (cell->blink && !data->blink_on) {
                continue;
            }
            if (reverse) {
                cairo_set_source_rgb(cr, 0, 0, 0);
            } else {
                cairo_set_source_rgb(cr, red, green, blue);
            }
            cairo_move_to(cr, left, top + data->cell_h - 4);
            cairo_show_text(cr, cell->text);
            if (cell->underline) {
                cairo_move_to(cr, left, top + data->cell_h - 2);
                cairo_line_to(cr, left + data->cell_w, top + data->cell_h - 2);
                cairo_stroke(cr);
            }
        }
    }
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_move_to(cr, 0, data->rows * data->cell_h + data->cell_h - 4);
    cairo_show_text(cr, data->status);
}

int gtkterm_on_key(Tn5250Terminal *term, unsigned keyval, unsigned state)
{
    int key = 0;
    int quit = 0;
    int produced;

    if (term == NULL || term->data == NULL || term->data->display == NULL) {
        return 0;
    }
    produced = gtkterm_translate(keyval, state, &term->data->escape_pending, &key, &quit);
    if (quit) {
        term->data->quit_flag = 1;
        return 1;
    }
    if (produced) {
        gtkterm_push_key(term->data, key);
        return 1;
    }
    if (term->data->escape_pending) {
        return 1;
    }
    return 0;
}

void gtkterm_on_click(Tn5250Terminal *term, double x, double y)
{
    int col;
    int row;

    if (term == NULL || term->data == NULL || term->data->display == NULL) {
        return;
    }
    if (term->data->cell_w < 1 || term->data->cell_h < 1) {
        return;
    }
    col = (int)(x / term->data->cell_w);
    row = (int)(y / term->data->cell_h);
    if (col < 0 || row < 0 || col >= tn5250_display_width(term->data->display) ||
        row >= tn5250_display_height(term->data->display)) {
        return;
    }
    tn5250_display_set_cursor(term->data->display, row, col);
    tn5250_display_update(term->data->display);
}

int gtkterm_blink_tick(Tn5250Terminal *term)
{
    int row;
    int col;
    int any = 0;

    if (term == NULL || term->data == NULL) {
        return 0;
    }
    for (row = 0; row < term->data->rows && !any; row++) {
        for (col = 0; col < term->data->cols; col++) {
            if (term->data->cells[row][col].blink) {
                any = 1;
                break;
            }
        }
    }
    if (!any) {
        return 0;
    }
    term->data->blink_on = !term->data->blink_on;
    gtkterm_queue(term);
    return 1;
}

const char *gtkterm_key_plan_text(void)
{
    return k_key_plan;
}

const char *gtkterm_attribute_plan_text(void)
{
    static char text[1024];
    size_t used = 0;
    int index;

    text[0] = '\0';
    for (index = 0; index < 32; index++) {
        int wrote = snprintf(text + used, sizeof text - used, "%d %s\n", index, k_attrs[index].name);
        if (wrote < 0 || (size_t)wrote >= sizeof text - used) {
            break;
        }
        used += (size_t)wrote;
    }
    return text;
}

const char *gtkterm_screen_plan_text(void)
{
    return k_screen_plan;
}

static int gtkterm_expect(const char *name, int ok)
{
    if (!ok) {
        g_printerr("key-check failed: %s\n", name);
        return 1;
    }
    return 0;
}

int gtkterm_self_check(void)
{
    int escape_pending = 0;
    int key = 0;
    int quit = 0;
    int rows = 0;
    int cols = 0;
    char indicators[96];
    int failed = 0;

    failed |= gtkterm_expect("enter",
        gtkterm_translate(GDK_KEY_Return, 0, &escape_pending, &key, &quit) == 1 && key == K_ENTER);
    failed |= gtkterm_expect("field exit",
        gtkterm_translate(GDK_KEY_KP_Enter, 0, &escape_pending, &key, &quit) == 1 && key == K_FIELDEXIT);
    failed |= gtkterm_expect("attention",
        gtkterm_translate(GDK_KEY_a, GDK_CONTROL_MASK, &escape_pending, &key, &quit) == 1 &&
        key == K_ATTENTION);
    failed |= gtkterm_expect("quit",
        gtkterm_translate(GDK_KEY_q, GDK_CONTROL_MASK, &escape_pending, &key, &quit) == 1 && quit == 1);
    quit = 0;
    failed |= gtkterm_expect("f1",
        gtkterm_translate(GDK_KEY_F1, 0, &escape_pending, &key, &quit) == 1 && key == K_F1);
    failed |= gtkterm_expect("f24",
        gtkterm_translate(GDK_KEY_F12, GDK_SHIFT_MASK, &escape_pending, &key, &quit) == 1 && key == K_F24);
    failed |= gtkterm_expect("letter",
        gtkterm_translate(GDK_KEY_a, 0, &escape_pending, &key, &quit) == 1 && key == 'a');
    failed |= gtkterm_expect("page",
        gtkterm_translate(GDK_KEY_Page_Up, 0, &escape_pending, &key, &quit) == 1 && key == K_ROLLDN);
    escape_pending = 0;
    failed |= gtkterm_expect("escape arm",
        gtkterm_translate(GDK_KEY_Escape, 0, &escape_pending, &key, &quit) == 0 && escape_pending == 1);
    failed |= gtkterm_expect("escape f1",
        gtkterm_translate(GDK_KEY_1, 0, &escape_pending, &key, &quit) == 1 && key == K_F1 &&
        escape_pending == 0);
    gtkterm_geometry_for_type("IBM-3179-2", &rows, &cols);
    failed |= gtkterm_expect("24x80", rows == 24 && cols == 80);
    gtkterm_geometry_for_type("IBM-3477-FC", &rows, &cols);
    failed |= gtkterm_expect("27x132", rows == 27 && cols == 132);
    gtkterm_format_indicators(indicators, sizeof indicators,
                              TN5250_DISPLAY_IND_MESSAGE_WAITING | TN5250_DISPLAY_IND_INSERT,
                              4, 6, NULL);
    failed |= gtkterm_expect("indicators",
        strstr(indicators, "5250") != NULL && strstr(indicators, "MW") != NULL &&
        strstr(indicators, "IM") != NULL && strstr(indicators, "005/007") != NULL);
    failed |= gtkterm_expect("attribute 0", strcmp(k_attrs[0].name, "green") == 0);
    failed |= gtkterm_expect("attribute 7", strcmp(k_attrs[7].name, "nondisplay") == 0);
    failed |= gtkterm_expect("attribute 16", strcmp(k_attrs[16].name, "turquoise") == 0);
    failed |= gtkterm_expect("attribute 31", strcmp(k_attrs[31].name, "nondisplay") == 0);
    return failed ? 1 : 0;
}

}
