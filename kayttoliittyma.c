#include <ncurses.h>
#include <stdio.h>
#include <string.h>

#include "kayttoliittyma.h"

int
main(void)
{
	int ch = 0;
	struct point cursor;

	memset(&cursor, 0, sizeof(struct point));

	initscr();
	cbreak();
	keypad(stdscr, TRUE);
	noecho();
	alusta_varit();

	piirra_kentta();

	curs_set(2);
	cursor.x = IKK_LEVEYS / 2;
	cursor.y = IKK_KORKEUS / 2;
	move(cursor.y, cursor.x);
	while ((ch = getch()) != 'q') {
		int	c = 0;

		switch (ch) {
		case 'k':
		case KEY_UP:
			if (laillinen_siirto(cursor.x, cursor.y - 1) < 0)
				continue;
			cursor.y--;
			attrset(COLOR_PAIR(7));
			move(cursor.y, cursor.x);
			break;
		case 'l':
		case KEY_RIGHT:
			if (laillinen_siirto(cursor.x + 1, cursor.y) < 0)
				continue;
			cursor.x++;
			attrset(COLOR_PAIR(7));
			move(cursor.y, cursor.x);
			break;
		case 'j':
		case KEY_DOWN:
			if (laillinen_siirto(cursor.x, cursor.y + 1) < 0)
				continue;
			cursor.y++;
			attrset(COLOR_PAIR(7));
			move(cursor.y, cursor.x);
			break;
		case 'h':
		case KEY_LEFT:
			if (laillinen_siirto(cursor.x - 1, cursor.y) < 0)
				continue;
			cursor.x--;
			attrset(COLOR_PAIR(7));
			move(cursor.y, cursor.x);
			break;
		case '1':
			c = getch();
			attrset(COLOR_PAIR(7));
			addch('X');
			move(cursor.y, cursor.x);
			break;
		case '2':
			c = getch();
			attrset(COLOR_PAIR(6));
			addch(' ');
			move(cursor.y, cursor.x);
			break;
		case TYHJA_MERKKI: /* XXX Space-näppäin, ei toimi vielä täysin
				      (tarvitsee kaksi painallusta) */
			c = getch();
			if (c == TYHJA_MERKKI) {
				attrset(COLOR_PAIR(7));
				addch('X');
			} /*else {
				attrset(COLOR_PAIR(4));
				addch(c);
				move(cursor.y, cursor.x);
			}*/
			break;
		}
		move(0, 2);
		attrset(COLOR_PAIR(6));
		printw(" (Piste nyt: x:%d, y:%d | %c) ", cursor.x, cursor.y, c);
		move(cursor.y, cursor.x);
	}

	clrtoeol();
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

int
laillinen_siirto(const int x, const int y)
{
	if (x < 1 || x >= IKK_LEVEYS)
		return -1;
	if (y < 1 || y > IKK_KORKEUS)
		return -1;
	return 0;
}

void
piirra_kentta(void)
{
	int	x = 0;
	int	y = 0;
	char	c = 0;

	attrset(COLOR_PAIR(6));
	/* Reunukset, X-akseli */
	for (x = 0; x < IKK_LEVEYS; x++) {
		move(0, x);
		addch('#');
		move(IKK_KORKEUS + 1, x);
		addch('#');
	}
	/* Reunukset, Y-akseli */
	for (y = 0; y < IKK_KORKEUS + 2; y++) {
		move(y, 0);
		addch('#');
		move(y, IKK_LEVEYS);
		addch('#');
	}
	/* Kentän luonti */
	for (y = 1; y < IKK_KORKEUS; y++) {
		for (x = 1; x < IKK_LEVEYS; x++) {
			move(y, x);
			addch(TYHJA_MERKKI);
		}
	}
	refresh();
}

