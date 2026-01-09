#include <bits/stdc++.h>
using namespace std;

void dfsOrder(int node, const vector<vector<int>>& graph, vector<int>& order, vector<bool>& visited) {
    visited[node] = true;
    for (int nei : graph[node]) {
        if (!visited[nei]) dfsOrder(nei, graph, order, visited);
    }
    order.push_back(node);
}

// FIXED: return sum of coins in this SCC, no "cost" param
long long dfsAssign(const vector<int>& coins, int node, const vector<vector<int>>& reverseGraph, vector<int>& comp, int compId) {
    comp[node] = compId;
    long long cost = coins[node];
    for (int nei : reverseGraph[node]) {
        if (comp[nei] == -1) cost += dfsAssign(coins, nei, reverseGraph, comp, compId);
    }
    return cost;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> coins(n);
    for (int i = 0; i < n; i++) cin >> coins[i];

    vector<vector<int>> graph(n), reverseGraph(n);

    // NEW: store edges to build SCC DAG later
    vector<pair<int,int>> edges;
    edges.reserve(m);

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        graph[a].push_back(b);
        reverseGraph[b].push_back(a);
        edges.push_back({a, b});
    }

    vector<int> order;
    vector<bool> visited(n, false);
    for (int i = 0; i < n; i++) {
        if (!visited[i]) dfsOrder(i, graph, order, visited);
    }

    vector<int> comp(n, -1);
    vector<long long> sccCost;
    int numComps = 0;

    for (int i = n - 1; i >= 0; i--) {
        int node = order[i];
        if (comp[node] == -1) {
            long long cost = dfsAssign(coins, node, reverseGraph, comp, numComps);
            sccCost.push_back(cost);
            numComps++;
        }
    }

    // Build SCC DAG
    vector<vector<int>> sccGraph(numComps);
    vector<int> indegree(numComps, 0);

    // dedupe edges between SCCs
    vector<pair<int,int>> sccEdges;
    sccEdges.reserve(m);
    for (auto [a, b] : edges) {
        int ca = comp[a], cb = comp[b];
        if (ca != cb) sccEdges.push_back({ca, cb});
    }
    sort(sccEdges.begin(), sccEdges.end());
    sccEdges.erase(unique(sccEdges.begin(), sccEdges.end()), sccEdges.end());

    for (auto [ca, cb] : sccEdges) {
        sccGraph[ca].push_back(cb);
        indegree[cb]++;
    }

    // DP on DAG (Kahn)
    vector<long long> dp(numComps, LLONG_MIN);
    queue<int> q;
    for (int i = 0; i < numComps; i++) {
        dp[i] = sccCost[i];          // can start anywhere
        if (indegree[i] == 0) q.push(i);
    }

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : sccGraph[u]) {
            dp[v] = max(dp[v], dp[u] + sccCost[v]);
            if (--indegree[v] == 0) q.push(v);
        }
    }

    cout << *max_element(dp.begin(), dp.end()) << "\n";
}


/*

vector<long long> dp(numComps, -1);

function<long long(int)> solve = [&](int v) -> long long {
    if (dp[v] != -1) return dp[v];
    long long bestChild = 0;
    for (int to : sccGraph[v]) {
        bestChild = max(bestChild, solve(to));
    }
    return dp[v] = sccCost[v] + bestChild;
};

long long ans = 0;
for (int v = 0; v < numComps; v++) ans = max(ans, solve(v));
cout << ans << "\n";


*/