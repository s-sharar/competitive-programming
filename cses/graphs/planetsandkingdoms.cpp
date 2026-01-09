#include <bits/stdc++.h>
using namespace std;

// kosaraju


void dfsOrder(int u, const vector<vector<int>>& g, vector<int>& seen, vector<int>& order) {
    seen[u] = 1;
    for (int v : g[u]) if (!seen[v]) dfsOrder(v, g, seen, order);
    order.push_back(u); // finished u
}

void dfsAssign(int u, const vector<vector<int>>& gr, vector<int>& comp, int compId) {
    comp[u] = compId;
    for (int v : gr[u]) if (comp[v] == -1) dfsAssign(v, gr, comp, compId);
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
        gr[b].push_back(a); // reversed
    }

    vector<int> seen(n, 0), order;
    order.reserve(n);

    // Pass 1: build finish order (Strongly connected component A will finish after component B if A has an edge to B)
    for (int i = 0; i < n; i++) {
        if (!seen[i]) dfsOrder(i, g, seen, order);
    }

    // Pass 2: assign components in reverse finish order on reversed graph
    vector<int> comp(n, -1);
    int numComps = 0;

    for (int i = n - 1; i >= 0; i--) {
        int node = order[i];
        if (comp[node] == -1) {
            dfsAssign(node, gr, comp, numComps);
            numComps++;
        }
    }

    cout << numComps << "\n";
    for (int i = 0; i < n; i++) {
        cout << comp[i] + 1 << (i + 1 == n ? '\n' : ' ');
    }
}
