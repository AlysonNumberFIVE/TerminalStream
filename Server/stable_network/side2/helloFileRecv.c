

#include "../c_version.h"

int     main(void)
{
    int     sockfd;

    sockfd = GoldiloxAPIClientConnection(
        "127.0.0.1", 4321
    );

    while (42)
    {
        StableRecv(sockfd);

    }
    return (0);
}
