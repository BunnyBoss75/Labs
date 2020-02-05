#include <fstream>
#include <iostream>
#include <time.h>
#include <string>
using namespace std;
string *createCouples(int** matrix, int n, int m, int amountCouple) {
	string *graf = new string[amountCouple];
	int count = 0;
	string couple;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (matrix[i][j]) {
				couple = "(" + to_string(i) + ", " + to_string(j) + ")";
				graf[count] = couple;
				count++;
			}
		}
	}
	return graf;
}
void showCouples(string* couple, int k, int amountCouple) {
	int count = 1;
	int* locationCouple = new int[k];
	for (int i = 0; i < k; i++) {
		locationCouple[i] = i;
	}
	while (locationCouple[0] != (amountCouple - k + 1)) {
		cout << count << ") ";
		count++;
		for (int i = 0; i < k; i++) {
			cout << couple[locationCouple[i]] << " ";
			//cout << locationCouple[i] << " ";
		}
		cout << endl;

		locationCouple[k - 1]++;
		int temp = k - 1, temp1 = 1;
		while ((locationCouple[k - 1] >= amountCouple) && (locationCouple[0] != (amountCouple - k + 1))) {
			temp = k - 1 - temp1;
			locationCouple[temp]++;
			for (temp++; temp < k; temp++) {
				locationCouple[temp] = locationCouple[temp - 1] + 1;
			}
			temp1++;
		}
	}
}
int main() {
	int n, m, k;
	ifstream ifMatrix("Matrix.txt");
	ifMatrix >> n >> m >> k;
	int** matrix = new int* [n];
	for (int i = 0; i < n; i++) {
		matrix[i] = new int[m];
		for (int j = 0; j < m; j++) {
			ifMatrix >> matrix[i][j];
		}
	}
	int amountCouple = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (matrix[i][j]) {
				amountCouple++;
			}
		}
	}
	string* couple = createCouples(matrix, n, m, amountCouple);
	showCouples(couple, k, amountCouple);
}