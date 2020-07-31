#include <bits/stdc++.h>
using namespace std;
#define REP(i,n) for(int i = 0; i < (n); i++)

const int A = 65;
struct Matrix {
	vector<vector<unsigned int>> a = vector<vector<unsigned int>>(A, vector<unsigned int>(A));
	Matrix operator *(const Matrix& other) {
		Matrix product;
		REP(i,A)REP(j,A)REP(k,A) {
			product.a[i][k] += a[i][j] * other.a[j][k];
		}
		return product;
	}
};
Matrix expo_power(Matrix a, int k) {
	Matrix product;
	REP(i,A) product.a[i][i] = 1;
	while(k > 0) {
		if(k % 2) {
			product = product * a;
		}
		a = a * a;
		k /= 2;
	}
	return product;
}


//vector<pair<int,int>> directions{{-2,-1},{-2,1},{-1,2},{-1,-2},{1,2},{1,-2},{2,-1},{2,1}};
bool inside(int row, int col) {
	return 0 <= min(row, col) && max(row, col) < 8;
}
int main() {
	// E. Knight Paths
	int k;
	cin >> k;
	k++;
	// unsigned int answer = 0;
	// unsigned int dp[8][8];
	
	Matrix single;
	REP(row, 8) {
		REP(col, 8) {
			for(int dr : {-2,-1,1,2}) {
				for(int dc : {-2,-1,1,2}) {
					if(abs(dr) != abs(dc)) {
						int new_row = row + dr;
						int new_col = col + dc;
						if(inside(new_row, new_col)) {
							single.a[8*row+col][8*new_row+new_col] = 1;
						}
					}
				}
			}
		}
	}
	for(int i = 0; i <= 64; i++) {
		single.a[i][64] = 1;
	}
	Matrix total = expo_power(single, k);
	cout << total.a[0][64] << endl;
	
	/*
	vector<unsigned int> dp(65);
	dp[0] = 1;
	REP(repeat, k) {
		vector<unsigned int> new_dp(65);
		REP(row, 8) {
			REP(col, 8) {
				for(int dr : {-2,-1,1,2}) {
					for(int dc : {-2,-1,1,2}) {
						if(abs(dr) != abs(dc)) {
							int new_row = row + dr;
							int new_col = col + dc;
							if(inside(new_row, new_col)) {
								new_dp[8*new_row+new_col] += dp[8*row+col]; // modulo 2^32
							}
						}
					}
				}
			}
		}
		new_dp[64] += dp[64];
		REP(row,8)REP(col,8) new_dp[64] += dp[8*row+col];
		dp = new_dp;
	}
	cout << dp[64] << endl;*/
}

/*
take this graph
from every vertex add an edge to a fake vertex N+1
also, an edge from N+1 to N+1

every path of length 5 in the initial graph corresponds to a path of length 6,7,8,...
	ending at vertex N+1
	*/
