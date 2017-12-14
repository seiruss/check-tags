#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "file.h"
#include "stack.h"
#include "check_tags.h"

static FILE *open_file(const char *filename)
{
	PRINTVF("Opening file, %s\n", filename);

	FILE *fp = fopen(filename, "r");

	if (fp == NULL)
		return NULL;

	PRINTVF("Opened file, %s\n", filename);

	return fp;
}

static int fpeek(FILE *fp)
{
	int ch;

	ch = fgetc(fp);
	ungetc(ch, fp);

	return ch;
}

int scan_file()
{
	int ch;		/* int, not char, to handle EOF */
	int line_number = 1;
	int column = 0;
	int peek;
	bool single_comment = false;
	bool multi_comment = false;
	bool slash = false;
	bool quote = false;

	FILE *fp = open_file(options.file_name);
	if (fp == NULL)
	{
		PRINTE("Can not open file\n");
		return EXIT_FAILURE;
	}

	if (options.verbose_file_open || options.verbose)
	{
		//PRINTVF("\t\t%s\t%s\n", "Line", "Col");
		PRINTVF("%20s %6s\n", "Line", "Col");
	}

	while ((ch = fgetc(fp)) != EOF)
	{
		++column;

		/* Ignore spaces, tabs, letters and numbers for performance */
		if (ch != NEWLINE && isblank(ch) || isalnum(ch))
			continue;

		if (multi_comment)
		{
			if ((quote && !slash) && (ch == SINGLE_QUOTE || ch == DOUBLE_QUOTE))
			{
				multi_comment = false;
				quote = false;
			}

			if ((slash && !quote) && (ch == ASTERISK && \
				(peek = fpeek(fp)) != EOF && peek == FORWARD_SLASH))
			{
				multi_comment = false;
				slash = false;
			}

			/* Ignore all except newline that do not end the multi comment */
			if (ch != NEWLINE)
				continue;
		}

		switch (ch)
		{
			case NEWLINE:
				++line_number;
				column = 0;
				single_comment = false;
				break;

			case LEFT_PARENTHESIS:
			case LEFT_BRACKET:
			case LEFT_BRACE:
				if (!single_comment && !multi_comment)
					if (add_to_top(ch, line_number, column))
						return EXIT_FAILURE;
				break;

			case RIGHT_PARENTHESIS:
			case RIGHT_BRACKET:
			case RIGHT_BRACE:
				if (!single_comment && !multi_comment)
					if (remove_from_top(ch, line_number, column))
						return EXIT_FAILURE;
				break;

			case POUND_SIGN:
				if (options.pound)
					single_comment = true;
				break;

			case FORWARD_SLASH:
				if ((peek = fpeek(fp)) != EOF)
				{
					if (peek == FORWARD_SLASH && options.single)
					{
						single_comment = true;
					}
					else if (peek == ASTERISK && options.multi && !quote)
					{
						multi_comment = true;
						slash = true;
					}
				}
				break;

			case SINGLE_QUOTE:
			case DOUBLE_QUOTE:
				if (options.multi && !slash)
				{
					multi_comment = true;
					quote = true;
				}
				break;

			default:
				break;
		}
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
