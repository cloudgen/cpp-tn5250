// gnome_app.cpp
// GNOME window. The center of the window is the 5250 terminal, not a web view.
// Session startup follows the curses client: config, stream, display, terminal, macro.

#include "gnome_app.h"
#include "gtkterm.h"
#include "logger.h"
#include "project.h"

#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>

#include "tn5250-private.h"

#define SESSION_ARG_MAX 48

struct session_form {
    char host[512];
    char map_name[64];
    char term_type[64];
    char devname[64];
    char trace[512];
    char extra[1024];
    int ssl;
    int ssl_verify;
    int underscores;
    int ruler;
};

struct app_state {
    GtkWidget *window;
    GtkWidget *host_entry;
    GtkWidget *map_entry;
    GtkWidget *term_combo;
    GtkWidget *dev_entry;
    GtkWidget *trace_entry;
    GtkWidget *extra_entry;
    GtkWidget *ssl_check;
    GtkWidget *verify_check;
    GtkWidget *ruler_check;
    GtkWidget *under_check;
    GtkWidget *area;
    GtkWidget *status;
    GtkWidget *error_dialog;
    Tn5250Terminal *term;
    int in_session;
    int quit_requested;
    int shutdown_seconds;
};

static struct app_state *g_app = NULL;
static int g_headless_status = 0;

static const char *k_term_ids[] = {
    "",
    "IBM-3179-2",
    "IBM-3477-FC",
    "IBM-3477-FG",
    "IBM-3180-2",
    "IBM-3196-A1",
    "IBM-5292-2",
    "IBM-5291-1",
    "IBM-5251-11",
    NULL
};

static const char *k_term_labels[] = {
    "default",
    "IBM-3179-2 24x80 color",
    "IBM-3477-FC 27x132 color",
    "IBM-3477-FG 27x132 monochrome",
    "IBM-3180-2 27x132 monochrome",
    "IBM-3196-A1 24x80 monochrome",
    "IBM-5292-2 24x80 color",
    "IBM-5291-1 24x80 monochrome",
    "IBM-5251-11 24x80 monochrome"
};

static void copy_text(char *dest, size_t dest_size, const char *src)
{
    if (src == NULL) {
        dest[0] = '\0';
        return;
    }
    g_strlcpy(dest, src, dest_size);
}

static void session_form_clear(struct session_form *form)
{
    memset(form, 0, sizeof *form);
    form->ssl_verify = -1;
    form->underscores = -1;
    form->ruler = -1;
}

static int is_logger_switch(const char *text)
{
    return strcmp(text, "--quiet") == 0 || strcmp(text, "--json") == 0 ||
           strcmp(text, "--debug") == 0 || strcmp(text, "--verbose") == 0;
}

static int is_logger_value(const char *text)
{
    return strcmp(text, "--prefix") == 0 || strcmp(text, "--home") == 0 ||
           strcmp(text, "--log-datestamp") == 0;
}

static int is_plan_verb(const char *text)
{
    return strcmp(text, "key-plan") == 0 || strcmp(text, "key-check") == 0 ||
           strcmp(text, "attribute-plan") == 0 || strcmp(text, "screen-plan") == 0 ||
           strcmp(text, "session-plan") == 0 || strcmp(text, "form-plan") == 0 ||
           strcmp(text, "help") == 0 || strcmp(text, "test") == 0 ||
           strcmp(text, "list") == 0 || strcmp(text, "show") == 0 ||
           strcmp(text, "--version") == 0 || strncmp(text, "--shutdown", 10) == 0;
}

static int collect_session_args(int argc, char **argv, char **out, int max_out)
{
    int count = 0;
    int index;

    for (index = 1; index < argc; index++) {
        if (is_logger_switch(argv[index]) || is_plan_verb(argv[index])) {
            continue;
        }
        if (is_logger_value(argv[index])) {
            index++;
            continue;
        }
        if (count >= max_out) {
            return -1;
        }
        out[count++] = argv[index];
    }
    return count;
}

static void append_extra(struct session_form *form, const char *text)
{
    size_t used = strlen(form->extra);
    size_t add = strlen(text);
    if (used + add + 2 >= sizeof form->extra) {
        return;
    }
    if (used > 0) {
        form->extra[used++] = ' ';
        form->extra[used] = '\0';
    }
    memcpy(form->extra + used, text, add + 1);
}

static int take_value(const char *text, const char *prefix, char *dest, size_t dest_size)
{
    size_t length = strlen(prefix);
    if (strncmp(text, prefix, length) != 0) {
        return 0;
    }
    copy_text(dest, dest_size, text + length);
    return 1;
}

