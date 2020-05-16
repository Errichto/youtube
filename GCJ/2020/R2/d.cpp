#include <bits/stdc++.h>
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

typedef long long ll;
const ll INF = 1e12L + 15;

const int nax = 2e5 + 15;
int k, q;
char S[nax];
ll L[nax], R[nax], SWITCH[nax];
int matching[nax];
int simple_parent[nax];
pair<int,pair<ll,ll>> parent[nax][20][2]; // fill with INF
vector<int> children[nax], rev_children[nax], all_children[nax]; // clear!
ll pref_forward[nax], pref_backwards[nax], suf_forward[nax], suf_backwards[nax];
int depth[nax];

void clear() {
	for(int i = 0; i <= k + 1; ++i) {
		children[i].clear();
		rev_children[i].clear();
		all_children[i].clear();
		L[i] = R[i] = SWITCH[i] = matching[i] = simple_parent[i] = depth[i] = 0;
		pref_forward[i] = pref_backwards[i] = suf_forward[i] = suf_backwards[i] = 0;
		for(int j = 0; j < 20; ++j) {
			for(int z : {0, 1}) {
				parent[i][j][z] = {0, {0LL, 0LL}};
			}
		}
	}
}
		

void min_self(ll& a, ll b) {
	a = min(a, b);
}

void read() {
	scanf("%d%d", &k, &q);
	scanf("%s", S);
	assert(k == (int) strlen(S));
	for(int i = k; i >= 1; --i) {
		S[i] = S[i-1];
	}
	S[0] = '(';
	S[k+1] = ')';
	k += 2;
	vector<int> stack;
	SWITCH[0] = SWITCH[k-1] = INF;
	matching[0] = k - 1;
	matching[k-1] = 0;
	for(int i = 0; i < k; ++i) {
		if(S[i] == '(') {
			if(i != 0) {
				assert(!stack.empty());
				simple_parent[i] = stack.back();
				children[stack.back()].push_back(i);
			}
			stack.push_back(i);
		}
		else {
			assert(!stack.empty());
			int left_match = stack.back();
			stack.pop_back();
			matching[i] = left_match;
			matching[left_match] = i;
		}
	}
	assert(stack.empty());
	for(int i = 1; i <= k - 2; ++i) scanf("%lld", &L[i]);
	for(int i = 1; i <= k - 2; ++i) scanf("%lld", &R[i]);
	for(int i = 1; i <= k - 2; ++i) scanf("%lld", &SWITCH[i]);
	for(int i = 0; i < k; ++i) {
		rev_children[i] = children[i];
		reverse(rev_children[i].begin(), rev_children[i].end());
		for(int& x : rev_children[i]) {
			x = matching[x];
		}
	}
	for(int a = 0; a < k; ++a) {
		for(int b : children[a]) {
			all_children[a].push_back(b);
			all_children[a].push_back(matching[b]);
		}
	}
}

void dfs_depth(int a) {
	for(int b : children[a]) {
		depth[b] = depth[matching[b]] = depth[a] + 1;
		dfs_depth(b);
	}
}

void bottom_up(int a) {
	for(int b : children[a]) {
		bottom_up(b);
	}
	ll maybe = 0;
	int prv = a;
	for(int b : children[a]) {
		assert(b == prv + 1);
		maybe += R[prv];
		maybe += SWITCH[b];
		prv = matching[b];
	}
	assert(prv + 1 == matching[a]);
	maybe += R[prv];
	if(SWITCH[a] > maybe) {
		debug() << "bottom up update: " imie(a) imie(SWITCH[a]) imie(maybe);
		SWITCH[a] = maybe;
	}
	
	maybe = 0;
	prv = matching[a];
	for(int b : rev_children[a]) {
		assert(prv - 1 == b);
		maybe += L[prv];
		maybe += SWITCH[b];
		prv = matching[b];
	}
	assert(prv - 1 == a);
	maybe += L[prv];
	if(SWITCH[matching[a]] > maybe) {
		debug() << "bottom up RIGHT update: " imie(matching[a]) imie(SWITCH[matching[a]]) imie(maybe);
		SWITCH[matching[a]] = maybe;
	}
}

void top_down(int a, ll left_to_right, ll right_to_left) {
	min_self(SWITCH[a], left_to_right);
	min_self(SWITCH[matching[a]], right_to_left);
	
	vector<ll> to_the_left, to_the_right;
	// to the left
	
	ll total_to_the_left = SWITCH[a];
	int prv = a;
	for(int b : children[a]) {
		assert(prv + 1 == b);
		total_to_the_left += L[b] + SWITCH[matching[b]];
		prv = matching[b];
	}
	assert(prv + 1 == matching[a]);
	total_to_the_left += L[matching[a]];
	
	ll total_to_the_right = SWITCH[matching[a]];
	prv = a;
	for(int b : children[a]) {
		assert(prv + 1 == b);
		total_to_the_right += R[prv] + SWITCH[b];
		prv = matching[b];
	}
	assert(prv + 1 == matching[a]);
	total_to_the_right += R[prv];
	
	for(int b : children[a]) {
		top_down(b, total_to_the_left - SWITCH[matching[b]], total_to_the_right - SWITCH[b]);
	}
	
	
	
	/*ll suffix = 0;
	int prv = matching[a];
	for(int b : rev_children[a]) {
		assert(b + 1 == prv);
		suffix += R[b];
		suffix += SWITCH[b];
		prv = matching[b];
	}
	assert(prv - 1 == a);
	suffix += L[prv];
	
	ll prefix = 0;
	prv = a;
	for(int b : children[a]) {
		assert(prv + 1 == b);
		prefix += L[b];
		suffix -= L[b];
		suffix -= SWITCH[matching[b]];
		to_the_left.push_back(prefix + suffix + SWITCH[a]);  // SHOULDN'T BE SWITCH[b] !!
		prefix += SWITCH[matching[b]];
		prv = matching[b];
	}*/
	// int s = (int) children.size();
	
}

