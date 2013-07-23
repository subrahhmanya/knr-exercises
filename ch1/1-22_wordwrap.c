#include <stdio.h>

/* The C Programming Language: 2nd Edition
 *
 * Exercise 1-22: Write a program to 'fold' long input lines into two or more
 * shorter lines after the last non-blank character that occurs before the n-th
 * column of input. Make sure your program does something intelligent with very
 * long lines, and if there are no blanks or tabs before the specified column.
 *
 * Answer: So... Quite a hefty requirement. In a nutshell, our goal is to
 * create line-wrapping. The simplest approach is to take every character until
 * EOF, like a stream. Spaces and tabs need special treatment. If your input
 * isn't a newline or a blank, it will just be printed. Spaces and tabs only
 * print if the next non-blank is before the end of the line length limit. To
 * make things prettier, I opted to ignore leading whitespace as well.
 *
 */

#define LINEWIDTH 20

int main() {
	int c, tmp, ts;
	int spaces = 0;
	int col = 0;

	printf("Just type. It'll wrap to %d characters per line.\n", LINEWIDTH);
	while ((c = getchar()) != EOF) {
		if (col >= LINEWIDTH) {
			putchar('\n');
			col = 0;
		}
		if (c == ' ') {
			if (col == 0) {
				continue;
			}
			spaces = 1;
			while ((tmp = getchar()) == ' ') {
				spaces++;
			}
			if (col + spaces < LINEWIDTH) {
				while (spaces > 0) {
					putchar(' ');
					col++;
					spaces--;
				}
			} else {
				putchar('\n');
				col = 0;
			}
			putchar(tmp);
			col++;
			continue;
		}
		/* There's some duplicated effort in here, but I couldn't find a cleaner
		 * way to put tab stuff in with the spaces, where it belongs */
		if (c == '\t') {
			if (col == 0) {
				continue;
			}
			spaces = 1;
			while ((tmp = getchar()) == '\t') {
				spaces++;
			}
			ts = (spaces * 8) - (col % 8);
			if (col + ts < LINEWIDTH) {
				spaces = (spaces * 8) - (col % 8);
				while (spaces > 0) {
					putchar(' ');
					spaces--;
					col++;
				}
			} else {
				putchar('\n');
				col = 0;
			}
			putchar(tmp);
			col++;
			continue;
		}
		putchar(c);
		col++;
		if (c == '\n') {
			col = 0;
		}
	}
	return 0;
}
