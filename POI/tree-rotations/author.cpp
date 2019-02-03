/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Rotacje na drzewie                               *
 *   Autor:             Adam Karczmarz                                   *
 *   Opis:              Rozwiazanie wzorcowe                             *
 *   Zlozonosc czasowa: O(n*lg^2(n))                                     *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cassert>

#define REP(AA,BB) for(AA=0; AA<(BB); ++AA)
#define FOR(AA,BB,CC) for(AA=BB; AA<(CC); ++AA)
#define FC(AA,BB) for(typeof(AA.begin()) BB=AA.begin(); BB!=AA.end(); ++BB)

using namespace std;

// wezel drzewa 
struct node;
struct node {
	node *left, *right, *prev;
	int sz, mn; long long inv; 
	node() { left=right=prev=0; inv=0LL; }
};

node *p[200100]; int cur, cnt[200100], MX, f;

// drzewo potegowe
int get(int x) {
	int res=0;
	while(x>0) {
		res+=cnt[x];
		x-=x&(-x);
	}
	return res;
}

void ins(int x, int v) {
	while(x<=MX) {
		cnt[x]+=v;
		x+=x&(-x);
	}
}

// wczytywanie wejscia
void read_input(node *tr) {
	int c; f=scanf("%d", &c);
	if(c!=0) {
		tr->sz=1;
		tr->mn=++cur;
		p[c-1]=tr;
	}
	else {
		tr->left=new node; tr->right=new node;
		read_input(tr->left); read_input(tr->right);
		tr->mn=tr->left->mn;
		tr->sz=tr->left->sz+tr->right->sz;
	}
}

// wstepne rotacje i liczenie dla kazdego wezla "prawego" poprzednika na sciezce do korzenia
void prepare(node *tr, node *par, int x) {
	if(par!=0) {
		if(x)
			tr->prev=par;
		else
			tr->prev=par->prev;
	}
	if(tr->sz==1)
		return;
	if(tr->right->sz>tr->left->sz)
		swap(tr->left, tr->right);
	prepare(tr->left, tr, 0); prepare(tr->right, tr, 1);
}

// obliczanie wyniku przy znanej liczbie inwersji w kazdym wezle
long long compute(node *tr) {
	if(tr->sz==1)
		return 0LL;
	return min(tr->inv, (long long)(tr->left->sz)*(tr->right->sz)-tr->inv)+compute(tr->left)+compute(tr->right);
}

int main(void) {
	int n, i; node *root=new node, *tmp;
	f=scanf("%d", &n); MX=n;
	read_input(root); prepare(root, 0, 0);
	FOR(i,1,n+1)
		ins(i,1);
	REP(i,n) {
		tmp=p[i]->prev;
		// aktualizacja "prawych" poprzednikow na sciezce do korzenia
		while(tmp!=0) {
			tmp->inv+=get(tmp->left->mn+tmp->left->sz-1)-get(tmp->left->mn-1);
			tmp=tmp->prev;
		}
		ins(p[i]->mn, -1);
	}
	printf("%lld\n", compute(root));
	return 0;
}

