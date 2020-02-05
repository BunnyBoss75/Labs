#include "pch.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <time.h>
using namespace std;
void create(int n) {
	ofstream ofMatrix("Matrix.txt");
	ofstream ofVector("Vector.txt");
	srand(time(NULL));
	int temp1, temp2;
	for (int i = 0; i < n; i++) {
		temp1 = rand() % 3 - 1;
		ofVector.write((char*)&temp1, sizeof(int));
		for (int j = 0; j < n; j++) {
			temp2 = rand() % 3 - 1;
			ofMatrix.write((char*)&temp2, sizeof(int));
		}
	}
}
int *returnVector(int n, int *vector) {
	ifstream ifVector("Vector.txt");
	char *temp = new char[sizeof(int)];
	for (int i = 0; i < n; i++) {
		ifVector.read(temp, sizeof(int));
		vector[i] = *(int*)temp;
	}
	delete temp;
	return vector;
}
int *returnMatrixLine(int n, int numberLine, int* matrixLine) {
	char *temp = new char[sizeof(int)];
	ifstream ifMatrix("Marix.txt");
	ifMatrix.seekg(n * numberLine * sizeof(int));
	for (int i = 0; i < n; i++) {
		ifMatrix.read(temp, sizeof(int));
		matrixLine[i] = *(int*)temp;
	}
	delete temp;
	return matrixLine;
}
int *returnMatrixColumn(int n, int numberColumn, int* matrixColumn) {
	char* temp = new char[sizeof(int)];
	ifstream ifMatrix("Marix.txt");
	ifMatrix.seekg(numberColumn * sizeof(int));
	for (int i = 0; i < n; i++) {
		ifMatrix.read(temp, sizeof(int));
		ifMatrix.seekg(ifMatrix.tellg() + (streampos)(n * sizeof(int)));
		matrixColumn[i] = *(int*)temp;
	}
	delete temp;
	return matrixColumn;
}
int main() {
	int thousand = 10000, count = 10;
	int *result = new int[thousand];
	int startTime, workTime;
	int temp = 0;
	int *matrixPart = new int[thousand];
	int *vector = new int[thousand];
	//create(thousand);
	for (int x = 0; x < count; x++) {
		for (int i = 0; i < thousand; i++) {
			result[i] = 0;
		}
		startTime = clock();
		vector = returnVector(thousand, vector);
		for (int i = 0; i < thousand; i++) {
			matrixPart = returnMatrixLine(thousand, i, matrixPart);
			for (int j = 0; j < thousand; j++) {
				result[i] += matrixPart[j] * vector[j];
			}
		}
		workTime = clock() - startTime;
		cout << "M * V = " << (double)workTime / CLOCKS_PER_SEC << " sec.\n";
		temp += workTime;
		for (int i = 0; i < thousand; i++) {
			result[i] = 0;
		}
		startTime = clock();
		vector = returnVector(thousand, vector);
		for (int i = 0; i < thousand; i++) {
			matrixPart = returnMatrixColumn(thousand, i, matrixPart);
			for (int j = 0; j < thousand; j++) {
				result[i] += vector[j] * matrixPart[j];
			}
		}
		workTime = clock() - startTime;
		cout << "V * M = " << (double)workTime / CLOCKS_PER_SEC << " sec.\n";
		temp += workTime;
	}
	cout << temp << endl;
	system("pause");
}