#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include "file.h"
#include "stack.h"

/******************************************************************************
	Check open and close tags in a file to determine
	if they are nested properly. Uses a linked list
	to store each tag's char, line, and column number.
******************************************************************************/

static void usage(char *argv[])
{
	printf("Usage: %s [FILE]\n\n", basename(argv[0]));
}

static void version(char *argv[])
{
	printf("%s 1.0\n", basename(argv[0]));
	printf("Written by Russell Seifert\n");
	printf("Contribute at <https://github.com/seiruss/check-tags>\n\n");
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		usage(argv);
		return EXIT_FAILURE;
	}

	for (int i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
		{
			usage(argv);
			return EXIT_SUCCESS;
		}
		else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0)
		{
			version(argv);
			return EXIT_SUCCESS;
		}
	}

	FILE *fp = open_file(argv[1]);
	scan_file(fp);

	fclose(fp);
	return EXIT_SUCCESS;
}
