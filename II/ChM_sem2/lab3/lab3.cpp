#include <iostream>
#include "Polynomial.h"
#include "ChM.h"
#include "Matrix.h"
using namespace std;

int amountIteration = 0;

bool prepareMatrix(Matrix& system, Matrix& vectorFreeMember) {
	Matrix transposed = system.getTransposed();
	system = transposed * system;
	vectorFreeMember = transposed * vectorFreeMember.getTransposed();
	vectorFreeMember.transpose();
	return system.getDeterminante() != 0;
}
double getMatrixNorm(const Matrix& matrix) {
	double result = 0;
	double tempMaxValue = 0;
	for (int i = 0; i < matrix.getHeight(); ++i) {
		tempMaxValue = 0;
		for (int j = 0; j < matrix.getHeight(); ++j) {
			if (abs(matrix[i][j]) > tempMaxValue) {
				tempMaxValue = abs(matrix[i][j]);
			}
		}
		result += tempMaxValue;
	}
	return result;
}
vector<double> calculateResidualsVector(Matrix& system, Matrix& vectorFreeMember, Matrix& x) {
	vector<double> result(system.getHeight());
	double tempResult;
	for (int i = 0; i < result.size(); ++i) {
		tempResult = 0;
		for (int j = 0; j < x.getWidth(); ++j) {
			tempResult += system[i][j] * x[0][j];
		}
		result[i] = vectorFreeMember[0][i] - tempResult;
	}
	return result;
}
vector<double> calculateResidualsVector(Matrix& system, Matrix& vectorFreeMember, vector<double>& x) {
	vector<double> result(system.getHeight());
	double tempResult;
	for (int i = 0; i < result.size(); ++i) {
		tempResult = 0;
		for (int j = 0; j < x.size(); ++j) {
			tempResult += system[i][j] * x[j];
		}
		result[i] = vectorFreeMember[0][i] - tempResult;
	}
	return result;
}
Matrix createMatrixS_SRM(const Matrix& system) {
	Matrix result(system.getHeight(), system.getWidth(), 0);
	for (int i = 0; i < result.getHeight(); ++i) {
		{
			double tempSum = 0;
			for (int k = 0; k < i; ++k) {
				tempSum += result[k][i] * result[k][i];
			}
			result[i][i] = sqrt(system[i][i] - tempSum);
		}
		for (int j = i + 1; j < result.getWidth(); ++j) {
			double tempSum = 0;
			for (int k = 0; k < i; ++k) {
				tempSum += result[k][i] * result[k][j];
			}
			result[i][j] = (system[i][j] - tempSum) / result[i][i];
		}
	}
	return result;
}
vector<double> calculateResult_SRM(Matrix& S, Matrix& vectorFreeMember, int amountX) {
	vector<double> y(amountX);
	y[0] = vectorFreeMember[0][0] / S[0][0];
	for (int i = 1; i < y.size(); ++i) {
		double tempSum = 0;
		for (int k = 0; k < i; ++k) {
			tempSum += S[k][i] * y[k];
		}
		y[i] = (vectorFreeMember[0][i] - tempSum) / S[i][i];
	}
	vector<double> x(amountX);
	x[amountX - 1] = y[amountX - 1] / S[amountX - 1][amountX - 1];
	for (int i = amountX - 2; i > -1; --i) {
		double tempSum = 0;
		for (int k = i + 1; k < amountX; ++k) {
			tempSum += S[i][k] * x[k];
		}
		x[i] = (y[i] - tempSum) / S[i][i];
	}
	return x;
}
vector<double> SRM(const Matrix& system, Matrix& vectorFreeMember, int amountX) {
	Matrix S = createMatrixS_SRM(system);
	vector<double> X = calculateResult_SRM(S, vectorFreeMember, amountX);
	return X;
}
void iteration_SIM(Matrix& system, Matrix& x, Matrix& vectorFreeeMember, Matrix& E, double alpha) {
	x = (E - (system * alpha)) * x.getTransposed() + vectorFreeeMember.getTransposed() * alpha;
	x.transpose();
}
vector<double> SIM(Matrix& system, Matrix& vectorFreeMember, int amountX, double epsilon) {
	double matrixNorm = getMatrixNorm(system);
	Matrix x(1, amountX, 0);
	Matrix E = Matrix::createUnitMatrix(amountX);
	double alpha = 1.0 / matrixNorm; 
	while (true) {
		iteration_SIM(system, x, vectorFreeMember, E, alpha);
		++amountIteration;
		vector<double> residualsVector = calculateResidualsVector(system, vectorFreeMember, x);
		double maxError = 0;
		for (int i = 0; i < residualsVector.size(); ++i) {
			if (maxError < residualsVector[i]) {
				maxError = residualsVector[i];
			}
		}
		if (maxError < epsilon) {
			break;
		}
	}
	return x.getVector();
}

