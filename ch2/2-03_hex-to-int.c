#include <stdio.h>
#include <ctype.h>

/* The C Programming Language, 2nd Edition
 *
 * Exercise 2-3: Write the function htoi(s), which converts a string of
 * hexadecimal digits (including an optional 0x or 0X) into its equivalent
 * integer value. The allowable digits are 0 through 9, a through f, and A
 * through F.
 *
 * Answer: ctype.h has some cool functions in it. Using just two functions from
 * that header, my function's length is much shorter than it would be if I
 * were to wing it alone with C primitives.
 *
 * Anyway, the idea is to make sure you're working with a hex digit,
 * homogenize the case of the letters, and ignore x's. Since hex is base-16
 * instead of base-10, plug a 16 in and perform some clever math based on
 * ASCII knowledge.
 *
 * Since the function can be objectively proven correct, I included test cases
 * to ensure that its output is correct.
 *
 * `man ascii` for more info, if you're using an OS that's actually useful.
 */

int htoi(char s[]) {
	int i, val;

	for (i = val = 0; isxdigit(s[i]) || toupper(s[i]) == 'X'; ++i) {
		if (toupper(s[i]) == 'X') {
			continue;
		}
		if (s[i] > '9') {
			val = 16 * val + (toupper(s[i]) - '7');
			// The 7 is because 'A' is 7 higher than '9' in ASCII and thus only needs
			// to be knocked down by that much to fall in line with the normal integer
			// conversion
		} else {
			val = 16 * val + (s[i] - '0');
		}
	}
	return val;
}

int main() {
	printf(" HEX | DECIMAL\n---------------\n   1 = %3d\n 0xf = %3d\n0X64 = %3d\n  fF = %3d\n 093 = %3d\n", htoi("1"), htoi("0xf"), htoi("0X64"), htoi("fF"), htoi("093"));
	return 0;
}
