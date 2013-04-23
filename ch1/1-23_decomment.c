#include <stdio.h>

/* The C Programming Language: 2nd Edition
 *
 * Exercise 1-23: Write a program to remove all comments from a C program.
 * Don't forget to handle quoted strings and character constants properly. C
 * comments do not nest.
 *
 * Answer: At first I didn't know why it was important to account for strings
 * or character constants. The reason behind this is that /* and // are valid
 * inside those parts of C, so they deserve special treatment.
 *
 * The states for this program are IN_MULTI for a multi-line comment,
 * IN_SINGLE for a single line comment, OUT for being outside a comment, and
 * IN_STRING for being inside a string or character constant. These four states
 * are all I need to determine whether I should output the contents of the C
 * file or not. Characters are only output when the state is OUT or IN_STRING,
 * and there are conditions for getting into and out of comment state.
 *
 * This structure is known as a finite state machine (FSM).
 */

#define OUT       0
#define IN_MULTI  1
#define IN_SINGLE 2
#define IN_STRING 3

char c, p;
int status;

int main() {
	// Treat input like a stream, since that's all the K&R has explained so far.
	while ((c = getchar()) != EOF) {
		/* This is to account for strings and character constants */
		if (c == '\'' || c == '"') {
			if (status == OUT) {
				status = IN_STRING;
			} else if (status == IN_STRING) {
				status = OUT;
			}
		}
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
		if (status == OUT || status == IN_STRING) {
			putchar(c);
		}

	}

	/* derpsauce
	 *
	 *
	 * Testing comment for the lulz. lolololol
	 */
}
