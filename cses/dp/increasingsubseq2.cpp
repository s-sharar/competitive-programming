#include <bits/stdc++.h>


using namespace std;

int MOD = 1e9 + 7;

typedef long long ll;

class FenwickTree {
    vector<ll> bits;
public:
    FenwickTree(int n) : bits(n + 1, 0);
    void add(int i, ll w) {
        for (; i <= n; i += i & -i) bits[i] = (bits[i] + w) % MOD;
    }
    ll query(int i) {
        ll sum = 0;
        for (; i > 0; i -= i & -i) sum += bits[i];
        return sum;
    }
};

int main() {

    int n;
    cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    vector<ll> u = a;
    sort(u.begin(), u.end());
    u.erase(unique(u.begin(), u.end()), u.end());

    FenwickTree t(u.size());
    int ret = 0;
    for (ll x : a) {
        int rank = lower_bound(u.begin(), u.end(), x) - u.begin() + 1;
        ll ways = (t.query(rank - 1) + 1) % MOD;
        ret = (ret + ways) % MOD;
        t.add(rank, ways);
    }
    cout << ret << "\n";
    return 0;
}