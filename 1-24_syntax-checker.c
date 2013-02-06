#include <stdio.h>

/* The C Programming Language: 2nd Edition
 * Exercise 1-24:
 * "Write a program to check a C program for rudimentary syntax errors like
 * unbalanced parentheses, brackets, and braces. Don't forget about quotes, both
 * single and double, escape sequences, and comments. (This program is hard if
 * you do it in full generality.)"
 *
 * Proksima from Freenode's ##c helped me understand full generality where
 * Ixquick, Wikipedia, and StackOverflow all failed: a program that has full
 * generality handles all use cases. In this case, my program should report no
 * errors from a well formed C source file, and return correct errors for every
 * non-valid C source file.
 *
 * I can tackle this one the same way I tackled the previous exercise: with a
 * FSM. The trick is in catching the mismatched levels.
 */

/* Create our nestable counts. These keep track of each type of syntax
 * character. */
#define PARENS 0
#define BRACKETS 1
#define BRACES 2

/* Create our states, which tell the parser what's going on. INSQ, INDQ, and
 * INCM are much larger so it's easier to tell what's what. If I were better
 * versed in binary operations, this could use less RAM. I intend to revisit
 * this later on. */
#define OUT 0
#define INPR 1
#define INBK 2
#define INBC 3
#define INSQ 100
#define INDQ 1000
#define INCM 10000

char c;
int counts[3];
int state, i, linenr;

int main() {
	for (i = 0; i < 3; ++i) {
		counts[i] = 0;
	}

	state = OUT;
	linenr = 1;
	// Begin streaming!
	while ((c = getchar()) != EOF) {
		if (c == '\n') {
			linenr += 1;
			if (state >= INSQ) {
				break;
			}
		}
		if (c == '(') {
			counts[PARENS] += 1;
			state += INPR;
		}
		if (c == ')') {
			counts[PARENS] -= 1;
			state -= INPR;
			if (counts[PARENS] < 0) {
				break;
			}
		}
		if (c == '[') {
			counts[BRACKETS] += 1;
			state += INBK;
		}
		if (c == ']') {
			counts[BRACKETS] -= 1;
			state -= INBK;
			if (counts[BRACKETS] < 0) {
				break;
			}
		}
		if (c == '{') {
			counts[BRACES] += 1;
			state += INBC;
		}
		if (c == '}') {
			counts[BRACES] -= 1;
			state -= INBC;
			if (counts[BRACES] < 0) {
				break;
			}
		}
		if (c == '"' && state > INDQ) {
			state -= INDQ;
			if (state < 0) {
				break;
			}
		}
		if (c == '"' && state < INSQ) {
			state += INDQ;
			if (state >= (INDQ * 2)) {
				break;
			}
		}
		if (c == '\'' && state > INSQ && state < INDQ) {
			state -= INSQ;
			if (state < 0) {
				break;
			}
		}
		if (c == '\'' && state < INSQ) {
			state += INSQ;
			if (state >= (INSQ * 2)) {
				break;
			}
		}
	}

	if (state != 0) {
		printf("SYNTAX ERROR: ");
		
		if (state >= INSQ && state < INDQ) {
			printf("Unclosed single quote on line %d!\n", linenr);
			return 1;
		}
		if (counts[PARENS] > 0) {
			printf("Unclosed parenthesis on line %d!\n", linenr);
			return 1;
		}
		if (counts[PARENS] < 0) {
			printf("Too many close parentheses on line %d!\n", linenr);
			return 1;
		}
		if (counts[BRACKETS] > 0) {
			printf("Unclosed brackets on line %d!\n", linenr);
			return 1;
		}
		if (counts[BRACKETS] < 0) {
			printf("Too many close brackets on line %d!\n", linenr);
			return 1;
		}
		if (counts[BRACES] > 0) {
			printf("Unclosed braces on line %d!\n", linenr);
			return 1;
		}
		if (counts[BRACES] < 0) {
			printf("Too many close braces on line %d!\n", linenr);
			return 1;
		}
	}

	printf("All clean.\n");
	return 0;
}
