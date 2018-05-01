#include "Matrix.h"

Matrix::Matrix(int nn, int mm)
{
	if (nn < 1)	// check nn value to be greater than 0
	{
		std::cerr << "n value must be greater than 0, using 1\n";

		nn = 1;
	}
	if (mm < 1)	// check m value to be greater than 0
	{
		std::cerr << "m value must be greater than 0, using 1\n";

		mm = 1;
	}

	n = nn;
	m = mm;

	initMatrix(n, m);
}

Matrix::Matrix(const Matrix & inMat)
{
	n = inMat.n;
	m = inMat.m;

	mat = new double*[n];

	for (int i = 0; i < n; i++)
	{
		mat[i] = new double[m];

		for (int j = 0; j < m; ++j)
		{
			if (i == j)
			{
				mat[i][j] = inMat.mat[i][j];
			}
			else
			{
				mat[i][j] = inMat.mat[i][j];
			}
		}
	}
}

Matrix::~Matrix()
{
	freeMemory();
}

void Matrix::freeMemory()
{
	for (int i = 0; i < n; i++)
		delete mat[i];

	delete mat;
}

void Matrix::initMatrix(int n, int m)
{
	mat = new double*[n];

	for (int i = 0; i < n; i++)
	{
		mat[i] = new double[m];

		for (int j = 0; j < m; ++j)
		{
			if (i == j)
			{
				mat[i][j] = 1.0;
			}
			else
			{
				mat[i][j] = 0.0;
			}
		}
	}
}

Matrix Matrix::inv()
{
	if (n != m)
	{
		std::cerr << "Cannot take inverse: non-square matrix\n";
		return *this;
	}

	Matrix iMat(*this);
	Matrix rMat(n, m);

	for (int col = 0; col < m; col++)
	{
		// row pivoting
		int loc = col;
		for (int i = loc; i < n; i++)
		{
			if (iMat(i, col) > iMat(loc, col))
				loc = i;
		}
		if (loc != col)
		{
			double* temp1 = iMat.mat[col];
			double* temp2 = rMat.mat[col];
			iMat.mat[col] = iMat.mat[loc];
			rMat.mat[col] = rMat.mat[loc];
			iMat.mat[loc] = temp1;
			rMat.mat[loc] = temp2;
		}

		// gauss elimination
		for (int row = col; row < n; row++)
		{
			if (row == col && iMat(row, col) != 1.0)
			{
				double mult = (1 / iMat(row, col));

				for (int i = 0; i < m; i++)
				{
					iMat(row, i) = mult * iMat(row, i);
					rMat(row, i) = mult * iMat(row, i);
				}
			}
			else if (row != col)
			{
				double mult = iMat(row, col) / iMat(col, col);

				for (int i = 0; i < m; i++)
				{
					iMat(row, i) = iMat(row, i) - (mult * iMat(col, i));
					rMat(row, i) = rMat(row, i) - (mult * rMat(col, i));
				}
			}
		}
		for (int row = col - 1; row >= 0; row--)
		{
			double mult = iMat(row, col) / iMat(col, col);

			for (int i = 0; i < m; i++)
			{
				iMat(row, i) = iMat(row, i) - (mult * iMat(col, i));
				rMat(row, i) = rMat(row, i) - (mult * rMat(col, i));
			}
		}
	}

	return rMat;
}

Matrix Matrix::transpose()
{
	Matrix rMat(m, n);

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			rMat(j,i) = mat[i][j];
		}
	}

	return rMat;
}

Matrix& Matrix::operator=(const Matrix & rhs)
{
	if (this != &rhs)
	{
		if (n != rhs.n || m != rhs.m)
		{
			freeMemory();
			n = 0;
			m = 0;

			mat = NULL;
			
			initMatrix(rhs.n, rhs.m);
			n = rhs.n;
			m = rhs.m;
		}
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; ++j)
			{
				if (i == j)
				{
					mat[i][j] = rhs.mat[i][j];
				}
				else
				{
					mat[i][j] = rhs.mat[i][j];
				}
			}
		}

	}

	return *this;
}

Matrix Matrix::operator+(const Matrix & rhs)
{
	if (n != rhs.n || m != rhs.m)
	{
		std::cerr << "Matrix dimensions must agree\n";
		return *this;
	}
	else
	{
		Matrix rMat(*this);

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				rMat.mat[i][j] = mat[i][j] + rhs.mat[i][j];
			}
		}

		return rMat;

	}
}

Matrix Matrix::operator-(const Matrix & rhs)
{
	if (n != rhs.n || m != rhs.m)
	{
		std::cerr << "Matrix dimensions must agree\n";
		return *this;
	}
	else
	{
		Matrix rMat(*this);

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				rMat.mat[i][j] = mat[i][j] - rhs.mat[i][j];
			}
		}

		return rMat;

	}
}

Matrix Matrix::operator*(const Matrix & rhs)
{
	if (m != rhs.n)
	{
		std::cerr << "Matrix dimensions must agree\n";
		return *this;
	}
	else
	{
		Matrix rMat(n, rhs.m);

		for (int row = 0; row < n; row++)
		{
			for (int col = 0; col < rhs.m; col++)
			{
				for (int i = 0; i < m; i++)
				{
					rMat.mat[row][col] += (mat[row][i] * rhs.mat[i][col]);
				}
			}
		}

		return rMat;
	}
}

double& Matrix::operator()(const int i, const int j)
{
	if (i >= 0 && i < n && j >= 0 && j < m)
		return mat[i][j];
	else
	{
		std::cerr << i << "  " << j << "Index out of bounds, returning value at [0][0]\n";
		return mat[0][0];
	}
}

const double Matrix::operator()(const int i, const int j) const
{
	if (i >= 0 && i < n && j >= 0 && j < m)
		return mat[i][j];
	else
	{
		std::cerr << i << "  " << j << "Index out of bounds\n";
		return 0.0;
	}
}

std::ostream & operator<<(std::ostream & os, const Matrix & M)
{
	os << "\n\n" << std::setprecision(2) << std::fixed;

	for (int i = 0; i < M.n; i++)
	{
		for (int j = 0; j < M.m; j++)
		{
			os << std::setw(10) << M.mat[i][j];
		}
		os << "\n";
	}

	return os;
}
