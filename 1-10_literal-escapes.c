#include <stdio.h>

/* The C Programming Language, 2nd Edition
 *
 * Exercise 1-10: Write a program to copy its input to its output, replacing
 * each tab by '\t', each backspace by '\b', and each backslash by '\\'. This
 * makes tabs and backspaces visible in an unambiguous way.
 *
 * Answer: Run a loop with getchar() and check its value. When you run into a
 * tab, backspace, or backslash, just output the two characters and move on.
 */

int main(void) {
	char c;

	while ((c = getchar()) != EOF) {
		if (c == '\t') {
			printf("\\t");
			continue;
		}
		if (c == '\b') {
			printf("\\b");
			continue;
		}
		if (c == '\\') {
			printf("\\\\");
			continue;
		}
		putchar(c);
	}

	return 0;
}
