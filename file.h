#ifndef FILE_H
#define FILE_H

// Tags the program checks for in the file
#define LEFT_PARENTHESIS	'('
#define RIGHT_PARENTHESIS	')'
#define LEFT_BRACKET		'['
#define RIGHT_BRACKET		']'
#define LEFT_BRACE			'{'
#define RIGHT_BRACE			'}'

/*
	Retrieves the filename from argv[1] and assigns it to a dynamically
	allocated string. Returns the string pointer.
*/
char *get_filename(const char *argv[]);

/*
	Opens the file in read-only and returns the file pointer.
*/
FILE *open_file(const char *filename);

/*
	Scans the file for tags and adds or removes them in a linked list.
	Improperly nested tags are handled elsewhere. Verifies the stack
	is empty and prints the relevant message. Returns nothing.
*/
void scan_file(FILE *fp);

#endif // FILE_H
