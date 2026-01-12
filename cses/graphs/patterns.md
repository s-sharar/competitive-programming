# Graph Algorithm Patterns

## 1. Disjoint Set Union (DSU / Union-Find)

**When to use:**
- Need to track connected components dynamically as edges are added
- Connectivity queries: "Are nodes A and B in the same component?"
- Finding number of components, largest component size
- Kruskal's MST algorithm

**Implementation:**
```cpp
class DSU {
    vector<int> parent, size;
public:
    DSU(int n) {
        parent.resize(n);
        size.resize(n, 1);
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]); // path compression
    }
    bool unionSets(int x, int y) {
        int xr = find(x), yr = find(y);
        if (xr == yr) return false;
        if (size[xr] < size[yr]) swap(xr, yr); // union by size
        parent[yr] = xr;
        size[xr] += size[yr];
        return true;
    }
};
```

**Used in:** `buildingroads.cpp`, `roadconstruction.cpp`, `roadreparations.cpp`

---

## 2. BFS (Breadth-First Search)

**When to use:**
- Shortest path in **unweighted** graphs (minimum number of edges)
- Level-order traversal / distance from source
- Finding if path exists between two nodes
- Bipartite check / 2-coloring

**Implementation:**
```cpp
vector<int> dist(n, -1);
vector<int> parent(n, -1);
queue<int> q;
q.push(start);
dist[start] = 0;

while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int v : adj[u]) {
        if (dist[v] == -1) {
            dist[v] = dist[u] + 1;
            parent[v] = u;
            q.push(v);
        }
    }
}
```

**Path reconstruction:**
```cpp
vector<int> path;
for (int v = target; v != -1; v = parent[v]) path.push_back(v);
reverse(path.begin(), path.end());
```

**Used in:** `labyrinth.cpp`, `messageroutes.cpp`, `buildingteams.cpp`, `monsters.cpp`

---

## 3. DFS (Depth-First Search)

**When to use:**
- Exploring all connected cells/nodes (flood fill)
- Counting connected components
- Cycle detection
- Topological sorting (via finish times)
- Kosaraju's SCC algorithm

**Implementation (recursive):**
```cpp
void dfs(int u, vector<vector<int>>& adj, vector<bool>& visited) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v]) dfs(v, adj, visited);
    }
}
```

**Grid flood fill:**
```cpp
void dfs(vector<vector<char>>& grid, int r, int c, int n, int m) {
    if (r < 0 || r >= n || c < 0 || c >= m || grid[r][c] == '#') return;
    grid[r][c] = '#'; // mark visited
    for (auto [dr, dc] : {{1,0},{-1,0},{0,1},{0,-1}}) {
        dfs(grid, r + dr, c + dc, n, m);
    }
}
```

**Used in:** `countingrooms.cpp`, `flightroutescheck.cpp`

---

## 4. Topological Sort (Kahn's Algorithm)

