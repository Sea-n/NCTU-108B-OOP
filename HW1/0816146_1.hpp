#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

#ifndef _SEAN_LARGE
#define _SEAN_LARGE

class Large {
	static const int SIZE = 10000;
	long long sign;
	long long A[SIZE]; // 5 digit * size, reversed

public:
	Large() {
		sign = 1;
		for (int i=0; i<SIZE; i++)
			A[i] = 0;
	}

	Large(const int s, const long long B[SIZE]) {
		sign = s;
		for (int i=0; i<SIZE; i++)
			A[i] = B[i];
	}

	Large(long long n) {
		for (int i=0; i<SIZE; i++)
			A[i] = 0;

		sign = (n < 0 ? -1 : 1);
		n *= sign;
		int i = 0;
		while (n) {
			A[i] = n % (int) 1e5;
			n /= 1e5;
		}
	}

	void operator=(const Large &b) {
		sign = b.sign;
		for (int i=0; i<SIZE; i++)
			A[i] = b.A[i];
	}

	void operator=(int n) {
		for (int i=0; i<SIZE; i++)
			A[i] = 0;

		sign = (n < 0 ? -1 : 1);
		n *= sign;
		int i = 0;
		while (n) {
			A[i++] = n % (int) 1e5;
			n /= (int) 1e5;
		}
	}

	Large abs() const;

	operator int() const {
		return 1;
		int p = Large::SIZE;
		while (p && !A[--p]);

		int k = A[p];

		while (--p >= 0)
			k = k*1e5 + A[p];

		k *= sign;

		return k;
	}

	friend istream &operator>>(istream &s, Large &a);
	friend ostream &operator<<(ostream &s, Large a);

	friend const Large operator-(const Large &a);
	friend void operator++(Large &a);
	friend void operator--(Large &a);
	friend void operator++(Large &a, int);
	friend void operator--(Large &a, int);

	friend const Large operator+(const Large &a, const Large &b);
	friend const Large operator-(const Large &a, const Large &b);
	friend const Large operator*(const Large &a, const Large &b);
	friend const Large operator/(const Large &a, const Large &b);
	friend const Large operator%(const Large &a, const Large &b);

	friend const Large operator+(const Large &a, long long b);
	friend const Large operator-(const Large &a, long long b);
	friend const Large operator*(const Large &a, long long b);
	friend const Large operator/(const Large &a, long long b);
	friend const Large operator%(const Large &a, long long b);

	friend void operator+=(Large &a, const Large &b);
	friend void operator-=(Large &a, const Large &b);
	friend void operator*=(Large &a, const Large &b);
	friend void operator/=(Large &a, const Large &b);
	friend void operator%=(Large &a, const Large &b);

	friend void operator+=(Large &a, const long long b);
	friend void operator-=(Large &a, const long long b);
	friend void operator*=(Large &a, const long long b);
	friend void operator/=(Large &a, const long long b);
	friend void operator%=(Large &a, const long long b);

	friend Large operator<<(Large &a, int b);
	friend Large operator>>(Large &a, int b);
	friend void operator<<=(Large &a, int b);
	friend void operator>>=(Large &a, int b);

	friend bool operator==(const Large &a, const Large &b);
	friend bool operator> (const Large &a, const Large &b);
	friend bool operator< (const Large &a, const Large &b);
	friend bool operator>=(const Large &a, const Large &b);
	friend bool operator<=(const Large &a, const Large &b);
};


istream &operator>>(istream &s, Large &a) {
	char str[5 * Large::SIZE];
	char tmp[20];
	s >> str;
	int L = strlen(str);

	if (str[0] == '-') {
		a.sign = -1;
		str[0] = '0';
	}

	if (str[0] == '+')
		str[0] = '0';

	for (int i=0; i<Large::SIZE; i++) {
		if ((i+1)*5 <= L) {
			strncpy(tmp, str + L-5*(i+1), 5);
			tmp[5] = '\0';
			a.A[i] = atoi(tmp);
		} else if (i*5 < L) {
			strncpy(tmp, str, L % 5);
			tmp[L % 5] = '\0';
			a.A[i] = atoi(tmp);
		} else {
			a.A[i] = 0;
		}
	}

	return s;
}

ostream &operator<<(ostream &s, Large a) {
	if (a.sign == -1)
		s << '-';

	int p = Large::SIZE;
	while (p && !a.A[--p]);

	cout << a.A[p];

	while (--p >= 0)
		s << setfill('0') << setw(5) << a.A[p];

	return s;
}


Large const operator-(const Large &a) {
	Large b = a;
	b.sign = -a.sign;
	return b;
}

void operator++(Large &a) {
	a += 1;
}

void operator--(Large &a) {
	a -= 1;
}

void operator++(Large &a, int) {
	a += 1;
}

void operator--(Large &a, int) {
	a -= 1;
}


