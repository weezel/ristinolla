CC=clang -g

all: slist
	${CC} -ansi -pedantic -Wall -o ristinolla ristinolla.c slist.o
slist:
	${CC} -ansi -pedantic -Wall -c -o slist.o slist.c
clean:
	rm -f *.o *.core ristinolla slist
