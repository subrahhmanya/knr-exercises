#include <stdio.h>

/* The C Programming Language: 2nd Edition
 * Exercise 1-21:
 * "Write a program `entab` that replaces strings of blanks by the minimum
 * number of tabs and blanks to achieve the same spacing. Use the same tab
 * stops as for `detab`. When either a tab or a single blank would suffice to
 * reach a tab stop, which should be given preference?"
 *
 * Answer: A blank. A tab character that comes after (tabstop - 1) blanks makes
 * little-to-no sense and could mess up alignment in some environments.
 *
 */

#define TABWIDTH 8

int main(void) {
	int column, c, spaces;
	spaces = column = 0;
	while ((c = getchar()) != EOF) {
		// First thing's first, advance by a column.
		column++;

		if (c == ' ') {
			/* Add to 'spaces' immediately, we'll decide if it needs to be
			 * output later.
			 */
			spaces++;

			if (column % TABWIDTH == 0 && spaces > 0) {
				putchar('\t');
				spaces = 0; // No spaces are left when we tab!
			}

		} else {
			/* Be sure to output any leftover spaces when we come across a
			 * non-space character. This should allow for spaces between words
			 * that don't fall along the tabstop lines.
			 */

			while (spaces > 0) {
				putchar(' ');
				spaces--;
			}

			// As usual, reset things on a newline.
			if (c == '\n') {
				column = 0;
				spaces = 0;
			}

			// Now we can output whatever it is.
			putchar(c);
		}
	}
	return 0;
}
