// slow solution for finding second smallest element
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for(int& x : a) {
        cin >> x;
    }
    for(int x : a) {
        int count_smaller = 0;
        for(int y : a) {
            if(y < x) {
                ++count_smaller;
            }
        }
        if(count_smaller == 1) {
            cout << x;
            return 0;
        }
    }
    assert(false);
}
