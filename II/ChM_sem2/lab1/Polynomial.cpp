#include "Polynomial.h"

Polynomial::Polynomial() : polynomial(0) {}

Polynomial::Polynomial(std::initializer_list<double> init) : polynomial(init) {}

Polynomial::Polynomial(int size, double value) : polynomial(size, value) {}

Polynomial::Polynomial(const std::vector<double>& _polynimial): polynomial(_polynimial) {}

Polynomial::Polynomial(const Polynomial& other) : polynomial(other.polynomial) {}

Polynomial::Polynomial(Polynomial&& other) : polynomial(move(other.polynomial)) {}

Polynomial::~Polynomial() {}



bool Polynomial::operator==(const Polynomial& other) {
	return this->polynomial == other.polynomial;
}

Polynomial& Polynomial::operator=(Polynomial&& other) {
	this->polynomial = move(other.polynomial);
	return *this;
}

Polynomial& Polynomial::operator=(const Polynomial& other){
	this->polynomial = other.polynomial;
	return *this;
}

Polynomial Polynomial::operator+(const Polynomial& other) {
	Polynomial result(0);
	if (this->polynomial.size() < other.polynomial.size()) {
		result = other;
		for (int i = 0; i < this->polynomial.size(); ++i) {
			result.polynomial[i] += this->polynomial[i];
		}
	}
	else {
		result = *this;
		for (int i = 0; i < other.polynomial.size(); ++i) {
			result.polynomial[i] += other.polynomial[i];
		}
	}
	return result;
}

Polynomial Polynomial::operator-(const Polynomial& other) {
	Polynomial result(0);
	if (this->polynomial.size() < other.polynomial.size()) {
		result = other;
		for (int i = 0; i < this->polynomial.size(); ++i) {
			result.polynomial[i] -= this->polynomial[i];
		}
	}
	else {
		result = *this;
		for (int i = 0; i < other.polynomial.size(); ++i) {
			result.polynomial[i] -= other.polynomial[i];
		}
	}
	return result;
}

Polynomial Polynomial::operator*(const Polynomial& other){
	Polynomial result(this->polynomial.size() + other.polynomial.size() - 1);
	for (int i = 0; i < this->polynomial.size(); ++i) {
		for (int j = 0; j < other.polynomial.size(); ++j) {
			result.polynomial[i + j] += this->polynomial[i] * other.polynomial[j];
		}
	}
	return result;
}

Polynomial Polynomial::operator/(const Polynomial& other) {
	int sizeThis = this->polynomial.size();
	int sizeOther = other.polynomial.size();
	int sizeResult = sizeThis - sizeOther + 1;
	Polynomial result(sizeResult);
	Polynomial temp(sizeOther);
	for (int j = 0; j < sizeOther; ++j) {
		temp.polynomial[j] = this->polynomial[sizeThis - sizeOther + j];
	}
	for (int i = sizeResult - 1; i > -1; --i) {
		result.polynomial[i] = temp.polynomial[sizeOther - 1] / other.polynomial[sizeOther - 1];
		if (i == 0) {
			continue;
		}
		for (int j = sizeOther - 1; j > 0; --j) {
			temp.polynomial[j] = temp.polynomial[j - 1] - result.polynomial[i] * other.polynomial[j - 1];
		}
		temp.polynomial[0] = this->polynomial[sizeThis - sizeOther - sizeResult + i];
	}
	return result;
}

Polynomial& Polynomial::operator+=(const Polynomial& other) {
	int deltaDegree = this->polynomial.size() - other.polynomial.size();
	if (deltaDegree < 0) {
		this->polynomial.reserve(-deltaDegree);
		for (int i = 0; i < -deltaDegree; ++i) {
			this->polynomial.push_back(0);
		}
	}
	for (int i = 0; i < other.polynomial.size(); ++i) {
		this->polynomial[i] += other.polynomial[i];
	}
	return *this;
}

Polynomial& Polynomial::operator-=(const Polynomial& other) {
	int deltaDegree = this->polynomial.size() - other.polynomial.size();
	if (deltaDegree < 0) {
		this->polynomial.reserve(-deltaDegree);
		for (int i = 0; i < deltaDegree; ++i) {
			this->polynomial.push_back(0);
		}
	}
	for (int i = 0; i < other.polynomial.size(); ++i) {
		this->polynomial[i] -= other.polynomial[i];
	}
	return *this;
}

Polynomial& Polynomial::operator*=(const Polynomial& other) {
	this->polynomial = this->operator*(other).polynomial;
	return *this;
}

Polynomial& Polynomial::operator/=(const Polynomial& other) {
	this->polynomial = this->operator/(other).polynomial;
	return *this;
}

Polynomial Polynomial::operator+(double number) {
	Polynomial result(*this);
	result.polynomial[0] += number;
	return result;
}

Polynomial Polynomial::operator-(double number) {
	Polynomial result(*this);
	result.polynomial[0] -= number;
	return result;
}

Polynomial Polynomial::operator*(double number) {
	Polynomial result(*this);
	for (int i = 0; i < result.polynomial.size(); ++i) {
		result.polynomial[i] *= number;
	}
	return result;
}

Polynomial Polynomial::operator/(double number) {
	Polynomial result(*this);
	for (int i = 0; i < result.polynomial.size(); ++i) {
		result.polynomial[i] /= number;
	}
	return result;
}

Polynomial& Polynomial::operator+=(double number) {
	this->polynomial[0] += number;
	return *this;
}

Polynomial& Polynomial::operator-=(double number) {
	this->polynomial[0] -= number;
	return *this;
}

Polynomial& Polynomial::operator*=(double number) {
	for (int i = 0; i < this->polynomial.size(); ++i) {
		this->polynomial[i] *= number;
	}
	return *this;
}

Polynomial& Polynomial::operator/=(double number) {
	for (int i = 0; i < this->polynomial.size(); ++i) {
		this->polynomial[i] /= number;
	}
	return *this;
}

double Polynomial::calculate(double x) {
	double result = this->polynomial[0];
	double temp = 1;
	for (int i = 1; i < this->polynomial.size(); ++i) {
		temp *= x;
		result += temp * this->polynomial[i];
	}
	return result;
}