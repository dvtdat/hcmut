#include "lib.cpp"

int main()
{
    // freopen("input.inp", "r", stdin);
    // int n, m; cin >> n >> m;
    // int s; cin >> s;

    // MyGraph graph(n);

    // for (int i = 0; i < m; ++i)
    // {
    //     int u, v, w; cin >> u >> v >> w;
    //     graph.addEdge(u, v, w);
    // }
   
    // int* distance = graph.dijkstra(s);
    // for (int i = 0; i < graph.getVertices(); ++i)
    // {
    //     cout << distance[i] << ' ';
    // }
    // cout << '\n';
    // distance = graph.bellmanFord(s);
    // for (int i = 0; i < graph.getVertices(); ++i)
    // {
    //     cout << distance[i] << ' ';
    // }

    int cnt = 0;
    for (int i = 1; i <= 2022; ++i)
    {
        if (i % 4 == 0 || i % 6 == 0) cnt++;
    }  
    cout << cnt;
}