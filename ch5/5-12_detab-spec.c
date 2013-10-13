#include <stdio.h>
#include <ctype.h>

/* The C Programming Language: 2nd Edition
 *
 * Exercise 5-12: Extend `entab` and `detab` to accept the shorthand
 * `entab -m +n` to mean tab stops every n columns, starting at column m.
 * Choose convenient (for the user) default behavior.
 */

#define DEFAULTTAB 8

int main(int argc, char *argv[]) {
	int column, c;
	int tabstart = (-1);
	int tabevery = (-1);
	char arg[4];
	column = 0;

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
				printf("detab: unrecognized argument %s\n", *argv);
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

		if (c == '\t') {
			/* No point in processing our tabs until we're after the offset */
			if (column > tabstart) {
				putchar(' ');
				while ((column - tabstart) % tabevery != 0) {
					putchar(' ');
					column++;
				}
			} else {
				putchar(' ');
			}
		} else {
			/* reset the counts on a newline */
			if (c == '\n') {
				column = 0;
			}
			putchar(c);
		}
	}
	
	return 0;
}
