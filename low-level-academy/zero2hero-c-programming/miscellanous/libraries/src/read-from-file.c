#include <stdio.h>
#include <unistd.h>

#include "../include/read-from-file.h"

int read_from_file(int fd, char *output) {
  ssize_t bytesRead;
  if (lseek(fd, 0, SEEK_END) == 0) {
    printf("File is empty\n");
    return -1;
  }
  lseek(fd, 0, SEEK_SET); // Reset pointer

  while ((bytesRead = read(fd, output, 99)) > 0) {
    output[bytesRead] = '\0';
    printf("%s", output);
  }

  if (bytesRead == -1) {
    perror("read");
    return -1;
  }

  return 0;
};
