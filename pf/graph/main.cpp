#include "dijkstra.h"

int main()
{
    int distance[maxN];

    int n, m; cin >> n >> m;

    for (int i = 0; i < m; ++i)
    {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back(ii(v, w));
        adj[v].push_back(ii(u, w));
    }

    dijkstra(adj, 0, distance);

    for (int i = 0; i < n; ++i)
    {
        cout << distance[i] << '\n';
    }
}