


#include "c_version.h"

bool    send_api_connection(int sockfd)
{
    char    response_message[400];

    bzero(response_message, 400);
    send(sockfd, "API\0", 4, 0);
    recv(sockfd, response_message, 400, 0);
    printf("response message %s\n", response_message);
    if (strcmp(response_message, "API_0K") == 0)
        return (true);
    printf("Error connecting to valid daemon. Closing connection.");
    close(sockfd);
    return (false);
}


int     GoldiloxAPIClientConnection(char *host, int port)
{
    int     sockfd;
    struct sockaddr_in socket_address;
    int enable;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("socket");
        return (-1);
    }
    enable = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
        perror("setsockopt(SO_REUSEADDR) failed");
    memset(&socket_address, '\0', sizeof(socket_address));
    socket_address.sin_family = AF_INET;
    socket_address.sin_addr.s_addr = inet_addr(host);
    socket_address.sin_port = htons(port);

    if (connect(sockfd, (struct sockaddr *)&socket_address,
        sizeof(socket_address)) < 0)
    {
        perror("connect");
        return (-2);
    }

    if (send_api_connection(sockfd) == false)
       exit(1); 

    return (sockfd);
}














