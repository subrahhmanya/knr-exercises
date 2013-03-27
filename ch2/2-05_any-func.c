#include <stdio.h>

/* The C Programming Language: 2nd Edition
 *
 * Exercise 2-5: Write the function any(s1,s2), which returns the first
 * location of the string s1 where any character from the string s2 occurs, or
 * -1 if s1 contains no characters from s2. (The standard library function
 *  strpbrk does the same job but returns a pointer to the location.)
 *
 * Answer: Similarly to squeeze(), any() uses two loops to do its job, but
 * instead of changing the string, we're just returning the index of the first
 * character found. If it's not found, it'll return a negative number. This
 * is a common practice in functions that return integers since it gives
 * programmers an easy case to check for: if any() returns anything less than
 * zero, the characters in s2 weren't found.
 *
 */

int any(char s1[], char s2[]) {
	int i, j;
	for (i = j = 0; s1[i] != '\0'; ++i) {
		while (s2[j++] != '\0') {
			if (s1[i] == s2[j]) {
				return i;
			}
		}
		j = 0;
	}
	return -1;
}

int main() {
	char foo[80] = "argle bargle";
	char bar[80] = "toobz";
	int result;

	if ((result = any(foo, bar)) != -1) {
		printf("Found a match at position %d!\n", result);
	} else {
		printf("No match found.\n");
	}
	// Should return a match at index 6.
	return 0;
}
