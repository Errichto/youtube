// https://leetcode.com/problems/jump-game-iv/
class Solution {
public:
    int minJumps(vector<int>& a) {
        int n = a.size();
        vector<bool> visited(n);
        visited[0] = true;
        vector<pair<int,int>> q;
        q.emplace_back(0, 0);
        map<int, vector<int>> occurrences;
        for(int i = 0; i < n; ++i) {
            occurrences[a[i]].push_back(i);
        }
        for(int iq = 0; iq < (int) q.size(); iq++) {
            int i = q[iq].first;
            int dist = q[iq].second;
            if(i == n - 1) {
                return dist;
            }
            for(int j : {i - 1, i + 1}) {
                if(0 <= j && j < n && !visited[j]) {
                    visited[j] = true;
                    q.emplace_back(j, dist + 1);
                }
            }
            for(int j : occurrences[a[i]]) {
                if(!visited[j]) {
                    visited[j] = true;
                    q.emplace_back(j, dist + 1);
                }
            }
            occurrences[a[i]].clear();
        }
        assert(false);
    }
};
