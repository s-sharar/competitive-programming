#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    sort(s.begin(), s.end());

    int n = (int)s.size();
    vector<int> used(n, 0);
    string cur;
    cur.reserve(n);
    vector<string> out;

    function<void()> dfs = [&]() {
        if ((int)cur.size() == n) {
            out.push_back(cur);
            return;
        }
        for (int i = 0; i < n; i++) {
            if (used[i]) continue;
            if (i > 0 && s[i] == s[i-1] && !used[i-1]) continue; // key line
            used[i] = 1;
            cur.push_back(s[i]);
            dfs();
            cur.pop_back();
            used[i] = 0;
        }
    };

    dfs();

    cout << out.size() << "\n";
    for (auto &p : out) cout << p << "\n";
}
