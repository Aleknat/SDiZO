#include "Graph.h"
using namespace std;



Graph::Graph(int nodes, int edges)
{
    int i, j;
    n = nodes;
    e = edges;
    vp = 0;
    vk = n - 1;
//----------------------------Macierz s¹siadów/

    M= new int* [n];  // Tworzymy tablicê wskaŸników dla macierzy


    for (i = 0; i < n; i++)
        M[i] = new int[n]; 

// Ustawiamy brak krawêdzi 0 to symboliczne brak krawedzi
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) M[i][j] = 0;

//------------------------- PO£¥CZONA LISTA S¥SIADÓW

    L = new Node *[n]; // Tworzymy tablicê list s¹siedztwa

// Tablicê wype³niamy pustymi listami

    for (i = 0; i < n; i++) L[i] = NULL;

}
// Konstruktor u¿ywany podczas wczytywania z pliku
Graph::Graph()
{

}
// Destruktor
Graph::~Graph()
{
    int i;

    //------------------------- PO£¥CZONA LISTA S¥SIADÓW
    for (i = 0; i < n; i++)
    {
        node = L[i];
        while (node)
        {
            node1 = node;
            node = node->next;
            delete node1;
        }
    }
    delete[] L;

// ----------------------------Macierz s¹siadów

    for (i = 0; i < n; i++) delete[] M[i];
    delete[] M;
}

// Wczytywanie grafu z pliku
void Graph::readGraph()
{
    fstream file;
    cout << "Podaj nazwe pliku: ";
    string name;
    cin >> name;  // podajemy nazwe pliku
    cout << endl;
    file.open(name, ios::in);
    if (file.good() == false)   // sprawdzamy czy plik istnieje
    {
        system("cls");
        cout << "Nie ma pliku" << endl;
        system("pause");
        return;
    }
    string line;


    int i, j;

    file >> line;           
    Graph::e = stoi(line);  // wczytujemy informacje o krawedziach
    file >> line;
    Graph::n = stoi(line);  // wczytujemy informacje o wierzcho³kach
    file >> line;
    Graph::vp = stoi(line); // wczytujemny informacje o wierzcho³ku pocz¹tkowym
    file >> line;
    Graph::vk = stoi(line); // wczytujemy informacje o wierzcho³ku koñcowym

    cout << "Wczytac jako skierowany czy nieskierowany? (sk/nsk)?: ";  // Decyduje o metodzie wczytania
    cin >> name;



    cout << endl;
    if (name != "nsk" && name != "sk")  // sprawdzamy poprawnoœæ wpisanych danych
    {
        cout << "Bledne dane" << endl;
        system("pause");
        return;
    }

    //-------------------------Macierz s¹siedztwa

    M = new int* [n];  // Tworzymy tablicê wskaŸników


    for (i = 0; i < n; i++)
        M[i] = new int[n]; // Tworzymy wiersze

// Ustawiamy brak krawêdzi 0 to symboliczne brak krawedzi
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) M[i][j] = 0;

    //------------------------- PO£¥CZONA LISTA S¥SIADÓW

    L = new Node * [n]; // Tworzymy tablicê list s¹siedztwa

// Tablicê wype³niamy pustymi listami

    for (i = 0; i < n; i++) L[i] = NULL;


    for (i = 0; i < e; i++) // Pêtla odczytuj¹ca kolejne krawêdzie
    {
        if (file.fail() || line.empty())
        {
            system("cls");
            cout << "Blad odczytu" << endl;
            system("pause");
            break;
        }

        int v1, v2;
        file >> line;



        v1 = stoi(line);

        file >> line;

        v2 = stoi(line);

        file >> line;

         M[v1][v2] = stoi(line);
         if(name=="nsk")
         M[v2][v1] = stoi(line);
            

         node = new Node;
         node->v = v2;
         node->waga = stoi(line);
         node->next = NULL;
         node1 = L[v1];
         if (L[v1] == NULL)
         {
             L[v1] = node;
         }
         else
         {
             while (node1->next)
             {
                 node1 = node1->next;
             }
             node1->next = node;

         }
         if (name == "nsk")
         {
             node = new Node;
             node->v = v1;
             node->waga = stoi(line);
             node->next = NULL;
             node1 = L[v2];
             if (L[v2] == NULL)
             {
                 L[v2] = node;
             }
             else
             {
                 while (node1->next)
                 {
                     node1 = node1->next;
                 }
                 node1->next = node;

             }
         }
    }
    if (name == "nsk")
        e = e * 2;
    file.close();
}











