#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int numPlanets, numQueries;
    cin >> numPlanets >> numQueries;

    vector<int> nextPlanet(numPlanets);
    for (int i = 0; i < numPlanets; i++) {
        cin >> nextPlanet[i];
        --nextPlanet[i];
    }

    // Build reverse edges + indegree for cycle detection
    vector<vector<int>> reverseEdges(numPlanets);
    vector<int> indegree(numPlanets, 0);
    for (int u = 0; u < numPlanets; u++) {
        int v = nextPlanet[u];
        reverseEdges[v].push_back(u);
        indegree[v]++;
    }

    // 1) Mark cycle nodes using Kahn removal
    queue<int> q;
    vector<bool> isCycleNode(numPlanets, true);
    for (int v = 0; v < numPlanets; v++) {
        if (indegree[v] == 0) q.push(v);
    }
    while (!q.empty()) {
        int v = q.front(); q.pop();
        isCycleNode[v] = false;
        int to = nextPlanet[v];
        indegree[to]--;
        if (indegree[to] == 0) q.push(to);
    }

    // 2) Binary lifting table for forward jumps
    const int LOG = 30; // 2^30 > 1e9; enough since steps <= n (2e5)
    vector<vector<int>> jump(LOG, vector<int>(numPlanets));
    for (int v = 0; v < numPlanets; v++) jump[0][v] = nextPlanet[v];
    for (int p = 1; p < LOG; p++) {
        for (int v = 0; v < numPlanets; v++) {
            jump[p][v] = jump[p - 1][ jump[p - 1][v] ];
        }
    }

    auto lift = [&](int start, int steps) {
        int cur = start;
        for (int p = 0; p < LOG; p++) {
            if (steps & (1 << p)) cur = jump[p][cur];
        }
        return cur;
    };

    // 3) Assign cycleId, posInCycle, cycleLen
    vector<int> cycleId(numPlanets, -1);
    vector<int> posInCycle(numPlanets, -1);
    vector<int> cycleLen; // indexed by cycleId
    int numCycles = 0;

    for (int v = 0; v < numPlanets; v++) {
        if (!isCycleNode[v] || cycleId[v] != -1) continue;

        // walk the cycle to label it
        int cur = v;
        vector<int> cycleNodes;
        while (cycleId[cur] == -1) {
            cycleId[cur] = numCycles;
            cycleNodes.push_back(cur);
            cur = nextPlanet[cur];
        }
        int L = (int)cycleNodes.size();
        for (int i = 0; i < L; i++) posInCycle[cycleNodes[i]] = i;
        cycleLen.push_back(L);
        numCycles++;
    }

    // 4) For all nodes, compute depthToCycle and cycleEntry using BFS from cycles via reverse edges
    vector<int> depthToCycle(numPlanets, -1);
    vector<int> cycleEntry(numPlanets, -1);

    queue<int> bfs;
    for (int v = 0; v < numPlanets; v++) {
        if (isCycleNode[v]) {
            depthToCycle[v] = 0;
            cycleEntry[v] = v;
            bfs.push(v);
        }
    }

    while (!bfs.empty()) {
        int v = bfs.front(); bfs.pop();
        for (int prev : reverseEdges[v]) {
            if (depthToCycle[prev] != -1) continue;
            depthToCycle[prev] = depthToCycle[v] + 1;
            cycleEntry[prev] = cycleEntry[v];
            cycleId[prev] = cycleId[v];
            bfs.push(prev);
        }
    }

    // Answer queries
    while (numQueries--) {
        int a, b;
        cin >> a >> b;
        --a; --b;

        if (cycleId[a] != cycleId[b]) {
            cout << -1 << "\n";
            continue;
        }

        // Case 1: b on the chain from a (tree ancestor)
        if (depthToCycle[a] >= depthToCycle[b]) {
            int lifted = lift(a, depthToCycle[a] - depthToCycle[b]);
            if (lifted == b) {
                cout << (depthToCycle[a] - depthToCycle[b]) << "\n";
                continue;
            }
        }

        // Otherwise, only reachable if b is on the cycle
        if (depthToCycle[b] != 0) {
            cout << -1 << "\n";
            continue;
        }

        int entry = cycleEntry[a]; // cycle node you reach from a
        int L = cycleLen[cycleId[b]];
        int distOnCycle = (posInCycle[b] - posInCycle[entry] + L) % L;

        cout << (ll)depthToCycle[a] + distOnCycle << "\n";
    }
}
