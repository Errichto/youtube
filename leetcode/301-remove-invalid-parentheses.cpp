
vector<int> pre;
set<pair<pair<int,int>,string>> visited;
void rec(int i, int balance, string here, const string& s, vector<string>& ret, int& best_len) {
    if(balance > pre[i]) {
        return;
    }
    pair<pair<int,int>,string> state{{i,balance},here};
    if(!visited.insert(state).second) {
        return;
    }
    if(i == (int) s.length()) {
        if(balance != 0) {
            return;
        }
        if(here.length() > best_len) {
            ret.clear();
            best_len = here.length();
            ret.push_back(here);
        }
        else if(here.length() == best_len) {
            ret.push_back(here);
        }
        return;
    }
    if(s[i] == '(' || s[i] == ')') {
        rec(i + 1, balance, here, s, ret, best_len);
    }
    if(s[i] == '(') balance++;
    if(s[i] == ')') balance--;
    if(balance < 0) return;
    here += s[i];
    rec(i + 1, balance, here, s, ret, best_len);
}

class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        int n = s.length();
        pre.clear();
        pre.resize(n + 1);
        visited.clear();
        for(int i = 0; i <= n; ++i) {
            for(int j = i; j < n; ++j) {
                if(s[j] == ')') {
                    pre[i]++;
                }
            }
        }
        vector<string> ret;
        int best_len = 0;
        rec(0, 0, "", s, ret, best_len);
        sort(ret.begin(), ret.end());
        ret.resize(  unique(ret.begin(), ret.end()) - ret.begin() );
        return ret;
    }
};
