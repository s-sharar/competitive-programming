#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    int n, m;
    cin >> n >> m;
    vector<int> indegree(n);

    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        adj[a].push_back(b);
        indegree[b]++;
    }

    vector<int> topoOrder;
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (indegree[i] == 0) q.push(i);
    }

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        topoOrder.push_back(node);
        for (int nei : adj[node]) {
            if (--indegree[nei] == 0) q.push(nei);
        }
    }

    vector<long long> dp(n, 0);
    dp[0] = 1;
    for (int u : topoOrder) {
        for (int nei : adj[u]) {
            dp[nei]  = (dp[nei] + dp[u]) % MOD;
        }
    }

    cout << dp[n - 1] << endl;

}
