#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int x, n;
    cin >> x >> n;

    set<int> lights;
    multiset<int> gaps;
    lights.insert(0);
    lights.insert(x);
    gaps.insert(x);

    int input;
    for (int i = 0; i < n; ++i) {
        cin >> input;
        auto it = lights.upper_bound(input);
        auto prevIt = prev(it);
        gaps.erase(gaps.find(*it - *prevIt));
        gaps.insert(*it - input);
        gaps.insert(input - *prevIt);
        lights.insert(input);
        cout << *gaps.rbegin() << (i + 1 == n ? '\n' : ' ');
    }
}
