// mergesort.cpp : Defines the entry point for the console application.
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
void quicksort(typ *tablica,long lewy, long prawy)
{
	long i, j;
	typ piwot;

	i = (lewy + prawy) / 2;
	piwot = tablica[i]; tablica[i] = tablica[prawy];
	for (j = i = lewy; i < prawy; i++)
		if (tablica[i] < piwot)
		{
			swap(tablica[i], tablica[j]);
			j++;
		}
	tablica[prawy] = tablica[j]; tablica[j] = piwot;
	if (lewy < j - 1)  quicksort(tablica, lewy, j - 1);
	if (j + 1 < prawy) quicksort(tablica, j + 1, prawy);
}



int main()
{
	double average=0;
	long i,rozmiar=0;
	int rozmiartab[4] = { 10000, 50000, 100000, 350000 };
	srand(time(NULL));
	cout << "### QUICKSORT ###" << endl;
	cout << "-----------------" << endl;

	for (int k = 0; k < 4; k++)
	{
		rozmiar = rozmiartab[k];
		int *tablica = new int[rozmiar];
		for (int j = 0; j < 100; j++)
		{
			for (i = 0; i < rozmiar; i++) tablica[i] = rand() % 100;

				//quicksort<int>(tablica, 0, rozmiar-1);

			start = clock();
			quicksort<int>(tablica, 0, rozmiar - 1);
			stop = clock();
			czas = (double)(stop - start) / CLOCKS_PER_SEC;
			cout << czas << " s" << endl;

			/*for (i = 0; i < rozmiar; i++)
			{
				cout << tablica[i] << " ";
			} */
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
