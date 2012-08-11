#include <stdio.h>
int main(void) {
	/* Rundown of variables:
	   c = current input char
	   ltrs = letter count
	   chars = string containing the characters the program will count
	   lengths = the counts for each character
	*/

	int c;
	int i = 0;
	char chars[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

	/* cnum is the number of characters found in the above string */
	int cnum = 0;
	while (chars[i] != '\0') {
		cnum += 1;
		++i;
	}

	/* This array need its members to be initialized to zero. */
	int lengths[cnum];
	for (i = 0; i <= cnum; ++i) {
		lengths[i] = 0;
	}

	// Capture input until it ends
	while ((c = getchar()) != EOF) {
		for (i = 0; i < cnum; ++i) {
			if (c == chars[i]) {
				lengths[i] += 1;
			}
		}
	}
	// This is ugly and I wish I knew a better way to do it.
	printf("\nCHARACTER FREQUENCY\n\n         5   10   15   20   25   30   35   40   45   50   55   60   65   70   75\n");
	int iter = 0;
	while (iter <= cnum) {
		i = lengths[iter];
		if (i > 0) {
			printf("%2c | ", chars[iter]);
			while (i > 0) {
				printf("#");
				i -= 1;
			}
			printf("\n");
		}
		++iter;
	}
	return 0;
}
