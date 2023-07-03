#include "lib.h"

void MyGraph::addUndirectedEdge(int u, int v, int w)
{
    adj[u].push_back(ii(v, w));
    adj[v].push_back(ii(u, w));
    E++; E++;
    if (u >= V) V = u + 1;
    if (v >= V) V = v + 1;
}

void MyGraph::addDirectedEdge(int u, int v, int w)
{
    adj[u].push_back(ii(v, w));
    E++;
    if (u >= V) V = u + 1;
    if (v >= V) V = v + 1;
}

int MyGraph::getVertices()
{
    return V;
}

int MyGraph::getEdges()
{
    return E;
}

int* MyGraph::dijkstra(int start)
{
    priority_queue<ii, vector<ii>, greater<ii>> pq;
    pq.push(ii(0, start));

    int* dist = new int[V];
    for (int i = 0; i < V; ++i) dist[i] = inf;
    dist[start] = 0;

    while (!pq.empty())
    {
        int u = pq.top().second;
        int du = pq.top().first;
        pq.pop();

        if (du != dist[u]) continue;

        for (int i = 0; i < (int)adj[u].size(); ++i)
        {
            int v = adj[u][i].first;
            int w = adj[u][i].second;

            if (dist[v] > du + w)
            {
                dist[v] = du + w;
                pq.push(ii(dist[v], v));
            }
        }
    }

    return dist;
}

int* MyGraph::bellmanFord(int start)
{
    int* dist = new int[V];
    for (int i = 0; i < V; ++i) dist[i] = inf;
    dist[start] = 0;

    for (int k = 0; k < V - 1; ++k)
    {
        for (int u = 0; u < V; ++u)
        {
            for (int i = 0; i < (int)adj[u].size(); ++i)
            {
                int v = adj[u][i].first;
                int w = adj[u][i].second;

                if (dist[u] != inf && dist[v] > dist[u] + w)
                {
                    dist[v] = dist[u] + w;
                }
            }
        }

        for (int i = 1; i < V; ++i)
        {
            cout << dist[i] << ' ';
        }   
        cout << '\n';
    }

    for (int u = 0; u < V; ++u)
    {
        for (int i = 0; i < (int)adj[u].size(); ++i)
        {
            int v = adj[u][i].first;
            int w = adj[u][i].second;
            if (dist[u] != inf && dist[v] > dist[u] + w)
            {
                hasNegativeCycle = true;
            }
        }
    }

    return dist;
}
