#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, target;
    cin >> n >> target;

    unordered_map<int, int> seen;  // value -> 0-based index
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;

        int need = target - x;
        if (seen.count(need)) {
            cout << seen[need] + 1 << " " << i + 1 << "\n";
            return 0;
        }
        seen[x] = i;
    }
    cout << "IMPOSSIBLE\n";
}
