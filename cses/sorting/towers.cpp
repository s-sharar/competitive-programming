#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    multiset<int> tops; // current top block of each tower

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;

        auto it = tops.upper_bound(x); // first top > x
        if (it == tops.end()) {
            // no tower can take x -> start new tower
            tops.insert(x);
        } else {
            // put x on this tower: replace its top
            tops.erase(it);
            tops.insert(x);
        }
    }

    cout << tops.size() << "\n";
    return 0;
}