static int session_form_from_args(struct session_form *form, int count, char **args)
{
    int index;
    const char *host = NULL;

    session_form_clear(form);
    for (index = 0; index < count; index++) {
        const char *text = args[index];
        if (take_value(text, "map=", form->map_name, sizeof form->map_name) ||
            take_value(text, "env.TERM=", form->term_type, sizeof form->term_type) ||
            take_value(text, "env.DEVNAME=", form->devname, sizeof form->devname) ||
            take_value(text, "trace=", form->trace, sizeof form->trace)) {
            continue;
        }
        if (strcmp(text, "+underscores") == 0) {
            form->underscores = 1;
            continue;
        }
        if (strcmp(text, "-underscores") == 0) {
            form->underscores = 0;
            continue;
        }
        if (strcmp(text, "+ruler") == 0) {
            form->ruler = 1;
            continue;
        }
        if (strcmp(text, "-ruler") == 0) {
            form->ruler = 0;
            continue;
        }
        if (strcmp(text, "+ssl_verify_server") == 0) {
            form->ssl_verify = 1;
            continue;
        }
        if (strcmp(text, "-ssl_verify_server") == 0) {
            form->ssl_verify = 0;
            continue;
        }
        if (text[0] == '+' || text[0] == '-' || strchr(text, '=') != NULL) {
            append_extra(form, text);
            continue;
        }
        host = text;
    }
    if (host == NULL || host[0] == '\0') {
        return 0;
    }
    if (strncmp(host, "ssl:", 4) == 0) {
        form->ssl = 1;
        host += 4;
    }
    copy_text(form->host, sizeof form->host, host);
    return form->host[0] != '\0';
}

static int push_arg(char **args, int *count, int max_args, const char *text)
{
    if (*count >= max_args) {
        return -1;
    }
    args[*count] = g_strdup(text);
    if (args[*count] == NULL) {
        return -1;
    }
    *count += 1;
    return 0;
}

static int push_flag(char **args, int *count, int max_args, int value, const char *name)
{
    char text[128];
    if (value < 0) {
        return 0;
    }
    snprintf(text, sizeof text, "%s%s", value ? "+" : "-", name);
    return push_arg(args, count, max_args, text);
}

static int push_pair(char **args, int *count, int max_args, const char *name, const char *value)
{
    char text[600];
    if (value == NULL || value[0] == '\0') {
        return 0;
    }
    snprintf(text, sizeof text, "%s=%s", name, value);
    return push_arg(args, count, max_args, text);
}

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

static void free_args(char **args, int count)
{
    int index;
    for (index = 0; index < count; index++) {
        g_free(args[index]);
    }
}

static int args_contain(char **args, int count, const char *text)
{
    int index;
    for (index = 0; index < count; index++) {
        if (strcmp(args[index], text) == 0) {
            return 1;
        }
    }
    return 0;
}

static int gnome_form_self_check(void)
{
    struct session_form form;
    char *args[SESSION_ARG_MAX];
    int count;
    char *sample[] = {
        (char *)"map=37",
        (char *)"+ruler",
        (char *)"+underscores",
        (char *)"+ssl_verify_server",
        (char *)"env.TERM=IBM-3477-FC",
        (char *)"env.DEVNAME=DSP01",
        (char *)"trace=trace-file",
        (char *)"ssl:ibmi.example"
    };
    int failed = 0;

    session_form_clear(&form);
    copy_text(form.host, sizeof form.host, "ibmi.example");
    copy_text(form.map_name, sizeof form.map_name, "37");
    copy_text(form.term_type, sizeof form.term_type, "IBM-3477-FC");
    copy_text(form.devname, sizeof form.devname, "DSP01");
    copy_text(form.trace, sizeof form.trace, "trace-file");
    copy_text(form.extra, sizeof form.extra, "ssl_ca_file=ca.pem");
    form.ssl = 1;
    form.ssl_verify = 1;
    form.underscores = 1;
    form.ruler = 1;
    count = form_to_args(&form, args, SESSION_ARG_MAX);
    if (count < 0 || !args_contain(args, count, "map=37") ||
        !args_contain(args, count, "env.TERM=IBM-3477-FC") ||
        !args_contain(args, count, "env.DEVNAME=DSP01") ||
        !args_contain(args, count, "trace=trace-file") ||
        !args_contain(args, count, "+ssl_verify_server") ||
        !args_contain(args, count, "+underscores") ||
        !args_contain(args, count, "+ruler") ||
        !args_contain(args, count, "ssl_ca_file=ca.pem") ||
        !args_contain(args, count, "ssl:ibmi.example")) {
        g_printerr("key-check failed: form builder\n");
        failed = 1;
    }
    if (count > 0) {
        free_args(args, count);
    }
    if (!session_form_from_args(&form, 8, sample) || form.ssl != 1 ||
        strcmp(form.host, "ibmi.example") != 0 || form.ruler != 1) {
        g_printerr("key-check failed: form parser\n");
        failed = 1;
    }
    count = form_to_args(&form, args, SESSION_ARG_MAX);
    if (count < 0 || !args_contain(args, count, "ssl:ibmi.example") ||
        !args_contain(args, count, "map=37")) {
        g_printerr("key-check failed: form round trip\n");
        failed = 1;
    }
    if (count > 0) {
        free_args(args, count);
    }
    if (session_form_from_args(&form, 0, sample)) {
        g_printerr("key-check failed: empty host\n");
        failed = 1;
    }
    return failed;
}

