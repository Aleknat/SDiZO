#pragma once
#include <iostream>
#include "Edge.h"
//Jest to kolejka prioretytowa na podstawie kopca
class Q
{
private:
    Edge* Heap;
    int position;
public:
    Q(int n);
    ~Q();

    void push(Edge );
    void pop();
    Edge front();
};
