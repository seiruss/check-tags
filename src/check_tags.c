#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <getopt.h>
#include "check_tags.h"
#include "file.h"
#include "stack.h"

/*
	Check open and close tags in a file to determine
	if they are nested properly. Uses a linked list
	to store each tag's char, line, and column number.
*/

static bool exit_after_args = false;

static struct option long_options[] =
{
	{ "help", no_argument, 0, 'h' },
	{ "version", no_argument, 0, 'V' },
	{ "verbose", no_argument, 0, 'v' },
	{ 0, 0, 0, 0 }
};

static void usage(char *argv[])
{
	PRINT("Usage: %s [OPTIONS] <FILE>\n\n", argv[0]);
	PRINT("Miscellaneous:\n"
		"  -h, --help	    Display this help\n"
		"  -V, --version	    version information\n"
		"  -v, --verbose	    verbose output\n\n"
		"Scanning options:\n"
		"  -p	ignore tags after # on same line\n"
		"  -s	ignore tags after // on same line\n"
		"  -m	ignore tags between /* */ on multiple lines\n"
		"  -u	ignore tags between \' \' on multiple lines\n"
		"  -q	ignore tags between \" \" on multiple lines\n"
		"  -a	ignore tags between all comments\n\n");
}

static void version(char *argv[])
{
	PRINT("%s 1.0\n", argv[0]);
	PRINT("Written by Russell Seifert\n");
	PRINT("Contribute at <https://github.com/seiruss/check-tags>\n\n");
}

static int parse_args(int argc, char *argv[])
{
	int c;
	int option_index = 0;
	opterr = 0; /* getopt() does not print its own error message */

	while ((c = getopt_long(argc, argv, "vVhampqsu",
				long_options, &option_index)) != -1)
	{
		switch (c)
		{
			/* verbose */
			case 'v':
				options.verbose = true;
				break;

			/* all options */
			case 'a':
				options.single = true;
				options.multi = true;
				options.pound = true;
				break;

			/* multi line comment */
			case 'm':
			case 'q':
			case 'u':
				options.multi = true;
				break;

			/* pound sign comment */
			case 'p':
				options.pound = true;
				break;

			/* single line comment */
			case 's':
				options.single = true;
				break;

			/* version */
			case 'V':
				version(argv);
				exit_after_args = true;
				return EXIT_SUCCESS;

			case '?':
				PRINTE("Invalid option '%s'\n", argv[optind - 1]);
				usage(argv);
				return EXIT_FAILURE;

			case 'h':
			default:
				usage(argv);
				exit_after_args = true;
				return EXIT_SUCCESS;
		}
	}

	/* File name is one less than argc */
	if (argc - optind == 1)
		options.file_name = argv[optind];
	else
	{
		if (argc - optind == 0)
		{
			PRINTE("File name is missing\n");
		}
		else
		{
			/* There are arguments after the file name */
			PRINTE("Too many arguments\n");
			usage(argv);
		}

		return EXIT_FAILURE;
	}

	PRINTV("Options: single=%d, multi=%d, pound=%d\n", options.single, \
		options.multi, options.pound);

	return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
	int res = EXIT_SUCCESS;

	if (argc < 2)
	{
		usage(argv);
		res = EXIT_FAILURE;
	}
	else
	{
		res = parse_args(argc, argv);

		if (res == EXIT_SUCCESS && !exit_after_args)
			res = scan_file();
	}

	return res;
}
