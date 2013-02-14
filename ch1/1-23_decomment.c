#include <stdio.h>

/* The C Programming Language: 2nd Edition
 * Exercise 1-23:
 * "Write a program to remove all comments from a C program. Don't forget to
 * handle quoted strings and character constants properly. C comments do not
 * nest."
 *
 * I'm not sure why the instructions tell the reader to account for quoted
 * strings and character constants. Comments always begin with either // or
 * /*, so that sets the boundary of state.
 *
 * The states for this program are IN_MULTI for a multi-line comment,
 * IN_SINGLE for a single line comment, and OUT for being outside a comment.
 * These three states are all I need to determine whether I should output the
 * contents of the C file or not. Characters are only output when the state is
 * OUT, and there are conditions for getting into and out of comment state.
 *
 * I don't know of any other way to do this without invoking some higher-level
 * libraries.
 */

#define IN_MULTI  1
#define IN_SINGLE 2
#define OUT       0

char c, p;
int status;

int main() {
	// Treat input like a stream, since that's all the K&R has explained so far.
	while ((c = getchar()) != EOF) {

		// Check for the ways to open a comment, and set state accordingly
		if (c == '/' && status == OUT) {
			// Look ahead and store the character that's returned
			p = getchar();

			if (p == '*') {
				status = IN_MULTI;
			} else if (p == '/') {
				status = IN_SINGLE;
			} else {
				putchar(c);
				putchar(p);
				continue;
			}
		}
		
		// Ignore everything in a single line comment until a newline
		if (status == IN_SINGLE) {

			if (c == '\n') {
				putchar(c);
				status = OUT;
				continue;
			}

		}

		// Ignore everything until you reach the end of a multi comment
		if (status == IN_MULTI && c == '*') {
			p = getchar();

			if (p == '/') {
				status = OUT;
				continue;
			}

		}

		// Output everything when we're not in a comment!
		if (status == OUT) {
			putchar(c);
		}

	}

	/* derpsauce
	 *
	 *
	 * Testing comment for the lulz. lolololol
	 */
}
