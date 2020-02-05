#include "pch.h"
#include <iostream>
using namespace std;
int sign(double a) {
	if ((abs(a) - 1e-16) < 0)
		return 0;
	else if (a < 0)
		return -1;
	else
		return 1;
}
int f(double**C, int n) {
	int i, count1 = 0, count2 = 0 ;
	int flag;
	flag = sign(C[0][0]);
	for (i = 1; i < n + 1; i++) {
		if (sign(C[i][0]) == 0 || sign(C[i][0]) == flag)
			continue;
		else {
			flag = sign(C[i][0]);
			count1++;
		}
	}
	flag = sign(C[0][1]);
	for (i = 1; i < n + 1; i++) {
		if (sign(C[i][1]) == 0 || sign(C[i][1]) == flag)
			continue;
		else {
			flag = sign(C[i][1]);
			count2++;
		}
	}
	return count1 - count2;
}
void f1(double**C, double**A, double b1, double b2, int n) {
	int i, j;
	for (i = 0; i < n + 1; i++) {
		C[i][0] = 0;
		C[i][1] = 0;
		for (j = 0; j < n + 1 - i; j++) {
			C[i][0] += A[i][j] * pow(b1, j);
			C[i][1] += A[i][j] * pow(b2, j);
		}
	}
}
int main() {
	int i, j, n, k;
	cout << "Enter deg of polynomial: ";
	cin >> n;
	double e, **A = new double*[n + 1], **B = new double*[n + 2], **C = new double*[n + 1];
	for (i = 0; i < n + 1; i++) {
		A[i] = new double[n + 1 - i];
		C[i] = new double[n + 1];
	}
	for (i = 0; i < n + 2; i++)
		B[i] = new double[2];
	for (i = 0; i < n + 1; i++) {
		printf("Enter coefficient at x^%d: ", n - i);
		cin >> A[0][n - i];
	}
	cout << "Enter left border: ";
	cin >> B[0][0];
	cout << "Enter right border: ";
	cin >> B[n + 1][0];
	cout << "Enter epsilon: ";
	cin >> e;
	for (i = 0; i < n + 2; i++) {
		B[i][1] = 0;
	}
	for (i = 1; i < n + 1; i++)
		for (j = 0; j < n + 1 - i; j++)
			A[i][j] = A[i - 1][j + 1] * (j + 1);
	i = 0;
	j = n + 1;
	while (1) {
		while (1) {
			f1(C, A, B[i][0], B[j][0], n);
			if (sign(C[0][0]) == 0)
				B[i][0] -= 0.5 * e;
			else if (sign(C[0][1]) == 0)
				B[j][0] += 0.5 * e;
			else
				break;
		}
		if (abs(B[i][0] - B[j][0]) < (e / 3))
			break;
		k = f(C, n);
		if (k == 0) {
			B[i][0] = B[j][0];
			j = n + 1;
			continue;
		}
		else if (abs(B[j][0] - B[i][0]) < e) {
			B[i][1] = k;
			B[i + 1][0] = B[j][0];
			i++;
			j = n + 1;
			continue;
		}
		else {
			B[i + 1][0] = (B[j][0] + B[i][0]) / 2;
			j = i + 1;
			continue;
		}
	}
	for (i = 0; i < n + 1; i++) {
		if (B[i][1] > 0) {
			f1(C, A, B[i][0] + e / 2, B[i][0], n);
			if (abs(C[0][0]) > 10e-5)
				B[i][1] = -1;
		}
	}
	for (i = 0; i < n + 2; i++) {
		if (B[i][1] > 0.1) {
			printf("%f, amount: %.0f", B[i][0], B[i][1]);
			cout << endl;
		}
	}
	system("pause");
}