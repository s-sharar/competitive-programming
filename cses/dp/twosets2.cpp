#include <bits/stdc++.h>
using namespace std;

static const int MOD = 1e9 + 7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    long long T = 1LL * n * (n + 1) / 2;
    if (T % 2) {
        cout << 0 << "\n";
        return 0;
    }

    int S = (int)(T / 2);
    vector<int> dp(S + 1, 0);
    dp[0] = 1;

    for (int x = 1; x <= n; x++) {
        for (int s = S; s >= x; --s) {
            dp[s] += dp[s - x];
            if (dp[s] >= MOD) dp[s] -= MOD;
        }
    }

    long long inv2 = 500000004LL;
    cout << (dp[S] * inv2) % MOD << "\n";
    return 0;
}
