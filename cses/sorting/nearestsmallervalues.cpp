#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<ll> input(n);
    for (int i = 0; i < n; ++i) {
        cin >> input[i];
    }

    stack<pair<ll, int>> st;
    vector<int> res(n);
    for (int i = n - 1; i >= 0; --i) {
        while(!st.empty() && st.top().first > input[i]) {
            const auto [val, idx] = st.top();
            st.pop();
            res[idx] = i + 1;
        }
        st.push({input[i], i});
    }
    while (!st.empty()) {
        const auto [val, idx] = st.top();
        st.pop();
        res[idx] = 0;
    }
    for (int i = 0; i < n; ++i) {
        char whitespace = (i == n - 1) ? '\n' : ' ';
        cout << res[i] << whitespace;
    }
}
