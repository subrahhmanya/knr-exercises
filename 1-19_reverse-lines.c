#include <stdio.h>

#define MAXLINELENGTH 9001

int get_line(char s[], int limit) {
	int c, i;

	for (i = 0; i < limit && (c = getchar()) != EOF && c != '\n'; ++i) {
		s[i] = c;
	}

	s[i] = '\0';

	/* If I don't include this check, I can't handle blank lines */
	if (c == EOF && i == 0) {
		return -1;
	} else {
		return i;
	}

}

/* Directly reverse a line's contents. */
void reverse(char input[], int size) {
	int tmp;
	int i = 0;
	size--;

	/* If len and i are the same, then there's no reason to proceed */
	while (size > i) {
		// Store the first character in a temporary spot...
		tmp = input[i];

		// ... and swap!
		input[i] = input[size];
		input[size] = tmp;

		// Bring our numbers closer together
		++i;
		--size;
	}
}

int main(void) {
	// An int and a string to store each line's data in
	int line_len;
	char buffer[MAXLINELENGTH];

	while ((line_len = get_line(buffer, MAXLINELENGTH)) != -1) {
		reverse(buffer, line_len);
		printf("%s\n", buffer);
	}
	return 0;
}
