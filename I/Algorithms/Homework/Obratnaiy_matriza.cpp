#include "pch.h"
#include <iostream>
#include <time.h>
using namespace std;
double def(double** A, int count) {  
	int i, j, k, z;
	double sum = 0;
	if (count == 1)
		return A[0][0];
	else {
		double** A1 = new double*[count - 1];
		for (i = 0; i < count - 1; i++)
			A1[i] = new double[count - 1];
		for (z = 0; z < count; z++) {
			for (i = 0, k = 0; i < count; k++, i++) {
				if (i == z)
					i++;
				if (i == count)
					break;
				for (j = 1; j < count; j++)
					A1[k][j - 1] = A[i][j];
			}
			sum += pow(-1, z) * def(A1, count - 1) * A[z][0];
		}
		for (i = 0; i < count - 1; i++)
			delete[] A1[i];
		delete[] A1;
		return sum;
	}
}
int main() {
	int n, i, j, k, z, y, x;
	cin >> n;
    double** A = new double* [n];
	for (i = 0; i < n; i++)
		A[i] = new double[n];
	double** At = new double*[n];
	for (i = 0; i < n; i++)
		At[i] = new double[n];
	double** Ad = new double*[n - 1];
	for (i = 0; i < n - 1; i++)
		Ad[i] = new double[n - 1];
	double** Ao = new double*[n];
	for (i = 0; i < n; i++)
		Ao[i] = new double[n];
	double** Ae = new double*[n];
	for (i = 0; i < n; i++)
		Ae[i] = new double[n];
	srand(time(NULL));
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			//cin >> A[i][j];
			A[i][j] = double (rand() % 100) / 10;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++)
			printf("%6.1f", A[i][j]);
		cout << endl;
	}
	double det = def(A, n);
	printf("determinant: %f\n", det);
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			At[j][i] = A[i][j];
		}
	}
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++) {
			for (k = 0, y = 0; k < n; k++, y++) {
				if (k == i)
					k++;
				if (k == n)
					break;
				for (z = 0, x = 0; z < n; z++, x++) {
					if (z == j)
						z++;
					if (z == n)
						break;
					Ad[y][x] = At[k][z];
				}
			}
			Ao[i][j] = (pow(-1, i + j) * def(Ad, n - 1)) / det;
		}
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++)
			printf("%7.2f", Ao[i][j]);
		cout << endl;
	}
	cout << endl;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			Ae[i][j] = 0;
			for (x = 0; x < n; x++)
				Ae[i][j] += A[i][x] * Ao[x][j];
		}
	}
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			printf("%10.5f", Ae[i][j]);
		}
		cout << endl;
	}
	double eps = 10e-10;
	bool program_good_work = true;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if ((i == j && abs(Ae[i][j] - 1) > eps) || (i != j && abs(Ae[i][j]) > eps))
				program_good_work = false;
		}
	}
	cout << program_good_work;
}