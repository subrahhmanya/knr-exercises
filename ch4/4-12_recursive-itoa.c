#include <stdio.h>
#include <string.h>

/* The C Programming Language: 2nd Edition
 *
 * Exercise 4-12: Adapt the ideas of printd() to write a recursive version of
 * itoa; that is, convert an integer into a string by calling a recursive
 * routine.
 *
 * Answer: Making itoa() recursive isn't too much work; it helps knowing how to
 * use static variables; they make it possible to increment the position in the
 * string without using an external variable. Additionally, you'll need to
 * understand flow control to prevent the sub-routines from executing further
 * than needed. As a result, itoa() gets called multiple times, but if it
 * calls itself, it immediately returns so it won't venture further. This is
 * to make sure i is reset to zero only after the number is finished, so the
 * next call starts at the beginning of the string.
 *
 * Normally, recursive functions shouldn't worry about state, but it's necessary
 * in this version of itoa.
 */

void itoa(int, char[]);
void reverse(char[]);

int main(void) {
	char foo[40] = "";

	itoa(829048, foo);
	printf("%s\n", foo);
	itoa(-4021, foo);
	printf("%s\n", foo);

	return 0;
}

void itoa(int num, char target[]) {
	static int i = 0;
	static int neg = 0;

	if (num < 0) {
		neg = 1;
		num = -num;
	}

	if (num /= 10 > 0) {
		target[i++] = (num % 10) + '0';
		num /= 10;
		itoa(num, target);
		return;
	} else {
		if (neg == 1) {
			neg = 0;
			target[i++] = '-';
			target[i] = '\0';
		} else {
			target[i] = '\0';
		}
		reverse(target);
	}
	i = 0;
}

void reverse(char s[]) {
	int c, i, j;

	for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}
