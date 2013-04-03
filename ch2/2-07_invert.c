#include <stdio.h>

/* The C Programming Language: 2nd Edition
 *
 * Exercise 2-07: Write a function invert(x,p,n) that returns x with the n bits
 * that begin at position p inverted (i.e. 1 changed into 0 and vice-versa),
 * leaving the others unchanged.
 *
 * Answer: The trick is to start with ~0 to get all 1s, then left-shift n
 * times. After that, flip again to get n number of 1s. Next, left shift the
 * appropriate number of times needed to line up the mask of 1s to the proper
 * location. Apply that mask to x with XOR and bam, job done!
 *
 * Here's a step by step illustration of invert(205, 5, 4), assuming 16-bit
 * unsigned integers:
 *
 * 1111111111111111     ~0
 * 1111111111110000     << 4
 * 0000000000001111     ~
 * 0000000000011110     << (5 - 4 == 1)
 *
 * Mask created. Now let's take our original number...
 * 0000000011001101     205
 *            ####      ^ ...and apply the mask!
 * 0000000011010011     End Result (211)
 */

unsigned invert(unsigned x, unsigned p, unsigned n) {
	return x ^ ((~(~0 << n)) << (p - n));
}

int main() {
	printf("invert(205, 5, 4) returns %d\n", invert(205, 5, 4));
	printf("11001101 flips 110[0110]1 to produce...\n11010011\n");
	printf("invert(1876, 7, 3) returns %d\n", invert(1876, 7, 3));
	printf("11101010100 flips 1110[101]0100 to produce...\n11100100100\n");
	return 0;
}
