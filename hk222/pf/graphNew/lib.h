#include <iostream>
#include <iomanip>
#include <string>
#include <stack>
#include <queue>
#include <vector>

using namespace std;

const int inf = 1e9;
const int maxN = 100;

typedef pair<int, int> ii;

class MyGraph
{
protected:
    int V;
    int E;
    vector<ii> adj[maxN];
    bool hasNegativeCycle = false;
public:
    MyGraph(): V(0), E(0) {}
    MyGraph(int V): V(V) {}
    ~MyGraph() {}
    void addUndirectedEdge(int u, int v, int w);
    void addDirectedEdge(int u, int v, int w);
    int getVertices();
    int getEdges();

    int* dijkstra(int s);
    int* bellmanFord(int s);
};

class MyBipartiteGraph
{

};