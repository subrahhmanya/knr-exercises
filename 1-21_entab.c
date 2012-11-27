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
	int c, spaces;
	spaces = 0;
	while ((c = getchar()) != EOF) {
		// Make sure the character is a space...
		if (c == ' ') {
			++spaces;
			// When spaces is equal to TABWIDTH, we can add a tab
			if (spaces == TABWIDTH) {
				putchar('\t');
				spaces = 0;
			}
		} else {
			/* As soon as we hit a non-space character, we need to make sure
			 * there aren't 1-7 spaces leftover. These need to be output before
			 * we output the non-space character itself! This little loop is
			 * interesting because it solves the problem of leftover spaces
			 * _and_ gets the 'spaces' back to zero, which it needs to be once
			 * we hit a non-space character.
			 */
			while (spaces != 0) {
				putchar(' ');
				--spaces;
			}
			// Output the non-space character.
			putchar(c);
		}
	}
}
