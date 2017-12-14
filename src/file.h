#ifndef FILE_H
#define FILE_H

/* Tags the program checks for in the file */
#define LEFT_PARENTHESIS	'('
#define RIGHT_PARENTHESIS	')'
#define LEFT_BRACKET		'['
#define RIGHT_BRACKET		']'
#define LEFT_BRACE			'{'
#define RIGHT_BRACE			'}'

/* Comments to check for in the file */
#define POUND_SIGN			'#'
#define ASTERISK			'*'
#define FORWARD_SLASH		'/'
#define SINGLE_QUOTE		'\''
#define DOUBLE_QUOTE		'\"'
#define NEWLINE				'\n'


/*
	Opens a file in read-only.

	@param	filename	file name from argv[1].
	@return				file pointer to filename.
*/
static FILE *open_file(const char *filename);

/*
	Peeks at the next character in a stream.

	@param	fp	file stream.
	@return		next character.
*/
static int fpeek(FILE *fp);

/*
	Scans the file for tags and adds or removes them in a linked list.
	Verifies the stack is empty and prints the relevant message.

	@param	fp	file to scan.
	@return		esit_success or exit_failure
*/
int scan_file();

#endif /* FILE_H */
