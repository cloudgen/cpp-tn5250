// gnome_app.h
// Window, menus, and the 5250 session. The center widget is the terminal.

#ifndef GNOME_APP_H
#define GNOME_APP_H

#ifdef __cplusplus
extern "C" {
#endif

int gnome_app_headless(int argc, char **argv);
int gnome_app_headless_status(void);
int gnome_app_run(int argc, char **argv);

#ifdef __cplusplus
}
#endif

#endif
