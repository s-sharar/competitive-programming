#include <bits/stdc++.h>
using namespace std;

using State = tuple<long long, int, int>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> adj(n);
    for (int i = 0; i < m; i++) {
        int a, b, len;
        cin >> a >> b >> len;
        --a; --b;
        adj[a].push_back({b, len});
    }


    vector<array<long long, 2>> minCost(n, {LLONG_MAX, LLONG_MAX});
    vector<array<bool, 2>> visited(n, {false, false});
    minCost[0][0] = 0;
    priority_queue<State, vector<State>, greater<>> pq;
    pq.push({0LL, 0, 0});
    while (!pq.empty()) {
        auto [cost, node, used] = pq.top();
        pq.pop();
        if (visited[node][used]) continue;
        minCost[node][used] = cost;
        visited[node][used] = true;
        for (auto [nei, costToMove] : adj[node]) {
            pq.push({cost + costToMove, nei, used});
            if (used == 0) {
                pq.push({cost + (costToMove / 2), nei, 1});
            }
        }
    }

    cout << minCost[n - 1][1] << endl;
}

/*
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> adj(n);
    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        --a; --b;
        adj[a].push_back({b, w});
    }

    const long long INF = (long long)4e18;
    vector<array<long long, 2>> dist(n, {INF, INF});
    dist[0][0] = 0;

    // (cost, node, usedDiscount)
    using State = tuple<long long, int, int>;
    priority_queue<State, vector<State>, greater<State>> pq;
    pq.push({0LL, 0, 0});

    while (!pq.empty()) {
        auto [cost, node, used] = pq.top();
        pq.pop();

        if (cost != dist[node][used]) continue;

        for (auto [nxt, w] : adj[node]) {
            // move without discount
            if (cost + w < dist[nxt][used]) {
                dist[nxt][used] = cost + w;
                pq.push({dist[nxt][used], nxt, used});
            }

            // use discount on this edge (only if not used yet)
            if (used == 0) {
                long long discounted = cost + (w / 2LL); // CSES uses floor
                if (discounted < dist[nxt][1]) {
                    dist[nxt][1] = discounted;
                    pq.push({dist[nxt][1], nxt, 1});
                }
            }
        }
    }

    cout << dist[n - 1][1] << "\n";
    return 0;
}



*/