#include "MainMenu.h"
#include <iostream>
#include <cstdio>
#include <windows.h>
#include <conio.h>
#include <random>
#include <ctime>
#include <iomanip>
using namespace std;


void MainMenu::run()   // Funkcja wyœwietlaj¹ca Menu g³ówne
{
	system("cls");

	while (true)
	{
		system("cls");
		cout << "\n \n \n MENU GLOWNE \n -----------------------------" << endl;
		cout << "1. Testowanie algorytmow" << endl;
		cout << "2. Pomiar czasu" << endl;
		int x;
		x = _getch();
		switch (x) {
		case '1':
			TestMenu();  // Przejscie do menu testów
			break;
		case '2':
			TimeMenu();  // Przejœcie do menu pomiarów
			break;
		default:
			cout << endl << "Bledne dane" << endl;
			Sleep(500);
		}

	}


}

void MainMenu::TestMenu()  // Funkcja implementuj¹ca Menu Testów 
{
	Graph g;
	while (true)
	{
		system("cls");

		cout << "\n \n \n MENU TESTOW \n -----------------------------" << endl;
		cout << "1. Wczytanie grafu z pliku" << endl;
		cout << "2. Wyswietlenie grafu macierzowo i listowo" << endl;
		cout << "3. Algorytm Prima" << endl;
		cout << "4. Algorytm Kruskala" << endl;
		cout << "5. Algorytm Dijkstry" << endl;
		cout << "6. Algorytm Bellmana-Forda" << endl;
		cout << "Esc - Wstecz" << endl;
		int x;
		x = _getch();
		
		

		switch (x) {
		case '1':
			g.readGraph();
			break;
		case '2':
			g.ShowGraphList();
			g.ShowGraphMatrix();
			system("pause");
			break;
		case '3':
			g.PrimList(true);
			g.PrimMatrix(true);
			system("pause");
			break;
		case '4':
			g.kruskalList(true);
			g.kruskalMatrix(true);
			system("pause");
			break;
		case '5':
			g.dijkstraList(g.vp,true);
			g.dijkstraMatrix(g.vp,true);
			system("pause");
			break;
		case '6':
			g.bellmanFordList(g.vp,true);
			g.bellmanFordMatrix(g.vp, true);
			system("pause");
			break;
		case 27:
			return;
			break;
		default:
			cout << endl << "Bledne dane" << endl;
			Sleep(500);
		}


	}
}

void MainMenu::TimeMenu()  // funkcja reprezentuj¹ca menu pomiaru czasu
{
	while (true)
	{
		system("cls");

		cout << "\n \n \n MENU POMIARU \n -----------------------------" << endl;
		cout << "1. Pomiary dla macierzy" << endl;
		cout << "2. Pomiary dla listy" << endl;
		cout << "Esc - Wstecz" << endl;
		int x;
		x = _getch();
		switch (x) {
		case '1':
			matrixTime();
			break;
		case '2':
			listTime();
			break;
		case 27:
			return;
			break;
		default:
			cout << endl << "Bledne dane" << endl;
			Sleep(500);
		}


	}
}

// Mierzy czas algorytmów grafowych dla listy
void MainMenu::listTime()
{

		system("cls");
		Graph* g;
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<> dist(INT_MIN, INT_MAX);
		int x = dist(gen);
		long long frequency, start, elapsed;
		QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
		long long int srednia[7] = { 0 };
		int n,e;
		cout << "Podaj ilosc wierzcholkow:  ";
		cin >> n;
		cout << endl;
		cout << "Podaj ilosc krawedzi: ";
		cin >> e;

		for (int i = 1; i <= 100; i++)
		{
			


			system("cls");
			uniform_int_distribution<> dist2(1, n);
			cout << "Algorytmy Listy " << endl << "Liczba wierzcholkow: " << n << endl;
			cout << "Liczba krawedzi: " << e << endl;
			cout<<"Pomiar: " << i << endl;

			g = new Graph(n, e);
			g->RandomGraphList();



			start = read_QPC();
			g->PrimList(false);
			elapsed = read_QPC() - start;
			srednia[0] = srednia[0] + elapsed;

			start = read_QPC();
			g->kruskalList(false);
			elapsed = read_QPC() - start;
			srednia[2] = srednia[2] + elapsed;



			g = new Graph(n, e);
			g->RandomDirectGraphList();




			start = read_QPC();
			g->dijkstraList(g->vp, false);
			elapsed = read_QPC() - start;
			srednia[1] = srednia[1] + elapsed;

			start = read_QPC();
			g->bellmanFordList(g->vp, false);
			elapsed = read_QPC() - start;
			srednia[3] = srednia[3] + elapsed;

		
		}
		srednia[0] = srednia[0] / 100;
		srednia[1] = srednia[1] / 100;
		srednia[2] = srednia[2] / 100;
		srednia[3] = srednia[3] / 100;

		cout << "1. Czas trwania algorytmu primList" << endl;
		cout << "Czas [us] = " << setprecision(0) << (1000000 * srednia[0]) /
			frequency << endl << endl;
		cout << "Czas [ns] = " << setprecision(0) << (1000000000 * srednia[0]) /
			frequency << endl << endl;
		cout << "2. Czas trwania algorytmu kruskalList" << endl;
		cout << "Czas [us] = " << setprecision(0) << (1000000 * srednia[2]) /
			frequency << endl << endl;
		cout << "Czas [ns] = " << setprecision(0) << (1000000000 * srednia[2]) /
			frequency << endl << endl;
		cout << "3. Czas trwania algorytmu dijkstryList" << endl;
		cout << "Czas [us] = " << setprecision(0) << (1000000 * srednia[1]) /
			frequency << endl << endl;
		cout << "Czas [ns] = " << setprecision(0) << (1000000000 * srednia[1]) /
			frequency << endl << endl;
		cout << "4. Czas trwania algorytmu bellmanFordList" << endl;
		cout << "Czas [us] = " << setprecision(0) << (1000000 * srednia[3]) /
			frequency << endl << endl;
		cout << "Czas [ns] = " << setprecision(0) << (1000000000 * srednia[3]) /
			frequency << endl << endl;



		system("pause");
}

