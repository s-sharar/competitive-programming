#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MOD = 1e9 + 7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, amount;
    cin >> n >> amount;
    vector<ll> coins(n);
    for (int i = 0; i < n; ++i) {
        cin >> coins[i];
    }

    vector<ll> dp(amount + 1, LLONG_MAX);
    dp[0] = 0;
    for (int i = 1; i <= amount; ++i) {
        for (auto elem : coins) {
            if (i - elem >= 0 && dp[i - elem] != LLONG_MAX) {
                dp[i] = min(dp[i], dp[i - elem] + 1);
            }
        }
    }
    cout << (dp[amount] != LLONG_MAX ? dp[amount] : -1) << "\n";

}
