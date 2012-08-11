#include <stdio.h>

#define MAXLENGTH 100

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

void copy(char from[], char to[]) {
	int i = 0;

	while ((to[i] = from[i]) != '\0') {
		++i;
	}
}

int main() {
	int len, max;

	char line[MAXLENGTH];
	char longest[MAXLENGTH];

	max = 0;
	while ((len = get_line(line, MAXLENGTH)) > 0) {
		if (len > max) {
			max = len;
			copy(line, longest);
		}
	}

	printf("\nThe longest line is %3d characters long.\n", max);
	printf("----------------------------------------\n");
	if (max > 0) {
		printf("%-s", longest);
		if (max == MAXLENGTH && longest[max - 1] != '\n') {
			printf("\n");
		}
	}

	return 0;
}
