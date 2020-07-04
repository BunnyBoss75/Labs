#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include "Polynomial.h"		
using namespace std;

double func(double x) {
	//return log(x) + 3 * log10(x);
	return x * x;
}

vector<double> gauss(vector<vector<double>> matrix) {
	double diagonal_element, flag;
	int row_num = matrix.size();
	int col_num = matrix[0].size();
	for (int i = 0; i < row_num; i++) {
		for (int j = 0; j < col_num; j++) {
			if (i == j) {
				int large_pivot_row = i;
				for (int k = i; k < row_num; ++k) {
					if (matrix[k][j] > matrix[large_pivot_row][j]) {
						large_pivot_row = k;
					}
				}
				if (i != large_pivot_row) {
					for (int k = 0; k < col_num; k++) {
						swap(matrix[large_pivot_row][k], matrix[i][k]);
					}
				}
				diagonal_element = matrix[i][j];
				for (int l = 0; l < col_num; l++) {
					matrix[i][l] /= diagonal_element;
				}
				for (int k = 0; k < row_num; k++) {
					flag = matrix[k][j];
					if (k != i) {
						for (int l = 0; l < col_num; l++) {
							matrix[k][l] = (matrix[k][l]) - flag * (matrix[i][l]);
						}
					}

				}
			}
		}
	}
	vector<double> result;
	for (int i = 0; i < row_num; i++) {
		result.push_back(matrix[i][col_num - 1]);
	}
	return result;
}

Polynomial createRMS(map<double, double>& funcRes, double* nodes, int amountNodes, int degreeRMS) {
	vector<vector<double>> matrixCoef;
	matrixCoef.reserve(degreeRMS + 1);
	for (int i = 0; i < degreeRMS + 1; ++i) {
		matrixCoef.emplace_back(degreeRMS + 2);
	}
	double tempCoef;
	for (int i = 0; i < degreeRMS + 1; ++i) {
		for (int j = 0; j < degreeRMS + 1; ++j) {
			for (int k = 0; k < amountNodes; ++k) {
				tempCoef = 1;
				for (int x = 0; x < i + j; ++x) {
					tempCoef *= nodes[k];
				}
				matrixCoef[i][j] += tempCoef;
			}
		}
		for (int j = 0; j < amountNodes; ++j) {
			tempCoef = funcRes[nodes[j]];
			for (int k = 0; k < i; ++k) {
				tempCoef *= nodes[j];
			}
			matrixCoef[i][degreeRMS + 1] += tempCoef;
		}
	}
	return gauss(matrixCoef);
}

double finiteDifference(map<double, double>& funcRes, double* nodes, int degree) {
	double result = funcRes[nodes[degree]];
	double combination = 1;
	for (int i = 1; i < degree + 1; ++i) {
		combination /= -i;
		combination *= 1.0 + degree - i;
		result += funcRes[nodes[degree - i]] * combination;
	}
	return result;
}

Polynomial createNewton(map<double, double>& funcRes, double* nodes, int amountNodes, double h) {
	Polynomial result{ funcRes[nodes[0]] };
	Polynomial t{ -nodes[0] / h + 1, 1 / h };
	Polynomial tMultiplication{ 1 };
	double fuct = 1;
	for (int i = 1; i < amountNodes; ++i) {
		t -= 1;
		tMultiplication *= t;
		fuct *= i;
		result += tMultiplication * (finiteDifference(funcRes, nodes, i) / fuct);
	}
	return result;
}

Polynomial createLagrange(map<double, double>& funcRes, double* nodes, int amountNodes) {
	Polynomial result(amountNodes);
	Polynomial temp;
	for (int i = 0; i < amountNodes; ++i) {
		temp = Polynomial(1, 1);
		for (int j = 0; j < amountNodes; ++j) {
			if (j != i) {
				temp *= Polynomial{ -nodes[j], 1 } / (nodes[i] - nodes[j]);
			}
		}
		temp *= funcRes[nodes[i]];
		result += temp;
	}
	return result;
}

