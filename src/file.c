#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "stack.h"

char *get_filename(const char *argv[])
{
	char *ch = malloc(strlen(argv[1]) + 1);

	if (ch == NULL)
	{
		fprintf(stderr, "Error: Unable to allocate memory for file\n");
		exit(EXIT_FAILURE);
	}

	strcpy(ch, argv[1]);

	return ch;
}

FILE *open_file(const char *filename)
{
	FILE *fp = fopen(filename, "r");

	if (fp == NULL)
	{
		fprintf(stderr, "Error: Can not open file\n");
		exit(EXIT_FAILURE);
	}

	return fp;
}

void scan_file(FILE *fp)
{
	int ch;		// int, not char, to handle EOF
	int line_number = 1;
	int column = 0;

	while ((ch = getc(fp)) != EOF)
	{
		++column;

		switch (ch)
		{
			case LEFT_PARENTHESIS: case LEFT_BRACKET: case LEFT_BRACE:
				add_to_top(ch, line_number, column);
				break;

			case RIGHT_PARENTHESIS: case RIGHT_BRACKET: case RIGHT_BRACE:
				remove_from_top(ch, line_number, column);
				break;

			case '\n':
				++line_number;
				column = 0;
				break;

			default:
				break;
		}
	}

	if (!is_empty())
	{
		fprintf(stderr, "Error: There are open tag(s) that are not closed\n");
		fprintf(stderr, "Tag: %c on line %d column %d\n", \
			get_top_tag(), get_top_line(), get_top_col());
		exit(EXIT_FAILURE);
	}

	printf("Tags are nested properly\n");
}
