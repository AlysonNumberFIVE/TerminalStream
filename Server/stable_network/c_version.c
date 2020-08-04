
#include "c_version.h"

char    *uitoa(long long size)
{
    size_t number_length;
    size_t saved_size;
    char *string_number;
    int c;

    saved_size = size;
    number_length = 0;
    while (size > 0)
    {
        number_length++;
        size /= 10;
    }
    string_number = (char *)malloc(sizeof(char) * number_length + 1);
    string_number[number_length--] = '\0';
    while (saved_size > 0) {
        c = saved_size % 10;
        string_number[number_length] = c + '0';
        saved_size /= 10;
        number_length--;
    }
    return (string_number);
}

void    buffered_send(int sockfd, unsigned char *buffer, size_t size)
{
    size_t      counter;
    ssize_t     sent;

//    write(1, buffer, size);
    if (size < 4096)
    {
        sent = send(sockfd, buffer, size, 0);
        return ;
    }
    counter = 0;
    while (counter < size)
    {
        sent = send(sockfd, buffer, 4096, 0);
        counter += sent;
        buffer += sent;
    }
}

unsigned char    *buffered_recv(int sockfd, size_t size)
{
    size_t          counter;
    unsigned char   *buffer;
    size_t          received;
    unsigned char   *head_ptr;


    buffer = (unsigned char *)malloc(sizeof(unsigned char) * size + 1);
    counter = 0;
    head_ptr = buffer;
    bzero(buffer, size);
    if (size < 4096)
    {
        received = recv(sockfd, buffer, 4096, 0);
        return (head_ptr);
    }
    while (counter < size)
    {
        received = recv(sockfd, buffer, 4096, 0);
        buffer += received;
        counter += received;
    }
    return (head_ptr);
}

int     receive_number_size(int sockfd)
{
    char    buffer[4096];

    bzero(buffer, 4096);
    recv(sockfd, buffer, 4096, 0);
    send(sockfd, "0K\0", 3, 0);
    return (atoi(buffer));
}

void     sending_number_size(int sockfd, size_t size)
{
    char buffer[4096];
    char *number;

    bzero(buffer, 4096);
    number = uitoa(size);
    send(sockfd, number, strlen(number) + 1, 0);
    recv(sockfd, buffer, 6, 0);
}


t_goldilox   *StableRecv(int sockfd)
{
    int size;
    t_goldilox  *goldiblock;
    unsigned char *content;

    goldiblock = (t_goldilox *)malloc(sizeof(t_goldilox));
    goldiblock->size = receive_number_size(sockfd);

    goldiblock->content = buffered_recv(sockfd, goldiblock->size);
  //  write(1, goldiblock->content, goldiblock->size);
    if (assert_buffer_is_file(goldiblock->content, goldiblock->size)
          == true)
    {
        file_recv(goldiblock->content, goldiblock->size);
        free(goldiblock->content);
        free(goldiblock);
        return (NULL);
    }
    return (goldiblock);
}

void    StableSend(int sockfd, unsigned char *buffer, size_t size)
{
    sending_number_size(sockfd, size);
    buffered_send(sockfd, buffer, size);
}

