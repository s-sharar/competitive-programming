#include <bits/stdc++.h>
using namespace std;

// binary lifting

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int numPlanets, numQueries;
    cin >> numPlanets >> numQueries;

    const int LOG = 60; // enough for k up to 1e18

    // jump[p][v] = where you end up after 2^p teleports from v
    vector<vector<int>> jump(LOG, vector<int>(numPlanets));

    // 2^0 = 1 teleport
    for (int planet = 0; planet < numPlanets; planet++) {
        int nextPlanet;
        cin >> nextPlanet;
        --nextPlanet;
        jump[0][planet] = nextPlanet;
    }

    // build doubling table
    for (int p = 1; p < LOG; p++) {
        for (int planet = 0; planet < numPlanets; planet++) {
            int midPlanet = jump[p - 1][planet];          // after 2^(p-1)
            jump[p][planet] = jump[p - 1][midPlanet];     // another 2^(p-1)
        }
    }

    while (numQueries--) {
        int startPlanet;
        long long k;
        cin >> startPlanet >> k;
        --startPlanet;

        int currentPlanet = startPlanet;

        // apply jumps for each set bit in k
        for (int p = 0; p < LOG; p++) {
            if (k & (1LL << p)) {
                currentPlanet = jump[p][currentPlanet];
            }
        }

        cout << currentPlanet + 1 << "\n";
    }
}
