#include <stdio.h>

/* The C Programming Language, 2nd Edition
 *
 * Exercise 1-6: Verify that the expression 'getchar() != EOF' is 0 or 1.
 *
 * Answer: Easy.
 */

int main(void) {
	int c;
	c = (getchar() != EOF);
	printf("%d\n", c);
	return 0;
}
