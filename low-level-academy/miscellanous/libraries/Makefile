# Variables
CC = gcc
CFLAGS = -Iinclude
SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))

# Default target
default: build
# Build target
build: $(OBJ)
	$(CC) $(CFLAGS) -o bin/program $^

# Rule to build object files
obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target
clean:
	rm -f obj/*.o bin/program
