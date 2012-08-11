#include <stdio.h>

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
