
#include "headers.h"
#include <arpa/inet.h>
#include <netinet/in.h>
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
#define PORT 8080

void unpack(char *buff, int n) {
    sleep(1);
    char receivedBuff[BUFF_SIZE - HEADER_SIZE + 1]; // Buffer to store the message
    struct MyHeader received;

    // Print the raw buffer data for debugging

    // Unpack header data
    memcpy(&received.type, buff, sizeof(int));
    memcpy(&received.ackno, buff + sizeof(int), sizeof(int));
    memcpy(receivedBuff, buff + HEADER_SIZE, BUFF_SIZE - HEADER_SIZE + 1);
    printf("Received type: %d and ackno: %d with msg: %s\n", ntohl(received.type), ntohl(received.ackno), receivedBuff);
}

int main() {

    int server_fd;
    struct sockaddr_in serverAddr, clientAddr;
    char buff[BUFF_SIZE];

    server_fd = socket(AF_INET, SOCK_DGRAM, 0);

    int opt = 1;

    // if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
    //     perror("setsockopt");
    //     exit(EXIT_FAILURE);
    // }

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

    while (1) {

        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(server_fd, &readfds);

        // from here
        // socklen_t len = sizeof(clientAddr);
        //
        // int rc = recvfrom(server_fd, buff, BUFF_SIZE - 1, 0, (struct sockaddr *)&clientAddr, &len);
        //
        // if (rc < 0) {
        //     perror("recvfrom error");
        //     continue;
        // }
        //
        // printf("Client %s:%d sent:", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
        // unpack(buff, rc);
        // memset(buff, 0, BUFF_SIZE);
        // to here
        //
        struct timeval timeout;
        timeout.tv_sec = 5;
        timeout.tv_usec = 0;

        int activity = select(server_fd + 1, &readfds, NULL, NULL, &timeout);
        while (waitpid(-1, NULL, WNOHANG) > 0)
            ;
        if (activity < 0) {
            perror("select error");
            close(server_fd);
            break;
        } else if (activity == 0) {
            printf("No data for 5 seconds. Still alive ...\n");
            continue;
        }

        if (FD_ISSET(server_fd, &readfds)) {
            socklen_t len = sizeof(clientAddr);

            int rc = recvfrom(server_fd, buff, BUFF_SIZE - 1, 0, (struct sockaddr *)&clientAddr, &len);

            if (rc < 0) {
                perror("recvfrom error");
                continue;
            }
            printf("Processing %s:%d.....\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
            pid_t pid = fork();
            if (pid < 0) {
                perror("fork() faild");
                close(server_fd);
                return -1;
            } else if (pid > 0) {
                printf("I am parent with pid %d\n", pid);
            } else if (pid == 0) {
                unpack(buff, rc);
                printf("Now exiting child process\n");
                exit(0);
            }
            memset(buff, 0, BUFF_SIZE);
        }

        // gettimeofday(&end, NULL); // End timer
        //
        // long seconds = end.tv_sec - start.tv_sec;
        // long useconds = end.tv_usec - start.tv_usec;
        // long total_micro = seconds * 1000000 + useconds;
        //
        // printf("Elapsed time: %.3f seconds\n", total_micro / 1e6);
    }

    close(server_fd);
    return 0;
}
