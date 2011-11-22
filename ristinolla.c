#include <sys/queue.h>

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "slist.h"

#define	SIVU 10
#define M1 'X'
#define M2 'O' /* iso o, jos nyt unohdat */


int laillinen_siirto(char **, struct point *);
struct point satunnainen_paikka(char **, char);
void tulosta_areena(char **);
char **luo_areena(void);
void free_areena(char **);
__dead void usage(void);


int
main(int argc, const char *argv[])
{
	char		**areena = NULL;
	char		 *file = NULL;
	int		  cflag, ch;
	struct point	  p;
	struct slist	 *siirrot = NULL;
	size_t i = 0;

	cflag = 0;

	if (argc < 2)
		usage();

	areena = luo_areena();
	memset(&p, 0, sizeof(struct point));

	while ((ch = getopt(argc, (char *const *)argv, "cf:")) != -1) {
		switch ((char)ch) {
		case 'c':
			cflag = 1;
			break;
		case 'f':
			file = optarg;
			break;
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;

	for (i = 0; i < 20; i++) {
		if (i % 2 == 0) {
			p = satunnainen_paikka(areena, M1);
			slist_insertbeginning(siirrot, &p);
		}
		else {
			p = satunnainen_paikka(areena, M2);
			slist_insertbeginning(siirrot, &p);
		}
	}

	tulosta_areena(areena);
	slist_print(siirrot);
	slist_clear(siirrot);

	free_areena(areena);

	return 0;
}

/* Palauta 1 mikäli siirto on laillinen */
int
laillinen_siirto(char **t, struct point *p)
{
	if (p->x < SIVU && p->y < SIVU && /* size_t:n takia x tai y ei voi olla < 0 */
			t[p->x][p->y] == ' ')
		return 1;
	return 0;
}

struct point
satunnainen_paikka(char **t, char c)
{
	struct point	p;

	do {
		p.x = arc4random() % SIVU;
		p.y = arc4random() % SIVU;
	} while (laillinen_siirto(t, &p) == 0);
	t[p.x][p.y] = c;

	switch (c) {
	case M1:
		p.merkki = M1;
		break;
	case M2:
		p.merkki = M2;
		break;
	}

	return p;
}

char **
luo_areena()
{
	char	**t = NULL;
	size_t	  i = 0;
	size_t	  j = 0;

	t = calloc(SIVU, sizeof(char *));
	if (t == NULL) {
		err(1, "calloc epäonnistui");
	}

	for (i = 0; i < SIVU; i++) {
		t[i] = calloc(SIVU, sizeof(char));
		if (t[i] == NULL)
			err(1,"calloc epäonnistui");

		for (j = 0; j < SIVU; j++)
			t[i][j] = ' ';
	}
	return t;
}

void
free_areena(char **t)
{
	int i;

	for (i = 0; i < SIVU; i++) {
		free(t[i]);
		t[i] = NULL;
	}
	free(t);
	t = NULL;
}

void
tulosta_areena(char **t)
{
	ssize_t	i, j;

	for (i = -1; i < SIVU; i++) {
		for (j = -1; j < SIVU; j++) {
			if (i == -1 || j == -1 || i + 1 == SIVU || j + 1 == SIVU)
				fprintf(stdout, "%c", ':');
			else
				fprintf(stdout, "%c", t[i][j]);
		}
		fprintf(stdout, "\n");
	}
}

void
lue_tiedosto_areenaksi(int fd)
{
}

void
usage(void)
{
	extern char *__progname;

	(void)fprintf(stderr, "usage: %s [-c] [-f file]\n", __progname);
	exit(1);
}

