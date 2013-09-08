#include <stdio.h>
#include <ctype.h>

/* The C Programming Language: 2nd Edition
 *
 * Exercise 5-6: Rewrite appropriate programs from earlier chapters and
 * exercises with pointers instead of array indexing. Good possibilites
 * include getline (Chapters 1 and 4), atoi, itoa, and their variants
 * (Chapters 2, 3, and 4), reverse (Chapter 3), and strindex and getop
 * (Chapter 4).
 *
 * Answer: This is more of the same. Practice or homework, basically. Thing is,
 * I hate homework, so let's do the bare minimum and only do the functions
 * that were explicitly listed. :)
 *
 * A cool side effect of using pointers is pointer-based functions seem to be
 * shorter!
 */

int get_line(char *, int);
int atoi(char *);
void itoa(int, char *);
void reverse(char *);
int strindex(char *, char *);
int getop(char *);

int main() {
	// simplistic testing, nothing fancy, screw busywork
	char foo[20] = "foobar";
	char bar[50];
	int baz;
	reverse(foo);
	printf("Let's test reverse(\"foobar\"): %s\n", foo);
	printf("Enter some text to test get_line(): ");
	if ((baz = get_line(bar, 50)) > 0) {
		printf("get_line() returns %d and updates to: %s", baz, bar);
	}
	printf("atoi(): %d\n", atoi("7529"));
	itoa(-4321, bar);
	printf("itoa(): %s\n", bar);
	printf("strindex(\"foobarness\", \"bar\"): %d\n", strindex("foobarness", "bar"));
	printf("Enter a RPN equation to test getop(): ");
	printf("getop(): %d, %s\n", getop(bar), bar);
	return 0;
}

void reverse(char *s) {
	char *end = s;
	char tween;
	while (*end != '\0') {
		end++;
	}
	end--; // get behind the \0
	while (end > s) {
		tween = *end;
		*end-- = *s;
		*s++ = tween;
	}
}

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

int atoi(char *s) {
	int n, sign;
	while (isspace(*s)) {
		s++;
	}
	sign = (*s == '-') ? -1 : 1;
	if (*s == '+' || *s == '-') {
		s++;
	}
	for (n = 0; isdigit(*s); n = 10 * n + (*s - '0'), s++);
	return n * sign;
}

void itoa(int n, char *s) {
	char *start = s;
	int sign = 0;
	if (n < 0) {
		sign = 1;
		n = -n;
	}
	do {
		*s = '0' + (n % 10);
		s++;
	} while ((n /= 10) > 0);
	if (sign) {
		*s = '-';
		s++;
	}
	*s = '\0';
	reverse(start);
}

int strindex(char *s, char *t) {
	int loc;
	int len;
	for (loc = 0; *s != '\0'; loc++, s++) {
		for (len = 0; *t != '\0' && *s == *t; len++, s++, t++);
		if (len > 0 && *t == '\0') {
			return loc;
		}
	}
	return -1;
}

/* This function is useless on its own. It should be used in a calculator
 * application that has an input buffer. Regardless, it should still store the
 * operand in a string and return an integer; that's all testable.
 */
int getop(char *s) {
	int c, next;
	while ((c = *s = getchar()) == ' ' || c == '\t');
	s++;
	*s = '\0';
	if (!isdigit(c) && c != '.' && c != '-') {
		return c;
	}
	if (c == '-') {
		next = getchar();
		if (!isdigit(next) && next != '.') {
			return c;
		} else {
			c = next;
		}
	} else {
		c = getchar();
	}
	while (isdigit(*s = c)) {
		s++;
		c = getchar();
	}
	if (c == '.') {
		*s = c;
		s++;
		while (isdigit(*s = c = getchar())) {
			s++;
		}
	}
	s++;
	*s = '\0';
	return 1; // number found
}
