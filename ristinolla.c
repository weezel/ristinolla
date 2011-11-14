#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define	SIVU 50
#define M1 'X'
#define M2 'O' /* iso o, jos nyt unohdat */

struct point {
	size_t	x;
	size_t	y;
};

int laillinen_siirto(struct point *);
char **luo_areena(void);
__dead void usage(void);


int
main(int argc, const char *argv[])
{
	char	**areena = NULL;
	char	 *file = NULL;
	int	  bflag, ch;

	bflag = 0;

	if (argc < 2)
		usage();

	areena = luo_areena();

	while ((ch = getopt(argc, (char *const *)argv, "bf:")) != -1) {
		switch ((char)ch) {
		case 'b':
			bflag = 1;
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

	fprintf(stdout, "%s\n", file);

	return 0;
}

/* Palauta 1 mikäli siirto on laillinen */
int
laillinen_siirto(struct point *p)
{
	if (p->x < SIVU && p->y < SIVU) /* size_t:n takia x tai y ei voi olla < 0 */
		return 1;
	return 0;
}

char **
luo_areena()
{
	char	**t = NULL;
	size_t	  i = 0;

	t = calloc(SIVU, sizeof(char *));
	if (t == NULL) {
		err(1, "calloc epäonnistui");
	}

	for (i=0; i < SIVU; i++) {
		t[i] = calloc(SIVU, sizeof(char));
		if (t[i] == NULL) {
			err(1,"calloc epäonnistui");
		}
	}
	return t;
}

void
usage(void)
{
	extern char *__progname;

	(void)fprintf(stderr, "usage: %s [-b] [-f file]\n", __progname);
	exit(1);
}

