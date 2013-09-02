#include <stdio.h>
#include <string.h>

/* The C Programming Language: 2nd Edition
 *
 * Exercise 5-4: Write the function strend(s,t), which returns 1 if the string
 * t occurs at the end of the string s, and zero otherwise.
 *
 * Answer: Check from the end of the string!
 */

int strend(char *, char *);

int main() {
	char *foo = "kekt";
	char *bar = "buckets of kekt";
	printf("%d\n", strend(bar, foo)); // should output 1
	foo = "missile";
	bar = "Did you see those missiles?!";
	printf("%d\n", strend(bar, foo)); // should output 0
	return 0;
}

int strend(char *s, char *t) {
	// Go to the end of s
	while (*s != '\0') {
		s++;
	}
	// back up s by however long t is
	s -= strlen(t);
	// Check to be sure the rest of the string matches
	for (; *s == *t && *s != '\0' && *t != '\0'; s++, t++);
	if (*s == '\0' && *t == '\0') {
		return 1;
	}
	return 0;
}
