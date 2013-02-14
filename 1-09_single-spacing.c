#include <stdio.h>

/* The C Programming Language, 2nd Edition
 *
 * Exercise 1-9: Write a program to copy its input to its output, replacing each
 * string of one or more blanks by a single blank.
 *
 * Answer: Run a loop with getchar() and check its value. If it's a space, count
 * it, but prevent further spaces from being printed. Anything else should
 * simply be spat out.
 */

int main(void) {
	char c;
	int spaces = 0;

	while ((c = getchar()) != EOF) {
		if (c == ' ') {
			if (spaces == 0) {
				putchar(c);
			}
			spaces++;
		} else {
			putchar(c);
		}
	}

	return 0;
}
