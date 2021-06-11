#include "NodeSet.h"



// Konstruktor
NodeSet::NodeSet ( int n )
{
  NS = new Node [ n ];    // Tworzymy tablicê dla elementów zbiorów
}

// Destruktor
NodeSet::~NodeSet( )
{
  delete [ ] NS;            // Usuwamy tablicê ze zbiorami
}

// Dodaje element do tablicy NS
void NodeSet::makeSet ( int v )
{
  NS [ v ].v   = v;
  NS [ v ].waga = 0;
}

// Zwraca indeks reprezentanta zbioru, w którym jest wierzcho³ek x
int NodeSet::findSet ( int x )
{
  if( NS [ x ].v != x )
      NS [ x ].v = findSet ( NS [ x ].v );
  return NS [ x ].v;
}

// £¹czy ze sob¹ zbiory 
void NodeSet::connect ( Edge edge )
{
  int va, vb;
  va = findSet ( edge.v1 );  
  vb = findSet ( edge.v2 );   
  if( va != vb )         
  {
    
      if (NS[va].waga > NS[vb].waga)
      {
          NS[vb].v = va;
      }
    else
    {
      NS [ va ].v = vb;    
      if( NS [ va ].waga == NS [ vb ].waga) NS [ vb ].waga++;
    }
  }
}