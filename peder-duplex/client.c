
#include "headers.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define LENCONST 64

int main(int argc, char *argv[]) {

    int clientSocket, wc;
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

    for (int i = 0; i < 10; i++) {
        headerData.type = htonl(i + 1);
        headerData.ackno = htonl(11 - i);
        memcpy(buff, &headerData, sizeof(headerData));
        memcpy(buff + sizeof(headerData), msg, strlen(msg) + 1);

        wc = sendto(clientSocket, buff, sizeof(headerData) + strlen(msg) + 1, 0, (struct sockaddr *)&serverAddr,
                    sizeof(serverAddr));
        if (wc < 0) {
            perror("sendto error");
            continue;
        }

        printf("Sent type:%d and ackno:%d with msg:%s\n", ntohl(headerData.type), ntohl(headerData.ackno), msg);
        memset(buff, 0, BUFF_SIZE);
        sleep(1);
    }
}
