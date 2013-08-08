#include <stdio.h>

/* The C Programming Language: 2nd Edition
 *
 * Exercise 4-14: Define a macro swap(t,x,y) that interchanges two arguments
 * of type t. (Block structure will help.)
 *
 * Answer: Macros are read and processed before syntax is, so you can turn
 * a macro into shorthand code; more shorthand than functions sometimes.
 *
 * This macro assumes x and y are of t type. If the types don't match up,
 * it'll (probably) break.
 */

#define swap(t, x, y) {\
	t z;\
	z = x;\
	x = y;\
	y = z;\
}

int main() {
	int a = 3;
	int b = 7;

	printf("a is %d, b is %d\n", a, b);
	swap(int, a, b);
	printf("Now swap, and... a is %d and b is %d!\n", a, b);
	return 0;
}
