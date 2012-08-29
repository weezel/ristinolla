#include <stdio.h>
#include <ncurses.h>

#include "kayttoliittyma.h"

int
main(int argc, const char *argv[])
{
	int ch = 0;

	initscr();
	raw();
	keypad(stdscr, TRUE);
	noecho();
	alusta_varit();

	piirra_kentta();

	curs_set(0);
	while (ch != 'q') {
		ch = getch();

	}

	endwin();

	return 0;
}

void
alusta_varit(void)
{
	if (has_colors()) {
		start_color();
		init_pair(1, COLOR_BLUE,	COLOR_BLUE);
		init_pair(2, COLOR_GREEN,	COLOR_BLACK);
		init_pair(3, COLOR_YELLOW,	COLOR_CYAN);
		init_pair(4, COLOR_BLUE,	COLOR_WHITE);
		init_pair(5, COLOR_CYAN,	COLOR_MAGENTA);
		init_pair(6, COLOR_MAGENTA,	COLOR_BLACK);
		init_pair(7, COLOR_WHITE,	COLOR_GREEN);
	}
}

void
piirra_kentta(void)
{
	int	x = 0;
	int	y = 0;
	char	c = 0;

	for (y = 0; y < IKK_KORKEUS; y++) {
		for (x = 0; x < IKK_LEVEYS; x++) {
			move(y, x);
			attrset(COLOR_PAIR(6));
			addch('#');
		}
	}
	refresh();
}

