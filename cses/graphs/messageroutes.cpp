#include <bits/stdc++.h>
using namespace std;

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

    vector<int> parent(n, -1);
    vector<bool> vis(n, false);

    queue<int> q;
    q.push(0);
    vis[0] = true;
    parent[0] = -1;

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (int nei : adj[node]) {
            if (!vis[nei]) {
                vis[nei] = true;
                parent[nei] = node;
                q.push(nei);
            }
        }
    }

    if (!vis[n - 1]) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    // Reconstruct path: n-1 -> ... -> 0
    vector<int> path;
    for (int v = n - 1; v != -1; v = parent[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());

    cout << path.size() << "\n";
    for (int i = 0; i < (int)path.size(); i++) {
        cout << path[i] + 1 << (i + 1 == (int)path.size() ? '\n' : ' ');
    }
}
