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

int scan_file();

#endif /* FILE_H */
