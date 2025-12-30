#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> values(n);
    for (int i = 0; i < n; ++i) cin >> values[i];
    // dp[i][v] = number of ways to fill positions 0..i such that a[i] = v
    vector<int> prev(m + 2, 0), curr(m + 2, 0);

    if (values[0] == 0) {
        for (int v = 1; v <= m; ++v) prev[v] = 1;
    } else {
        prev[values[0]] = 1;
    }

    for (int i = 1; i < n; ++i) {
        fill(curr.begin(), curr.end(), 0);

        if (values[i] == 0) {
            for (int v = 1; v <= m; ++v) {
                curr[v] = ( (long long)prev[v - 1] + prev[v] + prev[v + 1] ) % MOD;
            }
        } else {
            int v = values[i];
            curr[v] = ( (long long)prev[v - 1] + prev[v] + prev[v + 1] ) % MOD;
        }
        swap(prev, curr);
    }

    long long ans = 0;
    if (values[n - 1] == 0) {
        for (int v = 1; v <= m; ++v) ans = (ans + prev[v]) % MOD;
    } else {
        ans = prev[values[n - 1]];
    }

    cout << ans << "\n";
    return 0;
}
