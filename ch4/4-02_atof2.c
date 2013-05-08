#include <stdio.h>
#include <ctype.h>

/* The C Programming Language: 2nd Edition
 *
 * Exercise 4-2: Extend atof to handle scientific notation of the form
 *
 * 123.45e-6
 *
 * where a floating-point number may be followed by 'e' or 'E' and an
 * optionally signed exponent.
 *
 * Answer: It's relatively simple to extend atof. You need a variable to count
 * the number of places the decimal needs to be moved, and in which direction.
 * With a little clever manipulation of the `power` variable, you don't even
 * need to touch the math that's used just before atof() returns. :)
 */

double atof(char s[]) {
	double val, power;
	int i, sign, esign, exp;

	/* Skip whitespace */
	for (i = 0; isspace(s[i]); i++) {
	}

	sign = (s[i] == '-') ? -1 : 1;

	if (s[i] == '+' || s[i] == '-') {
		i++;
	}
	for (val = 0.0; isdigit(s[i]); i++) {
		val = 10.0 * val + (s[i] - '0');
	}
	if (s[i] == '.') {
		i++;
	}
	for (power = 1.0; isdigit(s[i]); i++) {
		val = 10.0 * val + (s[i] - '0');
		power *= 10.0;
	}
	/* Start the exponent checking... */
	if (s[i] == 'e' || s[i] == 'E') {
		i++;
		esign = (s[i] == '-') ? 1 : 0;
		if (s[i] == '+' || s[i] == '-') {
			i++;
		}
		/* This allows us to count how many times we need to mess with
		 * the power variable */
		exp = 0;
		while (isdigit(s[i])) {
			exp *= 10;
			exp += (s[i] - '0');
			i++;
		}
		/* And do our business, which is a bit tricky */
		while (exp > 0) {
			/* Because `power` is being divided with later, we need to reverse
			 * operands to ensure it shrinks and expands as needed. */
			if (esign == 1) {
				// A negative exponent means we need to divide by more
				power *= 10.0;
			} else {
				// And a positive exponent means we need to divide by less
				power /= 10.0;
			}
			exp--;
		}
	}
	/* The math stays the same */
	return sign * val / power;
}

int main(void) {
	// Declare the function so there's no confusion over what it returns.
	double atof(char s[]);
	/* Should print "0.0000012345678900" */
	printf("%20.16f\n", atof("   123.456789e-8     "));
	return 0;
}
