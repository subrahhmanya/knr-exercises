#include <stdio.h>

/* The C Programming Language: 2nd Edition
 *
 * Exercise 1-20: Write a program `detab` that replaces tabs in the input with
 * the proper number of blanks to space to the next tabstop. Assume a fixed set
 * of tabstops, say every 'n' columns. Should 'n' be a variable or a symbolic
 * parameter?
 *
 * Answer: 'n' should be a symbolic parameter. It's more apparent what's being
 * worked with and it's not susceptible to scope. Though, in this simple
 * program it really doesn't matter.
 *
 * The "correct" solution uses the isprint() stdlib function, but it's not
 * covered by this point in the book, so I did not use it.
 */

#define TABWIDTH 8

int main(void) {
	int column, c;
	column = 0;
	while ((c = getchar()) != EOF) {
		// Be sure that the character is a tab
		if (c == '\t') {
			/*
			 * Divide a line by TABWIDTH and you have your tabstops. If you
			 * modulo by TABWIDTH and it equals 0, you've reached a tabstop and
			 * don't need to output more spaces!
			 */
			while (column % TABWIDTH != 0 && column != 0) {
				putchar(' ');
				++column;
			}
		} else {
			if (c == '\n') {
				// Line-endings should reset the column counter after being output.
				putchar(c);
				column = 0;
			} else {
				// Now we can just output and increase column!
				putchar(c);
				++column;
			}
		}
	}
	return 0;
}
