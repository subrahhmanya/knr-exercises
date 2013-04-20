#include <stdio.h>
#include <string.h>
#include <limits.h>

/* The C Programming Language: 2nd Edition
 *
 * Exercise 3-5: Write the function itob(n,s,b) that converts the integer n
 * into a base b character representation in the string s. In particular,
 * itob(n,s,16) formats n as a hexadecimal integer in s.
 *
 * Answer: Retool the itoa() function written for 3-4 to take an additional
 * argument, then add a few more checks and account for ASCII's 7-character
 * distance between '9' and 'A', which makes bases higher than 16 function
 * without a large switch statement.
 */

void reverse(char s[]) {
	int c, i, j;

	for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

void itob(int n, char s[], unsigned b) {
	int i, sign, min, rem; // Add 'min' for later use

	if ((sign = n) < 0) {
		/* Detect this and add one so it can properly be made positive */
		if (n == INT_MIN) {
			n += 1;
			min = 1;
		}
		n = -n;
	}
	i = 0;
	if (b > 1) {
		do {
			/* If it's the first iteration of the loop and we've established
			 * that n == INT_MIN, we need to add one to the resulting string for it
			 * to be displayed properly. */
			rem = n % b;
			if (rem > 9) {
				rem += 7;
			}
			if (i == 0 && min == 1) {
				s[i++] = rem + '1';
			} else {
				s[i++] = rem + '0';
			}
		} while ((n /= b) > 0);
		/* This is annoying, but to make hex numbers right, you have to account
		 * for the +1 added to the final number causing bit flipping */
		if (min == 1) {
			for (i = 0; s[i] != '\0'; i++) {
				if (s[i] == '-') {
					continue;
				}
				if (i != 0 && s[i - 1] == '0' + (b + 7)) {
					s[i] += 1;
					s[i - 1] = '0';
				}
			}
		}
	}
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
		itob(tests[i], st, 16);
		printf("%12d in string form is %12s\n", tests[i], st);
	}
	return 0;
}
