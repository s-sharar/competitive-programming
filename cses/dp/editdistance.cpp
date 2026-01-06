#include <bits/stdc++.h>
using namespace std;

// Returns Levenshtein edit distance between a and b.
int editDistance(const string& a, const string& b) {
    int n = (int)a.size();
    int m = (int)b.size();

    // prev[j] = dp[i-1][j], curr[j] = dp[i][j]
    vector<int> prev(m + 1), curr(m + 1);

    // dp[0][j] = j (insert all j chars)
    for (int j = 0; j <= m; j++) prev[j] = j;

    for (int i = 1; i <= n; i++) {
        // dp[i][0] = i (delete all i chars)
        curr[0] = i;

        for (int j = 1; j <= m; j++) {
            if (a[i - 1] == b[j - 1]) {
                curr[j] = prev[j - 1];  // characters match, no new edit
            } else {
                int costDelete  = prev[j] + 1;     // delete a[i-1]
                int costInsert  = curr[j - 1] + 1; // insert b[j-1]
                int costReplace = prev[j - 1] + 1; // replace a[i-1] -> b[j-1]
                curr[j] = min({costDelete, costInsert, costReplace});
            }
        }

        prev.swap(curr);
    }

    return prev[m];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string a, b;
    cin >> a >> b;
    cout << editDistance(a, b) << "\n";
    return 0;
}
