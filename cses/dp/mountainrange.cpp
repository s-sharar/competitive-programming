#include <bits/stdc++.h>
using namespace std;

struct SegTreeMax {
    int n;
    vector<int> seg;
    SegTreeMax(int n_) : n(n_), seg(2*n, 0) {}
    void update(int p, int val) { // point set/max
        p += n;
        seg[p] = max(seg[p], val);
        for (p >>= 1; p; p >>= 1) seg[p] = max(seg[p<<1], seg[p<<1|1]);
    }
    int query(int l, int r) { // inclusive range max
        if (l > r) return 0;
        l += n; r += n;
        int res = 0;
        while (l <= r) {
            if (l & 1) res = max(res, seg[l++]);
            if (!(r & 1)) res = max(res, seg[r--]);
            l >>= 1; r >>= 1;
        }
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> h(n);
    for (int i = 0; i < n; i++) cin >> h[i];

    // Nearest greater on left (strict >)
    vector<int> L(n, -1), R(n, n);
    vector<int> st;
    st.reserve(n);
    for (int i = 0; i < n; i++) {
        while (!st.empty() && h[st.back()] <= h[i]) st.pop_back();
        L[i] = st.empty() ? -1 : st.back();
        st.push_back(i);
    }

    // Nearest greater on right (strict >)
    st.clear();
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && h[st.back()] <= h[i]) st.pop_back();
        R[i] = st.empty() ? n : st.back();
        st.push_back(i);
    }

    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](int a, int b) {
        if (h[a] != h[b]) return h[a] < h[b];
        return a < b;
    });

    SegTreeMax seg(n);
    vector<int> dp(n, 1);
    int ans = 1;

    for (int p = 0; p < n; ) {
        int q = p;
        while (q < n && h[idx[q]] == h[idx[p]]) q++; // group equal heights

        // compute dp for this height group (don’t update seg yet)
        for (int k = p; k < q; k++) {
            int i = idx[k];
            int best = seg.query(L[i] + 1, R[i] - 1);
            dp[i] = 1 + best;
            ans = max(ans, dp[i]);
        }

        // now update seg with this group's dp
        for (int k = p; k < q; k++) {
            int i = idx[k];
            seg.update(i, dp[i]);
        }

        p = q;
    }

    cout << ans << "\n";
    return 0;
}
