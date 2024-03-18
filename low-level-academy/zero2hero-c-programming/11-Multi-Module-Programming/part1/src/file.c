#include "file.h"
#include <stdio.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int open_file_rw(char *filename) {
  int fd = open(filename, O_RDWR);
  if (fd == -1) {
    perror("open");
    return fd;
  }
  return fd;
}
