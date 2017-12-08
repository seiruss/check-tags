#ifndef STACK_H
#define STACK_H


/*
	Check if the top of the stack is empty.

	@return	true - stack is empty, false - stack is not empty.
*/
BOOL is_empty();

/*
	Prints an error message if there are no tags on the stack and exits.
*/
static void no_open_tag();

/*
	@return	top tag.
*/
static char get_top_tag();

/*
	@return	 top line number.
*/
static int get_top_line();

/*
	@return	top column number.
*/
static int get_top_col();

/*
	Add tag

	Adds a new open tag to the stack.

	@param	tag		tag to add.
	@param	line	line to add.
	@param	col		column to add.
*/
void add_to_top(char tag, int line, int col);

/*
	Remove tag

	Checks to see if the current closing tag matches the opening tag.
	If not, displays an error showing the unexpected close tag and
	what tag was expected, then exits.
	Otherwise, it frees that tag from the stack.

	@param	tag		tag to remove.
	@param	line	line number of the tag.
	@param	col		column number of the tag.
*/
void remove_from_top(int tag, int line, int col);

#endif
