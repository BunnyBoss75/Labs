#include "pch.h"
#include <iostream>
#include <time.h>
#include <cmath>
using namespace std;
int main() {
	int n, i, ii, sum = 0, sum1 = INT_MAX, j = 0;
	srand(time(NULL));
	printf("enter matrix size\n");
	cin >> n;
	int **a = new int*[n];
	for (i = 0; i < n; i++)
		a[i] = new int[n];
	printf("0 - random, 1 - enter\n");
	cin >> i;
	if (i == 0)
		for (i = 0; i < n; i++)
			for (ii = 0; ii < n; ii++)
				a[i][ii] = rand() % 20 - 10;
	else
		for (i = 0; i < n; i++)
			for (ii = 0; ii < n; ii++)
				cin >> a[i][ii];
	for (i = 0; i < n; i++) {
		for (ii = 0; ii < n; ii++)
			printf("%2d  ", a[i][ii]);
		printf("\n");
	}
	printf("1)\n");
	for (ii = 0; ii < n; ii++) {
		for (i = 0; i < n; i++) {
			if (a[i][ii] < 0)
				break;
		}
		if (i == n)
			for (i = 0; i < n; i++) {
				sum += a[i][ii];
				j = 1;
			}
	}
	if (sum == 0 && j == 0)
		printf("matching string not found");
	else
		printf("sum = %d\n2)\n", sum);
	for (i = 1; i < n; i++) {
		for (ii = 0, sum = 0, j = i; j < n; j++, ii++)
			sum += abs(a[j][ii]);
		if (sum < sum1)
			sum1 = sum;
	}
	for (ii = 1; ii < n; ii++) {
		for (i = 0, sum = 0, j = ii; j < n; i++, j++)
			sum += abs(a[i][j]);
		if (sum < sum1)
			sum1 = sum;
	}
	printf("minsum = %d\n", sum1);
}