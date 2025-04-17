
#include <arpa/inet.h>
#include <linux/limits.h>
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

  char *msg = calloc(1, PAYLOAD_SIZE);
  if (!msg) {
    perror("calloc");
    exit(0);
  }

  if (argc == 2) {
    strncpy(msg, argv[1], PAYLOAD_SIZE);
  } else {
    strncpy(msg, "Some random data", PAYLOAD_SIZE);
  }

  struct timeval start, end;
  gettimeofday(&start, NULL); // Start timer

  socklen_t addr_len = sizeof(serverAddr);
  int receivedAck, receivedType;
  for (int i = 0; i < 5; i++) {
    printf("-----%d iteration starting------------\n", i);

    memset(buff, 0, BUFF_SIZE);
    headerData.type = htonl(ACK);
    headerData.ackno = htonl(0);
    memcpy(buff, &headerData, sizeof(headerData));
    // Send ack
    printf("Sending ack\n");
    wc = sendto(clientSocket, buff, sizeof(headerData), 0, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    if (wc < 0) {
      perror("sendto error");
      continue;
    }

    memset(buff, 0, BUFF_SIZE);
    rc = recvfrom(clientSocket, buff, BUFF_SIZE, 0, (struct sockaddr *)&serverAddr, &addr_len);

    if (rc < 0) {
      perror("recvfrom err()");
      exit(0);
    }
    memcpy(&receivedType, buff, sizeof(int));
    receivedType = ntohl(receivedType);
    memcpy(&receivedAck, buff + sizeof(int), sizeof(int));
    receivedAck = ntohl(receivedAck);
    printf("Received response type %d and ack %d\n", receivedType, receivedAck);

    if (receivedType != ACK) {
      printf("Failed to receive ack, trying again\n");
      continue;
    }

    memset(buff, 0, BUFF_SIZE);

    headerData.type = htonl(DATA);
    headerData.ackno = htonl(receivedAck + 1);
    memcpy(buff, &headerData, sizeof(headerData));

    memcpy(buff + sizeof(headerData), msg, strlen(msg) + 1);

    wc = sendto(clientSocket, buff, sizeof(headerData) + strlen(msg) + 1, 0, (struct sockaddr *)&serverAddr,
                sizeof(serverAddr));

    printf("Sent type:%d and ackno:%d with msg:%s\n", ntohl(headerData.type), ntohl(headerData.ackno), msg);

    if (wc < 0) {
      printf("sendto data err(), trying to re-establish\n");
      continue;
    }

    printf("Data was sent: %s\n", msg);

    memset(&headerData, 0, sizeof(headerData));
    memset(buff, 0, BUFF_SIZE);

    printf("-----%d iteration finished------------\n\n", i);
    sleep(1);
  }

  gettimeofday(&end, NULL); // End timer

  long seconds = end.tv_sec - start.tv_sec;
  long useconds = end.tv_usec - start.tv_usec;
  long total_micro = seconds * 1000000 + useconds;

  printf("Elapsed time: %.3f seconds\n", total_micro / 1e6);
  close(clientSocket);
  free(msg);
}
