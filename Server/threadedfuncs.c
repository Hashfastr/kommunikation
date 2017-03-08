#include "headers.h"

typedef struct passon {
    int argc;
    char *argv;
} passon;

void *networking(void *passing) {
    passon passed = *((struct passon*)(passing));
    printf("Networking thread reporting in...\nargc: %d\nargv[0]: %s\n\n",
            passed.argc,
            &passed.argv[0]);

    //something for the thread todo until something is implimented
    while (1>0) {
        sleep(2);
        printf("networking thread still alive!\n\n");
    }

    pthread_exit(NULL);
    return 0;
}

void *background(void *passing) {
    passon passed = *((struct passon*)(passing));
    printf("Background thread reporting in...\nargc: %d\nargv[0]: %s\n\n",
            passed.argc,
            &passed.argv[0]);
    
    //something for the thread todo until something is implimented
    sleep(1);

    while (1>0) {
        sleep(2);
        printf("background thread still alive!\n\n");
    }

    pthread_exit(NULL);
    return 0;
}
