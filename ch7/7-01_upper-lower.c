#include <stdio.h>
#include <ctype.h>
#include <string.h>

/* The C Programming Language: 2nd Edition
 *
 * Exercise 7-1: Write a program that converts upper case to lower or lower
 * case to upper, depending on the name it is invoked with, as found in
 * `argv[0]`.
 *
 * Notes: This one is, strangely, very easy. The primary gotcha is in the
 * argv[0] check. The simplest solution I came up with was to check argv[0]
 * for *both* upper and lower. If for some reason they're both in the path,
 * the one that occurred later in the string takes precedence, since it's
 * most likely to be the name of the executable itself rather than the
 * directory containing the binary.
 *
 * Edge cases, gotta love'em.
 */

int main(int argc, char *argv[]) {
	char c;
	int lpos, upos;
	char *plow, *pupp;
	while ((c = getchar()) != EOF) {
		plow = strstr(argv[0], "lower");
		pupp = strstr(argv[0], "upper");
		if (plow != NULL) {
			lpos = (int) (plow - argv[0]);
		} else {
			lpos = -1;
		}
		if (pupp != NULL) {
			upos = (int) (pupp - argv[0]);
		} else {
			upos = -1;
		}
		if (isalpha(c)) {
			/* These two are only equal when neither are found in argv[0].
			 * The odds of this happening are slim, but still possible.
			 */
			if (lpos > upos) {
				c = tolower(c);
			}
			if (upos > lpos) {
				c = toupper(c);
			}
		}
		putchar(c);
	}
	return 0;
}
