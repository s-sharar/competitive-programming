#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    sort(a.begin(), a.end());  // <-- required

    long long reach = 0;
    for (long long x : a) {
        if (x > reach + 1) break;
        reach += x;
    }

    cout << reach + 1 << "\n";
}
