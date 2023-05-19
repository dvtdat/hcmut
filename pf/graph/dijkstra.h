#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <string>
#include <math.h>
#include <stdio.h>

using namespace std;

typedef pair<int, int> ii;

const int maxN = 1000;
const int inf = 2e9;

vector<ii> adj[maxN];

void dijkstra(vector<ii> adj[], int start, int *distance)
{
    priority_queue<ii, vector<ii>, greater<ii>> pq;
    pq.push(ii(0, start));

    for (int i = 0; i < maxN; ++i) distance[i] = inf;
    distance[start] = 0;

    while(!pq.empty())
    {
        int u = pq.top().second;
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
