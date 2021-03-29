#include <iostream>
#include <queue>
#include <stack>
#include <fstream>
#include <cassert>
#include <tuple>

using namespace std;

struct node {
	unsigned char C = '\0';
	node *L = nullptr;
	node *R = nullptr;
};
typedef pair<int, node*> pr;

int main(int argc, char **argv) {
	char sc;
	unsigned char c;
	unsigned long long bits, sz;
	node *A;
	int wc[0x100] = {0};
	int len[0x100] = {0};
	long long hfm[0x100] = {0};

	/* Check argument */
	if (argc != 2) {
		cerr << "Usage: " << argv[0] << " <filename>\n";
		return 1;
	}

	string fnm = argv[1];
	assert(fnm.size() > 4 && "File name too short.");
	string ext = fnm.substr(fnm.size() - 4);
	assert(ext == ".txt" && "The input file extension must be txt.");


	ifstream in(argv[1], ios::binary);
	assert(in.is_open() && "No such file.");

	for (in.get(sc); in; in.get(sc)) {
		c = sc;
		assert(c != 0 && "This program cannot handle file with NULL character.");

		wc[c]++;
		wc[0]++;
	}


	/* Word Count */
	for (const char c: {'\0', 'a', 'e', 'i', 'o', 'u'})
		cout << wc[(int) c] << endl;

	/* Write to file.compress */
	string fo = fnm.substr(0, fnm.size() - 4);
	fo += ".compress";
	ofstream out(fo, ios::out | ios::binary);

	int cur = 7;
	char buf = '\0';
	auto wi = [&cur, &buf, &out](bool bit) {
		if (bit)
			buf |= 1<<cur;
		if (!cur--) {
			out.write(&buf, 1);
			cur = 7;
			buf = '\0';
		}
	};
	auto w = [wi](long long bits, int size = 1) {
#ifdef _DEBUG
		cerr << '[';
		for (int i=0; i<size; i++)
			cerr << (bits & (1ull<<i) ? 1 : 0);
		cerr << ']';
#endif
		for (int i=0; i<size; i++)
			wi(bits & (1ull<<i) ? 1 : 0);
	};

	/* Build Huffman Tree */
	priority_queue< pr, vector<pr>, greater<pr> > PQ;

	wc[0] = 1;
	for (int i=0; i<0x100; i++) {
		if (!wc[i])
			continue;
		A = new node{(unsigned char)i};
		PQ.push({wc[i], A});
	}

	while (PQ.size() > 1) {
		pr B = PQ.top(); PQ.pop();
		pr C = PQ.top(); PQ.pop();

		A = new node{'\0', B.second, C.second};
		pr n = {B.first + C.first,
			A};

		PQ.push(n);
	}

	/* Build Huffman Table from Tree */
	stack< tuple<node*, int, int> > S;

	A = PQ.top().second; PQ.pop();
	S.push({A, 0, 0});
	while (!S.empty()) {
		tie(A, sz, bits) = S.top(); S.pop();

		if (A->L == nullptr) {
			w(1);
			len[(int) A->C] = sz;
			hfm[(int) A->C] = bits;
			w(A->C, 8);
		} else {
			w(0);
			S.push({A->L, sz+1, bits});
			S.push({A->R, sz+1, bits | (1ull<<sz)});
		}
	}


	/* Compress */
	in.clear(); in.seekg(0, ios::beg);
	for (in.get(sc); in; in.get(sc)) {
		c = sc;
		w(hfm[c], len[c]);
	}
	w(hfm[0], len[0]);

	/* Flush last byte */
	while (cur != 7) w(1);

	return 0;
}
