#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<char>> grid(n, vector<char>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> grid[i][j];

    vector<vector<int>> dp(n, vector<int>(n, 0));
    dp[0][0] = (grid[0][0] == '.' ? 1 : 0);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == '*') {
                dp[i][j] = 0;
                continue;
            }
            if (i == 0 && j == 0) continue;

            long long ways = 0;
            if (i > 0) ways += dp[i - 1][j];
            if (j > 0) ways += dp[i][j - 1];
            dp[i][j] = ways % MOD;
        }
    }

    cout << dp[n - 1][n - 1] << "\n";
}
