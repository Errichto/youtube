// POI 18-2, Garbage
// O(N+M)
#include <bits/stdc++.h>
using namespace std;
const int NAX = 1e5 + 5;
vector<int> edges[NAX];
vector<int> where_opposite[NAX];

void add_edge(int a, int b) {
    //~ printf("(%d,%d)\n", a, b);
    where_opposite[a].push_back(edges[b].size());
    where_opposite[b].push_back(edges[a].size());
    edges[a].push_back(b);
    edges[b].push_back(a);
}
void remove_last_edge(int a) {
    assert(!edges[a].empty());
    int i = (int) edges[a].size() - 1;
    int b = edges[a][i];
    //~ printf("%d %d %d\n", a, b, i);
    int j = where_opposite[a][i];
    edges[a][i] = -1;
    edges[b][j] = -1;
}

vector<int> so_far; // stack
bool on_stack[NAX];
bool done[NAX];

vector<vector<int>> cycles;

int start; // starting vertex of the current cycle

// returns the beginning of the cycle
void dfs(int a) {
    assert(!done[a] && !on_stack[a]);
    // add to the stack
    on_stack[a] = true;
    so_far.push_back(a);
    while(!edges[a].empty()) {
        int b = edges[a].back();
        if(b == -1) {
            edges[a].pop_back();
            continue;
        }
        remove_last_edge(a);
        edges[a].pop_back();
        if(on_stack[b]) {
            start = b;
            cycles.push_back({}); // start a new cycle
            cycles.back().push_back(a);
            break;
        }
        else {
            dfs(b);
            cycles.back().push_back(a);
            if(start != a) {
                break;
            }
            else {
                start = -1; // the end of the cycle
            }
        }
    }
    // remove from stack
    on_stack[a] = false;
    so_far.pop_back();
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    while(m--) {
        int a, b, s1, s2;
        scanf("%d%d%d%d", &a, &b, &s1, &s2);
        if(s1 != s2) {
            add_edge(a, b);
        }
    }
    for(int a = 1; a <= n; ++a) {
        if(edges[a].size() % 2) { // odd degree
            puts("NIE");
            return 0;
        }
    }
    for(int a = 1; a <= n; ++a) {
        if(!edges[a].empty() && !done[a]) {
            dfs(a);
        }
    }
    printf("%d\n", (int) cycles.size());
    for(vector<int> cycle : cycles) {
        printf("%d", (int) cycle.size());
        cycle.push_back(cycle[0]);
        for(int a : cycle) {
            printf(" %d", a);
        }
        puts("");
    }
}
