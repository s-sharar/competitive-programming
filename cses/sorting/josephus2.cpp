#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template<class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,
                         tree_order_statistics_node_update>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long k;
    cin >> n >> k;

    ordered_set<int> s;
    for (int i = 1; i <= n; i++) s.insert(i);

    int idx = 0;
    while (!s.empty()) {
        idx = (idx + k) % s.size();
        auto it = s.find_by_order(idx);  // 0-based k-th
        cout << *it << " ";
        s.erase(it);
        // idx stays put: next living kid slides into this slot
    }
}
