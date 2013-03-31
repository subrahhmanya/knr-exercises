#include <stdio.h>

/* The C Programming Language: 2nd Edition
 *
 * Exercise 2-6: Write a function setbits(x,p,n,y) that returns x with the n
 * bits that begin at position p set to the rightmost bits of y, leaving the
 * other bits unchanged.
 *
 * Answer: The book hands you the function you need to get this done: getbits.
 * To be honest I don't fully understand the function, and this portion of the
 * chapter is very poorly explained. For instance, what is a lower order bit?
 * What is a right-adjusted bit field? Further, why are octal numbers used for
 * binary operations when each octal bit is only 3 binary bits long? It would
 * make more sense to use hexadecimal.
 *
 * At any rate, getbits()'s p parameter is the position from the right side of
 * a binary number. The far right bit is position 0 (zero), and n is the number
 * of binary fields it should take, reading to the right. This behavior wasn't
 * entirely obvious.
 *
 * Anyway, setbits() clears the right-most n bits of y and replaces them with
 * the result of getbits(). It took a little clever thought, but it works. :)
 */

unsigned getbits(unsigned x, int p, int n) {
	return (x >> (p + 1 - n)) & ~(~0 << n);
}

unsigned setbits(unsigned x, unsigned p, unsigned n, unsigned y) {
	/* ~0 << n sets the rightmost n fields to zero. Using & on that clears them
	 * from the end of y. Then using | on the result of getbits() sets them to
	 * the end of y, where they belong. */
	return y & (~0 << n) | getbits(x, p, n);
}

int main() {
	printf("With x as 74, p as 5, n as 4, and y as 0, setbits returns %d\n", setbits(74, 5, 4, 0));
	printf("1[0010]00 to 000[0000], creating 0000010\n\n");
	printf("With x as 90, p as 3, n as 2, and y as 20, setbits returns %d\n", setbits(90, 3, 2, 20));
	printf("101[10]10 to 00101[00], creating 0010110\n\n");
	printf("With x as 256, p as 8, n as 1, and y as 14, setbits returns %d\n", setbits(256, 8, 1, 14));
	printf("[1]00000000 to 00000111[0], creating 000001111\n");
	return 0;
}
