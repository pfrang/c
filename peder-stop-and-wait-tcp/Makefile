CC = gcc
CFLAGS = -Wall -Wextra -O2

all: client server

client: client.c headers.h
	$(CC) $(CFLAGS) -o client client.c

server: server.c headers.h
	$(CC) $(CFLAGS) -o server server.c

clean:
	rm -f client server