//------------------------------- PO£¥CZONA LISTA S¥SIADÓW


// Generuje losowy graf nieskierowany dla listy s¹siadów
void Graph::RandomGraphList()
{
    int i, v1, v2;   // Zmienne pomocnicze. v1,v2 - wierzho³ki

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(INT_MIN, INT_MAX);  // generowanie wag dla krawêdzi
    uniform_int_distribution<> dist1(0, n - 1);
    int x;

    node = new Node;
    node->v = 1;
    x = dist(gen);
    if (x == 0) x++;
    node->waga = x;
    node->next = NULL;
    L[0] = node;

    node = new Node;
    node->v = 0;
    node->waga = x;
    node->next = NULL;
    L[1] = node;


    for (i = 0; i < n - 2; i++)  // Pêtla dodaj¹ca minimaln¹ iloœæ krawêdzi, 
                                 // tak aby by³a zagwarantowana spójnoœæ grafu
    {
        uniform_int_distribution<> dist2(0, i+1);
        node = new Node;
        int y = dist2(gen);
        node->v = y;
        x = dist(gen);
        if (x == 0) x++;
        node->waga = x;
        node->next = NULL;
        node1 = L[i+2];
        if (L[i + 2] == NULL)
        {
            L[i + 2] = node;
        }
        else
        {
            while (node1->next)
            {
                node1 = node1->next;
            }
            node1->next = node;

        }

        node = new Node;
        node->v = i + 2;
        node->waga = x;
        node->next = NULL;
        node1 = L[y];
        if (L[y] == NULL)
        {
            L[y] = node;
        }
        else
        {
            while (node1->next)
            {
                node1 = node1->next;
            }
            node1->next = node;

        }
    }
    e = e - (n - 1);  // Uzwglêdnienie poprzedniej pêtli

    for (i = 0; i < e; i++) // Pêtla dodaj¹ca e-n krawêdzi 
    {
        v1 = dist1(gen);
        v2 = dist1(gen);
        bool exist = false;
        node = L[v1];
        if (v1 != v2)
        {


            while (node != NULL)
            {
                if (node->v == v2) exist = true;
                node = node->next;
            }
            node = L[v2];

            if (exist == true)
            {
                i--;
            }
            else 
            {
                x = dist(gen);
                if (x == 0) x++;

                node = new Node;    // tworzenie i dodawanie krawêdzi
                node->v = v2;
                node->waga = x;
                node->next = NULL;
                node1 = L[v1];
                if (L[v1] == NULL)
                {
                    L[v1] = node;
                }
                else
                {
                    while (node1->next)
                    {
                        node1 = node1->next;
                    }
                    node1->next = node;

                }

                node = new Node;   // tworzenie i dodawanie krawêdzi drugi raz
                node->v = v1;       // poniewa¿ jest to graf nieskierowany
                node->waga = x;
                node->next = NULL;
                node1 = L[v2];
                if (L[v2] == NULL)
                {
                    L[v2] = node;
                }
                else
                {
                    while (node1->next)
                    {
                        node1 = node1->next;
                    }
                    node1->next = node;

                }
            }
        }
        else
        {
            i--;
        }
    }

    e = e + (n - 1);  // wyrównanie iloœci krawêdzi
    e = e * 2;          // obliczenie iloœci dla grafu nieskierowanego
}

