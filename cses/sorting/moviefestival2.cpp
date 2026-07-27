#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<pair<int, int>> movies; // {end, start}

    for (int i = 0; i < n; i++) {
        int start, end;
        cin >> start >> end;
        movies.push_back({end, start});
    }

    sort(movies.begin(), movies.end());

    multiset<int> finishingTimes;

    for (int i = 0; i < k; i++) {
        finishingTimes.insert(0);
    }

    int watched = 0;

    for (auto [end, start] : movies) {
        // First finishing time strictly greater than start
        auto it = finishingTimes.upper_bound(start);

        // Nobody finishes by the movie's start
        if (it == finishingTimes.begin()) continue;

        // Largest finishing time <= start
        --it;

        finishingTimes.erase(it);
        finishingTimes.insert(end);
        watched++;
    }

    cout << watched << '\n';
}
