// tester.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>


int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "polish");
	int n, N;
	std::string plik, a, g, w;
	if(argc < 6){
		std::cout << "Ilość powtórzeń: ";
		std::cin >> n;
		std::cout << "\nDostępne algorytmy: \n s/S - Selection Sort\n i/I - Insertion Sort\n h/H - Heap Sort\n e/E - Shell Sort\n q/Q - Quick Sort\nPodaj algorytm: ";
		std::cin >> a;
		std::cout << "\nDostępne sposoby wczytywania danych: \n k/K - klawiatura\n l/L - losowo \n m/M - losowo malejąco\n r/R - losowo rosnąco\n a/A - losowo A-kształtne\n v/V - losowo V-kształtne \nPodaj sposób wczytania danych: ";
		std::cin >> g;
		std::cout << "\nPodaj ilość danych: ";
		std::cin >> N;
		std::cout << "\nPodaj nazwę pliku wynikowego(bez spacji i znaków specjalnych: ";
		std::cin >> plik;
		std::cout << "\nDostępne sposoby wypisu danych: \n c/C - Konsola\n p/P - Plik\nPodaj sposób wypisania danych: ";
		std::cin >> w;
		std::cout << std::endl;
	}
	else{
		n = atoi(argv[1]);
		a = argv[2];
		g = argv[3];
		N = atoi(argv[4]);
		plik = argv[5];
		w = "P";
		if(argc == 7)
			w = argv[6];
	}
	for(int i = 0; i < n; i++){
		if(system(("Sortowanie.exe " + a + " " + g + " " + std::to_string(N) +  " " + w + " >>" + plik + ".txt").c_str()))
			break;
	}
	system("pause");

    return 0;
}

