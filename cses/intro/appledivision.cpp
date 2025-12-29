#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int numApples;
    cin >> numApples;

    vector<long long> weights(numApples);
    long long totalWeight = 0;
    for (int i = 0; i < numApples; i++) {
        cin >> weights[i];
        totalWeight += weights[i];
    }

    long long minDifference = LLONG_MAX;

    int subsetCount = 1 << numApples;                 // 2^n subsets
    for (int mask = 0; mask < subsetCount; mask++) {
        long long groupWeight = 0;                    // sum of weights in subset "mask"
        for (int i = 0; i < numApples; i++) {
            if (mask & (1 << i)) { // check if current exists in the subset
                groupWeight += weights[i];
            }
        }

        long long difference = llabs(totalWeight - 2 * groupWeight);
        minDifference = min(minDifference, difference);
    }

    cout << minDifference << "\n";
    return 0;
}
