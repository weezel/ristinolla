#include <err.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "slist.h"

/* return 1 if empty, else 0 */
int
isempty(struct slist *sl)
{
	if (slist_size > 0)
		return 0;
	return 1;
}

struct slist *
_initialize_node(struct point *p)
{
	struct slist	*node = NULL;

	if ((node = malloc(sizeof(node))) == NULL)
		err(1, "malloc");
	memset(node, 0, sizeof(*node));
	node->next = NULL;
	node->point = p;

	return node;
}

void
slist_clear(struct slist *sl)
{
	while (slist_head != NULL)
		removebeginning(slist_head);
}

void
insertbeginning(struct slist *sl, struct point *p)
{
	struct slist	*node = NULL;

	node = _initialize_node(p);

	if (isempty(sl) == 1) {
		slist_head = node;
		slist_head->next = NULL;
		slist_size = 1;
	} else {
		node->next = slist_head;
		slist_head = node;
		slist_size++;
	}
}

void
removebeginning(struct slist *sl)
{
	struct slist	*newhead = NULL;

	if (isempty(sl) == 1)
		return;

	newhead = slist_head->next;

	if (slist_head->point) {
		free(slist_head->point);
		slist_head->point = NULL;
	}
	slist_head = newhead;

	slist_size--;
}

void
print_slist()
{
	struct slist	*node;

	node = slist_head;
	if (node == NULL) {
		fprintf(stdout, "List is empty [size %zu].\n", slist_size);
		return;
	}

	do {
		fprintf(stdout, "X: %zu, Y: %zu [size %zu]\n",
			node->point->x, node->point->y, slist_size);
		node = node->next;
	} while (node != NULL) ;
}

void
test_slist(void)
{
	struct slist	*sl;
	struct point	*p;
	struct point	*p2;

	if ((p = malloc(sizeof(struct point))) == NULL)
		err(1, "död");
	if ((p2 = malloc(sizeof(struct point))) == NULL)
		err(1, "död");

	p->x = 5;
	p->y = 8;
	p2->x = 1;
	p2->y = 2;

	printf("EMPTY LIST\n");
	print_slist();
	printf("\n");

	printf("ONE ELEMENT\n");
	insertbeginning(sl, p);
	print_slist();
	printf("\n");

	printf("TWO ELEMENTS\n");
	insertbeginning(sl, p2);
	print_slist();
	printf("\n");

	printf("REMOVE LAST ELEMENT\n");
	removebeginning(sl);
	print_slist();
	printf("\n");

	printf("REMOVE LAST ELEMENT #2\n");
	removebeginning(sl);
	print_slist();
	printf("\n");

	printf("TRY TO REMOVE FROM AN EMPTY LIST\n");
	removebeginning(sl);
	print_slist();
	printf("\n");

	printf("NEW MALLOC\n");
	if ((p = malloc(sizeof(struct point))) == NULL)
		err(1, "död");
	if ((p2 = malloc(sizeof(struct point))) == NULL)
		err(1, "död");
	p->x = 1;
	p->y = 1;
	p2->x = 9;
	p2->y = 9;
	insertbeginning(sl, p);
	insertbeginning(sl, p2);
	print_slist();
	printf("\n");

	printf("CLEAR ALL\n");
	slist_clear(sl);
	print_slist();
	printf("\n");

	sl = NULL;
}

