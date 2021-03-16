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

int D, n_inter, n_streets; // D I S
int n_cars; // V
int F; // finish bonus
map<string, int> mapping_names;
vector<string> memo_names;
vector<int> street_freq;
vector<int> priority;

struct Interval {
	int low, high, mod;
};
vector<Interval> intervals;

struct Intersection {
	int id;
	vector<int> ins;
	int cycle_sum;
	vector<pair<int,int>> cycle;
	vector<bool> taken;
	void debug() const {
		for(int r : ins) {
			cerr << street_freq[r] << " ";
		}
		cerr << endl;
	}
	// void gen_ones() {
		// for(int road : ins) {
			// if(!street_freq[road]) {
				// continue;
			// }
			// int len = 1;
			// cycle.emplace_back(road, len);
			// cycle_sum += len;
		// }
	// }
	void compute_intervals() {
		int count_nonempty = 0;
		for(int r : ins) {
			if(street_freq[r]) {
				count_nonempty++;
			}
		}
		for(int r : ins) {
			intervals[r].mod = count_nonempty;
		}
		cycle.clear();
		taken.clear();
		cycle.resize(count_nonempty);
		taken.resize(count_nonempty);
		// cycle.clear();
		// cycle_sum = 0;
		// for(int road : ins) {
			// if(priority[road]) {
				// cycle.emplace_back(road, priority[road]);
				// cycle_sum += priority[road];
			// }
		// }
		// int pref = 0;
		// for(int i = 0; i < (int) cycle.size(); ++i) {
			// int road = cycle[i].first;
			// int len = cycle[i].second;
			// [pref, pref + len - 1]
			// intervals[road] = Interval{pref, pref + len - 1, cycle_sum};
			// pref += len;
		// }
	}
	void print() const {
		printf("%d\n", id);
		printf("%d\n", (int) cycle.size());
		assert(!cycle.empty());
		set<int> used;
		for(pair<int,int> p : cycle) {
			if(p.second != 0) {
				used.insert(p.first);
			}
		}
		// ::debug() << imie(ins);
		// ::debug() << imie(cycle);
		for(pair<int,int> p : cycle) {
			if(p.second == 0) {
				for(int r : ins) {
					if(!used.count(r)) {
						p.first = r;
						used.insert(r);
						p.second = 1;
						break;
					}
				}
			}
			assert(p.second == 1);
			printf("%s %d\n", memo_names[p.first].c_str(), p.second);
		}
	}
};
vector<Intersection> intersections;

struct Street {
	int start, end; // B E
	string name;
	int len, id;
	void read(int _id) {
		id = _id;
		cin >> start >> end;
		intersections[end].ins.push_back(id);
		cin >> name;
		memo_names.push_back(name);
		mapping_names[name] = id;
		cin >> len;
	}
};
vector<Street> streets;

struct Car {
	int id;
	vector<int> path; // street ids
	void debug() const {
		for(int i = 0; i < (int) path.size() - 1; ++i) {
			int inter = streets[path[i]].end;
			cerr << intersections[inter].ins.size() << " ";
		}
		cerr << endl;
	}
	int size() const { return path.size(); }
	void read(int _id) {
		id = _id;
		int cnt;
		cin >> cnt;
		assert(cnt >= 2);
		for(int i = 0; i < cnt; ++i) {
			string s;
			cin >> s;
			auto it = mapping_names.find(s);
			assert(it != mapping_names.end());
			path.push_back(it->second);
			++street_freq[it->second];
		}
	}
};
vector<Car> cars;

void read() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> D >> n_inter >> n_streets >> n_cars >> F;
	priority.resize(n_streets);
	street_freq.resize(n_streets);
	streets.resize(n_streets);
	cars.resize(n_cars);
	intersections.resize(n_inter);
	intervals.resize(n_streets);
	for(int i = 0; i < n_inter; ++i) {
		intersections[i].id = i;
	}
	for(int i = 0; i < n_streets; ++i) {
		streets[i].read(i);
	}
	for(int i = 0; i < n_cars; ++i) {
		cars[i].read(i);
	}
}

void print() {
	int count_nonempty = 0;
	for(Intersection& inter : intersections) {
		if(!inter.cycle.empty()) {
			count_nonempty++;
		}
	}
	printf("%d\n", count_nonempty);
	for(Intersection& inter : intersections) {
		if(!inter.cycle.empty()) {
			inter.print();
		}
	}
}

// uses global array: int priority[n_streets];
void compute_intervals() {
	for(int road = 0; road < n_streets; ++road) {
		intervals[road] = {-1, -1, -1};
	}
	for(Intersection& inter : intersections) {
		inter.compute_intervals();
	}
}

// returns (score, finished)
pair<int,int> simulate() {
	compute_intervals();
	int score = 0, finished = 0;
	vector<int> nxt_street(n_cars);
	vector<int> when_avail(n_cars);
	vector<int> my_number(n_cars);
	vector<int> passed(n_streets);
	vector<int> reached(n_streets);
	
	auto put_car = [&](int car_id) {
		const Car& car = cars[car_id];
		int street_id = car.path[nxt_street[car_id]];
		my_number[car_id] = reached[street_id]++;
	};
	
	for(int car_id = 0; car_id < n_cars; ++car_id) {
		put_car(car_id);
	}
	vector<int> when_last_used(n_streets, -1);
	vector<int> order(n_cars);
	for(int i = 0; i < n_cars; ++i) {
		order[i] = i;
	}
	for(int time = 0; time < D; ++time) {
		random_shuffle(order.begin(), order.end());
		for(int car_id : order) {
		// for(int car_id = n_cars - 1; car_id >= 0; --car_id) {
		// for(int car_id = 0; car_id < n_cars; ++car_id) {
			const Car& car = cars[car_id];
			if(nxt_street[car_id] == car.size() - 1 || when_avail[car_id] > time) {
				continue;
			}
			int street_id = car.path[nxt_street[car_id]];
			if(when_last_used[street_id] == time) {
				continue;
			}
			if(passed[street_id] == my_number[car_id]) {
				Interval& interval = intervals[street_id];
				int tmp = time % interval.mod;
				int inter = streets[street_id].end;
				if(interval.low == -1 && !intersections[inter].taken[tmp]) {
					interval.low = interval.high = tmp;
					intersections[inter].taken[tmp] = true;
					intersections[inter].cycle[tmp] = {street_id, 1};
				}
				if(interval.low <= tmp && tmp <= interval.high) {
					passed[street_id]++;
					when_last_used[street_id] = time;
					bool is_last_road = (++nxt_street[car_id] == car.size() - 1);
					assert(nxt_street[car_id] < car.size());
					when_avail[car_id] = time + streets[car.path[nxt_street[car_id]]].len;
					if(!is_last_road) {
						put_car(car_id);
					}
					else if(when_avail[car_id] <= D) {
						score += F + D - when_avail[car_id];
						finished++;
					}
				}
			}
		}
	}
	return {score, finished};
}

int main() {
	read();
	
	pair<int, int> best;
	best.first = -1;
	for(int rep = 0; rep < 1000; ++rep) {
		srand(rep);
		pair<int,int> score_finished = simulate();
		if(score_finished.first > best.first) {
			cerr << score_finished.first << "    cars = " << score_finished.second << endl;
			best = {score_finished.first, rep};
		}
	}
	srand(best.second);
	assert(best.first != -1);
	// priority = best.second;
	pair<int,int> score_finished = simulate();
	cerr << score_finished.first << endl;
	print();
}
