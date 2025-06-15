#include <stdio.h>
#include <unistd.h>
#include "server.h"

void server_logic(int pipefd[2]) {
    close(pipefd[0]); // zamknij odczyt
    write(pipefd[1], "Hello clients! Who are you?", 28);
    sleep(1);
    write(pipefd[1], "Hello clients! Your PID?", 26);
    close(pipefd[1]);
}

client.h

#ifndef CLIENT_H
#define CLIENT_H

void client_logic(const char *name, int pipefd[2]);

#endif
