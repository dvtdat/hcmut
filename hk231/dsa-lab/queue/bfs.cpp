#include <bits/stdc++.h>

using namespace std;

void bfs(vector<vector<int>> adj, int s) {
	queue<int> q; q.push(s);
	vector<int> d;
	vector<int> visited(adj.size(), false);
	visited[s] = true;
	
	while (q.size()) {
	    int u = q.front(); q.pop();
        d.push_back(u);
	    
	    for (int v : adj[u]) {
	        if (visited[v]) continue;
	        visited[v] = true;
	        q.push(v);
	    }
	}
	
    for (int i = 0; i < d.size() - 1; ++i) cout << d[i] << ' '; cout << d.back();
}

int main() {
    	int init_graph[10][10] = {  {0, 1, 1, 0, 1, 0, 1, 0, 1, 0},
				    {0, 0, 1, 1, 0, 0, 0, 1, 0, 0},
				    {0, 1, 0, 0, 0, 1, 1, 0, 1, 1},
				    {1, 0, 0, 0, 0, 0, 0, 1, 0, 0},
				    {0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
				    {1, 0, 1, 0, 1, 0, 0, 0, 1, 0},
				    {0, 0, 1, 1, 0, 1, 0, 0, 0, 0},
				    {1, 0, 0, 0, 0, 1, 1, 0, 1, 0},
				    {0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
				    {1, 0, 1, 0, 1, 0, 0, 0, 1, 0} };
	int n = 10;
	vector<vector<int>> graph(n, vector<int>());
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (init_graph[i][j]) graph[i].push_back(j);
		}
	}

	bfs(graph, 0);
}