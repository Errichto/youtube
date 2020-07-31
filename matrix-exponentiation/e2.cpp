#include <bits/stdc++.h>
using namespace std;
const int A = 65;
#define REP(i, n) for(int i = 0; i < (n); i++)
struct Matrix {
	vector<vector<unsigned int>> a;
	Matrix() {
		a.resize(A, vector<unsigned int>(A));
	}
	Matrix operator *(Matrix other) {
		Matrix product = Matrix();
		REP(i, A) {
			REP(j, A) {
				REP(k, A) {
					product.a[i][k] += a[i][j] * other.a[j][k];
				}
			}
		}
		return product;
	}
};
Matrix expo_power(Matrix a, long long n) {
	Matrix res = Matrix();
	for(int i = 0; i < A; ++i) {
		res.a[i][i] = 1;
	}
	while(n) {
		if(n % 2) {
			res = res * a;
		}
		n /= 2;
		a = a * a;
	}
	return res;
}
int main() {
	long long n;
	cin >> n;
	Matrix single = Matrix();
	single.a[64][64] = 1; // the answer moves on to next step
	for(int cell = 0; cell < 64; ++cell) {
		single.a[cell][64] = 1; // add to the answer
		for(int cell2 = 0; cell2 < 64; ++cell2) {
			int row = cell / 8;
			int col = cell % 8;
			int r2 = cell2 / 8;
			int c2 = cell2 % 8;
			int d_row = abs(row - r2);
			int d_col = abs(col - c2);
			if((d_row == 2 && d_col == 1) || (d_row == 1 && d_col == 2)) {
				single.a[cell][cell2] = 1;
			}
		}
	}
	Matrix total = expo_power(single, n + 1); // n+1 because answer is taken as sum from previous iteration
	cout << total.a[0][64] << endl;
	/*Matrix total = expo_power(single, n);
	unsigned int answer = 0;
	for(int i = 0; i < A; ++i) {
		answer += total.a[0][i];
	}
	cout << answer << endl;*/
}
