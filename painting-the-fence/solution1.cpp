// solution 1, O(n*q + q^2)
#include "bits/stdc++.h"
using namespace std;
int main() {
    int n, q;
    scanf("%d%d", &n, &q);
    vector<pair<int,int>> intervals(q);
    vector<int> cnt(n);
    for(pair<int,int>& p : intervals) {
        scanf("%d%d", &p.first, &p.second);
        --p.first;
        --p.second;
        for(int i = p.first; i <= p.second; ++i) {
            ++cnt[i];
        }
    }
    int answer = 0;
    for(int A = 0; A < q; ++A) {
        int count_positive = 0;
        vector<int> ones(n);
        for(int i = intervals[A].first; i <= intervals[A].second; ++i) {
            --cnt[i];
        }
        
        for(int i = 0; i < n; ++i) {
            if(cnt[i] > 0) {
                ++count_positive;
            }
            if(cnt[i] == 1) {
                ++ones[i];
            }
        }
        // prefix sums on 'ones'
        for(int i = 1; i < n; ++i) {
            ones[i] += ones[i-1];
        }
        auto get_sum = [&](int L, int R) { // sum of interval [L,R]
            return ones[R] - (L ? ones[L-1] : 0);
        };
        
        for(int B = A + 1; B < q; ++B) {
            int lost_ones = get_sum(intervals[B].first, intervals[B].second);
            answer = max(answer, count_positive - lost_ones);
        }
        
        // roll back the decreases of 'cnt'
        for(int i = intervals[A].first; i <= intervals[A].second; ++i) {
            ++cnt[i];
        }
    }
    printf("%d\n", answer);
}
