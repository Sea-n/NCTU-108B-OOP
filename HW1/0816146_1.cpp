#include <iostream>
#include "0816146_1.hpp"

using namespace std;

int main() {
	Large a, b;
	cout << "Please ENTER two number a and b: ";
	cin >> a >> b;
	cout << endl;

	cout << " a = " <<  a << endl;
	cout << " b = " <<  b << endl;
	cout << "-a = " << -a << endl;
	cout << "-b = " << -b << endl;
	cout << endl;

	cout << "a >  b ? " << (a >  b) << endl;
	cout << "a <  b ? " << (a <  b) << endl;
	cout << "a >= b ? " << (a >= b) << endl;
	cout << "a <= b ? " << (a <= b) << endl;
	cout << "a == b ? " << (a == b) << endl;
	cout << endl;

	cout << "a + b = " << a + b << endl;
	cout << "a - b = " << a - b << endl;
	cout << "a * b = " << a * b << endl;
	cout << "a / b = " << a / b << endl;
	cout << "a \% b = " << a % b << endl;
	cout << endl;

	cout << "-a +  b = " << -a +  b << endl;
	cout << " a + -b = " <<  a + -b << endl;
	cout << "-a + -b = " << -a + -b << endl;
	cout << endl;
	return 0;
}
