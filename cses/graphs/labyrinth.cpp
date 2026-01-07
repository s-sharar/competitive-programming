#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<string> grid(n);
    pair<int,int> start{-1,-1}, target{-1,-1};

    for (int r = 0; r < n; r++) {
        cin >> grid[r];
        for (int c = 0; c < m; c++) {
            if (grid[r][c] == 'A') start = {r, c};
            if (grid[r][c] == 'B') target = {r, c};
        }
    }

    // Directions: D, U, R, L (any order is fine)
    const int dr[4] = {1, -1, 0, 0};
    const int dc[4] = {0, 0, 1, -1};
    const char moveChar[4] = {'D', 'U', 'R', 'L'};

    vector<vector<bool>> visited(n, vector<bool>(m, false));
    vector<vector<pair<int,int>>> parent(n, vector<pair<int,int>>(m, {-1, -1}));
    vector<vector<char>> moveTaken(n, vector<char>(m, 0));

    queue<pair<int,int>> q;
    visited[start.first][start.second] = true;
    q.push(start);

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();

        if (make_pair(r, c) == target) break;

        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k], nc = c + dc[k];
            if (nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
            if (grid[nr][nc] == '#') continue;
            if (visited[nr][nc]) continue;

            visited[nr][nc] = true;
            parent[nr][nc] = {r, c};
            moveTaken[nr][nc] = moveChar[k];
            q.push({nr, nc});
        }
    }

    if (!visited[target.first][target.second]) {
        cout << "NO\n";
        return 0;
    }

    // Reconstruct path from B -> A
    string path;
    for (auto cur = target; cur != start; cur = parent[cur.first][cur.second]) {
        path.push_back(moveTaken[cur.first][cur.second]);
    }
    reverse(path.begin(), path.end());

    cout << "YES\n";
    cout << path.size() << "\n";
    cout << path << "\n";
    return 0;
}
