// main.cpp
// Logger verbs stay headless. Every other run opens the GNOME 5250 window.

#include "gnome_app.h"
#include "logger.h"
#include "project.h"

int main(int argc, char **argv)
{
    logger_output_init(argc, argv);
    if (logger_is_test_verb()) {
        logger_info("test log");
        return 0;
    }
    if (gnome_app_headless(argc, argv)) {
        return gnome_app_headless_status();
    }
    logger_info("Starting %s %d.%d.%d",
                PROJECT_NAME, VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);
    return gnome_app_run(argc, argv);
}
