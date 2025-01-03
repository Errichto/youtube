#include <bits/stdc++.h>
using namespace std;

map<int, vector<int>> edges;



void topo(int a, vector<int>& order, map<int,int>& in, const set<int>& present) {
	order.push_back(a);
	for (int b : edges[a]) {
		if (present.count(b)) {
			if (--in[b] == 0) {
				topo(b, order, in, present);
			}
		}
	}
}

int main() {
	string s;
	long long answer = 0;
	while (getline(cin, s)) {
		if (s.empty() || !isdigit(s[0])) {
			continue;
		}
		int len = (int) s.length();
		// cout << s << "\n";
		vector<int> v;
		bool was_pipe = false;
		for (int i = 0; i < len; i++) {
			if (isdigit(s[i])) {
				int x = 0;
				while (isdigit(s[i])) {
					x = 10 * x + (s[i] - '0');
					i++;
				}
				v.push_back(x);
				// cout << "i=" << i << " s[i]=" << int(s[i]) << "\n";
				if (s[i] == '|') {
					was_pipe = true;
				}
				assert(s[i] == ',' || s[i] == '|' || s[i] == '\n' || s[i] == 0);
				// cout << "x=" << x << " ";
			}
		}
		if (was_pipe) {
			edges[v[0]].push_back(v[1]);
		}
		else {
			
			set<int> earlier;
			bool ok = true;
			// O(Q * K * OUT_DEGREE * log)
			// O(Q * K^2 * log) -- if you iterated pairs (x,y) in the input
			map<int,int> in;
			set<int> present;
			for (int x : v) {
				present.insert(x);
			}
			for (int i = 0; i < (int) v.size(); i++) {
				int x = v[i];
				for (int y : edges[x]) {
					if (present.count(y)) {
						++in[y];
					}
					if (earlier.count(y)) {
						ok = false;
					}
				}
				earlier.insert(x);
			}
			if (ok) {
				// answer += v[v.size()/2];
			}
			else {
				// incorrect
				vector<int> order;
				vector<int> starting;
				for (int x : v) {
					if (in[x] == 0) {
						starting.push_back(x);
					}
				}
				for (int x : starting) {
					topo(x, order, in, present);
				}
				answer += order[order.size()/2];
			}
		}
	}
	cout << answer << "\n";
}