static void join_args(char *dest, size_t dest_size, int count, char **args)
{
    size_t used = 0;
    int index;
    dest[0] = '\0';
    for (index = 0; index < count; index++) {
        size_t add = strlen(args[index]);
        if (used + add + 2 >= dest_size) {
            return;
        }
        if (used > 0) {
            dest[used++] = ' ';
        }
        memcpy(dest + used, args[index], add + 1);
        used += add;
    }
}

static int print_session_plan(int argc, char **argv)
{
    char *args[SESSION_ARG_MAX];
    int count = collect_session_args(argc, argv, args, SESSION_ARG_MAX);
    const char *host = NULL;
    char joined[2048];
    int index;

    if (count < 0) {
        g_printerr("session-plan has too many options\n");
        return 1;
    }
    for (index = 0; index < count; index++) {
        if (args[index][0] == '+' || args[index][0] == '-' || strchr(args[index], '=') != NULL) {
            continue;
        }
        host = args[index];
    }
    if (host == NULL) {
        g_printerr("session-plan requires a host\n");
        return 1;
    }
    join_args(joined, sizeof joined, count, args);
    g_print("host=%s\nargv=%s\n", host, joined);
    return 0;
}

static int print_form_plan(int argc, char **argv)
{
    char *incoming[SESSION_ARG_MAX];
    char *outgoing[SESSION_ARG_MAX];
    struct session_form form;
    int incoming_count = collect_session_args(argc, argv, incoming, SESSION_ARG_MAX);
    int outgoing_count;
    char joined[2048];

    if (incoming_count < 0) {
        g_printerr("form-plan has too many options\n");
        return 1;
    }
    if (!session_form_from_args(&form, incoming_count, incoming)) {
        g_printerr("form-plan requires a host\n");
        return 1;
    }
    outgoing_count = form_to_args(&form, outgoing, SESSION_ARG_MAX);
    if (outgoing_count < 0) {
        g_printerr("form-plan could not build the session\n");
        return 1;
    }
    join_args(joined, sizeof joined, outgoing_count, outgoing);
    g_print("host=%s%s\nargv=%s\n", form.ssl ? "ssl:" : "", form.host, joined);
    free_args(outgoing, outgoing_count);
    return 0;
}

static int shutdown_seconds(int argc, char **argv)
{
    int index;
    for (index = 1; index < argc; index++) {
        if (strncmp(argv[index], "--shutdown=", 11) == 0) {
            return atoi(argv[index] + 11);
        }
        if (strcmp(argv[index], "--shutdown") == 0 && index + 1 < argc) {
            return atoi(argv[index + 1]);
        }
    }
    return 0;
}

static int plan_verb_count(int argc, char **argv)
{
    int index;
    int count = 0;
    for (index = 1; index < argc; index++) {
        if (strcmp(argv[index], "key-plan") == 0 || strcmp(argv[index], "key-check") == 0 ||
            strcmp(argv[index], "attribute-plan") == 0 || strcmp(argv[index], "screen-plan") == 0 ||
            strcmp(argv[index], "session-plan") == 0 || strcmp(argv[index], "form-plan") == 0) {
            count++;
        }
    }
    return count;
}

extern "C" int gnome_app_headless_status(void)
{
    return g_headless_status;
}

