#include <stdio.h>
#include <string.h> // strdup, strcmp
#include <stdlib.h> // malloc, free

/* The C Programming Language: 2nd Edition
 *
 * Exercise 6-5: Write a function `undef` that will remove a name and
 * definition from the table maintai\ed by lookup() and install().
 *
 * Notes: since undef() operates on the same data structure as lookup()
 * and install(), I chose to depend on lookup() to find the correct node
 * to remove. The tricky part is juggling two pointers and cleaning up
 * the pointers to other nodes on the list.
 */

#define HASHSIZE 101

struct nlist {
	struct nlist *next;
	char *name;
	char *defn;
};

static struct nlist *hashtab[HASHSIZE];

unsigned hash(char *);
struct nlist *install(char *, char *);
struct nlist *lookup(char *);
int undef(char *);
void print_table(struct nlist *);

int main(int argc, char **argv) {
	/* Install a few words */
	install("foo", "1");
	install("bar", "2");
	install("baz", "4");
	/* Make up scenarios for changing and removing values */
	printf("We don't like baz, because his value is %s.\n", hashtab[hash("baz")]->defn);
	printf("Let's ressign baz to 3.\n");
	install("baz", "3");
	printf("baz is now %s.\n", hashtab[hash("baz")]->defn);
	printf("baz is a weird name. Let's try removing it.\n");
	undef("baz") ? : printf("baz was removed from the table! Let's check to make sure it's gone...\n");
	if (lookup("baz") == NULL) {
		printf("Success! baz is gone!\n");
	}
	return 0;
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

int undef(char *name) {
	struct nlist *np, *np2;
	if ((np = lookup(name)) == NULL) {
		return 1;
	}
	for (np = np2 = hashtab[hash(name)]; np != NULL; np2 = np, np = np->next) {
		if (np == np2) {
			hashtab[hash(name)] = np->next;
		} else {
			np2->next = np->next;
		}
		free(np->name);
		free(np->defn);
		free(np);
		return 0;
	}
}
