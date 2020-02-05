#include "pch.h"
#include <iostream>
#include <time.h>
using namespace std;
int main() {
	int n, i, j, t = INT_MIN;
	cin >> n;
	int** a = new int*[n];
	for (i = 0; i < n; i++)
		a[i] = new int[n];
	srand(time(NULL));
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			a[i][j] = rand() % 19 - 9;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (a[i][j] > t)
				t = a[i][j];
			printf("%2d ", a[i][j]);
		}
		printf("   %d\n", t);
		t = INT_MIN;
	}
	t = INT_MAX;
	printf("\n\n");
	for (j = 0; j < n; j++) {
		for (i = 0; i < n; i++)
			if (t > a[i][j])
				t = a[i][j];
		printf("%d ", t);
		t = INT_MAX;
	}
}