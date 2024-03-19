#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>

int main() {
  int fd = socket(AF_INET, SOCK_STREAM, 0);
  // Instead of this
  if (fd == -1) {
    perror("socket");
    return -1;
  }

  printf("%d\n", fd);
}
