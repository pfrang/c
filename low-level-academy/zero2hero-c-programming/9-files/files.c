#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char *argv[]) {
  // Apparently in Linux everything is a file and on open the kernel always returns an integer
  // "describing" the current file (whatever that means)
  // the open() f.example will return whats called a file descriptor int, int fd = open() etc
  // the kernel will return a number describing what file we want to access
  //
  // 0 = stdin
  // 1 = stdout
  // 2 = stderr

  if (argc != 2) {
    printf("Usage: %s <filename>\n", argv[0]);
    return 0;
  }
  
  int fd = open(argv[1], O_RDWR | O_CREAT, 0644); // Last argument is permission, standard for non private
  printf("File descriptior %d\n", fd);
  if (fd == -1) {
    perror("open");
    return -1;
  }

  char *s = "Hello good sir\n";

  write(fd, s, strlen(s));
  close(fd);

  return 0;
}

