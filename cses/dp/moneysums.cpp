#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> coins(n);
    for (int i = 0; i < n; i++) cin >> coins[i];

    unordered_set<long long> st;
    vector<long long> res;
    res.push_back(0);
    st.insert(0);

    for (int coin : coins) {
        int size = res.size();
        for (int i = 0; i < size; ++i) {
            long long node = res[i] + coin;
            if (!st.count(node)) {
                st.insert(node);
                res.push_back(node);
            }
        }
    }
    sort(res.begin(), res.end());
    res.erase(res.begin());
    cout << res.size() << "\n";
    for (int i = 0; i < res.size(); ++i) {
        cout << res[i] << (i + 1 == res.size() ? "\n" : " ");
    }
}

/*

better 0 1 knapsack sol

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> coins(n);

    int total = 0;
    for (int i = 0; i < n; i++) {
        cin >> coins[i];
        total += coins[i];
    }

    vector<char> possible(total + 1, 0);
    possible[0] = 1;

    for (int c : coins) {
        for (int s = total; s >= c; --s) {
            if (possible[s - c]) possible[s] = 1;
        }
    }

    vector<int> ans;
    for (int s = 1; s <= total; s++) {
        if (possible[s]) ans.push_back(s);
    }

    cout << ans.size() << "\n";
    for (int i = 0; i < (int)ans.size(); i++) {
        cout << ans[i] << (i + 1 == (int)ans.size() ? "\n" : " ");
    }
}


*/