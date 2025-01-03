#include <bits/stdc++.h>
using namespace std;

set<string> nodes;
map<string, vector<string>> edges;
void addEdge(string a, string b) {
	edges[a].push_back(b);
	edges[b].push_back(a);
}

int getNumber(string s) {
	if (isdigit(s.back())) {
		s.erase(s.begin());
		return stoi(s);
	}
	return -1;
}

int main() {
	map<string, int> value;
	for (int i = 0; i < 90; i++) {
		char s[7];
		scanf(" %s", s);
		int d;
		scanf(" %d", &d);
		value[string(s, s+3)] = d;
	}
	vector<vector<string>> ops;
	map<string, int> out;
	{
		char a[5], op[5], b[5], c[5];
		while (scanf(" %s", a) != EOF) {
			scanf(" %s %s -> %s", op, b, c);
			vector<string> v{string(a), string(b), string(c), string(op)};
			ops.push_back(v);
			addEdge(string(a), string(c));
			addEdge(string(b), string(c));
			addEdge(string(a), string(b));
			nodes.insert(string(a));
			nodes.insert(string(b));
			nodes.insert(string(c));
		}
	}
	
	for (string a : nodes) {
		if (getNumber(a) != -1) {
			for (string b : edges[a]) {
				for (string c : edges[b]) {
					for (string d : edges[c]) {
						for (string e : edges[d]) {
							if (getNumber(e) != -1 && abs(getNumber(a) - getNumber(e)) >= 5) {
								cout << a << " " << b << " " << c << " " << d << "\n";
							}
						}
					}
				}
			}
		}
	}
	return 0;
	
	map<string, vector<int>> numbers;
	for (string a : nodes) {
		if (getNumber(a) != -1) {
			numbers[a].push_back(getNumber(a));
			for (string b : edges[a]) {
				numbers[b].push_back(getNumber(a));
			}
		}
	}
	for (string s : nodes) {
		vector<int> v = numbers[s];
		sort(v.begin(), v.end());
		if (!v.empty() && v[0] != v.back()) {
			cout << s << ": ";
			for (int x : numbers[s]) {
				cout << x << ", ";
			}
			cout << "\n";
		}
	}
	// cout << nei.size() << " " << nodes.size() << "\n";
	
	return 0;
	for (auto p : out) {
		cout << p.first << " " << p.second << "\n";
	}
	#define op ophello
	for (int rep = 0; rep < (int) ops.size(); rep++) {
		for (vector<string> op : ops) {
			if (value.count(op[0]) && value.count(op[1]) && !value.count(op[2])) {
				int x = value[op[0]];
				int y = value[op[1]];
				string o = op[3];
				value[op[2]] = (o == "XOR" ? x^y : (o == "OR" ? x|y : x&y));
			}
		}
	}
	long long answer = 0;
	int i = 0;
	for (auto p : value) {
		if (p.first[0] == 'z') {
			answer += ((long long) p.second) << i;
			i++;
			// cout << p.first << " " << p.second << "\n";
		}
	}
	printf("%lld\n", answer);
}
