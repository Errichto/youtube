// Closest Pick
// https://codingcompetitions.withgoogle.com/codejam/round/00000000004362d7/00000000007c0f00
#include <bits/stdc++.h>
using namespace std;

void test_case() {
    int n, k;
    scanf("%d%d", &n, &k);
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    sort(a.begin(), a.end());
    int answer = 0;
    vector<int> best;
    best.push_back(a[0] - 1);
    best.push_back(k - a.back());
    for(int i = 0; i < (int) a.size() - 1; i++) {
        int x = a[i];
        int y = a[i+1];
        answer = max(answer, y - x - 1);
        best.push_back((y - x) / 2);
    }
    sort(best.rbegin(), best.rend());
    answer = max(answer, best[0] + best[1]);
    printf("%.10lf\n", (double) answer / k);
}

int main() {
    int T;
    scanf("%d", &T);
    for(int x = 1; x <= T; x++) {
        printf("Case #%d: ", x);
        test_case();
    }
}

/*

1 3 7
   6     8





10 14
  13    -> 2
  
10 15
  14   -> 2
  
  
A B   -> (B - A) / 2*/
