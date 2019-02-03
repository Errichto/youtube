// POI 18-2, Difference
// O(N * A + A^2) where A is the alphabet size
#include <bits/stdc++.h>
using namespace std;
const int NAX = 1e6 + 5;
char s[NAX];
vector<int> occurrences[26]; // occurrences[x] - indices where letter 'x' occurs

int consider(const vector<int>& A, const vector<int>& B) {
    if(A.empty() || B.empty()) {
        return 0;
    }
    // merge the two lists/vectors into one with -1, +1
    vector<int> seq;
    int pointer2 = 0;
    for(int i : A) {
        while(pointer2 < (int) B.size() && B[pointer2] < i) {
            seq.push_back(-1); // indices from B are changed to -1
            ++pointer2;
        }
        seq.push_back(1); // indices from A are changed to +1
    }
    while(pointer2 < (int) B.size()) {
        seq.push_back(-1);
        ++pointer2;
    }
    
    //~ for(int x : seq) {
        //~ printf("%d ", x);
    //~ }
    //~ puts("");
    
    // find the maximum sum of a subarray that contains at least one -1
    const int n = seq.size();
    vector<int> pref{0};
    for(int x : seq) {
        pref.push_back(pref.back() + x); // prefix sums
    }
    vector<int> pref_min(n + 1);
    for(int i = 1; i <= n; ++i) {
        pref_min[i] = min(pref_min[i-1], pref[i]); // minima of prefix sums
    }
    
    //~ for(int x : pref) {
        //~ printf("%d ", x);
    //~ }
    //~ puts("");
    
    int answer = 0;
    int last_negative = -1; // fake value, meaning there were no negative values so far
    for(int i = 0; i < n; ++i) {
        if(seq[i] == -1) {
            last_negative = i;
        }
        if(last_negative != -1) {
            answer = max(answer, pref[i+1] - pref_min[last_negative]);
        }
    }
    return answer;
}

int main() {
    int n;
    scanf("%d", &n);
    scanf("%s", s);
    assert(n == (int) strlen(s));
    for(int i = 0; i < n; ++i) {
        occurrences[s[i]-'a'].push_back(i);
    }
    int answer = 0;
    for(int a = 0; a < 26; ++a) {
        for(int b = 0; b < 26; ++b) {
            if(a != b) {
                answer = max(answer, consider(occurrences[a], occurrences[b]));
            }
        }
    }
    printf("%d\n", answer);
}
