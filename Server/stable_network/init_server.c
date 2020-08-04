

#include "c_version.h"


bool    assert_api_connection(int sockfd)
{
    char    response_message[400];

    bzero(response_message, 400);
    recv(sockfd, response_message, 400, 0);
    printf("response message %s\n", response_message);
    if (strcmp(response_message, "API") != 0)
    {
        close(sockfd);
        printf("Error, incorrect node");
        return (false);
    }
    send(sockfd, "API_0K\0", 7, 0);
    printf("Connection established\n");
    return (true);
}

int     HandshakeAccept(int sockfd, struct sockaddr_in server_addr)
{
    socklen_t   len;
    int         asock;

    while (true)
    {
        asock = accept(sockfd, (struct sockaddr *)&server_addr,
            &len);
        if (assert_api_connection(asock) == true)
            return (asock);
    }
    return (-1);
}

int     InitServer(int port, int listen_queue_length,
        struct sockaddr_in *server_address) 
{
    int     sockfd;
    struct sockaddr_in socket_address;

    *server_address = socket_address;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("socket");
        return (-1);
    }
    memset(&socket_address, '\0', sizeof(socket_address));
    socket_address.sin_family = AF_INET;
    socket_address.sin_addr.s_addr = INADDR_ANY;
    socket_address.sin_port = htons(port);

    if (bind(sockfd, (struct sockaddr *)&socket_address, sizeof(socket_address)))
    {
        perror("bind");
        return (-1);
    }
    if (listen(sockfd, listen_queue_length))
    {
        perror("listen");
        return (-2);
    }
    return (sockfd);
}
