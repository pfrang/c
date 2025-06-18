
#include "headers.h"
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage %s: msg", argv[0]);
  }

  char *msg = argv[1];
  struct sockaddr_in serverAddr;
  int serverFd, wc, rc;

  MyHeader *recvHeader = calloc(1, BUFF_SIZE);
  serverFd = socket(AF_INET, SOCK_DGRAM, 0);

  memset(&serverAddr, 0, sizeof(serverAddr));
  serverAddr.sin_port = htons(8080);
  serverAddr.sin_family = AF_INET;

  socklen_t len = sizeof(serverAddr);
 int buffLen = htonl(strlen(msg));

  recvHeader->type = ACK;
  recvHeader->ackno = htons(0);
  recvHeader->buffLen = htonl(strlen(msg));
	msg[strlen(msg)] = '\n';

  strcpy(recvHeader->buff, msg);

  // memset(recvHeader->buff, *str, strlen(str));
  while (1) {

    wc = sendto(serverFd, recvHeader, BUFF_SIZE, 0,
                (struct sockaddr *)&serverAddr, len);

	fprintf(stderr, recvHeader->buff);


    if (wc < 0) {
      printf("Error sending msg\n");
      break;
    }

    memset(recvHeader, 0, BUFF_SIZE);
    rc = recvfrom(serverFd, recvHeader, BUFF_SIZE, 0,
                  (struct sockaddr *)&serverAddr, &len);
    if (rc < 0) {
      printf("Error receiving \n");
      continue;
    }
    printf("Received ackno  %d \n", ntohs(recvHeader->ackno));

    memset(recvHeader, 0, BUFF_SIZE);
  }

  close(serverFd);

  return 0;
}
