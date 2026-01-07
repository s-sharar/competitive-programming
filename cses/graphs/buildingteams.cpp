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

    vector<int> color(n, 0);
    for (int i = 0; i < n; ++i) {
        if (color[i] != 0) continue;
        color[i] = 1;
        queue<int> q;
        q.push(i);
        while (!q.empty()) {
            int idx = q.front();
            q.pop();
            for (int nei : adj[idx]) {
                if (color[nei] == 0) {
                    color[nei] = 3 - color[idx];
                    q.push(nei);
                } else if (color[nei] == color[idx]) {
                    cout << "IMPOSSIBLE\n";
                    return 0;
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << color[i] << (i + 1 == n ? '\n' : ' ');
    }
}
