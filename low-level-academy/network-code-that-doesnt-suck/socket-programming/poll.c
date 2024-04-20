#include <arpa/inet.h>
#include <asm-generic/socket.h>
#include <netinet/in.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/poll.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_CLIENTS 256
#define PORT 8080
#define BUFF_SIZE 4096

typedef enum { STATE_NEW, STATE_CONNECTED, STATE_DISCONNCECTED } state_e;

// Structure to hold client state
typedef struct {
    int fd;
    state_e state;
    char buffer[BUFF_SIZE];
} clientstate_t;

clientstate_t clientStates[MAX_CLIENTS];

void init_clients() {
    for (int i = 0; i < MAX_CLIENTS; i++) {
        clientStates[i].fd = -1; // -1 indicates a free slot
        clientStates[i].state = STATE_NEW;
        memset(&clientStates[i].buffer, '\0', BUFF_SIZE); // Clear the buffer from previous user, set all to 0
    }
}

int find_free_slot() {
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clientStates[i].fd == -1) {
            return i; // Returns index of max client FDs. See above that -1 indicates a free slot in init_clients
        }
    }
    return -1; // No free slot found
}

int find_slot_by_fd(int fd) {
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clientStates[i].fd == fd) {
            return i;
        }
    }
    return -1; // Not found
}

int main() {
    int listen_fd, conn_fd, freeSlot;
    struct sockaddr_in server_addr, client_addr;

    socklen_t client_len = sizeof(client_addr);

    fd_set read_fds, write_fds; // What fds are readable, which are writeable

    struct pollfd fds[MAX_CLIENTS + 1];
    int nfds = 1;
    int opt = 1;

    // Initialize client states
    init_clients();

    // Create listening socket
    if ((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // To make socket non waiting / blocking
    if (setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    // Set up server address structure
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind
    if (bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    // Listen
    if (listen(listen_fd, 10) == -1) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    memset(fds, 0, sizeof(fds));
    fds[0].fd = listen_fd;
    fds[0].events = POLLIN; // If the listen_fd has an incoming connection awaiting to be connected
    nfds = 1;               // How many fds we are tracking / that are connected

    while (1) {
        int ii = 1;

        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (clientStates[i].fd != -1) {      // fd != 1 meaning they are actively in use
                fds[ii].fd = clientStates[i].fd; // Add that fd to the pollfd structure
                fds[ii].events = POLLIN;         // Input event
                ii++;
            }
        }
        // Wait for an event on one of the sockets
        int n_events = poll(fds, nfds, -1); // n_events return number of events that are waiting
        if (n_events == -1) {
            perror("poll");
            exit(EXIT_FAILURE);
        }

        // Check for new connections with bitwise operator. It checkf if revents has a bit on the last place, like 0x011
        // & 0x001 returns true while 0x110 & 0x001 returns false
        // IT checks if there is data to read
        if (fds[0].revents & POLLIN) {
            if ((conn_fd = accept(listen_fd, (struct sockaddr *)&client_addr, &client_len)) == -1) {
                perror("accept");
                continue;
            }

            printf("New connection from %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

            freeSlot = find_free_slot();

            if (freeSlot == -1) {
                printf("Server full: closing new connection\n");
                close(conn_fd);
            } else {
                clientStates[freeSlot].fd = conn_fd;
                clientStates[freeSlot].state = STATE_CONNECTED;
                nfds++; // one more fd poll is having to monitor for event tracking
                printf("Slot %d has fd %d\n", freeSlot, clientStates[freeSlot].fd);
            }

            n_events--;
        }

        // Check each client for read/write activity
        // // we start at 1 because we ignore the listen_fd
        for (int i = 1; i <= nfds && n_events > 0; i++) {
            if (fds[i].revents & POLLIN) {
                n_events--;

                int fd = fds[i].fd;
                int slot = find_slot_by_fd(fd);
                ssize_t bytes_read = read(fd, &clientStates[slot].buffer, sizeof(clientStates[i].buffer));
                if (bytes_read <= 0) {
                    // Connection closed or error
                    close(fd);
                    if (slot == -1) {
                        printf("Tried to close fd that doesnt exist?\n");
                    } else {
                        clientStates[slot].fd = -1; // Free up the slot
                        clientStates[slot].state = STATE_DISCONNCECTED;
                        printf("Client disconnected or error\n");
                        nfds--;
                    }
                } else {
                    printf("Received data from client. %s\n", clientStates[slot].buffer);
                }
            }
        }
    }

    return 0;
}
