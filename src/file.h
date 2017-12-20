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
#define FORWARD_SLASH		'/'
#define ASTERISK			'*'
#define SINGLE_QUOTE		'\''
#define DOUBLE_QUOTE		'\"'
#define NEWLINE				'\n'

/* Scanning options in comments */
struct
{
	bool single;
	bool multi;
	bool slash;
	bool s_quote;
	bool d_quote;
} comments;


/*
	Opens a file in read-only.

	@param	filename	file name from argv[1].
	@return				file pointer to filename.
*/
static FILE *open_file(const char *filename);

/*
	Checks if in a multi line comment and if it should be terminated.
	Returns true even on characters that end the multi line comment.
	This is because that character would be scanned when it should not be.

	@param	ch		character to process.
	@param	prev	previous character seen.
	@param	fp		file stream.
	@return			true if in multi comment, false if not.
*/
static bool in_multi_comment(int ch, int prev, FILE *fp);

/*
	Scans the file for tags and adds or removes them in a linked list.
	Verifies the stack is empty and prints the relevant message.

	@return		exit_success or exit_failure
*/
int scan_file();

#endif /* FILE_H */
