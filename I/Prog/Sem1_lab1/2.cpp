#include "pch.h"
#include <iostream>
using namespace std;
int main() {
	float x, y;
	cin >> x;
	if (x <= 0)
		y = 0;
	else if (x <= 1)
		y = x;
	else
		y = pow(x, 4);
	cout << y << endl;
	system("pause");
	return 0;
}