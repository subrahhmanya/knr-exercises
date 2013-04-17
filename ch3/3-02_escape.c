#include <stdio.h>

/* The C Programming Language: 2nd Edition
 *
 * Exercise 3-2: Write a function escape(s,t) that converts characters like
 * newline and tab into visible escape sequences like \n and \t as it copies
 * the string t to s. Use a switch. Write a function for the other direction
 * as well, converting escape sequences into the real characters.
 *
 * Answer: Fun! Switches can be used as shorthand if-else chains.
 */

#define STRMAX 80

void escape(char s[], char t[]) {
	// i for t, j for s
	int i, j;
	j = 0;
	for (i = 0; t[i] != '\0'; i++) {
		switch(t[i]) {
			case '\n':
				s[j++] = '\\';
				s[j++] = 'n';
				break;
			case '\t':
				s[j++] = '\\';
				s[j++] = 't';
				break;
			default:
				s[j++] = t[i];
				break;
		}
	}
	s[j] = '\0';
}

void unescape(char s[], char t[]) {
	// i for t, j for s
	int i, j;
	j = 0;
	for (i = 0; t[i] != '\0'; i++) {
		if (t[i] == '\\') {
			switch (t[i + 1]) {
				case 'n':
					s[j++] = '\n';
					break;
				case 't':
					s[j++] = '\t';
					break;
			}
		} else {
			s[j++] = t[i];
		}
	}
	s[j] = '\0';
}

int main() {
	char src[STRMAX] = "foo\nbar\t\tbaz\nnozzle";
	char dest[STRMAX] = "";
	/* Let's escape it... */
	escape(dest, src);
	printf("%s\n", dest);
	/* ...and unescape it! */
	unescape(dest, src);
	printf("%s\n", dest);
	return 0;
}
