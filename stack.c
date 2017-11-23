#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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

bool is_empty()
{
	return top == NULL;
}

char get_top_tag()
{
	// should never be empty
	if (is_empty())
	{
		fprintf(stderr, "Error: There are no more open tags\n");
		exit(EXIT_FAILURE);
	}

	return top->tag;
}

int get_top_line()
{
	// should never be empty
	if (is_empty())
	{
		fprintf(stderr, "Error: There are no more open tags\n");
		exit(EXIT_FAILURE);
	}

	return top->line;
}

int get_top_col()
{
	// should never be empty
	if (is_empty())
	{
		fprintf(stderr, "Error: There are no more open tags\n");
		exit(EXIT_FAILURE);
	}

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

void bad_nest(int ch, int line, int col)
{
	fprintf(stderr, "Error: Unexpected close tag, %c on line %d column %d\n", \
		ch, line, col);
	fprintf(stderr, "Expected close tag for %c on line %d column %d\n", \
		top->tag, top->line, top->col);

	exit(EXIT_FAILURE);
}

bool remove_from_top(int ch, int line, int col)
{
	if (is_empty())
	{
		fprintf(stderr, "Error: No more open tags for close tag, %c ", ch);
		fprintf(stderr, "on line %d column %d\n", line, col);
		exit(EXIT_FAILURE);
	}

	if (top->tag == LEFT_PARENTHESIS && ch != RIGHT_PARENTHESIS || \
		top->tag == LEFT_BRACKET && ch != RIGHT_BRACKET || \
		top->tag == LEFT_BRACE && ch != RIGHT_BRACE)
		return false;
	else
	{
		struct node *temp;
		temp = top;
		top = top->prev;
		free(temp);
	}

	return true;
}
