#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>

#include "server.h"

int init_server(server_t server, acceptfd_t *connect_info) {
    int socket_fd;
    struct sockaddr_in sock_addr;
    socklen_t sock_addr_size;
    printf("\n--- server init ---\n");

    // address init
    sock_addr.sin_family = server.domain;
    sock_addr.sin_port = htons(server.port);
    sock_addr.sin_addr.s_addr = inet_addr(server.address);

    // socket init
    printf("socket init\n");
    socket_fd = socket(server.domain, SOCK_STREAM, 0);
    if (socket_fd == -1) {
        perror("right..");
        return -1;
    }
    if (bind(socket_fd, (struct sockaddr *)&sock_addr, sizeof(sock_addr)) < 0) {
        perror("fuck");
        return -1;
    }
    if (listen(socket_fd, server.backlog) < 0) {
        perror("die");
        return -1;
    }
    printf("socket init finished\n");

    // for reading/writing through socket
    // this doesn't WORK
    sock_addr_size = sizeof(sock_addr);
    connect_info->socket_fd = socket_fd;
    connect_info->sockaddr = sock_addr;
    connect_info->sockaddr_len = sock_addr_size;
    printf("connect_info init complete\n");
    printf("--- server init completed ---\n");
    return 0;
};
