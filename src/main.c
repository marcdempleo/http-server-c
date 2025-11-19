#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "http_request.h"

#define BACKLOG_NUM 40
#define PORT 8080
#define IP_ADDR "127.0.0.1"
#define PACKET_SIZE 4096

int main(void) {
    int socket_fd, connect_fd;
    struct sockaddr_in sock_addr;
    socklen_t sock_addr_size;
    char buf[BUFFER_SIZE];

    // http response
    char *hello = "HTTP/1.1 200 OK\n"
                  "server: a shitty one\n";

    // address init
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(PORT);
    sock_addr.sin_addr.s_addr = inet_addr(IP_ADDR);

    // socket init
    printf("socket init\n");
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd == -1) {
        perror("right..");
        exit(1);
    }
    if (bind(socket_fd, (struct sockaddr *)&sock_addr, sizeof(sock_addr)) < 0) {
        perror("fuck");
        exit(2);
    }
    if (listen(socket_fd, BACKLOG_NUM) < 0) {
        perror("die");
        exit(3);
    }
    printf("init finished\n");

    /* signal(SIGINT, close_fd); */
    // event loop
    while (1) {
        sock_addr_size = sizeof(sock_addr);
        printf("waiting...\n");

        connect_fd =
            accept(socket_fd, (struct sockaddr *)&sock_addr, &sock_addr_size);

        if (connect_fd == -1)
            perror("cry");

        if (read(connect_fd, buf, BUFFER_SIZE) == -1) {
            perror("what??");
            return -1;
        }

        // just for logging yknow
        printf("%s\n", buf);

        // just for logging yknow pt. 2
        printf("%s\n", hello);

        if (write(connect_fd, hello, strlen(hello)) == -1) {
            perror("whoops!");
            return -1;
        }

        if (http_request(buf) == -1) {
            perror("crap..");
            return -1;
        }

        if (close(connect_fd) == -1) {
            perror("that's bad...");
            return -1;
        }
    }

    return 0;
}
