// POI 18-2, Tree Rotations
// O(N * log^2(N))
#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds;
using ordered_set = tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>;

const int NAX = 2e5 + 5;
ordered_set s[NAX];
int next_to_take = 0;
long long answer;

int rec() {
    int x;
    scanf("%d", &x);
    if(x > 0) {
        int me = next_to_take++;
        s[me].insert(x);
        return me;
    }
    int L = rec();
    int R = rec();
    const long long pairs = (long long) s[L].size() * (long long) s[R].size();
    if(s[L].size() > s[R].size()) {
        swap(L, R);
    }
    //~ for(int a : s[L]) {
        //~ printf("%d ", a);
    //~ }
    //~ printf(" with ");
    //~ for(int a : s[R]) {
        //~ printf("%d ", a);
    //~ }
    //~ puts("");
    long long inversions = 0;
    for(int a : s[L]) {
        inversions += s[R].order_of_key(a); // the number of elements strictly smaller than a
    }
    //~ printf("%lld\n", inversions);
    //~ puts("");
    for(int a : s[L]) {
        s[R].insert(a);
    }
    s[L].clear(); // better to swap with an empty set, to trigger the desctructor and free the memory
    answer += min(inversions, pairs - inversions);
    return R;
}

int main() {
    int n;
    scanf("%d", &n);
    rec();
    printf("%lld\n", answer);
}
