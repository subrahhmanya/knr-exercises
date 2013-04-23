#include <stdio.h>

/* The C Programming Language: 2nd Edition
 *
 * Exercise 1-19: Write a function reverse(s) that reverses the character
 * string 's'. Use it to write a program that reverses its input a line at a
 * time.
 *
 * Answer: This is really just as simple as using get_line() and reverse() in
 * tandem. I guess the point of this exercise is to teach the reader how to
 * combine the use of functions to get more complex behavior out of a program.
 *
 * My version includes the size of the string in the argument list instead of
 * duplicating effort that get_line() does, since it already puts the contents
 * into a string and returns the length of the string for me. For strict
 * passing of this exercise, reverse() should really only have one argument
 * and it should count the size of the string before it works with it. But
 * that's prone to issues, such as a string that hasn't been terminated
 * properly.
 */

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
