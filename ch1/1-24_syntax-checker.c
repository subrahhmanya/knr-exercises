#include <stdio.h>

/* The C Programming Language: 2nd Edition
 *
 * Exercise 1-24: Write a program to check a C program for rudimentary syntax
 * errors like unbalanced parentheses, brackets, and braces. Don't forget about
 * quotes, both single and double, escape sequences, and comments. (This
 * program is hard if you do it in full generality.)
 *
 * Answer: Proksima from Freenode's ##c helped me understand full generality
 * where Ixquick, Wikipedia, and StackOverflow all failed: a program that has
 * full generality handles all use cases. In this case, my program should
 * report no errors from a well formed C source file, and return correct errors
 * for every non-valid C source file.
 *
 * I can tackle this one the same way I tackled the previous exercise: with a
 * FSM. The trick is in catching the mismatched levels. This happens when,
 * after the source has been combed, there are values that aren't equal to
 * zero. Anything that's non-zero means there are too many or too few of a
 * specific syntax construct.
 *
 * Post-solution note: switch() would've made this MUCH shorter... but it's not
 * covered until chapter 3. I think part of the purpose of this exercise is to
 * teach the value of the switch structure later on. :)
 */

char c;

/* Set the state/count variables */
int linenr, parens, brackets, braces, singqs, dubqs, escapes, mcomms, scomms = 0;

int main() {
	linenr = 1;
	// Begin streaming!
	while ((c = getchar()) != EOF) {
		if (scomms == 1) {
			if (c == '\n') {
				scomms--;
			} else {
				continue;
			}
		} else if (mcomms == 1) {
			if (c == '*') {
				if (getchar() == '/') {
					mcomms--;
				}
			}
		} else {
			// Check for escape sequences
			if (c == '\\') {
				escapes++;
				c = getchar();
				// This does not detect all sequences; just the ones covered in Chapter 1.
				if (c != '\\' && c != 't' && c != '\'' && c != '"' && c != 'n' && c != 'b' && c != '0') {
					break;
				} else {
					escapes--;
				}
			}
			// Newline behavior
			if (c == '\n') {
				if (singqs > 0 || dubqs > 0) {
					break;
				}
				linenr++;
			}
			// Parentheses
			if (c == '(') {
				parens++;
			}
			if (c == ')') {
				parens -= 1;
				if (parens < 0) {
					break;
				}
			}
			// Brackets
			if (c == '[') {
				brackets++;
			}
			if (c == ']') {
				brackets--;
				if (brackets < 0) {
					break;
				}
			}
			// Braces
			if (c == '{') {
				braces++;
			}
			if (c == '}') {
				braces--;
				if (braces < 0) {
					break;
				}
			}
			// Double quotes
			if (c == '"') {
				if (dubqs == 0) {
					dubqs++;
				} else {
					dubqs--;
				}
			}
			// Single quotes, which are only checked outside of doubles.
			if (c == '\'' && dubqs == 0) {
				if (singqs == 0) {
					singqs++;
				} else {
					singqs--;
				}
			}
			// Comment detection
			if (c == '/') {
				if (getchar() == '*') {
					mcomms++;
				}
				if (getchar() == '/') {
					scomms++;
				}
			}
		}
	}

	if (escapes > 0) {
		printf("Invalid escape sequence on line %d!\n", linenr);
		return 1;
	}
	if (singqs > 0) {
		printf("Unclosed single quote on line %d!\n", linenr);
		return 1;
	}
	if (dubqs > 0) {
		printf("Unclosed double quote on line %d!\n", linenr);
		return 1;
	}
	if (brackets > 0) {
		printf("Unclosed brackets on line %d!\n", linenr);
		return 1;
	}
	if (brackets < 0) {
		printf("Too many close brackets on line %d!\n", linenr);
		return 1;
	}
	if (parens > 0) {
		printf("Unclosed parenthesis on line %d!\n", linenr);
		return 1;
	}
	if (parens < 0) {
		printf("Too many close parentheses on line %d!\n", linenr);
		return 1;
	}
	if (braces > 0) {
		printf("Unclosed braces on line %d!\n", linenr);
		return 1;
	}
	if (braces < 0) {
		printf("Too many close braces on line %d!\n", linenr);
		return 1;
	}
	if (mcomms == 1) {
		printf("Unclosed comment at end of file!\n");
		return 1;
	}

	printf("All clean.\n");
	return 0;
}
