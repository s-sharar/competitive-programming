#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<char>> grid(n, vector<char>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }

    // n == 1 edge case
    if (n == 1) {
        cout << grid[0][0] << "\n";
        return 0;
    }

    string ans;
    ans.reserve(2 * n - 1);
    ans.push_back(grid[0][0]);

    vector<pair<int,int>> cur;
    cur.push_back({0, 0});

    // visited marker per step to avoid duplicates in nxt
    vector<vector<int>> seen(n, vector<int>(n, 0));
    int stamp = 0;

    for (int step = 1; step <= 2 * n - 2; step++) {
        char best = '{'; // after 'z' in ASCII; acts as infinity

        // 1) find smallest next character reachable from cur
        for (auto [i, j] : cur) {
            if (i + 1 < n) best = min(best, grid[i + 1][j]);
            if (j + 1 < n) best = min(best, grid[i][j + 1]);
        }

        // 2) collect all next cells that have that smallest character
        vector<pair<int,int>> nxt;
        stamp++;
        for (auto [i, j] : cur) {
            if (i + 1 < n && grid[i + 1][j] == best && seen[i + 1][j] != stamp) {
                seen[i + 1][j] = stamp;
                nxt.push_back({i + 1, j});
            }
            if (j + 1 < n && grid[i][j + 1] == best && seen[i][j + 1] != stamp) {
                seen[i][j + 1] = stamp;
                nxt.push_back({i, j + 1});
            }
        }

        ans.push_back(best);
        cur.swap(nxt);
    }

    cout << ans << "\n";
    return 0;
}
