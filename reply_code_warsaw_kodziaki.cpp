#include "bits/stdc++.h"
using namespace std;
#define sim template < class c
#define ris return * this
#define dor > debug & operator <<
#define eni(x) sim > typename \
  enable_if<sizeof dud<c>(0) x 1, debug&>::type operator<<(c i) {
sim > struct rge { c b, e; };
sim > rge<c> range(c i, c j) { return rge<c>{i, j}; }
sim > auto dud(c* x) -> decltype(cerr << *x, 0);
sim > char dud(...);
struct debug {
#ifdef LOCAL
~debug() { cerr << endl; }
eni(!=) cerr << boolalpha << i; ris; }
eni(==) ris << range(begin(i), end(i)); }
sim, class b dor(pair < b, c > d) {
  ris << "(" << d.first << ", " << d.second << ")";
}
sim dor(rge<c> d) {
  *this << "[";
  for (auto it = d.b; it != d.e; ++it)
    *this << ", " + 2 * (it == d.b) << *it;
  ris << "]";
}
#else
sim dor(const c&) { ris; }
#endif
};
#define imie(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "

using ll = long long;

int H, W, count_clients, count_offices;
const int nax = 1005;
char grid[nax][nax];
int cost[nax][nax];
int id_client[nax][nax];
int odl[155][nax][nax];

const ll BIG_INF = 1e18L + 5;
const int INF = 1e9 + 5;
//~ void bfs(int row, int col,

struct Client {
  int row, col, reward;
  void read(int _id) {
    scanf("%d%d%d", &col, &row, &reward);
    id_client[row][col] = _id;
  }
};

struct Office {
  int row, col;
  
};





// Marek
constexpr int inf = INF;
int DajKoszt(char c) {
  switch (c) {
    case '#': return inf;
    case '~': return 800;
    case '*': return 200;
    case '+': return 150;
    case 'X': return 120;
    case '_': return 100;
    case 'H': return 70;
    case 'T': return 50;
    default:
      debug() << imie(c) imie(int(c));
      assert(false);
  }
}
const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, -1, 1};
void LiczOdleglosci() {
  auto LiczOd = [&](int indeks, int r_, int c_) -> void {
    vector<vector<pair<int, int>>> dist(1000);
    auto Daj = [&](int x) -> vector<pair<int, int>>& {
      if ((int) dist.size() <= x) {
        //debug() << imie(x);
        dist.resize(x + 1);
      }
      return dist[x];
    };
    for (int r = 0; r < H; r++) {
      for (int c = 0; c < W; c++) {
        odl[indeks][r][c] = inf;
      }
    }
    vector<vector<bool>> juz(H, vector<bool>(W, false));
    Daj(0).emplace_back(r_, c_);
    for (int o = 0; o < (int) dist.size(); o++) {
      for (int i = 0; i < (int) dist[o].size(); i++) {
        const int r = dist[o][i].first;
        const int c = dist[o][i].second;
        const int noo = o + DajKoszt(grid[r][c]);
        if (juz[r][c]) continue;
        juz[r][c] = true;
        odl[indeks][r][c] = o;
        for (int j = 0; j < 4; j++) {
          const int rr = r + dx[j];
          const int cc = c + dy[j];
          if (0 <= rr and rr < H and 0 <= cc and cc < W) {
            if (!juz[rr][cc] and grid[rr][cc] != '#') {
              Daj(noo).emplace_back(rr, cc);
            }
          }
        }
      }
    }
  };
  for (int r = 0; r < H; r++) {
    for (int c = 0; c < W; c++) {
      if (id_client[r][c] >= 0) {
        debug() << imie(r) imie(c) imie(id_client[r][c]);
        LiczOd(id_client[r][c], r, c);
      }
    }
  }
}
string Odzyskaj(int r, int c, int r2, int c2) { // office, client
  static constexpr char kier[4] = {'U', 'D', 'L', 'R'};
  const int id = id_client[r2][c2];
  //debug() << imie(r) imie(c) imie(r2) imie(c2) imie(id);
  assert(id >= 0);
  assert(odl[id][r][c] < inf);
  string res;
  int koszt = 0;
  while (r != r2 or c != c2) {
    int rrr = -1;
    int ccc = -1;
    int ooo = inf;
    char znak = '\0';
    for (int i = 0; i < 4; i++) {
      const int rr = r + dx[i];
      const int cc = c + dy[i];
      if (0 <= rr and rr < H and 0 <= cc and cc < W) {
        //debug() << imie(rr) imie(cc) imie(odl[id][rr][cc]);
        const int oo = odl[id][rr][cc] + DajKoszt(grid[rr][cc]);
        if (ooo > oo) {
          ooo = oo;
          rrr = rr;
          ccc = cc;
          znak = kier[i];
        }
      }
    }
    //debug() << imie(rrr) imie(ccc) imie(ooo) imie(znak);
    assert(rrr != -1);
    r = rrr;
    c = ccc;
    koszt += DajKoszt(grid[r][c]);
    res.push_back(znak);
  }
  //debug() << imie(koszt);
  return res;
}








