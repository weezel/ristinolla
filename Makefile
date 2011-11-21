CC=clang

all:
	${CC} -g -ansi -pedantic -Wall -o ristinolla ristinolla.c
slist:
	${CC} -g -ansi -pedantic -Wall -o slist slist.c
