
#include <stdio.h>
#include "lib.h"
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

void	map_file(unsigned char **content, size_t *size, char *filename)
{
	int				fd;
	struct stat		info;

	fd = open(filename, O_RDONLY);
	fstat(fd, &info);
	*size = info.st_size;
	*content = mmap(0, *size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
	if (*content == MAP_FAILED)
	{
		printf("Error mapping file\n");
		exit(1);
	}
}