int main() {
  scanf("%d%d%d%d", &W, &H, &count_clients, &count_offices);
  vector<Client> clients(count_clients);
  for(int row = 0; row < H; ++row) {
    for(int col = 0; col < W; ++col) {
      id_client[row][col] = -1;
    }
  }
  for(int i = 0; i < count_clients; ++i) {
    clients[i].read(i);
  }
  for(int row = 0; row < H; ++row) {
    scanf("%s", grid[row]);
  }
  LiczOdleglosci();
  //~ vector<Office> offices;
  //~ for(int row = 0; row < H; ++row) {
    //~ for(int col = 0; col < W; ++col) {
      //~ if(grid[row][col] != '#' && id_client[row][col] != -1 && (int) offices.size() < count_offices) {
        //~ offices.push_back(Office{row, col});
      //~ }
    //~ }
  //~ }
  
  vector<int> now_best_distance(count_clients, INF);
  vector<vector<bool>> is_office(H, vector<bool>(W));
  vector<pair<int,int>> offices;
  
  auto find_best_office = [&]() {
    pair<ll, pair<int,int>> best = make_pair(-1LL, make_pair(-1, -1));
    for(int row = 0; row < H; ++row) {
      for(int col = 0; col < W; ++col) {
        if(id_client[row][col] == -1 && !is_office[row][col] && grid[row][col] != '#') {
          ll would = 0;
          for(int c = 0; c < count_clients; ++c) {
            if(odl[c][row][col] != inf) {
              int reward = clients[c].reward;
              if(reward >= odl[c][row][col] || odl[c][row][col] < now_best_distance[c]) {
                would += reward - odl[c][row][col];
                if(reward < now_best_distance[c]) {
                  would -= reward - now_best_distance[c];
                }
              }
            }
          }
          best = max(best, make_pair(would, make_pair(row, col)));
        }
      }
    }
    pair<int,int> off = best.second;
    //~ static bool started = false;
    //~ if(!started) {
      //~ assert(id_client[10][970] != -1);
      //~ off = {10, 971};
      //~ started = true;
    //~ }
    int row = off.first;
    int col = off.second;
    assert(row != -1);
    assert(!is_office[row][col]);
    is_office[row][col] = true;
    for(int c = 0; c < count_clients; ++c) {
      if(odl[c][row][col] != inf) {
        now_best_distance[c] = min(now_best_distance[c], odl[c][row][col]);
      }
    }
    return make_pair(row, col);
  };
  
  for(int rep = 0; rep < count_offices; ++rep) {
    pair<int,int> off = find_best_office();
    offices.push_back(off);
  }
  for(int c = 0; c < count_clients; ++c) {
    assert(now_best_distance[c] != INF);
  }
  
  for(int rep : {1, 2, 3, 4, 3, 2, 1}) {
    for(int whom = 0; whom < (int) offices.size() - rep; ++whom) {
      for(int i = whom; i < whom + rep; ++i) {
        is_office[offices[i].first][offices[i].second] = false;
      }
      for(int& x : now_best_distance) {
        x = INF;
      }
      for(int i = whom; i < whom + rep; ++i) {
        for(int c = 0; c < count_clients; ++c) {
          for(int o = 0; o < (int) offices.size(); ++o) {
            if(!(whom <= o && o < whom + rep)) {
              now_best_distance[c] = min(now_best_distance[c], odl[c][offices[o].first][offices[o].second]);
            }
          }
        }
        pair<int,int> off = find_best_office();
        is_office[off.first][off.second] = true;
        offices[i] = off;
      }
    }
  }
  
  for(int& x : now_best_distance) {
    x = INF;
  }
  for(int c = 0; c < count_clients; ++c) {
    for(pair<int,int> off : offices) {
      now_best_distance[c] = min(now_best_distance[c], odl[c][off.first][off.second]);
    }
  }
  for(int c = 0; c < count_clients; ++c) {
    assert(now_best_distance[c] != INF);
  }
  
  long long answer = 0;
  
  for(pair<int,int> off : offices) {
    for(int c = 0; c < count_clients; ++c) {
      int tmp = odl[c][off.first][off.second];
      if(clients[c].reward >= tmp || tmp == now_best_distance[c]) {
        printf("%d %d ", off.second, off.first);
        string s = Odzyskaj(off.first, off.second, clients[c].row, clients[c].col);
        answer += clients[c].reward - odl[c][off.first][off.second];
        printf("%s\n", s.c_str());
        now_best_distance[c] = -1; // fake value, not to force something again
      }
    }
  }
  
  cerr << "wynik bez bonusu = " << answer << endl;
}
