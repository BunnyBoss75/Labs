#include "pch.h"
#include <iostream>
#include <cmath>
using namespace std;
int main() {
	float x, y;
	cout << "Please enter the x and y." << endl;
	cin >> x;
	cin >> y;
	if (abs(x) <= 1 && 0 >= y && y >= -2)
		cout << "YES" << endl;
	else if (abs(x) >= y && 0 < y && y <= 1)
		cout << "YES" << endl;
	else
		cout << "NO" << endl;
	system("pause");
	return 0;
}