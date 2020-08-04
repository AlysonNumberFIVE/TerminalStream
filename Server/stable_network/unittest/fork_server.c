

#include "../c_version.h"

struct sockaddr_in global_address;

int     init_server(int port)
{
    int     sockfd;
    struct sockaddr_in socket_address;

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
    
    if (bind(sockfd, (struct sockaddr *)&socket_address,
        sizeof(socket_address)) < 0)
    {
        perror("bind");
        return (-2);
    }
    
    if (listen(sockfd, 5) < 0)
    {
        perror("listen");
        return (-3);
    }
    global_address = socket_address;
    return (sockfd);
}


void    run_client(int accept_socket)
{
    char  buffer[4096];

    bzero(buffer, 4096);
    send(accept_socket, "Hello User\0", 11, 0);
    while (true)
    {
        recv(accept_socket, buffer, 4096, 0);
        printf("Accept, User said\n");
        send(accept_socket, buffer, strlen(buffer), 0);
        bzero(buffer, 4096);
    }
}


int     forking_server(int sockfd)
{
    int         accept_socket;
    socklen_t   length;
    pid_t       pid;
    
    length = sizeof(global_address);
    while (true)
    {
        accept_socket = accept(sockfd, (struct sockaddr *)&global_address,
            &length);
        if (accept_socket)
        {
            pid = fork();
            if (pid == 0)
            {
                run_client(accept_socket);
            }
        }
    }
}


int     main(int argc, char **argv)
{
    int     sockfd;

    if (argc != 2)
    {
        printf("Usage: %s [port]\n", argv[0]);
        return (-1);
    }
    
    sockfd = init_server(atoi(argv[1]));


    forking_server(sockfd);
    return (0);
}
