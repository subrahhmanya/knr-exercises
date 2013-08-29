#include <stdio.h>

/* The C Programming Language, 2nd Edition
 *
 * Exercise 5-3: Write a pointer version of the function strcat that we showed
 * in Chapter 2: strcat(s,t) copies the string t to the end of s.
 *
 * Answer: Pay careful attention to the passage before this exercise; there's
 * a difference between a character array and a pointer to a string constant.
 * The major difference is you can modify the contents of a character array.
 * String constants, like other constants, can't be modified. This practically
 * requires that the first argument to strcatp is a character array.
 *
 * When working with pointers, details seem to be of utmost importance.
 *
 * Thanks to Chris and dagle from Freenode's ##c for their input on
 * improving the code.
 */

#define ALLOC 80

void strcatp(char *s, char *t);

int main(void) {
	char foo[ALLOC] = "This is amazing!";
	char *bar = " Pointers for everyone!";
	strcatp(foo, bar);
	printf("%s\n", foo);
	return 0;
}

/* strcat: copy t into s; s must be large enough */
void strcatp(char *s, char *t) {
	while (*s != '\0') {
		s++;
	}
	/* Doing this without checking a buffer means it may screw up memory.
	 * It's the programmer's duty to ensure this doesn't happen, not the
	 * function's.
	 */
	while ((*s++ = *t++));
}
