

#include <sys/mman.h>
#include <sys/stat.h>
#include "c_version.h"

#define MAGIC_NUMBER_SIZE   4


char    *sub(char *string, int start, int length)
{
    char    *newstring;
    int     counter;

    counter = 0;
    newstring = (char *)malloc(sizeof(char) * length + 1);
    while (string[start] && counter < length)
    {
        newstring[counter] = string[start];
        counter++;
        start++;
    }
    newstring[counter] = '\0';
    return (newstring);
}


int    map_file(char *filename, unsigned char **content,
            size_t *size)
{
    int         fd;
    struct stat info;
    
    fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        perror("opening file\n");
        return (-1);
    }
    fstat(fd, &info);
    *size = info.st_size;
    *content = mmap(0, *size, PROT_READ, MAP_PRIVATE,
        fd, 0);
    if (*content == MAP_FAILED)
    {
        perror("mapping file");
        return (-2);
    }
    return (0);
}


unsigned char   *write_buffer(unsigned char *total_buffer,
    char *filename, unsigned char *file_content, size_t content_size)
{
    size_t      counter;
    size_t      travel;

    travel = 0;
    counter = 0;
    while (counter < strlen(filename))
    {
        total_buffer[travel] = filename[counter];
        travel++;
        counter++;
    }
    total_buffer[counter] = '\x44';
    total_buffer[counter + 1] = '\x33';
    total_buffer[counter + 2] = '\x22';
    total_buffer[counter + 3] = '\x11';

    counter += 4;
    travel = 0;
    while (travel < content_size)
    {
        total_buffer[counter] = file_content[travel];
        travel++;
        counter++;
    }
    return (total_buffer);
}


void    file_sender(int sockfd, char *filename)
{
    unsigned char   *file_content;
    size_t          size;
    int             value;
    unsigned char   *total_buffer;

    value = map_file(filename, &file_content, &size);
    if (value != 0)
        exit(1);
    
    total_buffer = (unsigned char *)malloc(sizeof(unsigned char)
        * size + strlen(filename) + MAGIC_NUMBER_SIZE);
    
    total_buffer = write_buffer(total_buffer, filename,
        file_content, size);
    

    StableSend(sockfd, total_buffer,
         size + strlen(filename) + MAGIC_NUMBER_SIZE);
}


void    write_file(unsigned char *buffer_content, char *filename,
    size_t size)
{
    int     fd;
    size_t content_size;

    fd = open(filename, O_RDWR | O_CREAT,  0777);
    content_size = size - strlen(filename) - MAGIC_NUMBER_SIZE;
    write(fd, buffer_content, content_size);
    close(fd);
}


bool    assert_flag(unsigned char *flag)
{
    printf("flag is %x%x%x%x\n",
       flag[0], flag[1], flag[2], flag[3]);
    return (
        flag[0] == '\x44' &&
        flag[1] == '\x33' && 
        flag[2] == '\x22'
   );
}

bool    assert_buffer_is_file(unsigned char *buffer, size_t size)
{
    int     counter;
    unsigned char *flag_checker;

    counter = 0;
    while (counter < size)
    {
        if (counter == 1024)
            break ;

       
        if (buffer[counter] == '\x44')
        {
            flag_checker = (unsigned char *)sub((char *)buffer, counter, 3);
            
            bool flag = assert_flag(flag_checker);
            if (flag == true)
                printf("TRUE\n");
            else
                printf("FALSE\n");
            return (flag);


        }
        counter++;  
    }
    return false;
}


void    file_recv(unsigned char *buffer, size_t size)
{
    int      counter;
    char    *filename;
    unsigned char *buffer_content;

    counter = 0;
    while (counter < size)
    {

        if (buffer[counter] == '\x44')
        {
            buffer[counter] = '\0';
            printf("Writing file..\n");
            filename = strdup((char *)buffer);
            counter += 4;
            buffer_content = &buffer[counter];
            write_file(buffer_content, filename, size);
            return  ;
        }
        counter++;
    }
    printf("Error: File not written\n");
    return ;
}








