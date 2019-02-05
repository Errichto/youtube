// incorrect solution for finding second smallest element
#include <bits/stdc++.h>
using namespace std;
// #warning TODO: remember about bigger N
const int MAX_N = 1e6 + 5;
int a[MAX_N];
set<int> asd[MAX_N], asdfasd[3*MAX_N];
int main() {
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }
    sort(a + 1, a + n);
    printf("%d\n", a[2]);
}
