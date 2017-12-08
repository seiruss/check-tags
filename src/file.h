#ifndef FILE_H
#define FILE_H

/* Tags the program checks for in the file */
#define LEFT_PARENTHESIS	'('
#define RIGHT_PARENTHESIS	')'
#define LEFT_BRACKET		'['
#define RIGHT_BRACKET		']'
#define LEFT_BRACE			'{'
#define RIGHT_BRACE			'}'

typedef int BOOL;
#define TRUE 1
#define FALSE 0


/*
	Opens a file in read-only.

	@param	filename	file name from argv[1].
	@return				file pointer to filename.
*/
FILE *open_file(const char *filename);

/*
	Scans the file for tags and adds or removes them in a linked list.
	Verifies the stack is empty and prints the relevant message.

	@param	fp	file to scan.
	@return		true - failure, false - success.
*/
BOOL scan_file(FILE *fp);

#endif
