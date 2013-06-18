#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* The C Programming Language: 2nd Edition
 *
 * Exercise 4-3: Given the basic framework, it's straightforward to extend the
 * calculator. Add the modulus (%) operator and provisions for negative
 * numbers.
 *
 * Answer: Supporting modulus is indeed rather easy. The modulus operator
 * divides the first operand by the second and returns the remainder, and C
 * supports this out of the box, so there's no need to implement much math.
 * Note that the modulus operator does integer division to get its remainder.
 * Doing a "proper" modulus operator would require more work, and floats can
 * be tricky. I might implement this sometime. For now, I typecasted.
 *
 * For negative numbers, you just need to make sure you allow the dash symbol
 * in two key places.
 */

#define MAXOP    100
#define NUMBER   '0'
#define MAXVAL   100
#define BUFSIZE  100

int getop(char []);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);

int sp = 0; // Next free stack position
double val[MAXVAL]; // Value stack
char buf[BUFSIZE]; // buffer for ungetch
int bufp = 0; // next free position in buf

/* Reverse Polish calculator:
 *
 * Binary operations (+-*\%)
 *     operand operand operator
 *
 * Example: 6 minus 2 in Reverse Polish Notation is "6 2 -"
 */
int main() {
	int type;
	double op2;
	char s[MAXOP];

	while ((type = getop(s)) != EOF) {
		switch (type) {
			case NUMBER:
				push(atof(s));
				break;
			case '+':
				push(pop() + pop());
				break;
			case '*':
				push(pop() * pop());
				break;
			case '-':
				op2 = pop();
				push(pop() - op2);
				break;
			case '/':
				op2 = pop();
				if (op2 != 0.0) {
					push(pop() / op2);
				} else {
					printf("Error: Cannot divide by zero.\n");
				}
				break;
			/* Yay for modulus! */
			case '%':
				op2 = pop();
				if (op2 != 0.0) {
					push((int)pop() % (int)op2);
				} else {
					printf("Error: Cannot modulo by zero.\n");
				}
				break;
			case '\n':
				printf("\t%.8g\n", pop());
				break;
			default:
				printf("Error: Unknown command %s\n", s);
				break;
		}
	}
	return 0;
}

void push(double f) {
	if (sp < MAXVAL) {
		val[sp++] = f;
	} else {
		printf("Error: Stack full. Cannot push %g\n", f);
	}
}

double pop(void) {
	if (sp > 0) {
		return val[--sp];
	} else {
		printf("Error: Stack empty.\n");
		return 0.0;
	}
}

int getop(char s[]) {
	int i, c;

	while ((s[0] = c = getch()) == ' ' || c == '\t') {
	}
	s[1] = '\0';
	/* The final check is for negative numbers. */
	if (!isdigit(c) && c != '.' && c != '-') {
		return c;
	}
	i = 0;
	/* The second half of this if-statement accounts for negatives */
	if (isdigit(c) || (i == 0 && c == '-')) {
		while (isdigit(s[++i] = c = getch())) {
		}
	}
	if (c == '.') {
		while (isdigit(s[++i] = c = getch())) {
		}
	}
	s[i] = '\0';
	if (c != EOF) {
		ungetch(c);
	}
	return NUMBER;
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
