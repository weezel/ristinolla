CC = clang
CFLAGS = -g -ansi -pedantic -Wall #-Wextra
LDFLAGS :=
OS = $(shell uname -s)

# OS related switches
ifeq ($(OS), Linux)
	LDFLAGS += -lbsd
endif


.PHONY: all clean

all: slist
	$(CC) $(CFLAGS) ${INCLUDES} slist.o ristinolla.c -o ristinolla $(LDFLAGS)
slist:
	$(CC) $(CFLAGS) -c -o slist.o slist.c
clean:
	rm -f *.o *.core ristinolla slist
