#include <bits/stdc++.h>
using namespace std;

static const int MOD = 1e9 + 7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    // rev[v] = all u such that u -> v
    vector<vector<int>> rev(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        rev[b].push_back(a);
    }

    int ALL = (1 << n) - 1;

    // dp[mask][v] = ways to start at 0, visit exactly "mask", end at v
    vector<vector<int>> dp(1 << n, vector<int>(n, 0));
    dp[1 << 0][0] = 1;

    for (int mask = 0; mask <= ALL; mask++) {
        if (!(mask & (1 << 0))) continue; // must include start

        // don't allow visiting end node early
        if ((mask & (1 << (n - 1))) && mask != ALL) continue;

        for (int v = 0; v < n; v++) {
            if (!(mask & (1 << v))) continue;

            int prevMask = mask ^ (1 << v); // remove v

            if (v == 0) {
                // only valid start state is mask == {0}
                continue;
            }

            long long ways = 0;
            for (int u : rev[v]) {
                if (prevMask & (1 << u)) {
                    ways += dp[prevMask][u];
                }
            }
            dp[mask][v] = (dp[mask][v] + (int)(ways % MOD)) % MOD;
        }
    }

    cout << dp[ALL][n - 1] << "\n";
    return 0;
}
