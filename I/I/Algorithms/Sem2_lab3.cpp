#include "pch.h"
#include <iostream>
#include <time.h>
using namespace std;
int main() {
	int m, n, p, q, i, j, k, x, count = 0;
	srand(time(NULL));
	printf("Enter m: ");
	cin >> m;
	printf("Enter n: ");
	cin >> n;
	printf("Enter p: ");
	cin >> p;
	printf("Enter q: ");
	cin >> q;
	int **A = new int*[m], **B = new int*[p];
	for (i = 0; i < m; i++)
		A[i] = new int[n];
	for (i = 0; i < p; i++)
		B[i] = new int[q];
	printf("Matrix A:\n");
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			A[i][j] = rand() % 2;
			printf("%d  ", A[i][j]);
		}
		cout << endl;
	}
	printf("Matrix B:\n");
	for (i = 0; i < p; i++) {
		for (j = 0; j < q; j++) {
			B[i][j] = rand() % 2;
			printf("%d  ", B[i][j]);
		}
		cout << endl;
	}
	for (i = 0; i < (m - p + 1); i++) {
		for (j = 0; j < (n - q + 1); j++) {
			if (A[i][j] == B[0][0]) {
				for (k = 0; k < p; k++) {
					for (x = 0; x < q; x++) {
						if (A[i + k][j + x] != B[k][x]) {
							k = p + 1;
							x = q + 1;
						}
					}
				}
				if ((k == (p)) && (x == (q))) {
					count++;
					printf("[%d][%d]\n", i, j);
				}
			}
		}
	}
	printf("Count: %d\n", count);
}