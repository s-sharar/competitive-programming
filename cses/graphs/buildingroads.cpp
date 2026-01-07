#include <bits/stdc++.h>
using namespace std;

class DSU {
    vector<int> parent, size;
    public:
    DSU(int n) {
        parent.resize(n);
        size.resize(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            size[i] = 1;
        }
    }
    int find(int x) {
        if (parent[x] == x) return x;
        parent[x] = find(parent[x]);
        return parent[x];
    }
    bool unionSets(int x, int y) {
        int xRoot = find(x);
        int yRoot = find(y);
        if (xRoot == yRoot) return false;
        if (size[xRoot] < size[yRoot]) {
            swap(xRoot, yRoot);
        }
        parent[yRoot] = xRoot;
        size[xRoot] += size[yRoot];
        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    DSU dsu(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        dsu.unionSets(a, b);
    }

    vector<int> reps;
    reps.reserve(n);
    for (int i = 0; i < n; i++) {
        if (dsu.find(i) == i) reps.push_back(i);
    }

    cout << (int)reps.size() - 1 << "\n";
    for (int i = 1; i < (int)reps.size(); i++) {
        cout << reps[0] + 1 << " " << reps[i] + 1 << "\n";
    }
}
