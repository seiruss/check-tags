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

bool is_empty();
int add_to_top(char tag, int line, int col);
int remove_from_top(int tag, int line, int col);

#endif /* STACK_H */
