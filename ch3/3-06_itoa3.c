#include <stdio.h>
#include <string.h>
#include <limits.h>

/* The C Programming Language: 2nd Edition
 *
 * Exercise 3-6: Write a version of itoa that accepts three arguments instead
 * of two. The third argument is a minimum field width; the converted number
 * must be padded with blanks on the left if necessary to make it wide enough.
 *
 * Answer: This is trivial. Process the number, then check the value of i. If
 * it's less than the field width, add a blank until i is equal to the field
 * width and terminate your string.
 */

void reverse(char s[]) {
	int c, i, j;

	for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

void itoa(int n, char s[], unsigned fw) {
	int i, sign, min; // Add 'min' for later use

	if ((sign = n) < 0) {
		/* Detect this and add one so it can properly be made positive */
		if (n == INT_MIN) {
			n += 1;
			min = 1;
		}
		n = -n;
	}
	i = 0;
	do {
		/* If it's the first iteration of the loop and we've established
		 * that n == INT_MIN, we need to add one to the resulting string for it
		 * to be displayed properly. */
		if (i == 0 && min == 1) {
			s[i++] = n % 10 + '1';
		} else {
			s[i++] = n % 10 + '0';
		}
	} while ((n /= 10) > 0);
	if (sign < 0) {
		s[i++] = '-';
	}
	while (i < fw) {
		s[i++] = ' ';
	}
	s[i] = '\0';
	reverse(s);
}

int main() {
	int i;
	char foo[16] = "";
	int tests[5] = {-25, 409689, 8, -1000, 135};
	for (i = 0; i < 5; i++) {
		itoa(tests[i], foo, 5);
		printf("Pad to 5 spaces! '%s'\n", foo);
	}
	return 0;
}
