#include <bits/stdc++.h>


using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    int ans = 0;
    unordered_set<int> seen;
    int l = 0;
    for (int r = 0; r < n; r++) {
        while (seen.count(a[r])) {
            seen.erase(a[l]);
            l++;
        }
        seen.insert(a[r]);
        ans += r - l + 1;
    }
    cout << ans << "\n";
    return 0;
}