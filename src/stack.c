#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "file.h"

struct node
{
	char tag;
	int line;
	int col;
	struct node *prev;
};

struct node *top = NULL;

BOOL is_empty()
{
	return (top == NULL);
}

static void no_open_tag()
{
	fprintf(stderr, "Error: There are no more open tags\n");
	exit(EXIT_FAILURE);
}

static char get_top_tag()
{
	if (is_empty())
		no_open_tag();

	return top->tag;
}

static int get_top_line()
{
	if (is_empty())
		no_open_tag();

	return top->line;
}

static int get_top_col()
{
	if (is_empty())
		no_open_tag();

	return top->col;
}

void add_to_top(char tag, int line, int col)
{
	struct node *new_node = malloc(sizeof(struct node));

	if (new_node == NULL)
	{
		fprintf(stderr, "Error: No memory to add a new tag\n");
		exit(EXIT_FAILURE);
	}

	new_node->tag = tag;
	new_node->line = line;
	new_node->col = col;

	new_node->prev = top;
	top = new_node;
}

void remove_from_top(int tag, int line, int col)
{
	if (is_empty())
	{
		/*
		*	Can not show the problem tag here as it will always show
		*	one of the last tags even if that is not the problem.
		*/

		/*
		fprintf(stderr, "Error: No more open tags for close tag, %c ", ch);
		fprintf(stderr, "on line %d column %d\n", line, col);
		*/

		fprintf(stderr, "Error: There are more close tags than open tags\n");
		exit(EXIT_FAILURE);
	}

	char top_tag = get_top_tag();

	if (top_tag == LEFT_PARENTHESIS && tag != RIGHT_PARENTHESIS || \
		top_tag == LEFT_BRACKET && tag != RIGHT_BRACKET || \
		top_tag == LEFT_BRACE && tag != RIGHT_BRACE)
	{
		fprintf(stderr, "Error: Unexpected close tag, %c on line %d column %d\n", \
		tag, line, col);
		fprintf(stderr, "Expected close tag for %c on line %d column %d\n", \
		get_top_tag(), get_top_line(), get_top_col());

		exit(EXIT_FAILURE);
	}

	struct node *temp;
	temp = top;
	top = top->prev;
	free(temp);
}
