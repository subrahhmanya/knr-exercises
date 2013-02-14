#include <stdio.h>

/* The C Programming Language, 2nd Edition
 *
 * Exercise 1-2: Experiment to find out what happens when printf()'s argument
 * string contains \c, where 'c' is some character that's not \, t, b, n, or ".
 *
 * Answer: This file will not (normally) compile because \d is not a valid
 * escape sequence. Your compiler may ignore this, however.
 */

int main(void) {
	printf("Hello world! \d\n");
	return 0;
}
