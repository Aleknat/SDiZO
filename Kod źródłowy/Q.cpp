#include "Q.h"

//konstruktor
Q::Q(int n)
{
    Heap = new Edge[n];         // Tworzymy tablic�
    position = 0;                      // Pozycja w kopcu
}

//Destruktor
Q::~Q()
{
    delete[] Heap;
}

// funkcja dodaje do kopca now� kraw�d� i przywraca w�asno�� kopca
void Q::push(Edge e)
{
    int i, j;

    i = position++;                  
    j = (i - 1) >> 1 ;         



    while (i && (Heap[j].waga > e.waga))
    {
        Heap[i] = Heap[j];
        i = j;
        j = (i - 1) >> 1;
    }

    Heap[i] = e;               
}

// funkcja usuwa korze� i przywraca w�asno�� kopca
void Q::pop()
{
    int i, j;
    Edge e;

    if (position)
    {
        e = Heap[--position];
        i = 0;
        j = 1;
        while (j < position)
        {
            if ((j + 1 < position) && (Heap[j + 1].waga < Heap[j].waga)) j++;
            if (e.waga <= Heap[j].waga) break;
            Heap[i] = Heap[j];
            i = j;
            j = (j << 1 ) + 1;
        }
        Heap[i] = e;
    }
}

//funkcja zwraca kraw�d� z pocz�tku kopca
Edge Q::front()
{
    return Heap[0];
}
