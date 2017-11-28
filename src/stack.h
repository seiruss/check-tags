#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

/******************************************************************************
	Check if this top of the stack is empty. Returns true or false.
******************************************************************************/
bool is_empty();

/******************************************************************************
	Prints an error message if there are no tags on the stack and exits.
******************************************************************************/
static void no_open_tag();

/******************************************************************************
	Returns the top tag.
******************************************************************************/
static char get_top_tag();

/******************************************************************************
	Returns the top line.
******************************************************************************/
static int get_top_line();

/******************************************************************************
	Returns the top column.
******************************************************************************/
static int get_top_col();

/******************************************************************************
	Adds a new open tag to the stack. Returns nothing.
******************************************************************************/
void add_to_top(char tag, int line, int col);

/******************************************************************************
	Checks to see if the current closing tag matches the opening tag.
	If not, displays an error showing the unexpected close tag and
	what tag was expected, then exits.
	Otherwise, it frees that tag from the stack. Returns nothing.
******************************************************************************/
void remove_from_top(int ch, int line, int col);

#endif // STACK_H
