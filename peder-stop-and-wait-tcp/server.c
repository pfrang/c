#include "headers.h"
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080

int main() {
  struct sockaddr_in serverAddr, clientAddr;
  int serverFd, rc, wc;

  MyHeader *recvHeader = calloc(1, BUFF_SIZE);
  serverFd = socket(AF_INET, SOCK_DGRAM, 0);

  memset(&serverAddr, 0, sizeof(serverAddr));
  serverAddr.sin_port = htons(8080);
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = INADDR_ANY;

  if (bind(serverFd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
    perror("bind");
    exit(EXIT_FAILURE);
    close(serverFd);
  }

  socklen_t len = sizeof(clientAddr);
  printf("UDP server listening on port %d...\n", PORT);
  while (1) {

    rc = recvfrom(serverFd, recvHeader, BUFF_SIZE, 0,
                  (struct sockaddr *)&clientAddr, &len);

    if (rc < 0) {
      printf("Error in rc %d", rc);
    }

    printf("Received type %d, ackno %d, buffLen %d, buff %s\n",
           ntohs(recvHeader->type), ntohs(recvHeader->ackno),
           ntohl(recvHeader->buffLen), recvHeader->buff);
    memset(recvHeader, 0, BUFF_SIZE);
  }
  close(serverFd);
  return 0;
}
