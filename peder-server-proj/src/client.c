#include <netinet/in.h> // Include this header
#include <stdio.h>
#include <string.h>
#include <unistd.h>
int main(int argc, char *argv[]) {

    // this is suppsoe to be a client accepting cli arguments and the data to a server urnning on port 8080

    int sockfd;

    struct sockaddr_in servaddr;

    if (argc != 3) {
        printf("Usage: %s <ip> <data>\n", argv[0]);
        return -1;
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd == -1) {
        perror("socket");
        return -1;
    }

    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;

    servaddr.sin_port = htons(8080);

    if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) {
        perror("inet_pton");
        return -1;
    }

    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1) {
        perror("connect");
        return -1;
    }

    if (write(sockfd, argv[2], strlen(argv[2])) == -1) {
        perror("write");
        return -1;
    }

    char buffer[1024] = {0}; // Buffer to store the response

    // Reading the response from the server
    ssize_t n = read(sockfd, buffer, sizeof(buffer) - 1);
    if (n == -1) {
        perror("read");
        close(sockfd);
        return -1;
    }

    buffer[n] = '\0'; // Null-terminate the string
    printf("Server response: %s\n", buffer);

    close(sockfd);

    return 0;
}
