#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    ll x;
    cin >> n >> x;

    unordered_map<ll, ll> cnt;

    ll pref = 0, ans = 0;
    cnt[0] = 1;

    for (int i = 0; i < n; i++) {
        ll a;
        cin >> a;
        pref += a;
        auto it = cnt.find(pref - x);
        if (it != cnt.end()) ans += it->second;
        cnt[pref]++;
    }

    cout << ans << "\n";
}
