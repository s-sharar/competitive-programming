#include <bits/stdc++.h>
using namespace std;

struct Project {
    long long s, e, p;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Project> a(n);
    for (int i = 0; i < n; i++) cin >> a[i].s >> a[i].e >> a[i].p;

    sort(a.begin(), a.end(), [](const Project& x, const Project& y) {
        return x.e < y.e;
    });

    vector<long long> ends(n);
    for (int i = 0; i < n; i++) ends[i] = a[i].e;

    vector<long long> dp(n + 1, 0); // dp[0]=0, dp[i]=best using first i projects

    for (int i = 1; i <= n; i++) {
        long long s = a[i - 1].s;
        long long p = a[i - 1].p;

        // j = number of projects with end < s
        int j = upper_bound(ends.begin(), ends.end(), s - 1) - ends.begin();

        dp[i] = max(dp[i - 1], p + dp[j]);
    }

    cout << dp[n] << "\n";
}
