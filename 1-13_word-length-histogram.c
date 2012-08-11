#include <stdio.h>
#define IN 1
#define OUT 0
#define MINWLENGTH 2
#define MAXWLENGTH 20

int main(void) {
	/* Rundown of variables:
	   c = current input char
	   state = inside or outside a word
	   ltrs = letter count
	   wrds = word count
	   lines = you should be shot if you don't know
	   lengths = an array that keeps track of how often words up to x chars long
	             occur.
	*/

	int c, state, ltrs, wrds, lines, wlen;
	int lengths[MAXWLENGTH];
	int i;
	for (i = 0; i <= MAXWLENGTH; ++i) {
		lengths[i] = 0;
	}

	ltrs = wrds = wlen = 0;
	lines = 1;
	state = OUT;
	// Capture input until it ends
	while ((c = getchar()) != EOF) {
		// If it's whitespace, we've exited a word
		if (c == '\n' || c == ' ' || c == '\t') {
			if (state == IN) {
				++wrds; // ...and should increase the count.
				state = OUT;
				/* Check to see if the word is eligible to be counted. */
				if (wlen <= MAXWLENGTH) {
					++lengths[wlen];
				}
				// Reset our word length now.
				wlen = 0;
			}
			/* If it's a new line, we're still out of a word but need to increment the
			   line count */
			if (c == '\n') {
				++lines;
			}
		} else {
			/* If nothing else, we know it's just a random character or a letter. */
			state = IN;
			++wlen;
		}
		/* Everything that's input counts as a letter. */
		++ltrs;
	}
	// This is ugly and I wish I knew a better way to do it.
	printf("\nWORD LENGTH FREQUENCY\n\n         5   10   15   20   25   30   35   40   45   50   55   60   65   70   75\n");
	int iter;
	iter = MINWLENGTH;
	while (iter <= MAXWLENGTH) {
		i = lengths[iter];
		if (i > 0) {
			printf("%2d | ", iter);
			while (i > 0) {
				printf("#");
				i = i-1;
			}
			printf("\n");
		}
		++iter;
	}
	printf("%d words, %d chars, %d lines.\n", wrds, ltrs, lines);
	return 0;
}
