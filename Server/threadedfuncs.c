#include "headers.h"

#define BACKLOG 10

typedef struct passon {
    int argc;
    char *exename;
    char *port;
} passon;

void *get_in_addr(struct sockaddr *sa) {
    if (sa->sa_family==AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

void *networking(void *passing) {
    passon passed = *((struct passon*)(passing));
    printf("Networking thread reporting in...\nargc: %d\nexename: %s\nport: %s\n\n",
            passed.argc,
            &passed.exename[0], &passed.port[0]);

    const char *service;
    service=&passed.port[0];
    int rv;
    struct addrinfo hints;
    struct addrinfo *servinfo;

    memset(&hints, 0, sizeof hints);
    hints.ai_family=AF_UNSPEC;
    hints.ai_socktype=SOCK_STREAM;
    hints.ai_flags=AI_PASSIVE;

    if ((rv=getaddrinfo(NULL, service, &hints, &servinfo))!=0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        exit(1);
    }

    pthread_exit(NULL);
    return 0;
}

void *background(void *passing) {
    passon passed = *((struct passon*)(passing));
    printf("Background thread reporting in...\nargc: %d\nexename: %s\n\n",
            passed.argc,
            &passed.exename[0]);

    //something for the thread todo until something is implimented
    sleep(1);

    while (1>0) {
        sleep(2);
        printf("background thread still alive!\n\n");
    }

    pthread_exit(NULL);
    return 0;
}
