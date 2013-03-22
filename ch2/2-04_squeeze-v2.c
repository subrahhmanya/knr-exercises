#include <stdio.h>

/* The C Programming Language: 2nd Edition
 *
 * Exercise 2-4: Write an alternate version of squeeze(s1, s2) that deletes
 * each character in s1 that matches any character in the string s2.
 *
 * Answer: This one is fairly easy, considering the fun trick that's covered
 * in the passage before this exercise with the unary operators ++ and --. C's
 * interesting behavior with these operators allows the programmer to write
 * shorter, faster logic.
 *
 * That said, I couldn't find a way to iterate through s2[] and s1[] in a
 * single loop, and I needed to use a flag. There may be a more clever way to
 * solve this.
 *
 */

// It'd be better to make this return a pointer (or string), but the book
// hasn't covered it yet!
void squeeze(char s1[], char s2[]) {
	int i, j, k, match;

	for (i = j = 0; s1[i] != '\0'; i++) {
		// I don't see a way to do this without a flag
		match = 0;
		for (k = 0; s2[k] != '\0'; k++) {
			if (s1[i] == s2[k]) {
				match = 1;
				break;
			}
		}
		// check our flag. if there wasn't a match, j needs to match i's value
		if (!match) {
			s1[j++] = s1[i];
		}
	}

	s1[j] = '\0';
}

int main() {
	char foo[16] = "foobarbaz";
	char bar[16] = "boz";

	squeeze(foo, bar);

	printf("%s\n", foo); // Should read "fara"

	return 0;
}
