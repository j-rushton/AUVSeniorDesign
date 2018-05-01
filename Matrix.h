#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <iomanip>

class Matrix
{
public:
	Matrix(const int nn = 1, const int mm = 1);
	Matrix(const Matrix& inMat);
	~Matrix();

	void freeMemory();
	void initMatrix(int n, int m);

	const int N() { return n; };
	const int M() { return m; };

	Matrix inv();
	Matrix transpose(); 

	Matrix& operator= (const Matrix& rhs);
	Matrix operator+ (const Matrix& rhs);
	Matrix operator- (const Matrix& rhs);
	Matrix operator* (const Matrix& rhs);
	double& operator() (const int i, const int j);
	const double operator() (const int i, const int j) const;

	friend std::ostream& operator<< (std::ostream& os, const Matrix& M);

private:
	double** mat;
	int n;
	int m;
};

#endif