#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "file.h"
#include "stack.h"
#include "check_tags.h"

static FILE *open_file(const char *filename)
{
	PRINTV("Opening file, %s\n", filename);

	FILE *fp = fopen(filename, "r");
	return fp;
}

static bool in_multi_comment(int ch, int prev, FILE *fp)
{
	if (!comments.multi)
		return false;

	/* asterisk */
	if ((comments.slash && !comments.s_quote && !comments.d_quote) && \
		(ch == FORWARD_SLASH && prev == ASTERISK))
	{
		comments.multi = false;
		comments.slash = false;
	}

	/* single quote */
	if ((comments.s_quote && !comments.d_quote && !comments.slash) && \
		(ch == SINGLE_QUOTE))
	{
		comments.multi = false;
		comments.s_quote = false;
	}

	/* double quote */
	if ((comments.d_quote && !comments.s_quote && !comments.slash) && \
		(ch == DOUBLE_QUOTE))
	{
		comments.multi = false;
		comments.d_quote = false;
	}

	return true;
}

int scan_file()
{
	int ch;		/* int, not char, to handle EOF */
	int line = 1;
	int column = 0;
	int prev = 0;

	FILE *fp = open_file(options.file_name);
	if (fp == NULL)
	{
		PRINTE("Can not open file\n");
		return EXIT_FAILURE;
	}
	else
		PRINTV("Opened file, %s\n", options.file_name);

	/* Verbose header */
	if (options.verbose)
		PRINTV("\n%20s %6s\n", "Line", "Col");

	/* Main loop to scan file */
	while ((ch = fgetc(fp)) != EOF)
	{
		++column;

		/* Must scan newline for single comment, line number, column */
		if (ch != NEWLINE)
		{
			/* Ignore spaces, tabs, letters and numbers for performance */
			if (isblank(ch) || isalnum(ch))
				continue;

			/* Ignore all characters that do not end comments */
			if (comments.single || in_multi_comment(ch, prev, fp))
			{
				prev = ch;	/* terminates multi comment */
				continue;
			}
		}

		switch (ch)
		{
			case NEWLINE:
				++line;
				column = 0;
				comments.single = false;
				break;

			case LEFT_PARENTHESIS:
			case LEFT_BRACKET:
			case LEFT_BRACE:
				if (!comments.single && !comments.multi)
					if (add_to_top(ch, line, column))
						return EXIT_FAILURE;
				break;

			case RIGHT_PARENTHESIS:
			case RIGHT_BRACKET:
			case RIGHT_BRACE:
				if (!comments.single && !comments.multi)
					if (remove_from_top(ch, line, column))
						return EXIT_FAILURE;
				break;

			case POUND_SIGN:
				if (options.pound)
					comments.single = true;
				break;

			case FORWARD_SLASH:
				if (prev == FORWARD_SLASH && options.slash)
					comments.single = true;
				break;

			case ASTERISK:
				if (prev == FORWARD_SLASH && options.asterisk && \
					!comments.s_quote && !comments.d_quote)
				{
					comments.multi = true;
					comments.slash = true;
				}
				break;

			case SINGLE_QUOTE:
				if (options.s_quote && !comments.slash && !comments.d_quote)
				{
					comments.multi = true;
					comments.s_quote = true;
				}
				break;

			case DOUBLE_QUOTE:
				if (options.d_quote && !comments.slash && !comments.s_quote)
				{
					comments.multi = true;
					comments.d_quote = true;
				}
				break;

			default:
				break;
		}

		prev = ch;
	}

	if (!is_empty())
	{
		/*
			Can not show the problem tag here as it will always show
			the top most tag even if it is not the problem tag.
		*/

		/* fprintf(stderr, "Tag: %c on line %d column %d\n", \
			get_top_tag(), get_top_line(), get_top_col()); */

		PRINTE("There are open tag(s) that are not closed\n");
		return EXIT_FAILURE;
	}

	PRINT("Tags are nested properly\n");
	return EXIT_SUCCESS;
}
