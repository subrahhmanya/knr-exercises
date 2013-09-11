#include <stdio.h>
#include <string.h>

/* The C Programming Language: 2nd Edition
 *
 * Exercise 5-7: Rewrite readlines to store lines in an array supplied by
 * main rather than calling alloc to maintain storage. How much faster is
 * the program?
 *
 */

#define MAXLINES 5000
#define MAXLEN 1000
#define MAXBUF 500000

// An additional argument is needed so we can store addresses
int readlines(char *lineptr[], int nlines, char *in_lines);
void writelines(char *lineptr[], int nlines);
int get_line(char line[], int lim);
void q_sort(char *v[], int left, int right);
void swap(char *v[], int i, int j);

char *lineptr[MAXLINES];

int main() {
	char line_store[MAXBUF]; // this is our buffer for storing lines
	int nlines;
	if ((nlines = readlines(lineptr, MAXLINES, line_store)) >= 0) {
		q_sort(lineptr, 0, nlines - 1);
		writelines(lineptr, nlines);
		return 0;
	} else {
		printf("error: input too big to sort\n");
		return 1;
	}
}

/* The third argument allows us to set and reference pointers to it so the
 * data inside it has structure, which is maintained by the pointers in
 * lineptr[]. Each time we start a new line, the current address of
 * line_store is stored, the text is stored in the buffer, and the process
 * repeats. While this (arguably) uses more RAM (the buffer's rather large),
 * it's marginally faster due to the allocation of RAM only one time as
 * opposed to x times, where x is the number of lines processed.
 */
int readlines(char *lineptr[], int maxlines, char *line_store) {
	int len, nlines, total;
	char line[MAXLEN];
	nlines = 0;
	total = 0; // number of characters processed
	while ((len = get_line(line, MAXLEN)) > 0) {
		if (nlines >= maxlines || total >= MAXBUF) {
			return -1;
		} else {
			total += len;
			line[len - 1] = '\0';
			lineptr[nlines++] = line_store; // copy the current spot to the array of pointers
			strncpy(line_store, line, len); // copy line into line_store
			line_store += len; // advance to the next available spot
		}
	}
	return nlines;
}

void writelines(char *lineptr[], int nlines) {
	while (nlines-- > 0) {
		printf("%s\n", *lineptr++);
	}
}

void q_sort(char *v[], int left, int right) {
	int i, last;
	if (left >= right) {
		return;
	}
	swap(v, left, (left + right) / 2);
	last = left;
	for (i = left + 1; i <= right; i++) {
		if (strcmp(v[i], v[left]) < 0) {
			swap(v, ++last, i);
		}
	}
	swap(v, left, last);
	q_sort(v, left, last - 1);
	q_sort(v, last + 1, right);
}

void swap(char *v[], int i, int j) {
	char *temp;
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

int get_line(char s[], int lim) {
	int c, i;
	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
		s[i] = c;
	}
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}
