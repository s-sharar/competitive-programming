#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int numMachines;
    long long targetProducts;
    cin >> numMachines >> targetProducts;

    vector<long long> machineTime(numMachines);
    for (int i = 0; i < numMachines; i++) cin >> machineTime[i];

    auto canProduce = [&](long long timeLimit) -> bool {
        __int128 totalProduced = 0;
        for (long long t : machineTime) {
            totalProduced += timeLimit / t;
            if (totalProduced >= targetProducts) return true; // early stop
        }
        return totalProduced >= targetProducts;
    };

    long long low = 0;
    long long high = 1;
    while (!canProduce(high)) high *= 2;  // find an upper bound

    while (low + 1 < high) {
        long long mid = low + (high - low) / 2;
        if (canProduce(mid)) high = mid;
        else low = mid;
    }

    cout << high << "\n";
    return 0;
}
