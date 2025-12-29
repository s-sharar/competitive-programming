#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        long long a, b;
        cin >> a >> b;
        long long mn = min(a, b), mx = max(a, b);

        if ((a + b) % 3 == 0 && mx <= 2 * mn) cout << "YES\n";
        else cout << "NO\n";
    }
}
