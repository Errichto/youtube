// POI 18-2, Temperature
// O(N), window maximum with deque-like structure
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    scanf("%d", &n);
    vector<pair<int,int>> in(n);
    for(pair<int,int>& p : in) {
        scanf("%d%d", &p.first, &p.second);
    }
    
    vector<int> indices{0}; // stack of indices of maxima
    int vector_start = 0;
    int answer = 1; // size 1 is always possible
    
    // Two pointers technique
    int a = 0;
    for(int b = 1; b < n; ++b) {
        while((int) indices.size() > vector_start && in[indices.back()].first < in[b].first) {
            indices.pop_back();
        }
        indices.push_back(b);
        // we've just added in[b]. Maybe we must increase 'a'
        while(in[indices[vector_start]].first > in[b].second) {
            a = indices[vector_start] + 1;
            ++vector_start;
        }
        answer = max(answer, b - a + 1); // interval [a, b] is ok
    }
    printf("%d\n", answer);
}
