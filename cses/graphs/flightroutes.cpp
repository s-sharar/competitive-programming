#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<pair<int, int>>> adj(n);
    for (int i = 0; i < m; i++) {
        int a, b, len;
        cin >> a >> b >> len;
        --a; --b;
        adj[a].push_back({b, len});
    }

    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
    vector<long long> res;
    vector<int> processed(n, 0);
    pq.push({0, 0});
    int kOrig = k;
    while (k) {
        auto [len, node] = pq.top();
        pq.pop();
        if (processed[node] >= kOrig) continue;
        ++processed[node];
        if (node == n - 1) {
            res.push_back(len);
            --k;
            if (k <= 0) break;
        }
        for (auto p : adj[node]) {
            pq.push({len + p.second, p.first});
        }
    }

    for (int i = 0; i < kOrig; ++i) {
        cout << res[i] << (i + 1 == kOrig ? "\n" : " ");
    }

}
