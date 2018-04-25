// quicksort.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include <time.h>

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

using namespace std;

clock_t start, stop;
double czas;

template < class typ >
void quicksort_r(typ *tablica, long lewy, long prawy)
{
	long i, j;
	typ piwot;

	i = (lewy + prawy) / 2;
	piwot = tablica[i]; tablica[i] = tablica[prawy];
	for (j = i = lewy; i < prawy; i++)
		if (tablica[i] > piwot)
		{
			swap(tablica[i], tablica[j]);
			j++;
		}
	tablica[prawy] = tablica[j]; tablica[j] = piwot;
	if (lewy < j - 1)  quicksort_r(tablica, lewy, j - 1);
	if (j + 1 < prawy) quicksort_r(tablica, j + 1, prawy);
}

template < class typ >
void mergesort(typ *tablica,typ *tablica2, int pierwszy, int ostatni)
{
	int srodek, i, i1, i2;

	srodek = (pierwszy + ostatni + 1) / 2;
	if (srodek - pierwszy > 1) 
		mergesort(tablica, tablica2, pierwszy, srodek - 1);
	if (ostatni - srodek > 0) 
		mergesort(tablica, tablica2, srodek, ostatni);
	i1 = pierwszy; i2 = srodek;
	for (i = pierwszy; i <= ostatni; i++)
	{
		if ((i1 == srodek) || ((i2 <= ostatni) && (tablica[i1] > tablica[i2])))
			tablica2[i]=tablica[i2++];
		else
			tablica2[i]=tablica[i1++];
	}
	for (i = pierwszy; i <= ostatni; i++) tablica[i] = tablica2[i];
}



int main()
{
	double average = 0;
	long i, rozmiar = 0;
	int rozmiartab[4] = { 10000, 50000, 100000, 350000 };
	srand(time(NULL));
	cout << "### MERGESORT ###" << endl;
	cout << "-----------------" << endl;

	for (int k = 0; k < 4; k++)
	{
		rozmiar = rozmiartab[k];
		int *tablica = new int[rozmiar];
		int *tablica2 = new int[rozmiar];
		for (int j = 0; j < 100; j++)
		{
			for (i = 0; i < rozmiar; i++) tablica[i] = rand() % 100;
			mergesort<int>(tablica, tablica2, 0, rozmiar-1);
			//quicksort_r<int>(tablica, 0, rozmiar - 1);

			start = clock();
			mergesort<int>(tablica, tablica2, 0, rozmiar - 1);
			stop = clock();
			czas = (double)(stop - start) / CLOCKS_PER_SEC;
			cout << czas << " s" << endl;
			cout << endl;
			average += czas;
		}
		cout << "Average: " << average / 100 << endl;
		average = 0;
		delete[] tablica;
		cout << endl;
		cout << endl;
	}

	return 0;
}
