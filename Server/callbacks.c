#include "headers.h"

int quit () {
    g_print("quitting...\n");
    gtk_main_quit();

    return(TRUE);
}
