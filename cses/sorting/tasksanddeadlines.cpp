#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<pair<long long, long long>> tasks(n);  // {duration, deadline}
    for (int i = 0; i < n; i++) {
        cin >> tasks[i].first >> tasks[i].second;
    }

    // Shortest job first: minimize sum of finishing times
    sort(tasks.begin(), tasks.end());

    long long t = 0, ans = 0;
    for (auto [a, d] : tasks) {
        t += a;
        ans += d - t;
    }

    cout << ans << "\n";
}
