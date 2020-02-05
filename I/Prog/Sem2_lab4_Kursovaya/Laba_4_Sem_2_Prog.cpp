#include "pch.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
using namespace std;
struct student {
	char number[58];
	char firstName[20];
	char lastName[20];
	double grade[8];
};
struct g {
	char number[58];
};
int main() {
	int i, j;
	double coef[8], score, passing;
	vector <double> v[8];
	vector <g> good;
	g g1;
	student s;
	ifstream fin("in.txt");
	ofstream fout("out.txt");
	cout << "Please enter passing grade: ";
	cin >> passing;
	if (!fin)
		cout << "Unable to open file in.txt";
	else if (!fout)
		cout << "Unable to open file out.txt";
	else {
		cout << "\nWrite to file:\n";
		for (i = 0; i < 8; i++)
			fin >> coef[i];
		while (!fin.eof()) {
			score = 0;
			fin >> s.number;
			fin >> s.firstName;
			fin >> s.lastName;
			for (i = 0; i < 8; i++) {
				fin >> s.grade[i];
				v[i].push_back(s.grade[i] * coef[i]);
				if (s.grade[i] > 2)
					score += s.grade[i] * coef[i];
			}
			if (score > passing) {
				strcpy_s(g1.number, s.number);
				strcat_s(g1.number, " ");
				strcat_s(g1.number, s.firstName);
				strcat_s(g1.number, " ");
				strcat_s(g1.number, s.lastName);
				good.push_back(g1);
			}
			fout << s.firstName << " " << s.lastName << " " << score << "\n";
			cout << s.firstName << " " << s.lastName << " " << score << "\n";
		}
		fout << "Student numbers with a passing grade:\n";
		cout << "Student numbers with a passing grade:\n";
		for (i = 0; i < good.size(); i++) {
			fout << good[i].number << "\n";
			cout << good[i].number << "\n";
		}
		for (i = 0; i < 8; i++) {
			score = 0;
			for (j = 0; j < v[0].size(); j++)
				if (v[i][j] / coef[i] < 3)
					score++;
			fout << "Percentage of not solving the task #" << i + 1 << ": " << score * 100.0 / v[0].size() << "\n";
			cout << "Percentage of not solving the task #" << i + 1 << ": " << score * 100.0 / v[0].size() << "\n";
		}
		for (i = 0; i < 8; i++) {
			fout << "Vector of task #" << i + 1 << ": ";
			cout << "Vector of task #" << i + 1 << ": ";
			for (j = 0; j < v[0].size(); j++) {
				fout << v[i][j] << " ";
				cout << v[i][j] << " ";

			}
			fout << "\n";
			cout << "\n";
		}
		fin.close();
		fout.close();
	}
}