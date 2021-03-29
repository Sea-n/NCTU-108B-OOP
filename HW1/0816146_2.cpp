#include <iostream>
#include <sstream>
#include "0816146_2.hpp"

using namespace std;

int main() {
	int x, k;
	int a, b, c;
	string line;

	while (cin >> x >> ws) {
		getline(cin, line);
		istringstream ss(line);

		vector<int> coef;
		while (ss >> k)
			coef.push_back(k);

		Polynomial p(x, coef);
		a = p.calculate();
		b = p.firstDerivative().calculate();
		c = p.secDerivative().calculate();
		cout << a << ' ' << b << ' ' << c << '\n';
	}
}
