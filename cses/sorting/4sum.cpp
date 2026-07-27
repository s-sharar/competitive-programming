#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long x;
    cin >> n >> x;

    vector<long long> a(n);
    for (auto& value : a) cin >> value;

    // pair sum -> indices producing that sum
    unordered_map<long long, pair<int, int>> seen;

    for (int j = 0; j < n; ++j) {
        // Try using j and k as the final two indices.
        // All pairs currently in seen end before j.
        for (int k = j + 1; k < n; ++k) {
            long long needed = x - a[j] - a[k];

            if (seen.count(needed)) {
                auto [i, p] = seen[needed];

                cout << i + 1 << ' '
                     << p + 1 << ' '
                     << j + 1 << ' '
                     << k + 1 << '\n';
                return 0;
            }
        }

        // Add pairs ending at j only after checking.
        for (int i = 0; i < j; ++i) {
            seen[a[i] + a[j]] = {i, j};
        }
    }

    cout << "IMPOSSIBLE\n";
}
