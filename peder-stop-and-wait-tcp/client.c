#include "headers.h"
#include "shared.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

void flipAck(MyHeader *recvHeader) { recvHeader->ackno = recvHeader->ackno ^ 1; }

int main(int argc, char *argv[]) {
  struct sockaddr_in serverAddr, clientAddr;
  socklen_t clientLen = sizeof(clientAddr);
  int serverFd, wc, rc;

  MyHeader *recvHeader = calloc(1, BUFF_SIZE);
  char *tmpBuff = calloc(1, PAYLOAD_SIZE);

  serverFd = socket(AF_INET, SOCK_DGRAM, 0);

  memset(&serverAddr, 0, sizeof(serverAddr));
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(8080);
  inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

  // "Connect" the UDP socket to the destination
  if (connect(serverFd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
    perror("connect");
    exit(EXIT_FAILURE);
  }

  // Now that the socket is connected, get our local address
  if (getsockname(serverFd, (struct sockaddr *)&clientAddr, &clientLen) == -1) {
    perror("getsockname");
    exit(EXIT_FAILURE);
  }

  in_addr_t local_ip = clientAddr.sin_addr.s_addr;
  u_int16_t local_port = clientAddr.sin_port;
  printf("Local ip %d, port %u\n", local_ip, ntohs(local_port));

  // Establish connection
  // Fill out header
  recvHeader->type = ACK;
  recvHeader->ackno = 0;
  recvHeader->src_ip = local_ip;
  recvHeader->src_port = local_port;

  // Send ACK packet
  printf("Sending packet to establish connection..\n");
  print_zulu_time();
  wc = send(serverFd, recvHeader, BUFF_SIZE, 0);
  printf("Sent ACK\n");

  if (wc < 0) {
    perror("send");
    exit(0);
  }

  memset(recvHeader, 0, BUFF_SIZE);

  // Receive response
  rc = recv(serverFd, recvHeader, BUFF_SIZE, 0);
  if (rc < 0) {
    perror("recv");
    exit(0);
  }

  printf("Received ackno: %d\n", ntohs(recvHeader->ackno));
  printf("Connection established...\n");

  while (1) {
    printf("Waiting for input...\n");
    scanf("%s", tmpBuff);
    int buffLen = strlen(tmpBuff);
    tmpBuff[buffLen] = '\0';
    // Now send the actual DATA payload
    memcpy(recvHeader->buff, tmpBuff, buffLen);
    recvHeader->buff[buffLen] = '\0';
    recvHeader->type = DATA;
    recvHeader->buffLen = htonl(buffLen);
    recvHeader->src_ip = local_ip;
    recvHeader->src_port = local_port;

    print_zulu_time();
    wc = send(serverFd, recvHeader, BUFF_SIZE, 0);
    printf("Sent payload, now waiting for ACK...\n");

    rc = recv(serverFd, recvHeader, BUFF_SIZE, 0);
    if (rc < 0) {
      perror("recv");
      exit(0);
    }
    printf("Received ACK %d\n", ntohs(recvHeader->ackno));

    memset(recvHeader, 0, BUFF_SIZE);
  }

  close(serverFd);
  return 0;
}
