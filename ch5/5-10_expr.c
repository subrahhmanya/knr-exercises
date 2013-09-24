#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

/* The C Programming Language: 2nd Edition
 *
 * Exercise 5-10: Write the program expr, which evaluates a reverse Polish
 * expression from the command line, where each operator or operand is a
 * separate argument. For example:
 *
 * expr 2 3 4 + *
 *
 * evaluates 2 × (3+4).
 */

#define STACKSIZE 100
#define NUMBER '0'

double stack[STACKSIZE];
double *stp = stack; // stack pointer

void push(double);
double pop(void);

/* This solution only offers basic arithmetic as proof of concept. See
 * Chapter 4's exercises on how to extend this to a fully featured
 * calculator. Note that for most shells, you'll need to escape the
 * multiplication symbol (*) or it will expand to every file in the current
 * directory; NOT what you want in this situation. :)
 * 
 * So if you want 6 × 8 for example, you'll need to type `6 8 \*`
 */
int main(int argc, char *argv[]) {
	int argp; // current argument position
	double op2;
	for (argp = 1; argp < argc; argp++) {
		printf("checking arg: %s\n", argv[argp]);
		int argtype = opt_type(argv[argp]);
		switch(argtype) {
			case '*':
				push(pop() * pop());
				break;
			case '+':
				push(pop() + pop());
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
					printf("error: divide by zero\n");
				}
				break;
			case NUMBER:
				printf("it's a number\n");
				push(atof(argv[argp]));
				break;
		}
		printf("%s\n", argv[argp]);
	}
	printf("%f\n", pop());
}

void push(double num) {
	if (stp >= stack + STACKSIZE) {
		printf("Cannot push: stack full.\n");
		return;
	}
	printf("add %f to stack.\n", num);
	*(++stp) = num;
}

double pop(void) {
	if (stp == stack) {
		printf("Cannot pop: stack empty.\n");
		return 0.0;
	}
	return *(stp--);
}

int opt_type(char op[]) {
	int i = 0;
	switch(op[i]) {
		case '*':
			return '*';
		case '+':
			return '+';
		case '/':
			return '/';
		case '-':
			if (op[i+1] == '\0') {
				return '-';
			}
			break;
	}

	while (isdigit(op[i])) {
		i++;
	}
	if (op[i] == '\0') {
		return NUMBER;
	}
}