extern "C" int gnome_app_headless(int argc, char **argv)
{
    int index;
    int plans;

    for (index = 1; index < argc; index++) {
        if (strcmp(argv[index], "--version") == 0) {
            g_print("%s %d.%d.%d\n", PROJECT_NAME, VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);
            g_print("tn5250 %s\n", VERSION);
            g_headless_status = 0;
            return 1;
        }
    }
    plans = plan_verb_count(argc, argv);
    if (plans > 1) {
        g_printerr("one plan command\n");
        g_headless_status = 1;
        return 1;
    }
    if (plans == 0) {
        return 0;
    }
    for (index = 1; index < argc; index++) {
        if (strcmp(argv[index], "key-check") == 0) {
            g_headless_status = gtkterm_self_check() || gnome_form_self_check();
            if (g_headless_status == 0) {
                g_print("PASS key-check\n");
            }
            return 1;
        }
        if (strcmp(argv[index], "key-plan") == 0) {
            g_print("%s", gtkterm_key_plan_text());
            g_headless_status = 0;
            return 1;
        }
        if (strcmp(argv[index], "attribute-plan") == 0) {
            g_print("%s", gtkterm_attribute_plan_text());
            g_headless_status = 0;
            return 1;
        }
        if (strcmp(argv[index], "screen-plan") == 0) {
            g_print("%s", gtkterm_screen_plan_text());
            g_headless_status = 0;
            return 1;
        }
        if (strcmp(argv[index], "session-plan") == 0) {
            g_headless_status = print_session_plan(argc, argv);
            return 1;
        }
        if (strcmp(argv[index], "form-plan") == 0) {
            g_headless_status = print_form_plan(argc, argv);
            return 1;
        }
    }
    return 0;
}

static void set_status(const char *text)
{
    if (g_app != NULL && g_app->status != NULL) {
        gtk_label_set_text(GTK_LABEL(g_app->status), text);
    }
}

static void dismiss_error_dialog(void)
{
    if (g_app != NULL && g_app->error_dialog != NULL) {
        gtk_dialog_response(GTK_DIALOG(g_app->error_dialog), GTK_RESPONSE_CLOSE);
    }
}

static void report_error(const char *text)
{
    GtkWidget *dialog;
    logger_error("%s", text);
    if (g_app == NULL || g_app->window == NULL) {
        return;
    }
    dialog = gtk_message_dialog_new(GTK_WINDOW(g_app->window), GTK_DIALOG_MODAL,
                                    GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE, "%s", text);
    g_app->error_dialog = dialog;
    gtk_dialog_run(GTK_DIALOG(dialog));
    g_app->error_dialog = NULL;
    gtk_widget_destroy(dialog);
}

static void read_form(struct session_form *form)
{
    const char *term_id;
    char *host;
    char *map_name;
    char *devname;
    char *trace;
    char *extra;

    session_form_clear(form);
    host = g_strdup(gtk_entry_get_text(GTK_ENTRY(g_app->host_entry)));
    map_name = g_strdup(gtk_entry_get_text(GTK_ENTRY(g_app->map_entry)));
    devname = g_strdup(gtk_entry_get_text(GTK_ENTRY(g_app->dev_entry)));
    trace = g_strdup(gtk_entry_get_text(GTK_ENTRY(g_app->trace_entry)));
    extra = g_strdup(gtk_entry_get_text(GTK_ENTRY(g_app->extra_entry)));
    g_strstrip(host);
    g_strstrip(map_name);
    g_strstrip(devname);
    g_strstrip(trace);
    g_strstrip(extra);
    copy_text(form->host, sizeof form->host, host);
    copy_text(form->map_name, sizeof form->map_name, map_name);
    copy_text(form->devname, sizeof form->devname, devname);
    copy_text(form->trace, sizeof form->trace, trace);
    copy_text(form->extra, sizeof form->extra, extra);
    term_id = gtk_combo_box_get_active_id(GTK_COMBO_BOX(g_app->term_combo));
    if (term_id != NULL) {
        copy_text(form->term_type, sizeof form->term_type, term_id);
    }
    form->ssl = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(g_app->ssl_check)) ? 1 : 0;
    form->ssl_verify = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(g_app->verify_check)) ? 1 : -1;
    form->ruler = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(g_app->ruler_check)) ? 1 : -1;
    form->underscores = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(g_app->under_check)) ? 1 : -1;
    g_free(host);
    g_free(map_name);
    g_free(devname);
    g_free(trace);
    g_free(extra);
}

