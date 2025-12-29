#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, amount;
    cin >> n >> amount;

    vector<int> coins(n);
    for (int i = 0; i < n; i++) cin >> coins[i];

    vector<int> dp(amount + 1, 0);
    dp[0] = 1;

    for (int c : coins) {
        for (int s = c; s <= amount; s++) {
            dp[s] += dp[s - c];
            if (dp[s] >= MOD) dp[s] -= MOD;
        }
    }

    cout << dp[amount] << "\n";
}
