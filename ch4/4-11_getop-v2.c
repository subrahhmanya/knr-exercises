#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

/* The C Programming Language: 2nd Edition
 *
 * Exercise 4-11: Modify getop() so that it doesn't need to use ungetch().
 * Hint: use an internal static variable.
 *
 * Answer: As the hint says, you need to use an internal static variable. What
 * this means is setting a variable inside getop() that will be remembered
 * between getop() calls. You can achieve the same effect with an external
 * variable, but that guarantees that the memory is used, whereas the static
 * internal variable only uses the memory if the function surrounding it is
 * called.
 */

#define MAXOP    100
#define NUMBER   '0'
#define MAXVAL   100
#define BUFSIZE  100

int getop(char []);
void push(double);
double pop(void);
int getch(void);
void stack_top(void);
double dupe_top(void);
void swap_top_two(void);
void clear_stack(void);
double fetch_var(char);
void store_var(char, double);
void store_last(double);
double fetch_last(void);

int sp = 0; // Next free stack position
double val[MAXVAL]; // Value stack
double vars[27];

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
	char ltr;

	while ((type = getop(s)) != EOF) {
		if (isalpha(type) && islower(type)) {
			push(fetch_var(type));
			continue;
		}
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
			/* sin() support */
			case '(':
				op2 = sin(pop());
				push(op2);
				break;
			/* exp() support */
			case '{':
				op2 = exp(pop());
				push(op2);
				break;
			/* pow() support */
			case '^':
				op2 = pop();
				push(pow(pop(), op2));
				break;
			/* 'lastprint' support */
			case '@':
				push(fetch_last());
				break;
			/* setting variables */
			case '=':
				ltr = getchar();
				if (isalpha(ltr) && islower(ltr)) {
					op2 = pop();
					store_var(ltr, op2);
					push(op2);
				}
				break;
			/* Final output */
			case '\n':
				op2 = pop();
				printf("\t%.8g\n", op2);
				/* Extra Credit: Lets output every non-zero variable! */
				for (ltr = 'a'; ltr <= 'z'; ltr++) {
					if (fetch_var(ltr) != 0) {
						printf("\t%c: %.8g\n", ltr, fetch_var(ltr));
					}
				}
				store_last(op2);
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
	static int buf = EOF;

	if (buf != EOF && buf != ' ' && buf != '\t' && !isdigit(buf) && buf != '.' && (buf < 'a' || buf > 'z')) {
		c = buf;
		buf = EOF;
		return c;
	}
	if (buf == EOF || buf == ' ' || buf == '\t') {
		while ((s[0] = c = getch()) == ' ' || c == '\t') {
		}
	} else {
		c = buf;
	}
	buf = EOF;
	s[1] = '\0';
	if (c >= 'a' && c <= 'z') {
		return c;
	}
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
	buf = c;
	return NUMBER;
}

int getch(void) {
	return getchar();
}

void stack_top(void) {
	if (sp > 0) {
		printf("Top of stack is %8g\n", val[sp - 1]);
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

double fetch_var(char c) {
	return vars[c - 'a'];
}

void store_var(char c, double f) {
	vars[c - 'a'] = f;
}

void store_last(double f) {
	vars[26] = f;
}

double fetch_last(void) {
	return vars[26];
}
