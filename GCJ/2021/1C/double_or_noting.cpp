// Double or NOTing
// https://codingcompetitions.withgoogle.com/codejam/round/00000000004362d7/00000000007c1139
#include <bits/stdc++.h>
using namespace std;

vector<int> get_seq() {
	static char s[105];
	scanf("%s", s);
	int n = strlen(s);
	if(s[0] == '0') {
		assert(n == 1);
		return {};
	}
	vector<int> blocks;
	int current = 0;
	for(int i = 0; i < n; i++) {
		current++;
		if(i == n - 1 || s[i] != s[i+1]) {
			blocks.push_back(current);
			current = 0;
		}
	}
	// for(int x : blocks) {
		// cerr << x << ", ";
	// }
	// cerr << endl;
	return blocks;
}

const int INF = 1e9 + 5;

int test(const vector<int>& a, const vector<int>& b, int start) {
	int cut = start;
	int build = start + (int) b.size() - (int) a.size();
	assert(build >= 0);
	
	
// even a.size() -- if we cut 5 elements, we can create at most 5 to the right
// odd a.size() -- if we cut 5 elements, we can create at most 6 to the right
	if((int) a.size() % 2 == 1) {
		if(build > cut + 1) {
			return INF;
		}
	}
	else {
		if(build > cut) {
			return INF;
		}
	}
	
	int operations = 0;
	for(int i = 0; i < (int) b.size(); i++) {
		int j = start + i;
		if(j < (int) a.size()) {
			if(j < (int) a.size() - 1) {
				if(a[j] != b[i]) {
					return INF;
				}
				continue;
			}
			// last element of a[]
			if(a[j] > b[i]) {
				return INF;
			}
			if(a[j] == b[i]) {
				continue;
			}
			operations += b[i] - a[j];
			assert(a[j] < b[i]); // allowed in some cases
			if((int) a.size() % 2 == 0) {
				// easy, just multiply by two
				continue;
			}
			// only possible to increase last element if we first negate
			if(start == 0) {
				return INF;
			}
			// old comment: so far cut 1, increase the last, create nothing new
			if(cut <= build) {
				return INF;
			}
		}
	}
	// cerr << operations << endl;
	for(int i = 0; i < build; i++) {
		// cerr << "b " << b[(int) b.size() - 1 - i] << endl;
		operations += b[(int) b.size() - 1 - i];
	}
	// cerr << operations << endl;
	operations += cut;
	return operations;
}

// (3) -> (5)
// CUT
// ()


// 111 -> 11111


void test_case() {
	vector<int> a = get_seq();
	vector<int> b = get_seq();
	if(a == b) {
		puts("0");
		return;
	}
	bool extra_operation = false;
	if(a == vector<int>{}) {
		a = {1};
		extra_operation = true;
	}
	// cerr << a.size() << " " << b.size() << endl;
	// TODO, handle empty sequences
	int answer = INF;
	for(int start = max(0, (int)a.size() - (int)b.size()); start <= (int) a.size(); start++) {
		int operations = test(a, b, start);
		answer = min(answer, operations);
	}
	if(answer == INF) {
		puts("IMPOSSIBLE");
	}
	else {
		printf("%d\n", answer + extra_operation);
	}
}
/*
           start
             v        j
(2, 4, 5, 1, 2, 1, 1, 3)
            (2, 1, 1, 3, 2, 7)      
                      i
                      
(2, 4) NEGATE
   (4)

(2, 4, 5) NEGATE
   (4, 5) MULT
   (4, 6) NEGATE          so far cut 1, increase the last, create nothing new
      (6)


(2, 4, 5) MULT
(2, 4, 5, 1)
   (4, 5, 1)
   
even a.size() -- if we cut 5 elements, we can create at most 5 to the right
odd a.size() -- if we cut 5 elements, we can create at most 6 to the right*/
   
int main() {
	int T;
	scanf("%d", &T);
	for(int nr = 1; nr <= T; ++nr) {
		printf("Case #%d: ", nr);
		test_case();
	}
}
/*


 1100101
11001010
  110101
  
  
   1100101
  11001010
 110010100
1100101000
  11010111
  
  
             ones
              V
  2, 1, 1, 1, 3, 10
     1, 1, 1, 3, 10


(1, 3, 1)   ->  (3, 1)

10001 -> 1110


(2, 4, 5, 1, 2, 1, 1, 3)
      (2, 1, 1, 5, 2, 7)
            
            
The only case where I cannot increase last:  FALSE
(2, 1, 1, 7, 3)    11010000000111
(2, 1, 1, 7, 5, *)


(5) -> ZERO -> (1) -> (1, 1) -> (1, 2) -> (1, 3) -> (3) -> (3, 1) -> ...

(5) -> (5, 1) -> (5, 2) -> ...*/
