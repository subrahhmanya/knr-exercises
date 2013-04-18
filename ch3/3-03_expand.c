#include <stdio.h>
#include <ctype.h>

/* The C Programming Language: 2nd Edition
 *
 * Exercise 3-3: Write a function expand(s1,s2) that expands shorthand
 * notations like 'a-z' in the string s1 into the equivalent complete list
 * 'abc...xyz' in s2. Allow for letters of either case and digits, and be
 * prepared to handle cases like 'a-b-c' and 'a-z0-9' and '-a-z'. Arrange that
 * a leading or trailing '-' is taken literally.
 *
 * Answer: This one was fun. The trick is to target dashes, since they have the
 * special behavior. From there, you decide what to do based on context. Once
 * you've determined that the characters on both sides of the dash are letters
 * OR numbers - no mixing - you store both values and put'em through a loop to
 * output the range. There are a few edge cases to watch out for, but it's
 * pretty simple to account for them.
 *
 * A limitation of my expand() is leading and trailing dashes are only output
 * once. You can lead or trail with > 1 dash and it will truncate it to only 1.
 * This could be seen as a bug or a feature. I haven't decided.
 */

void expand(char s1[], char s2[]) {
	int i, j;
	char start = 0;
	char end = 0;
	for (i = 0, j = 0; s1[i] != '\0'; i++) {
		if (s1[i] == '-') {
			if ((isalpha(s1[i - 1]) && isalpha(s1[i + 1])) || (isdigit(s1[i - 1]) && isdigit(s1[i + 1]))) {
				start = s1[i - 1];
				end = s1[i + 1];
				start = tolower(start);
				end = tolower(end);
				if (start == s2[j - 1]) {
					start++;
				}
				while (start <= end) {
					s2[j++] = start++;
				}
			} else {
				if (i == 0 || s1[i + 1] == '\0') {
					s2[j++] = '-';
				}
			}
		}
	}
	s2[j] = '\0';
}

int main() {
	char foo[21] = "A-Z";
	char bar[21] = "0-9";
	char baz[21] = "A-g-N";
	char fob[21] = "2-5-9";
	char woot[21] = "-a-f0-36-9b-h-";
	char derp[21] = "a-28-t";
	char dest[61] = "";

	printf("%26s\n", "INPUT |  OUTPUT");
	printf("%27s\n", "-----------------");

	expand(foo, dest);
	printf("%16s => %s\n", foo, dest);

	expand(bar, dest);
	printf("%16s => %s\n", bar, dest);

	expand(baz, dest);
	printf("%16s => %s\n", baz, dest);

	expand(fob, dest);
	printf("%16s => %s\n", fob, dest);

	expand(woot, dest);
	printf("%16s => %s\n", woot, dest);

	expand(derp, dest);
	printf("%16s => %s\n", derp, dest);

	return 0;
}
