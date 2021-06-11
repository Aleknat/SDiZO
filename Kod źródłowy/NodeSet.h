#pragma once
#include "Edge.h"
#include "Node.h"

//
class NodeSet
{
public:
    Node* NS;

    NodeSet(int);
    ~NodeSet();

    void makeSet(int );
    int findSet(int );
    void connect(Edge );
};