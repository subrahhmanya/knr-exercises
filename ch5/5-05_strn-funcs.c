#include <stdio.h>

/* The C Programming Language: 2nd Edition
 *
 * Exercise 5-5: Write versions of the library functions strncpy, strncat, and
 * strncmp, which operate on at most the first n charecetr of their argument
 * strings. For example, strncpy(s,t,n) copies at most n character of t to s.
 * Full descriptions are in Appendix B.
 */

char *strn_cpy(char *, const char *, size_t);
char *strn_cat(char *, const char *, size_t);
int strn_cmp(const char *, const char *, size_t);

int main() {
	/* This is to fill the array up beyond where I'll be filling it so I can
	 * test. */
	char foo[50] = "Meepineeeeeessssss";
	char *bar = "Merpy";
	printf("strn_cpy: %s\n", strn_cpy(foo, bar, 9));
	/* Test to see that the last element of the range is indeed a \0, and
	 * some other part further is something else. */
	if (foo[8] == '\0' && foo[14] != '\0') {
		printf("strn_cpy works as expected.\n");
	}
	bar = " hai";
	printf("strn_cat: %s\n", strn_cat(foo, bar, 9));
	// bar is 4 characters long. Let's test comparisons.
	printf("strn_cmp: %d\n", strn_cmp(bar, "hai lits", 10)); // -4
	printf("strn_cmp: %d\n", strn_cmp(bar, "no", 10)); // 2
	printf("strn_cmp: %d\n", strn_cmp(bar, "derp", 10)); // 0
	return 0;
}

char *strn_cpy(char *s, const char *t, size_t n) {
	char *start = s;
	while (n > 0 && *t != '\0') {
		*s++ = *t++;
		n--;
	}
	while (n > 0) {
		*s++ = '\0';
		n--;
	}
	return start;
}

char *strn_cat(char *s, const char *t, size_t n) {
	char *start = s;
	while (*s != '\0') {
		s++;
	}
	while (*t != '\0' && n > 0) {
		*s++ = *t++;
		n--;
	}
	*s = '\0';
	return start;
}

int strn_cmp(const char *s, const char *t, size_t n) {
	int slen, tlen;
	slen = tlen = 0;
	while (n > 0) {
		if (*s != '\0') {
			s++;
			slen++;
		}
		if (*t != '\0') {
			t++;
			tlen++;
		}
		n--;
	}
	return slen - tlen;
}
