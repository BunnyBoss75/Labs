#include <iostream>
#include <vector>
#include "Polynomial.h"
#include "ChM.h"
using namespace std;

double func(double x) {
	return log(x) + 3 * log10(x);
}

vector<Polynomial> createSplines(vector<double>& A, vector<double>& B, vector<double>& C, vector<double>& D, double* nodes, int n) {
	vector<Polynomial> result(n, 4); // reserve 4 places for splines coeficients
	for (int i = 0; i < n; ++i) {
		Polynomial temp{ -nodes[i + 1], 1 };
		result[i] += A[i];
		result[i] += temp * B[i];
		temp *= Polynomial{ -nodes[i + 1], 1 };
		result[i] += temp * C[i + 1] / 2;
		temp *= Polynomial{ -nodes[i + 1], 1 };
		result[i] += temp * D[i] / 6;
	}
	return result;
}

double getValueSpline(vector<Polynomial>& splines, double x, double* nodes, int amountNodes, double h) {
	if (x <= nodes[1]) {
		return splines[0].calculate(x);
	}
	else if (x >= nodes[amountNodes - 2]) {
		return splines[splines.size()- 1].calculate(x);
	}
	else {
		return splines[(int)((x - nodes[0]) / h)].calculate(x);
	}
}

int main() {
	// enter data
	double a = 1.1, b = 4, n = 5;
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

	vector<double> splineA(n);
	vector<double> splineB(n);
	vector<double> splineC;
	vector<double> splineD(n);

	// sweep method
	vector<double> sweepA(n - 1, h);
	vector<double> sweepB(n - 1, 4 * h);
	vector<double> sweepC(n - 1, h);
	vector<double> sweepD(n - 1);
	sweepA[0] = 0;
	sweepC[sweepC.size() - 1] = 0;
	for (int i = 0; i < sweepD.size(); ++i) {
		sweepD[i] = 6.0 * (funcRes[nodes[i + 2]] - 2.0 * funcRes[nodes[i + 1]] + funcRes[nodes[i]]) / h;
	}
	splineC = ChM::sweep(sweepA, sweepB, sweepC, sweepD, n - 1);
	splineC.emplace(splineC.begin(), 0);
	splineC.emplace_back(0);

	// generate spline coeficients
	for (int i = 0; i < n; ++i) {
		splineA[i] = funcRes[nodes[i + 1]];
		splineD[i] = (splineC[i + 1] - splineC[i]) / h;
		splineB[i] = h * splineC[i + 1] / 2.0 - h * h * splineD[i] / 6.0 + (funcRes[nodes[i + 1]] - funcRes[nodes[i]]) / h;
	}

	// generate splines
	vector<Polynomial> splines = createSplines(splineA, splineB, splineC, splineD, nodes, n);

	// create other polynomials
	Polynomial lagrange = ChM::createLagrange(funcRes, nodes, n + 1);
	Polynomial newton = ChM::createNewton(funcRes, nodes, n + 1, h);
	vector<Polynomial> rms;
	rms.reserve(n + 1);
	for (int i = 0; i < n + 1; ++i) {
		rms.emplace_back(ChM::createRMS(funcRes, nodes, n + 1, i));
	}
	
	// print results
	double tempValueSplines, tempValueLagrange, tempValueNewton, tempValueRMS;
	printf("coeficients of splines:\n  |     A     |     B     |     C     |     D\n");
	for (int i = 0; i < n; ++i) {
		printf("%d | %9.6f | %9.6f | %9.6f | %9.6f\n",i + 1, splineA[i], splineB[i], splineC[i + 1], splineD[i]);
	}
	printf("\nspline polynomials:\n");
	for (int i = 0; i < n; ++i) {
		printf("%d:\n  ", i);
		splines[i].printPolynomial();
		printf("\n");
	}
	printf("\nother polynomial:\nLagrange:\n  ");
	lagrange.printPolynomial();
	printf("\nNewton:\n  ");
	newton.printPolynomial();
	printf("\nRMS:\n");
	for (int i = 0; i < rms.size(); ++i) {
		printf("m = %d\n  ", i);
		rms[i].printPolynomial();
		printf("\n");
	}
	printf("\nnodes of interpolation:\n    xi    |   f(x)    |    S(x)   |  RnS(x)   |   Ln(x)   |  RnL(x)   |   Nn(x)   |   RnN(x)  | RMS(x) m = n |  RnRMS(x)\n");
	for (int i = 0; i < n + 1; ++i) {
		tempValueSplines = getValueSpline(splines, nodes[i], nodes, n + 1, h);
		tempValueLagrange = lagrange.calculate(nodes[i]);
		tempValueNewton = newton.calculate(nodes[i]);
		tempValueRMS = rms[rms.size() - 1].calculate(nodes[i]);
		printf("%9.6f | %9.6f | %9.6f | %9.6f | %9.6f | %9.6f | %9.6f | %9.6f |  %9.6f   | %9.6f\n",
			nodes[i], funcRes[nodes[i]], tempValueSplines, abs(funcRes[nodes[i]] - tempValueSplines), tempValueLagrange, abs(funcRes[nodes[i]] - tempValueLagrange),
			tempValueNewton, abs(funcRes[nodes[i]] - tempValueNewton), tempValueRMS, abs(funcRes[nodes[i]] - tempValueRMS));
	}
	printf("\nintermediate nodes:\n    xj    |   f(x)    |    S(x)   |  RnS(x)   |   Ln(x)   |  RnL(x)   |   Nn(x)   |   RnN(x)  | RMS(x) m = n |  RnRMS(x)\n");
	for (int i = 0; i < n + 2; ++i) {
		tempValueSplines = getValueSpline(splines, secondNodes[i], nodes, n + 1, h);
		tempValueLagrange = lagrange.calculate(secondNodes[i]);
		tempValueNewton = newton.calculate(secondNodes[i]);
		tempValueRMS = rms[rms.size() - 1].calculate(secondNodes[i]);
		printf("%9.6f | %9.6f | %9.6f | %9.6f | %9.6f | %9.6f | %9.6f | %9.6f |  %9.6f   | %9.6f\n",
			secondNodes[i], funcRes[secondNodes[i]], tempValueSplines, abs(funcRes[secondNodes[i]] - tempValueSplines), tempValueLagrange,
			abs(funcRes[secondNodes[i]] - tempValueLagrange), tempValueNewton, abs(funcRes[secondNodes[i]] - tempValueNewton), tempValueRMS, abs(funcRes[secondNodes[i]] - tempValueRMS));
	}
	printf("\ncomparison of accuracy at different m:\nnodes of interpolation:\n    xi        f(x)        ");
	for (int i = 0; i < n + 1; ++i) {
		printf("      m = %d             ", i);
	}
	printf("\n                      ");
	for (int i = 0; i < n + 1; ++i) {
		printf("|   RMS(x)  |  RnRMS(x) ");
	}
	printf("\n");
	for (int i = 0; i < n + 1; ++i) {
		printf("%9.6f | %9.6f", nodes[i], funcRes[nodes[i]]);
		for (int j = 0; j < n + 1; ++j) {
			tempValueRMS = rms[j].calculate(nodes[i]);
			printf(" | %9.6f | %9.6f", tempValueRMS, abs(funcRes[nodes[i]] - tempValueRMS));
		}
		printf("\n");
	}
	printf("\nintermediate nodes:\n    xj        f(x)        ");
	for (int i = 0; i < n + 1; ++i) {
		printf("      m = %d             ", i);
	}
	printf("\n                      ");
	for (int i = 0; i < n + 1; ++i) {
		printf("|   RMS(x)  |  RnRMS(x) ");
	}
	printf("\n");
	for (int i = 0; i < n + 2; ++i) {
		printf("%9.6f | %9.6f", secondNodes[i], funcRes[secondNodes[i]]);
		for (int j = 0; j < n + 1; ++j) {
			tempValueRMS = rms[j].calculate(secondNodes[i]);
			printf(" | %9.6f | %9.6f", tempValueRMS, abs(funcRes[secondNodes[i]] - tempValueRMS));
		}
		printf("\n");
	}

	delete[] nodes;
	delete[] secondNodes;
}