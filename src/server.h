#ifndef SERVER_H_
#define SERVER_H_
#include <netinet/in.h>
#include <stdint.h>
#include <sys/socket.h>

typedef struct server_desc {
    int domain;
    int sock_type;
    uint16_t port;
    char *address;
    int backlog;
} server_t;

typedef struct connect_info {
    int socket_fd;
    struct sockaddr_in sockaddr;
    socklen_t sockaddr_len;
} acceptfd_t;

int init_server(server_t server, acceptfd_t *connect_info);

#endif // SERVER_H_
