#include "lib.cpp"

int main()
{
    freopen("input.inp", "r", stdin);
    int distance[maxN];

    int n, m; cin >> n >> m;

    for (int i = 0; i < m; ++i)
    {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back(ii(v, w));
        adj[v].push_back(ii(u, w));
    }
   
    dijkstra(adj, 1, distance);
    print(distance);
}