// Mierzy czas algorytmów grafowych dla macierzy
void MainMenu::matrixTime()
{

	system("cls");
	Graph* g;
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(INT_MIN, INT_MAX);
	int x = dist(gen);
	long long frequency, start, elapsed;
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
	long long int srednia[7] = { 0 };
	int n, e;
	cout << "Podaj ilosc wierzcholkow:  ";
	cin >> n;
	cout << endl;
	cout << "Podaj ilosc krawedzi: ";
	cin >> e;

	for (int i = 1; i <= 100; i++)
	{

		system("cls");
		uniform_int_distribution<> dist2(1, n);
		cout << "Algorytmy Macierzy " << endl << "Liczba wierzcholkow: " << n << endl;
		cout << "Liczba krawedzi: " << e << endl;
		cout << "Pomiar: " << i << endl;

		g = new Graph(n, e);
		g->RandomGraphMatrix();



		start = read_QPC();
		g->PrimMatrix(false);
		elapsed = read_QPC() - start;
		srednia[0] = srednia[0] + elapsed;

		start = read_QPC();
		g->kruskalMatrix(false);
		elapsed = read_QPC() - start;
		srednia[2] = srednia[2] + elapsed;



		g = new Graph(n, e);
		g->RandomDirectGraphMatrix();




		start = read_QPC();
		g->dijkstraMatrix(g->vp, false);
		elapsed = read_QPC() - start;
		srednia[1] = srednia[1] + elapsed;

		start = read_QPC();
		g->bellmanFordMatrix(g->vp, false);
		elapsed = read_QPC() - start;
		srednia[3] = srednia[3] + elapsed;


	}
	srednia[0] = srednia[0] / 100;
	srednia[1] = srednia[1] / 100;
	srednia[2] = srednia[2] / 100;
	srednia[3] = srednia[3] / 100;

	cout << "1. Czas trwania algorytmu primMatrix" << endl;
	cout << "Czas [us] = " << setprecision(0) << (1000000 * srednia[0]) /
		frequency << endl << endl;
	cout << "Czas [ns] = " << setprecision(0) << (1000000000 * srednia[0]) /
		frequency << endl << endl;
	cout << "2. Czas trwania algorytmu kruskalMatrix" << endl;
	cout << "Czas [us] = " << setprecision(0) << (1000000 * srednia[2]) /
		frequency << endl << endl;
	cout << "Czas [ns] = " << setprecision(0) << (1000000000 * srednia[2]) /
		frequency << endl << endl;
	cout << "3. Czas trwania algorytmu dijkstryMatrix" << endl;
	cout << "Czas [us] = " << setprecision(0) << (1000000 * srednia[1]) /
		frequency << endl << endl;
	cout << "Czas [ns] = " << setprecision(0) << (1000000000 * srednia[1]) /
		frequency << endl << endl;
	cout << "4. Czas trwania algorytmu bellmanFordMatrix" << endl;
	cout << "Czas [us] = " << setprecision(0) << (1000000 * srednia[3]) /
		frequency << endl << endl;
	cout << "Czas [ns] = " << setprecision(0) << (1000000000 * srednia[3]) /
		frequency << endl << endl;


	system("pause");
}
long long int MainMenu::read_QPC()
{
	LARGE_INTEGER count;

	QueryPerformanceCounter(&count);
	return((long long int)count.QuadPart);
}