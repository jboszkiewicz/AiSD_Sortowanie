#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <chrono>

using namespace std;
using tp = chrono::time_point<std::chrono::system_clock>;
int opPorownania, opSwap;

//////////FUNKCJE POMOCNICZE//////////
void swap(int tab[], int i, int j){
	int tmp = tab[i];
	tab[i] = tab[j];
	tab[j] = tmp;
	opSwap++;
}

void drukuj(int tab[], int start, int end){
	for(int x = start; x < end; x++){
		printf("%d", tab[x]);
		if(x < end - 1) printf(", ");
		else printf("\n");
	}
}

//////////FUNKCJE SORTUJĄCE//////////
void SelectionSort(int tab[], int n){
	for(int k = 0; k < n; k++){
		int max = k;
		for(int j = k; j < n; j++){
			opPorownania++;
			if(tab[j] > tab[max])
				max = j;
		}
		swap(tab, k, max);
	}
}

void InsertionSort(int tab[], int n){
	for(int i = 1; i < n; i++){
		int x = tab[i]; //zapamiętanie elementu
		int j = i - 1;
		bool usedBreak = false;
		while(tab[j] < x){
			opPorownania++;
			tab[j + 1] = tab[j]; //przesunięcie elementu
			opSwap++;
			j--;
			if(j <= 0){
				usedBreak = true;
				break;
			}
		}
		if(!usedBreak) opPorownania++;
		tab[j + 1] = x;
	}
}

void HeapSort(int tab[], int n){
	//budowa kopca
	int i, parent, child;
	for(i = 1; i < n; i++){
		child = i;
		parent = (i - 1) / 2;
		bool usedBreak = false;
		while(tab[parent] > tab[child]){
			opPorownania++;
			swap(tab, parent, child);
			child = parent;
			parent = (child - 1) / 2;
			if(child <= 0){
				usedBreak = true;
				break;
			}
		}
		if(!usedBreak) opPorownania++;
	}

	//sortowanie
	int min_child;
	for(i = n - 1; i > 0; i--){
		swap(tab, 0, i);
		parent = 0;
		child = (parent * 2) + 1;
		while(child < i){
			min_child = (child + 1 < i && tab[child + 1] < tab[child]) ? child + 1: child;
			opPorownania++;
			opPorownania++;
			if(tab[parent] < tab[min_child]) break;
			swap(tab, parent, min_child);
			parent = min_child;
			child = (parent * 2) + 1;
		}
	}
}

void ShellSort(int tab[], int n, bool klawa){
	int przyrost = 1;
	//przyrost Knutha
	for(przyrost = 1; przyrost < n; przyrost = 3 * przyrost + 1);
	przyrost = przyrost / 9;
	//sortowanie
	while(przyrost > 0){
		if(klawa)	printf("Przyrost: %d\n", przyrost);
		for(int i = przyrost; i < n; i++){
			int liczba = tab[i], j;
			bool usedBreak = false;
			for(j = i; tab[j - przyrost] < liczba; j -= przyrost){
				opPorownania++;
				tab[j] = tab[j - przyrost];
				opSwap++;
				if(j < przyrost){
					usedBreak = true;
					break;
				}
			}
			if(!usedBreak) opPorownania++;
			tab[j] = liczba;
		}
		przyrost /= 3;
	}
}

void QuickSort(int tab[], int end, bool klawa,int start = 0){
	int pivot = tab[start], i = start, j = end;
	if(klawa) printf("Pivot: %d\n", pivot);
	do{
		while(tab[i] > pivot){ 
			i++; 
			opPorownania++;
		}
		opPorownania++;
		while(tab[j] < pivot){
			j--;
			opPorownania++;
		}
		opPorownania++;
		if(i <= j) swap(tab, i++, j--);
	} while(i < j);
	if(start < j) QuickSort(tab, j, klawa, start);
	if(i < end) QuickSort(tab, end, klawa, i);
}

//////////FUNKCJE LOSUJĄCE//////////
void JustRand(int tab[], int tabStart, int tabEnd, int start, int end){
	for(int x = tabStart; x < tabEnd; x++)
		tab[x] = (rand() % (end - start + 1)) + start;
}
//malejąco
void Descending(int tab[], int tabStart, int tabEnd, int start, int end){
	int prz = (end - start + 1) / (tabEnd - tabStart);
	for(int x = 0; x < tabEnd - tabStart; x++)
		tab[x + tabStart] = (rand() % prz) + (end - (x + 1) * prz);
}
//rosnąco
void Ascending(int tab[], int tabStart, int tabEnd, int start, int end){
	int prz = (end - start + 1) / (tabEnd - tabStart);
	for(int x = 0; x < tabEnd - tabStart; x++)
		tab[x + tabStart] = (rand() % prz) + x * prz;
}
//A-kształtne
void AForm(int tab[], int tabStart, int tabEnd, int start, int end){
	Ascending(tab, tabStart, tabEnd / 2, start, end);
	Descending(tab, tabEnd / 2, tabEnd, start, end);
}
//V-kształtne
void VForm(int tab[], int tabStart, int tabEnd, int start, int end){
	Descending(tab, tabStart, tabEnd / 2, start, end);
	Ascending(tab, tabEnd / 2, tabEnd, start, end);
}

