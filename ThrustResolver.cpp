#include "ThrustResolver.h"



ThrustResolver::ThrustResolver(int n)
{
	if (n <= 0)
	{
		std::cerr << "Number of Equations must be greater than 0\n";
		n = 1;
	}
	numEqs = n;

	status = new bool[numEqs];
	for (int i = 0; i < numEqs; i++)
	{
		activate(i);
	}

	eqs = new Matrix(n, 6);
	pwr = new Matrix(6);
}

ThrustResolver::~ThrustResolver()
{
	delete eqs;
	delete pwr;
	delete status;
}

bool ThrustResolver::getStatus(const int x)
{
	if (x >= 0 && x < numEqs)
	{
		return status[x];
	}
	return false;
}

const Matrix & ThrustResolver::getPwr()
{
	return *pwr;
}

const Matrix & ThrustResolver::getEqs(const int x)
{
	return *eqs;
}

void ThrustResolver::setEq(int n, Matrix & eq)
{
	if (eq.N() != 6 || eq.M() != 1)
	{
		std::cerr << "Invalid equation, ignoring\n";
		return;
	}
	if (n < 0 || n >= numEqs)
	{
		std::cerr << "Equation does not exist, ignoring\n";
		return;
	}

	for (int i = 0; i < 6; i++)
	{
		(*eqs)(n, i) = eq(n, 1);
	}
}

void ThrustResolver::activate(const int x)
{
	if (x >= 0 && x < numEqs)
	{
		status[x] = true;
	}
}

void ThrustResolver::deactivate(const int x)
{
	if (x >= 0 && x < numEqs)
	{
		status[x] = false;
	}
}

void ThrustResolver::solve(Matrix& input)
{
	Matrix At(numEqs, 6);
	Matrix M(1, 1);
	At = (*eqs).transpose();
	M = (*eqs) * At;

	(*pwr) = At * M.inv() * input;
}

