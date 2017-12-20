#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <getopt.h>
#include "check_tags.h"

/*
	Check open and close tags in a file to determine
	if they are nested properly. Uses a linked list
	to store each tag's char, line, and column number.
*/

int scan_file();

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
		"Scanning options to ignore tags:\n"
		"  -p	after # on same line\n"
		"  -s	after // on same line\n"
		"  -k	between /* */ on multiple lines\n"
		"  -u	between single quotes on multiple lines\n"
		"  -q	between double quotes on multiple lines\n"
		"  -a	ignore tags in all comments\n\n");
}

static void version(char *argv[])
{
	PRINT("%s 1.1\n", argv[0]);
	PRINT("Written by Russell Seifert\n");
	PRINT("Contribute at <https://github.com/seiruss/check-tags>\n\n");
}

static int parse_args(int argc, char *argv[])
{
	int c;
	int option_index = 0;
	opterr = 0; /* getopt() does not print its own error message */

	while ((c = getopt_long(argc, argv, "vVhpskuqa",
				long_options, &option_index)) != -1)
	{
		switch (c)
		{
			/* verbose */
			case 'v':
				options.verbose = true;
				break;

			/* pound sign */
			case 'p':
				options.pound = true;
				break;

			/* slash */
			case 's':
				options.slash = true;
				break;

			/* asterisk */
			case 'k':
				options.asterisk = true;
				break;

			/* single quote */
			case 'u':
				options.s_quote = true;
				break;

			/* double quote */
			case 'q':
				options.d_quote = true;
				break;

			/* all options */
			case 'a':
				options.pound = true;
				options.slash = true;
				options.asterisk = true;
				options.s_quote = true;
				options.d_quote = true;
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

	PRINTV("Options: pound=%d, slash=%d, asterisk=%d, s_quote=%d, "
		"d_quote=%d\n", options.pound, options.slash, options.asterisk, \
		options.s_quote, options.d_quote);

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
