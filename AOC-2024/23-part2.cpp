#include <bits/stdc++.h>
using namespace std;
map<string, vector<string>> edges; // adjacency list
set<string> vis;
set<pair<string,string>> pairs; // set of edges
vector<string> big;

void rec(string a, int i, vector<string> clique) {
	if (i == (int) edges[a].size()) {
		if (clique.size() > big.size()) {
			big = clique;
		}
		// if ((int) clique.size() == 13) cout << "X";
		// cout << clique.size() << " ";
		return;
	}
	
	rec(a, i + 1, clique);
	
	string b = edges[a][i];
	for (string s : clique) {
		if (!pairs.count({b,s})) {
			return;
		}
	}
	clique.push_back(b);
	rec(a, i + 1, clique);
}

int main() {
	char s[7];
	set<string> nodes;
	// not using: adjacency matrix
	while (scanf("%s", s) != EOF) {
		// printf("> %s\n", s);
		string a(s, s + 2);
		string b(s + 3, s + 5);
		
		nodes.insert(a);
		nodes.insert(b);
		edges[a].push_back(b);
		edges[b].push_back(a);
		pairs.insert({a,b});
		pairs.insert({b,a});
	}
	
	for (string a : nodes) {
		rec(a, 0, {a});
	}
	
	// cout << big.size() << "\n";
	sort(big.begin(), big.end());
	for (string s : big) {
		cout << s << ",";
	}
	cout << "\n";
}