static void apply_form_to_widgets(const struct session_form *form)
{
    int rows = 24;
    int cols = 80;
    gtk_entry_set_text(GTK_ENTRY(g_app->host_entry), form->host);
    gtk_entry_set_text(GTK_ENTRY(g_app->map_entry), form->map_name);
    gtk_entry_set_text(GTK_ENTRY(g_app->dev_entry), form->devname);
    gtk_entry_set_text(GTK_ENTRY(g_app->trace_entry), form->trace);
    gtk_entry_set_text(GTK_ENTRY(g_app->extra_entry), form->extra);
    if (form->term_type[0] != '\0') {
        gtk_combo_box_set_active_id(GTK_COMBO_BOX(g_app->term_combo), form->term_type);
    }
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(g_app->ssl_check), form->ssl);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(g_app->verify_check), form->ssl_verify == 1);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(g_app->ruler_check), form->ruler == 1);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(g_app->under_check), form->underscores == 1);
    gtkterm_geometry_for_type(form->term_type, &rows, &cols);
    gtkterm_set_geometry(g_app->term, rows, cols);
}

static void release_display(Tn5250Display *display)
{
    int drop_term = 0;
    if (display == NULL) {
        return;
    }
    if (display->terminal != NULL && display->terminal != g_app->term) {
        drop_term = 1;
    } else if (display->terminal == g_app->term) {
        display->terminal = NULL;
    }
    tn5250_display_destroy(display);
    if (drop_term) {
        g_app->term = gtkterm_new();
        gtkterm_set_widget(g_app->term, g_app->area);
    }
}

static void connect_session(void)
{
    struct session_form form;
    if (g_app == NULL || g_app->in_session) {
        return;
    }
    char *option_args[SESSION_ARG_MAX];
    char *parse_argv[SESSION_ARG_MAX + 1];
    int option_count;
    int index;
    Tn5250Config *config = NULL;
    Tn5250Stream *stream = NULL;
    Tn5250Display *display = NULL;
    Tn5250Session *session = NULL;
    Tn5250Macro *macro = NULL;
    Tn5250Terminal *active;
    const char *message = NULL;
    const char *host;
    char title[640];

    if (g_app->in_session) {
        return;
    }
    read_form(&form);
    option_count = form_to_args(&form, option_args, SESSION_ARG_MAX);
    if (option_count < 0) {
        report_error("a host is required");
        return;
    }
    config = tn5250_config_new();
    if (config == NULL) {
        free_args(option_args, option_count);
        report_error("could not allocate the session config");
        return;
    }
    if (tn5250_config_load_default(config) == -1) {
        message = "could not load tn5250 configuration";
        goto cleanup;
    }
    parse_argv[0] = (char *)PROJECT_NAME;
    for (index = 0; index < option_count; index++) {
        parse_argv[index + 1] = option_args[index];
    }
    if (tn5250_config_parse_argv(config, option_count + 1, parse_argv) == -1) {
        message = "could not parse session options";
        goto cleanup;
    }
    host = tn5250_config_get(config, "host");
    if (host == NULL || host[0] == '\0') {
        message = "a host is required";
        goto cleanup;
    }
#ifndef NDEBUG
    if (tn5250_config_get(config, "trace") != NULL) {
        tn5250_log_open(tn5250_config_get(config, "trace"));
    }
#endif
    stream = tn5250_stream_open(host, config);
    if (stream == NULL) {
        message = tn5250_has_error() ? tn5250_strerror() : "could not open the host";
        goto cleanup;
    }
    display = tn5250_display_new();
    if (display == NULL || tn5250_display_config(display, config) == -1) {
        message = "could not configure the display";
        goto cleanup;
    }
    active = g_app->term;
    if (tn5250_terminal_config(active, config) == -1) {
        message = "could not configure the terminal";
        goto cleanup;
    }
#ifndef NDEBUG
    if (strlen(host) >= 6 && memcmp(host, "debug:", 6) == 0) {
        Tn5250Terminal *wrapped = tn5250_debug_terminal_new(active, stream);
        if (wrapped == NULL) {
            message = "could not start the debug terminal";
            goto cleanup;
        }
        active = wrapped;
        if (tn5250_terminal_config(active, config) == -1) {
            message = "could not configure the debug terminal";
            goto cleanup;
        }
    }
#endif
    tn5250_terminal_init(active);
    tn5250_display_set_terminal(display, active);
    session = tn5250_session_new();
    tn5250_display_set_session(display, session);
    active->conn_fd = tn5250_stream_socket_handle(stream);
    tn5250_session_set_stream(session, stream);
    stream = NULL;
    if (tn5250_session_config(session, config) == -1) {
        message = "could not configure the session";
        goto cleanup;
    }
    macro = tn5250_macro_init();
    tn5250_macro_attach(display, macro);
    snprintf(title, sizeof title, "%s — %s", PROJECT_NAME, host);
    gtk_window_set_title(GTK_WINDOW(g_app->window), title);
    set_status("Connected");
    gtk_widget_grab_focus(g_app->area);
    logger_info("session started %s", host);
    g_app->in_session = 1;
    tn5250_session_main_loop(session);
    g_app->in_session = 0;
    logger_info("session ended");

cleanup:
    if (message != NULL) {
        report_error(message);
    }
    if (macro != NULL) {
        tn5250_macro_exit(macro);
    }
    if (display != NULL && display->terminal != NULL) {
        tn5250_terminal_term(display->terminal);
    } else if (g_app->term != NULL) {
        tn5250_terminal_term(g_app->term);
    }
    if (session != NULL) {
        tn5250_session_destroy(session);
    } else if (stream != NULL) {
        tn5250_stream_destroy(stream);
    }
    release_display(display);
    if (config != NULL) {
        tn5250_config_unref(config);
    }
#ifndef NDEBUG
    tn5250_log_close();
#endif
    free_args(option_args, option_count);
    gtk_window_set_title(GTK_WINDOW(g_app->window), PROJECT_NAME);
    set_status("Disconnected");
    if (g_app->quit_requested) {
        gtk_main_quit();
    }
}

