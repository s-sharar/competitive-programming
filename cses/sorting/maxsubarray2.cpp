#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, a, b;
    cin >> n >> a >> b;

    vector<long long> prefix(n + 1, 0);

    for (int i = 1; i <= n; i++) {
        long long x;
        cin >> x;
        prefix[i] = prefix[i - 1] + x;
    }

    multiset<long long> window;
    long long answer = LLONG_MIN;

    for (int r = a; r <= n; r++) {
        // prefix[r - a] becomes a valid starting prefix
        window.insert(prefix[r - a]);

        // prefix[r - b - 1] is now too far behind
        if (r - b - 1 >= 0) {
            window.erase(window.find(prefix[r - b - 1]));
        }

        answer = max(answer, prefix[r] - *window.begin());
    }

    cout << answer << '\n';
}