// Pokazuje graf jako liste s¹siadów
void Graph::ShowGraphList()
{
    int i;
    cout << endl;

    for (i = 0; i < n; i++)
    {
        cout << "L [ " << i << " ] =";
        node = L[i];
        while (node)
        {
            cout <<"  ["<< node->v<<", "<<node->waga<<"] ";
            node = node->next;
        }
        cout << endl;
    }
}


// Algorytm Prima dla listy
void Graph::PrimList(bool show)
{
    int current, i;
    Edge edge;
    Q Q(e);
    visited = new bool[n];
    MST* tree = new MST(e);
  
    for (i = 0; i < n; i++) {
        visited[i] = false;
    }

    current = 0;
    visited[current] = true;
    for (i = 1; i < n; i++) 
    {
        for (node = L[current]; node; node = node->next) 
        {
            if (!visited[node->v]) {
                edge.v1 = current;
                edge.v2 = node->v;
                edge.waga = node->waga;
                Q.push(edge);
            }
        }


        do {
            edge = Q.front();
            Q.pop();
        } while (visited[edge.v2]);
        tree->addEdge(edge);
        current = edge.v2;
        visited[edge.v2] = true;
    }
    if (show == true)
    {
        cout << endl;
        cout << "Drzewo MST - PrimList:";
        tree->wyswietl();
    }
     delete tree;
    
}
// Generuje losowy graf skierowany dla listy s¹siadów
void Graph::RandomDirectGraphList()
{
    int i, v1, v2;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, INT_MAX);
    uniform_int_distribution<> dist1(0, n - 1);
    int x;
    for (i = 0; i < e; i++)
    {
        v1 = dist1(gen);
        v2 = dist1(gen);
        bool exist = false;
        node = L[v1];
        if (v1 != v2)
        {


            while (node != NULL)
            {
                if (node->v == v2) exist = true;
                node = node->next;
            }
            node = L[v2];

            if (exist == true)
            {
                i--;
            }
            else
            {
                x = dist(gen);
                if (x == 0) x++;
                node = new Node;
                node->v = v2;
                node->waga = x;
                node->next = NULL;
                node1 = L[v1];
                if (L[v1] == NULL)
                {
                    L[v1] = node;
                }
                else
                {
                    while (node1->next)
                    {
                        node1 = node1->next;
                    }
                    node1->next = node;

                }
            }
        }
        else
        {
            i--;
        }
    }

}

// Algorytm Dijkstry dla listy s¹siadów
void Graph::dijkstraList(int v, bool show) {
    int i, j, cur, sptr, * costTab, * lastTab, * S;
    costTab = new int[n];       
    lastTab = new int[n];         
    visited = new bool[n];        
    S = new int[n];       
    sptr = 0;                 

    for (i = 0; i < n; i++)
    {
        costTab[i] = MAXINT;
        lastTab[i] = -1;
        visited[i] = false;
    }
    costTab[v] = 0;            

    bool NC=false;
    for (i = 0; i < n ; i++)
    {
        for (node = L[i]; node; node = node->next)
            if (node->waga<0)
            {
                cout<<endl << "Wyniki moga byc nie poprawne z powodu ujemnych wag" <<endl<< endl;
                NC = true;
                break;
            }
        if (NC) break;
    }



    for (i = 0; i < n; i++)
    {

        for (j = 0; visited[j]; j++);
            for (cur = j++; j < n; j++)
                if (!visited[j] && (costTab[j] < costTab[cur])) cur = j;
   
        visited[cur] = true;

        for (node = L[cur]; node; node = node->next)
            if (!visited[node->v] && (costTab[node->v] > costTab[cur] + node->waga))
            {
                costTab[node->v] = costTab[cur] + node->waga;
                lastTab[node->v] = cur;
            }
    }

    if (show == true)
    {
        cout << "Algorytm Dijkstry - dijkstraList" << endl;
        cout << "Start: " << v << endl;
        cout << "End   Dist   Path" << endl;
        for (i = 0; i < n; i++)
        {
            cout << "   " << i << " | ";
            if (costTab[i] == MAXINT || costTab[i] < 0)
            {
                cout << "INF | ";
            }
            else
            {
                cout << setw(3) << costTab[i] << " | ";
            }
            if (costTab[i] == MAXINT || costTab[i] < 0)
            {
                cout << "Brak ";
            }
            else
            {
                for (j = i; j > -1; j = lastTab[j]) S[sptr++] = j;
                while (sptr) cout << S[--sptr] << " ";
            }
            cout << endl;
        }
    }
    delete[] costTab;
    delete[] lastTab;
    delete[] S;
}

