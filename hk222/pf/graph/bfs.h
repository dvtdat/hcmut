#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <string>
#include <math.h>
#include <stdio.h>

using namespace std;

const int maxN = 1000;
vector<int> adj[maxN];

void bfs(vector<int> adj[], int start, int *order)
{
    queue<int> q; 
    q.push(start);

    for (int i = 0; i < maxN; ++i) order[i] = -1;
    order[start] = 0;

    while(!q.empty())
    {
        int u = q.front(); q.pop();

        for (int i = 0; i < (int)adj[u].size(); ++i)
        {
            int v = adj[u][i];
            if (order[v] == -1) 
            {
                q.push(v);
                order[v] = order[u] + 1;
            }
        }
    }
}