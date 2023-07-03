#include "lib.cpp"

int main()
{
    freopen("input.inp", "r", stdin);
    int n, m; cin >> n >> m;
    int s; cin >> s;

    MyGraph graph(n);

    for (int i = 0; i < m; ++i)
    {
        int u, v, w; cin >> u >> v >> w;
        graph.addDirectedEdge(u, v, w);
    }
   
    int* distance = graph.bellmanFord(s);
    for (int i = 1; i < graph.getVertices(); ++i)
    {
        cout << distance[i] << ' ';
    }
}