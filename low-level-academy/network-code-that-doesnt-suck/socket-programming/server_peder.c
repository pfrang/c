#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080

int main() {
    struct sockaddr_in serverInfo, clientInfo;

    serverInfo.sin_port = htons(PORT);
    serverInfo.sin_addr.s_addr = 0;
    serverInfo.sin_family = AF_INET;

    // socket
    int socketServer = socket(AF_INET, SOCK_STREAM, 0);

    socklen_t clientSize = 0;

    if (socketServer == -1) {
        perror("socket");
        return -1;
    }

    printf("Received socket fd %d\n", socketServer);
    // bind
    if (bind(socketServer, (struct sockaddr *)&serverInfo, sizeof(serverInfo)) == -1) {
        perror("bind");
        close(socketServer);
        return -1;
    }

    printf("Socket %d is now bound\n", socketServer);
    // listen

    if (listen(socketServer, 0) == -1) {
        perror("listen");
        close(socketServer);
        return -1;
    }

    printf("Socketserver is now listening on port %d\n", ntohs(serverInfo.sin_port));

    while (1) {
        int cfd = accept(socketServer, (struct sockaddr *)&clientInfo, &clientSize);
        printf("Received a connection on cfd <%d>\n", cfd);

        if (cfd == -1) {
            perror("accept");
            close(socketServer);
            return -1;
        }

        char *buff = "Heihei";

        write(cfd, buff, strlen(buff));

        close(cfd);
    }
    return 0;
}
