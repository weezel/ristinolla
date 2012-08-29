#include <err.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "slist.h"

static size_t slist_size;
static struct slist *slist_head;


/* return 1 if empty, else 0 */
int
slist_isempty(struct slist *sl)
{
	if (slist_size > 0)
		return 0;
	return 1;
}

struct slist *
slist_initialize_node(struct point *p)
{
	struct slist	*node = NULL;

	if ((node = malloc(sizeof(struct slist))) == NULL)
		err(1, "malloc");
	memset(node, 0, sizeof(*node));

	if ((node->point = malloc(sizeof(struct point))) == NULL)
		err(2, "malloc");
	memcpy(node->point, p, sizeof(struct point));

	node->next = NULL;

	return node;
}

void
slist_clear(struct slist *sl)
{
	while (slist_head != NULL)
		slist_removebeginning(slist_head);
}

void
slist_insertbeginning(struct slist *sl, struct point *p)
{
	struct slist	*node = NULL;

	node = slist_initialize_node(p);

	if (slist_isempty(sl) == 1) {
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
slist_removebeginning(struct slist *sl)
{
	struct slist	*newhead = NULL;

	if (slist_isempty(sl) == 1)
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
slist_print()
{
	struct slist	*node;

	node = slist_head;
	if (node == NULL) {
		fprintf(stdout, "List is empty [size %zu].\n", slist_size);
		return;
	}

	do {
		fprintf(stdout, "%c at (%zu, %zu) [size %zu]\n",
			node->point->merkki, node->point->x, node->point->y, slist_size);
		node = node->next;
	} while (node != NULL) ;
}

void
_slist_test(void)
{
	struct slist	*sl = NULL;
	struct point	*p  = NULL;
	struct point	*p2 = NULL;

	if ((p = malloc(sizeof(struct point))) == NULL)
		err(1, "död");
	if ((p2 = malloc(sizeof(struct point))) == NULL)
		err(1, "död");

	p->x = 5;
	p->y = 8;
	p->merkki = '#';
	p2->x = 1;
	p2->y = 2;
	p2->merkki = '#';

	printf("EMPTY LIST\n");
	slist_print();
	printf("\n");

	printf("ONE ELEMENT\n");
	slist_insertbeginning(sl, p);
	slist_print();
	printf("\n");

	printf("TWO ELEMENTS\n");
	slist_insertbeginning(sl, p2);
	slist_print();
	printf("\n");

	printf("REMOVE LAST ELEMENT\n");
	slist_removebeginning(sl);
	slist_print();
	printf("\n");

	printf("REMOVE LAST ELEMENT #2\n");
	slist_removebeginning(sl);
	slist_print();
	printf("\n");

	printf("TRY TO REMOVE FROM AN EMPTY LIST\n");
	slist_removebeginning(sl);
	slist_print();
	printf("\n");

	printf("NEW MALLOC\n");
	if ((p = malloc(sizeof(struct point))) == NULL)
		err(1, "död");
	if ((p2 = malloc(sizeof(struct point))) == NULL)
		err(1, "död");
	p->x = 1;
	p->y = 1;
	p->merkki = '#';
	p2->x = 9;
	p2->y = 9;
	p2->merkki = '#';
	slist_insertbeginning(sl, p);
	slist_insertbeginning(sl, p2);
	slist_print();
	printf("\n");

	printf("CLEAR ALL\n");
	slist_clear(sl);
	slist_print();
	printf("\n");

	sl = NULL;
}