// Algorytm kruskala dla listy s¹siadów
void Graph::kruskalList(bool show)
{
    Edge edge;
    int i;
    NodeSet NS(n);     
    Q Q(e);          
    MST T(e);       

    for (i = 0; i < n; i++)
        NS.makeSet(i);      

    for (i = 0; i < n-1; i++)
    {
        for (node = L[i]; node; node = node->next)
        {
            edge.v1 = i;
            edge.v2 = node->v;
            edge.waga = node->waga;
            Q.push(edge);
        }
    }


    for (i = 1; i < n; i++) 
    {
        do
        {
            edge = Q.front();     
            Q.pop();            
        } while (NS.findSet(edge.v1) == NS.findSet(edge.v2));
        T.addEdge(edge);      
        NS.connect(edge);     
    }

    if (show == true)
    {
        cout << endl;
        cout << "Drzewo MST - KruskalList:";
        T.wyswietl();
    }


}


// Algorytm Bellmana-Forda dla listy s¹siadów
void Graph::bellmanFordList(int v, bool show)
{
    int i, j,* costTab,* lastTab, sptr, * S;



    costTab = new  int[n];
    lastTab = new int[n]; 

    for (i = 0; i < n; i++)
    {
        costTab[i] = MAXINT;
        lastTab[i] = -1;
    }
;

    costTab[v] = 0;               
    for (i = 1; i < n; i++)  
    {         
        for (j = 0; j < n; j++) 
            for (node = L[j]; node; node = node->next) 
                if (costTab[node->v] > costTab[j] + node->waga && costTab[j] != INT_MAX) 
                {    
                    costTab[node->v] = costTab[j] + node->waga; 
                    lastTab[node->v] = j;   
                }
    }


    for (j = 0; j < n; j++)
        for (node = L[j]; node; node = node->next)
            if (costTab[node->v] > costTab[j] + node->waga)
            {
               if(show==true) cout << "Algorytm Bellmana-Forda - Wystepuje cykl ujemny" << endl;
                return;
            }

    if (show == true)
    {

            S = new int[n];   
            sptr = 0;
            cout << "Algorytm Bellmana-Forda - bellmanFordList" << endl;
            cout << "Start: " << v << endl;
            cout << "End   Dist   Path" << endl;
            for (i = 0; i < n; i++)
            {
                cout << "   " << i << " | ";
                if (costTab[i] == MAXINT )
                {
                    cout << "INF | ";
                }
                else
                {
                    cout << setw(3) << costTab[i] << " | ";
                }
                if (costTab[i] == MAXINT )
                {
                    cout << "Brak ";
                }
                else
                {
                    for (j = i; j != -1; j = lastTab[j])
                        S[sptr++] = j; 
                    while (sptr)       
                        cout << S[--sptr] << " "; 
                }
                cout << endl;
            }
            delete[] S;        
     }

    delete[] costTab;
    delete[] lastTab;

}