//////////KOMUNIKAT O BŁĘDZIE//////////
void ErrorComunicate(char *arg1){
	std::cerr << "\nError: Nieprawidłowe parametry! \n";
	std::cerr << "Poprawna forma to: " << arg1 << " algorytm sposób_wczytania_danych ilość_danych [sposób_wypisu_danuch=c]\n";
	std::cerr << "\nDostępne algorytmy: \n s/S - Selection Sort\n i/I - Insertion Sort\n h/H - Heap Sort\n e/E - Shell Sort\n q/Q - Quick Sort\n";
	std::cerr << "\nDostępne sposoby wczytywania danych: \n k/K - klawiatura\n l/L - losowo \n m/M - losowo malejąco\n r/R - losowo rosnąco\n a/A - losowo A-kształtne\n v/V - losowo V-kształtne \n";
	std::cerr << "\nDostępne sposoby wypisu danych: \n c/C - Konsola\n p/P - Plik\n";
}

int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "polish");
	opPorownania = 0;
	opSwap = 0;
	if(argc < 4 || argc > 5){
		ErrorComunicate(argv[0]);
		system("pause");
		return 1;
	}
	int n, k = 10000;
	if(!(n = atoi(argv[3])))		{
		ErrorComunicate(argv[0]);
		return 1;
	}
	int *tab = (int*)malloc(n * sizeof(int));
	srand(time(NULL));
	bool klawa = false;
	//wprowadzenie danych
	switch(toupper(argv[2][0])){
		 case 'K':
			 klawa = true;
			 for(int x = 0; x < n; x++)
				 scanf_s("%d", &tab[x]);
			 break;
		 case 'L':  JustRand(tab, 0, n, 10, k);
			 break;
		 case 'M':  Descending(tab, 0, n, 10, k);
			 break;
		 case 'R':  Ascending(tab, 0, n, 10, k);
			 break;
		 case 'A': AForm(tab, 0, n, 10, k);
			 break;
		 case 'V': VForm(tab, 0, n, 10, k);
			 break;
		 default:
			 ErrorComunicate(argv[0]);
			 return 1;
	 }
	//jeżeli dane podane z klawiatury - wypisz(według polecenia musi być)
	if(argv[2][0] == 'K' || argv[2][0] == 'k'){
		 printf("Dane do sortowania: \n");
		 drukuj(tab, 0, n);
	 }
	 tp start, end;

	 //wybór algorytmu
	 switch(toupper(argv[1][0])){
		 case 'S': 
			 start = chrono::system_clock::now();
			 SelectionSort(tab, n);
			 end = chrono::system_clock::now();
			 break;
		 case 'I': 
			 start = chrono::system_clock::now();
			 InsertionSort(tab, n);
			 end = chrono::system_clock::now();
			 break;
		 case 'H': 
			 start = chrono::system_clock::now();
			 HeapSort(tab, n);
			 end = chrono::system_clock::now();
			 break;
		 case 'E': 
			 start = chrono::system_clock::now();
			 ShellSort(tab, n, klawa);
			 end = chrono::system_clock::now();
			 break;
		 case 'Q': 
			 start = chrono::system_clock::now();
			 QuickSort(tab, n - 1, klawa);
			 end = chrono::system_clock::now();
			 break;
		 default:
			 ErrorComunicate(argv[0]);
			 return 1;
	 }
	//jeżeli dane podane z klawiatury - wypisz
	if(argv[2][0] == 'K' || argv[2][0] == 'k'){
		printf("Posortowane dane: \n");
		drukuj(tab, 0, n);
	}
	//format wypisu danych, drugi format(P) przyda się do zbierania info do sprawka
	char wypis = 'C';
	if(argc == 5) wypis = argv[4][0];
	if(toupper(wypis) == 'C'){
		cout << "Czas_sortowania: "<<  chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms" << endl;
		cout << "Liczba_operacji_porównania: " << opPorownania << endl;
		cout << "Liczba_zamian_elementów: " << opSwap << endl;
		system("pause");
	} else if(toupper(wypis) == 'P')
		cout << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " " << opPorownania << " " << opSwap << endl;

    return 0;
}

