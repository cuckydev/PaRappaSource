#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("usage: syncstrip file\n");
		return 0;
	}
	FILE *fp = fopen(argv[1], "rb");
	if (fp == NULL)
	{
		printf("Failed to open %s\n", argv[1]);
		return 1;
	}
	fseek(fp, 0, SEEK_END);
	size_t size = ftell(fp);
	if ((size % 2352) != 0)
	{
		printf("Invalid size\n");
		fclose(fp);
		return 1;
	}
	unsigned char *buf = malloc(size);
	if (buf == NULL)
	{
		printf("Failed to malloc buffer\n");
		fclose(fp);
		return 1;
	}
	rewind(fp);
	fread(buf, size, 1, fp);
	fclose(fp);
	
	fp = fopen(argv[1], "wb");
	if (fp == NULL)
	{
		printf("Failed to open %s\n", argv[1]);
		free(buf);
		return 1;
	}
	for (size_t i = 0; i < size; i += 2352)
		fwrite(buf + i + 16, 2352 - 16, 1, fp);
	free(buf);
	fclose(fp);
	
	return 0;
}