extern "C" {

static void on_connect(GtkWidget *widget, gpointer data)
{
    (void)widget;
    (void)data;
    connect_session();
}

static void on_disconnect(GtkWidget *widget, gpointer data)
{
    (void)widget;
    (void)data;
    if (g_app == NULL || !g_app->in_session) {
        return;
    }
    gtkterm_request_quit(g_app->term);
}

static void on_quit(GtkWidget *widget, gpointer data)
{
    (void)widget;
    (void)data;
    g_app->quit_requested = 1;
    dismiss_error_dialog();
    gtkterm_request_quit(g_app->term);
    if (!g_app->in_session) {
        gtk_main_quit();
    }
}

static gboolean on_delete(GtkWidget *widget, GdkEvent *event, gpointer data)
{
    (void)widget;
    (void)event;
    (void)data;
    g_app->quit_requested = 1;
    dismiss_error_dialog();
    gtkterm_request_quit(g_app->term);
    if (!g_app->in_session) {
        gtk_main_quit();
    }
    return TRUE;
}

static gboolean on_draw(GtkWidget *widget, cairo_t *cr, gpointer data)
{
    (void)widget;
    (void)data;
    gtkterm_draw(g_app->term, cr);
    return FALSE;
}

static gboolean on_key(GtkWidget *widget, GdkEventKey *event, gpointer data)
{
    (void)widget;
    (void)data;
    if (gtkterm_on_key(g_app->term, event->keyval, event->state)) {
        return TRUE;
    }
    return FALSE;
}

static gboolean on_button(GtkWidget *widget, GdkEventButton *event, gpointer data)
{
    (void)data;
    gtk_widget_grab_focus(widget);
    gtkterm_on_click(g_app->term, event->x, event->y);
    return TRUE;
}

static void on_term_changed(GtkComboBox *combo, gpointer data)
{
    int rows = 24;
    int cols = 80;
    const char *term_id;
    (void)data;
    if (g_app->in_session) {
        return;
    }
    term_id = gtk_combo_box_get_active_id(combo);
    gtkterm_geometry_for_type(term_id, &rows, &cols);
    gtkterm_set_geometry(g_app->term, rows, cols);
}

static void on_keyboard(GtkWidget *widget, gpointer data)
{
    GtkWidget *dialog;
    GtkWidget *view;
    GtkWidget *scroll;
    GtkWidget *content;
    (void)widget;
    (void)data;
    dialog = gtk_dialog_new_with_buttons("Keyboard", GTK_WINDOW(g_app->window),
                                         GTK_DIALOG_MODAL, "Close", GTK_RESPONSE_CLOSE, NULL);
    content = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(view), FALSE);
    gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(view)),
                             gtkterm_key_plan_text(), -1);
    scroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_size_request(scroll, 640, 420);
    gtk_container_add(GTK_CONTAINER(scroll), view);
    gtk_box_pack_start(GTK_BOX(content), scroll, TRUE, TRUE, 0);
    gtk_widget_show_all(dialog);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

