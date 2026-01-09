#include <bits/stdc++.h>

using namespace std;

class DSU {
    vector<int> parent, size;
    int components;
    int maxSize;
    public:
    DSU(int n) {
        parent.resize(n);
        size.resize(n);
        components = n;
        maxSize = 1;
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

    void unionSet(int x, int y) {
        int xRoot = find(x), yRoot = find(y);
        if (xRoot == yRoot) return;
        if (size[xRoot] < size[yRoot]) swap(xRoot, yRoot);
        parent[yRoot] = xRoot;
        size[xRoot] += size[yRoot];
        --components;
        maxSize = max(maxSize, size[xRoot]);
    }
    int getComponents() const {
        return components;
    }
    int getMaxSize() const {
        return maxSize;
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
        --a; --b;
        dsu.unionSet(a, b);
        cout << dsu.getComponents() << " " << dsu.getMaxSize() << endl;
    }
}