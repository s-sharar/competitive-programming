#include <bits/stdc++.h>
using namespace std;

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

    vector<int> res;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        res.push_back(node);
        for (int nei : adj[node]) {
            indegree[nei]--;
            if (!indegree[nei]) q.push(nei);
        }
    }

    if (res.size() < n) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }
    for (int i = 0; i < n; ++i) {
        cout << res[i] + 1 << (i + 1 == n ? "\n" : " ");
    }
}