**When to use:**
- Ordering tasks with prerequisites (DAG only)
- Detecting if a cycle exists (if topo order size < n, there's a cycle)
- DP on DAGs (process nodes in topological order)
- Course scheduling, build systems

**Implementation:**
```cpp
vector<int> indegree(n, 0);
for (int u = 0; u < n; u++)
    for (int v : adj[u]) indegree[v]++;

queue<int> q;
for (int i = 0; i < n; i++)
    if (indegree[i] == 0) q.push(i);

vector<int> topoOrder;
while (!q.empty()) {
    int u = q.front(); q.pop();
    topoOrder.push_back(u);
    for (int v : adj[u]) {
        if (--indegree[v] == 0) q.push(v);
    }
}

if (topoOrder.size() < n) { /* cycle exists */ }
```

**Used in:** `courseschedule.cpp`, `gameroutes.cpp`, `longestflightroute.cpp`

---

## 5. Dijkstra's Algorithm

**When to use:**
- Shortest path with **non-negative edge weights**
- Single source shortest paths
- Can track additional info (count of paths, min/max edges)

**Implementation:**
```cpp
vector<long long> dist(n, LLONG_MAX);
priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
dist[0] = 0;
pq.push({0, 0});

while (!pq.empty()) {
    auto [d, u] = pq.top(); pq.pop();
    if (d != dist[u]) continue; // skip outdated entries
    for (auto [v, w] : adj[u]) {
        if (dist[u] + w < dist[v]) {
            dist[v] = dist[u] + w;
            pq.push({dist[v], v});
        }
    }
}
```

**Used in:** `shortestroutes.cpp`, `investigation.cpp`, `flightroutes.cpp`

---

## 6. State-Space Dijkstra (Extended State)

**When to use:**
- Shortest path with additional constraints/modifiers
- "Use at most K special moves" / "Apply discount once"
- State = (node, extra_info) where extra_info tracks constraint usage

**Implementation:**
```cpp
// State: (cost, node, discountUsed)
using State = tuple<long long, int, int>;
vector<array<long long, 2>> dist(n, {LLONG_MAX, LLONG_MAX});
priority_queue<State, vector<State>, greater<>> pq;

dist[0][0] = 0;
pq.push({0, 0, 0});

while (!pq.empty()) {
    auto [cost, node, used] = pq.top(); pq.pop();
    if (cost > dist[node][used]) continue;
    
    for (auto [nei, w] : adj[node]) {
        // Normal edge
        if (cost + w < dist[nei][used]) {
            dist[nei][used] = cost + w;
            pq.push({dist[nei][used], nei, used});
        }
        // Use discount (if not used yet)
        if (used == 0 && cost + w/2 < dist[nei][1]) {
            dist[nei][1] = cost + w/2;
            pq.push({dist[nei][1], nei, 1});
        }
    }
}
```

**Used in:** `flyingdiscount.cpp`

---

## 7. K Shortest Paths

**When to use:**
- Find the k shortest paths from source to destination
- Allow processing a node up to k times

**Implementation:**
```cpp
priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
vector<int> count(n, 0);
vector<long long> results;
pq.push({0, 0});

while (!pq.empty() && results.size() < k) {
    auto [dist, node] = pq.top(); pq.pop();
    if (count[node] >= k) continue;
    count[node]++;
    
    if (node == target) results.push_back(dist);
    
    for (auto [nei, w] : adj[node]) {
        pq.push({dist + w, nei});
    }
}
```

**Used in:** `flightroutes.cpp`

---

## 8. Bellman-Ford Algorithm

**When to use:**
- Shortest paths with **negative edge weights**
- Detecting **negative cycles** (n-th iteration still updates)
- Finding negative cycle and reconstructing it
- Maximum score paths (negate weights, find shortest)

**Implementation (negative cycle detection):**
```cpp
vector<long long> dist(n, 0);  // 0 for all (super-source trick)
vector<int> parent(n, -1);
int x = -1;

for (int iter = 0; iter < n; iter++) {
    x = -1;
    for (auto [from, to, w] : edges) {
        if (dist[from] + w < dist[to]) {
            dist[to] = dist[from] + w;
            parent[to] = from;
            x = to;  // updated node on this iteration
        }
    }
}

if (x != -1) {
    // Negative cycle exists
    // Walk back n times to ensure we're on the cycle
    for (int i = 0; i < n; i++) x = parent[x];
    
    // Reconstruct cycle starting from x
    vector<int> cycle;
    int cur = x;
    do {
        cycle.push_back(cur);
        cur = parent[cur];
    } while (cur != x);
    cycle.push_back(x);
    reverse(cycle.begin(), cycle.end());
}
```

**Used in:** `cyclefinding.cpp`, `highscore.cpp`

---

## 9. Floyd-Warshall Algorithm

**When to use:**
- **All-pairs** shortest paths
- Small graphs (n ≤ 500)
- Negative weights allowed (no negative cycles)
- Dense graphs where running Dijkstra n times would be slower

**Implementation:**
```cpp
const long long INF = 1e18;
vector<vector<long long>> dist(n, vector<long long>(n, INF));

for (int i = 0; i < n; i++) dist[i][i] = 0;
for (auto [a, b, w] : edges) dist[a][b] = min(dist[a][b], w);

for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
        if (dist[i][k] >= INF) continue;
        for (int j = 0; j < n; j++) {
            if (dist[k][j] >= INF) continue;
            dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
        }
    }
}
```

**Used in:** `shortestroutes2.cpp`

---

## 10. Kruskal's Algorithm (MST)

**When to use:**
- Minimum Spanning Tree
- Works well with edge list representation
- Uses DSU for cycle detection

**Implementation:**
```cpp
sort(edges.begin(), edges.end(), [](auto& a, auto& b) {
    return a.cost < b.cost;
});

DSU dsu(n);
long long totalCost = 0;
int edgesUsed = 0;

for (auto [cost, u, v] : edges) {
    if (dsu.unionSets(u, v)) {
        totalCost += cost;
        edgesUsed++;
    }
}

if (edgesUsed != n - 1) { /* graph not connected */ }
```

**Used in:** `roadreparations.cpp`

---

## 11. Prim's Algorithm (MST)

**When to use:**
- Minimum Spanning Tree
- Works well with adjacency list representation
- Uses priority queue

**Implementation:**
```cpp
vector<bool> inMST(n, false);
priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
pq.push({0, 0}); // (edge_weight, node)
long long totalCost = 0;

while (!pq.empty()) {
    auto [w, u] = pq.top(); pq.pop();
    if (inMST[u]) continue;
    inMST[u] = true;
    totalCost += w;
    
    for (auto [v, wt] : adj[u]) {
        if (!inMST[v]) pq.push({wt, v});
    }
}
```

**Used in:** `roadreparations.cpp` (alternative solution)

---

## 12. Kosaraju's Algorithm (Strongly Connected Components)

**When to use:**
- Finding all SCCs in a directed graph
- Building DAG of SCCs for DP
- 2-SAT problems
- Checking if graph is strongly connected

**Implementation:**
```cpp
// Pass 1: Build finish order on original graph
vector<int> order;
vector<bool> seen(n, false);

function<void(int)> dfs1 = [&](int u) {
    seen[u] = true;
    for (int v : g[u]) if (!seen[v]) dfs1(v);
    order.push_back(u);
};

for (int i = 0; i < n; i++) if (!seen[i]) dfs1(i);

// Pass 2: Assign components in reverse order on reversed graph
vector<int> comp(n, -1);
int numComps = 0;

function<void(int)> dfs2 = [&](int u) {
    comp[u] = numComps;
    for (int v : gr[u]) if (comp[v] == -1) dfs2(v);
};

for (int i = n - 1; i >= 0; i--) {
    int u = order[i];
    if (comp[u] == -1) {
        dfs2(u);
        numComps++;
    }
}
```

**Used in:** `planetsandkingdoms.cpp`, `coincollector.cpp`, `giantpizza.cpp`

---

## 13. 2-SAT

**When to use:**
- Boolean satisfiability with clauses of exactly 2 literals
- Each constraint is (A OR B)
- Convert to implication graph: (A OR B) ⟹ (¬A → B) AND (¬B → A)

**Implementation:**
```cpp
// Node mapping: variable i -> positive: 2*i, negative: 2*i+1
// Negation: x ^ 1

auto litNode = [](char sign, int var) { return (sign == '+') ? 2*var : 2*var + 1; };
auto negNode = [](int node) { return node ^ 1; };

// For clause (A OR B):
addEdge(negNode(A), B);  // ¬A → B
addEdge(negNode(B), A);  // ¬B → A

// Run Kosaraju's SCC
// Check: if comp[x] == comp[¬x] for any variable, IMPOSSIBLE
// Assignment: choose x if comp[x] > comp[¬x]
```

**Used in:** `giantpizza.cpp`

---

## 14. Hierholzer's Algorithm (Eulerian Path/Circuit)

**When to use:**
- Visit **every edge exactly once**
- Eulerian circuit exists iff all vertices have even degree (undirected) or equal in/out degree (directed)
- Eulerian path exists iff exactly 0 or 2 vertices have odd degree (undirected) or exactly one vertex has out-in=1 and one has in-out=1 (directed)

**Implementation:**
```cpp
vector<int> it(n, 0);  // iterator for each node's adjacency list
vector<int> path;

function<void(int)> hierholzer = [&](int u) {
    while (it[u] < adj[u].size()) {
        auto [v, edgeId] = adj[u][it[u]++];
        if (!edgeUsed[edgeId]) {
            edgeUsed[edgeId] = true;
            hierholzer(v);
        }
    }
    path.push_back(u);  // add when stuck
};

hierholzer(start);
reverse(path.begin(), path.end());
```

**Used in:** `maildelivery.cpp`, `teleporterspath.cpp`

---

## 15. Cycle Detection

### Undirected Graph (DFS with parent tracking):
```cpp
bool dfs(int u, int parent, vector<vector<int>>& adj, 
         vector<bool>& visited, vector<int>& par, int& cycleStart, int& cycleEnd) {
    visited[u] = true;
    par[u] = parent;
    for (int v : adj[u]) {
        if (v == parent) continue;
        if (visited[v]) {
            cycleStart = v; cycleEnd = u;
            return true;
        }
        if (dfs(v, u, adj, visited, par, cycleStart, cycleEnd)) return true;
    }
    return false;
}
```

### Directed Graph (3-color DFS):
```cpp
// state: 0=unvisited, 1=in stack (gray), 2=finished (black)
vector<int> state(n, 0);

bool dfs(int u) {
    state[u] = 1;  // mark as in-progress
    for (int v : adj[u]) {
        if (state[v] == 1) {  // back edge = cycle!
            cycleStart = v; cycleEnd = u;
            return true;
        }
        if (state[v] == 0 && dfs(v)) return true;
    }
    state[u] = 2;  // mark as done
    return false;
}
```

**Used in:** `roundtrip.cpp` (undirected), `roundtrip2.cpp` (directed)

---

## 16. Bipartite Check / 2-Coloring

**When to use:**
- Dividing nodes into two groups where edges only go between groups
- Checking if graph is bipartite (no odd cycles)
- Team/side assignment problems

**Implementation:**
```cpp
vector<int> color(n, 0);  // 0=uncolored, 1 or 2
queue<int> q;

for (int i = 0; i < n; i++) {
    if (color[i] != 0) continue;
    color[i] = 1;
    q.push(i);
    
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (color[v] == 0) {
                color[v] = 3 - color[u];  // alternate: 1->2, 2->1
                q.push(v);
            } else if (color[v] == color[u]) {
                // Same color = odd cycle = not bipartite
                return false;
            }
        }
    }
}
```

**Used in:** `buildingteams.cpp`

---

## 17. Strong Connectivity Check

**When to use:**
- Check if every node can reach every other node in a directed graph
- Two DFS: one on original graph, one on reversed graph

**Implementation:**
```cpp
// If node 0 can reach all nodes, AND all nodes can reach node 0 → strongly connected

vector<int> seen(n, 0);
dfs(0, g, seen);  // check 0 reaches everyone
for (int v = 0; v < n; v++) {
    if (!seen[v]) { /* 0 cannot reach v */ }
}

fill(seen.begin(), seen.end(), 0);
dfs(0, gr, seen);  // check everyone reaches 0 (via reverse edges)
for (int v = 0; v < n; v++) {
    if (!seen[v]) { /* v cannot reach 0 */ }
}
```

**Used in:** `flightroutescheck.cpp`

---

## 18. Binary Lifting (Jump Pointers)

**When to use:**
- Answer "where do I end up after k steps?" queries
- Functional graphs (each node has exactly one outgoing edge)
- k-th ancestor in trees
- O(log k) per query after O(n log k) preprocessing

**Implementation:**
```cpp
const int LOG = 60;  // for k up to 1e18
vector<vector<int>> jump(LOG, vector<int>(n));

// Base: jump[0][v] = next[v] (1 step)
for (int v = 0; v < n; v++) jump[0][v] = next[v];

// Build: jump[p][v] = where you are after 2^p steps
for (int p = 1; p < LOG; p++) {
    for (int v = 0; v < n; v++) {
        jump[p][v] = jump[p-1][jump[p-1][v]];
    }
}

// Query: end position after k steps from start
int query(int start, long long k) {
    int cur = start;
    for (int p = 0; p < LOG; p++) {
        if (k & (1LL << p)) cur = jump[p][cur];
    }
    return cur;
}
```

**Used in:** `planetsqueries.cpp`, `planetsqueries2.cpp`

---

## 19. Functional Graph Analysis

**When to use:**
- Each node has exactly one outgoing edge
- Eventually enters a cycle (rho-shaped graph ρ)
- Finding cycle nodes, distance to cycle, position in cycle

**Implementation:**
```cpp
// 1) Find cycle nodes using Kahn's algorithm (remove leaves iteratively)
vector<bool> isCycleNode(n, true);
queue<int> q;
for (int v = 0; v < n; v++) if (indegree[v] == 0) q.push(v);
while (!q.empty()) {
    int v = q.front(); q.pop();
    isCycleNode[v] = false;
    int to = next[v];
    if (--indegree[to] == 0) q.push(to);
}

// 2) Label cycles and compute positions
// 3) BFS backwards from cycle to find depthToCycle for tail nodes
```

**Used in:** `planetsqueries2.cpp`

---

## 20. DP on DAGs

**When to use:**
- Counting paths, longest/shortest path in DAG
- Any recurrence where answer depends on successors/predecessors
- Process in topological order to ensure dependencies are resolved

**Implementation:**
```cpp
// Get topological order first (Kahn's)
vector<int> topoOrder = ... ;

// DP: count paths from 0 to n-1
vector<long long> dp(n, 0);
dp[0] = 1;

for (int u : topoOrder) {
    for (int v : adj[u]) {
        dp[v] = (dp[v] + dp[u]) % MOD;
    }
}
cout << dp[n-1];
```

**Longest path:**
```cpp
vector<int> dp(n, INT_MIN);
vector<int> parent(n, -1);
dp[0] = 1;  // 1 node in path

for (int u : topoOrder) {
    if (dp[u] == INT_MIN) continue;
    for (int v : adj[u]) {
        if (dp[u] + 1 > dp[v]) {
            dp[v] = dp[u] + 1;
            parent[v] = u;
        }
    }
}
```

**Used in:** `gameroutes.cpp`, `longestflightroute.cpp`, `coincollector.cpp`

---

## 21. Hamiltonian Path (Bitmask DP)

**When to use:**
- Visit **every node exactly once**
- Small n (≤ 20) due to O(2^n × n²) complexity
- NP-hard in general, but tractable with bitmask DP

**Implementation:**
```cpp
// dp[mask][v] = ways to reach v having visited exactly the nodes in mask
vector<vector<int>> dp(1 << n, vector<int>(n, 0));
dp[1 << 0][0] = 1;  // start at node 0

for (int mask = 0; mask < (1 << n); mask++) {
    for (int v = 0; v < n; v++) {
        if (!(mask & (1 << v))) continue;
        if (dp[mask][v] == 0) continue;
        
        for (int u : adj[v]) {
            if (mask & (1 << u)) continue;  // already visited
            int newMask = mask | (1 << u);
            dp[newMask][u] = (dp[newMask][u] + dp[mask][v]) % MOD;
        }
    }
}

cout << dp[(1 << n) - 1][n - 1];  // end at node n-1, all visited
```

**Used in:** `hamiltonianflights.cpp`

---

## 22. Multi-Source BFS

**When to use:**
- Compute distances from multiple sources simultaneously
- "Escape" problems: can player reach boundary before enemies?
- Precompute enemy/obstacle distances, then BFS with constraints

**Implementation:**
```cpp
// First: BFS from all monsters to get distMonster[r][c]
queue<pair<int,int>> q;
for (all monster positions) {
    distMonster[r][c] = 0;
    q.push({r, c});
}
// ... standard BFS ...

// Second: BFS from player, only move to cells where
// distPlayer[newR][newC] < distMonster[newR][newC]
```

**Used in:** `monsters.cpp`

---

## 23. SCC DAG + DP

**When to use:**
- Need to answer questions about strongly connected components
- DP where nodes in same SCC share the same answer
- Collapse SCCs to single nodes, then DP on DAG of SCCs

**Implementation:**
```cpp
// 1) Find SCCs using Kosaraju
// 2) Compute aggregate value for each SCC (e.g., sum of coins)
// 3) Build DAG of SCCs (deduplicate edges between SCCs)
// 4) DP on DAG (topological order via Kahn's)

vector<long long> dp(numSCCs);
for (int i = 0; i < numSCCs; i++) dp[i] = sccValue[i];

// Process in topological order
for (int u : topoOrder) {
    for (int v : sccAdj[u]) {
        dp[v] = max(dp[v], dp[u] + sccValue[v]);
    }
}
```

**Used in:** `coincollector.cpp`

---

## Quick Reference: When to Use What

| Problem Type | Algorithm |
|--------------|-----------|
| Shortest path, unweighted | BFS |
| Shortest path, non-negative weights | Dijkstra |
| Shortest path, negative weights | Bellman-Ford |
| All-pairs shortest paths | Floyd-Warshall |
| Minimum spanning tree | Kruskal's or Prim's |
| Connectivity / components (dynamic) | DSU |
| Topological ordering | Kahn's (BFS) or DFS |
| Strongly connected components | Kosaraju's or Tarjan's |
| Cycle detection (undirected) | DFS with parent |
| Cycle detection (directed) | 3-color DFS |
| Negative cycle detection | Bellman-Ford (n iterations) |
| Eulerian path/circuit | Hierholzer's |
| Hamiltonian path (small n) | Bitmask DP |
| K-th successor / ancestor | Binary Lifting |
| 2-SAT | Implication graph + SCC |
| Bipartite check | BFS 2-coloring |
| Path with constraints | State-space Dijkstra |
| DP on graph | Topological order + DP |
