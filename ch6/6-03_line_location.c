#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

/* The C Programming Language: 2nd Edition
 *
 * Exercise 6-3: Write a cross-referencer that prints a list of all words in a
 * document, and, for each word, a list of the line numbers on which it occurs.
 * Remove noise words like "the", "and", and so on.
 *
 * Notes: The trick to this is to pare down a few functions from 6-2, then add
 * a separate struct to be part of the tnode struct. I opted for a linked list
 * of line numbers and some recursion. getline could have been used, and might
 * have been slightly simpler, but this gets the job done. There's certainly
 * some room for better word detection, and the tlist structure could probably
 * be something that's not O(n), but this is Category-0 so who cares? :)
 */

#define BUFSIZE 1000
#define MAXWORD 100
#define DEF_PRE_LEN 4

struct tlist {
	struct tlist *next;
	int num;
};

struct tnode {
	char *word;
	struct tlist *lines;
	struct tnode *left;
	struct tnode *right;
};

char buf[BUFSIZE];
int bufp = 0;
int minlen;
int line_nr = 1;

int getch(void);
void ungetch(int);
int getword(char *, int);
struct tnode *addtree(struct tnode *, char *, int);
void addlist(struct tlist *, int);
void treeprint(struct tnode *);
void listprint(struct tlist *);
struct tnode *talloc(void);
struct tlist *lalloc(void);
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
	char word[MAXWORD];
	root = NULL;
	while (getword(word, MAXWORD) != EOF) {
		/* Only add the words we need to the tree */
		if (isalpha(word[0]) && strlen(word) > minlen) {
			root = addtree(root, word, line_nr);
		}
	}
	if (root == NULL) {
		printf("No words at that length or greater were found.\n");
		return 1;
	} else {
		treeprint(root);
		return 0;
	}
}

int getword(char *word, int lim) {
	int c;
	char *w = word;
	while (isspace(c = getch())) {
		if (c == '\n') {
			line_nr++;
		}
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

struct tnode *addtree(struct tnode *p, char *w, int pos) {
	int cond;
	if (p != NULL) {
		if ((cond = strcmp(w, p->word)) == 0) {
			addlist(p->lines, pos);
		} else if (cond < 0) {
			p->left = addtree(p->left, w, pos);
		} else if (cond > 0) {
			p->right = addtree(p->right, w, pos);
		}
	} else {
		p = talloc();
		p->lines = lalloc();
		p->word = mystrdup(w);
		/* Add to the list of lines */
		(p->lines)->num = pos;
		(p->lines)->next = NULL;
		p->left = p->right = NULL;
	}
	return p;
}

void addlist(struct tlist *l, int pos) {
	/* Follow the list until we reach the end */
	while (l->next != NULL) {
		l = l->next;
	}
	/* Don't add a line number if the numbers match! */
	if (l->num == pos) {
		return;
	}
	/* This won't happen unless l->next is NULL, meaning we've reached the end of the list. */
	struct tlist *newline = lalloc();
	newline->num = pos;
	newline->next = NULL;
	/* Let's add to it now */
	l->next = newline;
}

void treeprint(struct tnode *p) {
	if (p != NULL) {
		treeprint(p->left);
		printf("%-20s  ", p->word);
		listprint(p->lines);
		treeprint(p->right);
	}
}

void listprint(struct tlist *list) {
	printf("%3d ", list->num);
	if (list->next != NULL) {
		listprint(list->next);
	} else {
		printf("\n");
	}
}

struct tnode *talloc(void) {
	return (struct tnode *) malloc(sizeof(struct tnode));
}

struct tlist *lalloc(void) {
	return (struct tlist *) malloc(sizeof(struct tlist));
}

char *mystrdup(char *s) {
	char *p;
	p = (char *) malloc(strlen(s)+1);
	if (p != NULL) {
		strcpy(p , s);
	}
	return p;
}
