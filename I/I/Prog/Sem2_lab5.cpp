#include "pch.h"
#include <iostream>
#include <fstream>
using namespace std;
struct Detail {
	int id;
	double cost;
	Detail* next;
};
struct Employee {
	char firstName[20];
	char lastName[20];
	int idDet;
	double detPerDay;
	Employee* next;
};
void Add(Detail* d, Detail*& list) {
	if (list == NULL) {
		d->next = NULL;
		list = d;
	}
	else {
		d->next = list;
		list = d;
	}
}
void Add(Employee* d, Employee*& list) {
	if (list == NULL) {
		d->next = NULL;
		list = d;
	}
	else {
		d->next = list;
		list = d;
	}
}
int main() {
	bool f = false;
	int i, amountD, amountE;
	double sum = 0;
	ifstream fin("in.txt");
	ofstream fout("out.txt");
	Detail* dList = NULL, *dNow;
	Employee* eList = NULL, *eNow;
	fin >> amountD >> amountE;
	for (i = 0; i < amountD; i++) {
		Detail * d = new Detail;
		fin >> d->id >> d->cost;
		Add(d, dList);
	}
	for (i = 0; i < amountE; i++) {
		Employee* e = new Employee;
		fin >> e->firstName >> e->lastName >> e->idDet >> e->detPerDay;
		Add(e, eList);
	}
	eNow = eList;
	while (1) {
		dNow = dList;
		while (1) {
			if (dNow == NULL) {
				cout << "For " << eNow->firstName << " " << eNow->lastName << "no detail found!" << "\n";
				fout << "For " << eNow->firstName << " " << eNow->lastName << "no detail found!" << "\n";
				eNow = eNow->next;
				f = true;
				break;
			}
			else if (eNow->idDet == dNow->id)
				break;
			dNow = dNow->next;
		}
		if (f) {
			f = false;
			continue;
		}
		cout << "Daily income from " << eNow->firstName << " " << eNow->lastName << " is " << dNow->cost * eNow->detPerDay << "\n";
		fout << "Daily income from " << eNow->firstName << " " << eNow->lastName << " is " << dNow->cost * eNow->detPerDay << "\n";
		sum += dNow->cost * eNow->detPerDay;
		if (eNow->next == NULL)
			break;
		eNow = eNow->next;
	}
	cout << "All daily income: " << sum << "\n";
	fout << "All daily income: " << sum << "\n";
	system("pause");
}