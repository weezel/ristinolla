CC = clang
CFLAGS = -g -ansi -pedantic -Wall
OS = $(shell uname -s)
LDFLAGS =

# OS related switches
ifeq ($(OS), Linux)
	LDFLAGS += -lbsd
endif


default: all

all: slist
	$(CC) $(LDFLAGS) $(CFLAGS) -o ristinolla ristinolla.c slist.o
slist:
	$(CC) $(LDFLAGS) $(CFLAGS) -c -o slist.o slist.c
clean:
	rm -f *.o *.core ristinolla slist
