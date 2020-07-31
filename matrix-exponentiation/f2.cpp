#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 2e18L + 5;
int n;
#define REP(i) for(int i = 0; i < n; i++)
struct Matrix {
	vector<vector<ll>> a = vector<vector<ll>>(n, vector<ll>(n, INF));
	Matrix operator *(Matrix other) {
		Matrix product;
		REP(i) {
			REP(j) {
				REP(k) {
					product.a[i][k] = min(product.a[i][k], a[i][j] + other.a[j][k]);
				}
			}
		}
		return product;
	}
};
Matrix expo_power(Matrix a, long long k) {
	Matrix res = Matrix();
	for(int i = 0; i < n; ++i) {
		res.a[i][i] = 0;
	}
	while(k) {
		if(k % 2) {
			res = res * a;
		}
		k /= 2;
		a = a * a;
	}
	return res;
}
int main() {
	int m, k;
	scanf("%d%d%d", &n, &m, &k);
	Matrix single;
	while(m--) {
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		single.a[a-1][b-1] = c;
	}
	Matrix total = expo_power(single, k);
	ll answer = INF;
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j) {
			answer = min(answer, total.a[i][j]);
		}
	}
	if(answer > INF / 2) {
		puts("IMPOSSIBLE");
	}
	else {
		printf("%lld\n", answer);
	}
}
