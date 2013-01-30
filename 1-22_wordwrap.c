#include <stdio.h>

/* The C Programming Language: 2nd Edition
 * Exercise 1-22:
 * "Write a program to 'fold' long input lines into two or more shorter lines
 * after the last non-blank character that occurs before the n-th column of
 * input. Make sure your program does something intelligent with very long
 * lines, and if there are no blanks or tabs before the specified column."
 *
 * So... Quite a hefty requirement. In a nutshell, our goal is to create sane
 * hard-wrapping. This is a common function in text editors, and it's
 * important to get it right or the results are wonky.
 *
 *
 * TODO: get_line() is not fully correct. When it hits a \t, it counts it as
 * one character and has no concept of display count. I'll fix this later on.
 */

// For tradition's sake, let's wrap at 80 columns
#define MAXLEN 80

char data[MAXLEN];
int i, j, k;

int get_line(char s[], int lim) {
	/* Put as much as possible into a temp string, and count its length */
	int c, i;

	for (i = 0; i < lim && (c = getchar()) != EOF && c != '\n'; ++i) {
		s[i] = c;
	}
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}

/* Find the first blank character, starting from the end of the string. Returns
 * the position of the blank, or -1 if one wasn't found.
 */
int b_find_blank(char s[], int lim) {
	// Start at the end of the string and go backwards.
	for (i = lim; i >= 0; i--) {
		// Simply replace the first blank with a newline.
		if (s[i] == ' ' || s[i] == '\t') {
			return i;
		}
	}
	return -1;
}

int main() {
	while (j = get_line(data, MAXLEN)) {
		if (j == 80) {
			// We know it's a long line now. Let's make sure we're breaking in
			// the right place
			k = b_find_blank(data, MAXLEN);
			//printf("%d\n", k);
			if (k > -1) {
				data[k] = '\n';
				data[MAXLEN] = '\0';
				printf("%s", data);
				continue;
			} else {
				data[MAXLEN] = '\0';
				printf("%s\n", data);
				continue;
			}
		}
		printf("%s", data);
	}

}
