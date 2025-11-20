#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>

#include "server.h"

int init_server(server_t *server, int *connect_fd) {
    int socket_fd, accept_fd;
    struct sockaddr_in sock_addr;
    socklen_t sock_addr_size;

    // address init
    sock_addr.sin_family = server->domain;
    sock_addr.sin_port = server->port;
    sock_addr.sin_addr.s_addr = inet_addr(server->address);

    // socket init
    printf("socket init\n");
    socket_fd = socket(server->domain, SOCK_STREAM, 0);
    if (socket_fd == -1) {
        perror("right..");
        return -1;
    }
    if (bind(socket_fd, (struct sockaddr *)&sock_addr, sizeof(sock_addr)) < 0) {
        perror("fuck");
        return -1;
    }
    if (listen(socket_fd, server->backlog) < 0) {
        perror("die");
        return -1;
    }
    printf("init finished\n");

    // for reading/writing through socket
    // this doesn't WORK
    sock_addr_size = sizeof(sock_addr);
    *connect_fd =
        accept(socket_fd, (struct sockaddr *)&sock_addr, &sock_addr_size);
    printf("accept_fd init\n");
    return 0;
};
