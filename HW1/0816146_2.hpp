#include <vector>
#include "0816146_1.hpp"

using namespace std;

#ifndef _SEAN_POLY
#define _SEAN_POLY

class Polynomial {
	int x;
	vector<int> coef;

public:
	Polynomial(const int a, const vector<int> v) {
		x = a;
		coef = vector<int>(v.size());
		for (int i=0; i<v.size(); i++)
			coef[i] = v[i];
	}

	Polynomial(const Polynomial &p) {
		x = p.x;
		coef = p.coef;
	}

	int calculate() const;
	Polynomial firstDerivative() const;
	Polynomial derivative(int d) const;
	Polynomial secDerivative() const;
};

int Polynomial::calculate() const {
	int ans;
	ans = 0;
	int s = coef.size();
	for (int i=0; i<s; i++) {
		ans *= x;
		ans += coef[i];
	}

	return ans;
}

Polynomial Polynomial::firstDerivative() const {
	int s;
	s = coef.size();
	Polynomial p(*this);

	if (!s)
		return p;

	for (int i=0; i<s; i++)
		p.coef[i] *= s - i - 1;
	p.coef.pop_back();

	return p;
}

Polynomial Polynomial::derivative(int d) const {
	Polynomial p(*this);
	while (d--)
		p = p.firstDerivative();
	return p;
}

Polynomial Polynomial::secDerivative() const {
	return derivative(2);
}

#endif  // _SEAN_POLY
