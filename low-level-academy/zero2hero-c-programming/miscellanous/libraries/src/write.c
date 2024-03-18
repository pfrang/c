#include <stdio.h>

#include "../include/write.h"
#include <string.h>
#include <unistd.h>

ssize_t write_to_file(int fd, char *input) {
  ssize_t bytes = write(fd, input, strlen(input));
  if (bytes == -1) {
    perror("write");
    return -1;
  }

  return bytes;
}
