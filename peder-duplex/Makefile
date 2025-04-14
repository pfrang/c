CC = gcc
CFLAGS = -Wall -g

all: server client

server: server.c headers.h
	$(CC) $(CFLAGS) -o server server.c

client: client.c headers.h
	$(CC) $(CFLAGS) -o client client.c

clean:
	rm -f server client
