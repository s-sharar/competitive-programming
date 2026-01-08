#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

// push on improvement only
// dont put path properties in priority queue state


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> adj(n);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        --a; --b;
        adj[a].push_back({b, c});
    }

    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
    vector<long long> minDist(n, LLONG_MAX);
    vector<int> minFlights(n, INT_MAX);
    vector<int> maxFlights(n, INT_MIN);
    vector<int> numFlights(n, 0);
    minDist[0] = 0;
    minFlights[0] = 0;
    maxFlights[0] = 0;
    numFlights[0] = 1;
    pq.push({0, 0});
    while (!pq.empty()) {
        auto [cost, node] = pq.top();
        pq.pop();
        if (cost != minDist[node]) continue;
        for (auto [nei, costToMove] : adj[node]) {
            if (cost + costToMove < minDist[nei]) {
                minDist[nei] = cost + costToMove;
                minFlights[nei] = minFlights[node] + 1;
                maxFlights[nei] = maxFlights[node] + 1;
                numFlights[nei] = numFlights[node];
                pq.push({minDist[nei], nei});
            } else if (cost + costToMove == minDist[nei]) {
                minFlights[nei] = min(minFlights[nei], minFlights[node] + 1);
                maxFlights[nei] = max(maxFlights[nei], maxFlights[node] + 1);
                numFlights[nei] = (numFlights[nei] + numFlights[node]) % MOD;
            }
        }
    }
    cout << minDist[n - 1] << " " << numFlights[n - 1] << " " << minFlights[n - 1] << " " << maxFlights[n - 1] << endl;
}
