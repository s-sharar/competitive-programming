#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> adj;
vector<int> parent;
vector<int> state;
int cycleStart = -1;
int cycleEnd = -1;

bool dfs(int i) {
    state[i] = 1;
    for (int nei : adj[i]) {
        if (state[nei] == 0) {
            parent[nei] = i;
            if (dfs(nei)) return true;
        } else if (state[nei] == 1) {
            cycleStart = nei;
            cycleEnd = i;
            return true;
        }
    }
    state[i] = 2;
    return false;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    adj.resize(n);
    parent.resize(n, -1);
    state.resize(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        adj[a].push_back(b);
    }

    for (int i = 0; i < n; i++) {
        if (state[i] == 0) {
            if (dfs(i)) break;
        }
    }

    if (cycleStart == -1) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }
    vector<int> cycle;
    cycle.push_back(cycleStart);
    for (int v = cycleEnd; v != cycleStart; v = parent[v]) {
        cycle.push_back(v);
    }
    cycle.push_back(cycleStart);
    reverse(cycle.begin(), cycle.end());
    cout << cycle.size() << "\n";
    for (int i = 0; i < (int)cycle.size(); i++) {
        cout << cycle[i] + 1 << (i + 1 == (int)cycle.size() ? '\n' : ' ');
    } 
}