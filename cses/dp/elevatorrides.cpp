#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long x;
    cin >> n >> x;

    vector<long long> w(n);
    for (int i = 0; i < n; i++) cin >> w[i];

    int N = 1 << n;
    // dp[mask] = {rides, lastWeight}
    vector<pair<int, long long>> dp(N, {INT_MAX, LLONG_MAX});
    dp[0] = {1, 0};

    for (int mask = 1; mask < N; mask++) {
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                auto prev = dp[mask ^ (1 << i)];
                pair<int, long long> cand;

                if (prev.second + w[i] <= x) {
                    cand = {prev.first, prev.second + w[i]};
                } else {
                    cand = {prev.first + 1, w[i]};
                }

                dp[mask] = min(dp[mask], cand); // lexicographic compare
            }
        }
    }

    cout << dp[N - 1].first << "\n";
    return 0;
}
