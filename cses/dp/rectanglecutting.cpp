#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, b;
    cin >> a >> b;

    const int INF = 1e9;
    vector<vector<int>> dp(a + 1, vector<int>(b + 1, INF));

    for (int w = 1; w <= a; w++) {
        for (int h = 1; h <= b; h++) {
            if (w == h) {
                dp[w][h] = 0;
                continue;
            }
            // vertical cuts
            for (int k = 1; k < w; k++) {
                dp[w][h] = min(dp[w][h], dp[k][h] + dp[w - k][h] + 1);
            }
            // horizontal cuts
            for (int k = 1; k < h; k++) {
                dp[w][h] = min(dp[w][h], dp[w][k] + dp[w][h - k] + 1);
            }
        }
    }

    cout << dp[a][b] << "\n";
}
