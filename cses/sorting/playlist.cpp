#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<ll> ids(n);
    for (int i = 0; i < n; ++i) {
        cin >> ids[i];
    }
    unordered_map<ll, int> mp;
    int maxCount = 0;
    int l = 0;
    for (int r = 0; r < n; ++r) {
        mp[ids[r]]++;
        while (mp[ids[r]] > 1) {
            mp[ids[l]]--;
            ++l;
        }
        maxCount = max(maxCount, r - l + 1);
    }
    cout << maxCount << "\n";
}
 