ll get_R(int a) {
	if(a < matching[a]) {
		return SWITCH[a];
	}
	return R[a];
}
ll get_L(int a) {
	if(a < matching[a]) {
		return L[a];
	}
	return SWITCH[a];
}

void dfs_parent(int a) {
	#define L L_dont
	#define R R_dont
	#define SWITCH SWITCH_dont
	int prv = a;
	ll pref_f = 0, pref_b = 0;
	for(int b : all_children[a]) {
		pref_f += get_L(prv);
		pref_b += get_R(b);
		pref_forward[b] = pref_f;
		pref_backwards[b] = pref_b;
		prv = b;
	}
	ll suf_f = 0, suf_b = 0;
	prv = matching[a];
	for(int i = (int) all_children[a].size() - 1; i >= 0; --i) {
		int b = all_children[a][i];
		suf_f += get_R(b);
		suf_b += get_L(prv);
		suf_forward[b] = suf_f;
		suf_backwards[b] = suf_b;
		prv = b;
	}
	#undef L
	#undef R
	#undef SWITCH
	
	// pair<int,pair<ll,ll>> parent[nax][20][2];
	
	for(int b : all_children[a]) {
		parent[b][0][0] = {a,           {min(pref_backwards[b], suf_forward[b]+SWITCH[matching[a]]), min(pref_forward[b], suf_backwards[b]+SWITCH[a])}};
		parent[b][0][1] = {matching[a], {min(suf_forward[b], pref_backwards[b]+SWITCH[a]), min(suf_backwards[b], SWITCH[matching[a]] + pref_forward[b])}};
		// min_self(parent[b][0][0].second.first, parent[b][0][1].second.first + SWITCH[
		
		for(int j = 0; j < 19; ++j) {
			for(int one : {0, 1}) {
				for(int two : {0, 1}) {
					auto& big = parent[b][j+1][two];
					int b2 = parent[b][j][one].first;
					int b3 = parent[b2][j][two].first;
					big.first = b3;
					min_self(big.second.first, parent[b][j][one].second.first + parent[b2][j][two].second.first);
					min_self(big.second.second, parent[b][j][one].second.second + parent[b2][j][two].second.second);
				}
			}
			// parent[b][j][0] = 
		}
	}
	
	for(int b : children[a]) {
		dfs_parent(b);
	}
}

void test_case() {
	read();
	for(int i = 0; i < k; ++i){ 
		debug() << imie(i) imie(matching[i]) imie(SWITCH[i]);
	}
	depth[0] = depth[matching[0]] = 1;
	dfs_depth(0);
	bottom_up(0);
	top_down(0, INF, INF);
	dfs_parent(0);
	
	while(q--) {
		// TODO
		int start, end;
		scanf("%d%d", &start, &end);
		// from 1 to K
		pair<int, ll> S[2];
		pair<int, ll> E[2];
		S[0] = {start, 0};
		S[1] = {-1, INF};
		if(start > matching[start]) {
			swap(S[0], S[1]);
		}
		E[0] = {end, 0};
		E[1] = {-1, INF};
		if(end > matching[end]) {
			swap(E[0], E[1]);
		}
		int one = depth[start];
		int two = depth[end];
		auto jump_start = [&](int jump) {
			one -= (1 << jump);
			
		};
		auto jump_end = [&](int jump) {
			two -= (1 << jump);
			
		};
		for(int jump = 19; jump >= 0; --jump) {
			if(one >= (two + (1 << jump))) {
				jump_start(jump);
			}
			else if(two >= (one + (1 << jump))) {
				jump_end(jump);
			}
		}
		assert(one == two); // same level
		for(int jump = 19; jump >= 0; --jump) {
			int x = max(S[0].first, S[1].first);
			int y = max(E[0].first, E[1].first);
			x = parent[x][jump][0].first;
			y = parent[y][jump][0].first;
			if(x != y) {
				jump_start(jump);
				jump_end(jump);
			}
		}
		ll answer = INF;
		#define one one2
		#define two two2
		for(int one : {0, 1}) {
			for(int two : {0, 1}) {
				start = S[one].first;
				end = S[two].first;
				if(start == -1 || end == -1) {
					continue;
				}
				ll maybe = S[one].second + E[two].second;
				if(start == end) {
					min_self(answer, maybe);
				}
				else if(matching[start] == end) {
					min_self(answer, maybe + SWITCH[start]);
				}
				else {
					// siblings
					if(start < end) {
						min_self(answer, maybe + suf_forward[start] - suf_forward[end]);
						min_self(answer, maybe + pref_backwards[start] + SWITCH[parent[start][0][0].first] + suf_backwards[end]);
					}
					else {
						min_self(answer, maybe + pref_backwards[start] - pref_backwards[end]);
						min_self(answer, maybe + suf_forward[end] + SWITCH[parent[start][0][1].first] + pref_forward[start]);
					}
				}
			}
		}
		
		printf("%lld\n", answer);
	}
}

int main() {
	int T;
	scanf("%d", &T);
	for(int nr = 1; nr <= T; ++nr) {
		printf("Case #%d: ", nr);
		test_case();
	}
}
