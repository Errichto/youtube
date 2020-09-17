class Solution {
    map<pair<int,int>, int> answer;
    string text1, text2;
    int my_LCS(int len1, int len2) {
        if(len1 == 0 || len2 == 0) {
            return 0;
        }
        pair<int,int> my_state{len1, len2};
        auto it = answer.find(my_state);
        if(it != answer.end()) {
            return it->second;
        }
        if(text1[len1-1] == text2[len2-1]) {
            return answer[my_state] = 1 + my_LCS(len1-1, len2-1);
        }
        return answer[my_state] = max(my_LCS(len1-1, len2), my_LCS(len1, len2-1));
    }
    int longestCommonSubsequence(string _text1, string _text2) {
        text1 = _text1;
        text2 = _text2;
        return my_LCS(text1.length(), text2.length());
    }
        
        /*
        if(text1.empty() || text2.empty()) {
            return 0;
        }
        pair<int,int> my_state{text1.length(),text2.length()};
        auto it = answer.find(my_state);
        if(it != answer.end()) {
            return it->second;
        }
        if(text1.back() == text2.back()) {
            text1.pop_back();
            text2.pop_back();
            return answer[my_state] = 1 + longestCommonSubsequence(text1, text2);
        }
        return answer[my_state = max(longestCommonSubsequence(text1, string(text2.begin(), text2.end()-1)),
                   longestCommonSubsequence(text2, string(text1.begin(), text1.end()-1)));*/
    }
};