//--------------------------------------------------  MACIESZ S¥SIEDZTWA
// generowaniu losowego grafu nieskierowanego dla macierzy
void Graph::RandomGraphMatrix()
{
    int i,j, v1, v2;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(INT_MIN, INT_MAX);
    uniform_int_distribution<> dist1(0, n - 1);
    int x;

    node = new Node;
    node->v = 1;
    x = dist(gen);
    if (x == 0) x++;
    M[0][ 1] = x;
    M[1][0] = x;



    for (i = 0; i < n - 2; i++)
    {
        uniform_int_distribution<> dist2(0, i + 1);
        node = new Node;
        int y = dist2(gen);
        node->v = y;
        x = dist(gen);
        if (x == 0) x++;

        M[i+2][y] = x;
        M[y][i+2] = x;
    }


    e = e - (n-1);


    for (i = 0; i < e; i++)
    {
        v1 = dist1(gen);
        v2 = dist1(gen);
        if (v1 != v2)
        {
            if (M[v1][v2] != 0)
            {
                i--;
            }
            else
            {
                x = dist(gen);
                if (x == 0) x++;
                M[v1][v2] = x;
                M[v2][v1] = x;
            }
        }
        else
        {
            i--;
        }
    }
    e = e + (n - 1);
    e = e * 2;
}

// Generowanie grafu nieskierowanego dla macierzy
void Graph::RandomDirectGraphMatrix()
{
    int i, v1, v2;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, INT_MAX);
    uniform_int_distribution<> dist1(0, n - 1);
    int x;


    for (i = 0; i < e; i++)
    {
        v1 = dist1(gen);
        v2 = dist1(gen);
        if (v1 != v2)
        {
            if (M[v1][v2] != 0)
            {
                i--;
            }
            else
            {
                x = dist(gen);
                if (x == 0) x++;
                M[v1][v2] = x;
            }
        }
        else
        {
            i--;
        }
    }
}

// wyswietlenie grafu w postaci macierzy s¹siêdztwa
void Graph::ShowGraphMatrix()
{
    int i, j;
    cout << endl;
    cout << "   ";
    for (i = 0; i < n; i++) cout << setw(3) << i;
    cout << endl << endl;
    for (i = 0; i < n; i++)
    {
        cout << setw(3) << i;
            for (j = 0; j < n; j++)
            {
                 cout << setw(3) << M[i][j];
            }
        cout << endl;
    }
}

// Algorytm Prima dla macierzy
void Graph::PrimMatrix(bool show)
{
    int current, i, j;
    Edge edge;
    Q Q(e);
    visited = new bool[n];
    MST* tree = new MST( e);

    for (i = 0; i < n; i++) {
        visited[i] = false;
    }

    current = 0;
    visited[current] = true;
    for (i = 0; i < n-1; i++)
    {
        for (j = 0; j < n ; j++)
        {
            if (!visited[j] && M[current][j] != 0)
            {
                edge.v1 = current;
                edge.v2 = j;
                edge.waga = M[current][j];
                Q.push(edge);
            }
        }



            do {
                edge = Q.front();
                Q.pop();
            } while (visited[edge.v2]);
            tree->addEdge(edge);
            current = edge.v2;
            visited[edge.v2] = true;
    }
    if (show == true)
    {
        cout << endl;
        cout << "Drzewo MST - PrimMatrix:";
        tree->wyswietl();
    }
    delete tree;
}

