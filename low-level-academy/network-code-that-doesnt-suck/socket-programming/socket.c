#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>
int main() {

  struct sockaddr_in serverInfo = {0};

  struct sockaddr_in clientInfo = {0};

  int clientSize = 0;
  serverInfo.sin_family = AF_INET;
  serverInfo.sin_addr.s_addr = 0; // we are accepting connections from every iip
  serverInfo.sin_port = htons(5555);
  int fd = socket(AF_INET, SOCK_STREAM, 0); // its the same as open()
  if (fd == -1) {
    perror("socket");
    return -1;
  }

  printf("%d\n", fd);

  // bind
  if (bind(fd, (struct sockaddr *)&serverInfo, sizeof(serverInfo)) == -1) {
    perror("bind");
    close(fd);
    return -1;
  }
  // listen
  if (listen(fd, 0) == -1) {
    perror("listen");
    close(fd);
    return -1;
  }; // Second argument is how many processes it can put in baclog. 0 means
     // unlimited
  // accept
  int cfd = accept(fd, (struct sockaddr *)&clientInfo, &clientSize);
  if (cfd == -1) {
    perror("accept");
    close(fd);
    return -1;
  }

  close(cfd);
}
