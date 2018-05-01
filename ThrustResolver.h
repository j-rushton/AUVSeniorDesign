#ifndef THRUST_RESOLVER_H
#define THRUST_RESOLVER_H

#include "Matrix.h"

class ThrustResolver
{
public:
	ThrustResolver(int n = 0);
	~ThrustResolver();

	bool getStatus(const int x);
	const Matrix& getPwr();
	const Matrix& getEqs(const int x);

	void setEq(int n, Matrix &eq);

	void activate(const int x);
	void deactivate(const int x);

private:
	Matrix* eqs;
	Matrix* pwr;
	bool* status;
	int numEqs;

	void solve(Matrix& input);
};

#endif