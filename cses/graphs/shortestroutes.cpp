#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> adj(n);
    for (int i = 0; i < m; i++) {
        int a, b, len;
        cin >> a >> b >> len;
        --a; --b;
        adj[a].push_back({b, len});
    }

    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
    vector<bool> visited(n, false);
    vector<long long> res(n, 0);
    pq.push({0, 0});
    while (!pq.empty()) {
        auto [len, node] = pq.top();
        pq.pop();
        if (visited[node]) continue;
        res[node] = len;
        visited[node] = true;
        for (auto p : adj[node]) {
            if (!visited[p.first]) {
                pq.push({len + p.second, p.first});
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        cout << res[i] << (i + 1 == n ? "\n" : " ");
    }

}
