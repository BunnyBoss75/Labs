#pragma once

#include <vector>
#include <map>
#include "Polynomial.h"
 class ChM {
public:
	Polynomial static createRMS(std::map<double, double>& funcRes, double* nodes, int amountNodes, int degreeRMS);
	Polynomial static createNewton(std::map<double, double>& funcRes, double* nodes, int amountNodes, double h);
	Polynomial static createLagrange(std::map<double, double>& funcRes, double* nodes, int amountNodes);

	std::vector<double> static sweep(const std::vector<double>& a, const std::vector<double>& b, const std::vector<double>& c, const std::vector<double>& d, int n);

	std::vector<double> static gauss(std::vector<std::vector<double>> matrix);
	double static finiteDifference(std::map<double, double>& funcRes, double* nodes, int degree);
};

