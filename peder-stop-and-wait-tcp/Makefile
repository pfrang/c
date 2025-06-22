CC = gcc
CFLAGS = -Wall -Wextra -O2

all: client server

client: client.c headers.h shared.h
	$(CC) $(CFLAGS) -o build/client client.c shared.c

server: server.c headers.h shared.h
	$(CC) $(CFLAGS) -o server server.c shared.c

clean:
	rm -f /build

