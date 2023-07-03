#include "lib.h"

void print(int *distance)
{
    for (int i = 0; i < maxN; ++i)
    {
        if (distance[i] == inf) cout << setw(4) << "i";
        else cout << setw(4) << distance[i];
        cout << ' ';
    }
    cout << '\n';    
}

void dijkstra(vector<ii> adj[], int start, int *distance)
{
    priority_queue<ii, vector<ii>, greater<ii>> pq;
    pq.push(ii(0, start));

    for (int i = 0; i < maxN; ++i) distance[i] = inf;
    distance[start] = 0;
    cout << "Choosing " << 0 << " as the next vertex:";

    while(!pq.empty())
    {
        print(distance);
        int u = pq.top().second;
        cout << "Choosing " << u << " as the next vertex:";
        int du = pq.top().first;
        pq.pop();

        if (du != distance[u]) continue;

        for (int i = 0; i < (int)adj[u].size(); ++i)
        {
            int v = adj[u][i].first;
            int w = adj[u][i].second;
            
            if (distance[v] > du + w)
            {
                distance[v] = du + w;
                pq.push(ii(distance[v], v));
            }
        }
    }
}

void bellmanford(vector<ii> adj[], int start, int *distance)
{
    for (int i = 0; i < maxN; ++i) distance[i] = inf;
    distance[start] = 0;

    for (int k = 0; k < maxN - 1; ++k)
    {
        for (int u = 0; u < maxN; ++u)
        {
            for (int i = 0; i < (int)adj[u].size(); ++i)
            {
                int v = adj[u][i].first;
                int w = adj[u][i].second;

                if (distance[u] != inf && distance[v] > distance[u] + w)
                {
                    distance[v] = distance[u] + w;
                }
            }
        }
        print(distance);
    }

    for (int u = 0; u < maxN; ++u)
    {
        for (int i = 0; i < (int)adj[u].size(); ++i)
        {
            int v = adj[u][i].first;
            int w = adj[u][i].second;
            if (distance[u] != inf && distance[v] > distance[u] + w)
            {
                cout << "Contains negative weight cycle\n";
                return;
            }
        }
    }
}