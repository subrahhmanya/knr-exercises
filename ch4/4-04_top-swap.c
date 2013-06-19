#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* The C Programming Language: 2nd Edition
 *
 * Exercise 4-4: Add commands to print the top element of the stack without
 * popping, to duplicate it, and to swap the top two elements. Add a
 * command to clear the stack.
 *
 * Answer: Achieving this is pretty simple. Make your functions, then assign
 * them to "commands", which are basically any special characters that aren't
 * being used in the switch statement. Pretty basic manipulation of arrays.
 *
 * Note that any expression that has subtraction at the end needs either a
 * space or an additional newline input after it in order to calculate. This
 * is a limitation of the getchar() based approach.
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
void stack_top(void);
double dupe_top(void);
void swap_top_two(void);
void clear_stack(void);

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
			/* Top of stack */
			case '?':
				stack_top();
				break;
			/* Dupe the top of the stack */
			case '#':
				dupe_top();
				break;
			/* Swap the top two */
			case '~':
				swap_top_two();
				break;
			/* Clear the stack */
			case '!':
				clear_stack();
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
	int i = 0;
	int c, next;

	while ((s[0] = c = getch()) == ' ' || c == '\t') {
	}
	s[1] = '\0';
	/* The final check is for negative numbers. */
	if (!isdigit(c) && c != '.' && c != '-') {
		return c;
	}
	/* The second half of this if-statement accounts for negatives */
	if (c == '-') {
		next = getch();
		if (!isdigit(next) && next != '.') {
			return c;
		} else {
			c = next;
		}
	} else {
		c = getch();
	}

	while (isdigit(s[++i] = c)) {
		c = getch();
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

void stack_top(void) {
	if (sp > 0) {
		printf("Top of stack is %8g\n", val[sp - 1]);
	} else {
		printf("Error: Stack empty.\n");
	}
}

double dupe_top(void) {
	double temp = pop();
	push(temp);
	push(temp);
}

void swap_top_two(void) {
	double tmp1, tmp2;
	tmp1 = pop();
	tmp2 = pop();
	push(tmp1);
	push(tmp2);
}

void clear_stack(void) {
	sp = 0;
}
