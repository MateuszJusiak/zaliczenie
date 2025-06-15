CC=gcc
CFLAGS=-Wall

all: main

server: server.c
 $(CC) $(CFLAGS) -c server.c

client: client.c
 $(CC) $(CFLAGS) -c client.c

main: server client main.c
 $(CC) $(CFLAGS) main.c server.c client.c -o main

clean:
 rm -f *.o main
