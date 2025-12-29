#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> pos(n + 1), val(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> val[i];
        pos[val[i]] = i;
    }

    auto bad = [&](int a, int b) -> int { // a < b
        return pos[a] > pos[b];
    };

    int rounds = 1;
    for (int x = 2; x <= n; x++) rounds += bad(x - 1, x);

    while (m--) {
        int a, b;
        cin >> a >> b;

        int x = val[a], y = val[b];

        // collect affected adjacent pairs (u, u+1)
        vector<int> candidates = {x - 1, x, y - 1, y};
        sort(candidates.begin(), candidates.end());
        candidates.erase(unique(candidates.begin(), candidates.end()), candidates.end());

        // remove old contributions
        for (int u : candidates) {
            if (1 <= u && u < n) rounds -= bad(u, u + 1);
        }

        // do swap in val[] and update pos[]
        swap(val[a], val[b]);
        pos[x] = b;
        pos[y] = a;

        // add new contributions
        for (int u : candidates) {
            if (1 <= u && u < n) rounds += bad(u, u + 1);
        }

        cout << rounds << "\n";
    }
}
