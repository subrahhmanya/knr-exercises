#include <stdio.h>

/* The C Programming Language, 2nd Edition
 *
 * Exercise 1-8: Write a program to count blanks, tabs, and newlines.
 *
 * Answer: Run a loop with getchar() and check its value. Then add to the
 * counts and spit them out at the end of the loop.
 */

int main(void) {
	char c;
	int blanks, tabs, nls = 0;

	while ((c = getchar()) != EOF) {
		if (c == ' ') {
			blanks++;
		}
		if (c == '\t') {
			tabs++;
		}
		if (c == '\n') {
			nls++;
		}
	}

	printf("%d blanks, %d tabs, and %d newlines.\n", blanks, tabs, nls);
	return 0;
}
