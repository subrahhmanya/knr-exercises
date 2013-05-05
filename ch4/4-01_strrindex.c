#include <stdio.h>
#include <string.h>

/* The C Programming Language: 2nd Edition
 *
 * Exercise 4-1: Write the function strrindex(s, t), which returns the position
 * of the /rightmost/ occurrence of 't' in 's', or -1 if there is none.
 *
 * Answer: The directions are unclear. Is it asking for the rightmost index of
 * the first result from the beginning of the string, or the first index of the
 * first occurrence from the end of the string? I will assume the leftmost
 * index of the first occurrence from the end of the string, since it seems
 * more difficult and relevant.
 *
 * This exercise was made simpler by remembering the work we did in Chapter 3.
 * Specifically, itoa2. We made a reverse(s) function which reverses strings.
 * If we reverse our two strings, we can pass them to strindex(), do a little
 * math, and get the rightmost equivalent, all without copying and modifying
 * another function! This strengthens the concept of writing functions that
 * don't need to be fully understood in order to use or expand on their
 * functionality.
 *
 * In this instance, I reversed strindex's behavior without needing to know
 * anything beyond the concept of what strings are.
 *
 * (For the record I understand how strindex works :P)
 */

#define MAXLINE 1000

void reverse(char s[]) {
	int c, i, j;

	for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

int strindex(char s[], char t[]) {
	int i, j, k;

	for (i = 0; s[i] != '\0'; i++) {
		for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++) {
		}
		if (k > 0 && t[k] == '\0') {
			return i;
		}
	}
	return -1;
}

int strrindex(char s[], char t[]) {
	/* Instead of starting at the end and going back, let's be super lazy
	 * and just reverse it, call our buddy strindex, and reverse the
	 * strings again.
	 */
	reverse(s);
	reverse(t);
	/* We add strlen(t) to point to the first index of t when it's
	 * reversed again */
	int o = strindex(s, t) + strlen(t);
	reverse(s);
	reverse(t);

	// Be sure to return the correct offset with some math :3
	return (strlen(s) - o);
}

int main() {
	char haystack[MAXLINE] = "charred and burned, ouch! My stomach churned... I hope I'll be okay!";
	char needle[MAXLINE] = "ned";
	int pos = strrindex(haystack, needle);
	int i = 0;

	/* This is mostly just to provide a handy visual aid */
	printf("The phrase %s's rightmost occurrence is %d:\n", needle, pos);
	printf("%s\n", haystack);
	for (i = 0; i < pos; i++) {
		putchar(' ');
	}
	for (i = 0; i < strlen(needle); i++) {
		putchar('^');
	}
	printf("\n");
}
