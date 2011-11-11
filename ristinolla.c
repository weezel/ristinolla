#include <stdio.h>
#include <stdlib.h>

#define	SIVU 50
#define M1 'X'
#define M2 'O' /* iso o, jos nyt unohdat */

char **luo_areena(void);

int
main(int argc, const char *argv[])
{
	char	**areena = NULL;
	
	areena = luo_areena();

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
