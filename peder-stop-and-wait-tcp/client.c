
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


  struct sockaddr_in serverAddr;
  int serverFd, wc, rc;

  MyHeader *recvHeader = calloc(1, BUFF_SIZE);
  serverFd = socket(AF_INET, SOCK_DGRAM, 0);

  memset(&serverAddr, 0, sizeof(serverAddr));
  serverAddr.sin_port = htons(8080);
  serverAddr.sin_family = AF_INET;

  socklen_t len = sizeof(serverAddr);
  int buffLen = strlen(argv[1]);

	if(buffLen > PAYLOAD_SIZE)  {
		printf("Too bug string\n");
		return 0;
	}


  recvHeader->type = ACK;
  recvHeader->ackno = htons(0);
  recvHeader->buffLen = htonl(buffLen);
	char *msg = malloc(buffLen);
	msg[buffLen] = '\0';

  strcpy(recvHeader->buff, argv[1]);

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
