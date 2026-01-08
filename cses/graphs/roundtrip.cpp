#include <bits/stdc++.h>
using namespace std;

bool dfs(const vector<vector<int>>& adj,
         vector<bool>& visited,
         vector<int>& parent,
         int p,
         int u,
         int& cycleStart,
         int& cycleEnd) {
    visited[u] = true;
    parent[u] = p;

    for (int v : adj[u]) {
        if (v == p) continue;

        if (visited[v]) {
            // v is an ancestor in undirected DFS => cycle found
            cycleStart = v;
            cycleEnd = u;
            return true;
        }

        if (dfs(adj, visited, parent, u, v, cycleStart, cycleEnd)) return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<bool> visited(n, false);
    vector<int> parent(n, -1);

    int cycleStart = -1, cycleEnd = -1;

    for (int i = 0; i < n; i++) {
        if (!visited[i] && dfs(adj, visited, parent, -1, i, cycleStart, cycleEnd)) {
            break;
        }
    }

    if (cycleStart == -1) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    // Reconstruct cycle: cycleStart -> ... -> cycleEnd -> cycleStart
    vector<int> cycle;
    cycle.push_back(cycleStart);
    for (int v = cycleEnd; v != cycleStart; v = parent[v]) {
        cycle.push_back(v);
    }
    cycle.push_back(cycleStart);
    reverse(cycle.begin(), cycle.end());

    cout << cycle.size() << "\n";
    for (int i = 0; i < (int)cycle.size(); i++) {
        cout << cycle[i] + 1 << (i + 1 == (int)cycle.size() ? '\n' : ' ');
    }
}
