#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> a(n);
    long long S = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        S += a[i];
    }

    vector<vector<long long>> dp(n, vector<long long>(n, 0));

    for (int i = 0; i < n; i++) dp[i][i] = a[i];

    for (int len = 2; len <= n; len++) {
        for (int l = 0; l + len - 1 < n; l++) {
            int r = l + len - 1;
            dp[l][r] = max(a[l] - dp[l + 1][r],
                           a[r] - dp[l][r - 1]);
        }
    }

    long long D = dp[0][n - 1];
    cout << (S + D) / 2 << "\n";
}
