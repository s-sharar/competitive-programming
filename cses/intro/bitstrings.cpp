#include <bits/stdc++.h>
using namespace std;

static const long long MOD = 1000000007LL;

long long modpow(long long a, long long e) {
    long long res = 1 % MOD;
    a %= MOD;
    while (e > 0) {
        if (e & 1LL) res = (res * a) % MOD;
        a = (a * a) % MOD;
        e >>= 1LL;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n;
    cin >> n;
    cout << modpow(2, n) << "\n";
    return 0;
}
