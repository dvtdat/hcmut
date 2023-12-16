#include <bits/stdc++.h>

using namespace std;

bool bfs(vector<vector<int>> &adj, vector<int> &visited, vector<int> &d, int s) {
    queue<int> q; q.push(s);
    visited[s] = true;
    while (q.size()) {
        int u = q.front(); q.pop();

        for (int v : adj[u]) {
            if (visited[v]) {
                if (d[v] == d[u]) return false;
            } else {
                visited[v] = true;
                d[v] = !d[u];
                q.push(v);
            }
        }
    }

    return true;
}

bool isBipartite(vector<vector<int>> adj) {
    queue<int> q; q.push(0);
    vector<int> d((int)adj.size(), -1);
    vector<int> visited((int)adj.size(), false);

    for (int i = 0; i < (int)adj.size(); ++i) {
        if (visited[i]) continue;
        if (!bfs(adj, visited, d, i)) return false;
    }
    return true;
}

int main() {
    int G[6][6] = { {0, 1, 0, 0, 0, 1},
                    {1, 0, 1, 0, 0, 0},
                    {0, 1, 0, 1, 0, 0},
                    {0, 0, 1, 0, 1, 0},
                    {0, 0, 0, 1, 0, 1},
                    {1, 0, 0, 0, 1, 0} };
    int n = 6;

    vector<vector<int>> graph(n, vector<int>());
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (G[i][j]) graph[i].push_back(j);
            }
        }

    if (isBipartite(graph)) cout << "Yes"; else cout << "No";
}