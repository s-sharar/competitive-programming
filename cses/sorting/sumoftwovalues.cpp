#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, target;
    cin >> n >> target;
    vector<pair<int, int>> input;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        input.push_back({x, i + 1});
    }

    sort(input.begin(), input.end());
    bool found = false;
    int l = 0, r = n - 1;
    while (l < r) {
        if (input[l].first + input[r].first > target) {
            --r;
        } else if (input[l].first + input[r].first < target) {
            ++l;
        } else {
            cout << input[l].second << " " << input[r].second << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "IMPOSSIBLE" << endl;
    }

}
