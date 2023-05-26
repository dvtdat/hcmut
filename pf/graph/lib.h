#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> ii;

const int maxN = 15;
const int inf = 2e9;

vector<ii> adj[maxN];

void print(vector<ii> adj[]);
void dijkstra(vector<ii> adj[], int start, int *distance);
void bellmanford(vector<ii> adj[], int start, int *distance);