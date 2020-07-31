#include <bits/stdc++.h>
using namespace std;
#define REP(i,n) for(int i = 0; i < (n); i++)
const long long INF = 3e18L + 5;
int n;
struct Matrix {
	vector<vector<long long>> a = vector<vector<long long>>(n, vector<long long>(n, INF));
	Matrix operator *(const Matrix& other) {
		Matrix product;
		REP(i,n)REP(j,n)REP(k,n) {
			product.a[i][k] = min(product.a[i][k], a[i][j] + other.a[j][k]);
			// product.a[i][k] = (product.a[i][k] + (long long) a[i][j] * other.a[j][k]) % mod;
		}
		return product;
	}
};
Matrix expo_power(Matrix a, long long k) {
	Matrix product;
	REP(i,n) product.a[i][i] = 0;
	while(k > 0) {
		if(k % 2) {
			product = product * a;
		}
		a = a * a;
		k /= 2;
	}
	return product;
}
int main() {
	// F. Min Path
	int m;
	long long k;
	cin >> n >> m >> k;
	Matrix single;
	// REP(i,n)REP(j,n) {
		// single.a[i][j] = INF;
	// }
	for(int i = 0; i < m; i++) {
		int u, v, c;
		cin >> u >> v >> c;
		single.a[u-1][v-1] = c;
	}
	Matrix total = expo_power(single, k);
	long long answer = INF;
	REP(i,n)REP(j,n) {
		answer = min(answer, total.a[i][j]);
	}
	if(answer >= INF / 2) {
		cout << "IMPOSSIBLE" << endl;
	}
	else {
		cout << answer << endl;
	}
}
// O(N^3 * log(k))
