#include <stdio.h>
#include <math.h>

/* The C Programming Language: 2nd Edition
 *
 * Exercise 5-2: Write getfloat, the floating-point analog of getint. What
 * type does getfloat return as its function value?
 *
 * Answer: getfloat should return an integer, since getint's return value is
 * only important to check its status, not the value type that it's working
 * with. The only real "gotcha" here is making sure to use getch() after
 * checking for a decimal point so the resulting loop will actually execute.
 */

#define BUFSIZE 100

int getch(void);
void ungetch(int);
int getfloat(double *);

char buf[BUFSIZE];
int bufp = 0;

int main() {
	double foo;
	double *bar = &foo;
	while (getfloat(bar) > 0) {
		printf("%f\n", foo);
	}
	return 0;
}

int getfloat(double *pn) {
	int c, sign, places;

	while (isspace(c = getch())) {
	}
	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c);
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-') {
		c = getch();
	}
	if (c != '.' && !isdigit(c)) {
		return 0;
	}
	for (*pn = 0.0; isdigit(c); c = getch()) {
		*pn = 10.0 * *pn + (c - '0');
	}
	if (c == '.') {
		c = getch(); // skip the decimal point or the loop won't trigger
		for (places = -1; isdigit(c); c = getch()) {
			*pn += (double)(c - '0') * pow(10, places--);
		}
	}
	*pn *= sign;
	if (c != EOF) {
		ungetch(c);
	}
	return c;
}

int getch(void) {
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
	if (bufp >= BUFSIZE) {
		printf("ungetch: Too many characters.\n");
	} else {
		buf[bufp++] = c;
	}
}
