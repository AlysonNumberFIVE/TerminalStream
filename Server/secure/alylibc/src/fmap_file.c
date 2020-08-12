
#include <stdlib.h>
#include <stdio.h>

void		fmap_file(unsigned char **content, size_t *size, char *filename)
{
	FILE	*fp;

	fp = fopen(filename, "r");
	fseek(fp, 0, SEEK_END);
	*size = ftell(fp);
	fseek(fp, 0, SEEK_SET);	
	*content = (unsigned char *)malloc(sizeof(unsigned char ) * (*size));
	fread(*content, *size, 1, fp);
	fclose(fp);
}