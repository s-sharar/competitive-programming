#include <bits/stdc++.h>
using namespace std;

// Fenwick / BIT: prefix sums with point updates, both O(log n)
struct Fenwick {
    int n;
    vector<int> bit;

    Fenwick(int n) : n(n), bit(n + 1, 0) {}

    void add(int i, int v) {           // bit[i] += v  (1-indexed)
        for (; i <= n; i += i & -i) bit[i] += v;
    }

    int sum(int i) {                   // sum of [1..i]
        int s = 0;
        for (; i > 0; i -= i & -i) s += bit[i];
        return s;
    }

    int rangeSum(int l, int r) {       // sum of [l..r]
        if (l > r) return 0;
        return sum(r) - sum(l - 1);
    }
};

struct Range {
    long long l, r;
    int index;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<Range> ranges(n);
    vector<long long> coords;
    for (int i = 0; i < n; i++) {
        cin >> ranges[i].l >> ranges[i].r;
        ranges[i].index = i;
        coords.push_back(ranges[i].r);
    }

    // Compress rights: 1e9 -> [1..n]
    sort(coords.begin(), coords.end());
    coords.erase(unique(coords.begin(), coords.end()), coords.end());
    auto compress = [&](long long x) -> int {
        return (int)(lower_bound(coords.begin(), coords.end(), x) - coords.begin()) + 1;
    };

    // Same sort as Check: L asc, ties R desc (wider first)
    sort(ranges.begin(), ranges.end(), [](const Range& a, const Range& b) {
        if (a.l != b.l) return a.l < b.l;
        return a.r > b.r;
    });

    int m = (int)coords.size();
    vector<int> contains(n), contained(n);

    // How many ranges contain me?  (process left -> right)
    {
        Fenwick fw(m);
        for (int i = 0; i < n; i++) {
            int cr = compress(ranges[i].r);
            // previous have L <= mine; count those with R >= mine
            contained[ranges[i].index] = fw.rangeSum(cr, m);
            fw.add(cr, 1);
        }
    }

    // How many ranges do I contain?  (process right -> left)
    {
        Fenwick fw(m);
        for (int i = n - 1; i >= 0; i--) {
            int cr = compress(ranges[i].r);
            // later have L >= mine; count those with R <= mine
            contains[ranges[i].index] = fw.rangeSum(1, cr);
            fw.add(cr, 1);
        }
    }

    for (int x : contains) cout << x << ' ';
    cout << '\n';
    for (int x : contained) cout << x << ' ';
    cout << '\n';
}
