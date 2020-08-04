



#include "../c_version.h"

char    *input(char *message)
{
    char buffer[1024];
    write(1, message, strlen(message));
    bzero(buffer, 1024);
    read(0, buffer, 1024);
    return (strdup(buffer));
}

int     main(void)
{
    int     sockfd;
    char    *filename;

    sockfd = GoldiloxAPIClientConnection("127.0.0.1", 4242);

    while (42)
    {
        filename = input("What file would you like to send?");
        
        if (filename[0] == '\n' || strlen(filename) == 0)
        {
            free(filename);
            continue ;
        }
        filename[strlen(filename) -1] = '\0';
        file_sender(sockfd, filename);
    }
    
    return (0);
}
