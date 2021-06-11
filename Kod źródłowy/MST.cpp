#include "MST.h"

using namespace std;

// Konstruktor
MST::MST( int edges)
{
    
    waga = 0;
    e = edges;
    TabE = new Edge[e];
    x = 0;
}

//Destruktor
MST::~MST() 
{
    delete[]TabE;
}

// Dodaje krawedü do drzewa MST
void MST::addEdge(Edge edge)
{
    waga += edge.waga;
    TabE[x] = edge;
    x++; 
}

// Wyúwietla drzewo MST
void MST::wyswietl()
{
    cout << endl;
    cout << "Edge    "<<"waga"<<endl;
    for (int i = 0; i < x; i++) {

        cout <<"( "<< TabE[i].v1 << ", " << TabE[i].v2 <<" )"<< " [" << TabE[i].waga << "] ";

        cout << endl;
    }
    cout << endl << endl << "Waga: " << waga << endl << endl;
}