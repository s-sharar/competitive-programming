#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int from;
    int to;
    long long weight;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<Edge> edges;
    edges.reserve(m);
    for (int i = 0; i < m; i++) {
        int a, b;
        long long c;
        cin >> a >> b >> c;
        --a; --b;
        edges.push_back({a, b, c});
    }

    // TAKEAWAY 1:
    // We need to detect a negative cycle ANYWHERE in the graph (not just reachable from one source).
    // Trick: set dist[i] = 0 for all i (equivalent to adding a super-source with 0-weight edges).
    vector<long long> dist(n, 0);

    // TAKEAWAY 2:
    // Store parent pointers on relaxations so we can reconstruct the cycle (a "witness") later.
    vector<int> parent(n, -1);

    int x = -1; // TAKEAWAY 3: x will store a vertex updated on the nth pass (proof of negative cycle)

    // TAKEAWAY 4:
    // Bellman-Ford does n passes for negative cycle detection.
    // If there is any relaxation on the nth pass, a negative cycle exists.
    for (int iter = 0; iter < n; iter++) {
        x = -1; // reset; if it stays -1 this pass, no relaxation happened this pass
        for (auto [from, to, weight] : edges) {
            // Relaxation: can we improve dist[to] by going through from?
            if (dist[from] + weight < dist[to]) {
                dist[to] = dist[from] + weight;
                parent[to] = from; // TAKEAWAY 2: record how we improved to
                x = to;            // TAKEAWAY 3: the UPDATED node is the witness, not 'from'
            }
        }
    }

    // If x never got updated on the nth pass, there is no negative cycle anywhere.
    if (x == -1) {
        cout << "NO\n";
        return 0;
    }

    // TAKEAWAY 5:
    // x might be downstream of the negative cycle. To ensure x is INSIDE the cycle,
    // walk parent pointers n times (pigeonhole principle -> must enter a cycle).
    for (int i = 0; i < n; i++) x = parent[x];

    // TAKEAWAY 6:
    // Now x is guaranteed to be on the cycle.
    // Walk parent pointers until we come back to x to collect the cycle nodes.
    vector<int> cycle;
    int cur = x;
    cycle.push_back(cur);
    while (true) {
        cur = parent[cur];
        cycle.push_back(cur);
        if (cur == x) break;
    }

    reverse(cycle.begin(), cycle.end());

    cout << "YES\n";
    // TAKEAWAY 7:
    // Print 1-indexed nodes (CSES input is 1-indexed).
    for (int i = 0; i < (int)cycle.size(); i++) {
        cout << cycle[i] + 1 << (i + 1 == (int)cycle.size() ? '\n' : ' ');
    }
    return 0;
}
