#include <stdio.h>

/* The C Programming Language, 2nd Edition
 *
 * Exercise 1-11: How would you test the word count program? What kinds of
 * input are most likely to uncover bugs if there are any?
 *
 * Answer: New lines (such as those caused by wrapping text) are most likely to
 * introduce erroneous word counts, as well as symbols that are strung together
 * but don't create actual words.
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
		} else if (state == OUT) {
			state = IN;
			nw++;
		}
	}

	printf("%d %d %d\n", nl, nw, nc);

	return 0;
}
