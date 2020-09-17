#include <bits/stdc++.h>
using namespace std;
const int nax = 5e5 + 5;
const int mod = 1e9 + 7;
char s[nax];
#define REP(i) for(int i = 0; i < 2; ++i)
struct Matrix {
	int a[2][2] = {{0,0},{0,0}};
	Matrix operator *(const Matrix& other) const {
		Matrix product;
		REP(i) REP(j) REP(k) {
			product.a[i][k] = (product.a[i][k] + (long long) a[i][j] * other.a[j][k]) % mod;
		}
		return product;
	}
	void init(char match) {
		REP(i) REP(j) {
			a[i][j] = 0;
		}
		for(char ch = 'A'; ch <= 'Z'; ++ch) {
			if(match == '?' || ch == match) {
				if(ch == 'H') { // everthing moves to happy
					a[0][1]++;
					a[1][1]++;
				}
				else if(ch == 'S' || ch == 'D') {
					a[0][0]++;
					a[1][0]++;
				}
				else if(ch == 'A' || ch == 'E' || ch == 'I' || ch == 'U' || ch == 'O') {
					a[0][1]++;
					a[1][0]++;
				}
				else {
					a[0][0]++;
					a[1][1]++;
				}
			}
		}
	}
};

int main() {
	// H. String Mood Updates
	int n, q;
	scanf("%d%d", &n, &q);
	scanf("%s", s);
	
	int BASE = 1;
	while(BASE < n) {
		BASE *= 2;
	}
	vector<Matrix> tree(2 * BASE);
	for(int i = 0; i < n; ++i) {
		tree[BASE+i].init(s[i]);
	}
	for(int i = n; i < BASE; ++i) {
		tree[BASE+i].init('Z'); // neutral character
	}
	for(int i = BASE - 1; i >= 1; --i) {
		tree[i] = tree[2*i] * tree[2*i+1];
	}
	printf("%d\n", tree[1].a[1][1]); // root.m[happy][happy]
	while(q--) {
		int i;
		char new_ch;
		scanf("%d %c", &i, &new_ch);
		i--;
		tree[BASE+i].init(new_ch);
		for(int x = (BASE + i) / 2; x >= 1; x /= 2) {
			tree[x] = tree[2*x] * tree[2*x+1];
		}
		printf("%d\n", tree[1].a[1][1]);
	}
}
