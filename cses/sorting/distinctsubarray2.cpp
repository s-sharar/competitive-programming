#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    long long ret = 0;
    int l = 0;
    unordered_map<int, int> freq;

    for (int r = 0; r < n; r++) {
        freq[a[r]]++;
        while ((int)freq.size() > k) {
            if (--freq[a[l]] == 0) freq.erase(a[l]);
            l++;
        }
        ret += r - l + 1;
    }

    cout << ret << "\n";
}
