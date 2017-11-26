#include <stdio.h>
#include <stdlib.h>
#include "file.h"
#include "stack.h"

/*
	Check open and close tags in a file
	to determine if they are nested properly.
	Uses a linked list to store each tag's
	char, line, and column number.
*/

int main(int argc, const char *argv[])
{
	if (argc != 2)
	{
		printf("Usage: check_tags [FILE]\n");
		return EXIT_FAILURE;
	}

	char *filename = get_filename(argv);
	FILE *fp = open_file(filename);
	scan_file(fp);

	fclose(fp);
	free(filename);

	return EXIT_SUCCESS;
}
