#include <stdio.h>
#include <limits.h>
#include <float.h>

/* The C Programming Language, 2nd Edition
 *
 * Exercise 2-1: Write a program to determine the ranges of char, short,
 * int, and long variables, both signed and unsigned, by printing
 * appropriate values from standard headers and by direct computation.
 * Harder if you compute them: determine the ranges of the various
 * floating-point types.
 *
 * Answer: The trick to computing these numbers is to understand computer math,
 * which is done in binary, thus with 2. Keep squaring from 1 and you'll
 * eventually find the limit of the variable. Add or subtract from one of the
 * extremes and you'll find the other extreme.
 *
 */

int main() {
	unsigned char uc;
	signed char sc;
	unsigned short us;
	signed short ss;
	unsigned int ui;
	signed int si;
	unsigned long ul;
	signed long sl;
	unsigned long long ull;
	signed long long sll;
	float fl, fla, fll;
	double db, dba, dbl;
	long double ldb, ldba, ldbl;

	printf("Let's compute the minimums and maximums of each type!\n");
	uc = sc = us = ss = ui = si = ul = sl = sll = ull = 0;
	fl = fla = fll = db = dba = dbl = ldb = ldba = ldbl = 0.0;

	/* Characters */

	sc++;
	while (sc * 2 > sc) {
		sc = sc * 2 + 1;
	}

	printf("`signed char` maximum: %d\n", sc);
	sc++;
	printf("`signed char` minimum: %d\n", sc);
	uc--;
	printf("`unsigned char` maximum: %u\n", uc);

	/* Short ints */

	ss++;
	while (ss * 2 > ss) {
		ss = ss * 2 + 1;
	}

	printf("`signed short` maximum: %d\n", ss);
	ss++;
	printf("`signed short` minimum: %d\n", ss);
	us--;
	printf("`unsigned short` maximum: %u\n", us);

	/* Integers */

	si++;
	while (si * 2 > si) {
		si = si * 2 + 1;
	}

	printf("`signed int` maximum: %d\n", si);
	si++;
	printf("`signed int` minimum: %d\n", si);
	ui--;
	printf("`unsigned int` maximum: %u\n", ui);

	/* Long ints */

	sl++;
	while (sl * 2 > sl) {
		sl = sl * 2 + 1;
	}

	printf("`signed long` maximum: %li\n", sl);
	sl++;
	printf("`signed long` minimum: %li\n", sl);
	ul--;
	printf("`unsigned long` maximum: %lu\n", ul);

	/* Long long ints */

	sll++;
	while (sll * 2 > sll) {
		sll = sll * 2 + 1;
	}

	printf("`signed long long` maximum: %lli\n", sll);
	sll++;
	printf("`signed long long` minimum: %lli\n", sll);
	ull--;
	printf("`unsigned long long` maximum: %llu\n", ull);

	/* Floats */
	while (fl == 0.0) {
		fll = fla;
		fla = fla + 1111e28;
		fl = (fl + fla) - fla;
	}

	printf("`float` maximum: %e\n", fll);

	fl = 0.0;
	fll = 0.0;
	fla = 0.0;
	while (fl == 0.0) {
		fll = fla;
		fla = fla - 1111e28;
		fl = (fl - fla) + fla;
	}

	printf("`float` minimum: %e\n", fll);

	/* Doubles */
	while (db == 0.0) {
		dbl = dba;
		dba = dba + 1111e297;
		db = (db + dba) - dba;
	}

	printf("`float` maximum: %e\n", dbl);
	printf("`float` minimum: -%e\n", dbl);
	
	printf("\nNow, let's cheat and use the helpful headers!\n");
	printf("`char`s go from %d to %d (unsigned, up to %u)\n", SCHAR_MIN, SCHAR_MAX, UCHAR_MAX);
	printf("`short`s go from %d to %d (unsigned, up to %u)\n", SHRT_MIN, SHRT_MAX, USHRT_MAX);
	printf("`int`s go from %d to %d (unsigned, up to %u)\n", INT_MIN, INT_MAX, UINT_MAX);
	printf("`long`s go from %ld to %ld (unsigned, up to %lu)\n", LONG_MIN, LONG_MAX, ULONG_MAX);
	printf("`float`s range from %e to %e\n", FLT_MIN, FLT_MAX);
	printf("`double`s range from %e to %e\n", DBL_MIN, DBL_MAX);
	return 0;
}
