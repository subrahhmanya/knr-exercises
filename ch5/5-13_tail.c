#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* The C Programming Language: 2nd Edition
 *
 * Exercise 5-13: Write the program `tail`, which prints the last n lines of
 * its input. By default, n is 10, let us say, but it can be changed by an
 * optional argument, so that `tail -n` prints the last n lines. The program
 * should behave rationally no matter how unreasonable the input or the value
 * of n. Write the program so it make the best use of available storage; lines
 * should be stored as in the sorting program of Section 5.6, not in a
 * two-dimensional array of fixed size.
 */

#define MAXLINES 50000
#define MAXLEN 1000
#define DEFAULT_LINES 10
#define ALLOCSIZE 10000000

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

char *lineptr[MAXLINES];
int numlines;

int mygetline(char *line, int lim) {
	int c, i;
	for (i = 0; i < lim && (c = getchar()) != EOF && c != '\n'; i++) {
		*(line++) = c;
	}
	if (c == '\n') {
		i++; /* I count newlines; some don't */
		*(line++) = c;
	}
	*line = '\0';
	return i;
}

char *alloc(int n) {
	if (allocbuf + ALLOCSIZE - allocp >= n) {
		allocp += n;
		return allocp - n;
	} else {
		return 0;
	}
}

int readlines(char *lineptr[], int maxlines) {
	int len, nlines;
	char *p, line[MAXLEN];
	nlines = 0;
	while ((len = mygetline(line, MAXLEN)) > 0) {
		if (nlines >= maxlines || (p = alloc(len)) == NULL) {
			return -1;
		} else {
			line[len-1] = '\0';
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	}
	return nlines;
}

void writelines(char *lineptr[], int sline, int nlines) {
	int i;
	if (sline > 0) {
		i = sline;
	} else {
		i = 0;
	}
	for (; i < nlines && lineptr[i] != NULL; i++) {
		printf("%s\n", lineptr[i]);
	}
}

void parse_args(int argc, char *argv[]) {
	if (argc == 2 && *(++argv)[0] == '-') {
		int i = 1;
		char arg[10];
		for (i = 1; i < 10 && (*argv)[i] != '\0'; i++) {
			arg[i - 1] = (*argv)[i];
		}
		numlines = atoi(arg);
	} else {
		numlines = DEFAULT_LINES;
	}
}

int main(int argc, char *argv[]) {
	int nlines;
	parse_args(argc, argv);

	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		writelines(lineptr, nlines - numlines, nlines);
		return 0;
	} else {
		/* we should repeat ourselves here so tail fails, but gracefully. We
		 * _did_ gather some input, and should print it! */
		nlines = MAXLINES;
		writelines(lineptr, nlines - numlines, nlines);
		printf("-----------------------\n");
		printf("ERROR: Input too large.\n");
		return 1;
	}
}