static void on_about(GtkWidget *widget, gpointer data)
{
    char version[64];
    (void)widget;
    (void)data;
    snprintf(version, sizeof version, "%d.%d.%d (tn5250 %s)",
             VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, VERSION);
    gtk_show_about_dialog(GTK_WINDOW(g_app->window),
                          "program-name", PROJECT_NAME,
                          "version", version,
                          "comments", PROJECT_DESCRIPTION,
                          "license", "MIT",
                          NULL);
}

static gboolean on_blink(gpointer data)
{
    (void)data;
    if (g_app != NULL) {
        gtkterm_blink_tick(g_app->term);
    }
    return TRUE;
}

static gboolean on_shutdown(gpointer data)
{
    (void)data;
    g_app->quit_requested = 1;
    dismiss_error_dialog();
    gtkterm_request_quit(g_app->term);
    if (!g_app->in_session) {
        gtk_main_quit();
    }
    return FALSE;
}

static gboolean on_auto_connect(gpointer data)
{
    (void)data;
    connect_session();
    return FALSE;
}

static GtkWidget *menu_item(GtkWidget *menu, const char *label, GCallback callback)
{
    GtkWidget *item = gtk_menu_item_new_with_label(label);
    if (callback != NULL) {
        g_signal_connect(item, "activate", callback, NULL);
    }
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
    return item;
}

