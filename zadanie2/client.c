#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include "client.h"

static const char *client_name;

void handle_sigterm(int sig) {
    printf("%s: Terminating...\n", client_name);
    exit(0);
}

void handle_sigusr2(int sig) {
    printf("%s: Acknowledged\n", client_name);
}

void handle_sigint(int sig) {
    printf("%s: Shutting down\n", client_name);
    exit(0);
}

void client_logic(const char *name, int pipefd[2]) {
    client_name = name;
    signal(SIGTERM, handle_sigterm);
    signal(SIGUSR2, handle_sigusr2);
    signal(SIGINT, handle_sigint);

    printf("Imię: Client initialized\n");

    char buffer[100];
    close(pipefd[1]); // zamknij zapis

    while (read(pipefd[0], buffer, sizeof(buffer)) > 0) {
        if (strstr(buffer, "Who are you?")) {
            printf("I am %s\n", name);
        } else if (strstr(buffer, "Your PID?")) {
            printf("%s: PID is %d\n", name, getpid());
        }
    }

    close(pipefd[0]);
    pause(); // czeka na sygnały
}
