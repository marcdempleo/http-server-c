#ifndef SERVER_H_
#define SERVER_H_
#include <stdint.h>

typedef struct server_desc {
    int domain;
    int sock_type;
    uint16_t port;
    char *address;
    int backlog;
} server_t;

int init_server(server_t *server, int *connect_fd);

#endif // SERVER_H_
