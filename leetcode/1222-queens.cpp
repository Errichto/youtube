// https://leetcode.com/problems/queens-that-can-attack-the-king/
class Solution {
    bool inside(int row, int col) {
        return 0 <= row && row < 8
                && 0 <= col && col < 8;
    }
public:
    vector<vector<int>> queensAttacktheKing(
            vector<vector<int>>& queens,
            vector<int>& king
    ) {
        vector<vector<bool>> taken(8, vector<bool>(8));
        for(vector<int> queen : queens) {
            taken[queen[0]][queen[1]] = true;
        }
        vector<vector<int>> answer;
        for(int d1 = -1; d1 <= 1; d1++) {
            for(int d2 = -1; d2 <= 1; d2++) {
                if(d1 == 0 && d2 == 0) {
                    continue;
                }
                int row = king[0];
                int col = king[1];
                do {
                    row += d1;
                    col += d2;
                } while(inside(row, col) && !taken[row][col]);
                if(inside(row, col)) {
                    answer.push_back({row, col});
                }
            }
        }
        return answer;
    }
};
