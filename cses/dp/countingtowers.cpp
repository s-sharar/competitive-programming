#include <bits/stdc++.h>
using namespace std;

static const int MOD = 1e9 + 7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    vector<int> qs(t);
    int maxN = 0;
    for (int i = 0; i < t; i++) {
        cin >> qs[i];
        maxN = max(maxN, qs[i]);
    }

    vector<int> split(maxN + 1), merged(maxN + 1);
    // dp[1][0]=split, dp[1][1]=merged
    if (maxN >= 1) {
        split[1] = 1;
        merged[1] = 1;
    }

    for (int i = 2; i <= maxN; i++) {
        merged[i] = ( (2LL * merged[i - 1]) + split[i - 1] ) % MOD;
        split[i]  = ( merged[i - 1] + (4LL * split[i - 1]) ) % MOD;
    }

    for (int n : qs) {
        cout << ( (merged[n] + split[n]) % MOD ) << "\n";
    }
    return 0;
}
