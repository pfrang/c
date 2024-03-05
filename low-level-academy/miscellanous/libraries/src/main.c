#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "../include/file.h"
#include "../include/read-from-file.h"
#include "../include/write.h"

void flushStdin(void);
int read_from_file(int fd, char *output);

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage %s <filename>: \n", argv[0]);
    return 0;
  }

  int fd = open_file_rw(argv[1]);

  if (fd == -1) {
    return -1;
  }

  int choice;
  printf("Select an opion:\n");
  printf("1. Read file\n");
  printf("2. Write to file:\n");
  scanf("%d", &choice);
  flushStdin();

  switch (choice) {
  case 1: {
    char *output = malloc(100);
    int read = read_from_file(fd, output);
    free(output);
    break;
  }
  case 2: {
    char *input = malloc(100);
    printf("What do you want to write to file %s \n", argv[1]);
    fgets(input, 100, stdin);
    int writd = write_to_file(fd, input);
    if (writd == -1) {
      return -1;
    }
    free(input);
    break;
  default:
    printf("Illegal number %d", choice);
    return -1;
  }
  }

  close(fd);
  return 0;
}

void flushStdin() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF) {
  };
}
