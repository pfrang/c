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

#define PORT 8080
#define MAX_CLIENTS 1000

struct MyHeader Clients[MAX_CLIENTS];

int main() {

  int clientLen = 0;
  struct sockaddr_in serverAddr, clientAddr;
  int serverFd, rc, wc, isNewClient;

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

    rc = recvfrom(serverFd, recvHeader, BUFF_SIZE, 0, (struct sockaddr *)&clientAddr, &len);
    isNewClient = 1;

    int recvAckno = ntohs(recvHeader->ackno);
    enum PacketType recvType = recvHeader->type;
    short srcPort = recvHeader->src_port;
    u_int32_t srcIP = recvHeader->src_ip;

    for (int i = 0; i < clientLen + 1; i++) {
      if (Clients[i].src_ip == srcIP && Clients[i].src_port == srcPort) {
        isNewClient = 0;
        break;
      }
    }

    if (isNewClient) {
      printf("New client has connected, expecting ACK\n");
      if (recvType != ACK) {
        printf("Did not receive ACK\n");
        continue;
      }

      // Add client to list
      if (clientLen < MAX_CLIENTS) {
        Clients[clientLen++] = *recvHeader;
      } else {
        printf("Max clients reached!\n");
      }
    } else {
      printf("Client exists\n");
    }

    switch (recvType) {
    case ACK: {
      printf("Received ACK\n");
      break;
    }
    case DATA: {
      printf("Received DATA\n");
      break;
    }
    case RESET: {
      printf("Received RESET\n");
      break;
    }
    }

    print_zulu_time();

    if (rc < 0) {
      printf("Error in rc %d", rc);
    }

    char ipStr[INET_ADDRSTRLEN];
    struct in_addr ipAddr = {.s_addr = recvHeader->src_ip};
    inet_ntop(AF_INET, &ipAddr, ipStr, sizeof(ipStr));

    printf("Received type %u, ackno %d, src ip: %s, src port %hd, buffLen %d, "
           "buff: %s\n",
           recvHeader->type, ntohs(recvHeader->ackno), ipStr, srcPort, ntohl(recvHeader->buffLen), recvHeader->buff);

    MyHeader sendHeader;
    sendHeader.ackno = htons(1);

    printf("sending data..\n");
    print_zulu_time();
    wc = sendto(serverFd, &sendHeader, sizeof(sendHeader), 0, (struct sockaddr *)&clientAddr, len);
    if (wc < 0) {
      printf("Error sending\n");
      continue;
    }

    // expectedAckno = recvAckno ^ 1;
    memset(recvHeader, 0, BUFF_SIZE);
  }
  close(serverFd);
  return 0;
}
