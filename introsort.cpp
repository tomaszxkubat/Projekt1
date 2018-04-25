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

template <class Typ>
void Heapify(Typ *Tablica, long i, long Rozmiar)
{
	long j;
	while (i <= Rozmiar / 2)
	{
		j = 2 * i;
		if (j + 1 <= Rozmiar && Tablica[j + 1]>Tablica[j])
			j = j + 1;
		if (Tablica[i] < Tablica[j])
			swap(Tablica[i], Tablica[j]);
		else break;
		i = j;
	}
}
template <class Typ>
void HeapSort(Typ *Tablica, long Rozmiar)
{
	long i;
	for (i = Rozmiar / 2; i>0; --i)
		Heapify(Tablica - 1, i, Rozmiar);
	for (i = Rozmiar - 1; i>0; --i)
	{
		swap(Tablica[0], Tablica[i]);
		Heapify(Tablica - 1, 1, i);
	}
}
template <class Typ>
int Quicksort(Typ *Tablica, long Lewy, long Prawy, int Warunek)
{

	int i = 1, j;
	int Piwot;
	
		i = (Lewy + Prawy) / 2;
		Piwot = Tablica[i]; Tablica[i] = Tablica[Prawy];
		for (j = i = Lewy; i < Prawy; i++)
			if (Tablica[i] < Piwot)
			{
				swap(Tablica[i], Tablica[j]);
				j++;
			}
		Tablica[Prawy] = Tablica[j]; Tablica[j] = Piwot;
		if (Warunek != 0)
		{
		if (Lewy < j - 1)  Quicksort(Tablica, Lewy, j - 1, Warunek - 1);
		if (j + 1 < Prawy) Quicksort(Tablica, j + 1, Prawy, Warunek - 1);
	}
	else
		HeapSort(Tablica, Prawy);
	return 0;
}


template <class Typ>
void IntroSort(Typ *Tablica, long Rozmiar, int Warunek)
{
	Quicksort(Tablica, 0, Rozmiar - 1, Warunek);
}

int main()
{

	double average = 0;
	long i, rozmiar = 0;
	int rozmiartab[4] = { 10000, 50000, 100000, 350000 };
	srand(time(NULL));
	cout << "### INTROSORT ###" << endl;
	cout << "-----------------" << endl;

	for (int k = 0; k < 4; k++)
	{
		rozmiar = rozmiartab[k];
		int *tablica = new int[rozmiar];
			for (int j = 0; j < 100; j++)
		{
			for (i = 0; i < rozmiar; i++) tablica[i] = rand() % 100;

			//quicksort_r<int>(tablica, 0, rozmiar-1);
		
			start = clock();
			IntroSort(tablica, rozmiar, (int)floor(2 * log(rozmiar)));
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