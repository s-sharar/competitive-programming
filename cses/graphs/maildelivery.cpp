#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<pair<int,int>>> graph;
vector<int> degree;
vector<int> edgeUsed;
vector<int> it;
vector<int> route;

void hierholzer(int node) {
    while (it[node] < (int)graph[node].size()) {
        auto [nei, edgeId] = graph[node][it[node]];
        it[node]++;
        if (edgeUsed[edgeId]) continue;
        edgeUsed[edgeId] = 1;
        hierholzer(nei);
    }
    route.push_back(node); // add when stuck
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    graph.assign(n, {});
    degree.assign(n, 0);

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        graph[a].push_back({b, i});
        graph[b].push_back({a, i});
        degree[a]++;
        degree[b]++;
    }

    // 1) all degrees must be even
    for (int i = 0; i < n; i++) {
        if (degree[i] % 2 != 0) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
    }

    // 2) all nodes with degree > 0 must be reachable from node 0
    vector<int> visited(n, 0);
    stack<int> st;
    st.push(0);
    visited[0] = 1;

    while (!st.empty()) {
        int u = st.top();
        st.pop();
        for (auto [v, id] : graph[u]) {
            if (!visited[v]) {
                visited[v] = 1;
                st.push(v);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (degree[i] > 0 && !visited[i]) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
    }

    edgeUsed.assign(m, 0);
    it.assign(n, 0);
    route.clear();
    route.reserve(m + 1);

    hierholzer(0);

    if ((int)route.size() != m + 1) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    reverse(route.begin(), route.end());
    for (int i = 0; i < (int)route.size(); i++) {
        cout << route[i] + 1 << (i + 1 == (int)route.size() ? '\n' : ' ');
    }
}
