/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Smieci                                           *
 *   Autor:             Zbigniew Wojna                                   *
 *   Zlozonosc czasowa: O(n + m)                                         *
 *   Opis:              Rozwiazanie wzorcowe                             *
 *                      Znajdujemy cykl Eulera w grafie i wypisujemy     *
 *                      cykle proste                                     *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <string>
#include <queue>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <list>
#include <stack>
using namespace std;
#define PB push_back
#define MP make_pair
#define X first
#define Y second
#define REP(i,n) for(int i=0;i<(n);i++)
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define FORD(i,a,b) for(int i=(a);i>=(b);i--)
#define FORE(i,x) for(__typeof((x).begin()) i=(x).begin();i != (x).end();++i)
#define present(c,x) ((c).find(x) != (c).end()) 
#define cpresent(c,x) (find(all(c),x) != (c).end())
#define SZ(x) int((x).size()) 
#define ALL(x) (x).begin(),(x).end()
#define CLR(x,w) memset((x),w,sizeof (x))
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef vector<pii> vii;
typedef long long int lli;
typedef vector<lli> vl;
typedef pair<lli, lli> pll;
typedef vector<pll> vll;

typedef list<pii>::iterator iter;
#define MAXN 100005
#define MAXM 1000005


int ile = 1, n, m, a, b, licznik[MAXN], ki;
bool s1, s2, vis[MAXN];
iter it[2 * MAXM];
list<pii> kraw[MAXN];
stack<int> S;
vector<int> cykl, temp, res, dlg;

void add(int x,int y){
	kraw[x].push_front(pii(y,ile));
	kraw[y].push_front(pii(x,ile+1));
	it[ile++] = kraw[y].begin();
	it[ile++] = kraw[x].begin();
	licznik[x]++;
	licznik[y]++;
}

bool check(){
	FOR(i, 1, n)
		if(licznik[i] & 1)
			return false;
	return true;
}

void go(int x){
	int y;
	while(kraw[x].begin() != kraw[x].end()){
		S.push(x);
		y = kraw[x].begin()->first;
		kraw[y].erase(it[kraw[x].begin()->second]);
		kraw[x].pop_front();
		x = y;
	}	
}


void wypisz(){
	int akt;
	FORE(i, cykl){
		if(vis[*i]){
			res.PB(*i);
			ki = 1;
			while(vis[*i]){
				akt = temp.back();
				temp.pop_back();
				res.PB(akt);
				ki++;
				vis[akt] = false;
			}	
			res.PB(0);
			dlg.PB(ki);
		}
		temp.PB(*i);
		vis[*i] = true;
	}
	
	akt = 0;
	cout << dlg.size() << endl;
	FORE(j, dlg){
		cout << *j - 1 << " ";
		while(res[akt]){
			cout << res[akt] << " ";
			akt++;
		}
		cout << endl;
		akt++;
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin >> n >> m;
	REP(i, m){
		cin >> a >> b >> s1 >> s2;
		if(s1 != s2)
			add(a,b);
	}

	if (!check()){
		cout << "NIE" << endl;
		return 0;
	}

	FOR(i,1,n)
		if(kraw[i].begin() != kraw[i].end()){
			S.push(i);
			while(!S.empty()){
				int x = S.top(); 
				S.pop();
				cykl.PB(x);
				go(x);
			}
		}	
	wypisz();
	return 0;
}
