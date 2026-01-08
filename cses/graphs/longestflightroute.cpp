#include <bits/stdc++.h>
using namespace std;

// Takeaways: 
// DAG -> think topo order
// if processed in topo order, then we can guarantee a node is fully processed before considering its neighbors
// dp with graphs
// print path -> store parent refs

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n);
    vector<int> indegree(n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        adj[a].push_back(b);
        indegree[b]++;
    }
    queue<int> q;
    for (int i = 0; i < n; ++i) {
        if (!indegree[i]) q.push(i);
    }

    vector<int> topoOrder;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        topoOrder.push_back(node);
        for (int nei : adj[node]) {
            indegree[nei]--;
            if (!indegree[nei]) q.push(nei);
        }
    }

    vector<int> dp(n, INT_MIN);
    vector<int> parent(n, -1);
    dp[0] = 1;
    for (int i = 0; i < n; ++i) {
        int node = topoOrder[i];
        if (dp[node] == INT_MIN) continue;
        for (int nei : adj[node]) {
            if (dp[node] + 1 > dp[nei]) {
                parent[nei] = node;
                dp[nei] = dp[node] + 1;
            }
        }
    }
    if (dp[n - 1] == INT_MIN) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }
    vector<int> path;
    for (int i = n - 1; i != -1; i = parent[i]) {
        path.push_back(i);
    }
    reverse(path.begin(), path.end());
    cout << path.size() << endl;
    for (int i = 0; i < path.size(); ++i) {
        cout << path[i] + 1 << (i + 1 == path.size() ? "\n" : " ");
    }
}
