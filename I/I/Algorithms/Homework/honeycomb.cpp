#include "pch.h"
#include <iostream>
#include <time.h>
using namespace std;
void f1(int **A, int i, int j, int &k, int b, int n);
int f(int **A, int i, int j, int b, int n);
int main() {
	int n, i, j;
	cin >> n;
	int **A = new int *[n];
	for (i = 0; i < n; i++)
		A[i] = new int[n];
	srand(time(NULL));
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			//cin >> A[i][j];
			A[i][j] = rand() % 5 + 1;
	for (i = 0; i < n; i++) {
		if (i % 2 == 0)
			printf("    ");
		for (j = 0; j < n; j++)
			printf("   %d    ", A[i][j]);
		cout << endl;
	}
	printf("\n\n\n");
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++) {
			if (f(A, i, j, A[i][j], n)) {
				i = 0;
				j = -1;
			}
		}
	for (i = 0; i < n; i++) {
		if (i % 2 == 0)
			printf("    ");
		for (j = 0; j < n; j++)
			printf("   %d    ", A[i][j]);
		cout << endl;
	}
}
int f(int **A, int i, int j, int b, int n) {
	int k = 1, i1 = 0, j1 = 0;
	f1(A, i, j, k, b, n);
	if (k < 3) {
		for (i1 = 0; i1 < n; i1++)
			for (j1 = 0; j1 < n; j1++)
				if (A[i1][j1] == 0)
					A[i1][j1] = b;
		return 0;
	}
	else {
		for (i1 = 0; i1 < n; i1++)
			for (j1 = 0; j1 < n; j1++)
				if (A[i1][j1] == 0)
					A[i1][j1] = rand() % 5 + 1;
		return 1;
	}
}
void f1(int **A, int i, int j, int &k, int b, int n) {
	if (((i - 1) > 0) && (A[i - 2][j] == b)) {
		k++;
		A[i][j] = 0;
		f1(A, i - 2, j, k, b, n);
	}
	if ((i) && (A[i - 1][j] == b)) {
		k++;
		A[i][j] = 0;
		f1(A, i - 1, j, k, b, n);
	}
	if ((((!(i % 2)) && (i)) && ((j + 1) != n)) && (A[i - 1][j + 1] == b)) {
		k++;
		A[i][j] = 0;
		f1(A, i - 1, j + 1, k, b, n);
	}
	if (((i + 2) < n) && (A[i + 2][j] == b)) {
		k++;
		A[i][j] = 0;
		f1(A, i + 2, j, k, b, n);
	}
	if (((i + 1) != n) && (A[i + 1][j] == b)) {
		k++;
		A[i][j] = 0;
		f1(A, i + 1, j, k, b, n);
	}
	if ((((!(i % 2)) && ((i + 1) != n)) && ((j + 1) != n)) && (A[i + 1][j + 1] == b)) {
		k++;
		A[i][j] = 0;
		f1(A, i + 1, j + 1, k, b, n);
	}
	if ((((i % 2) && (i)) && (j)) && (A[i - 1][j - 1] == b)) {
		k++;
		A[i][j] = 0;
		f1(A, i - 1, j - 1, k, b, n);
	}
	if ((((i % 2) && ((i + 1) != n)) && (j)) && (A[i + 1][j - 1] == b)) {
		k++;
		A[i][j] = 0;
		f1(A, i + 1, j - 1, k, b, n);
	}
}