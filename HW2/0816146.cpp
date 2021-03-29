#include <iostream>
#include <cmath>
#include <string>
/*
 * The header files above are those you might use.
 * You can include other header files if you need to use them.
 * But make sure those header files can be used in the test environment.
 */
using namespace std;


class Machine {  /* DO NOT add any code in this parent class and its virtual function */
	protected:
		string type;
	public:
		virtual void welcome_message() {}
		virtual void problem_solver(int x) {}
		virtual void problem_solver(string str) {}
};


class Math_machine: public Machine {
	public:
		Math_machine(string type) {
			this->type = type;
		}

		void welcome_message() {
			cout << "Solving the " << type << " problem." << endl;
		}

		void problem_solver(int x) {
			for (int k=sqrt(x+1); k; k--) {
				if (x % k == 0) {
					cout << k << ' ' << x/k << '\n';
					break;
				}
				if ((x+1) % k == 0) {
					cout << k << ' ' << (x+1)/k << '\n';
					break;
				}
			}
		}
};

class String_machine: public Machine {
	public:
		String_machine(string type) {
			this->type = type;
		}

		void welcome_message() {
			cout << "Solving the " << type << " problem." << endl;
		}

		void problem_solver(string str) {
			int L = str.length();
			int ans = 0;
			for (int i=1; i<L; i++) {
				if (!((str[i-1] == '0' && str[i] == '1')
				   || (str[i-1] == '1' && str[i] == '0')))
					continue;

				for (int j=1; j<=i && j+i<=L; j++) {
					if (str[i - j] != str[i - 1]
					 || str[i+j-1] != str[i    ])
						break;
					ans++;
				}
			}

			cout << ans << endl;
		}
};

int main() {
	string type;
	int x;
	string str;

	while (cin >> type) {
		if (type == "math") {
			Math_machine m(type);
			m.welcome_message();
			cin >> x;
			m.problem_solver(x);
		} else if (type == "string") {
			String_machine m(type);
			m.welcome_message();
			cin >> str;
			m.problem_solver(str);
		} else {
			cout << "Unknown type '" << type << "'.\n";
		}
	}
}
