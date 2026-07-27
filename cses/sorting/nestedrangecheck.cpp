#include <bits/stdc++.h>
using namespace std;

struct Range {
    long long l, r;
    int index;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<Range> ranges(n);

    for (int i = 0; i < n; i++) {
        cin >> ranges[i].l >> ranges[i].r;
        ranges[i].index = i;
    }

    sort(ranges.begin(), ranges.end(), [](const Range& a, const Range& b) {
        if (a.l == b.l)
            return a.r > b.r;

        return a.l < b.l;
    });

    vector<int> contains(n, 0);
    vector<int> contained(n, 0);

    // Is the current range contained in a previous range?
    long long maxRight = LLONG_MIN;

    for (int i = 0; i < n; i++) {
        if (ranges[i].r <= maxRight) {
            contained[ranges[i].index] = 1;
        }

        maxRight = max(maxRight, ranges[i].r);
    }

    // Does the current range contain a later range?
    long long minRight = LLONG_MAX;

    for (int i = n - 1; i >= 0; i--) {
        if (ranges[i].r >= minRight) {
            contains[ranges[i].index] = 1;
        }

        minRight = min(minRight, ranges[i].r);
    }

    for (int x : contains)
        cout << x << ' ';
    cout << '\n';

    for (int x : contained)
        cout << x << ' ';
    cout << '\n';
}
