#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;
int remove_edge_number = 0; 
int remove_edge_weight = 0;

typedef struct edge {
    int u;
    int v;
    int w;
}edge;

typedef struct DisjointSet {
    int *p;
    int number;
    int *size;

    DisjointSet(int V){
        this->number = V;
        p = new int [V+1];
        size = new int [V+1];
        for (int i = 0; i < V; i++)
        {
            p[i] = i;
            size[i] = 1;
        }
    }

    int find(int x){
        if(x != p[x])
        {
            x = find(p[x]);
        }
        return x;
    }

    void merge(int x, int y){
        x = find(x);
        y = find(y);

        if(size[x] < size[y])
        {
            p[x] = y;
            size[y] += size[x];
        }
        else
        {
            p[y] = x;
            size[x] += size[y];
        }
    }
}DisjointSet;

void swap(edge& a, edge& b){
    edge temp;
    temp = a;
    a = b;
    b = temp;
}

void PrintEdge(edge* a, int E){
    cout << "Edge Weight is : ";
    for (int i = 0; i < E; i++)
    {
        cout << a[i].w << ' ';
    }
    cout << endl;
}

void ShowAdjList(vector<vector<int> > adj_list)
{
    cout << "========================================" << endl;
    cout << "Adj Table : " << endl;
    for (int i = 0; i < adj_list.size(); i++)
    {
        cout << setw(3) << i << " -> ";
        for (int j = 0; j < adj_list[i].size(); j++)
        {
            cout << setw(3) << adj_list[i][j] << " -> ";
        }
        cout << "NIL" ;
        cout << endl;
    }
    cout << "========================================" << endl;
}

void Sort(edge* edge_set, int E){
    vector<edge> A, B(E);

    int C[202];

    for (int i = 0; i < E; i++)
    {
        A.push_back(edge_set[i]);
        A[i].w  = edge_set[i].w * -1;
    }

    for (int i = 0; i < 202; i++)
    {
        C[i] = 0;
    }
    
    for (int i = 0; i < E; i++)
    {
        C[A[i].w + 100] = C[A[i].w + 100] + 1;
    }
    
    for (int i = 1; i < 202; i++)
    {
        C[i] = C[i] + C[i-1];
    }

    
    for (int i = E - 1; i >= 0 ; i--)
    {
        B[C[A[i].w + 100] - 1] = A[i];
        C[A[i].w + 100] = C[A[i].w + 100] - 1;
    }
    
    for (int i = 0; i < E; i++)
    {
        edge_set[i] = B[i];
        edge_set[i].w = edge_set[i].w * -1;
    }

    // cout << "Sorted Edges" << endl;
    // for (int i = 0; i < E; i++)
    // {
    //     cout << "w : " << setw(3) << edge_set[i].w << " , ";
    //     cout << "u : " << setw(3) << edge_set[i].u << " , ";
    //     cout << "v : " << setw(3) << edge_set[i].v << " \n";
    // }
}

vector<edge> KruskalMSP(edge* edge_set, int V, int E){
    
    DisjointSet disjointset(V);
    Sort(edge_set, E);

    int remove_weight = 0;
    int num_remove_edge = 0;
    
    vector<edge> A;
    vector<edge> MST;
    vector<edge> DeleteEdge;

    for (int i = 0; i < E; i++)
    {
        int u = disjointset.find(edge_set[i].u);
        int v = disjointset.find(edge_set[i].v);

        edge e;
        e.u = edge_set[i].u;
        e.v = edge_set[i].v;
        e.w = edge_set[i].w;

        if (u != v)
        {
            disjointset.merge(u, v);
            MST.push_back(e);
        }
        else
        {
            A.push_back(e);
            remove_edge_number += 1;
            remove_edge_weight += e.w;

            remove_weight += e.w;
            num_remove_edge += 1;
        }
    }

    A.insert(A.end(), MST.begin(), MST.end());

    return A;
}

int WHITE = 0;
int GRAY  = 1;
int BLACK = 2;

bool DFSVisit(vector<vector<int> >& G, vector<int>& color, int u)
{
    color[u] = GRAY;
    for (int v = 0; v < G[u].size(); v++)
    {
        if (color[G[u][v]] == GRAY)
        {
            return true;  // Cycle Exist
        }
        if (color[G[u][v]] == WHITE && DFSVisit(G, color, G[u][v]))
        {
            return true;  // Keep Eearching
        }
    }
    color[u] = BLACK;
    return false;  // Cycle Nonexist
}

bool DFS(vector<vector<int> >& G)
{
    vector<int> color(G.size(), WHITE);
    for (int u = 0; u < G.size(); u++)
    {
        if (color[u] == WHITE)
        {
            if (DFSVisit(G, color, u))
            {
                return true;  
            }
        }
    }
    return false;  
}


int main(int argc, char* argv[])
{
    if (argc < 3)
        {
            cout << "Error: The command format should be "
                << "\"./bin/cd <input-file.in> <output-file>\"" << endl;
            return 1;
        }

    //  READ FILE
    ifstream fin;
    fin.open(argv[1]);
    if (!fin.is_open())
    {
        cout << "Wrong File's Name!!" << endl;
    }
    int V, E;
    char type;
    fin >> type;
    fin >> V;
    fin >> E;
    edge* edge_set = new struct edge[E];
    for (int i = 0; i < E; i++)
    {
        fin >> edge_set[i].u;
        fin >> edge_set[i].v;
        fin >> edge_set[i].w;
    }
    fin.close();
    
    vector<edge> DeleteEdge;

    //  Undirective Graph
    if (type == 'u')
    {
        DeleteEdge = KruskalMSP(edge_set, V, E);
    }
    //  Directive Graph
    else
    {
        DeleteEdge = KruskalMSP(edge_set, V, E);
        vector<edge> temp;
        vector<vector<int> > adj_list(V);
        int remove_weght = 0;
        int num_remove_edge = 0;
        for (int i = remove_edge_number; i < DeleteEdge.size()-1; i++)
        {
            adj_list[DeleteEdge[i].u].push_back(DeleteEdge[i].v);
        }

        //ShowAdjList(adj_list);
    
        for (int i = 0; i < remove_edge_number; i++)
        {
            edge e;
            e.u = DeleteEdge[i].u;
            e.v = DeleteEdge[i].v;
            e.w = DeleteEdge[i].w;
            if (e.w >= 0)
            {
                vector<vector<int> > check_cycle_graph = adj_list;
                
                check_cycle_graph[e.u].push_back(e.v);

                if(DFS(check_cycle_graph))
                {
                    temp.push_back(e);
                    remove_weght += e.w;
                    num_remove_edge += 1;
                }
                else
                {
                    adj_list = check_cycle_graph;
                }
                
            }
            else
            {
                temp.push_back(e);
                remove_weght += e.w;
                num_remove_edge += 1;
            }
        }
        remove_edge_number = num_remove_edge;
        remove_edge_weight = remove_weght;
        DeleteEdge = temp;
    }
    
    //  WRITE FILE
    ofstream fout;
    fout.open(argv[2]);
    fout << remove_edge_weight << "\n";  

    for (int i=0 ; i<remove_edge_number ; ++i)
    {
        fout << DeleteEdge[i].u << " " << DeleteEdge[i].v << " " << DeleteEdge[i].w  << "\n";  
    }

    fout.close();
    return 0;
}