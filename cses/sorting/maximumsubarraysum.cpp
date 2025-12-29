#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    long long best = LLONG_MIN;
    long long cur = 0;

    for (int i = 0; i < n; i++) {
        long long x;
        cin >> x;
        cur = max(x, cur + x);   // best subarray ending here
        best = max(best, cur);   // best overall
    }

    cout << best << "\n";
}
