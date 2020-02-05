#include <iostream>
#include <ctime>
using namespace std;
int main() {
	int thousand = 1000;
	int** Matrix = new int*[thousand];
	for (int i = 0; i < thousand; i++) {
		Matrix[i] = new int[thousand];
	}
	int* Vector = new int[thousand];
	srand(time(NULL));
	for (int i = 0; i < thousand; i++) {
		Vector[i] = rand() % 3 - 1;
		for (int j = 0; j < thousand; j++) {
			Matrix[i][j] = rand() % 3 - 1;
		}
	}
	int* Result = new int[thousand];
	int workTime, workTime1 = 0, workTime2 = 0;
	cout <<"CLOCKS_PER_SEC: " << CLOCKS_PER_SEC << endl;
	for (int x = 0; x < 20; x++) {
		workTime = clock();
		for (int i = 0; i < thousand; i++) {
			Result[i] = 0;
			for (int j = 0; j < thousand; j++) {
				Result[i] += Matrix[i][j] * Vector[j];
			}
		}
		cout << "M * V = " << (double)(clock() - workTime) / CLOCKS_PER_SEC << "c." << " (" << (double)(clock() - workTime) << ")   ";
		workTime1 += clock() - workTime;
		workTime = clock();
		for (int i = 0; i < thousand; i++) {
			Result[i] = 0;
			for (int j = 0; j < thousand; j++) {
				Result[i] += Vector[j] * Matrix[j][i];
			}
		}
		cout << "V * M = " << (double)(clock() - workTime) / CLOCKS_PER_SEC << "c." << " (" << (double)(clock() - workTime) << ")\n";
		workTime2 += clock() - workTime;
	}
	cout << (double)workTime2 / (double)workTime1 << endl;
	system("pause");
}