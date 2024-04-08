#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_CLIENTS 2
struct client_state {
    int fd;
    char *buff[4069];
};

struct client_state clientState[MAX_CLIENTS];
void init_clients() {
    for (int i = 0; i < MAX_CLIENTS; i++) {
        clientState[i].fd = -1;
        memset(clientState[i].buff, '\0', sizeof(clientState[i].buff));
    }
}

void update_fds(int *nfds, int *clientFd, fd_set *read_fds) {

    // Find an empty slot for the new client
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clientState[i].fd == -1) {
            clientState[i].fd = *clientFd;
            break;
        }
    }

    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clientState[i].fd != -1) {
            FD_SET(clientState[i].fd, read_fds);
            if (clientState[i].fd >= *nfds) {
                *nfds = clientState[i].fd + 1;
            }
        }
    }
}

void read_from_fds(int nfds, int serverSocket, fd_set *read_fds) {

    for (int fd = 0; fd < nfds; fd++) {
        if (FD_ISSET(fd, read_fds) && fd != serverSocket) {
            for (int i = 0; i < MAX_CLIENTS; i++) {
                if (clientState[i].fd == fd) {

                    char buffer[4096];
                    ssize_t bytesRead;

                    // With 2 lines below only, it will only read first buffer sent
                    // read(clientFd, buffer, sizeof(buffer));
                    // printf("Received data from client %s\n", buffer);
                    // Continuously read data until there's nothing left
                    while ((bytesRead = read(clientState[i].fd, buffer, sizeof(buffer))) > 0) {
                        printf("Received data from client %s\n", buffer);
                        // Process the received data here as needed
                    }

                    if (bytesRead == -1) {
                        perror("read");
                        close(clientState[i].fd);
                        continue;
                    } else if (bytesRead == 0) {
                        // Client disconnected
                        printf("Client %d disconnected\n", fd);
                        close(clientState[i].fd);
                        FD_CLR(clientState[i].fd, read_fds);
                        clientState[i].fd = -1; // Reset the client state
                    }
                }
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int nfds, clientFd;
    fd_set read_fds, write_fds;

    int port = atoi(argv[1]);

    if (port < 0) {
        perror("atoi");
        exit(EXIT_FAILURE);
    }
    init_clients();

    struct sockaddr_in serverInfo, clientInfo;

    socklen_t clientSize = sizeof(clientInfo);

    memset(&serverInfo, 0, sizeof(serverInfo));
    serverInfo.sin_addr.s_addr = 0; // Any address
    serverInfo.sin_port = htons(port);
    serverInfo.sin_family = AF_INET;

    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("socket");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    if (bind(serverSocket, (struct sockaddr *)&serverInfo, sizeof(serverInfo)) == -1) {
        perror("bind");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    if (listen(serverSocket, 10) == -1) {
        perror("listen");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", port);

    while (1) {
        FD_ZERO(&read_fds);
        FD_ZERO(&write_fds);

        FD_SET(serverSocket, &read_fds);

        nfds = serverSocket + 1;

        if (select(nfds, &read_fds, &write_fds, NULL, NULL) == -1) {
            perror("select");
            close(serverSocket);
            exit(EXIT_FAILURE);
        }

        // This basically update_fds
        if (FD_ISSET(serverSocket, &read_fds)) {

            if ((clientFd = accept(serverSocket, (struct sockaddr *)&clientInfo, &clientSize)) == -1) {
                perror("accept");
                continue;
            }

            printf("New connection from %s, from port %d\n", inet_ntoa(clientInfo.sin_addr),
                   ntohs(clientInfo.sin_port));

            update_fds(&nfds, &clientFd, &read_fds);
        }

        read_from_fds(nfds, serverSocket, &read_fds);
    }

    close(serverSocket);
    return 0;
}
