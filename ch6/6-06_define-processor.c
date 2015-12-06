#include <stdio.h>
#include <string.h> // strdup, strcmp
#include <stdlib.h> // malloc, free

/* The C Programming Language: 2nd Edition
 *
 * Exercise 6-6: Implement a simple version of the `#define` processor
 * (i.e., no arguments) suitable for use with C programs, based on the
 * routines of this section. You may also find getch() and ungetch()
 * helpful.
 *
 * Notes: The routines this exercise is talking about are lookup() and
 * install(), which were used in 6-5. It also depends on the 'nlist'
 * data structure that those functions used. It's unclear what is meant
 * by "#define processor", so I opted for a simple string replacement
 * implementation. It only accepts one alpha-numeric name and one alpha-
 * numeric replacement, so nowhere *near* correctly supporting #define,
 * but it fulfills the requirements. There's room for improvement here,
 * for sure.
 */

#define HASHSIZE 101
#define MAXWORD 65
#define BUFSIZE 40

struct nlist {
	struct nlist *next;
	char *name;
	char *defn;
};

static struct nlist *hashtab[HASHSIZE];
enum states {
	NORMAL,
	INQUOTE,
	COMMENT_PART_IN,
	COMMENT_PART_OUT,
	ONELINE_COMMENT,
	INCOMMENT
};
static char buf[BUFSIZE];
static int bufp = 0;
int state = NORMAL;

unsigned hash(char *);
struct nlist *install(char *, char *);
struct nlist *lookup(char *);
int getch(void);
void ungetch(int);
int getword(char *, int);

int main() {
	char *word = malloc(sizeof(char) * MAXWORD);
	struct nlist *def;
	int define_phase = 0;
	char *name;
	char *desc;
	while (getword(word, MAXWORD) != EOF) {
		if (state == NORMAL && strcmp(word, "#define") == 0) {
			define_phase = 1;
			printf("%s", word);
			continue;
		}
		if (define_phase == 1) {
			name = strdup(word);
			define_phase = 2;
			printf("%s", word);
			continue;
		}
		if (define_phase == 2) {
			desc = strdup(word);
			define_phase = 0;
			printf("%s", word);
			install(name, desc);
			continue;
		}
		if (state == NORMAL && (def = lookup(word)) != NULL) {
			printf("%s", def->defn);
			continue;
		}
		printf("%s", word);
	}
}

/* form hash value for string s */
unsigned hash(char *s) {
	unsigned hashval;
	for (hashval = 0; *s != '\0'; s++) {
		hashval = *s + 31 * hashval;
	}
	return hashval % HASHSIZE;
}

/* Look for s in hashtab */
struct nlist *lookup(char *s) {
	struct nlist *np;
	for (np = hashtab[hash(s)]; np != NULL; np = np->next) {
		if (strcmp(s, np->name) == 0) {
			return np;
		}
	}
	return NULL;
}

/* put name and defn in hashtab */
struct nlist *install(char *name, char *defn) {
	struct nlist *np;
	unsigned hashval;
	if ((np = lookup(name)) == NULL) {
		np = (struct nlist *) malloc(sizeof(*np));
		if (np == NULL || (np->name = strdup(name)) == NULL) {
			return NULL;
		}
		hashval = hash(name);
		np->next = hashtab[hashval];
		hashtab[hashval] = np;
	} else {
		free ((void *) np->defn);
	}
	if ((np->defn = strdup(defn)) == NULL) {
		return NULL;
	}
	return np;
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

int getword(char *word, int lim) {
	int c;
	char *w = word;
	while (isspace(c = getch())) {
		if (c == '\n' && state == ONELINE_COMMENT) {
			state = NORMAL;
		}
		putchar(c);
	}
	if (c != EOF) {
		*w++ = c;
	} else {
		return EOF;
	}
	switch (c) {
		case '/':
			switch (state) {
				case NORMAL:
					state = COMMENT_PART_IN;
					break;
				case COMMENT_PART_IN:
					state = ONELINE_COMMENT;
					break;
				case COMMENT_PART_OUT:
					state = NORMAL;
					break;
			}
			break;
		case '*':
			switch (state) {
				case INCOMMENT:
					state = COMMENT_PART_OUT;
					break;
				case COMMENT_PART_IN:
					state = INCOMMENT;
					break;
			}
			break;
		case '"':
			switch (state) {
				case NORMAL:
					state = INQUOTE;
					break;
				case INQUOTE:
					state = NORMAL;
					break;
			}
			break;
	}
	if (!isalnum(c) && c != '#') {
		*w = '\0';
		return c;
	}
	for ( ; --lim > 0; w++) {
		if (!isalnum(*w = getch())) {
			ungetch(*w);
			break;
		}
	}
	*w = '\0';
	return word[0];
}
