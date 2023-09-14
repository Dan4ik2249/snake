// created by DanSul
#include <ncurses.h>
#include <stdlib.h>

int create_map(int *m)
{	
	for (int i = 0; i < LINES*COLS; i++) {
		m[i] = 0;
	}
	return 0;
}

int main(int argc, char *argv[])
{
	int x = 0, y = 0, ch = 0;
	int count = 0, k = 0;
	int p_x, p_y;
	int axis[2][8];
	if (NULL == initscr()) return __LINE__;
	int map[LINES*COLS];
	create_map(map);
	noecho();
	curs_set(0);
	keypad(stdscr, TRUE);
	do {
		if(count > 7) {
			mvaddch(axis[1][0], axis[0][0], ' ');
			count = 8;
			}

		switch(ch) {
			case KEY_UP:
				y = (y + LINES - 1) % LINES;
				break;
			case KEY_DOWN:
				y = (y + 1) % LINES;
				break;
			case KEY_LEFT:
				x = (x + COLS - 1) % COLS;
				break;
			case KEY_RIGHT:
				x = (x + 1) % COLS;
				break;
			default:
				break;
		}
		mvaddch(y, x, '*');
		if (k < 8) {
			axis[0][k] = x;
			axis[1][k] = y;
		}
		else {
			for(int i = 0; i < 7; i++ ) axis[0][i] = axis[0][i+1];
			axis[0][7] = x;
			for(int i = 0; i < 7; i++) axis[1][i] = axis[1][i+1];
			axis[1][7] = y;
			k = 9;
	}
		k++;
		count++;
		refresh;
	} while('q' != (ch = getch()));
	endwin();
	return 0;
}
