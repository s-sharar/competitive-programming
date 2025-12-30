#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};

void dfs(vector<vector<char>> &grid, int r, int c, int n, int m) {
    if (r < 0 || r >= n || c < 0 || c >= m || grid[r][c] == '#') return;
    grid[r][c] = '#';
    for (auto [dr, dc] : directions) {
        dfs(grid, r + dr, c + dc, n, m);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<char>> grid(n, vector<char>(m));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> grid[i][j];
        }
    }

    int rooms = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == '.') {
                dfs(grid, i, j, n, m);
                ++rooms;
            }
        }
    }

    cout << rooms << "\n";
    return 0;
}