int main() {
	// enter data
	double a = 1, b = 4, n = 3;
	double h = (b - a) / n;
	double* nodes = new double[n + 1];
	double* secondNodes = new double[n + 2];
	map<double, double> funcRes;
	for (int i = 0; i < n + 1; ++i) {
		nodes[i] = a + h * i;
		funcRes.emplace(nodes[i], func(nodes[i]));
	}
	for (int i = 0; i < n + 2; ++i) {
		secondNodes[i] = a + (2.0 * i - 1) / 2.0 * h;
		funcRes.emplace(secondNodes[i], func(secondNodes[i]));
	}
	// generate all polynomials
	Polynomial lagrange = createLagrange(funcRes, nodes, n + 1);
	Polynomial newton = createNewton(funcRes, nodes, n + 1, h);
	Polynomial rms = createRMS(funcRes, nodes, n + 1, n);
	// show result
	double funcValue, polynomValue;
	printf("lagrange: P(x) = % 3.10f ", lagrange.polynomial[0]);
	for (int i = 1; i < n + 1; ++i) {
		if (lagrange.polynomial[i] >= 0) {
			cout << "+ ";
		}
		printf("% 3.10f x^%d ", lagrange.polynomial[i], i);
	}
	cout << endl;
	for (int i = 0; i < n + 1; ++i) {
		funcValue = funcRes[nodes[i]];
		polynomValue = lagrange.calculate(nodes[i]);
		printf("x: % 2.5f, f(x): % 2.5f, P(x): % 2.5f, R(x): % 2.5f\n", nodes[i], funcValue, polynomValue, abs(funcValue - polynomValue));
	}
	cout << endl;
	for (int i = 0; i < n + 2; ++i) {
		funcValue = funcRes[secondNodes[i]];
		polynomValue = lagrange.calculate(secondNodes[i]);
		printf("x: % 2.5f, f(x): % 2.5f, P(x): % 2.5f, R(x): % 2.5f\n", secondNodes[i], funcValue, polynomValue, abs(funcValue - polynomValue));
	}
	cout << endl;
	printf("newton: P(x) = % 3.10f ", newton.polynomial[0]);
	for (int i = 1; i < n + 1; ++i) {
		if (newton.polynomial[i] >= 0) {
			cout << "+ ";
		}
		printf("% 3.10f x^%d ", newton.polynomial[i], i);
	}
	cout << endl;
	for (int i = 0; i < n + 1; ++i) {
		funcValue = funcRes[nodes[i]];
		polynomValue = newton.calculate(nodes[i]);
		printf("x: % 2.5f, f(x): % 2.5f, P(x): % 2.5f, R(x): % 2.5f\n", nodes[i], funcValue, polynomValue, abs(funcValue - polynomValue));
	}
	cout << endl;
	for (int i = 0; i < n + 2; ++i) {
		funcValue = funcRes[secondNodes[i]];
		polynomValue = newton.calculate(secondNodes[i]);
		printf("x: % 2.5f, f(x): % 2.5f, P(x): % 2.5f, R(x): % 2.5f\n", secondNodes[i], funcValue, polynomValue, abs(funcValue - polynomValue));
	}
	cout << endl;
	printf("rms: P(x) = % 3.10f ", rms.polynomial[0]);
	for (int i = 1; i < n + 1; ++i) {
		if (rms.polynomial[i] >= 0) {
			cout << "+ ";
		}
		printf("% 3.10f x^%d ", rms.polynomial[i], i);
	}
	cout << endl;
	for (int i = 0; i < n + 1; ++i) {
		funcValue = funcRes[nodes[i]];
		polynomValue = rms.calculate(nodes[i]);
		printf("x: % 2.5f, f(x): % 2.5f, P(x): % 2.5f, R(x): % 2.5f\n", nodes[i], funcValue, polynomValue, abs(funcValue - polynomValue));
	}
	cout << endl;
	for (int i = 0; i < n + 2; ++i) {
		funcValue = funcRes[secondNodes[i]];
		polynomValue = rms.calculate(secondNodes[i]);
		printf("x: % 2.5f, f(x): % 2.5f, P(x): % 2.5f, R(x): % 2.5f\n", secondNodes[i], funcValue, polynomValue, abs(funcValue - polynomValue));
	}
	cout << endl;
}