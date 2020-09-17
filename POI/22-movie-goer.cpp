// Movie-goer problem from POI 22, https://szkopul.edu.pl/problemset/problem/k-RYEjhwNTo_XdaCidXQUGMU/site/?key=statement
// video link: https://youtu.be/rF13507mRp8
#include <bits/stdc++.h>
using namespace std;
struct Node {
	long long sum, prefMax;
	void merge(Node left, Node right) {
		sum = left.sum + right.sum;
		prefMax = max(left.prefMax, left.sum + right.prefMax);
	}
};
const int INF = 1e9 + 5;
int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	vector<int> movie(n);
	for(int i = 0; i < n; i++) {
		scanf("%d", &movie[i]);
		movie[i]--;
	}
	vector<int> value(m);
	for(int i = 0; i < m; i++) {
		scanf("%d", &value[i]);
	}
	
	int BASE = 1;
	while(BASE < n) {
		BASE *= 2;
	}
	vector<Node> tree(2 * BASE);
	auto set = [&](int i, int val) {
		tree[BASE+i] = Node{val, max(0, val)};
		for(int j = (BASE + i) / 2; j >= 1; j /= 2) {
			tree[j].merge(tree[2*j], tree[2*j+1]);
		}
	};
	
	long long answer = 0;
	vector<vector<int>> where(m, {INF, INF});
	
	for(int i = n - 1; i >= 0; i--) {
		int m_id = movie[i];
		vector<int>& vec = where[m_id];
		int sec_last = vec[(int) vec.size() - 2];
		int last = vec.back();
		
		if(sec_last < INF) {
			set(sec_last, 0);
		}
		if(last < INF) {
			set(last, -value[m_id]);
		}
		set(i, value[m_id]);
		
		answer = max(answer, tree[1].prefMax);
		vec.push_back(i);
	}
	
	printf("%lld\n", answer);
}
