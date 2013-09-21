#include <stdio.h>

/* The C Programming Language: 2nd Edition
 *
 * Exercise 5-9: Rewrite the routines day_of_year() and month_day() with
 * pointers instead of indexing.
 */

static char daytab[] = {
	0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

int main() {
	int i, m, d, doy;
	int tvals[][4] = {
		{ 2012, 2, 29, 60 },
		{ 2013, 3, 1, 60 },
		{ 1985, 10, 22, 295 }
	};
	m = d = 0;
	doy = 0;

	// It said nothing about avoiding indexing in main()!
	for (i = 0; i < 3; i++) {
		doy = day_of_year(tvals[i][0], tvals[i][1], tvals[i][2]);
		month_day(tvals[i][0], doy, &m, &d);
		if (doy > 0 && m != 0 && d != 0) {
			printf("%4d-%02d-%02d is day %3d of the year. ", tvals[i][0], tvals[i][1], tvals[i][2], doy);
			printf("Day %3d of %4d is month %2d and day %3d.\n", doy, tvals[i][0], m, d);
		} else {
			printf("Out of range\n");
		}
	}
	return 0;
}

int day_of_year(int year, int month, int day) {
	int i, leap;
	leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;

	if (month < 1 || month > 12) {
		return -1;
	}
	// Slightly complicated pointer math is needed to account for leap years
	if (day > *(daytab + month) + ((month == 2) ? leap : 0) || day < 1) {
		return -1;
	}
	for (i = 1; i < month; i++) {
		// here, too
		day += *(daytab + i) + ((i ==2) ? leap : 0);
	}
	return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday) {
	int i, leap;
	leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;

	if (yearday > 365 + leap || yearday < 1) {
		*pmonth = 0;
		*pday = 0;
		return;
	}
	// ...and here. :P
	for (i = 1; yearday > *(daytab + i) + ((i == 2) ? leap : 0); i++) {
		yearday -= *(daytab + i) + ((i == 2) ? leap : 0);
	}
	*pmonth = i;
	*pday = yearday;
}

