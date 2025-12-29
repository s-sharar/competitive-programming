#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    long long k;
    cin >> n >> m >> k;

    vector<long long> a(n), b(m);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < m; i++) cin >> b[i];

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    int matches = 0;
    int j = m - 1;

    for (int i = n - 1; i >= 0 && j >= 0; --i) {
        long long lo = b[j] - k;
        long long hi = b[j] + k;

        if (lo <= a[i] && a[i] <= hi) {
            matches++;
            j--;
        } else if (a[i] < lo) {
            j--;   // apartment too big for this applicant -> try smaller apartment
            i++;   // cancel the for-loop's --i so we keep same applicant
        }
        // else (a[i] > hi): applicant wants too big -> drop applicant (i-- via loop)
    }

    cout << matches << "\n";
}
