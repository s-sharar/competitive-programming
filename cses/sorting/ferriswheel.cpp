#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, maxWeight;
    cin >> n >> maxWeight;

    vl weights(n);
    for (int i = 0; i < n; ++i) {
        cin >> weights[i];
    }
    sort(weights.begin(), weights.end());
    int i = 0, j = n - 1, count = 0;
    while (j >= i) {
        ll weight = weights[i] + weights[j];
        if (weight > maxWeight) {
            j--;
        } else {
            i++;
            j--;
        }
        count++;
    }
    cout << count << endl;
}
