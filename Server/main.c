#include "headers.h"
#include "threadedfuncs.c"
#include "callbacks.c"

#define NUM_THREADS 2
pthread_t backgroundProcesses[NUM_THREADS];

int main (int argc, char *argv[]) {
    //parse arguments
    if (argc!=2) {
        printf("Error: Usage: %s [PORT NUMBER] [OPTIONS]\n", argv[0]);
        return 0;
    }

    passon *tobepassed=malloc(sizeof *tobepassed);
    
    int graphical=0;
    tobepassed->port=0;
    for (int i=0; i<argc; i++) {
        switch (argv[i][1]) {
            case 'g':
                if (i==1) {
                    printf("Error: Usage: %s [PORT NUMBER] [OPTIONS]\n", argv[0]);
                    return 0;
                }
                graphical=1;
                break;

            default:
                break;
        }
    }

    if (atoi(argv[1]) > 65535 || atoi(argv[1]) < 1) {
        printf("Error: Port number must be in this range: [1, 65535]\n");
    }

    printf("Initalizing background threads...\n");

    tobepassed->argc=argc;
    tobepassed->exename=argv[0];
    tobepassed->port=argv[1];

    printf("creating networking thread...\n");
    pthread_create(&backgroundProcesses[0], NULL, networking, tobepassed);
    printf("creating background thread...\n");
    pthread_create(&backgroundProcesses[1], NULL, background, tobepassed);

    printf("done.\n");

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


