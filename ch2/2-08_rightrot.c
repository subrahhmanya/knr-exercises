#include <stdio.h>

/* The C Programming Language: 2nd Edition
 *
 * Exercise 2-8: Write a function rightrot(x,n) that returns the value of the
 * integer x rotated to the right by n bit positions.
 *
 * Answer: The problem is a little ambiguous. If we're just moving the bits to
 * the right n times, then the solution is a while loop combined with >>, which
 * I think is much too easy. So I'm going with what I think it is: wrapping the
 * bits around when they've reached the rightmost bit. It's more interesting
 * and a _bit_ more difficult. Oh I kill me sometimes, ha.
 *
 * The trick is to determine whether masking the rightmost bit off changes the
 * number that x is. If it does, then it's clear that the leftmost bit needs
 * to be 1, but only after we've right-shifted x to accomodate. This requires
 * a local mask variable.
 *
 * Due to the way shifting works, I have to establish the mask as ~0 first.
 * Further bit manipulation must be done in a second statement, I assume
 * because the ~ operator changes the bits that are filled in when you shift,
 * too. This screws with our manipulation, so either my solution is
 * suboptimal or it's just a side effect of the arithmetic.
 */

unsigned rightrot(unsigned x, unsigned n) {
	unsigned mask = ~0;
	/* For some reason, I can't assign this value all at once.
	 * I have to assign it to all-ones, then use a separate
	 * statement to mess with it again...
	 */
	mask = ~(mask >> 1);
	while (n > 0) {
		/* If x is different after masking the last bit, there's a 1 in the far
		 * right bit and we know we need a 1 at the far left */
		if (x > (x & (~0 << 1))) {
			x = x >> 1;
			x = x | mask;
		} else {
			x = x >> 1;
		}
		n--;
	}
	return x;
}

int main() {
	printf("rightrot(3052, 3) produces %u\n", rightrot(3052, 3));
	printf("rightrot(1, 1) produces %u\n", rightrot(1, 1));
	printf("rightrot(4096, 4) produces %u\n", rightrot(4096, 4));
	return 0;
}
