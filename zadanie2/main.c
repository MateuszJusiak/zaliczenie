#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "server.h"
#include "client.h"

int main() {
    int pipefd[2];
    pipe(pipefd);

    pid_t clients[4];
    const char *names[] = {"Anna", "Paul", "Rick", "Nina"};

    for (int i = 0; i < 4; i++) {
        if ((clients[i] = fork()) == 0) {
            client_logic(names[i], pipefd);
            exit(0);
        }
    }

    server_logic(pipefd);

    for (int i = 0; i < 4; i++) wait(NULL);

    return 0;
}
