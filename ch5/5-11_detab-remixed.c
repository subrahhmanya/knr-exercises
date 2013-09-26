#include <stdio.h>

/* The C Programming Language: 2nd Edition
 *
 * Exercise 5-11: Modify the programs entab and detab (written as exercises in
 * Chapter 1) to accept a list of tab stops as arguments. Use the default tab
 * settings if there are no arguments.
 */

#define TABWIDTH 8

int main(int argc, char *argv[]) {
	int column, c, tabnum, stop;
	column = 0;

	if (argc > 1) {
		tabnum = 1;
		stop = atoi(argv[tabnum]);
	} else {
		tabnum = 0;
	}

	while ((c = getchar()) != EOF) {
		if (c == '\t') {
			if (argc > 1) {
				// advance the argument if we're ahead of the last one
				if (column > stop && tabnum < (argc -1)) {
					stop = atoi(argv[++tabnum]);
				}
				// insert our spaces up to the tabstop
				while (column <= stop) {
					putchar(' ');
					column++;
				}
				// advance the argument (again) if needed.
				if (tabnum < (argc - 1)) {
					stop = atoi(argv[++tabnum]);
				}
			} else {
				// default tabstopping
				while (column % TABWIDTH != 1) {
					putchar(' ');
					column++;
				}
			}
		} else {
			// reset counters and the arglist
			if (c == '\n') {
				column = 0;
				if (tabnum > 0) {
					tabnum = 1;
					stop = atoi(argv[tabnum]);
				}
			}
			putchar(c);
			column++;
		}
	}

	return 0;
}
