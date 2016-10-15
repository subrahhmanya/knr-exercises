#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* The C Programming Language: 2nd Edition
 *
 * Exercise 5-20: Expand `dcl` to handle declarations with function
 * argument types, qualifiers like `const`, and so on.
 *
 * Notes: Basically, you need a qualifier string and an accepting
 * type string. This solution is nowhere near robust, and is in great
 * need of a refactor, but honestly I don't know where to begin fixing
 * this mess.
 *
 * The robust way to do this would be to have a list of valid tokens, their
 * semantic meaning, and a sort of "test string" that could be verified for
 * integrity before attempting to output. Once it's been checked for sanity,
 * the gathered details should be added to the final sentence in grammatical
 * order. That requires more work than this exercise is worth, however. If I
 * find myself bored with C, I'll come back to this, as it could be done much
 * better than what's here. Patches welcome!
 */

#define MAXTOKEN 100
#define BUFSIZE 100

enum { NAME, PARENS, BRACKETS, TYPE, QUAL };

void dcl(void);
void dirdcl(void);
int gettoken(void);
char buf[BUFSIZE];
int bufp = 0;
int tokentype;
int accept = 0;

char qual[MAXTOKEN];
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char clause[MAXTOKEN];
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
	} else if (tokentype == QUAL) {
		strcat(qual, token);
		gettoken();
	} else if (tokentype == TYPE) {
		strcat(datatype, " ");
		strcat(datatype, token);
	} else if (tokentype == NAME) {
		strcpy(name, token);
	} else {
		printf("error: expected name or (dcl)\n");
	}
	while ((type = gettoken()) == PARENS || type == BRACKETS) {
		if (type == PARENS) {
			strcat(out, " function returning");
			if (accept == 1) {
				strcpy(clause, " accepting ");
				while ((type = gettoken()) != '\n' && type != ')') {
					if (type == '(') {
						continue;
					}
					if (type == QUAL) {
						strcat(clause, token);
						strcat(clause, " ");
						continue;
					} else if (type == TYPE) {
						strcat(clause, token);
						return;
					} else {
						printf("Error: invalid argument type: %s\n", token);
					}
				}
				strcat(clause, "void");
				return;
			}
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
			accept = 1;
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
		if (strcmp(token, "const") == 0 ||
				strcmp(token, "static") == 0 ||
				strcmp(token, "long") == 0 ||
				strcmp(token, "short") == 0) {
			return tokentype = QUAL;
		}
		if (strcmp(token, "int") == 0 ||
				strcmp(token, "double") == 0 ||
				strcmp(token, "unsigned") == 0 ||
				strcmp(token, "signed") == 0 ||
				strcmp(token, "void") == 0 ||
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
		qual[0] = 0;
		gettoken();
		if (tokentype == QUAL) {
			strcpy(qual, token);
			gettoken();
		}
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
			printf("%s: %s %s %s %s\n\n", name, out, qual, datatype, clause);
		}
		accept = 0;
	}
	return 0;
}
