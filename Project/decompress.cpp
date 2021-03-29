#include <iostream>
#include <stack>
#include <fstream>
#include <cassert>

using namespace std;

struct node {
	unsigned char C = '\0';
	node *L = nullptr;
	node *R = nullptr;
};

int main(int argc, char **argv) {
	char buf, c;
	node *A;

	/* Check argument */
	if (argc != 2) {
		cerr << "Usage: " << argv[0] << " <filename>\n";
		return 1;
	}

	string fnm = argv[1];
	assert(fnm.size() > 9 && "File name too short.");
	string ext = fnm.substr(fnm.size() - 9);
	assert(ext == ".compress" && "The input file extension must be txt.");

	ifstream in(argv[1], ios::binary);
	assert(in.is_open() && "No such file.");

	/* Read bits */
	int cur = 0;
	auto ri = [&cur, &buf, &in]() {
		if (--cur < 0) {
			in.get(buf);
			cur = 7;
		}
		if (buf & (1<<cur))
			return true;
		else
			return false;
	};
	auto r = [ri](int size) {
		unsigned long long bits = 0;
		for (int i=0; i<size; i++)
			if (ri()) bits |= 1ull<<i;
		return bits;
	};

	/* Build Huffman Tree */
	node P;
	stack<node*> S;

	S.push(&P);
	while (!S.empty()) {
		A = S.top(); S.pop();

		if (r(1)) {
			A->C = r(8);
		} else {
			A->L = new node;
			A->R = new node;
			S.push(A->R);
			S.push(A->L);
		}
	}

	/* Decompress */
	string fo = fnm.substr(0, fnm.size() - 9);
	fo += "_decompressed.txt";
	ofstream out(fo, ios::out | ios::binary);

	A = &P;
	while (1) {
		if (A->L == nullptr) {
			if (A->C == 0)
				break;
			c = A->C;
			out.write(&c, 1);
			A = &P;
		} else if (r(1))
			A = A->L;
		else
			A = A->R;
	}

	return 0;
}
