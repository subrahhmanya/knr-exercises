#include <stdio.h>

/* The C Programming Language: 2nd Edition
 *
 * Exercise 5-8: There is no error checking in day_of_year or month_day.
 * Remedy this defect.
 *
 */

static char daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

int main() {
	int m, d, doy;
	m = d = 0;
	doy = 0;

	printf("Calling day_of_year(1973, 10, 32)\n> ");
	if ((doy = day_of_year(1973, 10, 32)) > 0) {
		printf("Oct 12nd, 1973 is day %d\n", doy);
	} else {
		printf("The month or day is out of range!\n");
	}
	printf("Calling month_day(1985, 295, ...)\n> ");
	month_day(1985, 295, &m, &d);
	if (m > 0 && d > 0) {
		printf("Day 295 of year 1985 is month %d and day %d\n", m, d);
	} else {
		printf("month_day: day of year out of range!\n");
	}
	printf("Calling day_of_year(1492, 5, 14)\n> ");
	if ((doy = day_of_year(1492, 5, 14)) > 0) {
		printf("May 14th, 1492 is day %d\n", doy);
	} else {
		printf("The month or day is out of range!\n");
	}
	printf("Calling month_day(2012, 367, ...)\n> ");
	month_day(2012, 367, &m, &d);
	if (m > 0 && d > 0) {
		printf("Day 295 of year 1985 is month %d and day %d\n", m, d);
	} else {
		printf("month_day: day of year out of range!\n");
	}
	return 0;
}

int day_of_year(int year, int month, int day) {
	int i, leap;
	leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;

	if (month < 1 || month > 12) {
		return -1;
	}
	if (day > daytab[leap][month] || day < 1) {
		return -1;
	}
	for (i = 1; i < month; i++) {
		day += daytab[leap][i];
	}
	return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday) {
	int i, leap;
	leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;

	// Check for edge case
	if (yearday > 365 + leap || yearday < 1) {
		*pmonth = 0; // Set to zero so the error is obvious
		*pday = 0;
		return;
	}
	for (i = 1; yearday > daytab[leap][i]; i++) {
		yearday -= daytab[leap][i];
	}
	*pmonth = i;
	*pday = yearday;
}
