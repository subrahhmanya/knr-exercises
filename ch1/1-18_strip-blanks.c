#include <stdio.h>

#define MAXLINELENGTH 9001
/* Write a program to remove trailing blanks and tabs from each line of input,
   and to delete entirely blank lines. */

int get_line(char s[], int lim) {
	int c, i;

	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
		s[i] = c;
	}
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i + 1] = '\0';
	return i;
}

int main(void) {
	char buffer[MAXLINELENGTH];
	int c, i, len;

	/* Make sure every line is gone over */
	while (len = get_line(buffer, MAXLINELENGTH)) {
		/* An empty for statement, simply to change the i variable. */
		for (i = len - 2; (i > 0) && (buffer[i] == ' ') || (buffer[i] == '\t'); --i);

		/* We've reached the end of the line's actual content. Terminate the line. */
		if (i >= 1) {
			buffer[i + 1] = '\n';
			buffer[i + 2] = '\0';
			printf("%s", buffer);
		}
	}
}

