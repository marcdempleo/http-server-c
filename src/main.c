#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "http/request.h"
#include "server.h"

#define BACKLOG_NUM 40
#define PORT 8080
#define IP_ADDR "127.0.0.1"
#define BUFFER_SIZE 4096

int main(void) {
    int socket_fd, connect_fd;
    server_t server;
    char buf[BUFFER_SIZE];

    server.address = IP_ADDR;
    server.domain = AF_INET;
    server.port = PORT;
    server.sock_type = SOCK_STREAM;
    server.backlog = BACKLOG_NUM;

    if (init_server(&server, &connect_fd) == -1) {
        printf("shit");
        _exit(-1);
    }

    // http response
    char *hello = "HTTP/1.1 200 OK\n"
                  "server: a shitty one\n";

    // event loop
    while (1) {
        printf("waiting...\n");
        if (connect_fd == -1)
            perror("cry");

        if (read(connect_fd, buf, BUFFER_SIZE) == -1) {
            perror("what??");
            _exit(-1);
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
