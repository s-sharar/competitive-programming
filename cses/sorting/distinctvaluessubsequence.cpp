#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1e9 + 7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    unordered_map<int, int> freq;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        freq[x]++;
    }

    long long ans = 1;
    for (auto [_, f] : freq) {
        ans = ans * (f + 1) % MOD;
    }
    cout << (ans - 1 + MOD) % MOD << "\n";
}