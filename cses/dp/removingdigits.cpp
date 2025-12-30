#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    const int INF = 1e9;
    vector<int> dp(n + 1, INF);
    dp[0] = 0;

    for (int i = 1; i <= n; i++) {
        int x = i;
        while (x > 0) {
            int d = x % 10;
            x /= 10;
            if (d == 0) continue;
            dp[i] = min(dp[i], dp[i - d] + 1);
        }
    }

    cout << dp[n] << "\n";
    return 0;
}
