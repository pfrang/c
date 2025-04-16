
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "headers.h"

int main(int argc, char *argv[]) {
  int clientSocket, wc, rc;
  char buff[BUFF_SIZE];
  struct sockaddr_in serverAddr;

  clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
  if (clientSocket < 0) {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  struct MyHeader headerData;

  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(8080);

  char *msg = calloc(0, BUFF_SIZE - HEADER_SIZE - 1);

  if (argc == 2) {
    msg = argv[1];
  } else {
    msg = "Hei hei";
  }

  struct timeval start, end;
  gettimeofday(&start, NULL);  // Start timer

  socklen_t addr_len = sizeof(serverAddr);
  for (int i = 0; i < 10; i++) {
    headerData.type = htonl(rand() % 3);
    headerData.ackno = 0;
    memcpy(buff, &headerData, sizeof(headerData));
    memcpy(buff + sizeof(headerData), msg, strlen(msg) + 1);

    wc = sendto(clientSocket, buff, sizeof(headerData) + strlen(msg) + 1, 0,
                (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    if (wc < 0) {
      perror("sendto error");
      continue;
    }

    printf("Sent type:%d and ackno:%d with msg:%s\n", ntohl(headerData.type),
           ntohl(headerData.ackno), msg);

    memset(buff, 0, BUFF_SIZE);
    rc = recvfrom(clientSocket, buff, BUFF_SIZE, 0,
                  (struct sockaddr *)&serverAddr, &addr_len);

    if (rc < 0) {
      perror("recvfrom error()");
    }

    printf("Received response: %s\n", buff);

    memset(&headerData, 0, sizeof(headerData));
    memset(buff, 0, BUFF_SIZE);

    sleep(1);
    printf("-----%d iteration finished------------\n", i);
  }

  gettimeofday(&end, NULL);  // End timer

  long seconds = end.tv_sec - start.tv_sec;
  long useconds = end.tv_usec - start.tv_usec;
  long total_micro = seconds * 1000000 + useconds;

  printf("Elapsed time: %.3f seconds\n", total_micro / 1e6);
  close(clientSocket);
}
