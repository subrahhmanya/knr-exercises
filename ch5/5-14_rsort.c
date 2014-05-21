#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* The C Programming Language: 2nd Edition
 *
 * Exercise 5-14: Modify the sort program to handle a -r flag, which
 * indicates sorting in reverse (decreasing) order. Be sure that -r works
 * with -n.
 */

#define MAXLINES 5000
char *lineptr[MAXLINES];

#define MAXLEN 1000
#define DEFAULT_LINES 10
#define ALLOCSIZE 10000000

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;
char *alloc(int);

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void reverse_set(char *lineptr[], int nlines);
void my_qsort(void *lineptr[], int left, int right, int (*comp)(const char *, const char *));
int numcmp(const char *, const char *);

void my_qsort(void *v[], int left, int right, int (*comp)(const char *, const char *)) {
	int i, last;
	void swap(void *v[], int, int);

	if (left >= right) {
		return;
	}
	swap(v, left, (left + right) / 2);
	last = left;
	for (i = left + 1; i <= right; i++) {
		if ((*comp)(v[i], v[left]) <= 0) {
			swap(v, ++last, i);
		}
	}
	swap(v, left, last);
	my_qsort(v, left, last - 1, comp);
	my_qsort(v, last + 1, right, comp);
}

int numcmp(const char *s1, const char *s2) {
	double v1, v2;

	v1 = atof(s1);
	v2 = atof(s2);
	if (v1 < v2) {
		return -1;
	} else if (v1 > v2) {
		return 1;
	} else {
		return 0;
	}
}

void swap(void *v[], int i, int j) {
	void *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
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

void writelines(char *lineptr[], int nlines) {
	int i = 0;
	for (; i < nlines && lineptr[i] != NULL; i++) {
		printf("%s\n", lineptr[i]);
	}
}

void reverse_set(char *lineptr[], int nlines) {
	int i;
	int j = nlines;
	for (i = 0; i < (nlines / 2); i++, j--) {
		if (i < nlines) {
			swap((void **)lineptr, i, j);
		}
	}
}

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

/* sort input lines */
int main (int argc, char *argv[]) {
	int nlines;        /* number of input lines read */
	int numeric = 0;   /* 1 if numeric sort */
	int reverse = 0;   /* 1 if reverse sort */

	if (argc > 1) {
		int i, j;
		for (i = 1, j = 0; --argc; i++) {
			if (argv[i][j++] == '-') {
				while (argv[i][j] != '\0') {
					switch(argv[i][j]) {
						case 'n':
							numeric = 1;
							break;
						case 'r':
							reverse = 1;
							break;
					}
					j++;
				}
			}
		}
	}
	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		my_qsort((void **) lineptr, 0, nlines - 1, (int (*)(const char *, const char *))(numeric ? numcmp : strcmp));
		if (reverse == 1) {
			reverse_set(lineptr, nlines - 1);
		}
		writelines(lineptr, nlines);
		return 0;
	} else {
		printf("Input too big to sort\n");
		return 1;
	}
}
