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
 *
 * Answer: A recursive function should do the job. I think...
 *
 */

#define LIMIT 17

char test[LIMIT] = "";
int i = 0;
int c;

void save_string(char s[]) {
	if (i < LIMIT - 1) {
		c = getchar();
		if (c != '\n') {
			if (c != EOF) {
				s[i] = c;
				i++;
			} else {
				return;
			}
		} else {
			return;
		}
		save_string(s);
	}
}

int main() {
	save_string(test);
	printf("%s\n", test);
	return 0;
}
