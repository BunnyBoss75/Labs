#pragma once

#include <iostream>
#include <vector>
using namespace std;

class Matrix {
public:
	Matrix();
	Matrix(const Matrix& other);
	Matrix(Matrix&& other);

	Matrix(double**& pointer, int _height, int _width);
	Matrix(int _heigth, int _width);
	Matrix(int _height, int _width, double value);

	~Matrix();

	Matrix& operator=(const Matrix& rhs);
	Matrix& operator=(Matrix&& rhs);

	bool operator==(const Matrix& rhs);
	Matrix operator+(const Matrix& rhs);
	Matrix operator-(const Matrix& rhs);
	Matrix operator*(const Matrix& rhs);

	Matrix operator*(const double number);

	double* operator[](const int _height);
	const double* operator[](const int _height) const;

	void transpose();
	Matrix getTransposed();
	vector<double> getVector();
	vector<vector<double>> getVectorOfVectors();
	double getDeterminante() const;

	double getHeight() const;
	double getWidth() const;
	void setEpsilon(double newEpsilon);
	double getEpsilon() const;

	void printfMatrix();

	static Matrix createUnitMatrix(int size);
private:
	double epsilon;

	int height;
	int width;
	double** matrix;
};