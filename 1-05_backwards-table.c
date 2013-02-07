#include <stdio.h>

/* The C Programming Language, 2nd Edition
 *
 * Exercise 1-5: Modify the temperature conversion program to print the table in
 * reverse order, that is, from 300 degrees to 0.
 *
 * Answer: Ensure that fahr starts at upper and the while loop runs until zero.
 */

int main(void) {
	float fahr, celsius;
	int lower, upper, step;

	lower = 0;
	upper = 300;
	step = 20;

	fahr = upper;

	printf("   F |  C\n");
	printf("------------\n");
	while (fahr >= 0) {
		celsius = (5.0 / 9.0) * (fahr - 32.0);
		printf(" %3.0f %6.1f\n", fahr, celsius);
		fahr -= step;
	}
	return 0;
}
