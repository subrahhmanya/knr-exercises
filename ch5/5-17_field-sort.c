#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* The C Programming Language: 2nd Edition
 *
 * Exercise 5-17: Add a field-handling capability, so sorting may be done on
 * fields within lines, each field sorted according to an independent set of
 * options. (The index of this book was sorted with -df for the index
 * category and -s for the page numbers.)
 *
 * Notes: The directions for this exercise are ambiguous. Given that this book
 * is meant to teach and keep things mostly simple, I opted for a program that
 * allows you to sort its input by a single field, using any sorting option
 * previously available. For the index, then, this program would need to be
 * ran multiple times to get the desired result. Sorting multiple ways at once
 * on different fields at once is a complexity level far beyond what's been
 * covered at this point in the book, so I don't think that was the intended
 * goal. Enough jabbering; code time!
 */


#define MAXLINES 5000
#define MAXLEN 1000
#define DEFAULT_LINES 10
#define ALLOCSIZE 10000000
#define DELIMITER '\t'

char *lineptr[MAXLINES];
static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;
int numeric = 0;   /* 1 if numeric sort */
int reverse = 0;   /* 1 if reverse sort */
int fold = 0;      /* 1 if folding upper and lower case */
int dir = 0;       /* 1 if directory order */
int fieldnum = 0;  /* Field to sort by, starting with 0. (This only gets used with -F) */

char *alloc(int);
int field_len(const char *);
int field_start(const char *, int);
int fieldcmp(const char *, const char *);
int istrcmp(const char *, const char *);
int mystrcmp(const char *, const char *);
int numcmp(const char *, const char *);
int readlines(char *lineptr[], int nlines);
void my_qsort(void *lineptr[], int left, int right, int (*comp)(const char *, const char *));
void reverse_set(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

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

int field_start(const char *s, int fieldnum) {
	if (fieldnum == 0) {
		return 0;
	}
	int i;
	for (i = 0; s[i] != '\0'; i++) {
		if (s[i] == DELIMITER) {
			fieldnum--;
			if (fieldnum == 0) {
				if (s[i+1] != '\0') {
					return i+1;
				}
			}
		}
	}
	return -1;
}

int field_len(const char *s) {
	int i = 0;
	while (s[i] != '\0') {
		if (s[i] == DELIMITER) {
			return i;
		}
		i++;
	}
	return i; /* If we reach the end of the string, we should return */
}

/* Produces substring copies of the fields to be compared, then hands it off
 * to a comparison function.
 */
int fieldcmp(const char *s1, const char *s2) {
	char tmp1[MAXLEN];
	char tmp2[MAXLEN];
	int start1 = field_start(s1, fieldnum);
	int start2 = field_start(s2, fieldnum);
	int len1 = field_len(s1 + start1);
	int len2 = field_len(s2 + start2);
	/* It should be safe to use strncpy here since we've established the
	 * boundaries of the field within the extant source strings
	 */
	strncpy(tmp1, s1 + start1, len1);
	tmp1[len1] = '\0';
	strncpy(tmp2, s2 + start2, len2);
	tmp2[len2] = '\0';
	return (numeric ? numcmp(tmp1, tmp2) : (fold || dir) ? mystrcmp(tmp1, tmp2) : strcmp(tmp1, tmp2));
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
int main(int argc, char *argv[]) {
	int nlines;        /* number of input lines read */
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
						case 'f':
							fold = 1;
							break;
						case 'd':
							dir = 1;
							break;
						case 'F':
							if (isdigit(argv[i][++j])) {
								fieldnum = (argv[i][j] - '0');
							}
							break;
					}
					j++;
				}
			}
		}
	}
	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		/* The trick is to chain inline if-statements. This will point to the correct
		function for comparison, which powers my_qsort */
		my_qsort((void **) lineptr, 0, nlines - 1, (int (*)(const char *, const char *))(fieldnum >= 0 ? fieldcmp : (numeric ? numcmp : (fold || dir ? mystrcmp : strcmp))));
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
