#include <stdio.h>

#define MINLENGTH 80

int main() {
	// longline is used as a boolean that tells us if it's a line worth printing
	int longline = 0;

	// len is simply a character counter, while c is the character itself.
	int len, c;
	char buffer[MINLENGTH];

	while ((c = getchar()) != EOF) {
		buffer[len] = c;

		/* When we meet the end of the line, we need to print the rest of the line,
		   but only if we're already in a long line. Otherwise, reset our state.
		 */
		if (c == '\n') {

			if (longline == 1 && len < MINLENGTH - 1) {
				buffer[len + 1] = '\0';
				printf("%-s", buffer);
			}

			len = 0;
			longline = 0;
			continue;
		}

		/* When the buffer has filled up, output its contents! */
		if (len == MINLENGTH) {
			buffer[len + 1] = '\0';
			printf("%-s", buffer);
			len = 0;
			longline = 1;
			continue;
		}

		/* If neither of the above cases are caught, increment our counter and fetch
		   more data.
		 */
		++len;
	}

	return 0;
}
