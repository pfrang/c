#include "../include/file.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
int open_file_rw(char *path) {
  int fd = open(path, O_APPEND | O_RDWR, 0644);
  if (fd == -1) {
    perror("open");
    return -1;
  }
  return fd;
}
