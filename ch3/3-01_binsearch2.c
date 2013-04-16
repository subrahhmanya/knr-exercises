#include <stdio.h>

/* The C Programming Language: 2nd Edition
 *
 * Exercise 3-1: Our binary search makes two tests inside the loop, when
 * one would suffice (at the price of more tests outside). Write a version
 * with only one test inside the loop and measure the difference in run-
 * time.
 *
 * Answer: I don't know how to measure the performance of the original
 * function. `time` reports 0.001 sec, so it's not precise enough.
 *
 * Anyway, the trick is to create a loop that will exit on two conditions:
 * either the last-inspected integer in the array matches the one we're
 * looking for, or it doesn't. The only issue with this is it won't exit
 * the loop as soon as it's found; it may take a few more iterations for it
 * to fully exit, where it will determine which condition made it exit.
 *
 * I don't have a good tool to measure execution time with (that I know of), so
 * my best guess is binsearch2 is faster because it uses only one test in the
 * while loop. However, it won't exit the loop as soon as the match is found; it
 * needs another few iterations for 'low' to equal or surpass 'high'.
 */

int binsearch(int x, int v[], int n) {
	int low, mid, high;

	low = 0;
	high = n - 1;
	while (low <= high) {
		mid = (low + high) / 2;
		if (x < v[mid]) {
			high = mid - 1;
		} else if (x > v[mid]) {
			low = mid + 1;
		} else {
			return mid;
		}
	}
	return -1;
}

int binsearch2(int x, int v[], int n) {
	int low, mid, high;

	low = 0;
	high = n - 1;

	while (low < high) {
		mid = (low + high) / 2;
		if (x <= v[mid]) {
			high = mid;
		} else {
			low = mid + 1;
		}
	}

	if (x == v[low]) {
		return low;
	} else {
		return -1;
	}
}

int main() {
	int foo[5] = {1, 2, 3, 5, 6};
	int i;
	for (i = 1; i < 7; i++) {
		printf("binsearch2 for %d is %d\n", i, binsearch2(i, foo, 5));
	}
}
