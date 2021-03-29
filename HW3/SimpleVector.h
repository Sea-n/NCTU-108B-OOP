#include <iostream>

using namespace std;

/*
 * Author: 0816146 Sean
 */
template <class T> class SimpleVector {
private:
	T *v;
	int s, c;

public:
	SimpleVector() {
		s = 0, c = 5;
		v = new T[c];
	}

	SimpleVector(int k) {
		s = 0, c = k;
		v = new T[c];
	}

	~SimpleVector() {
		delete[] v;
	}

	bool my_empty() {
		return !s;
	}

	int my_size() {
		return s;
	}

	void my_reverse() {
		T t;
		for (int i=0; i<s>>1; i++)
			t = v[i], v[i] = v[s-i-1], v[s-i-1] = t;
	}

	void my_clear() {
		s = 0;
	}

	void my_extend() {
		c <<= 1;
		T *t = new T[c];
		for (int i=0; i<s; i++)
			t[i] = v[i];

		delete[] v;
		v = t;
	}

	void my_push_back(T k) {
		if (s == c)
			my_extend();

		v[s++] = k;
	}

	T my_pop_back() {
		if (s == 0)
			return 0;

		return v[--s];
	}

	void my_insert(T k, T _p) {
		int p = _p;
		if (p < 0 || p > s)
			return;

		if (s == c)
			my_extend();

		for (int i=s; i>=p; i--)
			v[i] = v[i-1];

		v[p] = k;
		++s;
	}

	void my_set(T k, T _p) {
		int p = _p;
		if (p < 0 || p >= s)
			return;

		v[p] = k;
	}

	void print() {
		for (int i=0; i<s; i++)
			cout << v[i] << '_';
	}

	T operator[] (int p) {
		if (s == 0)
			return 0;

		if (p < 0 || p >= s)
			p = s - 1;

		return v[p];
	}
};
