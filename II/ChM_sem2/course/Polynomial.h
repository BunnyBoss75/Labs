#pragma once

#include <vector>
#include <algorithm>

class Polynomial {
public:
	Polynomial();
	Polynomial(std::initializer_list<double> list);
	Polynomial(int size, double value = 0);
	Polynomial(const std::vector<double>& _polynimial);

	Polynomial(const Polynomial& other);
	Polynomial(Polynomial&& other);

	~Polynomial();

	bool operator == (const Polynomial& other);

	Polynomial& operator=(Polynomial&& other);
	Polynomial& operator=(const Polynomial& other);

	Polynomial operator + (const Polynomial& other);
	Polynomial operator - (const Polynomial& other);
	Polynomial operator * (const Polynomial& other);
	Polynomial operator / (const Polynomial& other);
	Polynomial& operator += (const Polynomial& other);
	Polynomial& operator -= (const Polynomial& other);
	Polynomial& operator *= (const Polynomial& other);
	Polynomial& operator /= (const Polynomial& other);

	Polynomial operator + (double number);
	Polynomial operator - (double number);
	Polynomial operator * (double number);
	Polynomial operator / (double number);
	Polynomial& operator += (double number);
	Polynomial& operator -= (double number);
	Polynomial& operator *= (double number);
	Polynomial& operator /= (double number);

	double calculate(double x);
	void printPolynomial();

	std::vector<double> polynomial;
};