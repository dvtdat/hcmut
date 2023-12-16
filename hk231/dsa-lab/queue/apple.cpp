#include <bits/stdc++.h>

using namespace std;

bool check(vector<vector<int>>& adj, int x, int y) {
    int n = (int)adj.size();
    if (n < 1) return false;

    int m = (int)adj[0].size();

    return (0 <= x && x < n && 0 <= y && y < m);
}

typedef pair<int, int> ii;
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, -1, 1};
const int inf = (int)1e9;

void bfs(vector<vector<int>>& adj, vector<vector<int>>& d, int i, int j) {
    queue<ii> q; q.push(ii(i, j));
    d[i][j] = 0;

    while (q.size()) {
        int ux = q.front().first;
        int uy = q.front().second;
        q.pop();

        for (int k = 0; k < 4; ++k) {
            int vx = ux + dx[k];
            int vy = uy + dy[k];
            
            if (!check(adj, vx, vy) || adj[vx][vy] != 1) continue;
            
            if (d[vx][vy] > d[ux][uy] + 1) {
                d[vx][vy] = d[ux][uy] + 1;
                q.push(ii(vx, vy));
            }
        }
    }
}

int secondsToBeRotten(vector<vector<int>>& adj) {
    if ((int)adj.size() < 1) return -1;
    vector<vector<int>> d((int)adj.size(), vector<int>((int)adj[0].size(), inf));

    for (int i = 0; i < (int)adj.size(); ++i) {
        for (int j = 0; j < (int)adj[0].size(); ++j) {
            if (adj[i][j] == 2 && d[i][j] == inf) bfs(adj, d, i, j);
        }
    }

    int mx = 0;

    for (int i = 0; i < (int)adj.size(); ++i) {
        for (int j = 0; j < (int)adj[0].size(); ++j) {
            if (adj[i][j] == 1) mx = max(mx, d[i][j]);
        }
    }

    return (mx == inf ? -1 : mx);
}

int main() {
    int rows, cols;
    cin >> rows >> cols;
    vector<vector<int>> grid(rows, vector<int>(cols));
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) cin >> grid[i][j];
    }
    cout << secondsToBeRotten(grid);
}