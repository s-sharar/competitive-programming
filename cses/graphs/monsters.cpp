#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};
map<pair<int, int>, char> directionMap = {
    {{1, 0}, 'D'},
    {{-1, 0}, 'U'},
    {{0, -1}, 'L'},
    {{0, 1}, 'R'}
};

bool isOnEdge(int row, int col, int n, int m) {
    return row == 0 || row == n - 1 || col == 0 || col == m - 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<char>> grid(n, vector<char>(m));
    queue<pair<int, int>> myQ, monsterQ;

    pair<int,int> start = {-1,-1};

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> grid[i][j];
            if (grid[i][j] == 'A') {
                myQ.push({i, j});
                start = {i, j};
                grid[i][j] = '.';
            }
            if (grid[i][j] == 'M') monsterQ.push({i, j});
        }
    }

    vector<vector<pair<int, int>>> parent(n, vector<pair<int, int>>(m, {-1, -1}));
    vector<vector<bool>> myVisited(n, vector<bool>(m, false));
    if (start.first != -1) myVisited[start.first][start.second] = true;

    pair<int, int> found = {-1, -1};
    if (isOnEdge(myQ.front().first, myQ.front().second, n, m)) {
        cout << "YES\n";
        cout << 0 << "\n";
        cout << "\n";
        return 0;
    }

    while (true) {
        int mosterQLen = (int)monsterQ.size();
        for (int k = 0; k < mosterQLen; ++k) {
            auto [r, c] = monsterQ.front();   // renamed to avoid shadowing i/j
            monsterQ.pop();
            for (auto [dr, dc] : directions) {
                int newI = r + dr;
                int newJ = c + dc;
                if (newI >= 0 && newI < n && newJ >= 0 && newJ < m &&
                    grid[newI][newJ] != '#' && grid[newI][newJ] != 'M') {
                    monsterQ.push({newI, newJ});
                    grid[newI][newJ] = 'M';
                }
            }
        }

        int myQLen = (int)myQ.size();
        if (myQLen == 0) break;

        for (int k = 0; k < myQLen; ++k) {
            auto [r, c] = myQ.front();         // renamed to avoid shadowing i/j
            myQ.pop();

            if (isOnEdge(r, c, n, m)) {
                found = {r, c};
                break;
            }

            for (auto [dr, dc] : directions) {
                int newI = r + dr;
                int newJ = c + dc;
                if (newI >= 0 && newI < n && newJ >= 0 && newJ < m &&
                    grid[newI][newJ] != '#' && grid[newI][newJ] != 'M' &&
                    !myVisited[newI][newJ]) {

                    myVisited[newI][newJ] = true;
                    myQ.push({newI, newJ});
                    parent[newI][newJ] = {r, c};
                }
            }
        }

        if (found.first != -1) break;
    }

    if (found.first == -1) {
        cout << "NO\n";
        return 0;
    }

    cout << "YES\n";
    string path;
    auto [i, j] = found;
    while (parent[i][j] != make_pair(-1, -1)) {
        auto [prevI, prevJ] = parent[i][j];
        path.push_back(directionMap[{i - prevI, j - prevJ}]);
        i = prevI;
        j = prevJ;
    }
    reverse(path.begin(), path.end());
    cout << path.size() << "\n";
    cout << path << "\n";
    return 0;
}


/*

Better gpt code:

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<string> grid(n);
    for (int i = 0; i < n; i++) cin >> grid[i];

    const int INF = 1e9;
    vector<vector<int>> distM(n, vector<int>(m, INF));
    vector<vector<int>> distA(n, vector<int>(m, INF));
    vector<vector<pair<int,int>>> parent(n, vector<pair<int,int>>(m, {-1,-1}));
    vector<vector<char>> parentMove(n, vector<char>(m, 0));

    vector<pair<int,int>> dirs = {{1,0},{-1,0},{0,1},{0,-1}};
    vector<char> dch = {'D','U','R','L'};

    queue<pair<int,int>> q;
    pair<int,int> start{-1,-1};

    // init monsters and find A
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            if (grid[r][c] == 'M') {
                distM[r][c] = 0;
                q.push({r,c});
            } else if (grid[r][c] == 'A') {
                start = {r,c};
            }
        }
    }

    auto onEdge = [&](int r, int c) {
        return r == 0 || r == n-1 || c == 0 || c == m-1;
    };

    // 1) BFS monsters
    while (!q.empty()) {
        auto [r,c] = q.front(); q.pop();
        for (int k = 0; k < 4; k++) {
            int nr = r + dirs[k].first;
            int nc = c + dirs[k].second;
            if (nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
            if (grid[nr][nc] == '#') continue;
            if (distM[nr][nc] > distM[r][c] + 1) {
                distM[nr][nc] = distM[r][c] + 1;
                q.push({nr,nc});
            }
        }
    }

    // if A starts on edge, immediate escape (no monster can be on A at t=0)
    if (onEdge(start.first, start.second)) {
        cout << "YES\n0\n\n";
        return 0;
    }

    // 2) BFS A with safety constraint
    queue<pair<int,int>> aq;
    aq.push(start);
    distA[start.first][start.second] = 0;

    pair<int,int> exitCell{-1,-1};

    while (!aq.empty()) {
        auto [r,c] = aq.front(); aq.pop();
        int t = distA[r][c];

        for (int k = 0; k < 4; k++) {
            int nr = r + dirs[k].first;
            int nc = c + dirs[k].second;
            if (nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
            if (grid[nr][nc] == '#') continue;

            // must arrive strictly before any monster
            if (t + 1 >= distM[nr][nc]) continue;

            if (distA[nr][nc] == INF) {
                distA[nr][nc] = t + 1;
                parent[nr][nc] = {r,c};
                parentMove[nr][nc] = dch[k];
                aq.push({nr,nc});

                if (onEdge(nr,nc)) {
                    exitCell = {nr,nc};
                    while (!aq.empty()) aq.pop();
                    break;
                }
            }
        }
    }

    if (exitCell.first == -1) {
        cout << "NO\n";
        return 0;
    }

    // reconstruct path
    string path;
    int r = exitCell.first, c = exitCell.second;
    while (parent[r][c].first != -1) {
        path.push_back(parentMove[r][c]);
        auto [pr, pc] = parent[r][c];
        r = pr; c = pc;
    }
    reverse(path.begin(), path.end());

    cout << "YES\n" << path.size() << "\n" << path << "\n";
    return 0;
}






*/
