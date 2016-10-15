#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* The C Programming Language: 2nd Edition
 *
 * Exercise 6-1: Our version of `getword` does not properly handle underscores,
 * string constants, comments, or preprocessor control lines. Write a better
 * version.
 *
 * Notes: Preprocessor lines and one-line comments should be treated the same by
 * ignoring everything after the beginning. Underscores need to be treated like
 * part of the word, otherwise identifiers such as 'if_else' will get added to
 * the list. Anything inside quotes and multi-line comments needs to be ignored,
 * with a state variable to help us figure out what's going on.
 */


#define MAXWORD 100
#define BUFSIZE 1000

struct key {
	char *word;
	int count;
} keytab[] = {
	"auto",     0,
	"break",    0,
	"case",     0,
	"char",     0,
	"const",    0,
	"continue", 0,
	"default",  0,
	"else",     0,
	"enum",     0,
	"for",      0,
	"if",       0,
	"int",      0,
	"long",     0,
	"return",   0,
	"short",    0,
	"signed",   0,
	"static",   0,
	"struct",   0,
	"switch",   0,
	"typedef",  0,
	"unsigned", 0,
	"void",     0,
	"volatile", 0,
	"while",    0
};

#define NKEYS (sizeof keytab / sizeof(struct key))

char buf[BUFSIZE];
int bufp = 0;
enum states {
	NORMAL,
	INQUOTE,
	INCOMMENT
};
int state = NORMAL;

int getch(void);
void ungetch(int);
int getword(char *, int);
int binsearch(char *, struct key *, int);

int main() {
	int n;
	char word[MAXWORD];
	while (getword(word, MAXWORD) != EOF) {
		if (isalpha(word[0])) {
			if ((n = binsearch(word, keytab, NKEYS)) >= 0) {
				keytab[n].count++;
			}
		}
	}
	for (n = 0; n < NKEYS; n++) {
		if (keytab[n].count > 0) {
			printf("%4d %s\n", keytab[n].count, keytab[n].word);
		}
	}
	return 0;
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

int binsearch(char *word, struct key tab[], int n) {
	int cond;
	int low, high, mid;
	low = 0;
	high = n - 1;
	while (low <= high) {
		mid = (low + high) / 2;
		if ((cond = strcmp(word, tab[mid].word)) < 0) {
			high = mid - 1;
		} else if (cond > 0) {
			low = mid + 1;
		} else {
			return mid;
		}
	}
	return -1;
}

int getword(char *word, int lim) {
	int c;
	char *w = word;
	while (isspace(c = getch())) {
	}
	if (c != EOF && c != '#' && c != '"' && c != '/' && c != '*') {
		*w++ = c;
	}
	if (c == '*' && state == INCOMMENT) {
		if ((c = getch()) == '/') {
			state == NORMAL;
			return '/';
		}
	}
	/* Ignore comments */
	if (c == '/') {
		c = getch();
		if (c == '/') {
			while ((c = getch()) != EOF && c != '\n') {
			}
			return '*';
		}
		if (c == '*') {
			state = INCOMMENT;
			return '*';
		}
	}
	/* Handle quotes */
	if (c == '"') {
		state = INQUOTE;
	}
	if (state == INQUOTE) {
		while ((c = getch()) != '"' && c != EOF) {
		}
		state = NORMAL;
	}
	/* Ignore preprocessor lines */
	if (c == '#') {
		while ((c = getch()) != '\n' && c != EOF) {
		}
	}
	/* Add exceptions for underscores */
	if (!isalpha(c) && c != '_') {
		*w = '\0';
		return c;
	}
	for ( ; --lim > 0; w++) {
		if (!isalnum(*w = getch()) && *w != '_') {
			ungetch(*w);
			break;
		}
	}
	*w = '\0';
	return word[0];
}
