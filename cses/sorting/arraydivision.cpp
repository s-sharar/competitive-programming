#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<long long> a(n);
    long long low = 0, high = 0;

    for (long long& x : a) {
        cin >> x;
        low = max(low, x);
        high += x;
    }

    while (low < high) {
        long long mid = low + (high - low) / 2;

        int subarrays = 1;
        long long currentSum = 0;

        for (long long x : a) {
            if (currentSum + x > mid) {
                subarrays++;
                currentSum = x;
            } else {
                currentSum += x;
            }
        }

        if (subarrays <= k) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }

    cout << low << '\n';
}
