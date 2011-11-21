#ifndef _SLIST_H_
#define _SLIST_H_

struct point {
	size_t	x;
	size_t	y;
	char	merkki;
};

struct slist {
	struct point *point;
	struct slist *next;
};

static size_t slist_size;
static struct slist *slist_head;

int isempty(struct slist *);
struct slist *initialize_node(struct point *);
void slist_clear(struct slist *);
void insertbeginning(struct slist *, struct point *);
void removebeginning(struct slist *);
void print_slist();
void test_slist(void);

#endif /* _SLIST_H_ */