const Large operator+(const Large &a, const Large &b) {
	if (a.sign != b.sign)
		return a - -b;

	Large c(a);

	for (int i=0; i<Large::SIZE; i++) {
		c.A[i] += b.A[i];
		if (c.A[i] > 1e5) {
			c.A[i] -= 1e5;
			c.A[i+1]++;
		}
	}

	return c;
}

const Large operator-(const Large &a, const Large &b) {
	if (a.sign != b.sign)
		return a + -b;

	if (a.abs() < b.abs())
		return -(b - a);

	Large c(a);
	for (int i=Large::SIZE-1; i>=0; i--) {
		if (c.A[i] < b.A[i]) {
			c.A[i] += 1e5;
			c.A[i+1]--;
		}
		c.A[i] -= b.A[i];
	}

	return c;
}

const Large operator*(const Large &a, const Large &b) {
	if (a.sign != b.sign)
		return -(-a * b);

	if (a.sign == -1)
		return -a * -b;

	Large c;
	for (int i=0; i<Large::SIZE; i++)
		for (int j=0; i+j<Large::SIZE; j++)
			c.A[i+j] += a.A[i] * b.A[j];

	for (int i=1; i<Large::SIZE; i++) {
		c.A[i] += c.A[i-1] / 1e5;
		c.A[i-1] %= (int) 1e5;
	}

	return c;
}

const Large operator/(const Large &x, const Large &y) {
	if (x.sign != y.sign)
		return -(-x / y);

	if (x.sign == -1)
		return -x / -y;

	int p = 0;
	Large a(1, x.A), b(1, y.A);
	Large c;

	while (!b.A[Large::SIZE - 1]) {
		p++;
		b <<= 1;

		if (p > Large::SIZE) // Divide by zero
			return c; // +0
	}

	while (p) {
		if (b > a) {
			b >>= 1;
			p--;
		}

		while (a >= b) {
			a -= b;
			c.A[p]++;
		}
	}

	return c;
}

const Large operator%(const Large &a, const Large &b) {
	return a - (a/b*b);
}


const Large operator+(const Large &a, long long b) {
	return a + Large(b);
}

const Large operator-(const Large &a, long long b) {
	return a - Large(b);
}

const Large operator*(const Large &a, long long b) {
	return a * Large(b);
}

const Large operator/(const Large &a, long long b) {
	return a / Large(b);
}

const Large operator%(const Large &a, long long b) {
	return a % Large(b);
}


void operator+=(Large &a, const Large &b) {
	a = a + b;
}

void operator-=(Large &a, const Large &b) {
	a += -b;
}

void operator*=(Large &a, const Large &b) {
	a = a * b;
}

void operator/=(Large &a, const Large &b) {
	a = a / b;
}

void operator%=(Large &a, const Large &b) {
	a = a % b;
}


void operator+=(Large &a, const long long b) {
	Large c(b);
	a += c;
}

void operator-=(Large &a, const long long b) {
	Large c(b);
	a -= c;
}

void operator*=(Large &a, const long long b) {
	Large c(b);
	a *= c;
}

void operator/=(Large &a, const long long b) {
	Large c(b);
	a /= c;
}

void operator%=(Large &a, const long long b) {
	Large c(b);
	a %= c;
}


Large operator<<(Large &a, int b) {
	Large c;
	c.sign = a.sign;

	while (b--) {
		for (int i=1; i<Large::SIZE; i++)
			c.A[i] = a.A[i-1];
		c.A[0] = 0;
	}

	return c;
}

Large operator>>(Large &a, int b) {
	Large c;
	c.sign = a.sign;

	while (b--) {
		for (int i=Large::SIZE-1; i>0; i--)
			c.A[i-1] = a.A[i];
		c.A[Large::SIZE - 1] = 0;
	}

	return c;
}

void operator<<=(Large &a, int b) {
	a = a << b;
}

void operator>>=(Large &a, int b) {
	a = a >> b;
}


bool operator==(const Large &a, const Large &b) {
	if (a.sign != b.sign)
		return false;

	for (int i=0; i<Large::SIZE; i++)
		if (a.A[i] != b.A[i])
			return false;

	return true;
}

bool operator>(const Large &a, const Large &b) {
	if (a.sign ==  1 && b.sign == -1)
		return true;
	if (a.sign == -1 && b.sign ==  1)
		return false;
	if (a.sign == -1 && b.sign == -1)
		return (-a < -b);

	for (int i=Large::SIZE-1; i>=0; i--) {
		if (a.A[i] != b.A[i])
			return a.A[i] > b.A[i];
	}

	return false;
}

bool operator<(const Large &a, const Large &b) {
	return (b > a);
}

bool operator>=(const Large &a, const Large &b) {
	return !(a < b);
}

bool operator<=(const Large &a, const Large &b) {
	return !(a > b);
}

Large Large::abs() const {
	Large b(1, A);
	return b;
}

#endif  // _SEAN_LARGE
