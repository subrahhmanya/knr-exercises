#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* The C Programming Language: 2nd Edition
 *
 * Exercise 5-18: Make `dcl` recover from input errors.
 *
 * Notes: The book does a poor job of describing what the reader should
 * do here. Given that 5-20 calls for a refactor of `dcl`, my solution
 * will simply complain at missing parens and brackets, and silently
 * accept semicolons and comments at the end of the input line. Those are
 * considered "errors" to the book's version of the program, and so this
 * solution will fix them.
 *
 * This solution does not handle more complex data types such as const,
 * static, long ("long long ..."), {un}signed, etc. It also won't handle
 * arbitrary parentheses. Really simple stuff.
 */

#define MAXTOKEN 100
#define BUFSIZE 100

enum { NAME, PARENS, BRACKETS, TYPE };

void dcl(void);
void dirdcl(void);
int gettoken(void);
char buf[BUFSIZE];
int bufp = 0;
int tokentype;

char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];
int get_line(char *s, int lim);

void dcl(void) {
	int ns;
	for (ns = 0; gettoken() == '*'; ns++) {
	}
	dirdcl();
	while (ns-- > 0) {
		strcat(out, " pointer to");
	}
}

void dirdcl(void) {
	int type;
	if (tokentype == '(') {
		dcl();
		if (tokentype != ')') {
			printf("error: missing )\n");
		}
	} else if (tokentype == TYPE) {
		strcat(datatype, " ");
		strcat(datatype, token);
		// check again for another type
		gettoken();
	} else if (tokentype == NAME) {
		strcpy(name, token);
	} else {
		printf("error: expected name or (dcl)\n");
	}
	while ((type = gettoken()) == PARENS || type == BRACKETS) {
		if (type == PARENS) {
			strcat(out, " function returning");
		} else {
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
		}
	}
}

int gettoken(void) {
	char *p = token;
	while (buf[bufp] == ' ' || buf[bufp] == '\t') {
		bufp++;
	}
	if (buf[bufp] == '/') {
		if (buf[bufp+1] == '/' || buf[bufp+1] == '*') {
			while (buf[bufp] != '\n') {
				bufp++;
			}
		}
		return tokentype = buf[bufp];
	} else if (buf[bufp] == '(') {
		if (buf[++bufp] == ')') {
			strcpy(token, "()");
			bufp++;
			return tokentype = PARENS;
		} else {
			return tokentype = '(';
		}
	} else if (buf[bufp] == '[') {
		while (buf[bufp] != ']') {
			if (buf[bufp + 1] == '[') {
				return tokentype = buf[bufp + 1];
			}
			if (isspace(buf[bufp])) {
				bufp++;
				continue;
			}
			*p++ = buf[bufp++];
		}
		*p++ = buf[bufp++];
		*p = '\0';
		return tokentype = BRACKETS;
	} else if (isalpha(buf[bufp])) {
		*p++ = buf[bufp++];
		while (isalnum(buf[bufp])) {
			*p++ = buf[bufp++];
		}
		*p = '\0';
		/* check types */
		if (strcmp(token, "int") == 0 ||
				strcmp(token, "double") == 0 ||
				strcmp(token, "char") == 0) {
			return tokentype = TYPE;
		}
		return tokentype = NAME;
	} else {
		return tokentype = buf[bufp++];
	}
}

/* Returns length of line including \n
 */
int get_line(char *s, int lim) {
	int c, i;
	for (i = 0; i < lim - 1 && (c=getchar()) != EOF && c != '\n'; ++i) {
		*s++ = c;
	}
	if (c == '\n') {
		*s++ = c;
		i++;
	}
	*s = '\0';
	return i;
}

int main(void) {
	int len = 0;
	while ((len = get_line(buf, BUFSIZE)) > 0 && buf[len - 1] != EOF) {
		if (len == 1 && buf[bufp] == '\n') {
			continue;
		}
		bufp = 0;
		datatype[0] = 0;
		gettoken();
		if (tokentype == TYPE) {
			strcpy(datatype, token);
		}
		out[0] = '\0';
		name[0] = '\0';
		dcl();
		if (tokentype == ')') {
			printf("error: too many closing parens\n\n");
		} else if (tokentype == ']') {
			printf("error: too many closing brackets\n\n");
		} else if (tokentype == '(') {
			printf("error: too many opening parens\n\n");
		} else if (tokentype == '[') {
			printf("error: too many opening brackets\n\n");
		} else {
			printf("%s: %s %s\n\n", name, out, datatype);
		}
	}
	return 0;
}
