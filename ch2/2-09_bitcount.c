#include <stdio.h>

/* The C Programming Language: 2nd Edition
 *
 * Exercise 2-9: In a two's complement number system, x &= (x-1) deletes
 * the rightmost 1-bit in x. Explain why. Use this observation to write a
 * faster version of bitcount.
 *
 * Answer: Subtracting 1 from a number reverses the rightmost 1 bit and
 * replaces all lower-order bits to 0. So for example:
 *
 * 110100 (52) minus 1 is
 * 110011 (51)
 *
 * The & operator only masks bits off (makes them zero) if that bit in the
 * second operand is also zero. That means...
 *
 * 110100 (52) &
 * 110011 (51) is
 * 110000
 *
 * Why? Because the 2nd operand (51) is only masking off two fields, the 3rd
 * and 4th (which are zeros). The rightmost 1-bit in the 1st operand (52) is
 * in that mask, so it goes poof.
 */

unsigned bitcount(unsigned x) {
	int count = 0;
	while (x != 0) {
		x &= (x - 1);
		count++;
	}
	return count;
}

int main() {
	int i;
	unsigned test[4] = { 51, 65535, 256, 10834 };
	for (i = 0; i < 4; i++) {
		printf("%6u has %2d ones in its binary representation.\n", test[i], bitcount(test[i]));
	}
	return 0;
}
