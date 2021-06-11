#pragma once
#include <iostream>
#include "Edge.h"
#include "Node.h"
#include <cstdio>

// Klasa reprezentujaca drzewo MST
class MST {
public:
    Edge* TabE;
    int waga,e,x;

    MST( int );
    ~MST();

    void addEdge(Edge );
    void wyswietl();
};
