#include "headers.h"
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

void flipAck(MyHeader *recvHeader) {
  recvHeader->ackno = recvHeader->ackno ^ 1;
}

int main(int argc, char *argv[]) {

  struct sockaddr_in serverAddr;
  int serverFd, wc, rc;

  MyHeader *recvHeader = calloc(1, BUFF_SIZE);
  serverFd = socket(AF_INET, SOCK_DGRAM, 0);

  memset(&serverAddr, 0, sizeof(serverAddr));
  serverAddr.sin_port = htons(8080);
  serverAddr.sin_family = AF_INET;

  socklen_t len = sizeof(serverAddr);

  while (1) {
    char *tmpBuff = calloc(1, PAYLOAD_SIZE);

    recvHeader->type = ACK;
    recvHeader->ackno = 0;
    printf("Waiting for input...\n");
    scanf("%s", tmpBuff);
    int buffLen = strlen(tmpBuff);
    tmpBuff[buffLen] = '\0';

    wc = sendto(serverFd, recvHeader, BUFF_SIZE, 0,
                (struct sockaddr *)&serverAddr, len);

    printf("\n");

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
    printf("Connectino established, sending payload...\n");

    memcpy(recvHeader->buff, tmpBuff, buffLen);
    recvHeader->buff[buffLen] = '\0';

    recvHeader->type = DATA;
    recvHeader->buffLen = htonl(buffLen);

    wc = sendto(serverFd, recvHeader, BUFF_SIZE, 0,
                (struct sockaddr *)&serverAddr, len);

    memset(recvHeader, 0, BUFF_SIZE);
  }

  close(serverFd);

  return 0;
}
