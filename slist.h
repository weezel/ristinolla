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

int slist_isempty(struct slist *);
struct slist *slist_initialize_node(struct point *);
void slist_clear(struct slist *);
void slist_insertbeginning(struct slist *, struct point *);
void slist_removebeginning(struct slist *);
void slist_print();
void _slist_test(void);

#endif /* _SLIST_H_ */
