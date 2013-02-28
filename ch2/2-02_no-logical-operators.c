#include <stdio.h>

/* The C Programming Language, 2nd Edition
 *
 * Exercise 2-2: Write a loop equivalent to the 'for' loop above without
 * using && or ||.
 *
 * (The for loop is:
 *
 * for (i=0; i < lim - 1 && (c = getchar()) != '\n' && c != EOF)
 *     i++;
 * )
 *
 * Answer: A while loop and a few 'if's should do it.
 *
 */

#define LIMIT 17

char test[LIMIT] = "";
int i = 0;
int c;

int main() {
	while (i < LIMIT - 1) {
		c = getchar();
		if (c != '\n') {
			if (c != EOF) {
				test[i] = c;
				i++;
			} else {
				break;
			}
		} else {
			break;
		}
	}
	printf("%s\n", test);
	return 0;
}
