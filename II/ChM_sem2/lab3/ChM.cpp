#include "ChM.h"

std::vector<double> ChM::gauss(std::vector<std::vector<double>> matrix) {
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
						std::swap(matrix[large_pivot_row][k], matrix[i][k]);
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
	std::vector<double> result;
	for (int i = 0; i < row_num; i++) {
		result.push_back(matrix[i][col_num - 1]);
	}
	return result;
}

Polynomial ChM::createRMS(std::map<double, double>& funcRes, double* nodes, int amountNodes, int degreeRMS) {
	std::vector<std::vector<double>> matrixCoef;
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

double ChM::finiteDifference(std::map<double, double>& funcRes, double* nodes, int degree) {
	double result = funcRes[nodes[degree]];
	double combination = 1;
	for (int i = 1; i < degree + 1; ++i) {
		combination /= -i;
		combination *= 1.0 + degree - i;
		result += funcRes[nodes[degree - i]] * combination;
	}
	return result;
}

Polynomial ChM::createNewton(std::map<double, double>& funcRes, double* nodes, int amountNodes, double h) {
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

Polynomial ChM::createLagrange(std::map<double, double>& funcRes, double* nodes, int amountNodes) {
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

std::vector<double> ChM::sweep(const std::vector<double>& a, const std::vector<double>& b, const std::vector<double>& c, const std::vector<double>& d, int n) {
	// a - lower diagonal
	// b - main diagonal
	// c - upper diagnoal
	// d - constant terms
	std::vector<double> A(n);
	std::vector<double> B(n);
	std::vector<double> p(n);
	std::vector<double> x(n);
	A[0] = -c[0] / b[0];
	B[0] = d[0] / b[0];
	for (int i = 1; i < n; ++i) {
		p[i] = a[i] * A[i - 1] + b[i];
		A[i] = -c[i] / p[i];
		B[i] = (d[i] - a[i] * B[i - 1]) / p[i];
	}
	x[n - 1] = (d[n - 1] - a[n - 1] * B[n - 2]) / (a[n - 1] * A[n - 2] + b[n - 1]);
	for (int i = n - 2; i > -1; i--) {
		x[i] = A[i + 1] * x[i + 1] + B[i + 1];
	}
	return x;
}
