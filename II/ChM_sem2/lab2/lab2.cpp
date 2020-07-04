#include <iostream>
#include <map>
#include <vector>
using namespace std;

double func(double x) {
	return log(x) + 3 * log10(x);
}
double funcTest1(double x) {
	return 1;
}
double funcTest2(double x) {
	return x;
}
double funcTest3(double x) {
	return x * x * x;
}
double funcTest4(double x) {
	// x^11
	return x * x * x * x * x * x * x * x * x * x * x;
}

double leftQuadratureShape(double h, const map<double, double>& funcRes, double* nodes, int n) {
	double sum = 0;
	for (int i = 0; i < n; ++i) {
		sum += funcRes.at(nodes[i]);
	}
	return sum * h;
}

double rightQuadratureShape(double h, const map<double, double>& funcRes, double* nodes, int n) {
	double sum = 0;
	for (int i = 1; i < n + 1; ++i) {
		sum += funcRes.at(nodes[i]);
	}
	return sum * h;
}

double centralQuadratureShape(double h, const map<double, double>& funcRes, double* nodes, int n) {
	double sum = 0;
	for (int i = 0; i < n; ++i) {
		sum += funcRes.at(nodes[i] + h / 2);
	}
	return sum * h;
}

double trapezeQuadratureShape(double h, const map<double, double>& funcRes, double* nodes, int n) {
	double sum = funcRes.at(nodes[0]);
	for (int i = 1; i < n; ++i) {
		sum += 2 * funcRes.at(nodes[i]);
	}
	sum += funcRes.at(nodes[n]);
	return sum * h / 2;
}

double simpsonQuadratureShape(double h, const map<double, double>& funcRes, double* nodes, int n) {
	double sum = 0;
	for (int i = 0; i < n; ++i) {
		sum += (funcRes.at(nodes[i]) + 4 * funcRes.at(nodes[i] + h / 2) + funcRes.at(nodes[i + 1])) * h / 6.0;
	}
	return sum;
}

// there are need another nodes 
double gaussQuadratureShape(double (*_func)(double), int n, double a, double b) {
	if (n == 5) {
		double A[6] = { 0.17132449237917034504, 0.36076157304813860756, 0.46791393457269104738, 0.46791393457269104738, 0.36076157304813860756, 0.17132449237917034504 };
		double t[6] = { -0.93246951420315202781, -0.66120938646626451366, -0.23861918608319690863, 0.23861918608319690863, 0.66120938646626451366, 0.93246951420315202781 };
		double sum = 0;
		for (int i = 0; i < n + 1; ++i) {
			sum += A[i] * _func((a + b) / 2 + (b - a) * t[i] / 2);
		}
		return sum * (b - a) / 2;
	}
	else {
		throw "it isn't available";
	}

}

int main() {
	// enter data
	vector<double(*)(double)> functions{ func, funcTest1, funcTest2, funcTest3, funcTest4 };
	double a = 1.1, b = 4, n = 5;
	double h = (b - a) / n;
	double* nodes = new double[n + 1];
	map<double, double> funcRes;
	double currentResult;

	double resultToCheck[5] {
		5.8500982890504,
		2.9,
		7.395,
		63.633975,
		1398101.0717976351734
	};

	for (int j = 0; j < functions.size(); ++j) {
		// prepare data to current function
		for (int i = 0; i < n + 1; ++i) {
			nodes[i] = a + h * i;
			funcRes.emplace(nodes[i], functions[j](nodes[i]));
		}
		for (int i = 0; i < n; ++i) {
			funcRes.emplace(nodes[i] + h / 2, functions[j](nodes[i] + h / 2));
		}
		// calculate and print result
		currentResult = leftQuadratureShape(h, funcRes, nodes, n);
		switch (j) {
		case 0:
			printf("f(x):\n");
			break;
		case 1:
			printf("y = 1\n");
			break;
		case 2:
			printf("y = x\n");
			break;
		case 3:
			printf("y = x^3\n");
			break;
		case 4:
			printf("y = x^11\n");
			break;
		}
		printf("func: %.5f\nleft: %.5f, R(x): %.5f\n", resultToCheck[j], currentResult, abs(currentResult - resultToCheck[j]));
		currentResult = rightQuadratureShape(h, funcRes, nodes, n);
		printf("right: %.5f, R(x): %.5f\n", currentResult, abs(currentResult - resultToCheck[j]));
		currentResult = centralQuadratureShape(h, funcRes, nodes, n);
		printf("central: %.5f, R(x): %.5f\n", currentResult, abs(currentResult - resultToCheck[j]));
		currentResult = trapezeQuadratureShape(h, funcRes, nodes, n);
		printf("trapeze: %.5f, R(x): %.5f\n", currentResult, abs(currentResult - resultToCheck[j]));
		currentResult = simpsonQuadratureShape(h, funcRes, nodes, n);
		printf("simpson: %.5f, R(x): %.5f\n", currentResult, abs(currentResult - resultToCheck[j]));
		currentResult = gaussQuadratureShape(functions[j], n, a, b);
		printf("gauss: %.5f, R(x): %.5f\n\n", currentResult, abs(currentResult - resultToCheck[j]));

		funcRes.clear();
	}
	delete[] nodes;
}