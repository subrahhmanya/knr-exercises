#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

/* The C Programming Language: 2nd Edition
 *
 * Exercise 6-4: Write a program that prints the distinct words in its input
 * sorted into decreasing order of frequency of occurrence. Precede each word
 * by its count.
 *
 * Notes: The approach I took builds a separate sorted tree instead of
 * modifying the tree in-place, like a lot of sorting functions tend to do.
 * This meant doubling the amount of RAM needed to solve the exercise. There
 * is probably a more elegant way to do this -- even within Category-0
 * standards -- but I couldn't seem to figure it out. I'm disappointed that
 * freq_sort and addsorted couldn't seem to be combined.
 */

#define BUFSIZE 1000
#define MAXWORD 100
#define DEF_PRE_LEN 4

struct tnode {
	char *word;
	int count;
	struct tnode *left;
	struct tnode *right;
};

char buf[BUFSIZE];
int bufp = 0;
int minlen;

int getch(void);
void ungetch(int);
int getword(char *, int);
struct tnode *addtree(struct tnode *, char *);
struct tnode *freq_sort(struct tnode *, struct tnode *);
struct tnode *addsorted(struct tnode *, struct tnode *);
void treeprint(struct tnode *);
struct tnode *talloc(void);
char *mystrdup(char *);

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
	struct tnode *sorted;
	char word[MAXWORD];
	root = NULL;
	sorted = NULL;
	while (getword(word, MAXWORD) != EOF) {
		/* Only add the words we need to the tree */
		if (isalpha(word[0]) && strlen(word) > minlen) {
			root = addtree(root, word);
		}
	}
	/* Sort them in order of occurrence */
	if (root == NULL) {
		printf("No words at that length or greater were found.\n");
		return 1;
	} else {
		sorted = freq_sort(root, sorted);
		treeprint(sorted);
		return 0;
	}
}

/* Iterate over the "tree" and create a new, sorted tree */
struct tnode *freq_sort(struct tnode *p, struct tnode *s) {
	for (; p != NULL; p = p->right) {
		s = addsorted(p, s);
	}
	return s;
}

/* Add entries to the new tree, ordered by word frequency. I feel
 * that this function and freq_sort() could somehow be consolidated
 * and that this could be done better. Patches or PRs welcome.
 */
struct tnode *addsorted(struct tnode *p, struct tnode *s) {
	if (s != NULL) {
		if (p->count > s->count) {
			s->left = addsorted(p, s->left);
		} else {
			s->right = addsorted(p, s->right);
		}
	} else {
		s = talloc();
		s->word = mystrdup(p->word);
		s->count = p->count;
	}
	return s;
}

int getword(char *word, int lim) {
	int c;
	char *w = word;
	while (isspace(c = getch())) {
	}
	if (c == EOF) {
		return EOF;
	}
	if (c != EOF) {
		*w++ = c;
	}
	for ( ; --lim > 0; w++) {
		if (!isalpha(*w = getch())) {
			ungetch(*w);
			break;
		}
	}
	*w = '\0';
	return word[0];
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
	if (p != NULL) {
		/* We're putting all new things to the right side to dumb our tree struct
		 * down to a list. It's technically one address larger than a linked list,
		 * but there's no harm in re-purposing a structure.
		 */
		if (strcasecmp(p->word, w) == 0) {
			p->count++;
		} else {
			p->right = addtree(p->right, w);
		}
	} else {
		p = talloc();
		p->word = mystrdup(w);
		p->count = 1;
	}
	return p;
}

void treeprint(struct tnode *p) {
	if (p != NULL) {
		treeprint(p->left);
		printf("%4d  %-20s\n", p->count,  p->word);
		treeprint(p->right);
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
