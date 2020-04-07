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
	
	auto is_ok = [&]() {
		int pref = 0;
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
		// ok, we must sell at this price
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
		cout << A << " " << B << endl;
		assert(A == B);
	}
}
