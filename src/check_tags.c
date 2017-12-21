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
	{ "quiet", no_argument, 0, 'q' },
	{ 0, 0, 0, 0 }
};

static void usage(char *argv[])
{
	PRINT("Usage: %s [OPTIONS] <FILE>\n\n", argv[0]);
	PRINT("Miscellaneous:\n"
		"  -h, --help	    Display this help\n"
		"  -V, --version	    version information\n"
		"  -v, --verbose	    verbose output\n"
		"  -q, --quiet	    suppress normal output\n\n"
		"Scanning options to ignore tags:\n"
		"  -p	after # on same line\n"
		"  -s	after // on same line\n"
		"  -c	between /* */ on multiple lines\n"
		"  -i	between single quotes on multiple lines\n"
		"  -d	between double quotes on multiple lines\n"
		"  -a	ignore tags in all comments\n\n");
}

static void usage_short(char *argv[], char *msg)
{
	PRINTE("%s\n"
		"Usage: %s [OPTIONS] <FILE>\n"
		"Try '%s --help' for more information\n\n", msg, argv[0], argv[0]);
}

static void version(char *argv[])
{
	PRINT("%s 1.2\n", argv[0]);
	PRINT("Written by Russell Seifert\n");
	PRINT("Contribute at <https://github.com/seiruss/check-tags>\n\n");
}

static int parse_args(int argc, char *argv[])
{
	int c;
	int option_index = 0;
	opterr = 0; /* getopt() does not print its own error message */

	while ((c = getopt_long(argc, argv, "vVhqpscida",
				long_options, &option_index)) != -1)
	{
		switch (c)
		{
			/* verbose */
			case 'v':
				options.verbose = true;
				break;

			/* quiet */
			case 'q':
				options.quiet = true;
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
			case 'c':
				options.asterisk = true;
				break;

			/* single quote */
			case 'i':
				options.s_quote = true;
				break;

			/* double quote */
			case 'd':
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
				PRINTE("Invalid option '%s'\n"
					"Usage: %s [OPTIONS] <FILE>\n"
					"Try '%s --help' for more information\n\n", \
					argv[optind - 1], argv[0], argv[0]);
				return EXIT_FAILURE;

			case 'h':
				usage(argv);
				exit_after_args = true;
				return EXIT_SUCCESS;

			default:
				usage(argv);
				return EXIT_FAILURE;
		}
	}

	if (options.verbose && options.quiet)
	{
		usage_short(argv, "Can not have verbose and quiet enabled");
		return EXIT_FAILURE;
	}

	/* File name is one less than argc */
	if (argc - optind == 1)
		options.file_name = argv[optind];
	else
	{
		if (argc - optind == 0)
		{
			usage_short(argv, "File name is missing");
		}
		else
		{
			/* There are arguments after the file name */
			usage_short(argv, "Too many arguments");
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
	int rc = EXIT_SUCCESS;

	if (argc < 2)
	{
		usage(argv);
		rc = EXIT_FAILURE;
	}
	else
	{
		rc = parse_args(argc, argv);

		if (rc == EXIT_SUCCESS && !exit_after_args)
			rc = scan_file();
	}

	return rc;
}
