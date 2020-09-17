count elements x such that there exists some other element different by at most K
K=4
    
    5 8 8 8 8 8 8 13 14 14 ...
                ^

class Solution {
public:
    int countElements(vector<int>& arr, int K) {
        int n = arr.size();
        sort(arr.begin(), arr.end());
        int prv = -INF, prv_cnt = 0;
        int before_me_value = -INF;
        for(int i = 0; i < n; ++i) {
            if(i == n - 1 || arr[i] != arr[i+1]) {
                if((i!=n-1 && arr[i+1] <= arr[i] + K) || before_me_value >= arr[i]-K) {
                    answer += prv_cnt;
                }
            }
            if(arr[i] == prv) {
                prv_cnt++;
            }
            else {
                before_me_value = prv;
                prv = arr[i];
                prv_cnt = 1;
            }
        }
        return answer;
        
        /* unordered_set<int> s;
        for(int x : arr) {
            s.insert(x);
        }
        int cnt = 0;
        for(int x : arr) {
            if(s.count(x+1) == 1) {
                cnt++;
            }
        }
        return cnt;
        */
    }
};
