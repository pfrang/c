CC = gcc
CFLAGS = -Wall -Wextra
LDLIBS = -luuid

TARGET = main
SRCS = main.c

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS) $(LDLIBS)

clean:
	rm -f $(TARGET)
