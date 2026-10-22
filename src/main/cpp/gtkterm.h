// gtkterm.h
// GTK terminal for the tn5250 session. There is no WebKit view.

#ifndef GTKTERM_H
#define GTKTERM_H

#include <stddef.h>

struct _Tn5250Terminal;
typedef struct _Tn5250Terminal Tn5250Terminal;

#ifdef __cplusplus
extern "C" {
#endif

Tn5250Terminal *gtkterm_new(void);
void gtkterm_set_widget(Tn5250Terminal *term, void *widget);
void gtkterm_request_quit(Tn5250Terminal *term);
void gtkterm_set_geometry(Tn5250Terminal *term, int rows, int cols);
void gtkterm_geometry_for_type(const char *type_name, int *rows, int *cols);
void gtkterm_draw(Tn5250Terminal *term, void *cairo_context);
int gtkterm_on_key(Tn5250Terminal *term, unsigned keyval, unsigned state);
void gtkterm_on_click(Tn5250Terminal *term, double x, double y);
int gtkterm_blink_tick(Tn5250Terminal *term);

int gtkterm_translate(unsigned keyval, unsigned state, int *escape_pending,
                      int *key_out, int *quit_out);
void gtkterm_format_indicators(char *buf, size_t buflen, int indicators,
                               int cursor_x, int cursor_y, const char *macro_text);

const char *gtkterm_key_plan_text(void);
const char *gtkterm_attribute_plan_text(void);
const char *gtkterm_screen_plan_text(void);
int gtkterm_self_check(void);

#ifdef __cplusplus
}
#endif

#endif
