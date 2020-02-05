#include "pch.h"
#include <iostream>
#include <string>
using namespace std;
double f_1 (double x) {
	return (exp(x) - exp(-x)) * (exp(x) - exp(-x) - 2);
}
double f_2 (double x) {
	return (1.8 * pow(x, 4) - sin(10 * x)) * (21.6 * pow(x, 2) + 100 * sin(10 * x));
}
double f1 (double x) {
	return (exp(x) - exp(-x) - 2) / (exp(x) + exp(-x));
}
double f2(double x) {
	return (1.8 * pow(x, 4) - sin(10 * x)) / (7.2 * pow(x, 3) - 10 * cos(10 * x));
}
double method(double eps, int maxk, double a, double b, int &k, double (*f) (double), double(*f_) (double), int &flag_1) {
	double x, x1;
	if (f_(a) > 0) {
		x = a;
		x1 = b;
	}
	else {
		x = b;
		x1 = a;
	}
	while (abs(x - x1) > eps) {
		k++;
		x1 = x;
		printf("%.50f   ", x);
		x = x1 - f(x1);
		if (k > maxk) {
			flag_1 = 1;
			break;
		}
	}
	return x;
}
int main() {
	for (int i = 0; i < 2; i++) {
		double eps, a, b, x;
		int maxk, k = 0, flag_1 = 0;
		cout << "eps: ";
		cin >> eps;
		cout << "Max steps count: ";
		cin >> maxk;
		cout << "First \nEnter bounds left: ";
		cin >> a;
		cout << "right: ";
		cin >> b;
		if (i == 0) {
			x = method(eps, maxk, a, b, k, f1, f_1, flag_1);
		}
		else {
			x = method(eps, maxk, a, b, k, f2, f_2, flag_1);
		}
		if (flag_1 == 0)
			printf ("%.50f   %d\n", x, k);
		else
			cout << "Eror";
	}
}
