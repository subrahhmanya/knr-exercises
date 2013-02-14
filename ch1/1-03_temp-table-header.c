#include <stdio.h>

/* The C Programming Language, 2nd Edition
 *
 * Exercise 1-3: Modify the temperature conversion program to print a heading
 * above the table.
 *
 * Answer: Just add a printf() or two before the table.
 */

int main(void) {
	float fahr, celsius;
	int lower, upper, step;

	lower = 0;
	upper = 300;
	step = 20;

	fahr = lower;

	printf("   F |  C\n");
	printf("------------\n");
	while (fahr <= upper) {
		celsius = (5.0 / 9.0) * (fahr - 32.0);
		printf(" %3.0f %6.1f\n", fahr, celsius);
		fahr += step;
	}
	return 0;
}
