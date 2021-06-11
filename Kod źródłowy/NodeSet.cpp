#include "NodeSet.h"



// Konstruktor
NodeSet::NodeSet ( int n )
{
  NS = new Node [ n ];    // Tworzymy tablic� dla element�w zbior�w
}

// Destruktor
NodeSet::~NodeSet( )
{
  delete [ ] NS;            // Usuwamy tablic� ze zbiorami
}

// Dodaje element do tablicy NS
void NodeSet::makeSet ( int v )
{
  NS [ v ].v   = v;
  NS [ v ].waga = 0;
}

// Zwraca indeks reprezentanta zbioru, w kt�rym jest wierzcho�ek x
int NodeSet::findSet ( int x )
{
  if( NS [ x ].v != x )
      NS [ x ].v = findSet ( NS [ x ].v );
  return NS [ x ].v;
}

// ��czy ze sob� zbiory 
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