#include "pch.h"
#include <iostream>
#include <time.h>
#include <cmath>
using namespace std;
int n, i20;
double a[10000], o, o1;
int main() {
	int i;
	srand(time(NULL));
	printf("select the number of items\n");
	cin >> n;
	printf("0 - rand; 1 - enter\n");
	cin >> i;
	if (i == 0)
		for (i = 0; i < n; i++)
			a[i] = (double)(rand() % 1900 - 900) / 100;
	else
		for (i = 0; i < n; i++)
			cin >> a[i];
	for (i = 0; i < n; i++)
		printf("%.2f; ", a[i]);
	cout << endl;


	printf("1)\n");
	int nmax = 0, nmin = 0, nc = 0;
	double n1;
	for (i = 1; i < n - nmax;) {
		if (a[nmax] < a[nmax + i]) {
			nmax = nmax + i;
			i = 1;
		}
		else
			i++;
	}
	for (i = 1; i < n - nmin;) {
		if (a[nmin] > a[nmin + i]) {
			nmin = nmin + i;
			i = 1;
		}
		else
			i++;
	}
	n1 = (a[nmax] + a[nmin]) / 2;
	for (i = 0; i < n; i++)
		if (a[i] > n1)
			nc++;
	printf("Nmax = %.2f; Nmin = %.2f; Nmidle = %.3f; answer: %d\n", a[nmax], a[nmin], n1, nc);



	printf("2)\n");
	int n2 = -1;
	double sum = 0;
	for (i = 1; i < n - n2;) {
		if (a[n2 + i] > 0) {
			n2 = n2 + i;
			i = 1;
		}
		else
			i++;
	}
	for (i = 0; i < n2; i++) {
		sum += a[i];
	}
	if (i == -1)
		printf("no positive items found");
	else
		printf("answer:%.2f\n", sum);


	printf("3)\n");
	printf("enter a and b (a < b; a >= 0; b >= 0\n");
	cin >> o >> o1;
	for (i = 0; i < n; i++) {
		if (abs(a[i]) >= o && abs(a[i]) <= o1) {
			for (i20 = i; i20 < n - 1; i20++)
				a[i20] = a[i20 + 1];
			a[n - 1] = 0;
			i--;
		}
	}
	for (i = 0; i < n; i++)
		printf("%.2f; ", a[i]);
	cout << endl;
	system("pause");
}