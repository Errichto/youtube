/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Temperatura                                      *
 *   Autor:             Bartlomiej Wolowiec                              *
 *   Zlozonosc czasowa: O(n)                                             *
 *   Opis:              Rozwiazanie wzorcowe                             *
 *                                                                       *
 *************************************************************************/

/* - */
#include <iostream>
#include <algorithm>
#include <queue>
#include <cstdio>
#define PII pair<int, int>
using namespace std;
/* * */

#define MAX_N 1000000
int Tmin[MAX_N];
int Tmax[MAX_N];


#define TEMP second
#define POZ first

int main(void){
    int n, wynik=0;

    if (scanf("%i", &n) != 1) return 1;
    for(int i=0; i<n; i++)
        if(scanf("%i%i", &Tmin[i], &Tmax[i]) != 2) return 1;

    deque<PII> Q;
    for(int i=0; i<n; i++){
        int a=Tmin[i], b=Tmax[i];
        int naj = i;
        while(!Q.empty() && Q.front().TEMP <= a){
            naj = min(naj, Q.front().POZ);
            Q.pop_front();
        }
        Q.push_front(PII(naj, a));
        while(!Q.empty() && Q.back().TEMP > b){
            wynik = max(wynik, i-Q.back().POZ);
            Q.pop_back();
        }
    }
    while(!Q.empty()){
        wynik = max(wynik, n-Q.back().POZ);
        Q.pop_back();
    }
    printf("%i\n", wynik);
    return 0;
}
