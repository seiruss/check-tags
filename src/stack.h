#ifndef STACK_H
#define STACK_H

#define TOP_TAG		't'
#define TOP_LINE	'l'
#define TOP_COL		'c'

struct node
{
	char tag;
	int line;
	int col;
	struct node *prev;
};


/*
	Check if the top of the stack is empty.

	@return	true - stack is empty, false - stack is not empty.
*/
bool is_empty();

/*
	Get the top tag, line or column in the linked list.

	@param	c	option to select node type.
	@return		top tag, line or column.
*/
static int get_top_tag(int c);

/*
	Add tag

	Adds a new open tag to the stack.

	@param	tag		tag to add.
	@param	line	line to add.
	@param	col		column to add.
	@return			exit_success or exit_failure.
*/
int add_to_top(char tag, int line, int col);

/*
	Remove tag

	Checks to see if the current closing tag matches the opening tag.
	If not, displays an error showing the unexpected close tag and
	what tag was expected. Otherwise, it frees that tag from the stack.

	@param	tag		tag to remove.
	@param	line	line number of the tag.
	@param	col		column number of the tag.
	@return			exit_success or exit_failure.
*/
int remove_from_top(int tag, int line, int col);

#endif /* STACK_H */
