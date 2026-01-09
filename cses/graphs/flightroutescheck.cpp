#include <bits/stdc++.h>
using namespace std;

// strong connectivity check -> two dfs, one on original graph, one on reversed graph
// if any node s can reach any node u, and any node v can reach s
// u->s->v is a path hence the graph is strongly connected

void dfs(int start, const vector<vector<int>>& g, vector<int>& seen) {
    stack<int> st;
    st.push(start);
    seen[start] = 1;

    while (!st.empty()) {
        int u = st.top();
        st.pop();
        for (int v : g[u]) {
            if (!seen[v]) {
                seen[v] = 1;
                st.push(v);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> g(n), gr(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        g[a].push_back(b);
        gr[b].push_back(a); // reversed edge
    }

    vector<int> seen(n, 0);
    dfs(0, g, seen);
    for (int v = 0; v < n; v++) {
        if (!seen[v]) {
            cout << "NO\n" << 1 << " " << (v + 1) << "\n";
            return 0;
        }
    }

    fill(seen.begin(), seen.end(), 0);
    dfs(0, gr, seen);
    for (int v = 0; v < n; v++) {
        if (!seen[v]) {
            cout << "NO\n" << (v + 1) << " " << 1 << "\n";
            return 0;
        }
    }

    cout << "YES\n";
}
