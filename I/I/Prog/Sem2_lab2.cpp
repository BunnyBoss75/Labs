#include "pch.h"
#include <iostream>
#include <time.h>
using namespace std;
int f(int flag_1, int n, int b) {
	int i, j, o;
	double *A = new double[n];
	if (flag_1 == 0) {
		double **A = (double**)b;
		for (i = 0; i < n; i++) {
			if (A[i][i] > 0)
				o = 1;
			else if (A[i][i] == 0)
				o = 0;
			else
				o = -1;
			for (j = 0; j < n; j++)
				if (j != i)
					A[i][j] = o;
		}
		return (int)A;
	}
	else {
		double *A = (double*)b;
		for (i = 0; i < n; i++) {
			if (A[i*n + i] > 0)
				o = 1;
			else if (A[i*n + i] == 0)
				o = 0;
			else
				o = -1;
			for (j = 0; j < n; j++)
				if (j != i)
					A[i*n + j] = o;
		}
		return (int)A;
	}
}
int main() {
	srand(time(NULL));
	int i, j, n;
	cin >> n;
	double ** A = new double* [n];
	double *A1 = new double [n*n];
	for (i = 0; i < n; i++)
		A[i] = new double [n];
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			A1[i*n + j] = (double)(rand() % 1999) / 100 - 9.99;
			A[i][j] = A1[i*n + j];
		}
	}
	cout << "1" << endl;
	A = (double**)f(0, n, (int)A);
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			printf("%5.2f  ", A[i][j]);
		}
		cout << endl;
	}
	cout << "2" << endl;
	A1 = (double*)f(1, n, (int)A1);
	for (i = 0; i < n*n; i++) {
		printf("%5.2f  ", A1[i]);
		if (!(i % (n - 1)) & i != 0)
			cout << endl;
	}
	system("pause");
}