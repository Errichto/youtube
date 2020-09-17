// O((HW)^2 * log(HW)), where logarithm comes from a map
// a map is unnecessary, below is commented version without it -- runs 5 times faster when submitted
struct Position {
    pair<int,int> box, me;
    bool operator <(const Position& b) const {
        return make_pair(box, me) < make_pair(b.box, b.me);
    }
};

const int d_row[4] = {-1, 1, 0, 0};
const int d_col[4] = {0, 0, -1, 1};

class Solution {
public:
    int minPushBox(vector<vector<char>>& grid) {
        const int H = grid.size(); // height
        const int W = grid[0].size(); // width
        
        auto available = [&](int row, int col) {
            return 0 <= row && row < H && 0 <= col && col < W
                && grid[row][col] != '#';
        };
        
        pair<int, int> start_box, start_me, target;
        for(int row = 0; row < H; ++row) {
            for(int col = 0; col < W; ++col) {
                if(grid[row][col] == 'B') {
                    start_box = {row, col};
                }
                if(grid[row][col] == 'S') {
                    start_me = {row, col};
                }
                if(grid[row][col] == 'T') {
                    target = {row, col};
                }
            }
        }
        Position start{start_box, start_me};
        vector<vector<Position>> q;
        q.push_back({start});
        set<Position> processed;
        map<Position, int> dist;
        dist[start] = 0;
        for(int cur_dist = 0; cur_dist < (int) q.size(); ++cur_dist) {
            for(int i = 0; i < (int) q[cur_dist].size(); ++i) {
                Position state = q[cur_dist][i];
                if(state.box == target) {
                    return cur_dist;
                }
                if(processed.count(state)) {
                    continue;
                }
                processed.insert(state);
                //cout << state.box.first << "," << state.box.second << ", "
                //        << state.me.first << "," << state.me.second << endl;
                assert(dist[state] == cur_dist);
                for(int dir = 0; dir < 4; ++dir) {
                    int new_row = state.me.first + d_row[dir];
                    int new_col = state.me.second + d_col[dir];
                    if(available(new_row, new_col)) {
                        pair<int,int> new_box = state.box;
                        pair<int,int> new_me = {new_row, new_col};
                        int L = 0;
                        if(new_me == new_box) {
                            L++; // I'm pushing a box
                            new_box.first += d_row[dir];
                            new_box.second += d_col[dir];
                            if(!available(new_box.first, new_box.second)) {
                                continue;
                            }
                        }
                        Position new_state{new_box, new_me};
                        int dist2 = dist[state] + L;
                        if(dist.count(new_state) == 0 || dist[new_state] > dist2) {
                            dist[new_state] = dist2;
                            while(dist2 >= (int) q.size()) {
                                q.push_back({});
                            }
                            q[dist2].push_back(new_state);
                        }
                    }
                }
            }
        }
        return -1;
    }
};
/*
struct Position {
    pair<int,int> box, me;
    bool operator <(const Position& b) const {
        return make_pair(box, me) < make_pair(b.box, b.me);
    }
};

const int d_row[4] = {-1, 1, 0, 0};
const int d_col[4] = {0, 0, -1, 1};

class Solution {
public:
    int minPushBox(vector<vector<char>>& grid) {
        const int H = grid.size(); // height
        const int W = grid[0].size(); // width
        
        auto available = [&](int row, int col) {
            return 0 <= row && row < H && 0 <= col && col < W
                && grid[row][col] != '#';
        };
        
        pair<int, int> start_box, start_me, target;
        for(int row = 0; row < H; ++row) {
            for(int col = 0; col < W; ++col) {
                if(grid[row][col] == 'B') {
                    start_box = {row, col};
                }
                if(grid[row][col] == 'S') {
                    start_me = {row, col};
                }
                if(grid[row][col] == 'T') {
                    target = {row, col};
                }
            }
        }
        Position start{start_box, start_me};
        vector<vector<Position>> q;
        q.push_back({start});
        set<Position> processed;
        //map<Position, int> dist;
        const int INF = 1e9 + 5;
        vector<vector<vector<vector<int>>>> dist(H, vector<vector<vector<int>>>(W, vector<vector<int>>(H, vector<int>(W,INF))));
        #define DIST(state) dist[state.box.first][state.box.second][state.me.first][state.me.second]
        DIST(start) = 0;
        for(int cur_dist = 0; cur_dist < (int) q.size(); ++cur_dist) {
            for(int i = 0; i < (int) q[cur_dist].size(); ++i) {
                Position state = q[cur_dist][i];
                if(state.box == target) {
                    return cur_dist;
                }
                if(processed.count(state)) {
                    continue;
                }
                processed.insert(state);
                //cout << state.box.first << "," << state.box.second << ", "
                //        << state.me.first << "," << state.me.second << endl;
                assert(DIST(state) == cur_dist);
                for(int dir = 0; dir < 4; ++dir) {
                    int new_row = state.me.first + d_row[dir];
                    int new_col = state.me.second + d_col[dir];
                    if(available(new_row, new_col)) {
                        pair<int,int> new_box = state.box;
                        pair<int,int> new_me = {new_row, new_col};
                        int L = 0;
                        if(new_me == new_box) {
                            L++; // I'm pushing a box
                            new_box.first += d_row[dir];
                            new_box.second += d_col[dir];
                            if(!available(new_box.first, new_box.second)) {
                                continue;
                            }
                        }
                        Position new_state{new_box, new_me};
                        int dist2 = DIST(state) + L;
                        if(DIST(new_state) > dist2) {
                            DIST(new_state) = dist2;
                            while(dist2 >= (int) q.size()) {
                                q.push_back({});
                            }
                            q[dist2].push_back(new_state);
                        }
                    }
                }
            }
        }
        return -1;
    }
};
*/
