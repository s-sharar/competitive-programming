#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int from;
    int to;
    long long weight; // NEGATED score
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int numNodes, numEdges;
    cin >> numNodes >> numEdges;

    vector<Edge> edges;
    edges.reserve(numEdges);

    vector<vector<int>> forwardGraph(numNodes);

    for (int i = 0; i < numEdges; i++) {
        int a, b;
        long long score;
        cin >> a >> b >> score;
        --a; --b;

        edges.push_back({a, b, -score});     // negate for shortest path
        forwardGraph[a].push_back(b);
    }

    const long long INF = (long long)4e18;
    vector<long long> minCost(numNodes, INF);
    minCost[0] = 0;

    // Bellman-Ford: relax edges up to numNodes-1 times
    for (int iter = 0; iter < numNodes - 1; iter++) {
        bool improved = false;
        for (const auto& e : edges) {
            if (minCost[e.from] == INF) continue;
            long long candidate = minCost[e.from] + e.weight;
            if (candidate < minCost[e.to]) {
                minCost[e.to] = candidate;
                improved = true;
            }
        }
        if (!improved) break;
    }

    // Mark nodes affected by a negative cycle (in the negated graph)
    vector<char> affectedByNegCycle(numNodes, 0);
    queue<int> bfs;

    for (const auto& e : edges) {
        if (minCost[e.from] == INF) continue;
        if (minCost[e.from] + e.weight < minCost[e.to]) {
            if (!affectedByNegCycle[e.to]) {
                affectedByNegCycle[e.to] = 1;
                bfs.push(e.to);
            }
        }
    }

    // Propagate: any node reachable from an affected node is also "bad"
    while (!bfs.empty()) {
        int u = bfs.front();
        bfs.pop();
        for (int v : forwardGraph[u]) {
            if (!affectedByNegCycle[v]) {
                affectedByNegCycle[v] = 1;
                bfs.push(v);
            }
        }
    }

    if (affectedByNegCycle[numNodes - 1]) {
        cout << -1 << "\n";
        return 0;
    }

    cout << -minCost[numNodes - 1] << "\n"; // un-negate back to max score
    return 0;
}
