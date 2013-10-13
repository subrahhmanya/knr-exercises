#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* The C Programming Language: 2nd Edition
 *
 * Exercise 5-12: Extend `entab` and `detab` to accept the shorthand
 * `entab -m +n` to mean tab stops every n columns, starting at column m.
 * Choose convenient (for the user) default behavior.
 */

#define DEFAULTTAB 8

int main(int argc, char *argv[]) {
	int column, c, spaces;
	int tabstart = (-1);
	int tabevery = (-1);
	char arg[4];
	spaces = column = 0;

	if (argc > 1) {
		int i = 1;
		int j = 0;
		while (--argc > 0) {
			c = argv[i][j++];
			if (c == '-' || c == '+') {
				while (isdigit(argv[i][j])) {
					arg[j - 1] = argv[i][j];
					j++;
				}
				arg[3] = '\0';
				if (c == '-') {
					tabstart = atoi(arg);
				} else {
					tabevery = atoi(arg);
				}
				j = 0;
			} else {
				printf("entab: unrecognized argument %s\n", *argv);
			}
			i++;
		}
	}
	/* Clean up the mess if either argument hasn't been set to something sane */
	if (tabstart == -1) {
		tabstart = 0;
	}
	if (tabevery == -1) {
		tabevery = DEFAULTTAB;
	}

	while ((c = getchar()) != EOF) {
		column++;

		if (c == ' ') {
			/* No point in starting our tabs until we're after the offset */
			if (column > tabstart) {
				spaces++;
				if ((column - tabstart) % tabevery == 0) {
					if (spaces > 1) {
						putchar('\t');
						spaces = 0;
					}
				}
			}
		} else {
			/* output all extra spaces first */
			while (spaces > 0) {
				putchar(' ');
				spaces--;
			}
			/* reset the counts and argument position on a newline */
			if (c == '\n') {
				column = 0;
				spaces = 0;
			}
			putchar(c);
		}
	}
	
	return 0;
}
