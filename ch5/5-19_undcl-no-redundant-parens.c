#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* The C Programming Language: 2nd Edition
 *
 * Exercise 5-19: Modify `undcl` so that it does not add redundant parentheses
 * to declarations.
 *
 * Notes: The only circumstance that `undcl` will add extra parens is when it
 * comes across a pointer. So we look ahead and count pointers, then add them
 * all at once before output. It's a fairly simple fix.
 */

#define MAXTOKEN 100
#define BUFSIZE 100
#define MAXPTR 10

enum { NAME, PARENS, BRACKETS, TYPE };

int gettoken(void);
int getch(void);
void ungetch(int);

char buf[BUFSIZE];
int bufp = 0;
int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];

int gettoken(void) {
	int c;
	char *p = token;
	while ((c = getch()) == ' ' || c == '\t') {
	}
	if (c == '(') {
		if ((c = getch()) == ')') {
			strcpy(token, "()");
			return tokentype = PARENS;
		} else {
			ungetch(c);
			return tokentype = '(';
		}
	} else if (c == '[') {
		for (*p++ = c; (*p++ = getch()) != ']'; ) {
		}
		*p = '\0';
		return tokentype = BRACKETS;
	} else if (isalpha(c)) {
		for (*p++ = c; isalnum(c = getch()); ) {
			*p++ = c;
		}
		*p = '\0';
		ungetch(c);
		return tokentype = NAME;
	} else {
		return tokentype = c;
	}
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

int main(void) {
	int type, pcount, i, c;
	char temp[MAXTOKEN];
	char p[MAXPTR];
	while (gettoken() != EOF) {
		strcpy(out, token);
		while ((type = gettoken()) != '\n') {
			if (type == PARENS || type == BRACKETS) {
				strcat(out, token);
			} else if (type == '*') {
				pcount++;
				while ((c = getch()) == '*' || c == ' ') {
					if (c == '*') {
						if (pcount < (MAXPTR - 1)) {
							pcount++;
						} else {
							break;
						}
					}
				}
				ungetch(c);
				for (i = 0; i < pcount; i++) {
					p[i] = '*';
				}
				pcount = 0;
				p[i] = '\0';
				sprintf(temp, "(%s%s)", p, out);
				strcpy(out, temp);
			} else if (type == NAME) {
				sprintf(temp, "%s %s", token, out);
				strcpy(out, temp);
			} else {
				printf("Invalid input at %s\n", token);
			}
		}
		printf("%s\n", out);
	}
	return 0;
}
