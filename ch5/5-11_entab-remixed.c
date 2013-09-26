#include <stdio.h>
#include <stdlib.h>

/* The C Programming Language: 2nd Edition
 *
 * Exercise 5-11: Modify the programs entab and detab (written as exercises in
 * Chapter 1) to accept a list of tab stops as arguments. Use the default tab
 * settings if there are no arguments.
 */

/* The directions for this exercise aren't terribly clear. The way I see it,
 * each argument is a character column that all tabs should align to. For the
 * entab portion, I should count 2+ spaces forward and, if I reach a tabstop,
 * insert a tab. Then move onto the next argument. If 2+ spaces are present,
 * but don't reach the tabstop threshold, the spaces are left alone. This is
 * the best I could manage with the ambiguous instructions.
 */

#define TABWIDTH 8

int main(int argc, char *argv[]) {
	int column, c, spaces, tabnum, stop;
	spaces = column = 0;

	if (argc > 1) {
		tabnum = 1;
		stop = atoi(argv[tabnum]);
	} else {
		tabnum = 0;
	}

	while ((c = getchar()) != EOF) {
		column++;

		if (c == ' ') {
			spaces++;
			if (argc > 1) {
				if (column == stop) {
					if (tabnum < (argc - 1)) {
						stop = atoi(argv[++tabnum]);
					}
					if (spaces > 1) {
						putchar('\t');
						spaces = 0;
					}
				} else if (column > stop && tabnum < (argc -1)) {
					stop = atoi(argv[++tabnum]);
				}
			} else {
			// we need to do default tabstopping
				if (column % TABWIDTH == 0 && spaces > 1) {
					putchar('\t');
					spaces = 0;
				}
			}
		} else {
			// output all extra spaces first
			while (spaces > 0) {
				putchar(' ');
				spaces--;
			}
			// reset the counts and argument position on a newline
			if (c == '\n') {
				column = 0;
				spaces = 0;
				if (tabnum > 0) {
					tabnum = 1;
					stop = atoi(argv[tabnum]);
				}
			}
			putchar(c);
		}
	}
	
	return 0;
}
