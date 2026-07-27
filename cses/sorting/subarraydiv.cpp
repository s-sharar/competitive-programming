#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<long long> cnt(n, 0);
    cnt[0] = 1;

    long long pref = 0, ans = 0;
    for (int i = 0; i < n; i++) {
        long long a;
        cin >> a;
        pref += a;

        long long r = pref % n;
        if (r < 0) r += n;

        ans += cnt[r];
        cnt[r]++;
    }

    cout << ans << "\n";
}
