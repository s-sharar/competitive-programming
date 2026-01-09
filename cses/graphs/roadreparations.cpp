#include <bits/stdc++.h>

using namespace std;

struct Edge {
    int cost;
    int from;
    int to;
};

class DSU {
    vector<int> parent, size;
    int components;
    long long cost = 0;
    public:
    DSU(int n) {
        parent.resize(n);
        size.resize(n);
        components = n;
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
            size[i] = 1;
        }
    }

    int find(int u) {
        if (parent[u] == u) return u;
        parent[u] = find(parent[u]);
        return parent[u];
    }

    void unionSet(int cost, int u, int v) {
        int x = find(u);
        int y = find(v);
        if (x == y) return;
        this->cost += cost;
        if (size[x] < size[y]) swap(x, y);
        parent[y] = x;
        size[x] += size[y];
        --components;
    }

    int getComponents() const {
        return components;
    }

    long long getCost() const {
        return cost;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<Edge> edges(m);
    DSU dsu(n);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].from >> edges[i].to >> edges[i].cost;
        --edges[i].from; --edges[i].to;
    }
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b){
        return a.cost < b.cost;
    });
    

    for (auto [cost, from, to] : edges) {
        dsu.unionSet(cost, from, to);
    }

    if (dsu.getComponents() > 1) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    cout << dsu.getCost() << endl;


}


/*

With prims instead of kruskals


#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = (1LL<<62);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<pair<int,int>>> graph(n);
    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        --a; --b;
        graph[a].push_back({b, w});
        graph[b].push_back({a, w}); // undirected
    }

    vector<bool> inMST(n, false);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq; 
    // (edgeWeight, nodeToAdd)

    ll totalCost = 0;
    int nodesAdded = 0;

    // start from node 0 with cost 0
    pq.push({0, 0});

    while (!pq.empty()) {
        auto [w, v] = pq.top();
        pq.pop();

        if (inMST[v]) continue;
        inMST[v] = true;
        totalCost += w;
        nodesAdded++;

        for (auto [to, wt] : graph[v]) {
            if (!inMST[to]) pq.push({wt, to});
        }
    }

    if (nodesAdded != n) {
        cout << "IMPOSSIBLE\n";
    } else {
        cout << totalCost << "\n";
    }
}



*/