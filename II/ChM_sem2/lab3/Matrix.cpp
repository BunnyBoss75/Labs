#include "Matrix.h"

Matrix::Matrix(): epsilon(10e-8), height(0), width(0), matrix(nullptr) {}

Matrix::Matrix(const Matrix& other): epsilon(other.epsilon), height(other.height), width(other.width) {
	matrix = new double* [height];
	for (int i = 0; i < height; ++i) {
		matrix[i] = new double[width];
		for (int j = 0; j < width; ++j) {
			matrix[i][j] = other.matrix[i][j];
		}
	}
}

Matrix::Matrix(Matrix&& other): epsilon(other.epsilon), height(other.height), width(other.width), matrix(other.matrix) {
	other.height = 0;
	other.width = 0;
	other.matrix = nullptr;
}

Matrix::Matrix(double**& pointer, int _height, int _width): epsilon(10e-8), height(_height), width(_width), matrix(pointer){
	pointer = nullptr;
}

Matrix::Matrix(int _height, int _width): epsilon(10e-8), height(_height), width(_width) {
	matrix = new double* [height];
	for (int i = 0; i < height; ++i) {
		matrix[i] = new double[width];
	}
}

Matrix::Matrix(int _height, int _width, double value): epsilon(10e-8), height(_height), width(_width) {
	matrix = new double* [height];
	for (int i = 0; i < height; ++i) {
		matrix[i] = new double[width];
		for (int j = 0; j < width; ++j) {
			matrix[i][j] = value;
		}
	}
}

Matrix::~Matrix() {
	for (int i = 0; i < height; ++i) {
		delete matrix[i];
	}
	delete matrix;
}

Matrix& Matrix::operator=(const Matrix& rhs) {
	this->~Matrix();
	epsilon = rhs.epsilon;
	height = rhs.height;
	width = rhs.width;
	matrix = new double* [height];
	for (int i = 0; i < height; ++i) {
		matrix[i] = new double[width];
		for (int j = 0; j < width; ++j) {
			matrix[i][j] = rhs.matrix[i][j];
		}
	}
	return *this;
}

Matrix& Matrix::operator=(Matrix&& rhs) {
	this->~Matrix();

	epsilon = rhs.epsilon;
	height = rhs.height;
	width = rhs.width;
	matrix = rhs.matrix;

	rhs.height = 0;
	rhs.width = 0;
	rhs.matrix = nullptr;

	return *this;
}

bool Matrix::operator==(const Matrix& rhs) {
	if (height == rhs.height && width == rhs.width) {
		for (int i = 0; i < height; ++i) {
			for (int j = 0; j < width; ++j) {
				if (abs(matrix[i][j]) - abs(rhs.matrix[i][j]) >= epsilon) {
					return false;
				}
			}
		}
		return true;
	}
	else {
		return false;
	}
}

Matrix Matrix::operator+(const Matrix& rhs) {
	if (height != rhs.height || width != rhs.width) {
		throw "matrix dimensions are not equal";
	}
	Matrix result(height, width);
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			result[i][j] = matrix[i][j] + rhs.matrix[i][j];
		}
	}
	return result;
}

Matrix Matrix::operator-(const Matrix& rhs) {
	if (height != rhs.height || width != rhs.width) {
		throw "matrix dimensions are not equal";
	}
	Matrix result(height, width);
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			result[i][j] = matrix[i][j] - rhs.matrix[i][j];
		}
	}
	return result;
}

Matrix Matrix::operator*(const Matrix& rhs) {
	if (width != rhs.height) {
		throw "the number of columns of matrix 1 is not equal to the number of rows of matrix 2";
	}
	Matrix result(height, rhs.width, 0);
	for (int i = 0; i < result.height; ++i) {
		for (int j = 0; j < result.width; ++j) {
			for (int k = 0; k < width; ++k) {
				result[i][j] += matrix[i][k] * rhs.matrix[k][j];
			}
		}
	}
	return result;
}

Matrix Matrix::operator*(const double number) {
	Matrix result(*this);
	for (int i = 0; i < result.height; ++i) {
		for (int j = 0; j < result.width; ++j) {
			result[i][j] *= number;
		}
	}
	return result;
}

double* Matrix::operator[](const int _height) {
	return matrix[_height];
}

const double* Matrix::operator[](const int _height) const {
	return matrix[_height];
}

void Matrix::transpose() {
	if (height == width) {
		for (int i = 0; i < height; ++i) {
			for (int j = i + 1; j < width; ++j) {
				swap(matrix[i][j], matrix[j][i]);
			}
		}
	}
	else {
		double** newMatrix = new double* [width];
		for (int i = 0; i < width; ++i) {
			newMatrix[i] = new double[height];
			for (int j = 0; j < height; ++j) {
				newMatrix[i][j] = matrix[j][i];
			}
		}

		for (int i = 0; i < height; ++i) {
			delete matrix[i];
		}
		delete matrix;

		matrix = newMatrix;
		swap(height, width);
	}
}

Matrix Matrix::getTransposed() {
	Matrix result(width, height);
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			result[j][i] = matrix[i][j];
		}
	}
	return result;
}

vector<double> Matrix::getVector() {
	if (height != 1) {
		throw "it's not a vector";
	}
	vector<double> result(width);
	for (int i = 0; i < width; ++i) {
		result[i] = matrix[0][i];
	}
	return result;
}

vector<vector<double>> Matrix::getVectorOfVectors() {
	vector<vector<double>> result(height, vector<double>(width));
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			result[i][j] = matrix[i][j];
		}
	}
	return result;
}

double Matrix::getDeterminante() const{
	if (height != width) {
		throw "this isn't square matrix";
	}

	double result = 0;
	double temp; // using for intermediate multiplication 
	int* transposition = new int[height];
	for (int i = 0; i < height; ++i) {
		transposition[i] = i;
	}

	while (true) {
		temp = 1;
		for (int i = 0; i < height; ++i) {
			temp *= matrix[i][transposition[i]];
		}
		for (int i = 0; i < height - 1; ++i) {  // sign
			for (int x = i + 1; x < height; ++x) {
				if (transposition[i] > transposition[x]) {
					temp *= -1;
				}
			}
		}
		result += temp;

		// next transposition
		int j = height - 2;
		while (j != -1 && transposition[j] > transposition[j + 1]) { 
			--j;
		}
		if (j == -1) {
			break;
		}
		int k = height - 1;
		while (transposition[j] > transposition[k]) {
			--k;
		}
		swap(transposition[j], transposition[k]);
		int l = j + 1, r = height - 1;
		while (l < r) {
			swap(transposition[l++], transposition[r--]);
		}
	}

	delete[] transposition;
	return result;
}

double Matrix::getHeight() const {
	return height;
}

double Matrix::getWidth() const{
	return width;
}

void Matrix::setEpsilon(double newEpsilon) {
	epsilon = newEpsilon;
}

double Matrix::getEpsilon() const { 
	return epsilon;
}

void Matrix::printfMatrix() {
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			printf("%9.6f  ", matrix[i][j]);
		}
		printf("\n");
	}
}

Matrix Matrix::createUnitMatrix(int size) {
	Matrix result(size, size, 0);
	for (int i = 0; i < size; ++i) {
		result[i][i] = 1;
	}
	return result;
}
