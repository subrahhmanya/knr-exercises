#include <stdio.h>

/* The C Programming Language: 2nd Edition
 *
 * Exercise 2-10: Rewrite the function 'lower', which converts upper case
 * letters to lower case, with a conditional expression instead of if-else.
 *
 * Answer: The tertiary ?: operators also _evaluate_, so they can be used in
 * a lot of different places.
 */

int lower(int c) {
	return (c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c;
}

int main() {
	char foo = 'F';
	printf("The follow letter should be lowercase: %c\n", lower(foo));
	return 0;
}