// Algorytm dijkstry dla macierzy
void Graph::dijkstraMatrix(int v, bool show) {
    int i, j, u, sptr, * costTab, * lastTab, * S;
    costTab = new int[n];
    lastTab = new int[n];
    visited = new bool[n];
    S = new int[n];
    sptr = 0;

    for (i = 0; i < n; i++)
    {
        costTab[i] = MAXINT;
        lastTab[i] = -1;
        visited[i] = false;
    }

    bool NC = false;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (M[i][j] < 0)
            {
                cout << endl << "Wyniki moga byc nie poprawne z powodu ujemnych wag" << endl << endl;
                NC = true;
                break;
            }
        }
    if (NC) break;
    }
    costTab[v] = 0;

    for (i = 0; i < n - 1; i++)
    {


        for (j = 0; visited[j]; j++);
        for (u = j++; j < n; j++)
            if (!visited[j] && (costTab[j] < costTab[u])) u = j;

        visited[u] = true;

        for (j = 0; j < n; j++)
        {
            if (!visited[j] && M[u][j] != 0 && costTab[j] > costTab[u] + M[u][j])
            {
                costTab[j] = costTab[u] + M[u][j];
                lastTab[j] = u;
            }
        }
    }
    if (show == true)

    {
        cout << "Algorytm Dijkstry - dijkstraMatrix" << endl;
        cout << "Start: " << v << endl;
        cout << "End   Dist   Path" << endl;
        for (i = 0; i < n; i++)
        {
            cout << "   " << i << " | ";
            if (costTab[i] == MAXINT || costTab[i] < 0)
            {
                cout << "INF | ";
            }
            else
            {
                cout << setw(3) << costTab[i] << " | ";
            }
            if (costTab[i] == MAXINT || costTab[i] < 0)
            {
                cout << "Brak ";
            }
            else
            {
                for (j = i; j > -1; j = lastTab[j]) S[sptr++] = j;
                while (sptr) cout << S[--sptr] << " ";
            }
            cout << endl;
        }
    }
    delete[] costTab;
    delete[] lastTab;
    delete[] S;
}

// Algortym kruskala dla macierzy
void Graph::kruskalMatrix(bool show)
{
    Edge edge;
    int i,j;


    NodeSet NS(n);
    Q Q(e);
    MST T( e);

    for (i = 0; i < n; i++)
        NS.makeSet(i);

    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (M[i][j] != 0)
            {
                edge.v1 = i;
                edge.v2 = j;
                edge.waga = M[i][j];
                Q.push(edge);
            }

        }
    }


    for (i = 1; i < n; i++)
    {
        do
        {
            edge = Q.front();
            Q.pop();
        } while (NS.findSet(edge.v1) == NS.findSet(edge.v2));
        T.addEdge(edge);
        NS.connect(edge);
    }

    if (show == true)
    {
        cout << endl;
        cout << "Drzewo MST - KruskalMatrix:";
        T.wyswietl();
    }


}

// Algorytm BellmanaForda dla macierzy s¹siadów
void Graph::bellmanFordMatrix(int v, bool show)
{
    int i, j, * costTab, * lastTab, sptr, * S;



    costTab = new  int[n];
    lastTab = new int[n];

    for (i = 0; i < n; i++)
    {
        costTab[i] = MAXINT;
        lastTab[i] = -1;
    }


    costTab[v] = 0;
    for (int x = 1; x < n; x++)
    {
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)

                if (M[i][j] != 0 && costTab[j] > costTab[i] + M[i][j] && costTab[i] != INT_MAX)
                {
                    costTab[j] = costTab[i] + M[i][j];
                    lastTab[j] = i;
                }
        }
    }



    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)

            if (M[i][j] != 0 && costTab[j] > costTab[i] + M[i][j])
            {
               if(show==true) cout << "Algorytm Bellmana-Forda - Wystepuje cykl ujemny" << endl;
                return;
            }
    }


    if (show == true)
    {

            S = new int[n];
            sptr = 0;
            cout << "Algorytm Bellmana-Forda - bellmanFordMatrix" << endl;
            cout << "Start: " << v << endl;
            cout << "End   Dist   Path" << endl;
            for (i = 0; i < n; i++)
            {
                cout << "   " << i << " | ";
                if (costTab[i] == MAXINT )
                {
                    cout << "INF | ";
                }
                else
                {
                    cout << setw(3) << costTab[i] << " | ";
                }
                if (costTab[i] == MAXINT )
                {
                    cout << "Brak ";
                }
                else
                {
                    for (j = i; j != -1; j = lastTab[j])
                        S[sptr++] = j;
                    while (sptr)
                        cout << S[--sptr] << " ";
                }
                cout << endl;
            }
            delete[] S;
    }

    delete[] costTab;
    delete[] lastTab;

}