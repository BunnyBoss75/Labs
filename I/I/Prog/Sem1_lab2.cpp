#include "pch.h"
#include <iostream>
#include <cstdlib>
using namespace std;
int main() {
	double x = 1, x1;
	int n = 0;
	while (1) {
		n++;
		x1 = (2 - pow(x, 3)) / 5;
		if (abs(x - x1) < 0.00001)
			break;
		else
			x = x1;
	}
	printf("%19.19f\n%d\n", x1, n);
	system("pause");
}