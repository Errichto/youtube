/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Roznica                                          *
 *   Autor:             Zbigniew Wojna                                   *
 *   Zlozonosc czasowa: O(n * k)                                         *
 *   Opis:              Rozwiazanie wzorcowe                             *
 *                      Badamy od poczatku i konca mozliwe slowa         *
 *                      dynamicznie uaktualniajac liczbe liter           *
 *                      ktore sie pojawily i mialy sens                  *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <set>
#include <iostream>

using namespace std;

#define REP(i,n) for(int _n=n, i=0;i<_n;++i)
#define FOR(i,a,b) for(int i=(a),_b=(b);i<=_b;++i)
#define FORD(i,a,b) for(int i=(a),_b=(b);i>=_b;--i)
#define FORE(i,x) for(__typeof((x).begin()) i=(x).begin();i != (x).end();++i)
#define X first
#define Y second
#define PB push_back	
#define MP make_pair
#define MAXN 1000005		

int slowo[MAXN];		// tablica z wczytanym slowem
int licznik[26];		// tymczasowa tablica trzymajaca liczby poszczegolnych liter
bool ok[26];			// prawda oznacza ze potrzebujemy jeszcze dodatkowej litery 
						// na poczatku lub na koncu segmentu zlozonego z badanej litery
int n, temp, licz, maks;
char c;


int main()
{
	// wczytanie slowa i przesuniecie
	temp = scanf("%d", &n);
	temp = scanf("%c", &c);
	REP(i, n) 
	{
		temp = scanf("%c", &c);
		slowo[i] = c - 97;
	}	

	// wyliczamy najlepszy fragment dla kazdej litery 
	REP(i, 26)
	{
		
		// czyszczenie
		REP(j, 26)
		{
			ok[j] = false;
			licznik[j] = 0;
		}
		licz = 0;

		// petla po slowie od poczatku, gdy trafimy na badana litere zwiekszamy
		// jej liczbe i sprawdzamy czy max sie poprawil
		// w drugim przypadku zwiekszamy liczbe innej litery o ile ma to sens
		REP(j, n)
			if(slowo[j] == i)
			{
				licz++;
				REP(k, 26)
					if(licz - licznik[k] > maks && licznik[k] > 0)
							maks = max(maks, licz - licznik[k]);
			}
			else
			{
				if(licznik[slowo[j]] < licz + 1)
					licznik[slowo[j]]++;
				if(licznik[slowo[j]] > licz)
					ok[slowo[j]] = true;
				else
					if(ok[slowo[j]] == true)
					{
						ok[slowo[j]] = false;
						licznik[slowo[j]]--;
						maks = max(maks, licz - licznik[slowo[j]]);
					}
			}

		// czyszczenie
		REP(j, 26)
		{
			ok[j] = false;
			licznik[j] = 0;
		}
		licz = 0;

		// petla po slowie od konca
		FORD(j, n - 1, 0)
			if(slowo[j] == i)
			{
				licz++;
				REP(k, 26)
					if(licz - licznik[k] > maks && licznik[k] > 0)
							maks = max(maks, licz - licznik[k]);
			}
			else
			{
				if(licznik[slowo[j]] < licz + 1)
					licznik[slowo[j]]++;
				if(licznik[slowo[j]] > licz)
					ok[slowo[j]] = true;
				else
					if(ok[slowo[j]] == true)
					{
						ok[slowo[j]] = false;
						licznik[slowo[j]]--;
						maks = max(maks, licz - licznik[slowo[j]]);
					}
			}

		
	}


	// wypisanie wyniku
	printf("%d\n", maks);

	return 0;
}

