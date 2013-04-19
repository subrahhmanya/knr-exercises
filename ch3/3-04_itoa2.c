#include <stdio.h>
#include <string.h>
#include <limits.h>

/* The C Programming Language: 2nd Edition
 *
 * Exercise 3-4: In a two's complement number representation, our version of
 * itoa does not handle the largest negative number, that is, the value of n
 * equal to -(2^wordsize-1). Explain why not. Modify it to print that value
 * correctly, regardless of the machine on which it runs.
 *
 * Answer: The reason it doesn't work is because zero (0) takes up one of the
 * possible numbers. When the number n is INT_MIN, the operation `n = -n` to
 * make it positive doesn't work, which makes the math later on moot. I fixed
 * this by detecting that it's the lowest possible number, then adding one.
 * This makes the resulting positive number the largest possible positive
 * number. In order to make the string appear right, I spend the first
 * iteration of the do/while loop detecting INT_MIN and adding '1' to the
 * character that results from the math. The string then outputs properly.
 */

void reverse(char s[]) {
	int c, i, j;

	for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

void itoa(int n, char s[]) {
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
	s[i] = '\0';
	reverse(s);
}

int main() {
	int tests[5] = {INT_MIN, INT_MAX, -300, 172, 38478235};
	char st[101] = "";
	int i;
	
	for (i = 0; i < 5; i++) {
		itoa(tests[i], st);
		printf("%12d in string form is %12s\n", tests[i], st);
	}
	return 0;
}
