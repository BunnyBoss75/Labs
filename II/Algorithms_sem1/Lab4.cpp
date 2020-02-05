#include <fstream>
#include <iostream>
#include <time.h>
using namespace std;
int amountPoint;
struct point {
	double x;
	double y;
	double z;
};
struct triangle {
	double length1;
	double length2;
	double length3;
};
point* readPoint() {
	ifstream ifFile("file.txt");
	ifFile >> amountPoint;
	point* data = new point[amountPoint];
	for (int i = 0; i < amountPoint; i++) {
		ifFile >> data[i].x >> data[i].y >> data[i].z;
	}
	return data;
}
triangle countLength(point p1, point p2, point p3) {
	triangle tr;
	tr.length1 = pow(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2) + pow(p1.z - p2.z, 2), 0.5);
	tr.length2 = pow(pow(p2.x - p3.x, 2) + pow(p2.y - p3.y, 2) + pow(p2.z - p3.z, 2), 0.5);
	tr.length3 = pow(pow(p3.x - p1.x, 2) + pow(p3.y - p1.y, 2) + pow(p3.z - p1.z, 2), 0.5);
	return tr;
}
bool checkIsosceles(triangle tr) { //равнобедренный
	if (abs(tr.length1 - tr.length2) < 10e-6) {
		return true;
	}
	else if (abs(tr.length2 - tr.length3) < 10e-6) {
		return true;
	}
	else if (abs(tr.length3 - tr.length1) < 10e-6) {
		return true;
	}
	else {
		return false;
	}
}
bool checkRectangular(triangle tr) { //прямоугольный
	if (abs(pow(tr.length1, 2) - pow(tr.length2, 2) - pow(tr.length3, 2)) < 10e-6) {
		return true;
	}
	else if (abs(pow(tr.length2, 2) - pow(tr.length3, 2) - pow(tr.length1, 2)) < 10e-6) {
		return true;
	}
	else if (abs(pow(tr.length3, 2) - pow(tr.length1, 2) - pow(tr.length2, 2)) < 10e-6) {
		return true;
	}
	else {
		return false;
	}
}
void bruteForse1(point* data) {
	int counterIsosceles = 0;
	int counterRectangular = 0;
	triangle tr;
	for (int i = 0; i < amountPoint; i++) {
		for (int j = i + 1; j < amountPoint; j++) {
			for (int k = j + 1; k < amountPoint; k++) {
				tr = countLength(data[i], data[j], data[k]);
				if (checkIsosceles(tr)) {
					cout << data[i].x << " " << data[i].y << " " << data[i].z << "\n";
					cout << data[j].x << " " << data[j].y << " " << data[j].z << "\n";
					cout << data[k].x << " " << data[k].y << " " << data[k].z << " is isosceles\n\n";
					counterIsosceles++;
				}
				if (checkRectangular(tr)) {
					cout << data[i].x << " " << data[i].y << " " << data[i].z << "\n";
					cout << data[j].x << " " << data[j].y << " " << data[j].z << "\n";
					cout << data[k].x << " " << data[k].y << " " << data[k].z << " is rectangular\n\n";
					counterRectangular++;
				}
			}
		}
	}
	cout << "isosceles: " << counterIsosceles << " rectangular: " << counterRectangular << endl;
}
void bruteForse2(point* data) {
	int counterIsosceles = 0;
	int counterRectangular = 0;
	int k = 3;
	int* location = new int[k];
	triangle tr;
	for (int i = 0; i < k; i++) {
		location[i] = i;
	}
	while (location[0] != (amountPoint - k + 1)) {
		tr = countLength(data[location[0]], data[location[1]], data[location[2]]);
		if (checkIsosceles(tr)) {
			cout << data[location[0]].x << " " << data[location[0]].y << " " << data[location[0]].z << "\n";
			cout << data[location[1]].x << " " << data[location[1]].y << " " << data[location[1]].z << "\n";
			cout << data[location[2]].x << " " << data[location[2]].y << " " << data[location[2]].z << " is isosceles\n\n";
			counterIsosceles++;
		}
		if (checkRectangular(tr)) {
			cout << data[location[0]].x << " " << data[location[0]].y << " " << data[location[0]].z << "\n";
			cout << data[location[1]].x << " " << data[location[1]].y << " " << data[location[1]].z << "\n";
			cout << data[location[2]].x << " " << data[location[2]].y << " " << data[location[2]].z << " is rectangular\n\n";
			counterRectangular++;
			cout << endl;
		}
		location[k - 1]++;
		int temp = k - 1, temp1 = 1;
		while ((location[k - 1] >= amountPoint) && (location[0] != (amountPoint - k + 1))) {
			temp = k - 1 - temp1;
			location[temp]++;
			for (temp++; temp < k; temp++) {
				location[temp] = location[temp - 1] + 1;
			}
			temp1++;
		}
	}
	cout << "isosceles: " << counterIsosceles << " rectangular: " << counterRectangular << endl;
}
int main() {
	int workTime, workTime1, workTime2;
	point* data = readPoint();
	workTime = clock();
	bruteForse1(data);
	workTime1 = clock() - workTime;
	//workTime = clock();
	//bruteForse2(data);
	//workTime2 = clock() - workTime;
	//cout << workTime1 << " " << workTime2 << endl;
}