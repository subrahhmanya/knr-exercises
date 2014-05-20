#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* The C Programming Language: 2nd Edition
 *
 * Exercise 5-16: Add the -d ("directory order") option, which makes
 * comparisons only on letters, numbers, and blanks. Make sure it works in
 * conjunction with -f.
 */

#define MAXLINES 5000
char *lineptr[MAXLINES];

#define MAXLEN 1000
#define DEFAULT_LINES 10
#define ALLOCSIZE 10000000

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;
char *alloc(int);
int numeric = 0;   /* 1 if numeric sort */
int reverse = 0;   /* 1 if reverse sort */
int fold = 0;      /* 1 if folding upper and lower case */
int dir = 0;       /* 1 if directory order */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void reverse_set(char *lineptr[], int nlines);
void my_qsort(void *lineptr[], int left, int right, int (*comp)(const char *, const char *));
int numcmp(const char *, const char *);
int istrcmp(const char *, const char *);
int dirstrcmp(const char *, const char *);

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

/* Ignore character case, then send results to qsort */
int mystrcmp(const char *s1, const char *s2) {
	if (dir) {
		while (!isalpha(*s1) && !isspace(*s1) && isdigit(*s1)) {
			s1++;
		}
		while (!isalpha(*s2) && !isspace(*s2) && isdigit(*s2)) {
			s2++;
		}
	}
	while ((fold ? (tolower(*s1) == tolower(*s2)) : (*s1 == *s2))) {
		if (*s1 == '\0') {
			return 0;
		}
		s1++;
		s2++;
		if (dir) {
			while (!isalpha(*s1) && !isspace(*s1) && isdigit(*s1)) {
				s1++;
			}
			while (!isalpha(*s2) && !isspace(*s2) && isdigit(*s2)) {
				s2++;
			}
		}
	}
	return (fold ? (tolower(*s1) - tolower(*s2)) : (*s1 - *s2));
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

	if (argc > 1) {
		int i;
		for (i = 1; --argc; i++) {
			if (strcmp(argv[i], "-n") == 0) {
				numeric = 1;
			} else if (strcmp(argv[i], "-r") == 0) {
				reverse = 1;
			} else if (strcmp(argv[i], "-f") == 0) {
				fold = 1;
			} else if (strcmp(argv[i], "-d") == 0) {
				dir = 1;
			}
		}
	}
	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		/* The trick is to chain inline if-statements. This will point to the correct
		function for comparison, which powers my_qsort */
		my_qsort((void **) lineptr, 0, nlines - 1, (int (*)(const char *, const char *))(numeric ? numcmp : (fold ? mystrcmp : (dir ? mystrcmp : strcmp))));
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
