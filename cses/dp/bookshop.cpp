#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, x;
    cin >> n >> x;
    vector<int> price(n), pages(n);
    for (int i = 0; i < n; i++) cin >> price[i];
    for (int i = 0; i < n; i++) cin >> pages[i];

    vector<int> dp(x + 1, 0);

    for (int i = 0; i < n; i++) {
        int p = price[i], v = pages[i];
        for (int c = x; c >= p; c--) {
            dp[c] = max(dp[c], dp[c - p] + v);
        }
    }

    cout << dp[x] << "\n";
}
