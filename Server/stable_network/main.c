


#include "c_version.h"

/*
int     InitServer(int port, int listen_queue_length,
        struct sockaddr_in *server_address)
*/

int main(void)
{
    struct sockaddr_in  sockaddr;
    int sockfd;
    t_goldilox  *buffer;

    sockfd = InitServer(4242, 5, &sockaddr);
    while (42)
    {
        StableSend(sockfd, "hello World");

        buffer = StableRecv(sockfd);
    }
}
