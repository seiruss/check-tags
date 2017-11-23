#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "stack.h"

/*
	Check open and close tags in a file to determine if they are nested properly
	Uses a linked list to store each tag's char, line, and column number
*/

void help_message()
{
	printf("\nUsage: check_tags [FILE]\n\n");
	printf("\t-h\tdisplay this help\n");
	printf("\t-v\tversion information\n");
}

void version()
{
	printf("BETA\n");
}

int main(int argc, const char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "Error: Illegal number of arguments\n");
		help_message(argv);
		return EXIT_FAILURE;
	}

	for (int i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "-h") == 0)
		{
			help_message();
			return EXIT_SUCCESS;
		}
		else if (strcmp(argv[i], "-v") == 0)
		{
			version();
			return EXIT_SUCCESS;
		}
	}

	char *filename = get_filename(argv);
	FILE *fp = open_file(filename);
	scan_file(fp);

	fclose(fp);
	free(filename);
	return EXIT_SUCCESS;
}