int main() {
	// enter data
	double** pointerSystem = new double*[3];
	double** pointerFreeMember = new double*[1];
	pointerFreeMember[0] = new double[3]{ 0.8, 5.7, 3.2 };
	pointerSystem[0] = new double[3]{ 3.3, 2.1, 2.8 };
	pointerSystem[1] = new double[3]{ 4.1, 3.7, 4.8 };
	pointerSystem[2] = new double[3]{ 2.7, 1.8, 1.1 };
	Matrix system(pointerSystem, 3, 3);
	Matrix vectorFreeMember(pointerFreeMember, 1, 3);
	int amountX = system.getWidth();
	double epsilon = 0.0004055;

	// prepare matrix
	Matrix systemPrepared = system;
	Matrix vectorFreeMemberPrepared = vectorFreeMember;
	prepareMatrix(systemPrepared, vectorFreeMemberPrepared);
	// SRM - squere root method
	vector<double> X_SRM = SRM(systemPrepared, vectorFreeMemberPrepared, amountX);

	// SIM - simple iteration method
	vector<double> X_SIM = SIM(systemPrepared, vectorFreeMemberPrepared, amountX, epsilon);

	// gauss for test
	vector<vector<double>> systemVector = system.getVectorOfVectors();
	for (int i = 0; i < systemVector.size(); ++i) {
		systemVector[i].push_back(vectorFreeMember[0][i]);
	}
	vector<double> X_Gauss = ChM::gauss(systemVector);
	
	// calculate residuals vector
	vector<double> residualsVector_SRM = calculateResidualsVector(system, vectorFreeMember, X_SRM);
	vector<double> residualsVector_SIM = calculateResidualsVector(system, vectorFreeMember, X_SIM);
	vector<double> residualsVector_Gauss = calculateResidualsVector(system, vectorFreeMember, X_Gauss);

	// print result
	printf("Method                ");
	for (int i = 0; i < amountX; ++i) {
		printf("|    x%d     ", i);
	}
	printf("\nSRM                   ");
	for (int i = 0; i < amountX; ++i) {
		printf("| %9.6f ", X_SRM[i]);
	}
	printf("\nSRM ResidualsVector   ");
	for (int i = 0; i < amountX; ++i) {
		printf("| %9.6f ", residualsVector_SRM[i]);
	}
	printf("\nSIM                   ");
	for (int i = 0; i < amountX; ++i) {
		printf("| %9.6f ", X_SIM[i]);
	}
	printf("\nSIM ResidualsVector   ");
	for (int i = 0; i < amountX; ++i) {
		printf("| %9.6f ", residualsVector_SIM[i]);
	}
	printf("\nGauss                 ");
	for (int i = 0; i < amountX; ++i) {
		printf("| %9.6f ", X_Gauss[i]);
	}
	printf("\nGauss ResidualsVector ");
	for (int i = 0; i < amountX; ++i) {
		printf("| %9.6f ", residualsVector_Gauss[i]);
	}
	printf("\nk - %d\n", amountIteration);
}