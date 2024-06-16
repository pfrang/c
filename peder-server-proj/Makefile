TARGET_SRV = bin/server
TARGET_CLI = bin/client

SRC_SRV = $(wildcard src/server.c)
OBJ_SRV = $(SRC_SRV:src/server.c=obj/server.o)

SRC_CLI = $(wildcard src/client.c)
OBJ_CLI = $(SRC_CLI:src/client.c=obj/client.o)

run: clean default
		./$(TARGET_SRV)

default: $(TARGET_SRV) $(TARGET_CLI)

clean:
		rm -f obj/*.o
		rm -f bin/*

$(TARGET_SRV): $(OBJ_SRV)
		gcc -o $@ $^

$(OBJ_SRV): src/server.c
		gcc -c $< -o $@ -Iinclude

$(TARGET_CLI): $(OBJ_CLI)
		gcc -o $@ $^

$(OBJ_CLI): src/client.c
		gcc -c $< -o $@ -Iinclude
