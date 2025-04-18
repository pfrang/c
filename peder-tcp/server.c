
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "headers.h"
#define PORT 8080

void unpack(char *buff, int n) {
  sleep(1);
  char receivedBuff[BUFF_SIZE]; // Buffer to store the message
  struct MyHeader received;

  // Print the raw buffer data for debugging

  // Unpack header data
  memcpy(&received.type, buff, sizeof(int));
  memcpy(&received.ackno, buff + sizeof(int), sizeof(int));
  memcpy(receivedBuff, buff + HEADER_SIZE, BUFF_SIZE - HEADER_SIZE);
  printf("DATA: Received payload: type: %d and ackno: %d with msg: %s\n",
         ntohl(received.type), ntohl(received.ackno), receivedBuff);
}

int main() {
  int server_fd, wc;
  struct sockaddr_in serverAddr, clientAddr;
  char buff[BUFF_SIZE];
  char *res = calloc(1, PAYLOAD_SIZE);

  server_fd = socket(AF_INET, SOCK_DGRAM, 0);

  memset(&serverAddr, 0, sizeof(serverAddr));
  serverAddr.sin_port = htons(8080);
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = INADDR_ANY;

  if (bind(server_fd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
    perror("bind failed");
    close(server_fd);
    exit(EXIT_FAILURE);
  }

  printf("UDP server listening on port %d...\n", PORT);

  // struct timeval start, end;
  // gettimeofday(&start, NULL); // Start timer

  struct MyHeader headerData;
  socklen_t len = sizeof(clientAddr);

  while (1) {

    while (waitpid(-1, NULL, WNOHANG) > 0)
      ;

    int rc = recvfrom(server_fd, buff, BUFF_SIZE - 1, 0,
                      (struct sockaddr *)&clientAddr, &len);

    if (rc < 0) {
      perror("recvfrom error");
      continue;
    }

    enum PacketType type;
    memcpy(&type, buff, sizeof(int));
    int ackno;
    memcpy(&ackno, buff + sizeof(int), sizeof(int));

    type = ntohl(type);
    ackno = ntohl(ackno);
    printf("Processing %s:%d with type %d.....\n",
           inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port), type);

    switch (type) {
    case DATA: {
      if (ackno == 1) {

        // strncpy(res, "Data was received", PAYLOAD_SIZE - 1);
        // printf("Received data: %s\n\n", res);
        unpack(buff, BUFF_SIZE);
      } else {
        printf("Received DATA but unexpected ackno: %d\n", ackno);
      }
      break;
      // pid_t pid = fork();
      // if (pid < 0) {
      //   perror("fork() faild");
      //   close(server_fd);
      //   return -1;
      // } else if (pid > 0) {
      //   printf("I am parent with pid %d\n", pid);
      // } else if (pid == 0) {
      //   unpack(buff, rc);
      //   printf("Now exiting child process\n");
      //   wc = sendto(server_fd, res, BUFF_SIZE, 0,
      //               (struct sockaddr *)&clientAddr, sizeof(clientAddr));
      //   if (wc < 0) {
      //     perror("sendto err()");
      //     continue;
      //   }
      //
      //   memset(buff, 0, BUFF_SIZE);
      //
      //   exit(0);
      //   break;
      // }
    }
    case ACK: {
      printf("Received ack, now waiting 2 sec\n");
      headerData.ackno = htonl(0);
      headerData.type = htonl(ACK);
      memcpy(res, &headerData, sizeof(headerData));
      sleep(2);
      wc = sendto(server_fd, res, sizeof(headerData), 0,
                  (struct sockaddr *)&clientAddr, sizeof(clientAddr));

      if (wc < 0) {
        perror("sendto err()");
        continue;
      }
      printf("Ack was sent back\n");
      break;
    }
    case RESET: {
      printf("Received reset\n");
      strncpy(res, "Reset was received, nothins is done\n", PAYLOAD_SIZE - 1);
      break;
    }
    }

    memset(&headerData, 0, sizeof(headerData));
    memset(&buff, 0, BUFF_SIZE);
    memset(res, 0, PAYLOAD_SIZE);

    // gettimeofday(&end, NULL); // End timer
    //
    // long seconds = end.tv_sec - start.tv_sec;
    // long useconds = end.tv_usec - start.tv_usec;
    // long total_micro = seconds * 1000000 + useconds;
    //
    // printf("Elapsed time: %.3f seconds\n", total_micro / 1e6);
  }

  close(server_fd);
  free(res);
  return 0;
}
