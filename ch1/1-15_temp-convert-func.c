#include <stdio.h>

/* The C Programming Language: 2nd Edition
 *
 * Exercise 1-15: Rewrite the temperature conversion program of Section 1.2 to
 * use a function for conversion.
 *
 * Answer: This exercise teaches you the purpose of functions: to perform
 * specific operations that can be reused. Writing good functions is the
 * foundation of good programming. Without functions, programming would still
 * be in its version of the stone age.
 *
 * In the case of temperature conversion, all you really need to do is
 * outsource the math to a function and return the result.
 */

#define MAX_F 300.0
#define STEP 20.0

float convert_to_c(float f) {
	float celsius = (5.0 / 9.0) * (f - 32.0);
	return celsius;
}

int main() {
	printf("FAHRENHEIT   CELSIUS\n");
	float i;
	for (i = 0.0; i <= MAX_F; i += STEP) {
		printf("%4.0f           %7.3f\n", i, convert_to_c(i));
	}
	return 0;
}
