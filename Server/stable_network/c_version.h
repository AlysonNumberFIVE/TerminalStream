
#ifndef C_VERSION_H
#define C_VERSION_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

typedef struct s_goldilox {
    unsigned char *content;
    size_t      size;
}   t_goldilox;

t_goldilox   *StableRecv(int sockfd);
void    StableSend(int sockfd, unsigned char *buffer, size_t size);
bool    assert_buffer_is_file(unsigned char *buffer, size_t size);
void    file_recv(unsigned char *buffer, size_t size);
void    file_sender(int sockfd, char *filename);
int     InitServer(int port, int listen_queue_length,
        struct sockaddr_in *server_address);
int     GoldiloxAPIClientConnection(char *host, int port);
bool    assert_api_connection(int sockfd);
int     HandshakeAccept(int sockfd, struct sockaddr_in server_addr);
void    Close(int sockfd);

#endif
