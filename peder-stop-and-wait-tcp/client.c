
#include "headers.h"
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
  struct sockaddr_in serverAddr;
  int serverFd, wc, rc;
  MyHeader *recvHeader = calloc(1, BUFF_SIZE);

  serverFd = socket(AF_INET, SOCK_DGRAM, 0);

  memset(&serverAddr, 0, sizeof(serverAddr));
  serverAddr.sin_port = htons(8080);
  serverAddr.sin_family = AF_INET;

  socklen_t len = sizeof(serverAddr);

  char *str = "Test msh jasåjaså\n";

  recvHeader->type = ACK;
  recvHeader->ackno = htons(1);
  recvHeader->buffLen = htonl(strlen(str));

  strcpy(recvHeader->buff, str);

  // memset(recvHeader->buff, *str, strlen(str));
  while (1) {

    wc = sendto(serverFd, recvHeader, BUFF_SIZE, 0,
                (struct sockaddr *)&serverAddr, len);

    if (wc < 0) {
      printf("Error sending msg\n");
    }
    break;

    memset(recvHeader, 0, BUFF_SIZE);
  }

  close(serverFd);

  return 0;
}
