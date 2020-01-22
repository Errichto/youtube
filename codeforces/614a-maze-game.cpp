#include <bits/stdc++.h>
using namespace std;
 
int main() {
    int n, q;
    scanf("%d%d", &n, &q);
    set<pair<int,int>> cells; // O(log) per operation
    int bad_nei = 0;
    for(int i = 0; i < q; i++) {
        int row, col;
        scanf("%d%d", &row, &col);
        bool was_forbidden = cells.count({row, col});
        for(int r = row - 1; r <= row + 1; r++) {
            for(int c = col - 1; c <= col + 1; c++) {
                if(r == row) {
                    continue;
                }
                if(!(1 <= r && r <= 2 && 1 <= c && c <= n)) {
                    continue;
                }
                if(cells.count({r, c})) {
                    if(was_forbidden) {
                        bad_nei--;
                    }
                    else {
                        bad_nei++;
                    }
                }
            }
        }
        if(cells.count({row, col})) {
            cells.erase({row, col});
        }
        else {
            cells.insert({row, col});
        }
        if(bad_nei >= 1) {
            puts("NO");
        }
        else {
            puts("YES");
        }
    }
}
