#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<pair<int,int>> events;
    events.reserve(2*n);

    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        events.push_back({a, +1});
        events.push_back({b, -1});
    }

    sort(events.begin(), events.end()); // sort by time

    int cur = 0, best = 0;
    for (auto [t, delta] : events) {
        cur += delta;
        best = max(best, cur);
    }

    cout << best << "\n";
}
 