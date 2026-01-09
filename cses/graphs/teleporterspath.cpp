#include <bits/stdc++.h>
using namespace std;

void dfs(int node, const vector<vector<int>>& graph, vector<int>& it, vector<int>& path) {
    while (it[node] < (int)graph[node].size()) {
        int nei = graph[node][it[node]];
        it[node]++;                 // consume this directed edge
        dfs(nei, graph, it, path);
    }
    path.push_back(node);           // add on backtrack
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n);
    vector<int> indegree(n, 0);
    vector<int> outdegree(n, 0);

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        graph[a].push_back(b);
        indegree[b]++;
        outdegree[a]++;
    }

    vector<int> path;
    vector<int> it(n, 0);

    if (indegree[0] + 1 != outdegree[0] || outdegree[n - 1] + 1 != indegree[n - 1]) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }
    for (int i = 1; i < n - 1; i++) {
        if (indegree[i] != outdegree[i]) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
    }

    dfs(0, graph, it, path);

    // Hierholzer produces reverse order
    reverse(path.begin(), path.end());

    // Must use all edges and end at n-1
    if ((int)path.size() != m + 1 || path.back() != n - 1) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    for (int i = 0; i < (int)path.size(); i++) {
        cout << path[i] + 1 << (i + 1 == (int)path.size() ? '\n' : ' ');
    }
    return 0;
}
