#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"
#include "file.h"
#include "check_tags.h"

struct node *top = NULL;

/*
 * Check if the top of the stack is empty.
 *
 * @return	true - stack is empty, false - stack is not empty.
 */
bool is_empty()
{
	return (top == NULL);
}

/*
 * Get the top tag, line or column in the linked list.
 *
 * @param	c	option to select node type.
 * @return		top tag, line or column.
 */
static int get_top_tag(int c)
{
	if (is_empty()) {
		PRINTE("There are no more open tags\n");
		return EXIT_FAILURE;
	}

	switch (c) {
	case TOP_TAG:
		return top->tag;
	case TOP_LINE:
		return top->line;
	case TOP_COL:
		return top->col;
	default:
		PRINTE("Invalid option in get_top_tag, %c\n", c);
		return EXIT_FAILURE;
	}

	/* Should never get here */
	return EXIT_FAILURE;
}

/*
 * Add tag
 *
 * Adds a new open tag to the stack.
 *
 * @param	tag		tag to add.
 * @param	line		line to add.
 * @param	col		column to add.
 * @return			exit_success or exit_failure.
 */
int add_to_top(char tag, int line, int col)
{
	struct node *new_node = malloc(sizeof(struct node));

	if (new_node == NULL) {
		PRINTE("No memory to add a new tag\n");
		return EXIT_FAILURE;
	}

	new_node->tag = tag;
	new_node->line = line;
	new_node->col = col;

	new_node->prev = top;
	top = new_node;

	PRINTV("Added %6c %6d %6d\n", tag, line, col);

	return EXIT_SUCCESS;
}

/*
 * Remove tag
 *
 * Checks to see if the current closing tag matches the opening tag.
 * If not, displays an error showing the unexpected close tag and
 * what tag was expected. Otherwise, it frees that tag from the stack.
 *
 * @param	tag		tag to remove.
 * @param	line		line number of the tag.
 * @param	col		column number of the tag.
 * @return			exit_success or exit_failure.
 */
int remove_from_top(int tag, int line, int col)
{
	if (is_empty()) {
		/*
		 * Can not show the problem tag here as it will always show
		 * one of the last tags even if that is not the problem.
		 */

		/* fprintf(stderr, "Error: No more open tags for close tag, %c ", ch);
		fprintf(stderr, "on line %d column %d\n", line, col); */

		PRINTE("There are more close tags than open tags\n");
		return EXIT_FAILURE;
	}

	char top_tag = get_top_tag(TOP_TAG);
	if (top_tag == EXIT_FAILURE)
		return EXIT_FAILURE;

	if ((top_tag == LEFT_PARENTHESIS && tag != RIGHT_PARENTHESIS) || \
		(top_tag == LEFT_BRACKET && tag != RIGHT_BRACKET) || \
		(top_tag == LEFT_BRACE && tag != RIGHT_BRACE))
	{
		PRINTE("Unexpected close tag, %c on line %d column %d\n"
			"Expected close tag for %c on line %d column %d\n", \
			tag, line, col, top_tag, get_top_tag(TOP_LINE), \
			get_top_tag(TOP_COL));

		return EXIT_FAILURE;
	}

	struct node *temp;
	temp = top;
	top = top->prev;
	free(temp);

	PRINTV("Removed %4c %6d %6d\n", tag, line, col);

	return EXIT_SUCCESS;
}
