#include "headers.h"
#include "threadedfuncs.c"
#include "callbacks.c"

#define NUM_THREADS 2
pthread_t backgroundProcesses[NUM_THREADS];

int main (int argc, char *argv[]) {
    printf("Initalizing background threads...\n");
    

    passon *tobepassed=malloc(sizeof *tobepassed);

    tobepassed->argc=argc;
    tobepassed->argv=*argv;

    printf("creating networking thread...\n");
    pthread_create(&backgroundProcesses[0], NULL, networking, tobepassed);
    printf("creating background thread...\n");
    pthread_create(&backgroundProcesses[1], NULL, background, tobepassed);

    printf("done.\n");

    //parse arguments
    int graphical;
    for (int i=0; i<argc; i++) {
        switch (argv[i][1]) {
            case 'g':
                graphical=1;
                break;
            default:
                break;
        }
    }

    if (graphical) {
        gtk_init(&argc, &argv);
        
        GtkWidget *window;
        GtkWidget *button;

        window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        
        g_signal_connect(window, "delete_event", G_CALLBACK(quit), NULL);
        g_signal_connect(window, "destroy", G_CALLBACK(quit), NULL);

        gtk_container_set_border_width(GTK_CONTAINER(window), 10);
        button = gtk_button_new_with_label("No gui yet sorry :(\n\nclick to quit");

        g_signal_connect(button, "clicked", G_CALLBACK(quit), window);

        gtk_container_add(GTK_CONTAINER(window), button);

        gtk_widget_show(button);
        gtk_widget_show(window);

        gtk_main();
    }

    else pthread_join(backgroundProcesses[1], NULL);

    return 0;
}


