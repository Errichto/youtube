/*
"Buy and sell stocks II" but we can own any number of units of stock.
O(N^2) dp solution and greedy-ish O(N^2) solution, which can be
 	improved to O(N*log(N)) with a segment tree.
 
The main() function generates random tests and compares two answers.
*/

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 5;

void max_self(int& a, int b) {
	a = max(a, b);
}

int dp_solve(vector<int> prices) {
	int n = prices.size();
	vector<vector<int>> dp(n + 1, vector<int>(n + 1, -INF));
	dp[0][0] = 0;
	// dp[i][units] - max possible money after first i days
	// 				with this count of units in hand
	for(int i = 0; i < n; ++i) {
		for(int units = 0; units <= n; ++units) {
			max_self(dp[i+1][units], dp[i][units]); // do nothing
			if(units >= 1) {
				max_self(dp[i+1][units-1], dp[i][units] + prices[i]); // sell
			}
			if(units <= n - 1) {
				max_self(dp[i+1][units+1], dp[i][units] - prices[i]); // buy
			}
		}
	}
	return dp[n][0];
}	

int greedy_solve(vector<int> prices) {
	int n = prices.size();
	vector<pair<int,int>> order;
	for(int i = 0; i < n; ++i) {
		order.emplace_back(prices[i], i);
	}
	sort(order.rbegin(), order.rend()); // decreasingly
	
	// sequence of decisions like +1, +1, -1, 0, -1
	// +1 is buy, 0 is nothing, -1 is sell
	// no prefix sum can be negative
	vector<int> decision(n, +1);
	
	auto is_ok = [&]() { // use segment trees instead of linear check
		int pref = 0; // get get O(N*log(N)) total time complexity
		for(int x : decision) {
			pref += x;
			if(pref < 0) {
				return false;
			}
		}
		return true;
	};
	for(pair<int,int> p : order) {
		int where = p.second;
		// if possible, sell at this high price
		decision[where] = -1;
		if(is_ok()) {
			continue;
		}
		// if possible, do nothing with this high price
		decision[where] = 0;
		if(is_ok()) {
			continue;
		}
		// ok, we must buy at this price
		decision[where] = +1;
		assert(is_ok());
	}
	int money = 0;
	for(int i = 0; i < n; ++i) {
		if(decision[i] == 1) {
			money -= prices[i];
		}
		if(decision[i] == -1) {
			money += prices[i];
		}
	}
	return money;
}

struct Node {
	int sum, minPrefixSum;
	
	void assignLeafValue (int value) {
		sum = value;
		minPrefixSum = value;
	}
	
	void merge (const Node& left, const Node & right) {
		sum = left.sum + right.sum;
		minPrefixSum = min (left.minPrefixSum, left.sum + right.minPrefixSum);
	}
	
	int getValue () {
		return minPrefixSum;
	}
};

template < class T, class V >
class SegmentTree {
	vector < Node > tree;
	int N;
	
	private:
	int getSegmentTreeSize (int n) {
		int sz = 1;
		for (;sz < N; sz <<= 1);
		return sz << 1;
	}
	
	void buildTree (vector < T > & arr, int low, int high, int pos) {
		if (low == high) {
			tree[pos].assignLeafValue (arr[low]);
			return;
		}
		int mid = low + (high - low) / 2;
		buildTree (arr, low, mid, 1 + (pos << 1));
		buildTree (arr, mid + 1, high, 2 + (pos << 1));
		tree[pos].merge (tree[1 + (pos << 1)], tree[2 + (pos << 1)]);
	}
	
	void update (int index, T value, int low, int high, int pos) {
		if (index < low || index > high) return;
		if (low == high) {
			tree[pos].assignLeafValue (value);
			return;
		}
		int mid = low + (high - low) / 2;
		update (index, value, low, mid, 1 + (pos << 1));
		update (index, value, mid + 1, high, 2 + (pos << 1));
		tree[pos].merge (tree[1 + (pos << 1)], tree[2 + (pos << 1)]);
	}
	
	Node query (int left, int right, int low, int high, int pos) {
		if (left <= low && right >= high) {
			return tree[pos];
		}
		
		//if (left > right) {
			//return 
		
		int mid = (low + high) / 2;
		if (left > mid) {
			return query (left, right, mid + 1, high, 2 + (pos << 1));
		} else if (right <= mid) {
			return query (left, right, low, mid, 1 + (pos << 1));
		}
		
		Node leftResult = query (left, right, low, mid, 1 + (pos << 1));
		Node rightResult = query (left, right, mid + 1, high, 2 + (pos << 1));
		Node result;
		result.merge (leftResult, rightResult);
		return result;
	}
	
	public:
	SegmentTree (vector < T > & arr) {
		N = arr.size();
		tree.resize (getSegmentTreeSize(N));
		buildTree (arr, 0, N - 1, 0);
	}
	
	~SegmentTree () {
		tree.resize (0);
	}
	
	V query (int left, int right) {
		Node result = query (left, right, 0, N - 1, 0);
		return result.getValue();
	}
	
	void update (int index, T value) {
		update (index, value, 0, N - 1, 0);
	}
};

int greedy_solve_segment_tree (const vector < int > & prices) {
	const int n = prices.size();
	if (n == 0) return 0;
	vector < pair < int, int > > order;
	for (int i = 0; i < n; i++) {
		order.emplace_back (prices[i], i);
	}
	sort (order.rbegin(), order.rend());
	
	vector < int > decision (n, +1);
	
	SegmentTree < int, int > st (decision);
	
	auto is_ok = [&]() { // use segment trees instead of linear check
		int pref = st.query (0, n - 1);
		return pref >= 0;
	};
	
	for (pair < int, int > & p : order) {
		int where = p.second;
		// if possible, sell at this high price
		decision[where] = -1;
		st.update (where, -1);
		if(is_ok()) {
			continue;
		}
		// if possible, do nothing with this high price
		decision[where] = 0;
		st.update (where, 0);
		if(is_ok()) {
			continue;
		}
		// ok, we must buy at this price
		decision[where] = +1;
		st.update (where, +1);
		assert(is_ok());
	}
	int money = 0;
	for(int i = 0; i < n; ++i) {
		if(decision[i] == 1) {
			money -= prices[i];
		}
		if(decision[i] == -1) {
			money += prices[i];
		}
	}
	return money;
}

int r(int a, int b) { return rand() % (b - a + 1); }
int main() {
	for(int rep = 1; true; ++rep) {
		int n = r(1, 15);
		vector<int> prices(n);
		for(int i = 0; i < n; ++i) {
			prices[i] = r(1, 15);
		}
		cout << "#" << rep << " [";
		for(int x : prices) cout << x << ",";
		cout << "]  ";
		int A = dp_solve(prices);
		int B = greedy_solve(prices);
		int C = greedy_solve_segment_tree (prices);
		cout << A << " " << B << " " << C << endl;
		assert(A == B);
		assert(A == C);
	}
}
