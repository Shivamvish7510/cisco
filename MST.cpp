// prim algorthim

#include <iostream>
#include <queue>
using namespace std;

void primMst(Graph v)
{
    int V = G.v;
    int minWeight = 0;
    int visited[V] = {0};
    int parent[V] = {0};
    int minWeight = 0;
    int minNode = 0;
    int minEdge = 0;
    int i, j = 0;
    for (i = 0; i < V; i++)
    {
        visited[i] = 0;
        parent[i] = -1;
    }
    visited[0] = 1;
    parent[0] = -1;
    while (minNode < V - 1)
    {
        minWeight = 1000000;
        minNode = -1;
        for (i = 0; i < V; i++)
        {
            if (visited[i] == 1)
            {
                for (j = 0; j < V; j++)
                {
                    if (visited[j] == 0 && G.adj[i][j] != 0 &&
                        G.adj[i][j] < minWeight)
                    {
                        minWeight = G.adj[i][j];
                        minNode = j;
                        minEdge = i;
                    }
                }
            }
            visited[minNode] = 1;
            parent[minNode] = minEdge;
            minWeight = 0;
        }
        cout << "Edge " << minEdge << " - " << minNode << " : "
             << minWeight << endl;
    }
}
