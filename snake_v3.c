// created by DanSul

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#define MAX_SIZE 32

int restructure_map(int *map, int x, int y)
{
	srand(time(NULL));
	map[y*COLS + x] = 0;
	int k = rand()%100;
	k %= LINES;
	int m = rand()%1000;
	m %= COLS;
	map[k*COLS + m] = 1;
	return 0;
}

int create_map(int *m)
{	srand(time(NULL));
	int a;
	int b;
	
	for (int i = 0; i < LINES; i++) {
		for (int j = 0; j < COLS; j++) {
			m[i*COLS + j] = 0;
		}
	}

	for (int k = 0; k < 10; k++) {
		a = rand()%100;
		a %= LINES;
		b = rand()%1000;
		b %= COLS;
		m[a*COLS+b] = 1;
	}
	return 0;
}

int main(int argc, char *argv[])
{
	int x = 0, y = 0, ch = 0;
	unsigned int count, k = 0;
	int p_x, p_y;
	unsigned int size = 8;
	int axis[2][MAX_SIZE];

	if (NULL == initscr()) return __LINE__;
	int map[LINES*COLS];

	create_map(map);
	noecho();
	curs_set(0);
	keypad(stdscr, TRUE);

	do {
		if(count > (size - 1)) {
			mvaddch(axis[1][0], axis[0][0], ' ');
			count = size + 1;
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
		if (k < size) {
			axis[0][k] = x;
			axis[1][k] = y;
		}
		else {
			for(int i = 0; i < (size - 1); i++ ) axis[0][i] = axis[0][i+1];
			axis[0][size - 1] = x;
			for(int i = 0; i < (size - 1); i++) axis[1][i] = axis[1][i+1];
			axis[1][size - 1] = y;
			k = MAX_SIZE;
		}
		
		for (int i = 0; i < LINES; i++) {
			for (int j = 0; j < COLS; j++) {
				if (map[i*COLS + j] == 1) mvaddch(i, j, '*');
			}
		}

		if (map[y*COLS + x] == 1) {
			restructure_map(map, x, y);
			if (size < MAX_SIZE) size++;
		}

		k++;
		count++;
		refresh;
	} while('q' != (ch = getch()));
	endwin();
	return 0;
}
