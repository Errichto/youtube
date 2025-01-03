#include <bits/stdc++.h>
using namespace std;

int N;
map<string, int> nameID;
string getString(int id) {
	for (auto p : nameID) {
		if (p.second == id) {
			return p.first;
		}
	}
	assert(false);
}
int getID(string s) {
	if (nameID.count(s)) {
		return nameID[s];
	}
	nameID[s] = N++;
	return nameID[s];
}
const int XOR = 0, OR = 1, AND = 2;
int getOP(string s) {
	if (s == "XOR") return XOR;
	if (s == "OR") return OR;
	if (s == "AND") return AND;
	assert(false);
}

struct Operation {
	int a, b, c;
	int op;
};
vector<int> xs, ys, zs;

int main() {
	for (int i = 0; i < 90; i++) {
		char s[7];
		scanf(" %s", s);
		int d;
		scanf(" %d", &d);
		// value[string(s, s+3)] = d;
	}
	string tmp = "xyz";
	for (char c : tmp) {
		for (int i = 0; i <= 45; i++) {
			string s;
			s += c;
			if (i < 10) s += "0";
			s += to_string(i);
			if (c == 'x') xs.push_back(getID(s));
			if (c == 'y') ys.push_back(getID(s));
			if (c == 'z') zs.push_back(getID(s));
		}
	}
	char a[5], _op[5], b[5], c[5];
	vector<Operation> ops;
	while (scanf(" %s", a) != EOF) {
		scanf(" %s %s -> %s", _op, b, c);
		int A = getID(string(a));
		int B = getID(string(b));
		int C = getID(string(c));
		ops.push_back(Operation{A,B,C, getOP(string(_op))});
	}
	
	auto simulate = [&](long long x, long long y) {
		vector<int> value(N, -1);
		for (int i = 0; i < 45; i++) {
			value[xs[i]] = bool(x & (1LL << i));
			value[ys[i]] = bool(y & (1LL << i));
		}
		while (true) {
			bool anything = false;
			for (Operation op : ops) {
				if (value[op.a] != -1 && value[op.b] != -1 && value[op.c] == -1) {
					int xx = value[op.a];
					int yy = value[op.b];
					value[op.c] = (op.op == XOR ? xx^yy : (op.op == OR ? xx|yy : xx&yy));
					anything = true;
				}
			}
			if (!anything) {
				break;
			}
		}
		long long answer = 0;
		int i = 0;
		// for (int id : zs) {
			// cout << value[id] << " ";
		// }
		// cout << "\n";
		for (int id : zs) {
			if (value[id] == -1) {
				return 0LL;
			}
			assert(value[id] != -1);
			answer += ((long long) value[id]) << i;
			i++;
		}
		return answer;
		
		/*
		int pref = 0;
		for (int i = 0; i < 45; i++) {
			if ((answer & (1LL << i)) == ((x + y) & (1LL << i))) {
				cout << ".";
				pref++;
			}
			else {
				cout << "x";
			}
			// else {
				// break;
			// }
		}
		cout << "\n";
		return pref;*/
	};
	// vector<int> bad{5,6,12,13,25,37};
	// set<string> bads;
	// for (int x : bad) {
		// for (string s : nodes) {
			// if (getNumber(s) == x) {
				// bads.insert(s);
				
			// }
		// }
	// }
	
	// for (int i = 0; i < 44; i++) {
		// long long x = (1LL << i);
		// if (simulate(x, x) != 2 * x) {
			// cout << i << " ";
		// }
	// }
	// for (int i = 1; i <= 1024; i *= 2) {
		// cout << i << " " << simulate(i, i) << "\n";
	// }
	
	
	
	// return 0;
	
	swap(ops[39].c, ops[60].c);
	swap(ops[79].c, ops[98].c);
	swap(ops[26].c, ops[191].c);
	swap(ops[90].c, ops[153].c);
	vector<string> out;
	for (int id : {39, 60, 79, 98, 26, 191, 90, 153}) {
		out.push_back(getString(ops[id].c));
	}
	sort(out.begin(), out.end());
	for (string s : out) {
		cout << s << ",";
	}
	cout << endl;
	return 0;
	
	for (int rep = 0; rep < 50; rep++) {
		long long x = rand();
		x = (x << 15) + x;
		long long y = rand();
		y = (y << 15) + y;
		x %= (1LL << 45);
		y %= (1LL << 45);
		
		assert(simulate(x, y) == x + y);
	}
	return 0;
	
	for (int i = 0; i < (int) ops.size(); i++) {
		cout << i << " ";
		fflush(stdout);
		for (int j = i + 1; j < (int) ops.size(); j++) {
			// cout << i << " " << j << endl;
			swap(ops[i].c, ops[j].c);
			bool ok = true;
			for (int k = 0; k < 40; k++) {
				long long x = 1LL << k;
				if (simulate(x, x) != 2 * x || (x!=0 && simulate(x + 1, x-1) != 2 * x)) {
					ok = false;
				}
			}
			// for (int x = 0; x < 70 && ok; x++) {
				// for (int y = 0; y <= x && ok; y++) {
					// if (simulate(x, y) != x + y || simulate(y, x) != x + y) {
						// ok = false;
					// }
				// }
			// }
			if (ok) {
				cout << "[[[[ " << i << ", " << j << " ]]]] ";
				// cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
				// return 0;
			}
			swap(ops[i].c, ops[j].c);
		}
	}
}
