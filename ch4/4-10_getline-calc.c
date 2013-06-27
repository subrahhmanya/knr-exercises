#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

/* The C Programming Language: 2nd Edition
 *
 * Exercise 4-10: An alternate organization uses getline() to read an entire
 * input line; this makes getch() and ungetch() unnecessary. Revise the
 * calculator to use this approach.
 *
 * Answer: This is much trickier than it seems; it teaches you how to refactor
 * a program. You won't be using the built-in getline() for this, but rather
 * the function that we wrote back in Chapter 1.
 *
 * The majority of the trickiness lies in getop(). The idea is to store the
 * entire line in a buffer that sits in an external variable. Then you pick and
 * choose which chars to put into your target string, in much the same way we
 * picked and chose which characters to getch() previously.
 *
 * The rest of the program works about the same, with only a few minor tweaks
 * needed. The cool part is the whole thing didn't need to be rewritten; just
 * the "plumbing" part, getop().
 *
 * In addition to refactoring, this entire project demonstrates the usefulness
 * of modularizing your code into small, discrete functions.
 */

#define MAXOP    100
#define NUMBER   '0'
#define MAXVAL   100
#define BUFSIZE  100

int getop(char []);
void push(double);
double pop(void);
void stack_top(void);
double dupe_top(void);
void swap_top_two(void);
void clear_stack(void);
double fetch_var(char);
void store_var(char, double);
void store_last(double);
double fetch_last(void);
int mygetline(char [], int);

int sp = 0; // Next free stack position
double val[MAXVAL]; // Value stack
char buf[BUFSIZE]; // buffer
int bufp = 0; // next free position in buf
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

	while (mygetline(buf, BUFSIZE) != 0) {
		bufp = 0;
		while ((type = getop(s)) != '\0') {
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
					ltr = buf[bufp];
					if (isalpha(ltr) && islower(ltr)) {
						op2 = pop();
						store_var(ltr, op2);
						push(op2);
					} else {
						push(0.0);
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

	while ((s[0] = c = buf[bufp++]) == ' ' || c == '\t');
	if (c >= 'a' && c <= 'z') {
		return c;
	}
	s[1] = '\0';
	/* The final check is for negative numbers. */
	if (!isdigit(c) && c != '.' && c != '-') {
		return c;
	}
	i = 0;
	/* The second half of this if-statement accounts for negatives */
	if (c == '-') {
		if (!isdigit(buf[bufp]) && buf[bufp] != '.') {
			return c;
		} else {
			s[i] = c;
			c = buf[bufp];
		}
	} else {
		s[i] = c;
	}

	if (isdigit(c)) {
		while (isdigit(s[++i] = c = buf[bufp++]));
	}
	if (c == '.') {
		while (isdigit(s[++i] = c = buf[bufp++]));
	}
	s[i] = '\0';
	bufp--;
	return NUMBER;
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

int mygetline(char s[], int lim) {
	int c, i = 0;

	while (--lim > 0 && (c = getchar()) != EOF && c != '\n') {
		s[i++] = c;
	}
	if (c == '\n') {
		s[i++] = c;
	}
	s[i] = '\0';
	return i;
}
