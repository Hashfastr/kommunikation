#include <gtk/gtk.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 2
pthread_t backgroundProcesses[NUM_THREADS];

typedef struct passon {
    int argc;
    char *argv;
} passon;

void *networking(void *passing); 
void *background(void *passing);

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

    gtk_init(&argc, &argv);

    gtk_main();

    return 0;
}

void *networking(void *passing) {
    passon passed = *((struct passon*)(passing));
    printf("Networking thread reporting in...\nargc: %d\nargv[0]: %s\n\n", passed.argc, &passed.argv[0]);
    pthread_exit(NULL);
    return 0;
}

void *background(void *passing) {
    passon passed = *((struct passon*)(passing));
    printf("Background thread reporting in...\nargc: %d\nargv[0]: %s\n\n", passed.argc, &passed.argv[0]);
    pthread_exit(NULL);
    return 0;
}
