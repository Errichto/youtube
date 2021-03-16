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
// debug & operator << (debug & dd, P p) { dd << "(" << p.x << ", " << p.y << ")"; return dd; }

int dur, n_inter, n_streets; // D I S
int n_cars; // V
int F; // finish bonus

struct Intersection {
	vector<int> ins;
};
vector<Intersection> intersections;

map<string, int> mapping_names;
struct Street {
	int start, end; // B E
	string name; // todo, change to int
	int len, id;
	void read(int _id) {
		id = _id;
		cin >> start >> end;
		intersections[end].ins.push_back(id);
		cin >> name;
		mapping_names[name] = id;
		cin >> len;
	}
};
vector<Street> streets;

struct Car {
	int id;
	vector<int> path; // street ids
	void read(int _id) {
		id = _id;
		int cnt;
		cin >> cnt;
		for(int i = 0; i < cnt; ++i) {
			string s;
			cin >> s;
			auto it = mapping_names.find(s);
			assert(it != mapping_names.end());
			path.push_back(it->second);
		}
	}
};
vector<Car> cars;

void read() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> dur >> n_inter >> n_streets >> n_cars >> F;
	streets.resize(n_streets);
	cars.resize(n_cars);
	intersections.resize(n_inter);
	for(int i = 0; i < n_streets; ++i) {
		streets[i].read(i);
	}
	for(int i = 0; i < n_cars; ++i) {
		cars[i].read(i);
	}
}

int main() {
	read();
	printf("%d\n", n_inter);
	for(int i = 0; i < n_inter; ++i) {
		printf("%d\n", i);
		printf("%d\n", (int) intersections[i].ins.size());
		for(int street_id : intersections[i].ins) {
			printf("%s %d\n", streets[street_id].name.c_str(), 1);
		}
	}
}
