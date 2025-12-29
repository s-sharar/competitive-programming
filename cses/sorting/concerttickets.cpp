#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    multiset<int> tickets;
    for (int i = 0; i < n; i++) {
        int p; cin >> p;
        tickets.insert(p);
    }

    for (int i = 0; i < m; i++) {
        int x; cin >> x;
        auto it = tickets.upper_bound(x); // first > x
        if (it == tickets.begin()) {
            cout << -1 << "\n";
        } else {
            --it;               // now <= x
            cout << *it << "\n";
            tickets.erase(it);  // remove that ticket
        }
    }
}
