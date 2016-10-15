#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

/* The C Programming Language: 2nd Edition
 *
 * Exercise 6-2: Write a program that reads a C program and prints in
 * alphabetical order each group of variable names that are identical in the
 * first 6 characters, but different somewhere thereafter. Don't count words
 * within string and comments. Make 6 a parameter that can be set from the
 * command line.
 *
 * Notes: First off, "variable names" should be "words". It doesn't make sense
 * otherwise.
 *
 * The trick to this is we can traverse the tree with no problem, but to do
 * comparisons on the words, we need to know the last one we worked with. With
 * two additional static variables in treeprint(), we have all we need to
 * manipulate what we're outputting.
 */

#define BUFSIZE 1000
#define MAXWORD 100
#define DEF_PRE_LEN 6

struct key {
	char *word;
	int count;
};
struct tnode {
	char *word;
	int count;
	struct tnode *left;
	struct tnode *right;
};

enum states {
	NORMAL,
	INQUOTE,
	INCOMMENT
};
char buf[BUFSIZE];
int bufp = 0;
int state = NORMAL;
int minlen;

int getch(void);
void ungetch(int);
int getword(char *, int);
struct key *binsearch(char *, struct key *, int);
struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *, int);
struct tnode *talloc(void);
char *mystrdup(char *);
int check_prefix(char *, char*, int);

int main(int argc, char *argv[]) {
	switch (argc) {
		case 1:
			minlen = DEF_PRE_LEN;
			break;
		case 2:
			minlen = strtol(argv[1], NULL, 10);
			break;
		default:
			printf("Too many arguments.\n");
			return 1;
	}
	struct tnode *root;
	char word[MAXWORD];
	root = NULL;
	while (getword(word, MAXWORD) != EOF) {
		/* Only add the words we need to the tree */
		if (isalpha(word[0]) && strlen(word) > minlen) {
			root = addtree(root, word);
			if (root == NULL) {
				printf("No words at that length or greater were found.\n");
				return 1;
			}
		}
	}
	treeprint(root, minlen);
	return 0;
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

struct key *binsearch(char *word, struct key *tab, int n) {
	int cond;
	struct key *low = &tab[0];
	struct key *high = &tab[n];
	struct key *mid;
	while (low < high) {
		mid = low + (high-low) / 2;
		if ((cond = strcmp(word, mid->word)) < 0) {
			high = mid;
		} else if (cond > 0) {
			low = mid + 1;
		} else {
			return mid;
		}
	}
	return NULL;
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

struct tnode *addtree(struct tnode *p, char *w) {
	int cond;
	if (p == NULL) {
		p = talloc();
		p->word = mystrdup(w);
		p->count = 1;
		p->left = p->right = NULL;
	} else if ((cond = strcmp(w, p->word)) == 0) {
		p->count++;
	} else if (cond < 0) {
		p->left = addtree(p->left, w);
	} else {
		p->right = addtree(p->right, w);
	}
	return p;
}

int check_prefix(char *s1, char *s2, int len) {
	int i;
	if (len == 0) {
		return 1;
	}
	for (i == 0; *s1 == *s2 && *s1 != '\0' && i < len; i++, *s1++, *s2++) {
	}
	if (i == len) {
		return 1;
	}
	return 0;
}

void treeprint(struct tnode *p, int len) {
	static struct tnode *last; /* The last word we saw */
	static int output = 1; /* Controls whether we output 'last' or not */
	if (p != NULL) {
		treeprint(p->left, len);
		if (len == 0) {
			printf("%4d %s\n", p->count, p->word);
		} else {
			if (last != NULL) {
				if (check_prefix(last->word, p->word, len)) {
					if (output) {
						printf("%4d %s\n", last->count, last->word);
						output = 0;
					}
					printf("%4d %s\n", p->count, p->word);
				} else {
					output = 1;
				}
			}
			last = p;
		}
		treeprint(p->right, len);
	}
}

struct tnode *talloc(void) {
	return (struct tnode *) malloc(sizeof(struct tnode));
}

char *mystrdup(char *s) {
	char *p;
	p = (char *) malloc(strlen(s)+1);
	if (p != NULL) {
		strcpy(p , s);
	}
	return p;
}
