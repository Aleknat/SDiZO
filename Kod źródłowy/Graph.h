#pragma once

#include <iostream>
#include <ctime>
#include <fstream>
#include <math.h>
#include <iomanip>
#include <cstdio>
#include <windows.h>
#include <conio.h>
#include <random>
#include <ctime>
#include <fstream>
#include <string>
#include "Node.h"
#include "Edge.h"
#include "MST.h"
#include "Q.h"
#include "NodeSet.h"

// Klasa reprezentuj¹ca graf
class Graph
{
public:

	int n, e;
	int vp, vk;
	int** M;
	Node** L;
	Node* node, * node1;
	bool* visited;
	
	Graph();
	Graph(int, int);
	~Graph();
	void readGraph();


	// Macierz s¹siedztwa
	void RandomGraphMatrix();
	void ShowGraphMatrix();
	void PrimMatrix(bool);
	void RandomDirectGraphMatrix();
	void dijkstraMatrix(int, bool);
	void kruskalMatrix(bool);
	void bellmanFordMatrix(int, bool);

	//Lista s¹siadów
	void RandomGraphList();
	void ShowGraphList();
	void PrimList(bool);
	void RandomDirectGraphList();
	void dijkstraList(int, bool);
	void kruskalList(bool);
	void bellmanFordList(int, bool);
};