int gnome_app_run(int argc, char **argv)
{
    struct app_state app;
    char *incoming[SESSION_ARG_MAX];
    struct session_form form;
    int incoming_count;
    GtkWidget *root;
    GtkWidget *menu_bar;
    GtkWidget *session_menu;
    GtkWidget *session_item;
    GtkWidget *help_menu;
    GtkWidget *help_item;
    GtkWidget *row;
    GtkWidget *extra_row;
    GtkWidget *scroll;
    GtkWidget *connect_button;
    GtkWidget *disconnect_button;
    int index;
    int rows = 24;
    int cols = 80;

    memset(&app, 0, sizeof app);
    g_app = &app;
    incoming_count = collect_session_args(argc, argv, incoming, SESSION_ARG_MAX);
    session_form_clear(&form);
    if (incoming_count > 0) {
        session_form_from_args(&form, incoming_count, incoming);
    }
    app.shutdown_seconds = shutdown_seconds(argc, argv);
    if (!gtk_init_check(&argc, &argv)) {
        logger_error("GTK could not open a display");
        g_app = NULL;
        return 1;
    }
    app.term = gtkterm_new();
    if (app.term == NULL) {
        logger_error("could not create the terminal");
        g_app = NULL;
        return 1;
    }
    gtkterm_geometry_for_type(form.term_type, &rows, &cols);
    gtkterm_set_geometry(app.term, rows, cols);

    app.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(app.window), PROJECT_NAME);
    gtk_window_set_default_size(GTK_WINDOW(app.window), 960, 640);
    g_signal_connect(app.window, "delete-event", G_CALLBACK(on_delete), NULL);

    root = gtk_box_new(GTK_ORIENTATION_VERTICAL, 4);
    gtk_container_set_border_width(GTK_CONTAINER(root), 4);
    gtk_container_add(GTK_CONTAINER(app.window), root);

    menu_bar = gtk_menu_bar_new();
    session_item = gtk_menu_item_new_with_label("Session");
    session_menu = gtk_menu_new();
    menu_item(session_menu, "Connect", G_CALLBACK(on_connect));
    menu_item(session_menu, "Disconnect", G_CALLBACK(on_disconnect));
    menu_item(session_menu, "Quit", G_CALLBACK(on_quit));
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(session_item), session_menu);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), session_item);
    help_item = gtk_menu_item_new_with_label("Help");
    help_menu = gtk_menu_new();
    menu_item(help_menu, "Keyboard", G_CALLBACK(on_keyboard));
    menu_item(help_menu, "About", G_CALLBACK(on_about));
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(help_item), help_menu);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), help_item);
    gtk_box_pack_start(GTK_BOX(root), menu_bar, FALSE, FALSE, 0);

    row = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 4);
    gtk_box_pack_start(GTK_BOX(row), gtk_label_new("Host"), FALSE, FALSE, 0);
    app.host_entry = gtk_entry_new();
    gtk_widget_set_hexpand(app.host_entry, TRUE);
    g_signal_connect(app.host_entry, "activate", G_CALLBACK(on_connect), NULL);
    gtk_box_pack_start(GTK_BOX(row), app.host_entry, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(row), gtk_label_new("Map"), FALSE, FALSE, 0);
    app.map_entry = gtk_entry_new();
    gtk_entry_set_width_chars(GTK_ENTRY(app.map_entry), 6);
    gtk_entry_set_placeholder_text(GTK_ENTRY(app.map_entry), "37");
    gtk_box_pack_start(GTK_BOX(row), app.map_entry, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(row), gtk_label_new("Terminal"), FALSE, FALSE, 0);
    app.term_combo = gtk_combo_box_text_new();
    for (index = 0; k_term_ids[index] != NULL; index++) {
        gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(app.term_combo), k_term_ids[index], k_term_labels[index]);
    }
    gtk_combo_box_set_active_id(GTK_COMBO_BOX(app.term_combo), "");
    g_signal_connect(app.term_combo, "changed", G_CALLBACK(on_term_changed), NULL);
    gtk_box_pack_start(GTK_BOX(row), app.term_combo, FALSE, FALSE, 0);
    app.ssl_check = gtk_check_button_new_with_label("SSL");
    app.verify_check = gtk_check_button_new_with_label("Verify");
    app.ruler_check = gtk_check_button_new_with_label("Ruler");
    app.under_check = gtk_check_button_new_with_label("Underscores");
    gtk_box_pack_start(GTK_BOX(row), app.ssl_check, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(row), app.verify_check, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(row), app.ruler_check, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(row), app.under_check, FALSE, FALSE, 0);
    connect_button = gtk_button_new_with_label("Connect");
    gtk_box_pack_start(GTK_BOX(row), connect_button, FALSE, FALSE, 0);
    g_signal_connect(connect_button, "clicked", G_CALLBACK(on_connect), NULL);
    disconnect_button = gtk_button_new_with_label("Disconnect");
    gtk_box_pack_start(GTK_BOX(row), disconnect_button, FALSE, FALSE, 0);
    g_signal_connect(disconnect_button, "clicked", G_CALLBACK(on_disconnect), NULL);
    gtk_box_pack_start(GTK_BOX(root), row, FALSE, FALSE, 0);

    extra_row = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 4);
    gtk_box_pack_start(GTK_BOX(extra_row), gtk_label_new("Device"), FALSE, FALSE, 0);
    app.dev_entry = gtk_entry_new();
    gtk_entry_set_width_chars(GTK_ENTRY(app.dev_entry), 10);
    gtk_box_pack_start(GTK_BOX(extra_row), app.dev_entry, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(extra_row), gtk_label_new("Trace"), FALSE, FALSE, 0);
    app.trace_entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(extra_row), app.trace_entry, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(extra_row), gtk_label_new("Extra"), FALSE, FALSE, 0);
    app.extra_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(app.extra_entry), "ssl_ca_file= name=value +option");
    gtk_box_pack_start(GTK_BOX(extra_row), app.extra_entry, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(root), extra_row, FALSE, FALSE, 0);

    app.area = gtk_drawing_area_new();
    gtk_widget_set_can_focus(app.area, TRUE);
    gtk_widget_add_events(app.area, GDK_BUTTON_PRESS_MASK | GDK_KEY_PRESS_MASK);
    g_signal_connect(app.area, "draw", G_CALLBACK(on_draw), NULL);
    g_signal_connect(app.area, "key-press-event", G_CALLBACK(on_key), NULL);
    g_signal_connect(app.area, "button-press-event", G_CALLBACK(on_button), NULL);
    gtkterm_set_widget(app.term, app.area);
    scroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_widget_set_hexpand(scroll, TRUE);
    gtk_widget_set_vexpand(scroll, TRUE);
    gtk_container_add(GTK_CONTAINER(scroll), app.area);
    gtk_box_pack_start(GTK_BOX(root), scroll, TRUE, TRUE, 0);

    app.status = gtk_label_new("Disconnected");
    gtk_widget_set_halign(app.status, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(root), app.status, FALSE, FALSE, 0);

    apply_form_to_widgets(&form);
    gtk_widget_show_all(app.window);
    logger_info("gnome window ready");
    g_timeout_add(500, on_blink, NULL);
    if (app.shutdown_seconds > 0) {
        g_timeout_add_seconds(app.shutdown_seconds, on_shutdown, NULL);
    }
    if (form.host[0] != '\0') {
        g_idle_add(on_auto_connect, NULL);
    }
    gtk_main();
    if (app.term != NULL) {
        tn5250_terminal_destroy(app.term);
        app.term = NULL;
    }
    g_app = NULL;
    return 0;
}

}
