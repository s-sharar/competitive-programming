#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> p(n);
    for (int i = 0; i < n; i++) cin >> p[i];

    sort(p.begin(), p.end());
    long long median = p[n / 2];

    long long cost = 0;
    for (int i = 0; i < n; i++) cost += llabs(p[i] - median);

    cout << cost << "\n";
}
