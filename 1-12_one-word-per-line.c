#include <stdio.h>

/* The C Programming Language, 2nd Edition
 *
 * Exercise 1-12: Write a program that prints its input one word per line.
 *
 * Answer: Be sure to output letters when you're in a word, and a newline when
 * you're out of one.
 */

#define IN 1
#define OUT 0

int main(void) {
	int c, nl, nw, nc, state;
	state = OUT;
	nl = nw = nc = 0;

	while ((c = getchar()) != EOF) {
		nc++;
		if (c == '\n') {
			nl++;
		}
		if (c == ' ' || c == '\n' || c == '\t') {
			state = OUT;
			putchar('\n');
		} else if (state == OUT) {
			state = IN;
			nw++;
		}
		if (state == IN) {
			putchar(c);
		}
	}

	printf("%d %d %d\n", nl, nw, nc);

	return 0;
}
