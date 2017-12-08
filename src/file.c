#include <stdio.h>
#include <stdlib.h>
#include "file.h"
#include "stack.h"

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

BOOL scan_file(FILE *fp)
{
	int ch;		/* int, not char, to handle EOF */
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
		/*
		*	Can not show the problem tag here as it will
		*	always show the top most tag even if it is
		*	not the problem tag.
		*/

		/* fprintf(stderr, "Tag: %c on line %d column %d\n", \
			get_top_tag(), get_top_line(), get_top_col()); */

		return TRUE;
	}

	return FALSE;
}
